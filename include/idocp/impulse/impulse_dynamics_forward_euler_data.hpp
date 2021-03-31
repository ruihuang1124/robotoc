#ifndef IDOCP_IMPULSE_DYNAMICS_FORWARD_EULER_DATA_HPP_ 
#define IDOCP_IMPULSE_DYNAMICS_FORWARD_EULER_DATA_HPP_

#include "Eigen/Core"
#include "idocp/robot/robot.hpp"
#include "idocp/robot/impulse_status.hpp"


namespace idocp {

///
/// @class ImpulseDynamicsForwardEulerData
/// @brief Data used in ImpulseDynamicsForwardEuler.
///
class ImpulseDynamicsForwardEulerData {
public:
  ///
  /// @brief Constructs a data.
  /// @param[in] robot Robot model. 
  ///
  ImpulseDynamicsForwardEulerData(const Robot& robot);

  ///
  /// @brief Default constructor. 
  ///
  ImpulseDynamicsForwardEulerData();

  ///
  /// @brief Destructor. 
  ///
  ~ImpulseDynamicsForwardEulerData();

  ///
  /// @brief Default copy constructor. 
  ///
  ImpulseDynamicsForwardEulerData(
      const ImpulseDynamicsForwardEulerData&) = default;

  ///
  /// @brief Default copy operator. 
  ///
  ImpulseDynamicsForwardEulerData& operator=(
      const ImpulseDynamicsForwardEulerData&) = default;
 
  ///
  /// @brief Default move constructor. 
  ///
  ImpulseDynamicsForwardEulerData(
      ImpulseDynamicsForwardEulerData&&) noexcept = default;

  ///
  /// @brief Default move assign operator. 
  ///
  ImpulseDynamicsForwardEulerData& operator=(
      ImpulseDynamicsForwardEulerData&&) noexcept = default;

  ///
  /// @brief Set the impulse status, i.e., set dimension of the impulses.
  /// @param[in] impulse_status Impulse status.
  ///
  void setImpulseStatus(const ImpulseStatus& impulse_status);

  Eigen::MatrixXd dImDddv;

  Eigen::Block<Eigen::MatrixXd> dImDCdqv();

  const Eigen::Block<const Eigen::MatrixXd> dImDCdqv() const;

  Eigen::Block<Eigen::MatrixXd> dImDCdq();

  const Eigen::Block<const Eigen::MatrixXd> dImDCdq() const;

  Eigen::Block<Eigen::MatrixXd> dImDdq();

  const Eigen::Block<const Eigen::MatrixXd> dImDdq() const;

  Eigen::Block<Eigen::MatrixXd> dCdq();

  const Eigen::Block<const Eigen::MatrixXd> dCdq() const;

  Eigen::Block<Eigen::MatrixXd> dCdv();

  const Eigen::Block<const Eigen::MatrixXd> dCdv() const;

  Eigen::Block<Eigen::MatrixXd> MJtJinv();

  const Eigen::Block<const Eigen::MatrixXd> MJtJinv() const;

  Eigen::Block<Eigen::MatrixXd> MJtJinv_dImDCdqv();

  const Eigen::Block<const Eigen::MatrixXd> MJtJinv_dImDCdqv() const;

  Eigen::Block<Eigen::MatrixXd> Qdvfqv();

  const Eigen::Block<const Eigen::MatrixXd> Qdvfqv() const;

  Eigen::VectorBlock<Eigen::VectorXd> ImDC();

  const Eigen::VectorBlock<const Eigen::VectorXd> ImDC() const;

  Eigen::VectorBlock<Eigen::VectorXd> ImD();

  const Eigen::VectorBlock<const Eigen::VectorXd> ImD() const;

  Eigen::VectorBlock<Eigen::VectorXd> C();

  const Eigen::VectorBlock<const Eigen::VectorXd> C() const;

  Eigen::VectorBlock<Eigen::VectorXd> MJtJinv_ImDC();

  const Eigen::VectorBlock<const Eigen::VectorXd> MJtJinv_ImDC() const;

  Eigen::VectorBlock<Eigen::VectorXd> ldvf();

  const Eigen::VectorBlock<const Eigen::VectorXd> ldvf() const;

  Eigen::VectorBlock<Eigen::VectorXd> ldv();

  const Eigen::VectorBlock<const Eigen::VectorXd> ldv() const;

  Eigen::VectorBlock<Eigen::VectorXd> lf();

  const Eigen::VectorBlock<const Eigen::VectorXd> lf() const;

private:
  Eigen::MatrixXd dImDCdqv_full_, dCddv_full_, MJtJinv_full_, 
                  MJtJinv_dImDCdqv_full_, Qdvfqv_full_;
  Eigen::VectorXd ImDC_full_, MJtJinv_ImDC_full_, ldvf_full_;
  int dimv_, dimf_, dimvf_;

};

} // namespace idocp 

#include "idocp/impulse/impulse_dynamics_forward_euler_data.hxx"

#endif // IDOCP_IMPULSE_DYNAMICS_FORWARD_EULER_DATA_HPP_ 