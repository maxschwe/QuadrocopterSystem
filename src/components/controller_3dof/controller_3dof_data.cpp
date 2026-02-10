//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.283
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Feb 10 14:11:41 2026
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
  //    '<S1>/Mixer'
  //    '<S9>/MATLAB Function'
  //    '<S170>/MATLAB Function'

  { 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0, 0.0, -0.2, 0.0351, 1.0,
    0.2, 0.0, -0.0351 },

  // Variable: I
  //  Referenced by: '<S1>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: a
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S9>/MATLAB Function'
  //    '<S170>/MATLAB Function'

  13.0,

  // Variable: b
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S9>/MATLAB Function'
  //    '<S170>/MATLAB Function'

  0.085908,

  // Variable: d
  //  Referenced by: '<S1>/MATLAB Function2'

  0.05,

  // Variable: g
  //  Referenced by: '<S1>/MATLAB Function2'

  9.81,

  // Variable: guenther
  //  Referenced by: '<S1>/MATLAB Function1'

  1.0,

  // Variable: m
  //  Referenced by: '<S1>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S1>/MATLAB Function2'

  0.1,

  // Mask Parameter: PIDController_D
  //  Referenced by: '<S37>/Derivative Gain'

  0.35,

  // Mask Parameter: PIDController1_D
  //  Referenced by: '<S89>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_D
  //  Referenced by: '<S141>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController_D_c
  //  Referenced by: '<S198>/Derivative Gain'

  0.35,

  // Mask Parameter: PIDController1_D_k
  //  Referenced by: '<S250>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_D_m
  //  Referenced by: '<S302>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_I
  //  Referenced by: '<S145>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController1_I
  //  Referenced by: '<S93>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S41>/Integral Gain'

  0.8,

  // Mask Parameter: PIDController2_I_i
  //  Referenced by: '<S306>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController1_I_m
  //  Referenced by: '<S254>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_I_a
  //  Referenced by: '<S202>/Integral Gain'

  0.8,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S39>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S91>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S143>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_e
  //  Referenced by: '<S200>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S252>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_e
  //  Referenced by: '<S304>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_g
  //  Referenced by: '<S44>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S96>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_p
  //  Referenced by: '<S148>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S205>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S257>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S309>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S47>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S99>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S151>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_N_o
  //  Referenced by: '<S208>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N_l
  //  Referenced by: '<S260>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N_b
  //  Referenced by: '<S312>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S49>/Proportional Gain'

  0.8,

  // Mask Parameter: PIDController1_P
  //  Referenced by: '<S101>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController2_P
  //  Referenced by: '<S153>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController_P_f
  //  Referenced by: '<S210>/Proportional Gain'

  0.8,

  // Mask Parameter: PIDController1_P_k
  //  Referenced by: '<S262>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController2_P_n
  //  Referenced by: '<S314>/Proportional Gain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S1>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S9>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S9>/Saturation'

  0.15,

  // Expression: 0.90
  //  Referenced by: '<S170>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S170>/Saturation'

  0.15
};

//
// File trailer for generated code.
//
// [EOF]
//
