//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.52
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Nov 19 17:56:25 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof.h"
#include <cmath>
#include "rtwtypes.h"

// Model step function
void Controller::step()
{
  int32_T k;
  real32_T rtb_u[4];
  real32_T tau_Value;
  real32_T tau_Value_0;
  real32_T tau_Value_1;
  real32_T tau_Value_2;
  static const real32_T b[16]{ 0.25F, 0.25F, 0.25F, 0.25F, 0.0F, -2.5F, 0.0F,
    2.5F, 2.5F, 0.0F, -2.5F, 0.0F, 7.1225F, -7.1225F, 7.1225F, -7.1225F };

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   Constant: '<Root>/tau'

  tau_Value = rtP.tau_Value[1];
  tau_Value_0 = rtP.tau_Value[0];
  tau_Value_1 = rtP.tau_Value[2];
  tau_Value_2 = rtP.tau_Value[3];
  for (k = 0; k < 4; k++) {
    rtb_u[k] = std::sqrt((((b[k + 4] * tau_Value + b[k] * tau_Value_0) + b[k + 8]
      * tau_Value_1) + b[k + 12] * tau_Value_2) / 0.0013F) + 8.5908F;
  }

  // End of MATLAB Function: '<Root>/MATLAB Function'

  // Outport: '<Root>/throttle_1'
  rtY.throttle_1 = rtb_u[0];

  // Outport: '<Root>/throttle_2'
  rtY.throttle_2 = rtb_u[1];

  // Outport: '<Root>/throttle_3'
  rtY.throttle_3 = rtb_u[2];

  // Outport: '<Root>/throttle_4'
  rtY.throttle_4 = rtb_u[3];
}

// Model initialize function
void Controller::initialize()
{
  // (no initialization code required)
}

const char_T* Controller::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void Controller::RT_MODEL::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
Controller::Controller() :
  rtU(),
  rtY(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Controller::~Controller() = default;

// Real-Time Model get method
Controller::RT_MODEL * Controller::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
