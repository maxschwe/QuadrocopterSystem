//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller.cpp
//
// Code generated for Simulink model 'controller'.
//
// Model version                  : 1.207
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Oct 25 12:33:16 2025
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
  real_T forces_idx_3;
  real_T throttle_torque_part;
  real_T thrust_part;
  real_T torques_idx_0;
  real_T torques_idx_1;

  // MATLAB Function: '<Root>/MATLAB Function1' incorporates:
  //   Constant: '<Root>/Constant'
  //   Constant: '<Root>/Constant1'
  //   Constant: '<Root>/Constant2'
  //   Constant: '<Root>/Constant3'

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

  thrust_part = rtP.Constant_Value / 4.0;
  forces_idx_1 = 2.0 * rtDW.distance;
  forces_idx_2 = rtP.Constant2_Value / forces_idx_1;
  forces_idx_0 = forces_idx_2 + thrust_part;
  forces_idx_3 = rtP.Constant1_Value / forces_idx_1;
  forces_idx_1 = thrust_part - forces_idx_3;
  forces_idx_2 = thrust_part - forces_idx_2;
  forces_idx_3 += thrust_part;
  torques_idx_0 = 0.25 * rtP.Constant3_Value;
  torques_idx_1 = -0.25 * rtP.Constant3_Value;
  if (forces_idx_0 < rtDW.force_minimum) {
    thrust_part = 0.0;
  } else {
    thrust_part = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_0)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_0 < rtDW.torque_minimum) {
    throttle_torque_part = 0.0;
  } else {
    throttle_torque_part = (torques_idx_0 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_0 = thrust_part + throttle_torque_part;
  if (!(forces_idx_0 >= 0.0)) {
    forces_idx_0 = 0.0;
  }

  if (forces_idx_1 < rtDW.force_minimum) {
    thrust_part = 0.0;
  } else {
    thrust_part = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_1)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_1 < rtDW.torque_minimum) {
    throttle_torque_part = 0.0;
  } else {
    throttle_torque_part = (torques_idx_1 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_1 = thrust_part + throttle_torque_part;
  if (!(forces_idx_1 >= 0.0)) {
    forces_idx_1 = 0.0;
  }

  if (forces_idx_2 < rtDW.force_minimum) {
    thrust_part = 0.0;
  } else {
    thrust_part = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_2)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_0 < rtDW.torque_minimum) {
    throttle_torque_part = 0.0;
  } else {
    throttle_torque_part = (torques_idx_0 - rtDW.b_t) / rtDW.a_t;
  }

  forces_idx_2 = thrust_part + throttle_torque_part;
  if (!(forces_idx_2 >= 0.0)) {
    forces_idx_2 = 0.0;
  }

  if (forces_idx_3 < rtDW.force_minimum) {
    thrust_part = 0.0;
  } else {
    thrust_part = (sqrt(rtDW.b_f * rtDW.b_f - 4.0 * rtDW.a_f * (rtDW.c_f -
      forces_idx_3)) - rtDW.b_f) / (2.0 * rtDW.a_f);
  }

  if (torques_idx_1 < rtDW.torque_minimum) {
    throttle_torque_part = 0.0;
  } else {
    throttle_torque_part = (torques_idx_1 - rtDW.b_t) / rtDW.a_t;
  }

  thrust_part += throttle_torque_part;
  if (!(thrust_part >= 0.0)) {
    thrust_part = 0.0;
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

  if (thrust_part <= 100.0) {
    // Outport: '<Root>/Out4'
    rtY.Out4 = thrust_part;
  } else {
    // Outport: '<Root>/Out4'
    rtY.Out4 = 100.0;
  }

  // End of MATLAB Function: '<Root>/MATLAB Function1'
}

// Model initialize function
void Model::initialize()
{
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
