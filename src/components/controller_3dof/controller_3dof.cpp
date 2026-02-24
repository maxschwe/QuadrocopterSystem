//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
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
#include "rtwtypes.h"
#include <cstring>
#include <cmath>

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
  int_T nXc { 24 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  controller_3dof_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

//
// Output and update for atomic system:
//    '<S3>/KF_Elevation'
//    '<S4>/KF_Elevation'
//    '<S6>/KF_Elevation'
//
void Controller::KF_Elevation(const real_T rtu_A[4], const real_T rtu_B[2],
  const real_T rtu_C[2], const real_T rtu_Q[4], real_T rtu_R, real_T rtu_y,
  real_T rtu_u, const real_T rtu_Pold[4], real_T rty_x_dach[2], real_T rty_P[4])
{
  real_T P_pred[4];
  real_T b_I_0[4];
  real_T c_I[4];
  real_T c_I_0[4];
  real_T rtu_A_0[4];
  real_T x_pred[2];
  real_T K_idx_0;
  real_T K_idx_1;
  real_T c_I_idx_2;
  real_T c_I_idx_3;
  real_T rtu_A_1;
  real_T rtu_A_2;
  real_T rtu_A_3;
  real_T rtu_A_4;
  real_T rty_x_dach_0;
  int32_T tmp;
  int8_T b_I[4];
  K_idx_0 = rtu_A[0];
  K_idx_1 = rtu_A[1];
  rtu_A_3 = rtu_A[2];
  rtu_A_4 = rtu_A[3];
  for (int32_T i{0}; i < 2; i++) {
    tmp = i << 1;
    rty_x_dach_0 = rtu_Pold[tmp];
    rtu_A_1 = K_idx_0 * rty_x_dach_0;
    rtu_A_2 = K_idx_1 * rty_x_dach_0;
    rty_x_dach_0 = rtu_Pold[tmp + 1];
    rtu_A_0[tmp] = rtu_A_3 * rty_x_dach_0 + rtu_A_1;
    rtu_A_0[tmp + 1] = rtu_A_4 * rty_x_dach_0 + rtu_A_2;
  }

  rty_x_dach_0 = rty_x_dach[1];
  rtu_A_3 = rty_x_dach[0];
  for (int32_T i{0}; i < 2; i++) {
    K_idx_0 = rtu_A_0[i + 2];
    K_idx_1 = rtu_A_0[i];
    P_pred[i] = (K_idx_0 * rtu_A[2] + K_idx_1 * rtu_A[0]) + rtu_Q[i];
    P_pred[i + 2] = (K_idx_0 * rtu_A[3] + K_idx_1 * rtu_A[1]) + rtu_Q[i + 2];
    x_pred[i] = (rtu_A[i + 2] * rty_x_dach_0 + rtu_A[i] * rtu_A_3) + rtu_B[i] *
      rtu_u;
  }

  K_idx_0 = rtu_C[0] * P_pred[0];
  rty_x_dach_0 = rtu_C[1] * P_pred[3];
  K_idx_1 = ((rtu_C[1] * P_pred[1] + K_idx_0) * rtu_C[0] + (rtu_C[0] * P_pred[2]
              + rty_x_dach_0) * rtu_C[1]) + rtu_R;
  K_idx_0 = (rtu_C[1] * P_pred[2] + K_idx_0) / K_idx_1;
  K_idx_1 = (rtu_C[0] * P_pred[1] + rty_x_dach_0) / K_idx_1;
  rty_x_dach_0 = rtu_y - (rtu_C[0] * x_pred[0] + rtu_C[1] * x_pred[1]);
  rty_x_dach[0] = K_idx_0 * rty_x_dach_0 + x_pred[0];
  rty_x_dach[1] = K_idx_1 * rty_x_dach_0 + x_pred[1];
  b_I[1] = 0;
  b_I[2] = 0;
  b_I[0] = 1;
  b_I[3] = 1;
  rtu_A_0[0] = K_idx_0 * rtu_C[0];
  rtu_A_0[1] = K_idx_1 * rtu_C[0];
  rtu_A_0[2] = K_idx_0 * rtu_C[1];
  rtu_A_0[3] = K_idx_1 * rtu_C[1];
  rtu_A_1 = 1.0 - rtu_A_0[0];
  rtu_A_2 = 0.0 - rtu_A_0[1];
  c_I_idx_2 = 0.0 - rtu_A_0[2];
  c_I_idx_3 = 1.0 - rtu_A_0[3];
  for (int32_T i{0}; i < 2; i++) {
    tmp = i << 1;
    rty_x_dach_0 = P_pred[tmp];
    rtu_A_3 = rtu_A_1 * rty_x_dach_0;
    rtu_A_4 = rtu_A_2 * rty_x_dach_0;
    b_I_0[tmp] = static_cast<real_T>(b_I[i]) - rtu_A_0[i];
    c_I_0[tmp] = 0.0;
    rty_x_dach_0 = P_pred[tmp + 1];
    c_I[tmp] = c_I_idx_2 * rty_x_dach_0 + rtu_A_3;
    c_I[tmp + 1] = c_I_idx_3 * rty_x_dach_0 + rtu_A_4;
    b_I_0[tmp + 1] = static_cast<real_T>(b_I[i + 2]) - rtu_A_0[i + 2];
    c_I_0[tmp + 1] = 0.0;
  }

  rtu_A_3 = c_I[0];
  rtu_A_4 = c_I[1];
  rtu_A_1 = c_I[2];
  rtu_A_2 = c_I[3];
  for (int32_T i{0}; i < 2; i++) {
    tmp = i << 1;
    rty_x_dach_0 = b_I_0[tmp];
    c_I_idx_2 = rtu_A_3 * rty_x_dach_0 + c_I_0[tmp];
    c_I_idx_3 = c_I_0[tmp + 1] + rtu_A_4 * rty_x_dach_0;
    rty_x_dach_0 = b_I_0[tmp + 1];
    c_I_0[tmp] = rtu_A_1 * rty_x_dach_0 + c_I_idx_2;
    c_I_0[tmp + 1] = rtu_A_2 * rty_x_dach_0 + c_I_idx_3;
  }

  rty_x_dach_0 = K_idx_0 * rtu_R;
  rty_P[0] = rty_x_dach_0 * K_idx_0 + c_I_0[0];
  rtu_A_3 = K_idx_1 * rtu_R;
  rty_P[1] = rtu_A_3 * K_idx_0 + c_I_0[1];
  rty_P[2] = rty_x_dach_0 * K_idx_1 + c_I_0[2];
  rty_P[3] = rtu_A_3 * K_idx_1 + c_I_0[3];
}

// Model step function
void Controller::step()
{
  real_T A[16];
  real_T A_0[9];
  real_T tmp[9];
  real_T c_data[4];
  real_T rtb_Mixer[4];
  real_T rtb_thrust[4];
  real_T rtb_u_p[4];
  real_T B_0[3];
  real_T b_idx_0;
  real_T b_idx_1;
  real_T b_idx_2;
  real_T omega_dot_idx_2;
  real_T rtb_Filter;
  real_T rtb_Integrator_o;
  real_T rtb_Mixer_0;
  real_T rtb_Sum2;
  real_T rtb_UnaryMinus;
  real_T s;
  real_T smax;
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

  // Outport: '<Root>/y_pred' incorporates:
  //   Integrator: '<S1>/Integrator'

  for (i = 0; i < 6; i++) {
    rtY.y_pred[i] = rtX.Integrator_CSTATE[i];
  }

  // End of Outport: '<Root>/y_pred'

  // Sum: '<S2>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_Filter = rtU.w[1] - rtX.Integrator_CSTATE[0];

  // Gain: '<S50>/Filter Coefficient' incorporates:
  //   Integrator: '<S42>/Filter'

  rtb_Sum2 = rtP.PIDController_N * rtX.Filter_CSTATE;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_Integrator_o = rtU.w[2] - rtX.Integrator_CSTATE[1];

  // Gain: '<S102>/Filter Coefficient' incorporates:
  //   Gain: '<S92>/Derivative Gain'
  //   Integrator: '<S94>/Filter'
  //   Sum: '<S94>/SumD'

  rtDW.FilterCoefficient = (rtP.PIDController1_D * rtb_Integrator_o -
    rtX.Filter_CSTATE_g) * rtP.PIDController1_N;

  // Sum: '<S2>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_UnaryMinus = rtU.w[3] - rtX.Integrator_CSTATE[2];

  // Gain: '<S154>/Filter Coefficient' incorporates:
  //   Gain: '<S144>/Derivative Gain'
  //   Integrator: '<S146>/Filter'
  //   Sum: '<S146>/SumD'

  rtDW.FilterCoefficient_o = (rtP.PIDController2_D * rtb_UnaryMinus -
    rtX.Filter_CSTATE_e) * rtP.PIDController2_N;

  // MATLAB Function: '<S12>/MATLAB Function' incorporates:
  //   Gain: '<S104>/Proportional Gain'
  //   Gain: '<S156>/Proportional Gain'
  //   Gain: '<S52>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S151>/Integrator'
  //   Integrator: '<S47>/Integrator'
  //   Integrator: '<S99>/Integrator'
  //   SignalConversion generated from: '<S169>/ SFunction '
  //   Sum: '<S108>/Sum'
  //   Sum: '<S160>/Sum'
  //   Sum: '<S56>/Sum'

  rtb_Mixer[0] = rtU.w[0];
  rtb_Mixer[1] = (rtP.PIDController_P * rtb_Filter + rtX.Integrator_CSTATE_c) +
    rtb_Sum2;
  rtb_Mixer[2] = (rtP.PIDController1_P * rtb_Integrator_o +
                  rtX.Integrator_CSTATE_e) + rtDW.FilterCoefficient;
  rtb_Mixer[3] = (rtP.PIDController2_P * rtb_UnaryMinus +
                  rtX.Integrator_CSTATE_i) + rtDW.FilterCoefficient_o;
  std::memcpy(&A[0], &rtP.E[0], sizeof(real_T) << 4U);
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
      smax = rtb_Mixer[i];
      rtb_Mixer[i] = rtb_Mixer[ipiv_0 - 1];
      rtb_Mixer[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (rtb_Mixer[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        rtb_Mixer[jA - 1] -= A[(jA + jj) - 1] * rtb_Mixer[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = rtb_Mixer[i];
    if (smax != 0.0) {
      rtb_Mixer[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        rtb_Mixer[jA] -= A[jA + jj] * rtb_Mixer[i];
      }
    }
  }

  rtb_u_p[0] = 0.0;
  rtb_u_p[1] = 0.0;
  rtb_u_p[2] = 0.0;
  rtb_u_p[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = rtb_Mixer[tmp_data[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_u_p[tmp_data[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S12>/Saturation'
  if (rtb_u_p[0] > rtP.Saturation_UpperSat) {
    s = rtP.Saturation_UpperSat;
  } else if (rtb_u_p[0] < rtP.Saturation_LowerSat) {
    s = rtP.Saturation_LowerSat;
  } else {
    s = rtb_u_p[0];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S12>/Saturation'

  smax = s - rtP.b;
  rtb_thrust[0] = smax * smax;

  // Saturate: '<S12>/Saturation'
  if (rtb_u_p[1] > rtP.Saturation_UpperSat) {
    s = rtP.Saturation_UpperSat;
  } else if (rtb_u_p[1] < rtP.Saturation_LowerSat) {
    s = rtP.Saturation_LowerSat;
  } else {
    s = rtb_u_p[1];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S12>/Saturation'

  smax = s - rtP.b;
  rtb_thrust[1] = smax * smax;

  // Saturate: '<S12>/Saturation'
  if (rtb_u_p[2] > rtP.Saturation_UpperSat) {
    s = rtP.Saturation_UpperSat;
  } else if (rtb_u_p[2] < rtP.Saturation_LowerSat) {
    s = rtP.Saturation_LowerSat;
  } else {
    s = rtb_u_p[2];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S12>/Saturation'

  smax = s - rtP.b;
  rtb_thrust[2] = smax * smax;

  // Saturate: '<S12>/Saturation'
  if (rtb_u_p[3] > rtP.Saturation_UpperSat) {
    s = rtP.Saturation_UpperSat;
  } else if (rtb_u_p[3] < rtP.Saturation_LowerSat) {
    s = rtP.Saturation_LowerSat;
  } else {
    s = rtb_u_p[3];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S12>/Saturation'

  smax = s - rtP.b;
  rtb_thrust[3] = smax * smax;

  // Gain: '<S1>/Mixer' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  smax = 0.0;
  omega_dot_idx_2 = 0.0;
  rtb_Mixer_0 = 0.0;
  for (jj = 0; jj < 4; jj++) {
    s = rtP.a * rtb_thrust[jj];
    i = jj << 2;
    smax += rtP.E[i + 1] * s;
    omega_dot_idx_2 += rtP.E[i + 2] * s;
    rtb_Mixer_0 += rtP.E[i + 3] * s;
  }

  // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
  //   Gain: '<S1>/Mixer'
  //   Integrator: '<S1>/Integrator'

  b_idx_0 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    s = rtX.Integrator_CSTATE[jj + 3];
    b_idx_0 += rtP.I[3 * jj] * s;
    b_idx_1 += rtP.I[3 * jj + 1] * s;
    b_idx_2 += rtP.I[3 * jj + 2] * s;
  }

  std::memcpy(&A_0[0], &rtP.I[0], 9U * sizeof(real_T));
  B_0[0] = ((rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[0]) * std::cos
             (rtX.Integrator_CSTATE[1]) * rtP.d + smax) - rtP.p *
            rtX.Integrator_CSTATE[3]) - (b_idx_2 * rtX.Integrator_CSTATE[4] -
    b_idx_1 * rtX.Integrator_CSTATE[5]);
  B_0[1] = (rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[1]) * rtP.d +
            omega_dot_idx_2) - (b_idx_0 * rtX.Integrator_CSTATE[5] - b_idx_2 *
    rtX.Integrator_CSTATE[3]);
  B_0[2] = rtb_Mixer_0 - (b_idx_1 * rtX.Integrator_CSTATE[3] - b_idx_0 *
    rtX.Integrator_CSTATE[4]);
  i = 0;
  jj = 1;
  jA = 2;
  smax = std::abs(rtP.I[0]);
  s = std::abs(rtP.I[1]);
  if (s > smax) {
    smax = s;
    i = 1;
    jj = 0;
  }

  if (std::abs(rtP.I[2]) > smax) {
    i = 2;
    jj = 1;
    jA = 0;
  }

  A_0[jj] = rtP.I[jj] / rtP.I[i];
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
  smax = B_0[jj] - B_0[i] * A_0[jj];
  omega_dot_idx_2 = ((B_0[jA] - B_0[i] * A_0[jA]) - A_0[jA + 3] * smax) / A_0[jA
    + 6];
  smax = (smax - A_0[jj + 6] * omega_dot_idx_2) / A_0[jj + 3];
  tmp[0] = 1.0;
  tmp[3] = std::sin(rtX.Integrator_CSTATE[0]) * std::tan(rtX.Integrator_CSTATE[1]);
  tmp[6] = std::cos(rtX.Integrator_CSTATE[0]) * std::tan(rtX.Integrator_CSTATE[1]);
  tmp[1] = 0.0;
  tmp[4] = std::cos(rtX.Integrator_CSTATE[0]);
  tmp[7] = -std::sin(rtX.Integrator_CSTATE[0]);
  tmp[2] = 0.0;
  tmp[5] = std::sin(rtX.Integrator_CSTATE[0]) / std::cos(rtX.Integrator_CSTATE[1]);
  tmp[8] = std::cos(rtX.Integrator_CSTATE[0]) / std::cos(rtX.Integrator_CSTATE[1]);
  rtb_Mixer_0 = 0.0;
  b_idx_0 = 0.0;
  b_idx_1 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    s = rtX.Integrator_CSTATE[jj + 3];
    rtb_Mixer_0 += tmp[3 * jj] * s;
    b_idx_0 += tmp[3 * jj + 1] * s;
    b_idx_1 += tmp[3 * jj + 2] * s;
  }

  rtDW.dx[0] = rtb_Mixer_0;
  rtDW.dx[3] = ((B_0[i] - A_0[i + 6] * omega_dot_idx_2) - A_0[i + 3] * smax) /
    A_0[i];
  rtDW.dx[1] = b_idx_0;
  rtDW.dx[4] = smax;
  rtDW.dx[2] = b_idx_1;
  rtDW.dx[5] = omega_dot_idx_2;

  // End of MATLAB Function: '<S1>/MATLAB Function2'

  // Gain: '<S148>/Integral Gain'
  rtDW.IntegralGain = rtP.PIDController2_I * rtb_UnaryMinus;

  // Gain: '<S96>/Integral Gain'
  rtDW.IntegralGain_e = rtP.PIDController1_I * rtb_Integrator_o;

  // Sum: '<S42>/SumD' incorporates:
  //   Gain: '<S40>/Derivative Gain'
  //   Integrator: '<S1>/Integrator'
  //   UnaryMinus: '<S41>/Unary Minus'

  rtDW.SumD = rtP.PIDController_D * -rtX.Integrator_CSTATE[3] - rtb_Sum2;

  // Gain: '<S44>/Integral Gain'
  rtDW.IntegralGain_j = rtP.PIDController_I * rtb_Filter;
  if ((&rtM)->isMajorTimeStep()) {
    // UnitDelay: '<S3>/Unit Delay1'
    rtDW.x_dach_n[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_n[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S3>/KF_Elevation' incorporates:
    //   Constant: '<S3>/Constant'
    //   Constant: '<S3>/Constant1'
    //   Constant: '<S3>/Constant2'
    //   Constant: '<S3>/Constant5'
    //   Constant: '<S3>/Cov Messrauschen'
    //   Constant: '<S3>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S3>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, rtU.y
                 [0], rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_n,
                 rtDW.P_o);

    // UnitDelay: '<S4>/Unit Delay1'
    rtDW.x_dach_f[0] = rtDW.UnitDelay1_DSTATE_j[0];
    rtDW.x_dach_f[1] = rtDW.UnitDelay1_DSTATE_j[1];

    // MATLAB Function: '<S4>/KF_Elevation' incorporates:
    //   Constant: '<S4>/Constant'
    //   Constant: '<S4>/Constant1'
    //   Constant: '<S4>/Constant2'
    //   Constant: '<S4>/Constant5'
    //   Constant: '<S4>/Cov Messrauschen'
    //   Constant: '<S4>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S4>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_b, rtP.Constant1_Value_p,
                 rtP.Constant2_Value_d, rtP.CovProzessrauschen_Value_l,
                 rtP.CovMessrauschen_Value_c, rtU.y[1], rtP.Constant5_Value_c,
                 rtDW.UnitDelay_DSTATE_k, rtDW.x_dach_f, rtDW.P_n);

    // UnitDelay: '<S6>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S6>/KF_Elevation' incorporates:
    //   Constant: '<S6>/Constant'
    //   Constant: '<S6>/Constant1'
    //   Constant: '<S6>/Constant2'
    //   Constant: '<S6>/Constant5'
    //   Constant: '<S6>/Cov Messrauschen'
    //   Constant: '<S6>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S6>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_e, rtP.Constant1_Value_n,
                 rtP.Constant2_Value_g, rtP.CovProzessrauschen_Value_p,
                 rtP.CovMessrauschen_Value_n, rtU.y[2], rtP.Constant5_Value_d,
                 rtDW.UnitDelay_DSTATE_m, rtDW.x_dach, rtDW.P_p);
  }

  // Sum: '<S5>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Filter = rtU.w[1] - rtU.y[0];

  // Gain: '<S213>/Filter Coefficient' incorporates:
  //   Integrator: '<S205>/Filter'

  rtb_Integrator_o = rtP.PIDController_N_o * rtX.Filter_CSTATE_b;

  // Sum: '<S5>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_UnaryMinus = rtU.w[2] - rtU.y[1];

  // Gain: '<S265>/Filter Coefficient' incorporates:
  //   Gain: '<S255>/Derivative Gain'
  //   Integrator: '<S257>/Filter'
  //   Sum: '<S257>/SumD'

  rtDW.FilterCoefficient_b = (rtP.PIDController1_D_k * rtb_UnaryMinus -
    rtX.Filter_CSTATE_m) * rtP.PIDController1_N_l;

  // Sum: '<S5>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtU.w[3] - rtU.y[2];

  // Gain: '<S317>/Filter Coefficient' incorporates:
  //   Gain: '<S307>/Derivative Gain'
  //   Integrator: '<S309>/Filter'
  //   Sum: '<S309>/SumD'

  rtDW.FilterCoefficient_a = (rtP.PIDController2_D_m * rtb_Sum2 -
    rtX.Filter_CSTATE_c) * rtP.PIDController2_N_b;

  // MATLAB Function: '<S175>/MATLAB Function' incorporates:
  //   Gain: '<S215>/Proportional Gain'
  //   Gain: '<S267>/Proportional Gain'
  //   Gain: '<S319>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S210>/Integrator'
  //   Integrator: '<S262>/Integrator'
  //   Integrator: '<S314>/Integrator'
  //   MATLAB Function: '<S12>/MATLAB Function'
  //   SignalConversion generated from: '<S332>/ SFunction '
  //   Sum: '<S219>/Sum'
  //   Sum: '<S271>/Sum'
  //   Sum: '<S323>/Sum'

  rtb_Mixer[0] = rtU.w[0];
  rtb_Mixer[1] = (rtP.PIDController_P_f * rtb_Filter + rtX.Integrator_CSTATE_p)
    + rtb_Integrator_o;
  rtb_Mixer[2] = (rtP.PIDController1_P_k * rtb_UnaryMinus +
                  rtX.Integrator_CSTATE_iz) + rtDW.FilterCoefficient_b;
  rtb_Mixer[3] = (rtP.PIDController2_P_n * rtb_Sum2 + rtX.Integrator_CSTATE_j) +
    rtDW.FilterCoefficient_a;
  std::memcpy(&A[0], &rtP.E[0], sizeof(real_T) << 4U);
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
      smax = rtb_Mixer[i];
      rtb_Mixer[i] = rtb_Mixer[ipiv_0 - 1];
      rtb_Mixer[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (rtb_Mixer[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        rtb_Mixer[jA - 1] -= A[(jA + jj) - 1] * rtb_Mixer[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = rtb_Mixer[i];
    if (smax != 0.0) {
      rtb_Mixer[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        rtb_Mixer[jA] -= A[jA + jj] * rtb_Mixer[i];
      }
    }
  }

  rtb_thrust[0] = 0.0;
  rtb_thrust[1] = 0.0;
  rtb_thrust[2] = 0.0;
  rtb_thrust[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = rtb_Mixer[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S175>/Saturation' incorporates:
  //   MATLAB Function: '<S175>/MATLAB Function'

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

  // End of Saturate: '<S175>/Saturation'

  // Outport: '<Root>/values' incorporates:
  //   Integrator: '<Root>/Integrator'

  rtY.values[0] = rtX.Integrator_CSTATE_pz[0];
  rtY.values[1] = rtX.Integrator_CSTATE_pz[1];
  rtY.values[2] = rtX.Integrator_CSTATE_pz[2];
  rtY.values[3] = rtDW.x_dach_n[1];
  rtY.values[4] = rtDW.x_dach_f[1];
  rtY.values[5] = rtDW.x_dach[1];

  // SignalConversion generated from: '<Root>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_n[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_f[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach[1];

  // Gain: '<S311>/Integral Gain'
  rtDW.IntegralGain_p = rtP.PIDController2_I_i * rtb_Sum2;

  // Gain: '<S259>/Integral Gain'
  rtDW.IntegralGain_o = rtP.PIDController1_I_m * rtb_UnaryMinus;

  // Sum: '<S205>/SumD' incorporates:
  //   Gain: '<S203>/Derivative Gain'
  //   UnaryMinus: '<S204>/Unary Minus'

  rtDW.SumD_p = rtP.PIDController_D_c * -rtDW.x_dach_n[1] - rtb_Integrator_o;

  // Gain: '<S207>/Integral Gain'
  rtDW.IntegralGain_od = rtP.PIDController_I_a * rtb_Filter;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S3>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_n[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_n[1];

      // Update for UnitDelay: '<S3>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_o[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_o[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_o[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_o[3];

      // Update for UnitDelay: '<S4>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_j[0] = rtDW.x_dach_f[0];
      rtDW.UnitDelay1_DSTATE_j[1] = rtDW.x_dach_f[1];

      // Update for UnitDelay: '<S4>/Unit Delay'
      rtDW.UnitDelay_DSTATE_k[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_k[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_k[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_k[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S6>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S6>/Unit Delay'
      rtDW.UnitDelay_DSTATE_m[0] = rtDW.P_p[0];
      rtDW.UnitDelay_DSTATE_m[1] = rtDW.P_p[1];
      rtDW.UnitDelay_DSTATE_m[2] = rtDW.P_p[2];
      rtDW.UnitDelay_DSTATE_m[3] = rtDW.P_p[3];
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
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S1>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S1>/Integrator'

  // Derivatives for Integrator: '<S47>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_j;

  // Derivatives for Integrator: '<S42>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD;

  // Derivatives for Integrator: '<S99>/Integrator'
  _rtXdot->Integrator_CSTATE_e = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S94>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S151>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S146>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.FilterCoefficient_o;

  // Derivatives for Integrator: '<S210>/Integrator'
  _rtXdot->Integrator_CSTATE_p = rtDW.IntegralGain_od;

  // Derivatives for Integrator: '<S205>/Filter'
  _rtXdot->Filter_CSTATE_b = rtDW.SumD_p;

  // Derivatives for Integrator: '<S262>/Integrator'
  _rtXdot->Integrator_CSTATE_iz = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S257>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_b;

  // Derivatives for Integrator: '<S314>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S309>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.FilterCoefficient_a;

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE_pz[0] = rtDW.TmpSignalConversionAtIntegrator[0];
  _rtXdot->Integrator_CSTATE_pz[1] = rtDW.TmpSignalConversionAtIntegrator[1];
  _rtXdot->Integrator_CSTATE_pz[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S3>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_n[1];

  // Derivatives for Integrator: '<S4>/Integrator1'
  _rtXdot->Integrator1_CSTATE_o = rtDW.x_dach_f[1];

  // Derivatives for Integrator: '<S6>/Integrator1'
  _rtXdot->Integrator1_CSTATE_g = rtDW.x_dach[1];
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
  (&rtM)->Timing.stepSize0 = 0.005;

  {
    int32_T i;

    // InitializeConditions for Integrator: '<S1>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC;
    }

    // End of InitializeConditions for Integrator: '<S1>/Integrator'

    // InitializeConditions for Integrator: '<S47>/Integrator'
    rtX.Integrator_CSTATE_c = rtP.PIDController_InitialConditio_l;

    // InitializeConditions for Integrator: '<S42>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S99>/Integrator'
    rtX.Integrator_CSTATE_e = rtP.PIDController1_InitialConditi_d;

    // InitializeConditions for Integrator: '<S94>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S151>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController2_InitialConditi_n;

    // InitializeConditions for Integrator: '<S146>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController2_InitialCondition;

    // InitializeConditions for UnitDelay: '<S3>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S3>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S4>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_j[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_j[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S4>/Unit Delay'
    rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_p[0];
    rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_p[1];
    rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_p[2];
    rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_p[3];

    // InitializeConditions for UnitDelay: '<S6>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_i[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_i[1];

    // InitializeConditions for UnitDelay: '<S6>/Unit Delay'
    rtDW.UnitDelay_DSTATE_m[0] = rtP.UnitDelay_InitialCondition_m[0];
    rtDW.UnitDelay_DSTATE_m[1] = rtP.UnitDelay_InitialCondition_m[1];
    rtDW.UnitDelay_DSTATE_m[2] = rtP.UnitDelay_InitialCondition_m[2];
    rtDW.UnitDelay_DSTATE_m[3] = rtP.UnitDelay_InitialCondition_m[3];

    // InitializeConditions for Integrator: '<S210>/Integrator'
    rtX.Integrator_CSTATE_p = rtP.PIDController_InitialConditio_d;

    // InitializeConditions for Integrator: '<S205>/Filter'
    rtX.Filter_CSTATE_b = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S262>/Integrator'
    rtX.Integrator_CSTATE_iz = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S257>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S314>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController2_InitialConditi_o;

    // InitializeConditions for Integrator: '<S309>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_e;

    // InitializeConditions for Integrator: '<Root>/Integrator'
    rtX.Integrator_CSTATE_pz[0] = rtP.Integrator_IC_c;
    rtX.Integrator_CSTATE_pz[1] = rtP.Integrator_IC_c;
    rtX.Integrator_CSTATE_pz[2] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S3>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S4>/Integrator1'
    rtX.Integrator1_CSTATE_o = rtP.Integrator1_IC_n;

    // InitializeConditions for Integrator: '<S6>/Integrator1'
    rtX.Integrator1_CSTATE_g = rtP.Integrator1_IC_e;
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
