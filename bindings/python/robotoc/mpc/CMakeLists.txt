pybind11_add_robotoc_module(contact_planner_base)
pybind11_add_robotoc_module(trot_foot_step_planner)
pybind11_add_robotoc_module(crawl_foot_step_planner)
pybind11_add_robotoc_module(pace_foot_step_planner)
pybind11_add_robotoc_module(biped_walk_foot_step_planner)
pybind11_add_robotoc_module(jump_foot_step_planner)
pybind11_add_robotoc_module(flying_trot_foot_step_planner)
pybind11_add_robotoc_module(mpc_periodic_swing_foot_ref)
pybind11_add_robotoc_module(mpc_periodic_com_ref)
pybind11_add_robotoc_module(mpc_periodic_configuration_ref)
pybind11_add_robotoc_module(mpc_trot)
pybind11_add_robotoc_module(mpc_crawl)
pybind11_add_robotoc_module(mpc_pace)
pybind11_add_robotoc_module(mpc_biped_walk)
pybind11_add_robotoc_module(mpc_jump)
pybind11_add_robotoc_module(mpc_flying_trot)

install_robotoc_pybind_module(mpc)