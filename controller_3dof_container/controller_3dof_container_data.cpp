//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container_data.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.466
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Mar  3 13:28:30 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof_container.h"

// Block parameters (default storage)
Controller::P Controller::rtP{
  // Variable: E
  //  Referenced by:
  //    '<S1>/Mixer'
  //    '<S6>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  { 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0, 0.0, -0.2, 0.0351, 1.0,
    0.2, 0.0, -0.0351 },

  // Variable: I
  //  Referenced by: '<S1>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S11>/Gain'
  //    '<S180>/Gain'

  { 1.3802216903208069, 1.2738685565361183E-15, -8.4287551560373775E-16,
    -2.18957965610623E-16, 1.3802216903208102, -9.0557716396114723E-15,
    1.2950759622552228E-16, 2.6690227921397107E-15, 1.0000000000000091,
    0.28370316363827636, 3.9244547272064767E-16, -1.7274122730232925E-16,
    -4.5729423207176935E-18, 0.28845592509418644, -2.3468415306867628E-15,
    -7.21890262967409E-17, -3.9837301034868702E-16, 0.37871459014280356 },

  // Variable: Ki
  //  Referenced by:
  //    '<S11>/Gain2'
  //    '<S180>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: V
  //  Referenced by:
  //    '<S11>/Gain1'
  //    '<S180>/Gain1'

  { 1.0523714903208068, 1.2738685565361189E-15, -8.4287551560373805E-16,
    -2.1895796561062302E-16, 1.0523714903208103, -9.0557716396114739E-15,
    1.2950759622552228E-16, 2.6690227921397119E-15, 1.0000000000000091 },

  // Variable: a
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S6>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  13.0,

  // Variable: b
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S6>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  0.085908,

  // Variable: d
  //  Referenced by: '<S1>/MATLAB Function2'

  0.03,

  // Variable: g
  //  Referenced by: '<S1>/MATLAB Function2'

  9.81,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S97>/Derivative Gain'
  //    '<S266>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S45>/Derivative Gain'
  //    '<S214>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S149>/Derivative Gain'
  //    '<S318>/Derivative Gain'

  0.51,

  // Variable: ke
  //  Referenced by:
  //    '<S55>/Filter Coefficient'
  //    '<S107>/Filter Coefficient'
  //    '<S159>/Filter Coefficient'
  //    '<S224>/Filter Coefficient'
  //    '<S276>/Filter Coefficient'
  //    '<S328>/Filter Coefficient'

  100.0,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S101>/Integral Gain'
  //    '<S270>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S49>/Integral Gain'
  //    '<S218>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S153>/Integral Gain'
  //    '<S322>/Integral Gain'

  2.5,

  // Variable: kp_pitch
  //  Referenced by:
  //    '<S109>/Proportional Gain'
  //    '<S278>/Proportional Gain'

  1.42,

  // Variable: kp_roll
  //  Referenced by:
  //    '<S57>/Proportional Gain'
  //    '<S226>/Proportional Gain'

  1.4,

  // Variable: kp_yaw
  //  Referenced by:
  //    '<S161>/Proportional Gain'
  //    '<S330>/Proportional Gain'

  2.8,

  // Variable: m
  //  Referenced by: '<S1>/MATLAB Function2'

  1.114,

  // Variable: p
  //  Referenced by: '<S1>/MATLAB Function2'

  0.05,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S47>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S99>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S151>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S216>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S268>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_j
  //  Referenced by: '<S320>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_e
  //  Referenced by: '<S52>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_p
  //  Referenced by: '<S104>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_p
  //  Referenced by: '<S156>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S221>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S273>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_m
  //  Referenced by: '<S325>/Integrator'

  0.0,

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S1>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S7>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S7>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S7>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S7>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S7>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S7>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S7>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S7>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S8>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S8>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S8>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S8>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S8>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S8>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S8>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S8>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S10>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S10>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S10>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S10>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S10>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S10>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S10>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S10>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S6>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S6>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S2>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S11>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S180>/Integrator'

  0.0,

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S176>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S176>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S176>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S176>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S176>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S176>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S176>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S176>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S177>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S177>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S177>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S177>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S177>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S177>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S177>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S177>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S179>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S179>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S179>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S179>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S179>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S179>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S179>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S179>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S175>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S175>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S3>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S7>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A
  //  Referenced by: '<S7>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C
  //  Referenced by: '<S7>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S8>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_h
  //  Referenced by: '<S8>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_f
  //  Referenced by: '<S8>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S10>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_c
  //  Referenced by: '<S10>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_n
  //  Referenced by: '<S10>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S176>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_d
  //  Referenced by: '<S176>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_g
  //  Referenced by: '<S176>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S177>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_a
  //  Referenced by: '<S177>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_h
  //  Referenced by: '<S177>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S179>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_hf
  //  Referenced by: '<S179>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_j
  //  Referenced by: '<S179>/Transfer Fcn1'

  100.0
};

//
// File trailer for generated code.
//
// [EOF]
//
