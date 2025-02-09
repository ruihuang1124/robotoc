#include <string>
#include <memory>

#include "Eigen/Core"

#include "robotoc/solver/ocp_solver.hpp"
#include "robotoc/ocp/ocp.hpp"
#include "robotoc/robot/robot.hpp"
#include "robotoc/hybrid/contact_sequence.hpp"
#include "robotoc/cost/cost_function.hpp"
#include "robotoc/cost/configuration_space_cost.hpp"
#include "robotoc/cost/local_contact_force_cost.hpp"
#include "robotoc/constraints/constraints.hpp"
#include "robotoc/constraints/joint_position_lower_limit.hpp"
#include "robotoc/constraints/joint_position_upper_limit.hpp"
#include "robotoc/constraints/joint_velocity_lower_limit.hpp"
#include "robotoc/constraints/joint_velocity_upper_limit.hpp"
#include "robotoc/constraints/joint_torques_lower_limit.hpp"
#include "robotoc/constraints/joint_torques_upper_limit.hpp"
#include "robotoc/constraints/friction_cone.hpp"
#include "robotoc/solver/solver_options.hpp"

#include "robotoc/utils/ocp_benchmarker.hpp"


int main () {
  // Create a robot with contacts.
  const int LF_foot_id = 12;
  const int LH_foot_id = 22;
  const int RF_foot_id = 32;
  const int RH_foot_id = 42;
  const std::vector<int> contact_frames = {LF_foot_id, LH_foot_id, RF_foot_id, RH_foot_id}; 
  const std::vector<robotoc::ContactType> contact_types = {robotoc::ContactType::PointContact, 
                                                           robotoc::ContactType::PointContact,
                                                           robotoc::ContactType::PointContact,
                                                           robotoc::ContactType::PointContact};
  const std::string path_to_urdf = "../anymal_b_simple_description/urdf/anymal.urdf";
  const double baumgarte_time_step = 0.5 / 20;
  robotoc::Robot robot(path_to_urdf, robotoc::BaseJointType::FloatingBase, 
                       contact_frames, contact_types, baumgarte_time_step);

  // Create a cost function.
  auto cost = std::make_shared<robotoc::CostFunction>();
  Eigen::VectorXd q_standing(robot.dimq());
  q_standing << 0, 0, 0.4792, 0, 0, 0, 1, 
                -0.1,  0.7, -1.0, 
                -0.1, -0.7,  1.0, 
                 0.1,  0.7, -1.0, 
                 0.1, -0.7,  1.0;
  Eigen::VectorXd v_ref(robot.dimv());
  v_ref << 0, 0, 0, 0, 0, 0, 
           0, 0, 0, 
           0, 0, 0, 
           0, 0, 0, 
           0, 0, 0;
  auto config_cost = std::make_shared<robotoc::ConfigurationSpaceCost>(robot);
  config_cost->set_q_weight(Eigen::VectorXd::Constant(robot.dimv(), 10));
  config_cost->set_q_ref(q_standing);
  config_cost->set_q_weight_terminal(Eigen::VectorXd::Constant(robot.dimv(), 10));
  config_cost->set_v_weight(Eigen::VectorXd::Constant(robot.dimv(), 1));
  config_cost->set_v_weight_terminal(Eigen::VectorXd::Constant(robot.dimv(), 1));
  config_cost->set_a_weight(Eigen::VectorXd::Constant(robot.dimv(), 0.01));
  cost->push_back(config_cost);
  auto local_contact_force_cost = std::make_shared<robotoc::LocalContactForceCost>(robot);
  std::vector<Eigen::Vector3d> f_weight, f_ref;
  for (int i=0; i<contact_frames.size(); ++i) {
    Eigen::Vector3d fw; 
    fw << 0.001, 0.001, 0.001;
    f_weight.push_back(fw);
    Eigen::Vector3d fr; 
    fr << 0, 0, 70;
    f_ref.push_back(fr);
  }
  local_contact_force_cost->set_f_weight(f_weight);
  local_contact_force_cost->set_f_ref(f_ref);
  cost->push_back(local_contact_force_cost);

  // Create inequality constraints.
  auto constraints = std::make_shared<robotoc::Constraints>();
  auto joint_position_lower = std::make_shared<robotoc::JointPositionLowerLimit>(robot);
  auto joint_position_upper = std::make_shared<robotoc::JointPositionUpperLimit>(robot);
  auto joint_velocity_lower = std::make_shared<robotoc::JointVelocityLowerLimit>(robot);
  auto joint_velocity_upper = std::make_shared<robotoc::JointVelocityUpperLimit>(robot);
  auto joint_torques_lower  = std::make_shared<robotoc::JointTorquesLowerLimit>(robot);
  auto joint_torques_upper  = std::make_shared<robotoc::JointTorquesUpperLimit>(robot);
  const double mu = 0.7;
  auto friction_cone        = std::make_shared<robotoc::FrictionCone>(robot, mu);
  constraints->push_back(joint_position_lower);
  constraints->push_back(joint_position_upper);
  constraints->push_back(joint_velocity_lower);
  constraints->push_back(joint_velocity_upper);
  constraints->push_back(joint_torques_lower);
  constraints->push_back(joint_torques_upper);
  constraints->push_back(friction_cone);

  // Create the contact sequence
  auto contact_sequence = std::make_shared<robotoc::ContactSequence>(robot);

  auto contact_status_standing = robot.createContactStatus();
  contact_status_standing.activateContacts({0, 1, 2, 3});
  robot.updateFrameKinematics(q_standing);
  const std::vector<Eigen::Vector3d> contact_positions = {robot.framePosition(LF_foot_id), 
                                                       robot.framePosition(LH_foot_id),
                                                       robot.framePosition(RF_foot_id),
                                                       robot.framePosition(RH_foot_id)};
  contact_status_standing.setContactPlacements(contact_positions);
  contact_sequence->init(contact_status_standing);

  // Create OCPSolver
  const double T = 0.5;
  const int N = 20;
  robotoc::OCP ocp(robot, cost, constraints, contact_sequence, T, N);
  auto solver_options = robotoc::SolverOptions::defaultOptions();
  const int nthreads = 4;
  robotoc::OCPSolver ocp_solver(ocp, solver_options, nthreads);

  // Initial time and initial state
  const double t = 0;
  const Eigen::VectorXd q = q_standing;
  const Eigen::VectorXd v = Eigen::VectorXd::Zero(robot.dimv());

  ocp_solver.setSolution("q", q);
  ocp_solver.setSolution("v", v);
  Eigen::Vector3d f_init;
  f_init << 0, 0, 0.25*robot.totalWeight();
  ocp_solver.setSolution("f", f_init);

  ocp_solver.initConstraints(t);
  ocp_solver.solve(t, q, v);
  std::cout << ocp_solver.getSolverStatistics() << std::endl;

  const int num_iteration = 10000;
  robotoc::benchmark::CPUTime(ocp_solver, t, q, v, num_iteration);

  // std::cout << robot << std::endl;

  return 0;
}
