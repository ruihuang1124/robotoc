import robotoc
import numpy as np
from a1_simulator import A1Simulator


jump_type = 'longitudinal'
# jump_type = 'lateral'
# jump_type = 'back'
# jump_type = 'rotational'

if jump_type == 'longitudinal':
    jump_length = [0.6, 0, 0]
    jump_yaw = 0
elif jump_type == 'lateral':
    jump_length = [0, 0.4, 0]
    jump_yaw = 0
elif jump_type == 'back':
    jump_length = [-0.3, 0, 0]
    jump_yaw = 0
elif jump_type == 'rotational':
    jump_length = [0.1, 0.0, 0]
    jump_yaw = np.pi / 6


path_to_urdf = '../a1_description/urdf/a1.urdf'
contact_frames = ['FL_foot', 'RL_foot', 'FR_foot', 'RR_foot'] 
contact_types = [robotoc.ContactType.PointContact for i in contact_frames]
baumgarte_time_step = 0.05
robot = robotoc.Robot(path_to_urdf, robotoc.BaseJointType.FloatingBase, 
                      contact_frames, contact_types, baumgarte_time_step)

T = 0.8
N = 18
nthreads = 4
mpc = robotoc.MPCJump(robot, T, N, nthreads)

planner = robotoc.JumpFootStepPlanner(robot)
planner.set_jump_pattern(jump_length, jump_yaw)
mpc.set_jump_pattern(planner, flying_time=0.3, min_flying_time=0.2, 
                     ground_time=0.3, min_ground_time=0.2)

q = np.array([0, 0, 0.3181, 0, 0, 0, 1, 
              0.0,  0.67, -1.3, 
              0.0,  0.67, -1.3, 
              0.0,  0.67, -1.3, 
              0.0,  0.67, -1.3])
v = np.zeros(robot.dimv())
t = 0.0
option_init = robotoc.SolverOptions()
option_init.max_iter = 50
option_init.initial_sto_reg_iter = 50
mpc.init(t, q, v, option_init, sto=True)  

option_mpc = robotoc.SolverOptions()
option_mpc.max_iter = 2 # MPC iterations
option_mpc.initial_sto_reg_iter = 0
option_mpc.max_dt_mesh = T / N
mpc.set_solver_options(option_mpc)

sim_time_step = 0.0025 # 400 Hz MPC
sim_start_time = 0.0
sim_end_time = 1.5
sim = A1Simulator(path_to_urdf, sim_time_step, sim_start_time, sim_end_time)

if jump_type == 'longitudinal':
    sim.set_camera(2.0, 35, -0, q[0:3]+np.array([-0.1, 0.5, 0.]))
elif jump_type == 'lateral':
    sim.set_camera(2.0, 55, -0, q[0:3]+np.array([-0.1, 0.5, 0.]))
elif jump_type == 'back':
    sim.set_camera(1.5, 20, -0, q[0:3]+np.array([-0.4, 0.3, 0.]))
elif jump_type == 'rotational':
    sim.set_camera(2.0, 45, -10, q[0:3]+np.array([-0.1, 0.5, 0.]))

log = False
record = False

sim.run_simulation(mpc, q, v, feedback_delay=True, verbose=False, 
                   record=record, log=log, sim_name='a1_jump_'+jump_type)

if record:
    sim.disconnect()
    robotoc.utils.adjust_video_duration(sim.sim_name+'.mp4', 
                                        desired_duration_sec=(sim_end_time-sim_start_time))

if log:
    q_log = np.genfromtxt(sim.q_log)
    v_log = np.genfromtxt(sim.v_log)
    t_log = np.genfromtxt(sim.t_log)
    sim_steps = t_log.shape[0]

    vcom_log = []
    wcom_log = []
    for i in range(sim_steps):
        R = robotoc.utils.rotation_matrix(q_log[i][3:7])
        robot.forward_kinematics(q_log[i], v_log[i])
        vcom_log.append(R.T@robot.com_velocity()) # robot.com_velocity() is expressed in the world coordinate
        wcom_log.append(v_log[i][3:6])

    plot_mpc = robotoc.utils.PlotCoMVelocity()
    plot_mpc.plot(t_log, vcom_log, wcom_log,  fig_name=sim.sim_name+'_com_vel')
