//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container_data.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.500
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Mar  7 19:55:57 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_6dof_container.h"

// Block parameters (default storage)
Controller6dof::P Controller6dof::rtP{
  // Variable: B_eff
  //  Referenced by:
  //    '<S5>/B_Eff'
  //    '<S171>/MATLAB Function'
  //    '<S501>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S6>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S176>/Gain'
  //    '<S506>/Gain'

  { 1.6142259582794287, 1.2711870143100486E-15, 5.36115150372202E-16,
    9.1084845953510463E-16, 1.6142259582794254, -1.1979866809554318E-16,
    -1.2195293884720441E-16, -3.9067046768301071E-16, 1.0000000000000002,
    0.30544076258289282, 3.2400802708150655E-16, -6.363238227525555E-17,
    -4.6860780500689764E-16, 0.3106807225493351, 5.71499884074483E-17,
    2.9516739831244427E-17, 1.8317276333373346E-17, 0.38209946349085644 },

  // Variable: Ki
  //  Referenced by:
  //    '<S176>/Gain2'
  //    '<S506>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: N
  //  Referenced by:
  //    '<S220>/Filter Coefficient'
  //    '<S272>/Filter Coefficient'
  //    '<S324>/Filter Coefficient'
  //    '<S550>/Filter Coefficient'
  //    '<S602>/Filter Coefficient'
  //    '<S654>/Filter Coefficient'

  100.0,

  // Variable: N_pos
  //  Referenced by:
  //    '<S52>/Filter Coefficient'
  //    '<S104>/Filter Coefficient'
  //    '<S156>/Filter Coefficient'
  //    '<S382>/Filter Coefficient'
  //    '<S434>/Filter Coefficient'
  //    '<S486>/Filter Coefficient'

  100.0,

  // Variable: V
  //  Referenced by:
  //    '<S176>/Gain1'
  //    '<S506>/Gain1'

  { 1.1168589582794288, 1.2711870143100484E-15, 5.3611515037220214E-16,
    9.1084845953510463E-16, 1.1168589582794253, -1.1979866809554321E-16,
    -1.2195293884720443E-16, -3.9067046768301076E-16, 1.0000000000000002 },

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S171>/MATLAB Function'
  //    '<S501>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S171>/MATLAB Function'
  //    '<S501>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by:
  //    '<S2>/Constant'
  //    '<S3>/Constant'
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'

  9.81,

  // Variable: h
  //  Referenced by: '<S6>/MATLAB Function2'

  0.05,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S262>/Derivative Gain'
  //    '<S592>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S210>/Derivative Gain'
  //    '<S540>/Derivative Gain'

  0.33,

  // Variable: kd_x
  //  Referenced by:
  //    '<S42>/Derivative Gain'
  //    '<S372>/Derivative Gain'

  0.5,

  // Variable: kd_y
  //  Referenced by:
  //    '<S94>/Derivative Gain'
  //    '<S424>/Derivative Gain'

  0.5,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S314>/Derivative Gain'
  //    '<S644>/Derivative Gain'

  0.5,

  // Variable: kd_z
  //  Referenced by:
  //    '<S146>/Derivative Gain'
  //    '<S476>/Derivative Gain'

  2.0,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S266>/Integral Gain'
  //    '<S596>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S214>/Integral Gain'
  //    '<S544>/Integral Gain'

  1.18,

  // Variable: ki_x
  //  Referenced by:
  //    '<S46>/Integral Gain'
  //    '<S376>/Integral Gain'

  0.2,

  // Variable: ki_y
  //  Referenced by:
  //    '<S98>/Integral Gain'
  //    '<S428>/Integral Gain'

  0.2,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S318>/Integral Gain'
  //    '<S648>/Integral Gain'

  0.7,

  // Variable: ki_z
  //  Referenced by:
  //    '<S150>/Integral Gain'
  //    '<S480>/Integral Gain'

  0.1,

  // Variable: kp_x
  //  Referenced by:
  //    '<S54>/Proportional Gain'
  //    '<S384>/Proportional Gain'

  0.5,

  // Variable: kp_y
  //  Referenced by:
  //    '<S106>/Proportional Gain'
  //    '<S436>/Proportional Gain'

  0.5,

  // Variable: kp_z
  //  Referenced by:
  //    '<S158>/Proportional Gain'
  //    '<S488>/Proportional Gain'

  1.5,

  // Variable: m
  //  Referenced by:
  //    '<S2>/Constant'
  //    '<S3>/Constant'
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S6>/MATLAB Function2'

  { 0.0, 0.0, 0.0 },

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S148>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S96>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S44>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_m
  //  Referenced by: '<S478>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_p
  //  Referenced by: '<S426>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_j
  //  Referenced by: '<S374>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_i
  //  Referenced by: '<S212>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_n
  //  Referenced by: '<S264>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_h
  //  Referenced by: '<S316>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S542>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S594>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_c
  //  Referenced by: '<S646>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_cd
  //  Referenced by: '<S153>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S101>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S49>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S483>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_e
  //  Referenced by: '<S431>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_n
  //  Referenced by: '<S379>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_ay
  //  Referenced by: '<S217>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_nz
  //  Referenced by: '<S269>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S321>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_b
  //  Referenced by: '<S547>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_b
  //  Referenced by: '<S599>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S651>/Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S172>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S172>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S172>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S172>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S172>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S172>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S172>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S172>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S173>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S173>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S173>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S173>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S173>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S173>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S173>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S173>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S175>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S175>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S175>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S175>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S175>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S175>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S175>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S175>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S176>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S171>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S171>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S14>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S2>/Constant1'

  { 0.0, 0.0 },

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S6>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S502>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S502>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S502>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S502>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S502>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S502>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S502>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S502>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S503>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S503>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S503>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S503>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S503>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S503>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S503>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S503>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S505>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S505>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S505>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S505>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S505>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S505>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S505>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S505>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S506>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S501>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S501>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S344>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S3>/Constant1'

  { 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S172>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S173>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S175>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S502>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S503>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S505>/Integrator1'

  0.0,

  // Expression: false
  //  Referenced by: '<S1>/Constant'

  false
};

//
// File trailer for generated code.
//
// [EOF]
//
