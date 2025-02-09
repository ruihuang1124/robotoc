#ifndef ROBOTOC_TIME_DISCRETIZATION_HPP_ 
#define ROBOTOC_TIME_DISCRETIZATION_HPP_

#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <iostream>

#include "robotoc/hybrid/discretization_method.hpp"
#include "robotoc/hybrid/contact_sequence.hpp"
#include "robotoc/hybrid/grid_info.hpp"


namespace robotoc {

///
/// @class TimeDiscretization
/// @brief Time discretization of the hybrid optimal control problem.
///
class TimeDiscretization {
public:
  ///
  /// @brief Constructor. 
  /// @param[in] T Length of the horizon. Must be positive.
  /// @param[in] N Number of the discretization grids of the horizon except for 
  /// the discrete events. Must be positive.
  /// @param[in] reserved_num_discrete_events Reserved size of each discrete 
  /// events (impulse and lift) to avoid dynamic memory allocation. Must be 
  /// non-negative. Default is 0.
  ///
  TimeDiscretization(const double T, const int N, 
                     const int reserved_num_discrete_events=0);

  ///
  /// @brief Default constructor. 
  ///
  TimeDiscretization();

  ///
  /// @brief Destructor. 
  ///
  ~TimeDiscretization();

  ///
  /// @brief Default copy constructor. 
  ///
  TimeDiscretization(const TimeDiscretization&) = default;

  ///
  /// @brief Default copy assign operator. 
  ///
  TimeDiscretization& operator=(const TimeDiscretization&) = default;

  ///
  /// @brief Default move constructor. 
  ///
  TimeDiscretization(TimeDiscretization&&) noexcept = default;

  ///
  /// @brief Default move assign operator. 
  ///
  TimeDiscretization& operator=(TimeDiscretization&&) noexcept = default;

  ///
  /// @brief Sets the discretization method of the optimal contro problem. 
  /// @param[in] discretization_method The discretization method.
  ///
  void setDiscretizationMethod(const DiscretizationMethod discretization_method);

  ///
  /// @brief Discretizes the finite horizon taking into account the discrete 
  /// events.
  /// @param[in] contact_sequence Shared ptr to the contact sequence.
  /// @param[in] t Initial time of the horizon.
  /// @note If the discretization method is DiscretizationMethod::GridBased, 
  /// this funtion can change the structure of the discretization, i.e., 
  /// the number of grids on each contact phase. If the discretization method is 
  /// DiscretizationMethod::PhaseBased, this function keeps the structure of the 
  /// discretization. In the latter case, meshRefinement() is needed to chagne 
  /// the discretization structure.
  ///
  void discretize(const std::shared_ptr<ContactSequence>& contact_sequence, 
                  const double t);

  ///
  /// @brief Applies the mesh refinement and changes the structure of the 
  /// discretization, i.e., the number of grids on each contact phase for 
  /// the discretization method DiscretizationMethod::PhaseBased.
  /// Specifically, this function reduces the numbers of the grids
  /// from the phases where the solution is relatively accurate and increases
  /// them to the phases where the solution is relatively inaccurate while 
  /// keeping the total number of the discretization grids including the 
  /// discrete events. 
  /// @param[in] contact_sequence Contact sequence.
  /// @param[in] t Initial time of the horizon.
  /// @note This function do nothing if the discretization method is 
  /// DiscretizationMethod::GridBased.
  ///
  void meshRefinement(const std::shared_ptr<ContactSequence>& contact_sequence, 
                      const double t);

  ///
  /// @return Number of the time stages on the horizon. 
  ///
  int N() const;

  ///
  /// @return Number of the impulse stages on the horizon. 
  ///
  int N_impulse() const;

  ///
  /// @return Number of the lift stages on the horizon. 
  ///
  int N_lift() const; 

  ///
  /// @return Ideal number of the discretization grids on the horizon. 
  ///
  int N_ideal() const;

  ///
  /// @param[in] phase Contact phase of interest. 
  /// @return Number of the discretization grids on the specified contact phase. 
  ///
  int N_phase(const int phase) const;

  ///
  /// @brief Returns the total number of the contact phases. 
  /// @return Total number of the contact phases.
  ///
  int numContactPhases() const;

  ///
  /// @brief Returns the total number of the discrete events, that is, sum of 
  /// N_impulse() and N_lift(). 
  /// @return Total number of the discrete events.
  ///
  int numDiscreteEvents() const;

  ///
  /// @brief Returns the contact phase of the specified time stage. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return Contact phase of the time stage. 
  ///
  int contactPhase(const int time_stage) const;

  ///
  /// @brief Returns the contact phase after the specified impulse event. 
  /// @param[in] impulse_index Index of the impulse event of interest. 
  /// @return Contact phase after the impulse event. 
  ///
  int contactPhaseAfterImpulse(const int impulse_index) const;

