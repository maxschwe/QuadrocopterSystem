//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.331
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Feb 24 17:07:45 2026
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
  //    '<S12>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  { 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0, 0.0, -0.2, 0.0351, 1.0,
    0.2, 0.0, -0.0351 },

  // Variable: I
  //  Referenced by: '<S1>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: a
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S12>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  13.0,

  // Variable: b
  //  Referenced by:
  //    '<S1>/MATLAB Function1'
  //    '<S12>/MATLAB Function'
  //    '<S175>/MATLAB Function'

  0.085908,

  // Variable: d
  //  Referenced by: '<S1>/MATLAB Function2'

  0.03,

  // Variable: g
  //  Referenced by: '<S1>/MATLAB Function2'

  9.81,

  // Variable: m
  //  Referenced by: '<S1>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S1>/MATLAB Function2'

  0.1,

  // Mask Parameter: PIDController1_D
  //  Referenced by: '<S92>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_D
  //  Referenced by: '<S144>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController_D
  //  Referenced by: '<S40>/Derivative Gain'

  1.3,

  // Mask Parameter: PIDController1_D_k
  //  Referenced by: '<S255>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_D_m
  //  Referenced by: '<S307>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController_D_c
  //  Referenced by: '<S203>/Derivative Gain'

  1.3,

  // Mask Parameter: PIDController2_I
  //  Referenced by: '<S148>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController1_I
  //  Referenced by: '<S96>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S44>/Integral Gain'

  1.2,

  // Mask Parameter: PIDController2_I_i
  //  Referenced by: '<S311>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController1_I_m
  //  Referenced by: '<S259>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_I_a
  //  Referenced by: '<S207>/Integral Gain'

  1.2,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S42>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S94>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S146>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_e
  //  Referenced by: '<S205>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S257>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_e
  //  Referenced by: '<S309>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_l
  //  Referenced by: '<S47>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_d
  //  Referenced by: '<S99>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S151>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S210>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S262>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_o
  //  Referenced by: '<S314>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S50>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S102>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S154>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_N_o
  //  Referenced by: '<S213>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N_l
  //  Referenced by: '<S265>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N_b
  //  Referenced by: '<S317>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S52>/Proportional Gain'

  3.0,

  // Mask Parameter: PIDController1_P
  //  Referenced by: '<S104>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController2_P
  //  Referenced by: '<S156>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController_P_f
  //  Referenced by: '<S215>/Proportional Gain'

  3.0,

  // Mask Parameter: PIDController1_P_k
  //  Referenced by: '<S267>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController2_P_n
  //  Referenced by: '<S319>/Proportional Gain'

  0.0,

  // Expression: 0
  //  Referenced by: '<S1>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S12>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S12>/Saturation'

  0.15,

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S3>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S3>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S3>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S3>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S3>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S3>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S3>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 10000 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S3>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S4>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S4>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S4>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S4>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S4>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S4>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0; 0 10e-3]
  //  Referenced by: '<S4>/Cov Prozessrauschen'

  { 1.0, 0.0, 0.0, 0.01 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S4>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S6>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S6>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S6>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S6>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S6>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S6>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0; 0 10e-3]
  //  Referenced by: '<S6>/Cov Prozessrauschen'

  { 1.0, 0.0, 0.0, 0.01 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S6>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0.90
  //  Referenced by: '<S175>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S175>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<Root>/Integrator'

  0.0,

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
