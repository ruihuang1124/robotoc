#ifndef ROBOTOC_SPLIT_KKT_MATRIX_HPP_
#define ROBOTOC_SPLIT_KKT_MATRIX_HPP_

#include <iostream>

#include "Eigen/Core"

#include "robotoc/robot/robot.hpp"
#include "robotoc/robot/contact_status.hpp"


namespace robotoc {

///
/// @class SplitKKTMatrix
/// @brief The KKT matrix split into a time stage.
///
class SplitKKTMatrix {
public:
  ///
  /// @brief Construct a split KKT matrix.
  /// @param[in] robot Robot model. 
  ///
  SplitKKTMatrix(const Robot& robot);

  ///
  /// @brief Default constructor. 
  ///
  SplitKKTMatrix();

  ///
  /// @brief Destructor. 
  ///
  ~SplitKKTMatrix();

  ///
  /// @brief Default copy constructor. 
  ///
  SplitKKTMatrix(const SplitKKTMatrix&) = default;

  ///
  /// @brief Default copy operator. 
  ///
  SplitKKTMatrix& operator=(const SplitKKTMatrix&) = default;

  ///
  /// @brief Default move constructor. 
  ///
  SplitKKTMatrix(SplitKKTMatrix&&) noexcept = default;

  ///
  /// @brief Default move assign operator. 
  ///
  SplitKKTMatrix& operator=(SplitKKTMatrix&&) noexcept = default;

  ///
  /// @brief Set contact status, i.e., set dimension of the contacts.
  /// @param[in] contact_status Contact status.
  ///
  void setContactStatus(const ContactStatus& contact_status);

  ///
  /// @brief Jacobian of the state equation w.r.t. the state x.
  ///
  Eigen::MatrixXd Fxx;

  ///
  /// @brief Jacobian of the state equation (w.r.t. q) w.r.t. q.
  /// @return Reference to the block of the Jacobian of the constraints. Size 
  /// is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Fqq();

  ///
  /// @brief const version of SplitKKTMatrix::Fqq().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Fqq() const;

  ///
  /// @brief Jacobian of the state equation (w.r.t. q) w.r.t. v.
  /// @return Reference to the block of the Jacobian of the constraints. Size 
  /// is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Fqv();

  ///
  /// @brief const version of SplitKKTMatrix::Fqv().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Fqv() const;

  ///
  /// @brief Jacobian of the state equation (w.r.t. v) w.r.t. q.
  /// @return Reference to the block of the Jacobian of the constraints. Size 
  /// is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Fvq();

  ///
  /// @brief const version of SplitKKTMatrix::Fvq().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Fvq() const;

  ///
  /// @brief Jacobian of the state equation (w.r.t. v) to v.
  /// @return Reference to the block of the Jacobian of the constraints. Size 
  /// is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Fvv();

  ///
  /// @brief const version of SplitKKTMatrix::Fvv().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Fvv() const;

  ///
  /// @brief Jacobian of the state equation (w.r.t. v) w.r.t. u. 
  ///
  Eigen::MatrixXd Fvu;

  ///
  /// @brief Hessian w.r.t. to the state x and state x.
  ///
  Eigen::MatrixXd Qxx;

  ///
  /// @brief Hessian w.r.t. the configuration q and configuration q.
  /// @return Reference to the Hessian. Size is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qqq();

  ///
  /// @brief const version of SplitKKTMatrix::Qqq().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qqq() const;

  ///
  /// @brief Hessian w.r.t. the configuration q and joint velocity v. 
  /// @return Reference to the Hessian. Size is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qqv();

  ///
  /// @brief const version of SplitKKTMatrix::Qqv().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qqv() const;

  ///
  /// @brief Hessian w.r.t. the joint velocity v and configuration q. 
  /// @return Reference to the Hessian. Size is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qvq();

  ///
  /// @brief const version of SplitKKTMatrix::Qvq().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qvq() const;

  ///
  /// @brief Hessian w.r.t. the joint velocity v and joint velocity v.
  /// @return Reference to the Hessian. Size is Robot::dimv() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qvv();

  ///
  /// @brief const version of SplitKKTMatrix::Qvv().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qvv() const;

  ///
  /// @brief Hessian w.r.t. the acceleration a and acceleration a. 
  ///
  Eigen::MatrixXd Qaa;

  ///
  /// @brief Hessian w.r.t. the state x and the control input torques u.
  ///
  Eigen::MatrixXd Qxu;

  ///
  /// @brief Hessian of the Lagrangian with respect to the configuration q and
  /// control input torques u. 
  /// @return Reference to the Hessian. Size is Robot::dimu() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qqu();

  ///
  /// @brief const version of SplitKKTMatrix::Qqu().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qqu() const;

  ///
  /// @brief Hessian of the Lagrangian with respect to the velocity v and
  /// control input torques u. 
  /// @return Reference to the Hessian. Size is Robot::dimu() x Robot::dimv().
  ///
  Eigen::Block<Eigen::MatrixXd> Qvu();

  ///
  /// @brief const version of SplitKKTMatrix::Qvu().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qvu() const;

  ///
  /// @brief Hessian w.r.t. the control input torques u and the control input 
  /// torques u.
  ///
  Eigen::MatrixXd Quu;

  ///
  /// @brief Hessian of the Lagrangian with respect to the contact forces f. 
  /// @return Reference to the Hessian. Size is 
  /// ContactStatus::dimf() x ContactStatus::dimf().
  ///
  Eigen::Block<Eigen::MatrixXd> Qff();

  ///
  /// @brief const version of SplitKKTMatrix::Qff().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qff() const;

  ///
  /// @brief Hessian of the Lagrangian with respect to the configuration and 
  /// contact forces. 
  /// @return Reference to the Hessian. Size is 
  /// Robot::dimv() x ContactStatus::dimf().
  ///
  Eigen::Block<Eigen::MatrixXd> Qqf();

