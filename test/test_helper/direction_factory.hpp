#ifndef IDOCP_TEST_HELPER_DIRECTION_FACTORY_HPP_
#define IDOCP_TEST_HELPER_DIRECTION_FACTORY_HPP_

#include "idocp/robot/robot.hpp"
#include "idocp/hybrid/contact_sequence.hpp"
#include "idocp/hybrid/hybrid_container.hpp"


namespace idocp {
namespace testhelper {

Direction CreateDirection(const Robot& robot, const int N, 
                          const int max_num_impulse=0);

Direction CreateDirection(const Robot& robot, const ContactSequence& contact_sequence, 
                          const double T, const int N, const int max_num_impulse, 
                          const double t, const bool is_parnmpc=false);


} // namespace testhelper
} // namespace idocp

#endif // IDOCP_TEST_HELPER_DIRECTION_FACTORY_HPP_ 