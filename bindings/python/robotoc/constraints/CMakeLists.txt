pybind11_add_robotoc_module(constraint_component_base)
pybind11_add_robotoc_module(impulse_constraint_component_base)
pybind11_add_robotoc_module(constraints)
pybind11_add_robotoc_module(joint_position_lower_limit)
pybind11_add_robotoc_module(joint_position_upper_limit)
pybind11_add_robotoc_module(joint_velocity_lower_limit)
pybind11_add_robotoc_module(joint_velocity_upper_limit)
pybind11_add_robotoc_module(joint_acceleration_lower_limit)
pybind11_add_robotoc_module(joint_acceleration_upper_limit)
pybind11_add_robotoc_module(joint_torques_lower_limit)
pybind11_add_robotoc_module(joint_torques_upper_limit)
pybind11_add_robotoc_module(friction_cone)
pybind11_add_robotoc_module(impulse_friction_cone)
pybind11_add_robotoc_module(wrench_friction_cone)
pybind11_add_robotoc_module(impulse_wrench_friction_cone)

install_robotoc_pybind_module(constraints)