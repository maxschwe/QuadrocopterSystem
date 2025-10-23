//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_data.cpp
//
// Code generated for Simulink model 'controller'.
//
// Model version                  : 1.206
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Oct 23 19:05:47 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller.h"

// Block parameters (default storage)
Model::P Model::rtP = {
  // Mask Parameter: DiscretePIDController_D
  //  Referenced by: '<S31>/Derivative Gain'

  0.003,

  // Mask Parameter: DiscretePIDController1_D
  //  Referenced by: '<S85>/Derivative Gain'

  0.003,

  // Mask Parameter: DiscretePIDController_Different
  //  Referenced by: '<S33>/UD'

  0.0,

  // Mask Parameter: DiscretePIDController1_Differen
  //  Referenced by: '<S87>/UD'

  0.0,

  // Mask Parameter: DiscretePIDController1_I
  //  Referenced by: '<S91>/Integral Gain'

  0.0,

  // Mask Parameter: DiscretePIDController_I
  //  Referenced by: '<S37>/Integral Gain'

  0.0,

  // Mask Parameter: DiscretePIDController_InitialCo
  //  Referenced by: '<S40>/Integrator'

  0.0,

  // Mask Parameter: DiscretePIDController1_InitialC
  //  Referenced by: '<S94>/Integrator'

  0.0,

  // Mask Parameter: DiscretePIDController_P
  //  Referenced by: '<S45>/Proportional Gain'

  0.014,

  // Mask Parameter: DiscretePIDController1_P
  //  Referenced by: '<S99>/Proportional Gain'

  0.014,

  // Expression: 10
  //  Referenced by: '<Root>/Constant'

  10.0,

  // Expression: 0
  //  Referenced by: '<Root>/target_roll'

  0.0,

  // Computed Parameter: Integrator_gainval
  //  Referenced by: '<S40>/Integrator'

  1.0,

  // Computed Parameter: Tsamp_WtEt
  //  Referenced by: '<S35>/Tsamp'

  250.0,

  // Expression: 0
  //  Referenced by: '<Root>/target_pitch'

  0.0,

  // Computed Parameter: Integrator_gainval_l
  //  Referenced by: '<S94>/Integrator'

  0.004,

  // Computed Parameter: Tsamp_WtEt_a
  //  Referenced by: '<S89>/Tsamp'

  250.0,

  // Expression: 0
  //  Referenced by: '<Root>/Constant3'

  0.0
};

//
// File trailer for generated code.
//
// [EOF]
//
