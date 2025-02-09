#ifndef ROBOTOC_IMPULSE_STATE_EQUATION_HPP_
#define ROBOTOC_IMPULSE_STATE_EQUATION_HPP_

#include "Eigen/Core"

#include "robotoc/robot/robot.hpp"
#include "robotoc/robot/se3_jacobian_inverse.hpp"
#include "robotoc/ocp/split_solution.hpp"
#include "robotoc/impulse/impulse_split_solution.hpp"
#include "robotoc/impulse/impulse_split_direction.hpp"
#include "robotoc/impulse/impulse_split_kkt_residual.hpp"
#include "robotoc/impulse/impulse_split_kkt_matrix.hpp"


namespace robotoc {

///
/// @class ImpulseStateEquation
/// @brief State equation. Only represent kinematic relation
/// between stages.
///
class ImpulseStateEquation {
public:
  ///
  /// @brief Constructs an impulse state equation.
  /// @param[in] robot Robot model. 
  ///
  ImpulseStateEquation(const Robot& robot);

  ///
  /// @brief Default constructor.  
  ///
  ImpulseStateEquation();
  
  ///
  /// @brief Destructor. 
  ///
  ~ImpulseStateEquation();

  ///
  /// @brief Default copy constructor. 
  ///
  ImpulseStateEquation(const ImpulseStateEquation&) = default;

  ///
  /// @brief Default copy assign operator. 
  ///
  ImpulseStateEquation& operator=(const ImpulseStateEquation&) = default;

  ///
  /// @brief Default move constructor. 
  ///
  ImpulseStateEquation(ImpulseStateEquation&&) noexcept = default;

  ///
  /// @brief Default move assign operator. 
  ///
  ImpulseStateEquation& operator=(ImpulseStateEquation&&) noexcept = default;

  ///
  /// @brief Computes the residual in the impulse state equation. 
  /// @param[in] robot Robot model. 
  /// @param[in] s Solution at the current impulse stage. 
  /// @param[in] q_next Configuration at the next time stage. 
  /// @param[in] v_next Generalized velocity at the next time stage. 
  /// @param[in, out] kkt_residual Impulse split KKT residual at the current 
  /// impulse stage. 
  ///
  static void evalStateEquation(const Robot& robot, 
                                const ImpulseSplitSolution& s, 
                                const Eigen::VectorXd& q_next, 
                                const Eigen::VectorXd& v_next, 
                                ImpulseSplitKKTResidual& kkt_residual);

  ///
  /// @brief Linearizes the impulse state equation. 
  /// @param[in] robot Robot model. 
  /// @param[in] q_prev Configuration at the previous time stage. 
  /// @param[in] s Solution at the current impulse stage. 
  /// @param[in] s_next Solution at the next time stage. 
  /// @param[in, out] kkt_matrix Impulse split KKT matrix at the current impulse 
  /// stage. 
  /// @param[in, out] kkt_residual Impulse split KKT residual at the current 
  /// impulse stage. 
  ///
  static void linearizeStateEquation(const Robot& robot, 
                                     const Eigen::VectorXd& q_prev, 
                                     const ImpulseSplitSolution& s, 
                                     const SplitSolution& s_next, 
                                     ImpulseSplitKKTMatrix& kkt_matrix, 
                                     ImpulseSplitKKTResidual& kkt_residual);

  ///
  /// @brief Corrects the linearized state equation using the Jacobian of the 
  /// Lie group. 
  /// @param[in] robot Robot model. 
  /// @param[in] s Solution at the current impulse stage. 
  /// @param[in] s_next Solution at the next time stage. 
  /// @param[in, out] kkt_matrix Impulse split KKT matrix at the current impulse 
  /// stage. 
  /// @param[in, out] kkt_residual Impulse split KKT residual at the current 
  /// impulse stage. 
  ///
  void correctLinearizedStateEquation(const Robot& robot, 
                                      const ImpulseSplitSolution& s, 
                                      const SplitSolution& s_next, 
                                      ImpulseSplitKKTMatrix& kkt_matrix, 
                                      ImpulseSplitKKTResidual& kkt_residual);

  ///
  /// @brief Corrects the costate direction using the Jacobian of the Lie group. 
  /// @param[in, out] d Split direction. 
  ///
  void correctCostateDirection(ImpulseSplitDirection& d) {
    if (has_floating_base_) {
      Fq_tmp_ = Fqq_prev_inv_.transpose() * d.dlmdgmm.template head<6>();
      d.dlmdgmm.template head<6>() = - Fq_tmp_;
    }
  }

private:
  Eigen::MatrixXd Fqq_inv_, Fqq_prev_inv_, Fqq_tmp_;  
  Eigen::VectorXd Fq_tmp_;
  SE3JacobianInverse se3_jac_inverse_;
  bool has_floating_base_;

};

} // namespace robotoc 

#endif // ROBOTOC_IMPULSE_STATE_EQUATION_HPP_ 