//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container_data.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.480
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Mar  7 15:55:02 2026
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
  //    '<S176>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S4>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: N
  //  Referenced by:
  //    '<S56>/Filter Coefficient'
  //    '<S108>/Filter Coefficient'
  //    '<S160>/Filter Coefficient'
  //    '<S224>/Filter Coefficient'
  //    '<S276>/Filter Coefficient'
  //    '<S328>/Filter Coefficient'

  100.0,

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S176>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S176>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by: '<S4>/MATLAB Function2'

  9.81,

  // Variable: h
  //  Referenced by: '<S4>/MATLAB Function2'

  0.03,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S98>/Derivative Gain'
  //    '<S266>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S46>/Derivative Gain'
  //    '<S214>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S150>/Derivative Gain'
  //    '<S318>/Derivative Gain'

  0.51,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S102>/Integral Gain'
  //    '<S270>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S50>/Integral Gain'
  //    '<S218>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S154>/Integral Gain'
  //    '<S322>/Integral Gain'

  2.5,

  // Variable: kp_pitch
  //  Referenced by:
  //    '<S110>/Proportional Gain'
  //    '<S278>/Proportional Gain'

  1.42,

  // Variable: kp_roll
  //  Referenced by:
  //    '<S58>/Proportional Gain'
  //    '<S226>/Proportional Gain'

  1.4,

  // Variable: kp_yaw
  //  Referenced by:
  //    '<S162>/Proportional Gain'
  //    '<S330>/Proportional Gain'

  2.8,

  // Variable: m
  //  Referenced by: '<S4>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S4>/MATLAB Function2'

  { 0.05, 0.05, 0.01 },

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S48>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S100>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S152>/Filter'

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
  //  Referenced by: '<S53>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_p
  //  Referenced by: '<S105>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_p
  //  Referenced by: '<S157>/Integrator'

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
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S9>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S9>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S9>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S9>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S9>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S9>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S9>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S9>/Unit Delay'

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

  // Expression: [1; 0]
  //  Referenced by: '<S12>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S12>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S12>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S12>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S12>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S12>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S12>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S12>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S8>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S8>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S2>/Integrator'

  0.0,

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
  //  Referenced by: '<S178>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S178>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S178>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S178>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S178>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S178>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S178>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S178>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S180>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S180>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S180>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S180>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S180>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S180>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S180>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S180>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S176>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S176>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S3>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S9>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S10>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S12>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S177>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S178>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S180>/Integrator1'

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
