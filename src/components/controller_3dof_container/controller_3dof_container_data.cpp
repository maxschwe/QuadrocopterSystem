//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container_data.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.490
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Mar 13 18:06:58 2026
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
Controller3dof::P Controller3dof::rtP{
  // Variable: B_eff
  //  Referenced by:
  //    '<S5>/B_Eff'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S4>/MATLAB Function2'

  { 0.0304, 0.0, 0.0, 0.0, 0.0315, 0.0, 0.0, 0.0, 0.0476 },

  // Variable: N
  //  Referenced by:
  //    '<S52>/Filter Coefficient'
  //    '<S104>/Filter Coefficient'
  //    '<S156>/Filter Coefficient'
  //    '<S221>/Filter Coefficient'
  //    '<S273>/Filter Coefficient'
  //    '<S325>/Filter Coefficient'

  100.0,

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by: '<S4>/MATLAB Function2'

  9.81,

  // Variable: h
  //  Referenced by: '<S4>/MATLAB Function2'

  0.044,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S94>/Derivative Gain'
  //    '<S263>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S42>/Derivative Gain'
  //    '<S211>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S146>/Derivative Gain'
  //    '<S315>/Derivative Gain'

  0.5,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S98>/Integral Gain'
  //    '<S267>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S46>/Integral Gain'
  //    '<S215>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S150>/Integral Gain'
  //    '<S319>/Integral Gain'

  0.7,

  // Variable: kp_pitch
  //  Referenced by:
  //    '<S106>/Proportional Gain'
  //    '<S275>/Proportional Gain'

  1.42,

  // Variable: kp_roll
  //  Referenced by:
  //    '<S54>/Proportional Gain'
  //    '<S223>/Proportional Gain'

  1.4,

  // Variable: kp_yaw
  //  Referenced by:
  //    '<S158>/Proportional Gain'
  //    '<S327>/Proportional Gain'

  1.2,

  // Variable: m
  //  Referenced by: '<S4>/MATLAB Function2'

  1.21,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S44>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S96>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S148>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S213>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S265>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_j
  //  Referenced by: '<S317>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_e
  //  Referenced by: '<S49>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_p
  //  Referenced by: '<S101>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_p
  //  Referenced by: '<S153>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S218>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S270>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_m
  //  Referenced by: '<S322>/Integrator'

  0.0,

  // Expression: zeros(6, 1)
  //  Referenced by: '<S3>/Constant'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: zeros(6, 1)
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0.90
  //  Referenced by: '<S8>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S8>/Saturation'

  0.15,

  // Expression: 0.90
  //  Referenced by: '<S177>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S177>/Saturation'

  0.15,

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S171>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S171>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S171>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S171>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S171>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S171>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S171>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S171>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S172>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S172>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S172>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S172>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S172>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S172>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S172>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S172>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S173>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S173>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S173>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S173>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S173>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S173>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S173>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S173>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S340>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S340>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S340>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S340>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S340>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S340>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S340>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S340>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S341>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S341>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S341>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S341>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S341>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S341>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S341>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S341>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S342>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S342>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S342>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S342>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S342>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S342>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S342>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S342>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S10>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S179>/Integrator'

  0.0,

  // Computed Parameter: TransferFcn_A
  //  Referenced by: '<S5>/Transfer Fcn'

  -50.0,

  // Computed Parameter: TransferFcn_C
  //  Referenced by: '<S5>/Transfer Fcn'

  50.0,

  // Computed Parameter: TransferFcn1_A
  //  Referenced by: '<S5>/Transfer Fcn1'

  -50.0,

  // Computed Parameter: TransferFcn1_C
  //  Referenced by: '<S5>/Transfer Fcn1'

  50.0,

  // Computed Parameter: TransferFcn2_A
  //  Referenced by: '<S5>/Transfer Fcn2'

  -50.0,

  // Computed Parameter: TransferFcn2_C
  //  Referenced by: '<S5>/Transfer Fcn2'

  50.0,

  // Computed Parameter: TransferFcn3_A
  //  Referenced by: '<S5>/Transfer Fcn3'

  -50.0,

  // Computed Parameter: TransferFcn3_C
  //  Referenced by: '<S5>/Transfer Fcn3'

  50.0,

  // Expression: 0
  //  Referenced by: '<S171>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S172>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S173>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S340>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S341>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S342>/Integrator1'

  0.0,

  // Expression: true
  //  Referenced by: '<S1>/Constant'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