  ///
  /// @brief Returns the contact phase after the specified lift event. 
  /// @param[in] lift_index Index of the lift event of interest. 
  /// @return Contact phase after the lift event. 
  ///
  int contactPhaseAfterLift(const int lift_index) const;

  ///
  /// @brief Returns the impulse event index after the specified time stage. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return Impulse event index after the time stage. 
  ///
  int impulseIndexAfterTimeStage(const int time_stage) const;

  ///
  /// @brief Returns the lift event index after the specified time stage. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return Lift event index after the time stage. 
  ///
  int liftIndexAfterTimeStage(const int time_stage) const;

  ///
  /// @brief Returns the time stage before the specified impulse event. 
  /// @param[in] impulse_index Index of the impulse event of interest. 
  /// @return Time stage before the impulse event. 
  ///
  int timeStageBeforeImpulse(const int impulse_index) const;

  ///
  /// @brief Returns the time stage after the specified impulse event. 
  /// @param[in] impulse_index Index of the impulse event of interest. 
  /// @return Time stage after the impulse event. 
  ///
  int timeStageAfterImpulse(const int impulse_index) const;

  ///
  /// @brief Returns the time stage before the specified lift event. 
  /// @param[in] lift_index Index of the lift event of interest. 
  /// @return Time stage before the lift event. 
  ///
  int timeStageBeforeLift(const int lift_index) const;

  ///
  /// @brief Returns the time stage after the specified lift event. 
  /// @param[in] lift_index Index of the lift event of interest. 
  /// @return Time stage after the lift event. 
  ///
  int timeStageAfterLift(const int lift_index) const;

  ///
  /// @brief Checks wheather the time stage is just before an impulse event.
  /// @param[in] time_stage Time stage of interest. 
  /// @return true if the time stage is just before an impulse event. 
  /// false if not.
  ///
  bool isTimeStageBeforeImpulse(const int time_stage) const;

  ///
  /// @brief Checks wheather the time stage is just after an impulse event.
  /// @param[in] time_stage Time stage of interest. 
  /// @return true if the time stage is just after an impulse event. 
  /// false if not.
  ///
  bool isTimeStageAfterImpulse(const int time_stage) const;

  ///
  /// @brief Checks wheather the time stage is just before a lift event. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return true if the time stage is just before the lift. false if not.
  ///
  bool isTimeStageBeforeLift(const int time_stage) const;

  ///
  /// @brief Checks wheather the time stage is just after a lift event. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return true if the time stage is just after the lift. false if not.
  ///
  bool isTimeStageAfterLift(const int time_stage) const;

  ///
  /// @brief Returns the initial time of the horizon. 
  /// @return Initial time of the horizon.
  ///
  double t0() const;

  ///
  /// @brief Returns the final time of the horizon. 
  /// @return Final time of the horizon.
  ///
  double tf() const;

  ///
  /// @brief Returns the time of the specified impulse event. 
  /// @param[in] impulse_index Index of impulse event of interest. 
  /// @return Time of the impulse event of interest.
  ///
  double impulseTime(const int impulse_index) const;

  ///
  /// @brief Returns the time of the specified lift event. 
  /// @param[in] lift_index Index of lift event of interest. 
  /// @return Time of the lift event of interest.
  ///
  double liftTime(const int lift_index) const;

  ///
  /// @brief Returns the maximum time step over the horizon. 
  /// @return The maximum time step.
  ///
  double dt_max() const;

  ///
  /// @brief Returns the ideal time step. 
  /// @return The ideal time step.
  ///
  double dt_ideal() const;

  ///
  /// @brief Returns the grid info of the specified time stage. 
  /// @param[in] time_stage Time stage of interest. 
  /// @return Grid info of the time stage of interest.
  ///
  const GridInfo& gridInfo(const int time_stage) const;

  ///
  /// @brief Returns the grid info of the specified impulse stage. 
  /// @param[in] impulse_index Index of impulse event of interest. 
  /// @return Grid info of the impulse stage of the impulse event.
  ///
  const GridInfo& gridInfoImpulse(const int impulse_index) const;

  ///
  /// @brief Returns the grid info of the specified aux stage of an impulse. 
  /// @param[in] impulse_index Index of impulse event of interest. 
  /// @return Grid info of the aux stage of the impulse event.
  ///
  const GridInfo& gridInfoAux(const int impulse_index) const;

  ///
  /// @brief Returns the grid info of the specified lift stage of a lift. 
  /// @param[in] lift_index Index of lift event of interest. 
  /// @return Grid info of the aux stage of the impulse event.
  ///
  const GridInfo& gridInfoLift(const int lift_index) const;

