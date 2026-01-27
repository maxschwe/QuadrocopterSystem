//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.128
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jan 27 11:00:42 2026
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
  // Mask Parameter: PIDController_D
  //  Referenced by: '<S32>/Derivative Gain'

  0.5,

  // Mask Parameter: PIDController1_D
  //  Referenced by: '<S84>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_D
  //  Referenced by: '<S136>/Derivative Gain'

  0.0,

  // Mask Parameter: PIDController2_I
  //  Referenced by: '<S140>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController1_I
  //  Referenced by: '<S88>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S36>/Integral Gain'

  1.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S34>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S86>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S138>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_i
  //  Referenced by: '<S39>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_l
  //  Referenced by: '<S91>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S143>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S42>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S94>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S146>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S44>/Proportional Gain'

  0.82,

  // Mask Parameter: PIDController1_P
  //  Referenced by: '<S96>/Proportional Gain'

  0.0,

  // Mask Parameter: PIDController2_P
  //  Referenced by: '<S148>/Proportional Gain'

  0.0,

  // Expression: 90
  //  Referenced by: '<Root>/Saturation'

  90.0,

  // Expression: 15
  //  Referenced by: '<Root>/Saturation'

  15.0
};

//
// File trailer for generated code.
//
// [EOF]
//
