//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container_data.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.496
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Mar  3 20:48:26 2026
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
Controller::P Controller::rtP{
  // Variable: E
  //  Referenced by:
  //    '<S1>/Mixer'
  //    '<S167>/MATLAB Function'
  //    '<S497>/MATLAB Function'

  { 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0, 0.0, -0.2, 0.0351, 1.0,
    0.2, 0.0, -0.0351 },

  // Variable: I
  //  Referenced by: '<S1>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S172>/Gain'
  //    '<S502>/Gain'

  { 1.3802216903208069, 1.2738685565361183E-15, -8.4287551560373775E-16,
    -2.18957965610623E-16, 1.3802216903208102, -9.0557716396114723E-15,
    1.2950759622552228E-16, 2.6690227921397107E-15, 1.0000000000000091,
    0.28370316363827636, 3.9244547272064767E-16, -1.7274122730232925E-16,
    -4.5729423207176935E-18, 0.28845592509418644, -2.3468415306867628E-15,
    -7.21890262967409E-17, -3.9837301034868702E-16, 0.37871459014280356 },

  // Variable: Ki
  //  Referenced by:
  //    '<S172>/Gain2'
  //    '<S502>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: V
  //  Referenced by:
  //    '<S172>/Gain1'
  //    '<S502>/Gain1'

  { 1.0523714903208068, 1.2738685565361189E-15, -8.4287551560373805E-16,
    -2.1895796561062302E-16, 1.0523714903208103, -9.0557716396114739E-15,
    1.2950759622552228E-16, 2.6690227921397119E-15, 1.0000000000000091 },

  // Variable: a
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S167>/MATLAB Function'
  //    '<S497>/MATLAB Function'

  13.0,

  // Variable: b
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S167>/MATLAB Function'
  //    '<S497>/MATLAB Function'

  0.085908,

  // Variable: g
  //  Referenced by:
  //    '<S1>/MATLAB Function2'
  //    '<S2>/Constant'
  //    '<S3>/Constant'

  9.81,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S258>/Derivative Gain'
  //    '<S588>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S206>/Derivative Gain'
  //    '<S536>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S310>/Derivative Gain'
  //    '<S640>/Derivative Gain'

  0.51,

  // Variable: ke
  //  Referenced by:
  //    '<S216>/Filter Coefficient'
  //    '<S268>/Filter Coefficient'
  //    '<S320>/Filter Coefficient'
  //    '<S546>/Filter Coefficient'
  //    '<S598>/Filter Coefficient'
  //    '<S650>/Filter Coefficient'

  100.0,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S262>/Integral Gain'
  //    '<S592>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S210>/Integral Gain'
  //    '<S540>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S314>/Integral Gain'
  //    '<S644>/Integral Gain'

  2.5,

  // Variable: kp_pitch
  //  Referenced by:
  //    '<S270>/Proportional Gain'
  //    '<S600>/Proportional Gain'

  1.42,

  // Variable: kp_roll
  //  Referenced by:
  //    '<S218>/Proportional Gain'
  //    '<S548>/Proportional Gain'

  1.4,

  // Variable: kp_yaw
  //  Referenced by:
  //    '<S322>/Proportional Gain'
  //    '<S652>/Proportional Gain'

  2.8,

  // Variable: m
  //  Referenced by:
  //    '<S1>/MATLAB Function2'
  //    '<S2>/Constant'
  //    '<S3>/Constant'

  1.114,

  // Variable: p
  //  Referenced by: '<S1>/MATLAB Function2'

  0.05,

  // Mask Parameter: PIDController2_D
  //  Referenced by: '<S472>/Derivative Gain'

  2.0,

  // Mask Parameter: PIDController1_D
  //  Referenced by: '<S420>/Derivative Gain'

  0.5,

  // Mask Parameter: PIDController_D
  //  Referenced by: '<S368>/Derivative Gain'

  0.5,

  // Mask Parameter: PIDController2_D_m
  //  Referenced by: '<S142>/Derivative Gain'

  2.0,

  // Mask Parameter: PIDController1_D_j
  //  Referenced by: '<S90>/Derivative Gain'

  0.5,

  // Mask Parameter: PIDController_D_i
  //  Referenced by: '<S38>/Derivative Gain'

  0.5,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S372>/Integral Gain'

  0.2,

  // Mask Parameter: PIDController1_I
  //  Referenced by: '<S424>/Integral Gain'

  0.2,

  // Mask Parameter: PIDController2_I
  //  Referenced by: '<S476>/Integral Gain'

  0.1,

  // Mask Parameter: PIDController_I_b
  //  Referenced by: '<S42>/Integral Gain'

  0.2,

  // Mask Parameter: PIDController1_I_g
  //  Referenced by: '<S94>/Integral Gain'

  0.2,

  // Mask Parameter: PIDController2_I_a
  //  Referenced by: '<S146>/Integral Gain'

  0.1,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S474>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S422>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S370>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S538>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S590>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_c
  //  Referenced by: '<S642>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S144>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S92>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_f
  //  Referenced by: '<S40>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_i
  //  Referenced by: '<S208>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_n
  //  Referenced by: '<S260>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_h
  //  Referenced by: '<S312>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S479>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_e
  //  Referenced by: '<S427>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_n
  //  Referenced by: '<S375>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_b
  //  Referenced by: '<S543>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_b
  //  Referenced by: '<S595>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_k5
  //  Referenced by: '<S647>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_cd
  //  Referenced by: '<S149>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S97>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S45>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_ay
  //  Referenced by: '<S213>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_nz
  //  Referenced by: '<S265>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S317>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S482>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S430>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S378>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N_j
  //  Referenced by: '<S152>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController1_N_o
  //  Referenced by: '<S100>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_N_o
  //  Referenced by: '<S48>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_P
  //  Referenced by: '<S484>/Proportional Gain'

  1.5,

  // Mask Parameter: PIDController1_P
  //  Referenced by: '<S432>/Proportional Gain'

  0.5,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S380>/Proportional Gain'

  0.5,

  // Mask Parameter: PIDController2_P_j
  //  Referenced by: '<S154>/Proportional Gain'

  1.5,

  // Mask Parameter: PIDController1_P_n
  //  Referenced by: '<S102>/Proportional Gain'

  0.5,

  // Mask Parameter: PIDController_P_d
  //  Referenced by: '<S50>/Proportional Gain'

  0.5,

  // Expression: [0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S1>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S498>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S498>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S498>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S498>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S498>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S498>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S498>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S498>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S499>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S499>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S499>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S499>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S499>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S499>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S499>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S499>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S501>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S501>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S501>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S501>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S501>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S501>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S501>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S501>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S497>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S497>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S340>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S3>/Constant1'

  { 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S172>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S502>/Integrator'

  0.0,

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S168>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S168>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S168>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S168>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S168>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S168>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S168>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S168>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S169>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S169>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S169>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S169>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S169>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S169>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S169>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S169>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S171>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S171>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S171>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S171>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S171>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S171>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S171>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S171>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S167>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S167>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S10>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S2>/Constant1'

  { 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S168>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A
  //  Referenced by: '<S168>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C
  //  Referenced by: '<S168>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S169>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_m
  //  Referenced by: '<S169>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_j
  //  Referenced by: '<S169>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S171>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_n
  //  Referenced by: '<S171>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_m
  //  Referenced by: '<S171>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S498>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_e
  //  Referenced by: '<S498>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_l
  //  Referenced by: '<S498>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S499>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_ee
  //  Referenced by: '<S499>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_c
  //  Referenced by: '<S499>/Transfer Fcn1'

  100.0,

  // Expression: 0
  //  Referenced by: '<S501>/Integrator1'

  0.0,

  // Computed Parameter: TransferFcn1_A_my
  //  Referenced by: '<S501>/Transfer Fcn1'

  -100.0,

  // Computed Parameter: TransferFcn1_C_p
  //  Referenced by: '<S501>/Transfer Fcn1'

  100.0
};

//
// File trailer for generated code.
//
// [EOF]
//