  ///
  /// @brief const version of SplitKKTMatrix::Qqf().
  ///
  const Eigen::Block<const Eigen::MatrixXd> Qqf() const;

  ///
  /// @brief Jacobian of the state equation (w.r.t. q) w.r.t. q_prev.
  /// If Robot::hasFloatingBase() is true, size is Robot::dimv() x Robot::dimv().
  /// Otherwise, 0 x 0.
  ///
  Eigen::MatrixXd Fqq_prev;

  ///
  /// @brief Derivative of the discrete time state equation w.r.t. the 
  /// length of the time interval. 
  ///
  Eigen::VectorXd fx;

  ///
  /// @brief Derivative of the discrete-time state equation w.r.t. the 
  /// configuration q w.r.t. the length of the time interval. 
  /// @return Reference to the vector. Size is Robot::dimv().
  ///
  Eigen::VectorBlock<Eigen::VectorXd> fq();

  ///
  /// @brief const version of SplitKKTMatrix::fq().
  ///
  const Eigen::VectorBlock<const Eigen::VectorXd> fq() const;

  ///
  /// @brief Derivative of the discrete-time state equation w.r.t. the 
  /// velocity v w.r.t. the length of the time interval. 
  /// @return Reference to the vector. Size is Robot::dimv().
  ///
  Eigen::VectorBlock<Eigen::VectorXd> fv();

  ///
  /// @brief const version of SplitKKTMatrix::fv().
  ///
  const Eigen::VectorBlock<const Eigen::VectorXd> fv() const;

  ///
  /// @brief Hessian of the Lagrangian w.r.t. the switching time. 
  ///
  double Qtt;

  ///
  /// @brief Hessian of the Lagrangian w.r.t. the previoius switching time. 
  ///
  double Qtt_prev;

  ///
  /// @brief Derivative of the Hamiltonian w.r.t. the state. 
  ///
  Eigen::VectorXd hx;

  ///
  /// @brief Derivative of the Hamiltonian w.r.t. the configuration q. 
  /// @return Reference to the vector. Size is Robot::dimv().
  ///
  Eigen::VectorBlock<Eigen::VectorXd> hq();

  ///
  /// @brief const version of SplitKKTMatrix::hq().
  ///
  const Eigen::VectorBlock<const Eigen::VectorXd> hq() const;

  ///
  /// @brief Derivative of the Hamiltonian w.r.t. the velocity v. 
  /// @return Reference to the vector. Size is Robot::dimv().
  ///
  Eigen::VectorBlock<Eigen::VectorXd> hv();

  ///
  /// @brief const version of SplitKKTMatrix::hv().
  ///
  const Eigen::VectorBlock<const Eigen::VectorXd> hv() const;

  ///
  /// @brief Derivative of the Hamiltonian w.r.t. the control input. 
  ///
  Eigen::VectorXd hu;

  /// 
  /// @brief Derivative of the Hamiltonian w.r.t. the acceleration.
  /// 
  Eigen::VectorXd ha;

  ///
  /// @brief Derivative of the Hamiltonian w.r.t. the stack of the contact 
  /// forces f. 
  /// @return Reference to the derivative w.r.t.f. Size is 
  /// SplitKKTMatrix::dimf().
  ///
  Eigen::VectorBlock<Eigen::VectorXd> hf();

  ///
  /// @brief const version of SplitKKTMatrix::hf().
  ///
  const Eigen::VectorBlock<const Eigen::VectorXd> hf() const;

  ///
  /// @brief Set the all components zero.
  ///
  void setZero();

  ///
  /// @brief Returns the dimension of the stack of contact forces at the current 
  /// contact status.
  /// @return Dimension of the stack of contact forces.
  ///
  int dimf() const;

  ///
  /// @brief Checks dimensional consistency of each component. 
  /// @return true if the dimension is consistent. false if not.
  ///
  bool isDimensionConsistent() const;

  ///
  /// @brief Checks the equivalence of two SplitKKTMatrix.
  /// @param[in] other Other object.
  /// @return true if this and other is same. false otherwise.
  ///
  bool isApprox(const SplitKKTMatrix& other) const;

  ///
  /// @brief Checks this has at least one NaN.
  /// @return true if this has at least one NaN. false otherwise.
  ///
  bool hasNaN() const;

  ///
  /// @brief Set by random value based on the current contact status. 
  ///
  void setRandom();

  ///
  /// @brief Set by random value. Contact status is reset.
  /// @param[in] contact_status Contact status.
  ///
  void setRandom(const ContactStatus& contact_status);

  ///
  /// @brief Generates split KKT matrix filled randomly.
  /// @return Split KKT matrix filled randomly.
  /// @param[in] robot Robot model. 
  ///
  static SplitKKTMatrix Random(const Robot& robot);

  ///
  /// @brief Generates split KKT matrix filled randomly.
  /// @return Split KKT matrix filled randomly.
  /// @param[in] robot Robot model. 
  /// @param[in] contact_status Contact status.
  ///
  static SplitKKTMatrix Random(const Robot& robot, 
                               const ContactStatus& contact_status);

  ///
  /// @brief Displays the split KKT matrix onto a ostream.
  ///
  void disp(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, 
                                  const SplitKKTMatrix& kkt_matrix);

private:
  Eigen::MatrixXd Qff_full_, Qqf_full_;
  Eigen::VectorXd hf_full_;
  bool has_floating_base_;
  int dimv_, dimx_, dimu_, dimf_;

};

} // namespace robotoc 

#include "robotoc/ocp/split_kkt_matrix.hxx"

#endif // ROBOTOC_SPLIT_KKT_MATRIX_HPP_ 