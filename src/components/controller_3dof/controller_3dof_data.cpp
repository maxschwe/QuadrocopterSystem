//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_data.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.86
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Nov 28 17:24:05 2025
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
  //  Referenced by: '<S31>/Derivative Gain'

  0.0008,

  // Mask Parameter: PIDController_I
  //  Referenced by: '<S35>/Integral Gain'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S33>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_d
  //  Referenced by: '<S38>/Integrator'

  0.0,

  // Mask Parameter: PIDController_N
  //  Referenced by: '<S41>/Filter Coefficient'

  10.0,

  // Mask Parameter: PIDController_P
  //  Referenced by: '<S43>/Proportional Gain'

  0.01,

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
  //  Referenced by: '<Root>/Constant3'

  0.0,

  // Expression: 0
  //  Referenced by: '<Root>/Constant'

  0.0,

  // Expression: 0
  //  Referenced by: '<Root>/Constant1'

  0.0,

  // Expression: 85
  //  Referenced by: '<Root>/Saturation'

  85.0,

  // Expression: 20
  //  Referenced by: '<Root>/Saturation'

  20.0,

  // Computed Parameter: Assertion_Enabled
  //  Referenced by: '<S1>/Assertion'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
