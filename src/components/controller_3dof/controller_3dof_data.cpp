//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.432
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Mar  2 17:08:49 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof.h"

// Block parameters (default storage)
Controller::P Controller::rtP{
  // Variable: E
  //  Referenced by:
  //    '<S1>/MATLAB Function'
  //    '<S2>/Mixer'
  //    '<S7>/MATLAB Function'

  { 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0, 0.0, -0.2, 0.0351, 1.0,
    0.2, 0.0, -0.0351 },

  // Variable: I
  //  Referenced by: '<S2>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S8>/Gain'
  //    '<S9>/Gain'

  { 1.3802216903208069, -1.1689319505302168E-15, 1.0647104335002291E-16,
    1.1405702684131154E-16, 1.3802216903208084, -4.3274502277546515E-15,
    -2.3768025384816916E-16, 1.1361613433531991E-15, 1.0000000000000009,
    0.28293371809008039, -2.8682421990747374E-16, 4.3708845130654013E-17,
    -3.3227702790609789E-16, 0.287656757999691, -6.5465690730310854E-16,
    -6.4235040674506349E-17, 1.7983518807488254E-16, 0.3766981865241954 },

  // Variable: Ki
  //  Referenced by:
  //    '<S8>/Gain2'
  //    '<S9>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: V
  //  Referenced by:
  //    '<S8>/Gain1'
  //    '<S9>/Gain1'

  { 1.0523714903208068, -1.1689319505302172E-15, 1.0647104335002295E-16,
    1.1405702684131151E-16, 1.0523714903208086, -4.3274502277546523E-15,
    -2.3768025384816916E-16, 1.1361613433531993E-15, 1.0000000000000009 },

  // Variable: a
  //  Referenced by:
  //    '<S1>/MATLAB Function'
  //    '<S2>/MATLAB Function1'
  //    '<S7>/MATLAB Function'

  13.0,

  // Variable: b
  //  Referenced by:
  //    '<S1>/MATLAB Function'
  //    '<S2>/MATLAB Function1'
  //    '<S7>/MATLAB Function'

  0.085908,

  // Variable: d
  //  Referenced by: '<S2>/MATLAB Function2'

  0.03,

  // Variable: g
  //  Referenced by: '<S2>/MATLAB Function2'

  9.81,

  // Variable: kd_pitch
  //  Referenced by: '<S98>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by: '<S46>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by: '<S150>/Derivative Gain'

  0.51,

  // Variable: ke
  //  Referenced by:
  //    '<S56>/Filter Coefficient'
  //    '<S108>/Filter Coefficient'
  //    '<S160>/Filter Coefficient'

  100.0,

  // Variable: ki_pitch
  //  Referenced by: '<S102>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by: '<S50>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by: '<S154>/Integral Gain'

  2.5,

  // Variable: m
  //  Referenced by: '<S2>/MATLAB Function2'

  1.114,

  // Variable: p
  //  Referenced by: '<S2>/MATLAB Function2'

  0.08,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S48>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S100>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S152>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S53>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S105>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S157>/Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S3>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S3>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S3>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S3>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S3>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S3>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S3>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S3>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S4>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S4>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S4>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S4>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S4>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S4>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S4>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S4>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S6>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S6>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S6>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S6>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S6>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S6>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S6>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S6>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Computed Parameter: TransferFcn_A
  //  Referenced by: '<S3>/Transfer Fcn'

  -100.0,

  // Computed Parameter: TransferFcn_C
  //  Referenced by: '<S3>/Transfer Fcn'

  100.0,

  // Computed Parameter: TransferFcn_A_c
  //  Referenced by: '<S4>/Transfer Fcn'

  -100.0,

  // Computed Parameter: TransferFcn_C_a
  //  Referenced by: '<S4>/Transfer Fcn'

  100.0,

  // Computed Parameter: TransferFcn_A_o
  //  Referenced by: '<S6>/Transfer Fcn'

  -100.0,

  // Computed Parameter: TransferFcn_C_n
  //  Referenced by: '<S6>/Transfer Fcn'

  100.0,

  // Expression: 0
  //  Referenced by: '<S8>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S1>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S1>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<Root>/Integrator'

  0.0,

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S2>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S9>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S7>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S7>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S3>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S4>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S6>/Integrator1'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
