//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.100
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Dec  1 15:00:20 2025
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
  //  Referenced by: '<S33>/Derivative Gain'

  0.0082,

  // Mask Parameter: PIDController1_D
  //  Referenced by: '<S85>/Derivative Gain'

  0.0082,

  // Mask Parameter: PIDController2_D
  //  Referenced by: '<S137>/Derivative Gain'

  0.006,

  // Mask Parameter: PIDController2_I
  //  Referenced by: '<S141>/Integral Gain'

  0.005,

  // Mask Parameter: PIDController1_I
  //  Referenced by: '<S89>/Integral Gain'

  0.02,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S37>/Integral Gain'

  0.02,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S35>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S87>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S139>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S40>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_l
  //  Referenced by: '<S92>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S144>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S43>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController1_N
  //  Referenced by: '<S95>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController2_N
  //  Referenced by: '<S147>/Filter Coefficient'

  100.0,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S45>/Proportional Gain'

  0.012,

  // Mask Parameter: PIDController1_P
  //  Referenced by: '<S97>/Proportional Gain'

  0.012,

  // Mask Parameter: PIDController2_P
  //  Referenced by: '<S149>/Proportional Gain'

  0.006,

  // Mask Parameter: CheckStaticRange_max
  //  Referenced by: '<S1>/max_val'

  85.0,

  // Mask Parameter: CheckStaticRange_min
  //  Referenced by: '<S1>/min_val'

  20.0,

  // Expression: 5
  //  Referenced by: '<Root>/Constant2'

  5.0,

  // Expression: 0
  //  Referenced by: '<Root>/target_roll'

  0.0,

  // Expression: 0
  //  Referenced by: '<Root>/target_pitch'

  0.0,

  // Expression: 0
  //  Referenced by: '<Root>/target_yaw'

  0.0,

  // Expression: 90
  //  Referenced by: '<Root>/Saturation'

  90.0,

  // Expression: 15
  //  Referenced by: '<Root>/Saturation'

  15.0,

  // Computed Parameter: Assertion_Enabled
  //  Referenced by: '<S1>/Assertion'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
