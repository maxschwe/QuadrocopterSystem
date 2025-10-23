//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller.cpp
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
#include <math.h>
#include "rtwtypes.h"

// Model step function
void Model::step()
{
  real_T forces_idx_0;
  real_T forces_idx_1;
  real_T forces_idx_2;
  real_T rtb_Sum;
  real_T rtb_Sum_h3;
  real_T rtb_Tsamp_l;
  real_T torques_idx_0;
  real_T torques_idx_1;

  // Sum: '<Root>/Sum' incorporates:
  //   Constant: '<Root>/target_roll'
  //   Inport: '<Root>/roll'

  rtDW.Sum_d = rtP.target_roll_Value - rtU.roll;

  // SampleTimeMath: '<S35>/Tsamp' incorporates:
  //   Gain: '<S31>/Derivative Gain'
  //
  //  About '<S35>/Tsamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //
  rtDW.Tsamp = rtP.DiscretePIDController_D * rtDW.Sum_d * rtP.Tsamp_WtEt;

  // Sum: '<Root>/Sum1' incorporates:
  //   Constant: '<Root>/target_pitch'
  //   Inport: '<Root>/pitch'

  rtDW.Sum1 = rtP.target_pitch_Value - rtU.pitch;

  // SampleTimeMath: '<S89>/Tsamp' incorporates:
  //   Gain: '<S85>/Derivative Gain'
  //
  //  About '<S89>/Tsamp':
  //   y = u * K where K = 1 / ( w * Ts )
  //
  rtb_Tsamp_l = rtP.DiscretePIDController1_D * rtDW.Sum1 * rtP.Tsamp_WtEt_a;

  // MATLAB Function: '<Root>/MATLAB Function1' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant3'
  //   Delay: '<S33>/UD'
  //   Delay: '<S87>/UD'
  //   DiscreteIntegrator: '<S40>/Integrator'
  //   DiscreteIntegrator: '<S94>/Integrator'
  //   Gain: '<S45>/Proportional Gain'
  //   Gain: '<S99>/Proportional Gain'
  //   Sum: '<S103>/Sum'
  //   Sum: '<S33>/Diff'
  //   Sum: '<S49>/Sum'
  //   Sum: '<S87>/Diff'

  if (!rtDW.a_f_not_empty) {
    rtDW.a_f_not_empty = true;
    rtDW.a_f = 0.00063476735;
    rtDW.b_f = 0.0440387423;
    rtDW.c_f = -1.31423643;
    rtDW.a_t = 0.00460737;
    rtDW.b_t = -0.1452505;
    rtDW.force_minimum = -2.2204460492503131E-16;
    rtDW.torque_minimum = 31.52568602044116;
  }

  rtDW.thrust_part = rtP.Constant_Value / 4.0;
  forces_idx_1 = 2.0 * rtDW.distance;
  forces_idx_2 = ((rtP.DiscretePIDController1_P * rtDW.Sum1 +
                   rtDW.Integrator_DSTATE_f) + (rtb_Tsamp_l - rtDW.UD_DSTATE_p))
    / forces_idx_1;
  forces_idx_0 = forces_idx_2 + rtDW.thrust_part;
  rtb_Sum = ((rtP.DiscretePIDController_P * rtDW.Sum_d + rtDW.Integrator_DSTATE)
             + (rtDW.Tsamp - rtDW.UD_DSTATE)) / forces_idx_1;
  forces_idx_1 = rtDW.thrust_part - rtb_Sum;
  forces_idx_2 = rtDW.thrust_part - forces_idx_2;
  rtDW.thrust_part += rtb_Sum;
  torques_idx_0 = 0.25 * rtP.Constant3_Value;
  torques_idx_1 = -0.25 * rtP.Constant3_Value;
  if (forces_idx_0 < rtDW.force_minimum) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_0)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_0 < rtDW.torque_minimum) {
    rtb_Sum_h3 = 0.0;
  } else {
    rtb_Sum_h3 = (torques_idx_0 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_0 = rtb_Sum + rtb_Sum_h3;
  if (!(forces_idx_0 >= 0.0)) {
    forces_idx_0 = 0.0;
  }

  if (forces_idx_1 < rtDW.force_minimum) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_1)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_1 < rtDW.torque_minimum) {
    rtb_Sum_h3 = 0.0;
  } else {
    rtb_Sum_h3 = (torques_idx_1 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_1 = rtb_Sum + rtb_Sum_h3;
  if (!(forces_idx_1 >= 0.0)) {
    forces_idx_1 = 0.0;
  }

  if (forces_idx_2 < rtDW.force_minimum) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_2)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_0 < rtDW.torque_minimum) {
    rtb_Sum_h3 = 0.0;
  } else {
    rtb_Sum_h3 = (torques_idx_0 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_2 = rtb_Sum + rtb_Sum_h3;
  if (!(forces_idx_2 >= 0.0)) {
    forces_idx_2 = 0.0;
  }

  if (rtDW.thrust_part < rtDW.force_minimum) {
    rtb_Sum = 0.0;
  } else {
    rtb_Sum = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      rtDW.thrust_part)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_1 < rtDW.torque_minimum) {
    rtb_Sum_h3 = 0.0;
  } else {
    rtb_Sum_h3 = (torques_idx_1 - rtDW.b_t) / rtDW.a_t;
  }

  rtDW.thrust_part = rtb_Sum + rtb_Sum_h3;
  if (!(rtDW.thrust_part >= 0.0)) {
    rtDW.thrust_part = 0.0;
  }

  if (forces_idx_0 <= 100.0) {
    // Outport: '<Root>/Out1'
    rtY.Out1 = forces_idx_0;
  } else {
    // Outport: '<Root>/Out1'
    rtY.Out1 = 100.0;
  }

  if (forces_idx_1 <= 100.0) {
    // Outport: '<Root>/Out2'
    rtY.Out2 = forces_idx_1;
  } else {
    // Outport: '<Root>/Out2'
    rtY.Out2 = 100.0;
  }

  if (forces_idx_2 <= 100.0) {
    // Outport: '<Root>/Out3'
    rtY.Out3 = forces_idx_2;
  } else {
    // Outport: '<Root>/Out3'
    rtY.Out3 = 100.0;
  }

  if (rtDW.thrust_part <= 100.0) {
    // Outport: '<Root>/Out4'
    rtY.Out4 = rtDW.thrust_part;
  } else {
    // Outport: '<Root>/Out4'
    rtY.Out4 = 100.0;
  }

  // End of MATLAB Function: '<Root>/MATLAB Function1'

  // Update for DiscreteIntegrator: '<S40>/Integrator' incorporates:
  //   Gain: '<S37>/Integral Gain'

  rtDW.Integrator_DSTATE += rtP.DiscretePIDController_I * rtDW.Sum_d *
    rtP.Integrator_gainval;

  // Update for Delay: '<S33>/UD'
  rtDW.UD_DSTATE = rtDW.Tsamp;

  // Update for DiscreteIntegrator: '<S94>/Integrator' incorporates:
  //   Gain: '<S91>/Integral Gain'

  rtDW.Integrator_DSTATE_f += rtP.DiscretePIDController1_I * rtDW.Sum1 *
    rtP.Integrator_gainval_l;

  // Update for Delay: '<S87>/UD'
  rtDW.UD_DSTATE_p = rtb_Tsamp_l;
}

// Model initialize function
void Model::initialize()
{
  // InitializeConditions for DiscreteIntegrator: '<S40>/Integrator'
  rtDW.Integrator_DSTATE = rtP.DiscretePIDController_InitialCo;

  // InitializeConditions for Delay: '<S33>/UD'
  rtDW.UD_DSTATE = rtP.DiscretePIDController_Different;

  // InitializeConditions for DiscreteIntegrator: '<S94>/Integrator'
  rtDW.Integrator_DSTATE_f = rtP.DiscretePIDController1_InitialC;

  // InitializeConditions for Delay: '<S87>/UD'
  rtDW.UD_DSTATE_p = rtP.DiscretePIDController1_Differen;

  // SystemInitialize for MATLAB Function: '<Root>/MATLAB Function1'
  rtDW.distance = 0.2;
}

const char_T* Model::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void Model::RT_MODEL::setErrorStatus(const char_T* const volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
Model::Model() :
  rtU(),
  rtY(),
  rtDW(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
Model::~Model()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Model::RT_MODEL * Model::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