  ///
  /// @brief Checks wheather the STO is enabled for the specified discrete event. 
  /// @param[in] event_index Index of the discrete event of interest. 
  /// @return true if the STO is enabled. false if not.
  ///
  bool isSTOEnabledEvent(const int event_index) const;

  ///
  /// @brief Checks wheather the STO is enabled at the specified phase duration. 
  /// @param[in] phase Phase of interest. 
  /// @return true if the STO is enabled. false if not.
  ///
  bool isSTOEnabledPhase(const int phase) const;

  ///
  /// @brief Checks wheather the STO is enabled at the next phase duration of 
  /// the specified phase. 
  /// @param[in] phase Phase of interest. 
  /// @return true if the STO is enabled. false if not.
  ///
  bool isSTOEnabledNextPhase(const int phase) const;

  ///
  /// @brief Checks wheather the STO is enabled for the specified impulse event. 
  /// @param[in] impulse_index Index of the impulse of interest. 
  /// @return true if the STO is enabled. false if not.
  ///
  bool isSTOEnabledImpulse(const int impulse_index) const;

  ///
  /// @brief Checks wheather the STO is enabled for the specified lift event. 
  /// @param[in] lift_index Index of the lift of interest. 
  /// @return true if the STO is enabled. false if not.
  ///
  bool isSTOEnabledLift(const int lift_index) const;

  ///
  /// @brief Returns the event index of the specified impulse event. 
  /// @param[in] impulse_index Index of the impulse of interest. 
  /// @return The event index of the specified impulse event.
  ///
  int eventIndexImpulse(const int impulse_index) const;

  ///
  /// @brief Returns the event index of the specified lift event. 
  /// @param[in] lift_index Index of the lift of interest. 
  /// @return The event index of the specified lift event.
  ///
  int eventIndexLift(const int lift_index) const;

  ///
  /// @brief Returns the event type of the specified discrete event.
  /// @return Event type of the discrete event. 
  ///
  DiscreteEventType eventType(const int event_index) const;

  ///
  /// @brief Returns the current discretization method. 
  /// @return The current discretization method.
  ///
  DiscretizationMethod discretizationMethod() const;

  ///
  /// @brief Reserve the discrete-event data. 
  /// @param[in] reserved_num_discrete_events Reserved size of discrete events  
  /// on the horizon. Must be non-negative.
  ///
  void reserve(const int reserved_num_discrete_events);

  ///
  /// @return Reserved size of the discrete-event data. 
  ///
  int reservedNumDiscreteEvents() const;

  ///
  /// @brief Returns the time steps of the discretization grids over the horzion. 
  /// @return Time steps.
  ///
  std::vector<double> timeSteps() const;

  ///
  /// @brief Returns the time points of the discretization grids over the horzion. 
  /// @return Time points.
  ///
  std::vector<double> timePoints() const;

  ///
  /// @brief Checks wheather the optimal control problem is tractable. 
  /// @return true if the optimal control problem is consistent. false if not.
  ///
  bool isFormulationTractable() const;

  ///
  /// @brief Checks wheather the switching times are consistent. 
  /// @return true if the switching times are consistent. false if not.
  ///
  bool isSwitchingTimeConsistent() const;

  ///
  /// @brief Displays the discretization of the hybrid optimal control problem 
  /// onto a ostream.
  ///
  void disp(std::ostream& os) const;

  friend std::ostream& operator<<(std::ostream& os, 
                                  const TimeDiscretization& discretization);

private:
  double T_, dt_ideal_, max_dt_, eps_;
  int N_, N_ideal_, N_impulse_, N_lift_, reserved_num_discrete_events_;
  std::vector<int> N_phase_, contact_phase_from_time_stage_, 
                   impulse_index_after_time_stage_, 
                   lift_index_after_time_stage_, time_stage_before_impulse_, 
                   time_stage_before_lift_;
  std::vector<bool> is_time_stage_before_impulse_, is_time_stage_before_lift_,
                    sto_impulse_, sto_lift_, sto_event_;
  std::vector<GridInfo> grid_, grid_impulse_, grid_lift_;
  std::vector<DiscreteEventType> event_types_;
  DiscretizationMethod discretization_method_;

  void countDiscreteEvents(
      const std::shared_ptr<ContactSequence>& contact_sequence, const double t,
      const bool refine_grids);

  void countTimeStepsGridBased(const double t);

  void countTimeStepsPhaseBased(const double t);

  void countTimeStages();

  void countContactPhase();

  void countSTOEvents();

  void setInitialTime(const double t);
};

} // namespace robotoc

#include "robotoc/hybrid/time_discretization.hxx"

#endif // ROBOTOC_TIME_DISCRETIZATION_HPP_ 