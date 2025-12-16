//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.102
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Dec 15 14:54:13 2025
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

// private model entry point functions
extern void controller_3dof_derivatives();

//=========*
//  Asserts *
// =========
#ifndef utAssert
#if defined(DOASSERTS)
#if !defined(PRINT_ASSERTS)
#include <assert.h>
#define utAssert(exp)                  assert(exp)
#else
#include <stdio.h>

static void _assert(char_T *statement, char_T *file, int line)
{
  printf("%s in %s on line %d\n", statement, file, line);
}

#define utAssert(_EX)                  ((_EX) ? (void)0 : _assert(#_EX, __FILE__, __LINE__))
#endif

#else
#define utAssert(exp)                                            // do nothing
#endif
#endif

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void Controller::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 6 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  controller_3dof_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  controller_3dof_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  controller_3dof_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void Controller::step()
{
  real_T b_data[4];
  real_T rtb_Saturation[4];
  real_T rtb_u[4];
  real_T rtb_Saturation_0;
  real_T rtb_Saturation_1;
  real_T rtb_Saturation_2;
  real_T rtb_Saturation_3;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T rtb_Sum_e;
  real_T tmp;
  int32_T i;
  int32_T rtb_Saturation_tmp;
  static const real_T a[16]{ 0.25, 0.25, 0.25, 0.25, 0.0, -2.5, 0.0, 2.5, 2.5,
    0.0, -2.5, 0.0, 7.1225, -7.1225, 7.1225, -7.1225 };

  int32_T b_size_idx_0;
  if ((&rtM)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&rtM)->isMinorTimeStep()) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // Sum: '<Root>/Sum' incorporates:
  //   Inport: '<Root>/roll'
  //   Inport: '<Root>/roll_target'

  rtb_Sum_e = rtU.roll_target - rtU.roll;

  // Gain: '<S43>/Filter Coefficient' incorporates:
  //   Gain: '<S33>/Derivative Gain'
  //   Integrator: '<S35>/Filter'
  //   Sum: '<S35>/SumD'

  rtDW.FilterCoefficient = (rtP.PIDController_D * rtb_Sum_e - rtX.Filter_CSTATE)
    * rtP.PIDController_N;

  // Sum: '<Root>/Sum1' incorporates:
  //   Inport: '<Root>/pitch'
  //   Inport: '<Root>/pitch_target'

  rtb_Sum1 = rtU.pitch_target - rtU.pitch;

  // Gain: '<S95>/Filter Coefficient' incorporates:
  //   Gain: '<S85>/Derivative Gain'
  //   Integrator: '<S87>/Filter'
  //   Sum: '<S87>/SumD'

  rtDW.FilterCoefficient_p = (rtP.PIDController1_D * rtb_Sum1 -
    rtX.Filter_CSTATE_d) * rtP.PIDController1_N;

  // Sum: '<Root>/Sum2' incorporates:
  //   Inport: '<Root>/yaw'
  //   Inport: '<Root>/yaw_target'

  rtb_Sum2 = rtU.yaw_target - rtU.yaw;

  // Gain: '<S147>/Filter Coefficient' incorporates:
  //   Gain: '<S137>/Derivative Gain'
  //   Integrator: '<S139>/Filter'
  //   Sum: '<S139>/SumD'

  rtDW.FilterCoefficient_d = (rtP.PIDController2_D * rtb_Sum2 -
    rtX.Filter_CSTATE_j) * rtP.PIDController2_N;

  // SignalConversion generated from: '<S2>/ SFunction ' incorporates:
  //   Gain: '<S149>/Proportional Gain'
  //   Gain: '<S45>/Proportional Gain'
  //   Gain: '<S97>/Proportional Gain'
  //   Inport: '<Root>/throttle'
  //   Integrator: '<S144>/Integrator'
  //   Integrator: '<S40>/Integrator'
  //   Integrator: '<S92>/Integrator'
  //   MATLAB Function: '<Root>/MATLAB Function'
  //   Sum: '<S101>/Sum'
  //   Sum: '<S153>/Sum'
  //   Sum: '<S49>/Sum'

  rtb_Saturation[0] = rtU.throttle;
  rtb_Saturation[1] = (rtP.PIDController_P * rtb_Sum_e + rtX.Integrator_CSTATE)
    + rtDW.FilterCoefficient;
  rtb_Saturation[2] = (rtP.PIDController1_P * rtb_Sum1 + rtX.Integrator_CSTATE_f)
    + rtDW.FilterCoefficient_p;
  rtb_Saturation[3] = (rtP.PIDController2_P * rtb_Sum2 + rtX.Integrator_CSTATE_j)
    + rtDW.FilterCoefficient_d;

  // MATLAB Function: '<Root>/MATLAB Function'
  rtb_Saturation_0 = 0.0;
  rtb_Saturation_1 = 0.0;
  rtb_Saturation_2 = 0.0;
  rtb_Saturation_3 = 0.0;
  for (i = 0; i < 4; i++) {
    tmp = rtb_Saturation[i];
    rtb_Saturation_tmp = i << 2;
    rtb_Saturation_0 += a[rtb_Saturation_tmp] * tmp;
    rtb_Saturation_1 += a[rtb_Saturation_tmp + 1] * tmp;
    rtb_Saturation_2 += a[rtb_Saturation_tmp + 2] * tmp;
    rtb_Saturation_3 += a[rtb_Saturation_tmp + 3] * tmp;
    rtb_u[i] = 0.0;
  }

  rtb_Saturation[3] = rtb_Saturation_3;
  rtb_Saturation[2] = rtb_Saturation_2;
  rtb_Saturation[1] = rtb_Saturation_1;
  rtb_Saturation[0] = rtb_Saturation_0;
  rtb_Saturation_tmp = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Saturation[i] / 0.0013 >= 0.0) {
      rtb_Saturation_tmp++;
    }
  }

  b_size_idx_0 = rtb_Saturation_tmp;
  rtb_Saturation_tmp = 0;
  for (i = 0; i < 4; i++) {
    tmp = rtb_Saturation[i] / 0.0013;
    if (tmp >= 0.0) {
      b_data[rtb_Saturation_tmp] = tmp;
      rtb_Saturation_tmp++;
    }
  }

  for (rtb_Saturation_tmp = 0; rtb_Saturation_tmp < b_size_idx_0;
       rtb_Saturation_tmp++) {
    b_data[rtb_Saturation_tmp] = std::sqrt(b_data[rtb_Saturation_tmp]);
  }

  rtb_Saturation_tmp = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Saturation[i] / 0.0013 >= 0.0) {
      rtb_u[i] = b_data[rtb_Saturation_tmp] + 8.5908;
      rtb_Saturation_tmp++;
    }
  }

  if ((&rtM)->isMajorTimeStep()) {
    // Assertion: '<S1>/Assertion' incorporates:
    //   Constant: '<S1>/max_val'
    //   Constant: '<S1>/min_val'
    //   Logic: '<S1>/conjunction'
    //   RelationalOperator: '<S1>/max_relop'
    //   RelationalOperator: '<S1>/min_relop'

    utAssert((rtP.CheckStaticRange_min <= rtb_u[0]) && (rtb_u[0] <=
              rtP.CheckStaticRange_max));
    utAssert((rtP.CheckStaticRange_min <= rtb_u[1]) && (rtb_u[1] <=
              rtP.CheckStaticRange_max));
    utAssert((rtP.CheckStaticRange_min <= rtb_u[2]) && (rtb_u[2] <=
              rtP.CheckStaticRange_max));
    utAssert((rtP.CheckStaticRange_min <= rtb_u[3]) && (rtb_u[3] <=
              rtP.CheckStaticRange_max));
  }

  // Saturate: '<Root>/Saturation'
  if (rtb_u[0] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttle_1'
    rtY.throttle_1 = rtP.Saturation_UpperSat;
  } else if (rtb_u[0] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttle_1'
    rtY.throttle_1 = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttle_1'
    rtY.throttle_1 = rtb_u[0];
  }

  if (rtb_u[1] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttle_2'
    rtY.throttle_2 = rtP.Saturation_UpperSat;
  } else if (rtb_u[1] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttle_2'
    rtY.throttle_2 = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttle_2'
    rtY.throttle_2 = rtb_u[1];
  }

  if (rtb_u[2] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttle_3'
    rtY.throttle_3 = rtP.Saturation_UpperSat;
  } else if (rtb_u[2] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttle_3'
    rtY.throttle_3 = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttle_3'
    rtY.throttle_3 = rtb_u[2];
  }

  if (rtb_u[3] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttle_4'
    rtY.throttle_4 = rtP.Saturation_UpperSat;
  } else if (rtb_u[3] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttle_4'
    rtY.throttle_4 = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttle_4'
    rtY.throttle_4 = rtb_u[3];
  }

  // End of Saturate: '<Root>/Saturation'

  // Gain: '<S141>/Integral Gain'
  rtDW.IntegralGain = rtP.PIDController2_I * rtb_Sum2;

  // Gain: '<S89>/Integral Gain'
  rtDW.IntegralGain_i = rtP.PIDController1_I * rtb_Sum1;

  // Gain: '<S37>/Integral Gain'
  rtDW.IntegralGain_l = rtP.PIDController_I * rtb_Sum_e;
  if ((&rtM)->isMajorTimeStep()) {
    rt_ertODEUpdateContinuousStates(&(&rtM)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&rtM)->Timing.clockTick0;
    (&rtM)->Timing.t[0] = rtsiGetSolverStopTime(&(&rtM)->solverInfo);

    {
      // Update absolute timer for sample time: [0.005s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.005, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&rtM)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void Controller::controller_3dof_derivatives()
{
  Controller::XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S40>/Integrator'
  _rtXdot->Integrator_CSTATE = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S35>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S92>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S87>/Filter'
  _rtXdot->Filter_CSTATE_d = rtDW.FilterCoefficient_p;

  // Derivatives for Integrator: '<S144>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S139>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.FilterCoefficient_d;
}

// Model initialize function
void Controller::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&rtM)->solverInfo, &(&rtM)->Timing.simTimeStep);
    rtsiSetTPtr(&(&rtM)->solverInfo, (&rtM)->getTPtrPtr());
    rtsiSetStepSizePtr(&(&rtM)->solverInfo, &(&rtM)->Timing.stepSize0);
    rtsiSetdXPtr(&(&rtM)->solverInfo, &(&rtM)->derivs);
    rtsiSetContStatesPtr(&(&rtM)->solverInfo, (real_T **) &(&rtM)->contStates);
    rtsiSetNumContStatesPtr(&(&rtM)->solverInfo, &(&rtM)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&rtM)->solverInfo, (boolean_T**) &(&rtM)
      ->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&rtM)->solverInfo, (&rtM)->getErrorStatusPtr());
    rtsiSetRTModelPtr(&(&rtM)->solverInfo, (&rtM));
  }

  rtsiSetSimTimeStep(&(&rtM)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&rtM)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&rtM)->solverInfo, false);
  (&rtM)->intgData.y = (&rtM)->odeY;
  (&rtM)->intgData.f[0] = (&rtM)->odeF[0];
  (&rtM)->intgData.f[1] = (&rtM)->odeF[1];
  (&rtM)->intgData.f[2] = (&rtM)->odeF[2];
  (&rtM)->contStates = ((X *) &rtX);
  (&rtM)->contStateDisabled = ((XDis *) &rtXDis);
  (&rtM)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&rtM)->solverInfo, static_cast<void *>(&(&rtM)->intgData));
  rtsiSetSolverName(&(&rtM)->solverInfo,"ode3");
  (&rtM)->setTPtr(&(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.005;

  // InitializeConditions for Integrator: '<S40>/Integrator'
  rtX.Integrator_CSTATE = rtP.PIDController_InitialConditio_d;

  // InitializeConditions for Integrator: '<S35>/Filter'
  rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

  // InitializeConditions for Integrator: '<S92>/Integrator'
  rtX.Integrator_CSTATE_f = rtP.PIDController1_InitialConditi_l;

  // InitializeConditions for Integrator: '<S87>/Filter'
  rtX.Filter_CSTATE_d = rtP.PIDController1_InitialCondition;

  // InitializeConditions for Integrator: '<S144>/Integrator'
  rtX.Integrator_CSTATE_j = rtP.PIDController2_InitialConditi_k;

  // InitializeConditions for Integrator: '<S139>/Filter'
  rtX.Filter_CSTATE_j = rtP.PIDController2_InitialCondition;
}

time_T** Controller::RT_MODEL::getTPtrPtr()
{
  return &(Timing.t);
}

boolean_T Controller::RT_MODEL::getStopRequested() const
{
  return (Timing.stopRequestedFlag);
}

void Controller::RT_MODEL::setStopRequested(boolean_T aStopRequested)
{
  (Timing.stopRequestedFlag = aStopRequested);
}

const char_T* Controller::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void Controller::RT_MODEL::setErrorStatus(const char_T* const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

time_T* Controller::RT_MODEL::getTPtr() const
{
  return (Timing.t);
}

void Controller::RT_MODEL::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

boolean_T* Controller::RT_MODEL::getStopRequestedPtr()
{
  return (&(Timing.stopRequestedFlag));
}

const char_T** Controller::RT_MODEL::getErrorStatusPtr()
{
  return &errorStatus;
}

boolean_T Controller::RT_MODEL::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

boolean_T Controller::RT_MODEL::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

time_T Controller::RT_MODEL::getTStart() const
{
  return (Timing.tStart);
}

// Constructor
Controller::Controller() :
  rtU(),
  rtY(),
  rtDW(),
  rtX(),
  rtXDis(),
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
