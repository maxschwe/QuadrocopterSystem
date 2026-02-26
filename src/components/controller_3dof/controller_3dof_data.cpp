//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.352
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Feb 26 18:20:48 2026
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

  { 4.8162325473254732, -4.5815932932854847E-17, -9.5385573792593762E-16,
    -1.3406080991824339E-15, 4.8168918826532545, -3.0030181977003071E-15,
    2.2159675382151523E-16, -4.6668145962235449E-16, 2.3152781706241252,
    0.50587280591417183, 7.3877073429728637E-17, -4.5617498558133229E-17,
    1.1565020081584054E-16, 0.51519313823967927, -2.1317333829409328E-16,
    5.2133517671979619E-17, 6.026253801518084E-17, 0.56322111470092207,
    0.31622776601683866, -2.271791668812762E-16, 7.6097447264009891E-17,
    -6.270619816169662E-17, 0.31622776601683916, -1.0783645040121002E-15,
    -1.5329456682202211E-16, -9.9087325655952365E-16, 0.31622776601683722 },

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
  //  Referenced by: '<S97>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by: '<S45>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by: '<S149>/Derivative Gain'

  0.51,

  // Variable: ke
  //  Referenced by:
  //    '<S55>/Filter Coefficient'
  //    '<S107>/Filter Coefficient'
  //    '<S159>/Filter Coefficient'

  100.0,

  // Variable: ki_pitch
  //  Referenced by: '<S101>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by: '<S49>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by: '<S153>/Integral Gain'

  2.5,

  // Variable: m
  //  Referenced by: '<S2>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S2>/MATLAB Function2'

  3.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S47>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S99>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S151>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S52>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S104>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S156>/Integrator'

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

  // Expression: 0
  //  Referenced by: '<S2>/Integrator'

  0.0,

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
