//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.234
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Feb  3 11:10:18 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof.h"
#include <cstring>
#include <cmath>
#include "rtwtypes.h"

// private model entry point functions
extern void controller_3dof_derivatives();

//
// This function updates continuous states using the ODE1 fixed-step
// solver algorithm
//
void Controller::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE1_IntgData *id { static_cast<ODE1_IntgData *>(rtsiGetSolverData(si)) };

  real_T *f0 { id->f[0] };

  int_T i;
  int_T nXc { 18 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  controller_3dof_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void Controller::step()
{
  real_T A[16];
  real_T A_0[9];
  real_T tmp[9];
  real_T B_0[4];
  real_T c_data[4];
  real_T rtb_thrust[4];
  real_T rtb_u_f[4];
  real_T B_1[3];
  real_T dx_tmp;
  real_T omega_dot_idx_0;
  real_T rtb_Filter;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T s;
  real_T smax;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  int32_T c_k;
  int32_T f;
  int32_T i;
  int32_T ijA;
  int32_T jA;
  int32_T jj;
  int32_T rtemp;
  int8_T ipiv[4];
  int8_T tmp_data[4];
  int8_T tmp_data_0[4];
  int8_T ipiv_0;
  if ((&rtM)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&rtM)->isMinorTimeStep()) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  for (i = 0; i < 6; i++) {
    // Integrator: '<S1>/Integrator'
    rtDW.Integrator[i] = rtX.Integrator_CSTATE[i];
  }

  // Outport: '<Root>/y_pred'
  rtY.y_pred[0] = rtDW.Integrator[0];
  rtY.y_pred[1] = rtDW.Integrator[1];
  rtY.y_pred[2] = rtDW.Integrator[2];
  if ((&rtM)->isMajorTimeStep()) {
    // UnitDelay: '<Root>/Unit Delay'
    rtDW.UnitDelay[0] = rtDW.UnitDelay_DSTATE[0];
    rtDW.UnitDelay[1] = rtDW.UnitDelay_DSTATE[1];
    rtDW.UnitDelay[2] = rtDW.UnitDelay_DSTATE[2];
  }

  // Sum: '<S2>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtb_Filter = rtU.w[1] - rtDW.UnitDelay[0];

  // Gain: '<S47>/Filter Coefficient' incorporates:
  //   Gain: '<S37>/Derivative Gain'
  //   Integrator: '<S39>/Filter'
  //   Sum: '<S39>/SumD'

  rtDW.FilterCoefficient = (rtP.PIDController_D * rtb_Filter - rtX.Filter_CSTATE)
    * rtP.PIDController_N;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/w'

  rtb_Sum2 = rtU.w[2] - rtDW.UnitDelay[1];

  // Gain: '<S99>/Filter Coefficient' incorporates:
  //   Gain: '<S89>/Derivative Gain'
  //   Integrator: '<S91>/Filter'
  //   Sum: '<S91>/SumD'

  rtDW.FilterCoefficient_g = (rtP.PIDController1_D * rtb_Sum2 -
    rtX.Filter_CSTATE_d) * rtP.PIDController1_N;

  // Sum: '<S2>/Sum2' incorporates:
  //   Inport: '<Root>/w'

  rtb_Sum1 = rtU.w[3] - rtDW.UnitDelay[2];

  // Gain: '<S151>/Filter Coefficient' incorporates:
  //   Gain: '<S141>/Derivative Gain'
  //   Integrator: '<S143>/Filter'
  //   Sum: '<S143>/SumD'

  rtDW.FilterCoefficient_e = (rtP.PIDController2_D * rtb_Sum1 -
    rtX.Filter_CSTATE_a) * rtP.PIDController2_N;

  // MATLAB Function: '<S9>/MATLAB Function' incorporates:
  //   Gain: '<S101>/Proportional Gain'
  //   Gain: '<S153>/Proportional Gain'
  //   Gain: '<S49>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S148>/Integrator'
  //   Integrator: '<S44>/Integrator'
  //   Integrator: '<S96>/Integrator'
  //   SignalConversion generated from: '<S166>/ SFunction '
  //   Sum: '<S105>/Sum'
  //   Sum: '<S157>/Sum'
  //   Sum: '<S53>/Sum'

  B_0[0] = rtU.w[0];
  B_0[1] = (rtP.PIDController_P * rtb_Filter + rtX.Integrator_CSTATE_b) +
    rtDW.FilterCoefficient;
  B_0[2] = (rtP.PIDController1_P * rtb_Sum2 + rtX.Integrator_CSTATE_n) +
    rtDW.FilterCoefficient_g;
  B_0[3] = (rtP.PIDController2_P * rtb_Sum1 + rtX.Integrator_CSTATE_f) +
    rtDW.FilterCoefficient_e;
  std::memcpy(&A[0], &rtP.MATLABFunction_E[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (i = 0; i < 3; i++) {
    jj = i * 5;
    jA = 5 - i;
    rtemp = 0;
    smax = std::abs(A[jj]);
    for (c_k = 2; c_k < jA; c_k++) {
      s = std::abs(A[(jj + c_k) - 1]);
      if (s > smax) {
        rtemp = c_k - 1;
        smax = s;
      }
    }

    if (A[jj + rtemp] != 0.0) {
      if (rtemp != 0) {
        jA = i + rtemp;
        ipiv[i] = static_cast<int8_T>(jA + 1);
        smax = A[i];
        A[i] = A[jA];
        A[jA] = smax;
        smax = A[i + 4];
        A[i + 4] = A[jA + 4];
        A[jA + 4] = smax;
        smax = A[i + 8];
        A[i + 8] = A[jA + 8];
        A[jA + 8] = smax;
        smax = A[i + 12];
        A[i + 12] = A[jA + 12];
        A[jA + 12] = smax;
      }

      jA = (jj - i) + 4;
      for (rtemp = jj + 2; rtemp <= jA; rtemp++) {
        A[rtemp - 1] /= A[jj];
      }
    }

    jA = jj + 6;
    rtemp = 2 - i;
    for (c_k = 0; c_k <= rtemp; c_k++) {
      smax = A[((c_k << 2) + jj) + 4];
      if (smax != 0.0) {
        f = (jA - i) + 2;
        for (ijA = jA; ijA <= f; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[i];
    if (i + 1 != ipiv_0) {
      smax = B_0[i];
      B_0[i] = B_0[ipiv_0 - 1];
      B_0[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (B_0[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        B_0[jA - 1] -= A[(jA + jj) - 1] * B_0[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = B_0[i];
    if (smax != 0.0) {
      B_0[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        B_0[jA] -= A[jA + jj] * B_0[i];
      }
    }
  }

  rtb_u_f[0] = 0.0;
  rtb_u_f[1] = 0.0;
  rtb_u_f[2] = 0.0;
  rtb_u_f[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.MATLABFunction_a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.MATLABFunction_a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = B_0[tmp_data[jj]] / rtP.MATLABFunction_a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_u_f[tmp_data[jj]] = c_data[jj] + rtP.MATLABFunction_b;
  }

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[0] > rtP.Saturation_UpperSat) {
    dx_tmp = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[0] < rtP.Saturation_LowerSat) {
    dx_tmp = rtP.Saturation_LowerSat;
  } else {
    dx_tmp = rtb_u_f[0];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'

  smax = dx_tmp - rtP.MATLABFunction1_b;
  rtb_thrust[0] = smax * smax;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[1] > rtP.Saturation_UpperSat) {
    dx_tmp = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[1] < rtP.Saturation_LowerSat) {
    dx_tmp = rtP.Saturation_LowerSat;
  } else {
    dx_tmp = rtb_u_f[1];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'

  smax = dx_tmp - rtP.MATLABFunction1_b;
  rtb_thrust[1] = smax * smax;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[2] > rtP.Saturation_UpperSat) {
    dx_tmp = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[2] < rtP.Saturation_LowerSat) {
    dx_tmp = rtP.Saturation_LowerSat;
  } else {
    dx_tmp = rtb_u_f[2];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'

  smax = dx_tmp - rtP.MATLABFunction1_b;
  rtb_thrust[2] = smax * smax;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[3] > rtP.Saturation_UpperSat) {
    dx_tmp = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[3] < rtP.Saturation_LowerSat) {
    dx_tmp = rtP.Saturation_LowerSat;
  } else {
    dx_tmp = rtb_u_f[3];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'

  smax = dx_tmp - rtP.MATLABFunction1_b;
  rtb_thrust[3] = smax * smax;

  // MATLAB Function: '<S1>/MATLAB Function2'
  omega_dot_idx_0 = 0.0;
  smax = 0.0;
  s = 0.0;
  for (jj = 0; jj < 3; jj++) {
    dx_tmp = rtDW.Integrator[jj + 3];
    omega_dot_idx_0 += rtP.MATLABFunction2_I[3 * jj] * dx_tmp;
    smax += rtP.MATLABFunction2_I[3 * jj + 1] * dx_tmp;
    s += rtP.MATLABFunction2_I[3 * jj + 2] * dx_tmp;
  }

  std::memcpy(&A_0[0], &rtP.MATLABFunction2_I[0], 9U * sizeof(real_T));

  // Gain: '<S1>/Mixer' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  tmp_0 = 0.0;
  tmp_1 = 0.0;
  tmp_2 = 0.0;
  for (jj = 0; jj < 4; jj++) {
    dx_tmp = rtP.MATLABFunction1_a * rtb_thrust[jj];
    i = jj << 2;
    tmp_0 += rtP.Mixer_Gain[i + 1] * dx_tmp;
    tmp_1 += rtP.Mixer_Gain[i + 2] * dx_tmp;
    tmp_2 += rtP.Mixer_Gain[i + 3] * dx_tmp;
  }

  // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
  //   Gain: '<S1>/Mixer'

  B_1[0] = (tmp_0 - 0.5 * rtDW.Integrator[3]) - (s * rtDW.Integrator[4] - smax *
    rtDW.Integrator[5]);
  B_1[1] = (tmp_1 - 0.5 * rtDW.Integrator[4]) - (omega_dot_idx_0 *
    rtDW.Integrator[5] - s * rtDW.Integrator[3]);
  B_1[2] = (tmp_2 - 0.5 * rtDW.Integrator[5]) - (smax * rtDW.Integrator[3] -
    omega_dot_idx_0 * rtDW.Integrator[4]);
  i = 0;
  jj = 1;
  jA = 2;
  smax = std::abs(rtP.MATLABFunction2_I[0]);
  s = std::abs(rtP.MATLABFunction2_I[1]);
  if (s > smax) {
    smax = s;
    i = 1;
    jj = 0;
  }

  if (std::abs(rtP.MATLABFunction2_I[2]) > smax) {
    i = 2;
    jj = 1;
    jA = 0;
  }

  A_0[jj] = rtP.MATLABFunction2_I[jj] / rtP.MATLABFunction2_I[i];
  A_0[jA] /= A_0[i];
  A_0[jj + 3] -= A_0[i + 3] * A_0[jj];
  A_0[jA + 3] -= A_0[i + 3] * A_0[jA];
  A_0[jj + 6] -= A_0[i + 6] * A_0[jj];
  A_0[jA + 6] -= A_0[i + 6] * A_0[jA];
  if (std::abs(A_0[jA + 3]) > std::abs(A_0[jj + 3])) {
    rtemp = jj;
    jj = jA;
    jA = rtemp;
  }

  A_0[jA + 3] /= A_0[jj + 3];
  A_0[jA + 6] -= A_0[jA + 3] * A_0[jj + 6];
  smax = B_1[jj] - B_1[i] * A_0[jj];
  s = ((B_1[jA] - B_1[i] * A_0[jA]) - A_0[jA + 3] * smax) / A_0[jA + 6];
  smax = (smax - A_0[jj + 6] * s) / A_0[jj + 3];
  dx_tmp = std::tan(rtDW.Integrator[1]);
  tmp_0 = std::cos(rtDW.Integrator[0]);
  tmp_1 = std::sin(rtDW.Integrator[0]);
  omega_dot_idx_0 = std::cos(rtDW.Integrator[1]);
  tmp[0] = 1.0;
  tmp[3] = tmp_1 * dx_tmp;
  tmp[6] = tmp_0 * dx_tmp;
  tmp[1] = 0.0;
  tmp[4] = tmp_0;
  tmp[7] = -tmp_1;
  tmp[2] = 0.0;
  tmp[5] = tmp_1 / omega_dot_idx_0;
  tmp[8] = tmp_0 / omega_dot_idx_0;
  omega_dot_idx_0 = 0.0;
  tmp_0 = 0.0;
  tmp_1 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    dx_tmp = rtDW.Integrator[jj + 3];
    omega_dot_idx_0 += tmp[3 * jj] * dx_tmp;
    tmp_0 += tmp[3 * jj + 1] * dx_tmp;
    tmp_1 += tmp[3 * jj + 2] * dx_tmp;
  }

  rtDW.dx[0] = omega_dot_idx_0;
  rtDW.dx[3] = ((B_1[i] - A_0[i + 6] * s) - A_0[i + 3] * smax) / A_0[i];
  rtDW.dx[1] = tmp_0;
  rtDW.dx[4] = smax;
  rtDW.dx[2] = tmp_1;
  rtDW.dx[5] = s;

  // Gain: '<S145>/Integral Gain'
  rtDW.IntegralGain = rtP.PIDController2_I * rtb_Sum1;

  // Gain: '<S93>/Integral Gain'
  rtDW.IntegralGain_b = rtP.PIDController1_I * rtb_Sum2;

  // Gain: '<S41>/Integral Gain'
  rtDW.IntegralGain_f = rtP.PIDController_I * rtb_Filter;

  // Sum: '<S3>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Filter = rtU.w[1] - rtU.y[0];

  // Gain: '<S208>/Filter Coefficient' incorporates:
  //   Gain: '<S198>/Derivative Gain'
  //   Integrator: '<S200>/Filter'
  //   Sum: '<S200>/SumD'

  rtDW.FilterCoefficient_b = (rtP.PIDController_D_c * rtb_Filter -
    rtX.Filter_CSTATE_g) * rtP.PIDController_N_o;

  // Sum: '<S3>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum1 = rtU.w[2] - rtU.y[1];

  // Gain: '<S260>/Filter Coefficient' incorporates:
  //   Gain: '<S250>/Derivative Gain'
  //   Integrator: '<S252>/Filter'
  //   Sum: '<S252>/SumD'

  rtDW.FilterCoefficient_bz = (rtP.PIDController1_D_k * rtb_Sum1 -
    rtX.Filter_CSTATE_m) * rtP.PIDController1_N_l;

  // Sum: '<S3>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtU.w[3] - rtU.y[2];

  // Gain: '<S312>/Filter Coefficient' incorporates:
  //   Gain: '<S302>/Derivative Gain'
  //   Integrator: '<S304>/Filter'
  //   Sum: '<S304>/SumD'

  rtDW.FilterCoefficient_a = (rtP.PIDController2_D_m * rtb_Sum2 -
    rtX.Filter_CSTATE_c) * rtP.PIDController2_N_b;

  // MATLAB Function: '<S170>/MATLAB Function' incorporates:
  //   Gain: '<S210>/Proportional Gain'
  //   Gain: '<S262>/Proportional Gain'
  //   Gain: '<S314>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S205>/Integrator'
  //   Integrator: '<S257>/Integrator'
  //   Integrator: '<S309>/Integrator'
  //   MATLAB Function: '<S9>/MATLAB Function'
  //   SignalConversion generated from: '<S327>/ SFunction '
  //   Sum: '<S214>/Sum'
  //   Sum: '<S266>/Sum'
  //   Sum: '<S318>/Sum'

  B_0[0] = rtU.w[0];
  B_0[1] = (rtP.PIDController_P_f * rtb_Filter + rtX.Integrator_CSTATE_p) +
    rtDW.FilterCoefficient_b;
  B_0[2] = (rtP.PIDController1_P_k * rtb_Sum1 + rtX.Integrator_CSTATE_i) +
    rtDW.FilterCoefficient_bz;
  B_0[3] = (rtP.PIDController2_P_n * rtb_Sum2 + rtX.Integrator_CSTATE_j) +
    rtDW.FilterCoefficient_a;
  std::memcpy(&A[0], &rtP.MATLABFunction_E_a[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (i = 0; i < 3; i++) {
    jj = i * 5;
    jA = 5 - i;
    rtemp = 0;
    smax = std::abs(A[jj]);
    for (c_k = 2; c_k < jA; c_k++) {
      s = std::abs(A[(jj + c_k) - 1]);
      if (s > smax) {
        rtemp = c_k - 1;
        smax = s;
      }
    }

    if (A[jj + rtemp] != 0.0) {
      if (rtemp != 0) {
        jA = i + rtemp;
        ipiv[i] = static_cast<int8_T>(jA + 1);
        smax = A[i];
        A[i] = A[jA];
        A[jA] = smax;
        smax = A[i + 4];
        A[i + 4] = A[jA + 4];
        A[jA + 4] = smax;
        smax = A[i + 8];
        A[i + 8] = A[jA + 8];
        A[jA + 8] = smax;
        smax = A[i + 12];
        A[i + 12] = A[jA + 12];
        A[jA + 12] = smax;
      }

      jA = (jj - i) + 4;
      for (rtemp = jj + 2; rtemp <= jA; rtemp++) {
        A[rtemp - 1] /= A[jj];
      }
    }

    jA = jj + 6;
    rtemp = 2 - i;
    for (c_k = 0; c_k <= rtemp; c_k++) {
      smax = A[((c_k << 2) + jj) + 4];
      if (smax != 0.0) {
        f = (jA - i) + 2;
        for (ijA = jA; ijA <= f; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[i];
    if (i + 1 != ipiv_0) {
      smax = B_0[i];
      B_0[i] = B_0[ipiv_0 - 1];
      B_0[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (B_0[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        B_0[jA - 1] -= A[(jA + jj) - 1] * B_0[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = B_0[i];
    if (smax != 0.0) {
      B_0[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        B_0[jA] -= A[jA + jj] * B_0[i];
      }
    }
  }

  rtb_thrust[0] = 0.0;
  rtb_thrust[1] = 0.0;
  rtb_thrust[2] = 0.0;
  rtb_thrust[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.MATLABFunction_a_c >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.MATLABFunction_a_c >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = B_0[tmp_data_0[jj]] / rtP.MATLABFunction_a_c;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.MATLABFunction_b_j;
  }

  // Saturate: '<S170>/Saturation' incorporates:
  //   MATLAB Function: '<S170>/MATLAB Function'

  if (rtb_thrust[0] > rtP.Saturation_UpperSat_o) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat_o;
  } else if (rtb_thrust[0] < rtP.Saturation_LowerSat_g) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat_g;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_thrust[0];
  }

  if (rtb_thrust[1] > rtP.Saturation_UpperSat_o) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat_o;
  } else if (rtb_thrust[1] < rtP.Saturation_LowerSat_g) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat_g;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_thrust[1];
  }

  if (rtb_thrust[2] > rtP.Saturation_UpperSat_o) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat_o;
  } else if (rtb_thrust[2] < rtP.Saturation_LowerSat_g) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat_g;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_thrust[2];
  }

  if (rtb_thrust[3] > rtP.Saturation_UpperSat_o) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat_o;
  } else if (rtb_thrust[3] < rtP.Saturation_LowerSat_g) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat_g;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_thrust[3];
  }

  // End of Saturate: '<S170>/Saturation'

  // Gain: '<S306>/Integral Gain'
  rtDW.IntegralGain_p = rtP.PIDController2_I_i * rtb_Sum2;

  // Gain: '<S254>/Integral Gain'
  rtDW.IntegralGain_o = rtP.PIDController1_I_m * rtb_Sum1;

  // Gain: '<S202>/Integral Gain'
  rtDW.IntegralGain_od = rtP.PIDController_I_a * rtb_Filter;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<Root>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.Integrator[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.Integrator[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.Integrator[2];
    }
  }                                    // end MajorTimeStep

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
      // Update absolute timer for sample time: [0.01s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.01, which is the step size
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
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S1>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S1>/Integrator'

  // Derivatives for Integrator: '<S44>/Integrator'
  _rtXdot->Integrator_CSTATE_b = rtDW.IntegralGain_f;

  // Derivatives for Integrator: '<S39>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S96>/Integrator'
  _rtXdot->Integrator_CSTATE_n = rtDW.IntegralGain_b;

  // Derivatives for Integrator: '<S91>/Filter'
  _rtXdot->Filter_CSTATE_d = rtDW.FilterCoefficient_g;

  // Derivatives for Integrator: '<S148>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S143>/Filter'
  _rtXdot->Filter_CSTATE_a = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S205>/Integrator'
  _rtXdot->Integrator_CSTATE_p = rtDW.IntegralGain_od;

  // Derivatives for Integrator: '<S200>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_b;

  // Derivatives for Integrator: '<S257>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S252>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_bz;

  // Derivatives for Integrator: '<S309>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S304>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.FilterCoefficient_a;
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
  (&rtM)->intgData.f[0] = (&rtM)->odeF[0];
  (&rtM)->contStates = ((X *) &rtX);
  (&rtM)->contStateDisabled = ((XDis *) &rtXDis);
  (&rtM)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&rtM)->solverInfo, static_cast<void *>(&(&rtM)->intgData));
  rtsiSetSolverName(&(&rtM)->solverInfo,"ode1");
  (&rtM)->setTPtr(&(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.01;

  {
    int32_T i;

    // InitializeConditions for Integrator: '<S1>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC;
    }

    // End of InitializeConditions for Integrator: '<S1>/Integrator'

    // InitializeConditions for UnitDelay: '<Root>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition;
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition;
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition;

    // InitializeConditions for Integrator: '<S44>/Integrator'
    rtX.Integrator_CSTATE_b = rtP.PIDController_InitialConditio_g;

    // InitializeConditions for Integrator: '<S39>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S96>/Integrator'
    rtX.Integrator_CSTATE_n = rtP.PIDController1_InitialConditi_k;

    // InitializeConditions for Integrator: '<S91>/Filter'
    rtX.Filter_CSTATE_d = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S148>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S143>/Filter'
    rtX.Filter_CSTATE_a = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S205>/Integrator'
    rtX.Integrator_CSTATE_p = rtP.PIDController_InitialConditio_d;

    // InitializeConditions for Integrator: '<S200>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S257>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S252>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S309>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController2_InitialConditi_o;

    // InitializeConditions for Integrator: '<S304>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_e;
  }
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
