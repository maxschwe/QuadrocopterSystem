//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.466
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Mar  3 13:28:30 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof_container.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>

// private model entry point functions
extern void controller_3dof_container_derivatives();

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
  int_T nXc { 42 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  controller_3dof_container_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

//
// Output and update for atomic system:
//    '<S7>/KF_Elevation'
//    '<S8>/KF_Elevation'
//    '<S10>/KF_Elevation'
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
  real_T b_a[16];
  real_T A_0[9];
  real_T tmp_0[9];
  real_T c_data[4];
  real_T rtb_Mixer[4];
  real_T rtb_thrust[4];
  real_T rtb_u_e[4];
  real_T B_0[3];
  real_T b_idx_1;
  real_T b_idx_2;
  real_T omega_dot_idx_2;
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_gy;
  real_T rtb_FilterCoefficient_o;
  real_T rtb_Mixer_0;
  real_T rtb_Mixer_1;
  real_T rtb_Sum_l;
  real_T rtb_UnaryMinus;
  real_T rtb_UnaryMinus_a;
  real_T s;
  real_T smax;
  int32_T d_k;
  int32_T i;
  int32_T ijA;
  int32_T jBcol;
  int32_T jj;
  int32_T kAcol;
  int32_T pipk;
  int8_T ipiv[4];
  int8_T p[4];
  int8_T tmp_data[4];
  int8_T tmp_data_0[4];
  boolean_T tmp;
  if ((&rtM)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&rtM)->isMinorTimeStep()) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // Outport: '<Root>/x_pred' incorporates:
  //   Integrator: '<S1>/Integrator'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i] = rtX.Integrator_CSTATE[i];
  }

  // End of Outport: '<Root>/x_pred'
  tmp = ((&rtM)->isMajorTimeStep());
  if (tmp) {
    // UnitDelay: '<S7>/Unit Delay1'
    rtDW.x_dach_d[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_d[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S7>/KF_Elevation' incorporates:
    //   Constant: '<S7>/Constant'
    //   Constant: '<S7>/Constant1'
    //   Constant: '<S7>/Constant2'
    //   Constant: '<S7>/Constant5'
    //   Constant: '<S7>/Cov Messrauschen'
    //   Constant: '<S7>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S7>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value,
                 rtX.Integrator_CSTATE[0], rtP.Constant5_Value,
                 rtDW.UnitDelay_DSTATE, rtDW.x_dach_d, rtDW.P_dr);
  }

  // Sum: '<S9>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtb_FilterCoefficient = rtU.w[1] - rtDW.x_dach_d[0];

  // Gain: '<S55>/Filter Coefficient' incorporates:
  //   Integrator: '<S47>/Filter'

  rtb_FilterCoefficient_gy = rtP.ke * rtX.Filter_CSTATE;
  if (tmp) {
    // UnitDelay: '<S8>/Unit Delay1'
    rtDW.x_dach_j[0] = rtDW.UnitDelay1_DSTATE_f[0];
    rtDW.x_dach_j[1] = rtDW.UnitDelay1_DSTATE_f[1];

    // MATLAB Function: '<S8>/KF_Elevation' incorporates:
    //   Constant: '<S8>/Constant'
    //   Constant: '<S8>/Constant1'
    //   Constant: '<S8>/Constant2'
    //   Constant: '<S8>/Constant5'
    //   Constant: '<S8>/Cov Messrauschen'
    //   Constant: '<S8>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S8>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_j, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_a, rtP.CovProzessrauschen_Value_o,
                 rtP.CovMessrauschen_Value_e, rtX.Integrator_CSTATE[1],
                 rtP.Constant5_Value_i, rtDW.UnitDelay_DSTATE_i, rtDW.x_dach_j,
                 rtDW.P_nu);
  }

  // Sum: '<S9>/Sum1' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus = rtU.w[2] - rtDW.x_dach_j[0];

  // Gain: '<S107>/Filter Coefficient' incorporates:
  //   Integrator: '<S99>/Filter'

  rtb_FilterCoefficient_o = rtP.ke * rtX.Filter_CSTATE_e;
  if (tmp) {
    // UnitDelay: '<S10>/Unit Delay1'
    rtDW.x_dach_a[0] = rtDW.UnitDelay1_DSTATE_a[0];
    rtDW.x_dach_a[1] = rtDW.UnitDelay1_DSTATE_a[1];

    // MATLAB Function: '<S10>/KF_Elevation' incorporates:
    //   Constant: '<S10>/Constant'
    //   Constant: '<S10>/Constant1'
    //   Constant: '<S10>/Constant2'
    //   Constant: '<S10>/Constant5'
    //   Constant: '<S10>/Cov Messrauschen'
    //   Constant: '<S10>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S10>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a, rtP.Constant1_Value_i,
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE[2],
                 rtP.Constant5_Value_k, rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_a,
                 rtDW.P_j);
  }

  // Sum: '<S9>/Sum2' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus_a = rtU.w[3] - rtDW.x_dach_a[0];

  // Gain: '<S159>/Filter Coefficient' incorporates:
  //   Integrator: '<S151>/Filter'

  rtb_Sum_l = rtP.ke * rtX.Filter_CSTATE_j;

  // MATLAB Function: '<S6>/MATLAB Function'
  for (pipk = 0; pipk < 16; pipk++) {
    A[pipk] = rtP.E[pipk];
    b_a[pipk] = 0.0;
  }

  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (pipk = 0; pipk < 3; pipk++) {
    jj = pipk * 5;
    i = 5 - pipk;
    jBcol = 0;
    smax = std::abs(A[jj]);
    for (d_k = 2; d_k < i; d_k++) {
      s = std::abs(A[(jj + d_k) - 1]);
      if (s > smax) {
        jBcol = d_k - 1;
        smax = s;
      }
    }

    if (A[jj + jBcol] != 0.0) {
      if (jBcol != 0) {
        i = pipk + jBcol;
        ipiv[pipk] = static_cast<int8_T>(i + 1);
        smax = A[pipk];
        A[pipk] = A[i];
        A[i] = smax;
        smax = A[pipk + 4];
        A[pipk + 4] = A[i + 4];
        A[i + 4] = smax;
        smax = A[pipk + 8];
        A[pipk + 8] = A[i + 8];
        A[i + 8] = smax;
        smax = A[pipk + 12];
        A[pipk + 12] = A[i + 12];
        A[i + 12] = smax;
      }

      i = (jj - pipk) + 4;
      for (jBcol = jj + 2; jBcol <= i; jBcol++) {
        A[jBcol - 1] /= A[jj];
      }
    }

    i = jj + 6;
    jBcol = 2 - pipk;
    for (d_k = 0; d_k <= jBcol; d_k++) {
      smax = A[((d_k << 2) + jj) + 4];
      if (smax != 0.0) {
        kAcol = (i - pipk) + 2;
        for (ijA = i; ijA <= kAcol; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - i) + 1] * -smax;
        }
      }

      i += 4;
    }
  }

  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  if (ipiv[0] > 1) {
    pipk = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = 1;
    p[0] = static_cast<int8_T>(pipk);
  }

  if (ipiv[1] > 2) {
    pipk = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = static_cast<int8_T>(pipk);
  }

  if (ipiv[2] > 3) {
    pipk = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = static_cast<int8_T>(pipk);
  }

  for (jBcol = 0; jBcol < 4; jBcol++) {
    jj = (p[jBcol] - 1) << 2;
    b_a[jBcol + jj] = 1.0;
    for (d_k = jBcol + 1; d_k < 5; d_k++) {
      pipk = (jj + d_k) - 1;
      if (b_a[pipk] != 0.0) {
        for (i = d_k + 1; i < 5; i++) {
          kAcol = (jj + i) - 1;
          b_a[kAcol] -= A[(((d_k - 1) << 2) + i) - 1] * b_a[pipk];
        }
      }
    }
  }

  // SignalConversion generated from: '<S12>/ SFunction ' incorporates:
  //   Gain: '<S109>/Proportional Gain'
  //   Gain: '<S161>/Proportional Gain'
  //   Gain: '<S57>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S104>/Integrator'
  //   Integrator: '<S156>/Integrator'
  //   Integrator: '<S52>/Integrator'
  //   MATLAB Function: '<S6>/MATLAB Function'
  //   Sum: '<S113>/Sum'
  //   Sum: '<S165>/Sum'
  //   Sum: '<S61>/Sum'

  rtb_Mixer[0] = rtU.w[0];
  rtb_Mixer[1] = (rtP.kp_roll * rtb_FilterCoefficient + rtX.Integrator_CSTATE_j)
    + rtb_FilterCoefficient_gy;
  rtb_Mixer[2] = (rtP.kp_pitch * rtb_UnaryMinus + rtX.Integrator_CSTATE_c) +
    rtb_FilterCoefficient_o;
  rtb_Mixer[3] = (rtP.kp_yaw * rtb_UnaryMinus_a + rtX.Integrator_CSTATE_o) +
    rtb_Sum_l;

  // MATLAB Function: '<S6>/MATLAB Function'
  for (i = 0; i < 4; i++) {
    jBcol = i << 2;
    for (d_k = 3; d_k >= 0; d_k--) {
      kAcol = d_k << 2;
      pipk = d_k + jBcol;
      smax = b_a[pipk];
      if (smax != 0.0) {
        b_a[pipk] = smax / A[d_k + kAcol];
        for (ijA = 0; ijA < d_k; ijA++) {
          jj = ijA + jBcol;
          b_a[jj] -= A[ijA + kAcol] * b_a[pipk];
        }
      }
    }
  }

  s = 0.0;
  omega_dot_idx_2 = 0.0;
  rtb_Mixer_0 = 0.0;
  rtb_Mixer_1 = 0.0;
  for (i = 0; i < 4; i++) {
    smax = rtb_Mixer[i];
    jj = i << 2;
    s += b_a[jj] * smax;
    omega_dot_idx_2 += b_a[jj + 1] * smax;
    rtb_Mixer_0 += b_a[jj + 2] * smax;
    rtb_Mixer_1 += b_a[jj + 3] * smax;
    rtb_u_e[i] = 0.0;
  }

  rtb_Mixer[3] = rtb_Mixer_1;
  rtb_Mixer[2] = rtb_Mixer_0;
  rtb_Mixer[1] = omega_dot_idx_2;
  rtb_Mixer[0] = s;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      pipk++;
    }
  }

  jBcol = pipk;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      tmp_data[pipk] = static_cast<int8_T>(i);
      pipk++;
    }
  }

  for (jj = 0; jj < jBcol; jj++) {
    c_data[jj] = rtb_Mixer[tmp_data[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_u_e[tmp_data[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S6>/Saturation'
  if (rtb_u_e[0] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[0] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[0];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S6>/Saturation'

  s = smax - rtP.b;
  rtb_thrust[0] = s * s;

  // Saturate: '<S6>/Saturation'
  if (rtb_u_e[1] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[1] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[1];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S6>/Saturation'

  s = smax - rtP.b;
  rtb_thrust[1] = s * s;

  // Saturate: '<S6>/Saturation'
  if (rtb_u_e[2] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[2] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[2];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S6>/Saturation'

  s = smax - rtP.b;
  rtb_thrust[2] = s * s;

  // Saturate: '<S6>/Saturation'
  if (rtb_u_e[3] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[3] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[3];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S6>/Saturation'

  s = smax - rtP.b;
  rtb_thrust[3] = s * s;

  // Gain: '<S1>/Mixer' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  s = 0.0;
  omega_dot_idx_2 = 0.0;
  rtb_Mixer_0 = 0.0;
  for (pipk = 0; pipk < 4; pipk++) {
    smax = rtP.a * rtb_thrust[pipk];
    jj = pipk << 2;
    s += rtP.E[jj + 1] * smax;
    omega_dot_idx_2 += rtP.E[jj + 2] * smax;
    rtb_Mixer_0 += rtP.E[jj + 3] * smax;
  }

  // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
  //   Gain: '<S1>/Mixer'
  //   Integrator: '<S1>/Integrator'

  rtb_Mixer_1 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (pipk = 0; pipk < 3; pipk++) {
    smax = rtX.Integrator_CSTATE[pipk + 3];
    rtb_Mixer_1 += rtP.I[3 * pipk] * smax;
    b_idx_1 += rtP.I[3 * pipk + 1] * smax;
    b_idx_2 += rtP.I[3 * pipk + 2] * smax;
  }

  std::memcpy(&A_0[0], &rtP.I[0], 9U * sizeof(real_T));
  B_0[0] = ((rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[0]) * std::cos
             (rtX.Integrator_CSTATE[1]) * rtP.d + s) + -rtP.p *
            rtX.Integrator_CSTATE[3]) - (b_idx_2 * rtX.Integrator_CSTATE[4] -
    b_idx_1 * rtX.Integrator_CSTATE[5]);
  B_0[1] = ((rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[1]) * rtP.d +
             omega_dot_idx_2) + -rtP.p * rtX.Integrator_CSTATE[4]) -
    (rtb_Mixer_1 * rtX.Integrator_CSTATE[5] - b_idx_2 * rtX.Integrator_CSTATE[3]);
  B_0[2] = (-rtP.p * rtX.Integrator_CSTATE[5] + rtb_Mixer_0) - (b_idx_1 *
    rtX.Integrator_CSTATE[3] - rtb_Mixer_1 * rtX.Integrator_CSTATE[4]);
  jj = 0;
  pipk = 1;
  i = 2;
  smax = std::abs(rtP.I[0]);
  s = std::abs(rtP.I[1]);
  if (s > smax) {
    smax = s;
    jj = 1;
    pipk = 0;
  }

  if (std::abs(rtP.I[2]) > smax) {
    jj = 2;
    pipk = 1;
    i = 0;
  }

  A_0[pipk] = rtP.I[pipk] / rtP.I[jj];
  A_0[i] /= A_0[jj];
  A_0[pipk + 3] -= A_0[jj + 3] * A_0[pipk];
  A_0[i + 3] -= A_0[jj + 3] * A_0[i];
  A_0[pipk + 6] -= A_0[jj + 6] * A_0[pipk];
  A_0[i + 6] -= A_0[jj + 6] * A_0[i];
  if (std::abs(A_0[i + 3]) > std::abs(A_0[pipk + 3])) {
    jBcol = pipk;
    pipk = i;
    i = jBcol;
  }

  A_0[i + 3] /= A_0[pipk + 3];
  A_0[i + 6] -= A_0[i + 3] * A_0[pipk + 6];
  s = B_0[pipk] - B_0[jj] * A_0[pipk];
  omega_dot_idx_2 = ((B_0[i] - B_0[jj] * A_0[i]) - A_0[i + 3] * s) / A_0[i + 6];
  s = (s - A_0[pipk + 6] * omega_dot_idx_2) / A_0[pipk + 3];
  tmp_0[0] = 1.0;
  tmp_0[3] = std::sin(rtX.Integrator_CSTATE[0]) * std::tan
    (rtX.Integrator_CSTATE[1]);
  tmp_0[6] = std::cos(rtX.Integrator_CSTATE[0]) * std::tan
    (rtX.Integrator_CSTATE[1]);
  tmp_0[1] = 0.0;
  tmp_0[4] = std::cos(rtX.Integrator_CSTATE[0]);
  tmp_0[7] = -std::sin(rtX.Integrator_CSTATE[0]);
  tmp_0[2] = 0.0;
  tmp_0[5] = std::sin(rtX.Integrator_CSTATE[0]) / std::cos
    (rtX.Integrator_CSTATE[1]);
  tmp_0[8] = std::cos(rtX.Integrator_CSTATE[0]) / std::cos
    (rtX.Integrator_CSTATE[1]);
  rtb_Mixer_0 = 0.0;
  rtb_Mixer_1 = 0.0;
  b_idx_1 = 0.0;
  for (pipk = 0; pipk < 3; pipk++) {
    smax = rtX.Integrator_CSTATE[pipk + 3];
    rtb_Mixer_0 += tmp_0[3 * pipk] * smax;
    rtb_Mixer_1 += tmp_0[3 * pipk + 1] * smax;
    b_idx_1 += tmp_0[3 * pipk + 2] * smax;
  }

  // SignalConversion generated from: '<S2>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_d[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_j[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach_a[1];

  // Sum: '<S151>/SumD' incorporates:
  //   Gain: '<S149>/Derivative Gain'
  //   UnaryMinus: '<S150>/Unary Minus'

  rtDW.SumD = rtP.kd_yaw * -rtDW.x_dach_a[1] - rtb_Sum_l;

  // Gain: '<S153>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_yaw * rtb_UnaryMinus_a;

  // Sum: '<S99>/SumD' incorporates:
  //   Gain: '<S97>/Derivative Gain'
  //   UnaryMinus: '<S98>/Unary Minus'

  rtDW.SumD_k = rtP.kd_pitch * -rtDW.x_dach_j[1] - rtb_FilterCoefficient_o;

  // Gain: '<S101>/Integral Gain'
  rtDW.IntegralGain_d = rtP.ki_pitch * rtb_UnaryMinus;

  // Sum: '<S47>/SumD' incorporates:
  //   Gain: '<S45>/Derivative Gain'
  //   UnaryMinus: '<S46>/Unary Minus'

  rtDW.SumD_p = rtP.kd_roll * -rtDW.x_dach_d[1] - rtb_FilterCoefficient_gy;

  // Gain: '<S49>/Integral Gain'
  rtDW.IntegralGain_i = rtP.ki_roll * rtb_FilterCoefficient;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[0] = rtb_Mixer_0;
  rtDW.dx[3] = ((B_0[jj] - A_0[jj + 6] * omega_dot_idx_2) - A_0[jj + 3] * s) /
    A_0[jj];

  // Sum: '<S11>/Sum' incorporates:
  //   SignalConversion generated from: '<S11>/Gain1'

  rtDW.Sum[0] = 0.0;

  // Sum: '<S180>/Sum' incorporates:
  //   SignalConversion generated from: '<S180>/Gain1'

  rtDW.Sum_d[0] = 0.0;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[1] = rtb_Mixer_1;
  rtDW.dx[4] = s;

  // Sum: '<S11>/Sum' incorporates:
  //   SignalConversion generated from: '<S11>/Gain1'

  rtDW.Sum[1] = 0.0;

  // Sum: '<S180>/Sum' incorporates:
  //   SignalConversion generated from: '<S180>/Gain1'

  rtDW.Sum_d[1] = 0.0;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[2] = b_idx_1;
  rtDW.dx[5] = omega_dot_idx_2;

  // Sum: '<S11>/Sum' incorporates:
  //   SignalConversion generated from: '<S11>/Gain1'

  rtDW.Sum[2] = 0.0;

  // Sum: '<S180>/Sum' incorporates:
  //   SignalConversion generated from: '<S180>/Gain1'

  rtDW.Sum_d[2] = 0.0;
  if (tmp) {
    // UnitDelay: '<S176>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_b[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_b[1];

    // MATLAB Function: '<S176>/KF_Elevation' incorporates:
    //   Constant: '<S176>/Constant'
    //   Constant: '<S176>/Constant1'
    //   Constant: '<S176>/Constant2'
    //   Constant: '<S176>/Constant5'
    //   Constant: '<S176>/Cov Messrauschen'
    //   Constant: '<S176>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S176>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_p,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_h3,
                 rtP.CovMessrauschen_Value_j, rtU.y[0], rtP.Constant5_Value_d,
                 rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_g, rtDW.P_n);

    // UnitDelay: '<S177>/Unit Delay1'
    rtDW.x_dach_n[0] = rtDW.UnitDelay1_DSTATE_b4[0];
    rtDW.x_dach_n[1] = rtDW.UnitDelay1_DSTATE_b4[1];

    // MATLAB Function: '<S177>/KF_Elevation' incorporates:
    //   Constant: '<S177>/Constant'
    //   Constant: '<S177>/Constant1'
    //   Constant: '<S177>/Constant2'
    //   Constant: '<S177>/Constant5'
    //   Constant: '<S177>/Cov Messrauschen'
    //   Constant: '<S177>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S177>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_i, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_ph, rtP.CovProzessrauschen_Value_d,
                 rtP.CovMessrauschen_Value_i, rtU.y[1], rtP.Constant5_Value_b,
                 rtDW.UnitDelay_DSTATE_g, rtDW.x_dach_n, rtDW.P_d);

    // UnitDelay: '<S179>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_n[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_n[1];

    // MATLAB Function: '<S179>/KF_Elevation' incorporates:
    //   Constant: '<S179>/Constant'
    //   Constant: '<S179>/Constant1'
    //   Constant: '<S179>/Constant2'
    //   Constant: '<S179>/Constant5'
    //   Constant: '<S179>/Cov Messrauschen'
    //   Constant: '<S179>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S179>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_d,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_i,
                 rtP.CovMessrauschen_Value_o, rtU.y[2], rtP.Constant5_Value_bx,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach, rtDW.P_h);
  }

  // Sum: '<S178>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtb_Sum_l = rtU.w[1] - rtDW.x_dach_g[0];

  // Gain: '<S224>/Filter Coefficient' incorporates:
  //   Integrator: '<S216>/Filter'

  rtb_FilterCoefficient_o = rtP.ke * rtX.Filter_CSTATE_n;

  // Sum: '<S178>/Sum1' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus = rtU.w[2] - rtDW.x_dach_n[0];

  // Gain: '<S276>/Filter Coefficient' incorporates:
  //   Integrator: '<S268>/Filter'

  rtb_FilterCoefficient_gy = rtP.ke * rtX.Filter_CSTATE_i;

  // Sum: '<S178>/Sum2' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus_a = rtU.w[3] - rtDW.x_dach[0];

  // Gain: '<S328>/Filter Coefficient' incorporates:
  //   Integrator: '<S320>/Filter'

  rtb_FilterCoefficient = rtP.ke * rtX.Filter_CSTATE_c;

  // MATLAB Function: '<S175>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S6>/MATLAB Function'

  for (pipk = 0; pipk < 16; pipk++) {
    A[pipk] = rtP.E[pipk];
    b_a[pipk] = 0.0;
  }

  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  for (pipk = 0; pipk < 3; pipk++) {
    jj = pipk * 5;
    i = 5 - pipk;
    jBcol = 0;
    smax = std::abs(A[jj]);
    for (d_k = 2; d_k < i; d_k++) {
      s = std::abs(A[(jj + d_k) - 1]);
      if (s > smax) {
        jBcol = d_k - 1;
        smax = s;
      }
    }

    if (A[jj + jBcol] != 0.0) {
      if (jBcol != 0) {
        i = pipk + jBcol;
        ipiv[pipk] = static_cast<int8_T>(i + 1);
        smax = A[pipk];
        A[pipk] = A[i];
        A[i] = smax;
        smax = A[pipk + 4];
        A[pipk + 4] = A[i + 4];
        A[i + 4] = smax;
        smax = A[pipk + 8];
        A[pipk + 8] = A[i + 8];
        A[i + 8] = smax;
        smax = A[pipk + 12];
        A[pipk + 12] = A[i + 12];
        A[i + 12] = smax;
      }

      i = (jj - pipk) + 4;
      for (jBcol = jj + 2; jBcol <= i; jBcol++) {
        A[jBcol - 1] /= A[jj];
      }
    }

    i = jj + 6;
    jBcol = 2 - pipk;
    for (d_k = 0; d_k <= jBcol; d_k++) {
      smax = A[((d_k << 2) + jj) + 4];
      if (smax != 0.0) {
        kAcol = (i - pipk) + 2;
        for (ijA = i; ijA <= kAcol; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - i) + 1] * -smax;
        }
      }

      i += 4;
    }
  }

  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  p[3] = 4;
  if (ipiv[0] > 1) {
    pipk = p[ipiv[0] - 1];
    p[ipiv[0] - 1] = 1;
    p[0] = static_cast<int8_T>(pipk);
  }

  if (ipiv[1] > 2) {
    pipk = p[ipiv[1] - 1];
    p[ipiv[1] - 1] = p[1];
    p[1] = static_cast<int8_T>(pipk);
  }

  if (ipiv[2] > 3) {
    pipk = p[ipiv[2] - 1];
    p[ipiv[2] - 1] = p[2];
    p[2] = static_cast<int8_T>(pipk);
  }

  for (jBcol = 0; jBcol < 4; jBcol++) {
    jj = (p[jBcol] - 1) << 2;
    b_a[jBcol + jj] = 1.0;
    for (d_k = jBcol + 1; d_k < 5; d_k++) {
      pipk = (jj + d_k) - 1;
      if (b_a[pipk] != 0.0) {
        for (i = d_k + 1; i < 5; i++) {
          kAcol = (jj + i) - 1;
          b_a[kAcol] -= A[(((d_k - 1) << 2) + i) - 1] * b_a[pipk];
        }
      }
    }
  }

  // SignalConversion generated from: '<S181>/ SFunction ' incorporates:
  //   Gain: '<S226>/Proportional Gain'
  //   Gain: '<S278>/Proportional Gain'
  //   Gain: '<S330>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S221>/Integrator'
  //   Integrator: '<S273>/Integrator'
  //   Integrator: '<S325>/Integrator'
  //   MATLAB Function: '<S175>/MATLAB Function'
  //   Sum: '<S230>/Sum'
  //   Sum: '<S282>/Sum'
  //   Sum: '<S334>/Sum'

  rtb_Mixer[0] = rtU.w[0];
  rtb_Mixer[1] = (rtP.kp_roll * rtb_Sum_l + rtX.Integrator_CSTATE_l) +
    rtb_FilterCoefficient_o;
  rtb_Mixer[2] = (rtP.kp_pitch * rtb_UnaryMinus + rtX.Integrator_CSTATE_ja) +
    rtb_FilterCoefficient_gy;
  rtb_Mixer[3] = (rtP.kp_yaw * rtb_UnaryMinus_a + rtX.Integrator_CSTATE_iq) +
    rtb_FilterCoefficient;

  // MATLAB Function: '<S175>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S6>/MATLAB Function'

  for (i = 0; i < 4; i++) {
    jBcol = i << 2;
    for (d_k = 3; d_k >= 0; d_k--) {
      kAcol = d_k << 2;
      pipk = d_k + jBcol;
      smax = b_a[pipk];
      if (smax != 0.0) {
        b_a[pipk] = smax / A[d_k + kAcol];
        for (ijA = 0; ijA < d_k; ijA++) {
          jj = ijA + jBcol;
          b_a[jj] -= A[ijA + kAcol] * b_a[pipk];
        }
      }
    }
  }

  s = 0.0;
  omega_dot_idx_2 = 0.0;
  rtb_Mixer_0 = 0.0;
  rtb_Mixer_1 = 0.0;
  for (i = 0; i < 4; i++) {
    smax = rtb_Mixer[i];
    jj = i << 2;
    s += b_a[jj] * smax;
    omega_dot_idx_2 += b_a[jj + 1] * smax;
    rtb_Mixer_0 += b_a[jj + 2] * smax;
    rtb_Mixer_1 += b_a[jj + 3] * smax;
    rtb_thrust[i] = 0.0;
  }

  rtb_Mixer[3] = rtb_Mixer_1;
  rtb_Mixer[2] = rtb_Mixer_0;
  rtb_Mixer[1] = omega_dot_idx_2;
  rtb_Mixer[0] = s;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      pipk++;
    }
  }

  jBcol = pipk;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_Mixer[i] / rtP.a >= 0.0) {
      tmp_data_0[pipk] = static_cast<int8_T>(i);
      pipk++;
    }
  }

  for (jj = 0; jj < jBcol; jj++) {
    c_data[jj] = rtb_Mixer[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S175>/Saturation' incorporates:
  //   MATLAB Function: '<S175>/MATLAB Function'

  if (rtb_thrust[0] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[0] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_thrust[0];
  }

  if (rtb_thrust[1] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[1] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_thrust[1];
  }

  if (rtb_thrust[2] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[2] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_thrust[2];
  }

  if (rtb_thrust[3] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[3] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_thrust[3];
  }

  // End of Saturate: '<S175>/Saturation'

  // SignalConversion generated from: '<S3>/Integrator'
  rtDW.TmpSignalConversionAtIntegrat_p[0] = rtDW.x_dach_g[1];
  rtDW.TmpSignalConversionAtIntegrat_p[1] = rtDW.x_dach_n[1];
  rtDW.TmpSignalConversionAtIntegrat_p[2] = rtDW.x_dach[1];

  // Sum: '<S320>/SumD' incorporates:
  //   Gain: '<S318>/Derivative Gain'
  //   UnaryMinus: '<S319>/Unary Minus'

  rtDW.SumD_kz = rtP.kd_yaw * -rtDW.x_dach[1] - rtb_FilterCoefficient;

  // Gain: '<S322>/Integral Gain'
  rtDW.IntegralGain_p = rtP.ki_yaw * rtb_UnaryMinus_a;

  // Sum: '<S268>/SumD' incorporates:
  //   Gain: '<S266>/Derivative Gain'
  //   UnaryMinus: '<S267>/Unary Minus'

  rtDW.SumD_kb = rtP.kd_pitch * -rtDW.x_dach_n[1] - rtb_FilterCoefficient_gy;

  // Gain: '<S270>/Integral Gain'
  rtDW.IntegralGain_m = rtP.ki_pitch * rtb_UnaryMinus;

  // Sum: '<S216>/SumD' incorporates:
  //   Gain: '<S214>/Derivative Gain'
  //   UnaryMinus: '<S215>/Unary Minus'

  rtDW.SumD_e = rtP.kd_roll * -rtDW.x_dach_g[1] - rtb_FilterCoefficient_o;

  // Gain: '<S218>/Integral Gain'
  rtDW.IntegralGain_l = rtP.ki_roll * rtb_Sum_l;

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[3] = rtDW.TmpSignalConversionAtIntegrat_p[0];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[0] = rtX.Integrator_CSTATE_f[0];

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[4] = rtDW.TmpSignalConversionAtIntegrat_p[1];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[1] = rtX.Integrator_CSTATE_f[1];

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[5] = rtDW.TmpSignalConversionAtIntegrat_p[2];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[2] = rtX.Integrator_CSTATE_f[2];
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S7>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_d[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_d[1];

      // Update for UnitDelay: '<S7>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_dr[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_dr[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_dr[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_dr[3];

      // Update for UnitDelay: '<S8>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_f[0] = rtDW.x_dach_j[0];
      rtDW.UnitDelay1_DSTATE_f[1] = rtDW.x_dach_j[1];

      // Update for UnitDelay: '<S8>/Unit Delay'
      rtDW.UnitDelay_DSTATE_i[0] = rtDW.P_nu[0];
      rtDW.UnitDelay_DSTATE_i[1] = rtDW.P_nu[1];
      rtDW.UnitDelay_DSTATE_i[2] = rtDW.P_nu[2];
      rtDW.UnitDelay_DSTATE_i[3] = rtDW.P_nu[3];

      // Update for UnitDelay: '<S10>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_a[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_a[1];

      // Update for UnitDelay: '<S10>/Unit Delay'
      rtDW.UnitDelay_DSTATE_d[0] = rtDW.P_j[0];
      rtDW.UnitDelay_DSTATE_d[1] = rtDW.P_j[1];
      rtDW.UnitDelay_DSTATE_d[2] = rtDW.P_j[2];
      rtDW.UnitDelay_DSTATE_d[3] = rtDW.P_j[3];

      // Update for UnitDelay: '<S176>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_b[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S176>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S177>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b4[0] = rtDW.x_dach_n[0];
      rtDW.UnitDelay1_DSTATE_b4[1] = rtDW.x_dach_n[1];

      // Update for UnitDelay: '<S177>/Unit Delay'
      rtDW.UnitDelay_DSTATE_g[0] = rtDW.P_d[0];
      rtDW.UnitDelay_DSTATE_g[1] = rtDW.P_d[1];
      rtDW.UnitDelay_DSTATE_g[2] = rtDW.P_d[2];
      rtDW.UnitDelay_DSTATE_g[3] = rtDW.P_d[3];

      // Update for UnitDelay: '<S179>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_n[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_n[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S179>/Unit Delay'
      rtDW.UnitDelay_DSTATE_f[0] = rtDW.P_h[0];
      rtDW.UnitDelay_DSTATE_f[1] = rtDW.P_h[1];
      rtDW.UnitDelay_DSTATE_f[2] = rtDW.P_h[2];
      rtDW.UnitDelay_DSTATE_f[3] = rtDW.P_h[3];
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
void Controller::controller_3dof_container_derivatives()
{
  Controller::XDot *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S1>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S1>/Integrator'

  // Derivatives for Integrator: '<S52>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S47>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD_p;

  // Derivatives for Integrator: '<S104>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S99>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_k;

  // Derivatives for Integrator: '<S156>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S151>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.SumD;

  // Derivatives for Integrator: '<S221>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S216>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.SumD_e;

  // Derivatives for Integrator: '<S273>/Integrator'
  _rtXdot->Integrator_CSTATE_ja = rtDW.IntegralGain_m;

  // Derivatives for Integrator: '<S268>/Filter'
  _rtXdot->Filter_CSTATE_i = rtDW.SumD_kb;

  // Derivatives for Integrator: '<S325>/Integrator'
  _rtXdot->Integrator_CSTATE_iq = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S320>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.SumD_kz;

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S11>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S180>/Integrator'
  _rtXdot->Integrator_CSTATE_i[0] = rtDW.Sum_d[0];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[0] = rtDW.TmpSignalConversionAtIntegrat_p[0];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S11>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S180>/Integrator'
  _rtXdot->Integrator_CSTATE_i[1] = rtDW.Sum_d[1];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[1] = rtDW.TmpSignalConversionAtIntegrat_p[1];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S11>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S180>/Integrator'
  _rtXdot->Integrator_CSTATE_i[2] = rtDW.Sum_d[2];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[2] = rtDW.TmpSignalConversionAtIntegrat_p[2];

  // Derivatives for Integrator: '<S7>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_d[1];

  // Derivatives for TransferFcn: '<S7>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE = rtP.TransferFcn1_A * rtX.TransferFcn1_CSTATE;

  // Derivatives for Integrator: '<S8>/Integrator1'
  _rtXdot->Integrator1_CSTATE_i = rtDW.x_dach_j[1];

  // Derivatives for TransferFcn: '<S8>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_a = rtP.TransferFcn1_A_h *
    rtX.TransferFcn1_CSTATE_a;

  // Derivatives for Integrator: '<S10>/Integrator1'
  _rtXdot->Integrator1_CSTATE_k = rtDW.x_dach_a[1];

  // Derivatives for TransferFcn: '<S10>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_c = rtP.TransferFcn1_A_c *
    rtX.TransferFcn1_CSTATE_c;

  // Derivatives for Integrator: '<S176>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach_g[1];

  // Derivatives for TransferFcn: '<S176>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_o = rtP.TransferFcn1_A_d *
    rtX.TransferFcn1_CSTATE_o;

  // Derivatives for Integrator: '<S177>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_n[1];

  // Derivatives for TransferFcn: '<S177>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_k = rtP.TransferFcn1_A_a *
    rtX.TransferFcn1_CSTATE_k;

  // Derivatives for Integrator: '<S179>/Integrator1'
  _rtXdot->Integrator1_CSTATE_km = rtDW.x_dach[1];

  // Derivatives for TransferFcn: '<S179>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_e = rtP.TransferFcn1_A_hf *
    rtX.TransferFcn1_CSTATE_e;
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
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC[i];
    }

    // End of InitializeConditions for Integrator: '<S1>/Integrator'

    // InitializeConditions for UnitDelay: '<S7>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S7>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for Integrator: '<S52>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S47>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for UnitDelay: '<S8>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S8>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_d[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_d[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_d[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_d[3];

    // InitializeConditions for Integrator: '<S104>/Integrator'
    rtX.Integrator_CSTATE_c = rtP.PIDController1_InitialConditi_p;

    // InitializeConditions for Integrator: '<S99>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController1_InitialCondition;

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_e[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_e[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_e[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_e[3];

    // InitializeConditions for Integrator: '<S156>/Integrator'
    rtX.Integrator_CSTATE_o = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S151>/Filter'
    rtX.Filter_CSTATE_j = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[0] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S11>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S180>/Integrator'
    rtX.Integrator_CSTATE_i[0] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[1] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S11>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S180>/Integrator'
    rtX.Integrator_CSTATE_i[1] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[2] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S11>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S180>/Integrator'
    rtX.Integrator_CSTATE_i[2] = rtP.Integrator_IC_f;

    // InitializeConditions for UnitDelay: '<S176>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_b[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S176>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_o[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_o[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_o[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_o[3];

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b4[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_b4[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay'
    rtDW.UnitDelay_DSTATE_g[0] = rtP.UnitDelay_InitialCondition_p[0];
    rtDW.UnitDelay_DSTATE_g[1] = rtP.UnitDelay_InitialCondition_p[1];
    rtDW.UnitDelay_DSTATE_g[2] = rtP.UnitDelay_InitialCondition_p[2];
    rtDW.UnitDelay_DSTATE_g[3] = rtP.UnitDelay_InitialCondition_p[3];

    // InitializeConditions for UnitDelay: '<S179>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_n[0] = rtP.UnitDelay1_InitialCondition_mp[0];
    rtDW.UnitDelay1_DSTATE_n[1] = rtP.UnitDelay1_InitialCondition_mp[1];

    // InitializeConditions for UnitDelay: '<S179>/Unit Delay'
    rtDW.UnitDelay_DSTATE_f[0] = rtP.UnitDelay_InitialCondition_eq[0];
    rtDW.UnitDelay_DSTATE_f[1] = rtP.UnitDelay_InitialCondition_eq[1];
    rtDW.UnitDelay_DSTATE_f[2] = rtP.UnitDelay_InitialCondition_eq[2];
    rtDW.UnitDelay_DSTATE_f[3] = rtP.UnitDelay_InitialCondition_eq[3];

    // InitializeConditions for Integrator: '<S221>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S216>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController_InitialConditio_c;

    // InitializeConditions for Integrator: '<S273>/Integrator'
    rtX.Integrator_CSTATE_ja = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S268>/Filter'
    rtX.Filter_CSTATE_i = rtP.PIDController1_InitialConditi_k;

    // InitializeConditions for Integrator: '<S325>/Integrator'
    rtX.Integrator_CSTATE_iq = rtP.PIDController2_InitialConditi_m;

    // InitializeConditions for Integrator: '<S320>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_j;

    // InitializeConditions for Integrator: '<S3>/Integrator'
    rtX.Integrator_CSTATE_f[0] = rtP.Integrator_IC_fv;
    rtX.Integrator_CSTATE_f[1] = rtP.Integrator_IC_fv;
    rtX.Integrator_CSTATE_f[2] = rtP.Integrator_IC_fv;

    // InitializeConditions for Integrator: '<S7>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for TransferFcn: '<S7>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE = 0.0;

    // InitializeConditions for Integrator: '<S8>/Integrator1'
    rtX.Integrator1_CSTATE_i = rtP.Integrator1_IC_e;

    // InitializeConditions for TransferFcn: '<S8>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE_a = 0.0;

    // InitializeConditions for Integrator: '<S10>/Integrator1'
    rtX.Integrator1_CSTATE_k = rtP.Integrator1_IC_e4;

    // InitializeConditions for TransferFcn: '<S10>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE_c = 0.0;

    // InitializeConditions for Integrator: '<S176>/Integrator1'
    rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_g;

    // InitializeConditions for TransferFcn: '<S176>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE_o = 0.0;

    // InitializeConditions for Integrator: '<S177>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_l;

    // InitializeConditions for TransferFcn: '<S177>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE_k = 0.0;

    // InitializeConditions for Integrator: '<S179>/Integrator1'
    rtX.Integrator1_CSTATE_km = rtP.Integrator1_IC_o;

    // InitializeConditions for TransferFcn: '<S179>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE_e = 0.0;
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
