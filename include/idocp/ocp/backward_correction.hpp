#ifndef IDOCP_BACKWARD_CORRECTION_HPP_
#define IDOCP_BACKWARD_CORRECTION_HPP_

#include <vector>

#include "Eigen/Core"

#include "idocp/robot/robot.hpp"
#include "idocp/ocp/split_kkt_matrix.hpp"
#include "idocp/ocp/split_kkt_residual.hpp"
#include "idocp/ocp/split_backward_correction.hpp"
#include "idocp/hybrid/hybrid_container.hpp"


namespace idocp {

///
/// @class BackwardCorrection
/// @brief Backward correction.
///
class BackwardCorrection {
public:
  ///
  /// @brief Construct factorizer.
  /// @param[in] robot Robot model. Must be initialized by URDF or XML.
  /// @param[in] N Number of discretization of the horizon. Must be more than 1. 
  /// @param[in] nthreads Number of the threads in solving the optimal control 
  /// problem. Must be positive. Default is 1.
  ///
  BackwardCorrection(const Robot& robot, const int N, const int max_num_impulse, 
                     const int nthreads);

  ///
  /// @brief Default constructor. 
  ///
  BackwardCorrection();

  ///
  /// @brief Destructor. 
  ///
  ~BackwardCorrection();
 
  ///
  /// @brief Default copy constructor. 
  ///
  BackwardCorrection(const BackwardCorrection&) = default;

  ///
  /// @brief Default copy operator. 
  ///
  BackwardCorrection& operator=(const BackwardCorrection&) = default;

  ///
  /// @brief Default move constructor. 
  ///
  BackwardCorrection(BackwardCorrection&&) noexcept = default;

  ///
  /// @brief Default move assign operator. 
  ///
  BackwardCorrection& operator=(BackwardCorrection&&) noexcept = default;

  void initAuxMat(ParNMPC& parnmpc, std::vector<Robot>& robots, 
                  const Solution& s, KKTMatrix& kkt_matrix);

  void coarseUpdate(ParNMPC& parnmpc, std::vector<Robot>& robots, 
                    const ContactSequence& contact_sequence, 
                    const Eigen::VectorXd& q, const Eigen::VectorXd& v, 
                    const Solution& s, KKTMatrix& kkt_matrix, 
                    KKTResidual& kkt_residual);

  void backwardCorrection(ParNMPC& parnmpc, std::vector<Robot>& robots, 
                          const KKTMatrix& kkt_matrix, 
                          const KKTResidual& kkt_residual, 
                          const Solution& s, Direction& d);

  double primalStepSize() const;

  double dualStepSize() const;

  static const Eigen::VectorXd& q_prev(const ParNMPCDiscretizer& discretizer, 
                                       const Eigen::VectorXd& q, 
                                       const Solution& s, 
                                       const int time_stage) {
    assert(time_stage >= 0);
    assert(time_stage < discretizer.N());
    if (discretizer.isTimeStageAfterImpulse(time_stage)) {
      return s.impulse[discretizer.impulseIndexBeforeTimeStage(time_stage)].q;
    }
    else if (discretizer.isTimeStageAfterLift(time_stage)) {
      return s.lift[discretizer.liftIndexBeforeTimeStage(time_stage)].q;
    }
    else if (time_stage > 0) {
      return s[time_stage-1].q;
    }
    else { 
      assert(time_stage == 0);
      return q;
    }
  }

  static const Eigen::VectorXd& v_prev(const ParNMPCDiscretizer& discretizer, 
                                       const Eigen::VectorXd& v, 
                                       const Solution& s, 
                                       const int time_stage) {
    assert(time_stage >= 0);
    assert(time_stage < discretizer.N());
    if (discretizer.isTimeStageAfterImpulse(time_stage)) {
      return s.impulse[discretizer.impulseIndexBeforeTimeStage(time_stage)].v;
    }
    else if (discretizer.isTimeStageAfterLift(time_stage)) {
      return s.lift[discretizer.liftIndexBeforeTimeStage(time_stage)].v;
    }
    else if (time_stage > 0) {
      return s[time_stage-1].v;
    }
    else { 
      assert(time_stage == 0);
      return v;
    }
  }

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

private:
  int N_, max_num_impulse_, nthreads_, N_all_;
  BackwardCorrector corrector_;
  Solution s_new_;
  std::vector<Eigen::MatrixXd> aux_mat_, aux_mat_impulse_, aux_mat_aux_, 
                               aux_mat_lift_;
  Eigen::VectorXd primal_step_sizes_, dual_step_sizes_;

};

} // namespace idocp

#endif // IDOCP_BACKWARD_CORRECTION_HPP_ 