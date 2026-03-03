//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.496
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Mar  3 20:48:26 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_6dof_container.h"
#include "rtwtypes.h"
#include <cmath>
#include <cstring>

// private model entry point functions
extern void controller_6dof_container_derivatives();

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
  int_T nXc { 60 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  controller_6dof_container_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

//
// Output and update for atomic system:
//    '<S2>/MATLAB Function'
//    '<S3>/MATLAB Function'
//
void Controller::MATLABFunction(real_T rtu_u, real_T rtu_u_g, real_T rtu_u_h,
  real_T rtu_u_hc, real_T rty_y[4])
{
  rty_y[0] = 0.0;
  rty_y[1] = 0.0;
  rty_y[2] = 0.0;
  rty_y[3] = 0.0;

  // SignalConversion generated from: '<S6>/ SFunction '
  rty_y[0] = std::fmin(std::fmax(rtu_u, 0.0), 12.0);
  rty_y[1] = std::fmin(std::fmax(rtu_u_g, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[2] = std::fmin(std::fmax(rtu_u_h, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[3] = rtu_u_hc;
}

//
// Output and update for atomic system:
//    '<S168>/KF_Elevation'
//    '<S169>/KF_Elevation'
//    '<S171>/KF_Elevation'
//    '<S498>/KF_Elevation'
//    '<S499>/KF_Elevation'
//    '<S501>/KF_Elevation'
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
  real_T a_0[9];
  real_T d[9];
  real_T tmp_0[9];
  real_T c_data[4];
  real_T rtb_Saturation_a[4];
  real_T rtb_thrust[4];
  real_T rtb_y[4];
  real_T B_0[3];
  real_T a_1[3];
  real_T tmp_1[3];
  real_T a;
  real_T omega_dot_idx_0;
  real_T omega_dot_idx_2;
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_l;
  real_T rtb_FilterCoefficient_p;
  real_T rtb_Sum2;
  real_T rtb_Sum_bw;
  real_T rtb_Sum_d0;
  real_T rtb_UnaryMinus;
  real_T rtb_UnaryMinus_d;
  real_T rtb_UnaryMinus_m;
  real_T rtb_y_0;
  real_T rtb_y_1;
  real_T rtb_y_2;
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
  static const int8_T b[3]{ 0, 0, 1 };

  static const int8_T c[3]{ 0, 1, 0 };

  static const int8_T d_0[3]{ 1, 0, 0 };

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

  std::memcpy(&rtY.x_pred[0], &rtX.Integrator_CSTATE[0], 12U * sizeof(real_T));

  // Sum: '<S3>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_FilterCoefficient = rtX.Integrator_CSTATE[2] - rtU.w[2];

  // Gain: '<S482>/Filter Coefficient' incorporates:
  //   Gain: '<S472>/Derivative Gain'
  //   Integrator: '<S474>/Filter'
  //   Sum: '<S474>/SumD'

  rtDW.FilterCoefficient = (rtP.PIDController2_D * rtb_FilterCoefficient -
    rtX.Filter_CSTATE) * rtP.PIDController2_N;

  // Sum: '<S3>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_FilterCoefficient_p = rtU.w[1] - rtX.Integrator_CSTATE[1];

  // Gain: '<S430>/Filter Coefficient' incorporates:
  //   Gain: '<S420>/Derivative Gain'
  //   Integrator: '<S422>/Filter'
  //   Sum: '<S422>/SumD'

  rtDW.FilterCoefficient_p = (rtP.PIDController1_D * rtb_FilterCoefficient_p -
    rtX.Filter_CSTATE_g) * rtP.PIDController1_N;

  // Sum: '<S3>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_UnaryMinus = rtX.Integrator_CSTATE[0] - rtU.w[0];

  // Gain: '<S378>/Filter Coefficient' incorporates:
  //   Gain: '<S368>/Derivative Gain'
  //   Integrator: '<S370>/Filter'
  //   Sum: '<S370>/SumD'

  rtDW.FilterCoefficient_e = (rtP.PIDController_D * rtb_UnaryMinus -
    rtX.Filter_CSTATE_k) * rtP.PIDController_N;

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   Constant: '<S3>/Constant'
  //   Gain: '<S380>/Proportional Gain'
  //   Gain: '<S432>/Proportional Gain'
  //   Gain: '<S484>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S375>/Integrator'
  //   Integrator: '<S427>/Integrator'
  //   Integrator: '<S479>/Integrator'
  //   Sum: '<S384>/Sum'
  //   Sum: '<S3>/Sum3'
  //   Sum: '<S436>/Sum'
  //   Sum: '<S488>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtP.PIDController2_P * rtb_FilterCoefficient
    + rtX.Integrator_CSTATE_a) + rtDW.FilterCoefficient), (rtP.PIDController1_P *
    rtb_FilterCoefficient_p + rtX.Integrator_CSTATE_j) +
                 rtDW.FilterCoefficient_p, (rtP.PIDController_P * rtb_UnaryMinus
    + rtX.Integrator_CSTATE_m) + rtDW.FilterCoefficient_e, rtU.w[3], rtb_y);
  tmp = ((&rtM)->isMajorTimeStep());
  if (tmp) {
    // UnitDelay: '<S498>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S498>/KF_Elevation' incorporates:
    //   Constant: '<S498>/Constant'
    //   Constant: '<S498>/Constant1'
    //   Constant: '<S498>/Constant2'
    //   Constant: '<S498>/Constant5'
    //   Constant: '<S498>/Cov Messrauschen'
    //   Constant: '<S498>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S498>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value,
                 rtX.Integrator_CSTATE[6], rtP.Constant5_Value,
                 rtDW.UnitDelay_DSTATE, rtDW.x_dach_e, rtDW.P_b);
  }

  // Sum: '<S500>/Sum'
  rtb_FilterCoefficient_l = rtb_y[1] - rtDW.x_dach_e[0];

  // Gain: '<S546>/Filter Coefficient' incorporates:
  //   Integrator: '<S538>/Filter'

  rtb_UnaryMinus_d = rtP.ke * rtX.Filter_CSTATE_n;
  if (tmp) {
    // UnitDelay: '<S499>/Unit Delay1'
    rtDW.x_dach_o[0] = rtDW.UnitDelay1_DSTATE_a[0];
    rtDW.x_dach_o[1] = rtDW.UnitDelay1_DSTATE_a[1];

    // MATLAB Function: '<S499>/KF_Elevation' incorporates:
    //   Constant: '<S499>/Constant'
    //   Constant: '<S499>/Constant1'
    //   Constant: '<S499>/Constant2'
    //   Constant: '<S499>/Constant5'
    //   Constant: '<S499>/Cov Messrauschen'
    //   Constant: '<S499>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S499>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a, rtP.Constant1_Value_j,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_e,
                 rtP.CovMessrauschen_Value_o, rtX.Integrator_CSTATE[7],
                 rtP.Constant5_Value_d, rtDW.UnitDelay_DSTATE_m, rtDW.x_dach_o,
                 rtDW.P_n);
  }

  // Sum: '<S500>/Sum1'
  rtb_UnaryMinus_m = rtb_y[2] - rtDW.x_dach_o[0];

  // Gain: '<S598>/Filter Coefficient' incorporates:
  //   Integrator: '<S590>/Filter'

  rtb_Sum_bw = rtP.ke * rtX.Filter_CSTATE_e;
  if (tmp) {
    // UnitDelay: '<S501>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S501>/KF_Elevation' incorporates:
    //   Constant: '<S501>/Constant'
    //   Constant: '<S501>/Constant1'
    //   Constant: '<S501>/Constant2'
    //   Constant: '<S501>/Constant5'
    //   Constant: '<S501>/Cov Messrauschen'
    //   Constant: '<S501>/Cov Prozessrauschen'
    //   Integrator: '<S1>/Integrator'
    //   UnitDelay: '<S501>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_a,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_p,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE[8],
                 rtP.Constant5_Value_g, rtDW.UnitDelay_DSTATE_j, rtDW.x_dach,
                 rtDW.P_l);
  }

  // Sum: '<S500>/Sum2'
  rtb_Sum_d0 = rtb_y[3] - rtDW.x_dach[0];

  // Gain: '<S650>/Filter Coefficient' incorporates:
  //   Integrator: '<S642>/Filter'

  rtb_Sum2 = rtP.ke * rtX.Filter_CSTATE_j;

  // Saturate: '<S167>/Saturation' incorporates:
  //   Gain: '<S548>/Proportional Gain'
  //   Gain: '<S600>/Proportional Gain'
  //   Gain: '<S652>/Proportional Gain'
  //   Integrator: '<S543>/Integrator'
  //   Integrator: '<S595>/Integrator'
  //   Integrator: '<S647>/Integrator'
  //   MATLAB Function: '<S497>/MATLAB Function'
  //   SignalConversion generated from: '<S503>/ SFunction '
  //   Sum: '<S552>/Sum'
  //   Sum: '<S604>/Sum'
  //   Sum: '<S656>/Sum'

  rtb_Saturation_a[0] = rtb_y[0];
  rtb_Saturation_a[1] = (rtP.kp_roll * rtb_FilterCoefficient_l +
    rtX.Integrator_CSTATE_my) + rtb_UnaryMinus_d;
  rtb_Saturation_a[2] = (rtP.kp_pitch * rtb_UnaryMinus_m +
    rtX.Integrator_CSTATE_b) + rtb_Sum_bw;
  rtb_Saturation_a[3] = (rtP.kp_yaw * rtb_Sum_d0 + rtX.Integrator_CSTATE_l) +
    rtb_Sum2;

  // MATLAB Function: '<S497>/MATLAB Function'
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

  rtb_y_0 = 0.0;
  rtb_y_1 = 0.0;
  rtb_y_2 = 0.0;
  s = 0.0;
  for (i = 0; i < 4; i++) {
    smax = rtb_Saturation_a[i];
    jj = i << 2;
    rtb_y_0 += b_a[jj] * smax;
    rtb_y_1 += b_a[jj + 1] * smax;
    rtb_y_2 += b_a[jj + 2] * smax;
    s += b_a[jj + 3] * smax;
    rtb_Saturation_a[i] = 0.0;
  }

  rtb_y[3] = s;
  rtb_y[2] = rtb_y_2;
  rtb_y[1] = rtb_y_1;
  rtb_y[0] = rtb_y_0;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_y[i] / rtP.a >= 0.0) {
      pipk++;
    }
  }

  jBcol = pipk;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_y[i] / rtP.a >= 0.0) {
      tmp_data[pipk] = static_cast<int8_T>(i);
      pipk++;
    }
  }

  for (jj = 0; jj < jBcol; jj++) {
    c_data[jj] = rtb_y[tmp_data[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_Saturation_a[tmp_data[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S497>/Saturation'
  if (rtb_Saturation_a[0] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[0] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[0];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S497>/Saturation'

  rtb_y_0 = smax - rtP.b;
  rtb_thrust[0] = rtb_y_0 * rtb_y_0;

  // Saturate: '<S497>/Saturation'
  if (rtb_Saturation_a[1] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[1] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[1];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S497>/Saturation'

  rtb_y_0 = smax - rtP.b;
  rtb_thrust[1] = rtb_y_0 * rtb_y_0;

  // Saturate: '<S497>/Saturation'
  if (rtb_Saturation_a[2] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[2] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[2];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S497>/Saturation'

  rtb_y_0 = smax - rtP.b;
  rtb_thrust[2] = rtb_y_0 * rtb_y_0;

  // Saturate: '<S497>/Saturation'
  if (rtb_Saturation_a[3] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[3] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[3];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S497>/Saturation'

  rtb_y_0 = smax - rtP.b;
  rtb_thrust[3] = rtb_y_0 * rtb_y_0;

  // Gain: '<S1>/Mixer'
  rtY.thrust = 0.0;

  // Gain: '<S1>/Mixer' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  rtb_y_0 = 0.0;
  rtb_y_1 = 0.0;
  rtb_y_2 = 0.0;
  for (pipk = 0; pipk < 4; pipk++) {
    smax = rtP.a * rtb_thrust[pipk];
    jj = pipk << 2;
    rtY.thrust += rtP.E[jj] * smax;
    rtb_y_0 += rtP.E[jj + 1] * smax;
    rtb_y_1 += rtP.E[jj + 2] * smax;
    rtb_y_2 += rtP.E[jj + 3] * smax;
  }

  // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
  //   Gain: '<S1>/Mixer'
  //   Integrator: '<S1>/Integrator'

  a = 1.0 / rtP.m;
  omega_dot_idx_0 = 0.0;
  s = 0.0;
  omega_dot_idx_2 = 0.0;
  for (pipk = 0; pipk < 3; pipk++) {
    smax = rtX.Integrator_CSTATE[pipk + 9];
    omega_dot_idx_0 += rtP.I[3 * pipk] * smax;
    s += rtP.I[3 * pipk + 1] * smax;
    omega_dot_idx_2 += rtP.I[3 * pipk + 2] * smax;
  }

  std::memcpy(&A_0[0], &rtP.I[0], 9U * sizeof(real_T));
  B_0[0] = (rtb_y_0 - rtP.p * rtX.Integrator_CSTATE[9]) - (omega_dot_idx_2 *
    rtX.Integrator_CSTATE[10] - s * rtX.Integrator_CSTATE[11]);
  B_0[1] = (rtb_y_1 - rtP.p * rtX.Integrator_CSTATE[10]) - (omega_dot_idx_0 *
    rtX.Integrator_CSTATE[11] - omega_dot_idx_2 * rtX.Integrator_CSTATE[9]);
  B_0[2] = (rtb_y_2 - rtP.p * rtX.Integrator_CSTATE[11]) - (s *
    rtX.Integrator_CSTATE[9] - omega_dot_idx_0 * rtX.Integrator_CSTATE[10]);
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
  tmp_0[0] = std::cos(rtX.Integrator_CSTATE[8]);
  tmp_0[3] = -std::sin(rtX.Integrator_CSTATE[8]);
  tmp_0[6] = 0.0;
  tmp_0[1] = std::sin(rtX.Integrator_CSTATE[8]);
  tmp_0[4] = std::cos(rtX.Integrator_CSTATE[8]);
  tmp_0[7] = 0.0;
  d[0] = std::cos(rtX.Integrator_CSTATE[7]);
  d[3] = 0.0;
  d[6] = std::sin(rtX.Integrator_CSTATE[7]);
  d[2] = -std::sin(rtX.Integrator_CSTATE[7]);
  d[5] = 0.0;
  d[8] = std::cos(rtX.Integrator_CSTATE[7]);
  for (pipk = 0; pipk < 3; pipk++) {
    i = 3 * pipk + 2;
    tmp_0[i] = b[pipk];
    jBcol = 3 * pipk + 1;
    d[jBcol] = c[pipk];
    a_0[3 * pipk] = 0.0;
    a_0[jBcol] = 0.0;
    a_0[i] = 0.0;
  }

  for (pipk = 0; pipk < 3; pipk++) {
    smax = a_0[3 * pipk];
    i = 3 * pipk + 1;
    rtb_y_0 = a_0[i];
    jBcol = 3 * pipk + 2;
    rtb_y_1 = a_0[jBcol];
    for (d_k = 0; d_k < 3; d_k++) {
      rtb_y_2 = d[3 * pipk + d_k];
      smax += tmp_0[3 * d_k] * rtb_y_2;
      rtb_y_0 += tmp_0[3 * d_k + 1] * rtb_y_2;
      rtb_y_1 += tmp_0[3 * d_k + 2] * rtb_y_2;
    }

    a_0[jBcol] = rtb_y_1;
    a_0[i] = rtb_y_0;
    a_0[3 * pipk] = smax;
  }

  d[1] = 0.0;
  d[4] = std::cos(rtX.Integrator_CSTATE[6]);
  d[7] = -std::sin(rtX.Integrator_CSTATE[6]);
  d[2] = 0.0;
  d[5] = std::sin(rtX.Integrator_CSTATE[6]);
  d[8] = std::cos(rtX.Integrator_CSTATE[6]);
  for (pipk = 0; pipk < 3; pipk++) {
    d[3 * pipk] = d_0[pipk];
    smax = 0.0;
    rtb_y_0 = 0.0;
    rtb_y_1 = 0.0;
    for (i = 0; i < 3; i++) {
      rtb_y_2 = d[3 * pipk + i];
      smax += a_0[3 * i] * rtb_y_2;
      rtb_y_0 += a_0[3 * i + 1] * rtb_y_2;
      rtb_y_1 += a_0[3 * i + 2] * rtb_y_2;
    }

    tmp_0[3 * pipk + 2] = rtb_y_1;
    tmp_0[3 * pipk + 1] = rtb_y_0;
    tmp_0[3 * pipk] = smax;
  }

  for (pipk = 0; pipk < 9; pipk++) {
    a_0[pipk] = a * tmp_0[pipk];
  }

  a_1[0] = 0.0;
  a_1[1] = 0.0;
  a_1[2] = -rtY.thrust;
  tmp_1[0] = 0.0;
  tmp_1[1] = 0.0;
  tmp_1[2] = rtP.g;
  a = 0.0;
  rtb_y_0 = 0.0;
  rtb_y_1 = 0.0;
  for (pipk = 0; pipk < 3; pipk++) {
    smax = a_1[pipk];
    a += a_0[3 * pipk] * smax;
    rtb_y_0 += a_0[3 * pipk + 1] * smax;
    rtb_y_1 += a_0[3 * pipk + 2] * smax;
  }

  a_1[2] = rtb_y_1;
  a_1[1] = rtb_y_0;
  a_1[0] = a;
  tmp_0[0] = 1.0;
  tmp_0[3] = std::sin(rtX.Integrator_CSTATE[6]) * std::tan
    (rtX.Integrator_CSTATE[7]);
  tmp_0[6] = std::cos(rtX.Integrator_CSTATE[6]) * std::tan
    (rtX.Integrator_CSTATE[7]);
  tmp_0[1] = 0.0;
  tmp_0[4] = std::cos(rtX.Integrator_CSTATE[6]);
  tmp_0[7] = -std::sin(rtX.Integrator_CSTATE[6]);
  tmp_0[2] = 0.0;
  tmp_0[5] = std::sin(rtX.Integrator_CSTATE[6]) / std::cos
    (rtX.Integrator_CSTATE[7]);
  tmp_0[8] = std::cos(rtX.Integrator_CSTATE[6]) / std::cos
    (rtX.Integrator_CSTATE[7]);
  rtb_y_0 = 0.0;
  rtb_y_1 = 0.0;
  rtb_y_2 = 0.0;
  for (pipk = 0; pipk < 3; pipk++) {
    smax = rtX.Integrator_CSTATE[pipk + 9];
    rtb_y_0 += tmp_0[3 * pipk] * smax;
    rtb_y_1 += tmp_0[3 * pipk + 1] * smax;
    rtb_y_2 += tmp_0[3 * pipk + 2] * smax;
    rtDW.dx[pipk] = rtX.Integrator_CSTATE[pipk + 3];
    rtDW.dx[pipk + 3] = tmp_1[pipk] + a_1[pipk];
  }

  // SignalConversion generated from: '<S340>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_e[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_o[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach[1];

  // Sum: '<S642>/SumD' incorporates:
  //   Gain: '<S640>/Derivative Gain'
  //   UnaryMinus: '<S641>/Unary Minus'

  rtDW.SumD = rtP.kd_yaw * -rtDW.x_dach[1] - rtb_Sum2;

  // Gain: '<S644>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_yaw * rtb_Sum_d0;

  // Sum: '<S590>/SumD' incorporates:
  //   Gain: '<S588>/Derivative Gain'
  //   UnaryMinus: '<S589>/Unary Minus'

  rtDW.SumD_n = rtP.kd_pitch * -rtDW.x_dach_o[1] - rtb_Sum_bw;

  // Gain: '<S592>/Integral Gain'
  rtDW.IntegralGain_k = rtP.ki_pitch * rtb_UnaryMinus_m;

  // Sum: '<S538>/SumD' incorporates:
  //   Gain: '<S536>/Derivative Gain'
  //   UnaryMinus: '<S537>/Unary Minus'

  rtDW.SumD_d = rtP.kd_roll * -rtDW.x_dach_e[1] - rtb_UnaryMinus_d;

  // Gain: '<S540>/Integral Gain'
  rtDW.IntegralGain_e = rtP.ki_roll * rtb_FilterCoefficient_l;

  // Gain: '<S372>/Integral Gain'
  rtDW.IntegralGain_i = rtP.PIDController_I * rtb_UnaryMinus;

  // Gain: '<S424>/Integral Gain'
  rtDW.IntegralGain_d = rtP.PIDController1_I * rtb_FilterCoefficient_p;

  // Gain: '<S476>/Integral Gain'
  rtDW.IntegralGain_l = rtP.PIDController2_I * rtb_FilterCoefficient;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[6] = rtb_y_0;
  rtDW.dx[9] = ((B_0[jj] - A_0[jj + 6] * omega_dot_idx_2) - A_0[jj + 3] * s) /
    A_0[jj];

  // Sum: '<S172>/Sum' incorporates:
  //   SignalConversion generated from: '<S172>/Gain1'

  rtDW.Sum[0] = 0.0;

  // Sum: '<S502>/Sum' incorporates:
  //   SignalConversion generated from: '<S502>/Gain1'

  rtDW.Sum_j[0] = 0.0;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[7] = rtb_y_1;
  rtDW.dx[10] = s;

  // Sum: '<S172>/Sum' incorporates:
  //   SignalConversion generated from: '<S172>/Gain1'

  rtDW.Sum[1] = 0.0;

  // Sum: '<S502>/Sum' incorporates:
  //   SignalConversion generated from: '<S502>/Gain1'

  rtDW.Sum_j[1] = 0.0;

  // MATLAB Function: '<S1>/MATLAB Function2'
  rtDW.dx[8] = rtb_y_2;
  rtDW.dx[11] = omega_dot_idx_2;

  // Sum: '<S172>/Sum' incorporates:
  //   SignalConversion generated from: '<S172>/Gain1'

  rtDW.Sum[2] = 0.0;

  // Sum: '<S502>/Sum' incorporates:
  //   SignalConversion generated from: '<S502>/Gain1'

  rtDW.Sum_j[2] = 0.0;
  if (tmp) {
    // UnitDelay: '<S168>/Unit Delay1'
    rtDW.x_dach_es[0] = rtDW.UnitDelay1_DSTATE_f[0];
    rtDW.x_dach_es[1] = rtDW.UnitDelay1_DSTATE_f[1];

    // MATLAB Function: '<S168>/KF_Elevation' incorporates:
    //   Constant: '<S168>/Constant'
    //   Constant: '<S168>/Constant1'
    //   Constant: '<S168>/Constant2'
    //   Constant: '<S168>/Constant5'
    //   Constant: '<S168>/Cov Messrauschen'
    //   Constant: '<S168>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S168>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_o, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_c, rtP.CovProzessrauschen_Value_a,
                 rtP.CovMessrauschen_Value_k, rtU.y[3], rtP.Constant5_Value_df,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach_es, rtDW.P_i);

    // UnitDelay: '<S169>/Unit Delay1'
    rtDW.x_dach_k[0] = rtDW.UnitDelay1_DSTATE_a5[0];
    rtDW.x_dach_k[1] = rtDW.UnitDelay1_DSTATE_a5[1];

    // MATLAB Function: '<S169>/KF_Elevation' incorporates:
    //   Constant: '<S169>/Constant'
    //   Constant: '<S169>/Constant1'
    //   Constant: '<S169>/Constant2'
    //   Constant: '<S169>/Constant5'
    //   Constant: '<S169>/Cov Messrauschen'
    //   Constant: '<S169>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S169>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_o,
                 rtP.Constant2_Value_lc, rtP.CovProzessrauschen_Value_f,
                 rtP.CovMessrauschen_Value_n, rtU.y[4], rtP.Constant5_Value_e,
                 rtDW.UnitDelay_DSTATE_fb, rtDW.x_dach_k, rtDW.P_kl);

    // UnitDelay: '<S171>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_o[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_o[1];

    // MATLAB Function: '<S171>/KF_Elevation' incorporates:
    //   Constant: '<S171>/Constant'
    //   Constant: '<S171>/Constant1'
    //   Constant: '<S171>/Constant2'
    //   Constant: '<S171>/Constant5'
    //   Constant: '<S171>/Cov Messrauschen'
    //   Constant: '<S171>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S171>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_px, rtP.Constant1_Value_f,
                 rtP.Constant2_Value_k, rtP.CovProzessrauschen_Value_j,
                 rtP.CovMessrauschen_Value_k4, rtU.y[5], rtP.Constant5_Value_m,
                 rtDW.UnitDelay_DSTATE_k, rtDW.x_dach_g, rtDW.P_k);
  }

  // Sum: '<S2>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtU.y[2] - rtU.w[2];

  // Gain: '<S152>/Filter Coefficient' incorporates:
  //   Gain: '<S142>/Derivative Gain'
  //   Integrator: '<S144>/Filter'
  //   Sum: '<S144>/SumD'

  rtDW.FilterCoefficient_m = (rtP.PIDController2_D_m * rtb_Sum2 -
    rtX.Filter_CSTATE_kb) * rtP.PIDController2_N_j;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_UnaryMinus_m = rtU.w[1] - rtU.y[1];

  // Gain: '<S100>/Filter Coefficient' incorporates:
  //   Gain: '<S90>/Derivative Gain'
  //   Integrator: '<S92>/Filter'
  //   Sum: '<S92>/SumD'

  rtDW.FilterCoefficient_j = (rtP.PIDController1_D_j * rtb_UnaryMinus_m -
    rtX.Filter_CSTATE_m) * rtP.PIDController1_N_o;

  // Sum: '<S2>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum_bw = rtU.y[0] - rtU.w[0];

  // Gain: '<S48>/Filter Coefficient' incorporates:
  //   Gain: '<S38>/Derivative Gain'
  //   Integrator: '<S40>/Filter'
  //   Sum: '<S40>/SumD'

  rtDW.FilterCoefficient_l = (rtP.PIDController_D_i * rtb_Sum_bw -
    rtX.Filter_CSTATE_l) * rtP.PIDController_N_o;

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Constant: '<S2>/Constant'
  //   Gain: '<S102>/Proportional Gain'
  //   Gain: '<S154>/Proportional Gain'
  //   Gain: '<S50>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S149>/Integrator'
  //   Integrator: '<S45>/Integrator'
  //   Integrator: '<S97>/Integrator'
  //   Sum: '<S106>/Sum'
  //   Sum: '<S158>/Sum'
  //   Sum: '<S2>/Sum3'
  //   Sum: '<S54>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtP.PIDController2_P_j * rtb_Sum2 +
    rtX.Integrator_CSTATE_f) + rtDW.FilterCoefficient_m),
                 (rtP.PIDController1_P_n * rtb_UnaryMinus_m +
                  rtX.Integrator_CSTATE_ak) + rtDW.FilterCoefficient_j,
                 (rtP.PIDController_P_d * rtb_Sum_bw + rtX.Integrator_CSTATE_jq)
                 + rtDW.FilterCoefficient_l, rtU.w[3], rtb_Saturation_a);

  // SignalConversion generated from: '<S2>/Vector Concatenate' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'

  rtDW.VectorConcatenate_l[0] = rtb_Saturation_a[0];
  rtDW.VectorConcatenate_l[1] = rtb_Saturation_a[1];
  rtDW.VectorConcatenate_l[2] = rtb_Saturation_a[2];
  rtDW.VectorConcatenate_l[3] = rtb_Saturation_a[3];

  // Sum: '<S170>/Sum'
  rtb_Sum_d0 = rtb_Saturation_a[1] - rtDW.x_dach_es[0];

  // Gain: '<S216>/Filter Coefficient' incorporates:
  //   Integrator: '<S208>/Filter'

  rtb_FilterCoefficient_l = rtP.ke * rtX.Filter_CSTATE_mg;

  // Sum: '<S170>/Sum1'
  rtb_UnaryMinus_d = rtb_Saturation_a[2] - rtDW.x_dach_k[0];

  // Gain: '<S268>/Filter Coefficient' incorporates:
  //   Integrator: '<S260>/Filter'

  rtb_FilterCoefficient_p = rtP.ke * rtX.Filter_CSTATE_jd;

  // Sum: '<S170>/Sum2'
  rtb_UnaryMinus = rtb_Saturation_a[3] - rtDW.x_dach_g[0];

  // Gain: '<S320>/Filter Coefficient' incorporates:
  //   Integrator: '<S312>/Filter'

  rtb_FilterCoefficient = rtP.ke * rtX.Filter_CSTATE_lf;

  // Saturate: '<S167>/Saturation' incorporates:
  //   Gain: '<S218>/Proportional Gain'
  //   Gain: '<S270>/Proportional Gain'
  //   Gain: '<S322>/Proportional Gain'
  //   Integrator: '<S213>/Integrator'
  //   Integrator: '<S265>/Integrator'
  //   Integrator: '<S317>/Integrator'
  //   MATLAB Function: '<S167>/MATLAB Function'
  //   SignalConversion generated from: '<S173>/ SFunction '
  //   Sum: '<S222>/Sum'
  //   Sum: '<S274>/Sum'
  //   Sum: '<S326>/Sum'

  rtb_Saturation_a[1] = (rtP.kp_roll * rtb_Sum_d0 + rtX.Integrator_CSTATE_bg) +
    rtb_FilterCoefficient_l;
  rtb_Saturation_a[2] = (rtP.kp_pitch * rtb_UnaryMinus_d +
    rtX.Integrator_CSTATE_fs) + rtb_FilterCoefficient_p;
  rtb_Saturation_a[3] = (rtP.kp_yaw * rtb_UnaryMinus + rtX.Integrator_CSTATE_bj)
    + rtb_FilterCoefficient;

  // MATLAB Function: '<S167>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S497>/MATLAB Function'

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

  rtb_y_0 = 0.0;
  rtb_y_1 = 0.0;
  rtb_y_2 = 0.0;
  s = 0.0;
  for (i = 0; i < 4; i++) {
    smax = rtb_Saturation_a[i];
    jj = i << 2;
    rtb_y_0 += b_a[jj] * smax;
    rtb_y_1 += b_a[jj + 1] * smax;
    rtb_y_2 += b_a[jj + 2] * smax;
    s += b_a[jj + 3] * smax;
    rtb_thrust[i] = 0.0;
  }

  rtb_y[3] = s;
  rtb_y[2] = rtb_y_2;
  rtb_y[1] = rtb_y_1;
  rtb_y[0] = rtb_y_0;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_y[i] / rtP.a >= 0.0) {
      pipk++;
    }
  }

  jBcol = pipk;
  pipk = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_y[i] / rtP.a >= 0.0) {
      tmp_data_0[pipk] = static_cast<int8_T>(i);
      pipk++;
    }
  }

  for (jj = 0; jj < jBcol; jj++) {
    c_data[jj] = rtb_y[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S167>/Saturation' incorporates:
  //   MATLAB Function: '<S167>/MATLAB Function'

  if (rtb_thrust[0] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[0] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_thrust[0];
  }

  if (rtb_thrust[1] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[1] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_thrust[1];
  }

  if (rtb_thrust[2] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[2] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_thrust[2];
  }

  if (rtb_thrust[3] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[3] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_thrust[3];
  }

  // End of Saturate: '<S167>/Saturation'

  // SignalConversion generated from: '<S10>/Integrator'
  rtDW.TmpSignalConversionAtIntegrat_i[0] = rtDW.x_dach_es[1];
  rtDW.TmpSignalConversionAtIntegrat_i[1] = rtDW.x_dach_k[1];
  rtDW.TmpSignalConversionAtIntegrat_i[2] = rtDW.x_dach_g[1];

  // Sum: '<S312>/SumD' incorporates:
  //   Gain: '<S310>/Derivative Gain'
  //   UnaryMinus: '<S311>/Unary Minus'

  rtDW.SumD_e = rtP.kd_yaw * -rtDW.x_dach_g[1] - rtb_FilterCoefficient;

  // Gain: '<S314>/Integral Gain'
  rtDW.IntegralGain_p = rtP.ki_yaw * rtb_UnaryMinus;

  // Sum: '<S260>/SumD' incorporates:
  //   Gain: '<S258>/Derivative Gain'
  //   UnaryMinus: '<S259>/Unary Minus'

  rtDW.SumD_h = rtP.kd_pitch * -rtDW.x_dach_k[1] - rtb_FilterCoefficient_p;

  // Gain: '<S262>/Integral Gain'
  rtDW.IntegralGain_im = rtP.ki_pitch * rtb_UnaryMinus_d;

  // Sum: '<S208>/SumD' incorporates:
  //   Gain: '<S206>/Derivative Gain'
  //   UnaryMinus: '<S207>/Unary Minus'

  rtDW.SumD_g = rtP.kd_roll * -rtDW.x_dach_es[1] - rtb_FilterCoefficient_l;

  // Gain: '<S210>/Integral Gain'
  rtDW.IntegralGain_o = rtP.ki_roll * rtb_Sum_d0;

  // Gain: '<S42>/Integral Gain'
  rtDW.IntegralGain_eo = rtP.PIDController_I_b * rtb_Sum_bw;

  // Gain: '<S94>/Integral Gain'
  rtDW.IntegralGain_lh = rtP.PIDController1_I_g * rtb_UnaryMinus_m;

  // Gain: '<S146>/Integral Gain'
  rtDW.IntegralGain_dz = rtP.PIDController2_I_a * rtb_Sum2;
  if (tmp) {
    // Constant: '<S2>/Constant1' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate'

    rtDW.VectorConcatenate_l[4] = rtP.Constant1_Value_ot[0];
    rtDW.VectorConcatenate_l[5] = rtP.Constant1_Value_ot[1];
  }

  // Outport: '<Root>/values'
  for (i = 0; i < 6; i++) {
    rtY.values[i] = rtDW.VectorConcatenate_l[i];
  }

  // End of Outport: '<Root>/values'
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S498>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S498>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_b[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_b[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_b[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_b[3];

      // Update for UnitDelay: '<S499>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_o[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_o[1];

      // Update for UnitDelay: '<S499>/Unit Delay'
      rtDW.UnitDelay_DSTATE_m[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_m[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_m[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_m[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S501>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S501>/Unit Delay'
      rtDW.UnitDelay_DSTATE_j[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_j[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_j[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_j[3] = rtDW.P_l[3];

      // Update for UnitDelay: '<S168>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_f[0] = rtDW.x_dach_es[0];
      rtDW.UnitDelay1_DSTATE_f[1] = rtDW.x_dach_es[1];

      // Update for UnitDelay: '<S168>/Unit Delay'
      rtDW.UnitDelay_DSTATE_f[0] = rtDW.P_i[0];
      rtDW.UnitDelay_DSTATE_f[1] = rtDW.P_i[1];
      rtDW.UnitDelay_DSTATE_f[2] = rtDW.P_i[2];
      rtDW.UnitDelay_DSTATE_f[3] = rtDW.P_i[3];

      // Update for UnitDelay: '<S169>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a5[0] = rtDW.x_dach_k[0];
      rtDW.UnitDelay1_DSTATE_a5[1] = rtDW.x_dach_k[1];

      // Update for UnitDelay: '<S169>/Unit Delay'
      rtDW.UnitDelay_DSTATE_fb[0] = rtDW.P_kl[0];
      rtDW.UnitDelay_DSTATE_fb[1] = rtDW.P_kl[1];
      rtDW.UnitDelay_DSTATE_fb[2] = rtDW.P_kl[2];
      rtDW.UnitDelay_DSTATE_fb[3] = rtDW.P_kl[3];

      // Update for UnitDelay: '<S171>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_o[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_o[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S171>/Unit Delay'
      rtDW.UnitDelay_DSTATE_k[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_k[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_k[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_k[3] = rtDW.P_k[3];
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
void Controller::controller_6dof_container_derivatives()
{
  Controller::XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S1>/Integrator'
  std::memcpy(&_rtXdot->Integrator_CSTATE[0], &rtDW.dx[0], 12U * sizeof(real_T));

  // Derivatives for Integrator: '<S479>/Integrator'
  _rtXdot->Integrator_CSTATE_a = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S474>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S427>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S422>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_p;

  // Derivatives for Integrator: '<S375>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S370>/Filter'
  _rtXdot->Filter_CSTATE_k = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S543>/Integrator'
  _rtXdot->Integrator_CSTATE_my = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S538>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.SumD_d;

  // Derivatives for Integrator: '<S595>/Integrator'
  _rtXdot->Integrator_CSTATE_b = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S590>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_n;

  // Derivatives for Integrator: '<S647>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S642>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.SumD;

  // Derivatives for Integrator: '<S149>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_dz;

  // Derivatives for Integrator: '<S144>/Filter'
  _rtXdot->Filter_CSTATE_kb = rtDW.FilterCoefficient_m;

  // Derivatives for Integrator: '<S97>/Integrator'
  _rtXdot->Integrator_CSTATE_ak = rtDW.IntegralGain_lh;

  // Derivatives for Integrator: '<S92>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_j;

  // Derivatives for Integrator: '<S45>/Integrator'
  _rtXdot->Integrator_CSTATE_jq = rtDW.IntegralGain_eo;

  // Derivatives for Integrator: '<S40>/Filter'
  _rtXdot->Filter_CSTATE_l = rtDW.FilterCoefficient_l;

  // Derivatives for Integrator: '<S213>/Integrator'
  _rtXdot->Integrator_CSTATE_bg = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S208>/Filter'
  _rtXdot->Filter_CSTATE_mg = rtDW.SumD_g;

  // Derivatives for Integrator: '<S265>/Integrator'
  _rtXdot->Integrator_CSTATE_fs = rtDW.IntegralGain_im;

  // Derivatives for Integrator: '<S260>/Filter'
  _rtXdot->Filter_CSTATE_jd = rtDW.SumD_h;

  // Derivatives for Integrator: '<S317>/Integrator'
  _rtXdot->Integrator_CSTATE_bj = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S312>/Filter'
  _rtXdot->Filter_CSTATE_lf = rtDW.SumD_e;

  // Derivatives for Integrator: '<S340>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S172>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S502>/Integrator'
  _rtXdot->Integrator_CSTATE_n[0] = rtDW.Sum_j[0];

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_bf[0] = rtDW.TmpSignalConversionAtIntegrat_i[0];

  // Derivatives for Integrator: '<S340>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S172>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S502>/Integrator'
  _rtXdot->Integrator_CSTATE_n[1] = rtDW.Sum_j[1];

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_bf[1] = rtDW.TmpSignalConversionAtIntegrat_i[1];

  // Derivatives for Integrator: '<S340>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S172>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S502>/Integrator'
  _rtXdot->Integrator_CSTATE_n[2] = rtDW.Sum_j[2];

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_bf[2] = rtDW.TmpSignalConversionAtIntegrat_i[2];

  // Derivatives for Integrator: '<S168>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_es[1];

  // Derivatives for TransferFcn: '<S168>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE = rtP.TransferFcn1_A * rtX.TransferFcn1_CSTATE;

  // Derivatives for Integrator: '<S169>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_k[1];

  // Derivatives for TransferFcn: '<S169>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_k = rtP.TransferFcn1_A_m *
    rtX.TransferFcn1_CSTATE_k;

  // Derivatives for Integrator: '<S171>/Integrator1'
  _rtXdot->Integrator1_CSTATE_d = rtDW.x_dach_g[1];

  // Derivatives for TransferFcn: '<S171>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_p = rtP.TransferFcn1_A_n *
    rtX.TransferFcn1_CSTATE_p;

  // Derivatives for Integrator: '<S498>/Integrator1'
  _rtXdot->Integrator1_CSTATE_g = rtDW.x_dach_e[1];

  // Derivatives for TransferFcn: '<S498>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_i = rtP.TransferFcn1_A_e *
    rtX.TransferFcn1_CSTATE_i;

  // Derivatives for Integrator: '<S499>/Integrator1'
  _rtXdot->Integrator1_CSTATE_m = rtDW.x_dach_o[1];

  // Derivatives for TransferFcn: '<S499>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_pa = rtP.TransferFcn1_A_ee *
    rtX.TransferFcn1_CSTATE_pa;

  // Derivatives for Integrator: '<S501>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach[1];

  // Derivatives for TransferFcn: '<S501>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE_g = rtP.TransferFcn1_A_my *
    rtX.TransferFcn1_CSTATE_g;
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

  // InitializeConditions for Integrator: '<S1>/Integrator'
  std::memcpy(&rtX.Integrator_CSTATE[0], &rtP.Integrator_IC[0], 12U * sizeof
              (real_T));

  // InitializeConditions for Integrator: '<S479>/Integrator'
  rtX.Integrator_CSTATE_a = rtP.PIDController2_InitialConditi_o;

  // InitializeConditions for Integrator: '<S474>/Filter'
  rtX.Filter_CSTATE = rtP.PIDController2_InitialCondition;

  // InitializeConditions for Integrator: '<S427>/Integrator'
  rtX.Integrator_CSTATE_j = rtP.PIDController1_InitialConditi_e;

  // InitializeConditions for Integrator: '<S422>/Filter'
  rtX.Filter_CSTATE_g = rtP.PIDController1_InitialCondition;

  // InitializeConditions for Integrator: '<S375>/Integrator'
  rtX.Integrator_CSTATE_m = rtP.PIDController_InitialConditio_n;

  // InitializeConditions for Integrator: '<S370>/Filter'
  rtX.Filter_CSTATE_k = rtP.PIDController_InitialConditionF;

  // InitializeConditions for UnitDelay: '<S498>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
  rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

  // InitializeConditions for UnitDelay: '<S498>/Unit Delay'
  rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
  rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
  rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
  rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

  // InitializeConditions for Integrator: '<S543>/Integrator'
  rtX.Integrator_CSTATE_my = rtP.PIDController_InitialConditio_b;

  // InitializeConditions for Integrator: '<S538>/Filter'
  rtX.Filter_CSTATE_n = rtP.PIDController_InitialConditio_a;

  // InitializeConditions for UnitDelay: '<S499>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_e[0];
  rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_e[1];

  // InitializeConditions for UnitDelay: '<S499>/Unit Delay'
  rtDW.UnitDelay_DSTATE_m[0] = rtP.UnitDelay_InitialCondition_f[0];
  rtDW.UnitDelay_DSTATE_m[1] = rtP.UnitDelay_InitialCondition_f[1];
  rtDW.UnitDelay_DSTATE_m[2] = rtP.UnitDelay_InitialCondition_f[2];
  rtDW.UnitDelay_DSTATE_m[3] = rtP.UnitDelay_InitialCondition_f[3];

  // InitializeConditions for Integrator: '<S595>/Integrator'
  rtX.Integrator_CSTATE_b = rtP.PIDController1_InitialConditi_b;

  // InitializeConditions for Integrator: '<S590>/Filter'
  rtX.Filter_CSTATE_e = rtP.PIDController1_InitialConditi_a;

  // InitializeConditions for UnitDelay: '<S501>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_b[0];
  rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_b[1];

  // InitializeConditions for UnitDelay: '<S501>/Unit Delay'
  rtDW.UnitDelay_DSTATE_j[0] = rtP.UnitDelay_InitialCondition_k[0];
  rtDW.UnitDelay_DSTATE_j[1] = rtP.UnitDelay_InitialCondition_k[1];
  rtDW.UnitDelay_DSTATE_j[2] = rtP.UnitDelay_InitialCondition_k[2];
  rtDW.UnitDelay_DSTATE_j[3] = rtP.UnitDelay_InitialCondition_k[3];

  // InitializeConditions for Integrator: '<S647>/Integrator'
  rtX.Integrator_CSTATE_l = rtP.PIDController2_InitialCondit_k5;

  // InitializeConditions for Integrator: '<S642>/Filter'
  rtX.Filter_CSTATE_j = rtP.PIDController2_InitialConditi_c;

  // InitializeConditions for Integrator: '<S340>/Integrator'
  rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_k;

  // InitializeConditions for Integrator: '<S172>/Integrator'
  rtX.Integrator_CSTATE_ay[0] = rtP.Integrator_IC_p;

  // InitializeConditions for Integrator: '<S502>/Integrator'
  rtX.Integrator_CSTATE_n[0] = rtP.Integrator_IC_g;

  // InitializeConditions for Integrator: '<S340>/Integrator'
  rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_k;

  // InitializeConditions for Integrator: '<S172>/Integrator'
  rtX.Integrator_CSTATE_ay[1] = rtP.Integrator_IC_p;

  // InitializeConditions for Integrator: '<S502>/Integrator'
  rtX.Integrator_CSTATE_n[1] = rtP.Integrator_IC_g;

  // InitializeConditions for Integrator: '<S340>/Integrator'
  rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_k;

  // InitializeConditions for Integrator: '<S172>/Integrator'
  rtX.Integrator_CSTATE_ay[2] = rtP.Integrator_IC_p;

  // InitializeConditions for Integrator: '<S502>/Integrator'
  rtX.Integrator_CSTATE_n[2] = rtP.Integrator_IC_g;

  // InitializeConditions for UnitDelay: '<S168>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_m[0];
  rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_m[1];

  // InitializeConditions for UnitDelay: '<S168>/Unit Delay'
  rtDW.UnitDelay_DSTATE_f[0] = rtP.UnitDelay_InitialCondition_j[0];
  rtDW.UnitDelay_DSTATE_f[1] = rtP.UnitDelay_InitialCondition_j[1];
  rtDW.UnitDelay_DSTATE_f[2] = rtP.UnitDelay_InitialCondition_j[2];
  rtDW.UnitDelay_DSTATE_f[3] = rtP.UnitDelay_InitialCondition_j[3];

  // InitializeConditions for UnitDelay: '<S169>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE_a5[0] = rtP.UnitDelay1_InitialCondition_a[0];
  rtDW.UnitDelay1_DSTATE_a5[1] = rtP.UnitDelay1_InitialCondition_a[1];

  // InitializeConditions for UnitDelay: '<S169>/Unit Delay'
  rtDW.UnitDelay_DSTATE_fb[0] = rtP.UnitDelay_InitialCondition_i[0];
  rtDW.UnitDelay_DSTATE_fb[1] = rtP.UnitDelay_InitialCondition_i[1];
  rtDW.UnitDelay_DSTATE_fb[2] = rtP.UnitDelay_InitialCondition_i[2];
  rtDW.UnitDelay_DSTATE_fb[3] = rtP.UnitDelay_InitialCondition_i[3];

  // InitializeConditions for UnitDelay: '<S171>/Unit Delay1'
  rtDW.UnitDelay1_DSTATE_o[0] = rtP.UnitDelay1_InitialCondition_f[0];
  rtDW.UnitDelay1_DSTATE_o[1] = rtP.UnitDelay1_InitialCondition_f[1];

  // InitializeConditions for UnitDelay: '<S171>/Unit Delay'
  rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_g[0];
  rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_g[1];
  rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_g[2];
  rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_g[3];

  // InitializeConditions for Integrator: '<S149>/Integrator'
  rtX.Integrator_CSTATE_f = rtP.PIDController2_InitialCondit_cd;

  // InitializeConditions for Integrator: '<S144>/Filter'
  rtX.Filter_CSTATE_kb = rtP.PIDController2_InitialConditi_k;

  // InitializeConditions for Integrator: '<S97>/Integrator'
  rtX.Integrator_CSTATE_ak = rtP.PIDController1_InitialConditi_j;

  // InitializeConditions for Integrator: '<S92>/Filter'
  rtX.Filter_CSTATE_m = rtP.PIDController1_InitialConditi_k;

  // InitializeConditions for Integrator: '<S45>/Integrator'
  rtX.Integrator_CSTATE_jq = rtP.PIDController_InitialConditio_d;

  // InitializeConditions for Integrator: '<S40>/Filter'
  rtX.Filter_CSTATE_l = rtP.PIDController_InitialConditio_f;

  // InitializeConditions for Integrator: '<S213>/Integrator'
  rtX.Integrator_CSTATE_bg = rtP.PIDController_InitialConditi_ay;

  // InitializeConditions for Integrator: '<S208>/Filter'
  rtX.Filter_CSTATE_mg = rtP.PIDController_InitialConditio_i;

  // InitializeConditions for Integrator: '<S265>/Integrator'
  rtX.Integrator_CSTATE_fs = rtP.PIDController1_InitialCondit_nz;

  // InitializeConditions for Integrator: '<S260>/Filter'
  rtX.Filter_CSTATE_jd = rtP.PIDController1_InitialConditi_n;

  // InitializeConditions for Integrator: '<S317>/Integrator'
  rtX.Integrator_CSTATE_bj = rtP.PIDController2_InitialConditi_n;

  // InitializeConditions for Integrator: '<S312>/Filter'
  rtX.Filter_CSTATE_lf = rtP.PIDController2_InitialConditi_h;

  // InitializeConditions for Integrator: '<S10>/Integrator'
  rtX.Integrator_CSTATE_bf[0] = rtP.Integrator_IC_m;
  rtX.Integrator_CSTATE_bf[1] = rtP.Integrator_IC_m;
  rtX.Integrator_CSTATE_bf[2] = rtP.Integrator_IC_m;

  // InitializeConditions for Integrator: '<S168>/Integrator1'
  rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

  // InitializeConditions for TransferFcn: '<S168>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S169>/Integrator1'
  rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_g;

  // InitializeConditions for TransferFcn: '<S169>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE_k = 0.0;

  // InitializeConditions for Integrator: '<S171>/Integrator1'
  rtX.Integrator1_CSTATE_d = rtP.Integrator1_IC_p;

  // InitializeConditions for TransferFcn: '<S171>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE_p = 0.0;

  // InitializeConditions for Integrator: '<S498>/Integrator1'
  rtX.Integrator1_CSTATE_g = rtP.Integrator1_IC_h;

  // InitializeConditions for TransferFcn: '<S498>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE_i = 0.0;

  // InitializeConditions for Integrator: '<S499>/Integrator1'
  rtX.Integrator1_CSTATE_m = rtP.Integrator1_IC_n;

  // InitializeConditions for TransferFcn: '<S499>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE_pa = 0.0;

  // InitializeConditions for Integrator: '<S501>/Integrator1'
  rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_ph;

  // InitializeConditions for TransferFcn: '<S501>/Transfer Fcn1'
  rtX.TransferFcn1_CSTATE_g = 0.0;
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
