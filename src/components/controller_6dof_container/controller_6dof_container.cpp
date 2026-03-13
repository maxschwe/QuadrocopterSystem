//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.517
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Mar 13 20:41:26 2026
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
static void rate_scheduler(Controller6dof::RT_MODEL *const rtM);

//
//         This function updates active task flag for each subrate.
//         The function is called at model base rate, hence the
//         generated code self-manages all its subrates.
//
static void rate_scheduler(Controller6dof::RT_MODEL *const rtM)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (rtM->Timing.TaskCounters.TID[2])++;
  if ((rtM->Timing.TaskCounters.TID[2]) > 3) {// Sample time: [0.02s, 0.0s]
    rtM->Timing.TaskCounters.TID[2] = 0;
  }
}

//
// This function updates continuous states using the ODE1 fixed-step
// solver algorithm
//
void Controller6dof::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE1_IntgData *id { static_cast<ODE1_IntgData *>(rtsiGetSolverData(si)) };

  real_T *f0 { id->f[0] };

  int_T i;
  int_T nXc { 52 };

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
void Controller6dof::MATLABFunction(real_T rtu_u, real_T rtu_u_g, real_T rtu_u_h,
  real_T rtu_u_hc, real_T rty_y[4])
{
  rty_y[0] = 0.0;
  rty_y[1] = 0.0;
  rty_y[2] = 0.0;
  rty_y[3] = 0.0;

  // SignalConversion generated from: '<S10>/ SFunction '
  rty_y[0] = std::fmin(std::fmax(rtu_u, 0.0), 13.0);
  rty_y[1] = std::fmin(std::fmax(rtu_u_g, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[2] = std::fmin(std::fmax(rtu_u_h, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[3] = rtu_u_hc;
}

//
// Output and update for atomic system:
//    '<S173>/MATLAB Function'
//    '<S511>/MATLAB Function'
//
void Controller6dof::MATLABFunction_e(const real_T rtu_tau[4], real_T rty_u[4])
{
  real_T A[16];
  real_T B_0[4];
  real_T c_data[4];
  real_T smax;
  int32_T jj;
  int32_T kAcol;
  int32_T n;
  int8_T ipiv[4];
  int8_T tmp_data[4];
  B_0[0] = rtu_tau[0];
  B_0[1] = rtu_tau[1];
  B_0[2] = rtu_tau[2];
  B_0[3] = rtu_tau[3];
  std::memcpy(&A[0], &rtP.B_eff[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (int32_T j{0}; j < 3; j++) {
    int32_T e;
    int32_T jA;
    int8_T ipiv_0;
    jj = j * 5;
    n = 5 - j;
    jA = 0;
    smax = std::abs(A[jj]);
    for (kAcol = 2; kAcol < n; kAcol++) {
      real_T s;
      s = std::abs(A[(jj + kAcol) - 1]);
      if (s > smax) {
        jA = kAcol - 1;
        smax = s;
      }
    }

    if (A[jj + jA] != 0.0) {
      if (jA != 0) {
        kAcol = j + jA;
        ipiv[j] = static_cast<int8_T>(kAcol + 1);
        smax = A[j];
        A[j] = A[kAcol];
        A[kAcol] = smax;
        smax = A[j + 4];
        A[j + 4] = A[kAcol + 4];
        A[kAcol + 4] = smax;
        smax = A[j + 8];
        A[j + 8] = A[kAcol + 8];
        A[kAcol + 8] = smax;
        smax = A[j + 12];
        A[j + 12] = A[kAcol + 12];
        A[kAcol + 12] = smax;
      }

      n = (jj - j) + 4;
      for (kAcol = jj + 2; kAcol <= n; kAcol++) {
        A[kAcol - 1] /= A[jj];
      }
    }

    jA = jj + 6;
    e = 2 - j;
    for (kAcol = 0; kAcol <= e; kAcol++) {
      smax = A[((kAcol << 2) + jj) + 4];
      if (smax != 0.0) {
        int32_T f;
        f = (jA - j) + 2;
        for (n = jA; n <= f; n++) {
          A[n - 1] += A[((jj + n) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[j];
    if (j + 1 != ipiv_0) {
      smax = B_0[j];
      B_0[j] = B_0[ipiv_0 - 1];
      B_0[ipiv_0 - 1] = smax;
    }
  }

  for (int32_T j{0}; j < 4; j++) {
    kAcol = j << 2;
    if (B_0[j] != 0.0) {
      for (jj = j + 2; jj < 5; jj++) {
        B_0[jj - 1] -= A[(jj + kAcol) - 1] * B_0[j];
      }
    }
  }

  for (int32_T j{3}; j >= 0; j--) {
    kAcol = j << 2;
    smax = B_0[j];
    if (smax != 0.0) {
      B_0[j] = smax / A[j + kAcol];
      for (jj = 0; jj < j; jj++) {
        B_0[jj] -= A[jj + kAcol] * B_0[j];
      }
    }
  }

  rty_u[0] = 0.0;
  rty_u[1] = 0.0;
  rty_u[2] = 0.0;
  rty_u[3] = 0.0;
  jj = 0;
  for (int32_T j{0}; j < 4; j++) {
    if (B_0[j] / rtP.a >= 0.0) {
      jj++;
    }
  }

  n = jj;
  jj = 0;
  for (int32_T j{0}; j < 4; j++) {
    if (B_0[j] / rtP.a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(j);
      jj++;
    }
  }

  for (int32_T j{0}; j < n; j++) {
    c_data[j] = B_0[tmp_data[j]] / rtP.a;
    c_data[j] = std::sqrt(c_data[j]);
    rty_u[tmp_data[j]] = c_data[j] + rtP.b;
  }
}

//
// Output and update for atomic system:
//    '<S336>/KF_Elevation'
//    '<S337>/KF_Elevation'
//    '<S338>/KF_Elevation'
//    '<S342>/KF_Elevation'
//    '<S343>/KF_Elevation'
//    '<S344>/KF_Elevation'
//    '<S674>/KF_Elevation'
//    '<S675>/KF_Elevation'
//    '<S676>/KF_Elevation'
//    '<S680>/KF_Elevation'
//    ...
//
void Controller6dof::KF_Elevation(const real_T rtu_A[4], const real_T rtu_B[2],
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
void Controller6dof::step()
{
  real_T dx_c_tmp_3[9];
  real_T dx_c_tmp_4[9];
  real_T dx_c_tmp_5[9];
  real_T rtb_TmpSignalConversionAtGainIn[6];
  real_T rtb_VectorConcatenate1[4];
  real_T rtb_thrust[4];
  real_T y_e[4];
  real_T B_1[3];
  real_T tmp_0[3];
  real_T RateTransition;
  real_T RateTransition_0;
  real_T RateTransition_1;
  real_T dx_c_tmp;
  real_T dx_c_tmp_0;
  real_T dx_c_tmp_1;
  real_T dx_c_tmp_2;
  real_T maxval;
  real_T rtb_Sum1_h;
  real_T rtb_Sum2;
  real_T rtb_Sum_l5;
  real_T tau_idx_0;
  real_T tau_idx_1;
  real_T tau_idx_2;
  int32_T i;
  int32_T r1;
  int32_T r3;
  int32_T rtemp;
  boolean_T tmp;
  static const int8_T b[3]{ 0, 0, 1 };

  static const int8_T c[3]{ 0, 1, 0 };

  static const int8_T d[3]{ 1, 0, 0 };

  if ((&rtM)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&rtM)->isMinorTimeStep()) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  tmp = ((&rtM)->isMajorTimeStep() &&
         (&rtM)->Timing.TaskCounters.TID[1] == 0);
  if (tmp) {
    // UnitDelay: '<S336>/Unit Delay1'
    rtDW.x_dach_fe[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_fe[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S336>/KF_Elevation' incorporates:
    //   Constant: '<S336>/Constant'
    //   Constant: '<S336>/Constant1'
    //   Constant: '<S336>/Constant2'
    //   Constant: '<S336>/Constant5'
    //   Constant: '<S336>/Cov Messrauschen'
    //   Constant: '<S336>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S336>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_b2, rtP.Constant1_Value_e,
                 rtP.Constant2_Value_n, rtP.CovProzessrauschen_Value_l,
                 rtP.CovMessrauschen_Value_k, rtU.y[3], rtP.Constant5_Value_j,
                 rtDW.UnitDelay_DSTATE, rtDW.x_dach_fe, rtDW.P_h);

    // UnitDelay: '<S337>/Unit Delay1'
    rtDW.x_dach_l[0] = rtDW.UnitDelay1_DSTATE_h[0];
    rtDW.x_dach_l[1] = rtDW.UnitDelay1_DSTATE_h[1];

    // MATLAB Function: '<S337>/KF_Elevation' incorporates:
    //   Constant: '<S337>/Constant'
    //   Constant: '<S337>/Constant1'
    //   Constant: '<S337>/Constant2'
    //   Constant: '<S337>/Constant5'
    //   Constant: '<S337>/Cov Messrauschen'
    //   Constant: '<S337>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S337>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_o,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_cd,
                 rtP.CovMessrauschen_Value_mi, rtU.y[4], rtP.Constant5_Value_e,
                 rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_l, rtDW.P_jh);

    // UnitDelay: '<S338>/Unit Delay1'
    rtDW.x_dach_m[0] = rtDW.UnitDelay1_DSTATE_i[0];
    rtDW.x_dach_m[1] = rtDW.UnitDelay1_DSTATE_i[1];

    // MATLAB Function: '<S338>/KF_Elevation' incorporates:
    //   Constant: '<S338>/Constant'
    //   Constant: '<S338>/Constant1'
    //   Constant: '<S338>/Constant2'
    //   Constant: '<S338>/Constant5'
    //   Constant: '<S338>/Cov Messrauschen'
    //   Constant: '<S338>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S338>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_g, rtP.Constant1_Value_f,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_kq, rtU.y[5], rtP.Constant5_Value_cj,
                 rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_m, rtDW.P_j);

    // SignalConversion generated from: '<S175>/Gain'
    rtb_TmpSignalConversionAtGainIn[0] = rtDW.x_dach_fe[0];
    rtb_TmpSignalConversionAtGainIn[1] = rtDW.x_dach_l[0];
    rtb_TmpSignalConversionAtGainIn[2] = rtDW.x_dach_m[0];
    rtb_TmpSignalConversionAtGainIn[3] = rtDW.x_dach_fe[1];
    rtb_TmpSignalConversionAtGainIn[4] = rtDW.x_dach_l[1];
    rtb_TmpSignalConversionAtGainIn[5] = rtDW.x_dach_m[1];

    // Sum: '<S11>/Sum2' incorporates:
    //   Inport: '<Root>/w'
    //   Inport: '<Root>/y'

    rtb_Sum_l5 = rtU.w[2] - rtU.y[2];

    // Gain: '<S160>/Proportional Gain'
    rtDW.ProportionalGain = rtP.kp_z * rtb_Sum_l5;

    // Gain: '<S148>/Derivative Gain'
    rtDW.DerivativeGain = rtP.kd_z * rtb_Sum_l5;

    // Sum: '<S11>/Sum1' incorporates:
    //   Inport: '<Root>/w'
    //   Inport: '<Root>/y'

    rtb_Sum1_h = rtU.y[1] - rtU.w[1];

    // Gain: '<S108>/Proportional Gain'
    rtDW.ProportionalGain_p = rtP.kp_y * rtb_Sum1_h;

    // Gain: '<S96>/Derivative Gain'
    rtDW.DerivativeGain_d = rtP.kd_y * rtb_Sum1_h;

    // Sum: '<S11>/Sum' incorporates:
    //   Inport: '<Root>/w'
    //   Inport: '<Root>/y'

    rtb_Sum2 = rtU.w[0] - rtU.y[0];

    // Gain: '<S56>/Proportional Gain'
    rtDW.ProportionalGain_c = rtP.kp_x * rtb_Sum2;

    // Gain: '<S44>/Derivative Gain'
    rtDW.DerivativeGain_b = rtP.kd_x * rtb_Sum2;
  }

  // Gain: '<S158>/Filter Coefficient' incorporates:
  //   Integrator: '<S150>/Filter'
  //   Sum: '<S150>/SumD'

  rtDW.FilterCoefficient = (rtDW.DerivativeGain - rtX.Filter_CSTATE) * rtP.N_pos;

  // Gain: '<S106>/Filter Coefficient' incorporates:
  //   Integrator: '<S98>/Filter'
  //   Sum: '<S98>/SumD'

  rtDW.FilterCoefficient_n = (rtDW.DerivativeGain_d - rtX.Filter_CSTATE_b) *
    rtP.N_pos;

  // Gain: '<S54>/Filter Coefficient' incorporates:
  //   Integrator: '<S46>/Filter'
  //   Sum: '<S46>/SumD'

  rtDW.FilterCoefficient_m = (rtDW.DerivativeGain_b - rtX.Filter_CSTATE_f) *
    rtP.N_pos;

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Constant: '<S11>/Constant'
  //   Inport: '<Root>/w'
  //   Integrator: '<S103>/Integrator'
  //   Integrator: '<S155>/Integrator'
  //   Integrator: '<S51>/Integrator'
  //   Sum: '<S112>/Sum'
  //   Sum: '<S11>/Sum3'
  //   Sum: '<S164>/Sum'
  //   Sum: '<S60>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtDW.ProportionalGain + rtX.Integrator_CSTATE)
    + rtDW.FilterCoefficient), (rtDW.ProportionalGain_p +
    rtX.Integrator_CSTATE_b) + rtDW.FilterCoefficient_n,
                 (rtDW.ProportionalGain_c + rtX.Integrator_CSTATE_m) +
                 rtDW.FilterCoefficient_m, rtU.w[3], y_e);

  // RateTransition: '<S2>/Rate Transition'
  if (tmp) {
    // RateTransition: '<S2>/Rate Transition'
    rtDW.RateTransition[0] = y_e[0];
    rtDW.RateTransition[1] = y_e[1];
    rtDW.RateTransition[2] = y_e[2];
    rtDW.RateTransition[3] = y_e[3];

    // Gain: '<S175>/Gain'
    tau_idx_1 = 0.0;
    tau_idx_2 = 0.0;
    tau_idx_0 = 0.0;
    for (i = 0; i < 6; i++) {
      maxval = rtb_TmpSignalConversionAtGainIn[i];
      tau_idx_1 += rtP.K_free_rot[3 * i] * maxval;
      tau_idx_2 += rtP.K_free_rot[3 * i + 1] * maxval;
      tau_idx_0 += rtP.K_free_rot[3 * i + 2] * maxval;
    }

    rtDW.Gain[2] = tau_idx_0;
    rtDW.Gain[1] = tau_idx_2;
    rtDW.Gain[0] = tau_idx_1;

    // End of Gain: '<S175>/Gain'
  }

  // End of RateTransition: '<S2>/Rate Transition'

  // SignalConversion generated from: '<S12>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate1'

  rtb_VectorConcatenate1[0] = rtDW.RateTransition[0];

  // SignalConversion generated from: '<S2>/Vector Concatenate' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'

  rtDW.VectorConcatenate[0] = y_e[0];
  rtDW.VectorConcatenate[1] = y_e[1];
  rtDW.VectorConcatenate[2] = y_e[2];
  rtDW.VectorConcatenate[3] = y_e[3];

  // Sum: '<S175>/Sum2' incorporates:
  //   Gain: '<S175>/Gain1'

  RateTransition = rtDW.RateTransition[2];
  RateTransition_0 = rtDW.RateTransition[1];
  RateTransition_1 = rtDW.RateTransition[3];

  // Gain: '<S175>/Gain2'
  maxval = 0.0;
  tau_idx_1 = 0.0;
  tau_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    // Sum: '<S175>/Sum2' incorporates:
    //   Gain: '<S175>/Gain1'

    tmp_0[i] = ((rtP.S_free_rot[i + 3] * RateTransition + rtP.S_free_rot[i] *
                 RateTransition_0) + rtP.S_free_rot[i + 6] * RateTransition_1) -
      rtDW.Gain[i];

    // Gain: '<S175>/Gain2' incorporates:
    //   Integrator: '<S175>/Integrator'

    tau_idx_0 = rtX.Integrator_CSTATE_a[i];
    maxval += rtP.Ki_free_rot[3 * i] * tau_idx_0;
    tau_idx_1 += rtP.Ki_free_rot[3 * i + 1] * tau_idx_0;
    tau_idx_2 += rtP.Ki_free_rot[3 * i + 2] * tau_idx_0;
  }

  // Sum: '<S175>/Sum2' incorporates:
  //   Concatenate: '<S12>/Vector Concatenate1'
  //   Gain: '<S175>/Gain2'

  rtb_VectorConcatenate1[1] = tmp_0[0] - maxval;
  rtb_VectorConcatenate1[2] = tmp_0[1] - tau_idx_1;
  rtb_VectorConcatenate1[3] = tmp_0[2] - tau_idx_2;

  // MATLAB Function: '<S173>/MATLAB Function'
  MATLABFunction_e(rtb_VectorConcatenate1, y_e);

  // Saturate: '<S173>/Saturation'
  if (y_e[0] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_UpperSat;
  } else if (y_e[0] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = y_e[0];
  }

  if (y_e[1] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_UpperSat;
  } else if (y_e[1] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = y_e[1];
  }

  if (y_e[2] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_UpperSat;
  } else if (y_e[2] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = y_e[2];
  }

  if (y_e[3] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_UpperSat;
  } else if (y_e[3] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = y_e[3];
  }

  // End of Saturate: '<S173>/Saturation'

  // Sum: '<S175>/Sum'
  rtDW.Sum[0] = rtDW.RateTransition[1] - rtDW.x_dach_fe[0];
  rtDW.Sum[1] = rtDW.RateTransition[2] - rtDW.x_dach_l[0];
  rtDW.Sum[2] = rtDW.RateTransition[3] - rtDW.x_dach_m[0];
  if (tmp) {
    // Gain: '<S48>/Integral Gain'
    rtDW.IntegralGain = rtP.ki_x * rtb_Sum2;

    // Gain: '<S100>/Integral Gain'
    rtDW.IntegralGain_f = rtP.ki_y * rtb_Sum1_h;

    // Gain: '<S152>/Integral Gain'
    rtDW.IntegralGain_l = rtP.ki_z * rtb_Sum_l5;

    // Constant: '<S2>/Constant1' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate'

    rtDW.VectorConcatenate[4] = rtP.Constant1_Value_ot[0];
    rtDW.VectorConcatenate[5] = rtP.Constant1_Value_ot[1];
  }

  for (i = 0; i < 6; i++) {
    // Outport: '<Root>/values'
    rtY.values[i] = rtDW.VectorConcatenate[i];

    // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
    //   Integrator: '<S4>/Integrator'
    //   Outport: '<Root>/x_pred'

    rtY.x_pred[i] = rtX.Integrator_CSTATE_e[i];
  }

  if (tmp) {
    // Sum: '<S349>/Sum2' incorporates:
    //   Inport: '<Root>/w'
    //   Integrator: '<S4>/Integrator'

    rtb_Sum2 = rtU.w[2] - rtX.Integrator_CSTATE_e[2];

    // Gain: '<S498>/Proportional Gain'
    rtDW.ProportionalGain_l = rtP.kp_z * rtb_Sum2;

    // Gain: '<S486>/Derivative Gain'
    rtDW.DerivativeGain_i = rtP.kd_z * rtb_Sum2;

    // Sum: '<S349>/Sum1' incorporates:
    //   Inport: '<Root>/w'
    //   Integrator: '<S4>/Integrator'

    rtb_Sum1_h = rtX.Integrator_CSTATE_e[1] - rtU.w[1];

    // Gain: '<S446>/Proportional Gain'
    rtDW.ProportionalGain_j = rtP.kp_y * rtb_Sum1_h;

    // Gain: '<S434>/Derivative Gain'
    rtDW.DerivativeGain_k = rtP.kd_y * rtb_Sum1_h;

    // Sum: '<S349>/Sum' incorporates:
    //   Inport: '<Root>/w'
    //   Integrator: '<S4>/Integrator'

    rtb_Sum_l5 = rtU.w[0] - rtX.Integrator_CSTATE_e[0];

    // Gain: '<S394>/Proportional Gain'
    rtDW.ProportionalGain_b = rtP.kp_x * rtb_Sum_l5;

    // Gain: '<S382>/Derivative Gain'
    rtDW.DerivativeGain_io = rtP.kd_x * rtb_Sum_l5;
  }

  // Gain: '<S496>/Filter Coefficient' incorporates:
  //   Integrator: '<S488>/Filter'
  //   Sum: '<S488>/SumD'

  rtDW.FilterCoefficient_a = (rtDW.DerivativeGain_i - rtX.Filter_CSTATE_n) *
    rtP.N_pos;

  // Gain: '<S444>/Filter Coefficient' incorporates:
  //   Integrator: '<S436>/Filter'
  //   Sum: '<S436>/SumD'

  rtDW.FilterCoefficient_d = (rtDW.DerivativeGain_k - rtX.Filter_CSTATE_m) *
    rtP.N_pos;

  // Gain: '<S392>/Filter Coefficient' incorporates:
  //   Integrator: '<S384>/Filter'
  //   Sum: '<S384>/SumD'

  rtDW.FilterCoefficient_p = (rtDW.DerivativeGain_io - rtX.Filter_CSTATE_p) *
    rtP.N_pos;

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   Constant: '<S349>/Constant'
  //   Inport: '<Root>/w'
  //   Integrator: '<S389>/Integrator'
  //   Integrator: '<S441>/Integrator'
  //   Integrator: '<S493>/Integrator'
  //   Sum: '<S349>/Sum3'
  //   Sum: '<S398>/Sum'
  //   Sum: '<S450>/Sum'
  //   Sum: '<S502>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtDW.ProportionalGain_l +
    rtX.Integrator_CSTATE_bh) + rtDW.FilterCoefficient_a),
                 (rtDW.ProportionalGain_j + rtX.Integrator_CSTATE_j) +
                 rtDW.FilterCoefficient_d, (rtDW.ProportionalGain_b +
    rtX.Integrator_CSTATE_f) + rtDW.FilterCoefficient_p, rtU.w[3], y_e);

  // RateTransition: '<S3>/Rate Transition'
  if (tmp) {
    // RateTransition: '<S3>/Rate Transition'
    rtDW.RateTransition_i[0] = y_e[0];
    rtDW.RateTransition_i[1] = y_e[1];
    rtDW.RateTransition_i[2] = y_e[2];
    rtDW.RateTransition_i[3] = y_e[3];
  }

  // End of RateTransition: '<S3>/Rate Transition'

  // SignalConversion generated from: '<S350>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S350>/Vector Concatenate1'

  rtb_VectorConcatenate1[0] = rtDW.RateTransition_i[0];
  if (tmp) {
    // UnitDelay: '<S674>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE_j[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE_j[1];

    // MATLAB Function: '<S674>/KF_Elevation' incorporates:
    //   Constant: '<S674>/Constant'
    //   Constant: '<S674>/Constant1'
    //   Constant: '<S674>/Constant2'
    //   Constant: '<S674>/Constant5'
    //   Constant: '<S674>/Cov Messrauschen'
    //   Constant: '<S674>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S674>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_n1b, rtP.Constant1_Value_d,
                 rtP.Constant2_Value_e, rtP.CovProzessrauschen_Value_b,
                 rtP.CovMessrauschen_Value_a2, rtX.Integrator_CSTATE_h[0],
                 rtP.Constant5_Value_a, rtDW.UnitDelay_DSTATE_j, rtDW.x_dach_e,
                 rtDW.P_k);

    // UnitDelay: '<S675>/Unit Delay1'
    rtDW.x_dach_f[0] = rtDW.UnitDelay1_DSTATE_c[0];
    rtDW.x_dach_f[1] = rtDW.UnitDelay1_DSTATE_c[1];

    // MATLAB Function: '<S675>/KF_Elevation' incorporates:
    //   Constant: '<S675>/Constant'
    //   Constant: '<S675>/Constant1'
    //   Constant: '<S675>/Constant2'
    //   Constant: '<S675>/Constant5'
    //   Constant: '<S675>/Cov Messrauschen'
    //   Constant: '<S675>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S675>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_e, rtP.Constant1_Value_et,
                 rtP.Constant2_Value_gl, rtP.CovProzessrauschen_Value_a,
                 rtP.CovMessrauschen_Value_h, rtX.Integrator_CSTATE_h[1],
                 rtP.Constant5_Value_ek, rtDW.UnitDelay_DSTATE_a, rtDW.x_dach_f,
                 rtDW.P_l);

    // UnitDelay: '<S676>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S676>/KF_Elevation' incorporates:
    //   Constant: '<S676>/Constant'
    //   Constant: '<S676>/Constant1'
    //   Constant: '<S676>/Constant2'
    //   Constant: '<S676>/Constant5'
    //   Constant: '<S676>/Cov Messrauschen'
    //   Constant: '<S676>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S676>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_h, rtP.Constant1_Value_jl,
                 rtP.Constant2_Value_jg, rtP.CovProzessrauschen_Value_g,
                 rtP.CovMessrauschen_Value_j, rtX.Integrator_CSTATE_h[2],
                 rtP.Constant5_Value_ia, rtDW.UnitDelay_DSTATE_n, rtDW.x_dach,
                 rtDW.P_o);

    // SignalConversion generated from: '<S513>/Gain'
    rtb_TmpSignalConversionAtGainIn[0] = rtDW.x_dach_e[0];
    rtb_TmpSignalConversionAtGainIn[1] = rtDW.x_dach_f[0];
    rtb_TmpSignalConversionAtGainIn[2] = rtDW.x_dach[0];
    rtb_TmpSignalConversionAtGainIn[3] = rtDW.x_dach_e[1];
    rtb_TmpSignalConversionAtGainIn[4] = rtDW.x_dach_f[1];
    rtb_TmpSignalConversionAtGainIn[5] = rtDW.x_dach[1];

    // Gain: '<S513>/Gain'
    tau_idx_1 = 0.0;
    tau_idx_2 = 0.0;
    tau_idx_0 = 0.0;
    for (i = 0; i < 6; i++) {
      maxval = rtb_TmpSignalConversionAtGainIn[i];
      tau_idx_1 += rtP.K_free_rot[3 * i] * maxval;
      tau_idx_2 += rtP.K_free_rot[3 * i + 1] * maxval;
      tau_idx_0 += rtP.K_free_rot[3 * i + 2] * maxval;
    }

    rtDW.Gain_d[2] = tau_idx_0;
    rtDW.Gain_d[1] = tau_idx_2;
    rtDW.Gain_d[0] = tau_idx_1;

    // End of Gain: '<S513>/Gain'
  }

  // Sum: '<S513>/Sum2' incorporates:
  //   Gain: '<S513>/Gain1'

  RateTransition = rtDW.RateTransition_i[2];
  RateTransition_0 = rtDW.RateTransition_i[1];
  RateTransition_1 = rtDW.RateTransition_i[3];

  // Gain: '<S513>/Gain2'
  maxval = 0.0;
  tau_idx_1 = 0.0;
  tau_idx_2 = 0.0;
  for (i = 0; i < 3; i++) {
    // Sum: '<S513>/Sum2' incorporates:
    //   Gain: '<S513>/Gain1'

    tmp_0[i] = ((rtP.S_free_rot[i + 3] * RateTransition + rtP.S_free_rot[i] *
                 RateTransition_0) + rtP.S_free_rot[i + 6] * RateTransition_1) -
      rtDW.Gain_d[i];

    // Gain: '<S513>/Gain2' incorporates:
    //   Integrator: '<S513>/Integrator'

    tau_idx_0 = rtX.Integrator_CSTATE_n[i];
    maxval += rtP.Ki_free_rot[3 * i] * tau_idx_0;
    tau_idx_1 += rtP.Ki_free_rot[3 * i + 1] * tau_idx_0;
    tau_idx_2 += rtP.Ki_free_rot[3 * i + 2] * tau_idx_0;
  }

  // Sum: '<S513>/Sum2' incorporates:
  //   Concatenate: '<S350>/Vector Concatenate1'
  //   Gain: '<S513>/Gain2'

  rtb_VectorConcatenate1[1] = tmp_0[0] - maxval;
  rtb_VectorConcatenate1[2] = tmp_0[1] - tau_idx_1;
  rtb_VectorConcatenate1[3] = tmp_0[2] - tau_idx_2;

  // MATLAB Function: '<S511>/MATLAB Function'
  MATLABFunction_e(rtb_VectorConcatenate1, y_e);

  // Saturate: '<S511>/Saturation'
  if (y_e[0] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (y_e[0] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = y_e[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  RateTransition = maxval - rtP.b;
  rtb_thrust[0] = RateTransition * RateTransition;

  // Saturate: '<S511>/Saturation'
  if (y_e[1] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (y_e[1] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = y_e[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  RateTransition = maxval - rtP.b;
  rtb_thrust[1] = RateTransition * RateTransition;

  // Saturate: '<S511>/Saturation'
  if (y_e[2] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (y_e[2] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = y_e[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  RateTransition = maxval - rtP.b;
  rtb_thrust[2] = RateTransition * RateTransition;

  // Saturate: '<S511>/Saturation'
  if (y_e[3] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (y_e[3] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = y_e[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  RateTransition = maxval - rtP.b;
  rtb_thrust[3] = RateTransition * RateTransition;

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  RateTransition = 0.0;
  tau_idx_0 = 0.0;
  tau_idx_1 = 0.0;
  tau_idx_2 = 0.0;
  for (i = 0; i < 4; i++) {
    maxval = rtP.a * rtb_thrust[i];
    r1 = i << 2;
    RateTransition += rtP.B_eff[r1] * maxval;
    tau_idx_0 += rtP.B_eff[r1 + 1] * maxval;
    tau_idx_1 += rtP.B_eff[r1 + 2] * maxval;
    tau_idx_2 += rtP.B_eff[r1 + 3] * maxval;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'
  //   Integrator: '<S6>/Integrator'

  RateTransition_0 = 1.0 / rtP.m;
  RateTransition_1 = std::sin(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp = std::cos(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_0 = std::sin(rtX.Integrator_CSTATE_h[1]);
  maxval = std::cos(rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_1 = std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_2 = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_3[0] = dx_c_tmp;
  dx_c_tmp_3[3] = -RateTransition_1;
  dx_c_tmp_3[6] = 0.0;
  dx_c_tmp_3[1] = RateTransition_1;
  dx_c_tmp_3[4] = dx_c_tmp;
  dx_c_tmp_3[7] = 0.0;
  dx_c_tmp_4[0] = maxval;
  dx_c_tmp_4[3] = 0.0;
  dx_c_tmp_4[6] = dx_c_tmp_0;
  dx_c_tmp_4[2] = -dx_c_tmp_0;
  dx_c_tmp_4[5] = 0.0;
  dx_c_tmp_4[8] = maxval;
  for (i = 0; i < 3; i++) {
    r1 = 3 * i + 2;
    dx_c_tmp_3[r1] = b[i];
    r3 = 3 * i + 1;
    dx_c_tmp_4[r3] = c[i];
    dx_c_tmp_5[3 * i] = 0.0;
    dx_c_tmp_5[r3] = 0.0;
    dx_c_tmp_5[r1] = 0.0;
  }

  for (i = 0; i < 3; i++) {
    RateTransition_1 = dx_c_tmp_5[3 * i];
    r1 = 3 * i + 1;
    dx_c_tmp = dx_c_tmp_5[r1];
    r3 = 3 * i + 2;
    dx_c_tmp_0 = dx_c_tmp_5[r3];
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_4[3 * i + rtemp];
      RateTransition_1 += dx_c_tmp_3[3 * rtemp] * maxval;
      dx_c_tmp += dx_c_tmp_3[3 * rtemp + 1] * maxval;
      dx_c_tmp_0 += dx_c_tmp_3[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_5[r3] = dx_c_tmp_0;
    dx_c_tmp_5[r1] = dx_c_tmp;
    dx_c_tmp_5[3 * i] = RateTransition_1;
  }

  dx_c_tmp_4[1] = 0.0;
  dx_c_tmp_4[4] = dx_c_tmp_2;
  dx_c_tmp_4[7] = -dx_c_tmp_1;
  dx_c_tmp_4[2] = 0.0;
  dx_c_tmp_4[5] = dx_c_tmp_1;
  dx_c_tmp_4[8] = dx_c_tmp_2;
  for (i = 0; i < 3; i++) {
    dx_c_tmp_4[3 * i] = d[i];
    RateTransition_1 = 0.0;
    dx_c_tmp = 0.0;
    dx_c_tmp_0 = 0.0;
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_4[3 * i + rtemp];
      RateTransition_1 += dx_c_tmp_5[3 * rtemp] * maxval;
      dx_c_tmp += dx_c_tmp_5[3 * rtemp + 1] * maxval;
      dx_c_tmp_0 += dx_c_tmp_5[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_3[3 * i + 2] = dx_c_tmp_0;
    dx_c_tmp_3[3 * i + 1] = dx_c_tmp;
    dx_c_tmp_3[3 * i] = RateTransition_1;
  }

  for (i = 0; i < 9; i++) {
    dx_c_tmp_5[i] = RateTransition_0 * dx_c_tmp_3[i];
  }

  tmp_0[0] = 0.0;
  tmp_0[1] = 0.0;
  tmp_0[2] = RateTransition;
  RateTransition = 0.0;
  RateTransition_0 = 0.0;
  RateTransition_1 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = tmp_0[i];
    RateTransition += dx_c_tmp_5[3 * i] * maxval;
    RateTransition_0 += dx_c_tmp_5[3 * i + 1] * maxval;
    RateTransition_1 += dx_c_tmp_5[3 * i + 2] * maxval;
    rtDW.dx_c[i] = rtX.Integrator_CSTATE_e[i + 3];
  }

  rtDW.dx_c[3] = RateTransition;
  rtDW.dx_c[4] = RateTransition_0;
  rtDW.dx_c[5] = -rtP.g + RateTransition_1;

  // End of MATLAB Function: '<S4>/MATLAB Function2'

  // MATLAB Function: '<S6>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S6>/Integrator'

  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[0]) * std::cos
      (rtX.Integrator_CSTATE_h[1]) * rtP.h;
    tau_idx_1 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[1]) * rtP.h;
  }

  RateTransition = 0.0;
  RateTransition_0 = 0.0;
  RateTransition_1 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtX.Integrator_CSTATE_h[i + 3];
    RateTransition += rtP.J[3 * i] * maxval;
    RateTransition_0 += rtP.J[3 * i + 1] * maxval;
    RateTransition_1 += rtP.J[3 * i + 2] * maxval;
  }

  std::memcpy(&dx_c_tmp_3[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = tau_idx_0 - (RateTransition_1 * rtX.Integrator_CSTATE_h[4] -
                        RateTransition_0 * rtX.Integrator_CSTATE_h[5]);
  B_1[1] = tau_idx_1 - (RateTransition * rtX.Integrator_CSTATE_h[5] -
                        RateTransition_1 * rtX.Integrator_CSTATE_h[3]);
  B_1[2] = tau_idx_2 - (RateTransition_0 * rtX.Integrator_CSTATE_h[3] -
                        RateTransition * rtX.Integrator_CSTATE_h[4]);
  r1 = 0;
  i = 1;
  r3 = 2;
  maxval = std::abs(rtP.J[0]);
  tau_idx_1 = std::abs(rtP.J[1]);
  if (tau_idx_1 > maxval) {
    maxval = tau_idx_1;
    r1 = 1;
    i = 0;
  }

  if (std::abs(rtP.J[2]) > maxval) {
    r1 = 2;
    i = 1;
    r3 = 0;
  }

  dx_c_tmp_3[i] = rtP.J[i] / rtP.J[r1];
  dx_c_tmp_3[r3] /= dx_c_tmp_3[r1];
  dx_c_tmp_3[i + 3] -= dx_c_tmp_3[r1 + 3] * dx_c_tmp_3[i];
  dx_c_tmp_3[r3 + 3] -= dx_c_tmp_3[r1 + 3] * dx_c_tmp_3[r3];
  dx_c_tmp_3[i + 6] -= dx_c_tmp_3[r1 + 6] * dx_c_tmp_3[i];
  dx_c_tmp_3[r3 + 6] -= dx_c_tmp_3[r1 + 6] * dx_c_tmp_3[r3];
  if (std::abs(dx_c_tmp_3[r3 + 3]) > std::abs(dx_c_tmp_3[i + 3])) {
    rtemp = i;
    i = r3;
    r3 = rtemp;
  }

  dx_c_tmp_3[r3 + 3] /= dx_c_tmp_3[i + 3];
  dx_c_tmp_3[r3 + 6] -= dx_c_tmp_3[r3 + 3] * dx_c_tmp_3[i + 6];
  tau_idx_1 = B_1[i] - B_1[r1] * dx_c_tmp_3[i];
  tau_idx_2 = ((B_1[r3] - B_1[r1] * dx_c_tmp_3[r3]) - dx_c_tmp_3[r3 + 3] *
               tau_idx_1) / dx_c_tmp_3[r3 + 6];
  tau_idx_1 = (tau_idx_1 - dx_c_tmp_3[i + 6] * tau_idx_2) / dx_c_tmp_3[i + 3];
  dx_c_tmp_5[0] = 1.0;
  dx_c_tmp_5[3] = std::sin(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_5[6] = std::cos(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_5[1] = 0.0;
  dx_c_tmp_5[4] = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_5[7] = -std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_5[2] = 0.0;
  dx_c_tmp_5[5] = std::sin(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_5[8] = std::cos(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  tau_idx_0 = 0.0;
  RateTransition = 0.0;
  RateTransition_0 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtX.Integrator_CSTATE_h[i + 3];
    tau_idx_0 += dx_c_tmp_5[3 * i] * maxval;
    RateTransition += dx_c_tmp_5[3 * i + 1] * maxval;
    RateTransition_0 += dx_c_tmp_5[3 * i + 2] * maxval;
  }

  rtDW.dx[0] = tau_idx_0;
  rtDW.dx[3] = ((B_1[r1] - dx_c_tmp_3[r1 + 6] * tau_idx_2) - dx_c_tmp_3[r1 + 3] *
                tau_idx_1) / dx_c_tmp_3[r1];
  rtDW.dx[1] = RateTransition;
  rtDW.dx[4] = tau_idx_1;
  rtDW.dx[2] = RateTransition_0;
  rtDW.dx[5] = tau_idx_2;

  // End of MATLAB Function: '<S6>/MATLAB Function2'

  // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
  //   Integrator: '<S6>/Integrator'
  //   Outport: '<Root>/x_pred'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i + 6] = rtX.Integrator_CSTATE_h[i];
  }

  // Sum: '<S513>/Sum'
  rtDW.Sum_j[0] = rtDW.RateTransition_i[1] - rtDW.x_dach_e[0];
  rtDW.Sum_j[1] = rtDW.RateTransition_i[2] - rtDW.x_dach_f[0];
  rtDW.Sum_j[2] = rtDW.RateTransition_i[3] - rtDW.x_dach[0];
  if (tmp) {
    // Gain: '<S386>/Integral Gain'
    rtDW.IntegralGain_h = rtP.ki_x * rtb_Sum_l5;

    // Gain: '<S438>/Integral Gain'
    rtDW.IntegralGain_l4 = rtP.ki_y * rtb_Sum1_h;

    // Gain: '<S490>/Integral Gain'
    rtDW.IntegralGain_fl = rtP.ki_z * rtb_Sum2;
  }

  if ((&rtM)->isMajorTimeStep() &&
      (&rtM)->Timing.TaskCounters.TID[2] == 0) {
    // Outputs for Atomic SubSystem: '<S2>/Subsystem Reference1'
    // UnitDelay: '<S342>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_nf[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_nf[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_nf[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_nf[3];

    // MATLAB Function: '<S342>/KF_Elevation' incorporates:
    //   Constant: '<S342>/Constant'
    //   Constant: '<S342>/Constant1'
    //   Constant: '<S342>/Constant2'
    //   Constant: '<S342>/Constant5'
    //   Constant: '<S342>/Cov Messrauschen'
    //   Constant: '<S342>/Cov Prozessrauschen'
    //   UnitDelay: '<S342>/Unit Delay'
    //   UnitDelay: '<S342>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, 0.0,
                 rtP.Constant5_Value, rtb_thrust, rtDW.UnitDelay1_DSTATE_o,
                 rtDW.UnitDelay_DSTATE_nf);

    // UnitDelay: '<S343>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_ax[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_ax[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_ax[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_ax[3];

    // MATLAB Function: '<S343>/KF_Elevation' incorporates:
    //   Constant: '<S343>/Constant'
    //   Constant: '<S343>/Constant1'
    //   Constant: '<S343>/Constant2'
    //   Constant: '<S343>/Constant5'
    //   Constant: '<S343>/Cov Messrauschen'
    //   Constant: '<S343>/Cov Prozessrauschen'
    //   UnitDelay: '<S343>/Unit Delay'
    //   UnitDelay: '<S343>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_j,
                 rtP.Constant2_Value_i, rtP.CovProzessrauschen_Value_f,
                 rtP.CovMessrauschen_Value_a, 0.0, rtP.Constant5_Value_p,
                 rtb_thrust, rtDW.UnitDelay1_DSTATE_d, rtDW.UnitDelay_DSTATE_ax);

    // UnitDelay: '<S344>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_oo[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_oo[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_oo[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_oo[3];

    // MATLAB Function: '<S344>/KF_Elevation' incorporates:
    //   Constant: '<S344>/Constant'
    //   Constant: '<S344>/Constant1'
    //   Constant: '<S344>/Constant2'
    //   Constant: '<S344>/Constant5'
    //   Constant: '<S344>/Cov Messrauschen'
    //   Constant: '<S344>/Cov Prozessrauschen'
    //   UnitDelay: '<S344>/Unit Delay'
    //   UnitDelay: '<S344>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value_n, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_g, rtP.CovProzessrauschen_Value_c,
                 rtP.CovMessrauschen_Value_e, 0.0, rtP.Constant5_Value_o,
                 rtb_thrust, rtDW.UnitDelay1_DSTATE_co, rtDW.UnitDelay_DSTATE_oo);

    // Update for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' incorporates:
    //   SignalConversion generated from: '<S13>/w'
    //   Sum: '<S13>/Sum'
    //   UnitDelay: '<S342>/Unit Delay1'
    //   UnitDelay: '<S343>/Unit Delay1'
    //   UnitDelay: '<S344>/Unit Delay1'

    maxval = rtDW.DiscreteTimeIntegrator_DSTATE_b[0];
    tau_idx_1 = rtDW.DiscreteTimeIntegrator_DSTATE_b[1];
    tau_idx_2 = rtDW.DiscreteTimeIntegrator_DSTATE_b[2];
    rtDW.DiscreteTimeIntegrator_DSTATE_b[0] = (0.0 - rtDW.UnitDelay1_DSTATE_o[0])
      * rtP.DiscreteTimeIntegrator_gainval + maxval;
    rtDW.DiscreteTimeIntegrator_DSTATE_b[1] = (0.0 - rtDW.UnitDelay1_DSTATE_d[0])
      * rtP.DiscreteTimeIntegrator_gainval + tau_idx_1;
    rtDW.DiscreteTimeIntegrator_DSTATE_b[2] = (0.0 - rtDW.UnitDelay1_DSTATE_co[0])
      * rtP.DiscreteTimeIntegrator_gainval + tau_idx_2;

    // End of Outputs for SubSystem: '<S2>/Subsystem Reference1'

    // Outputs for Atomic SubSystem: '<S3>/Subsystem Reference1'
    // UnitDelay: '<S680>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_k[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_k[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_k[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_k[3];

    // MATLAB Function: '<S680>/KF_Elevation' incorporates:
    //   Constant: '<S680>/Constant'
    //   Constant: '<S680>/Constant1'
    //   Constant: '<S680>/Constant2'
    //   Constant: '<S680>/Constant5'
    //   Constant: '<S680>/Cov Messrauschen'
    //   Constant: '<S680>/Cov Prozessrauschen'
    //   UnitDelay: '<S680>/Unit Delay'
    //   UnitDelay: '<S680>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value_b, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_f, rtP.CovProzessrauschen_Value_d,
                 rtP.CovMessrauschen_Value_i, 0.0, rtP.Constant5_Value_c,
                 rtb_thrust, rtDW.UnitDelay1_DSTATE_f, rtDW.UnitDelay_DSTATE_k);

    // UnitDelay: '<S681>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_p[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_p[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_p[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_p[3];

    // MATLAB Function: '<S681>/KF_Elevation' incorporates:
    //   Constant: '<S681>/Constant'
    //   Constant: '<S681>/Constant1'
    //   Constant: '<S681>/Constant2'
    //   Constant: '<S681>/Constant5'
    //   Constant: '<S681>/Cov Messrauschen'
    //   Constant: '<S681>/Cov Prozessrauschen'
    //   UnitDelay: '<S681>/Unit Delay'
    //   UnitDelay: '<S681>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value_n1, rtP.Constant1_Value_n,
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_dl,
                 rtP.CovMessrauschen_Value_m, 0.0, rtP.Constant5_Value_i,
                 rtb_thrust, rtDW.UnitDelay1_DSTATE_e, rtDW.UnitDelay_DSTATE_p);

    // UnitDelay: '<S682>/Unit Delay'
    rtb_thrust[0] = rtDW.UnitDelay_DSTATE_i[0];
    rtb_thrust[1] = rtDW.UnitDelay_DSTATE_i[1];
    rtb_thrust[2] = rtDW.UnitDelay_DSTATE_i[2];
    rtb_thrust[3] = rtDW.UnitDelay_DSTATE_i[3];

    // MATLAB Function: '<S682>/KF_Elevation' incorporates:
    //   Constant: '<S682>/Constant'
    //   Constant: '<S682>/Constant1'
    //   Constant: '<S682>/Constant2'
    //   Constant: '<S682>/Constant5'
    //   Constant: '<S682>/Cov Messrauschen'
    //   Constant: '<S682>/Cov Prozessrauschen'
    //   UnitDelay: '<S682>/Unit Delay'
    //   UnitDelay: '<S682>/Unit Delay1'

    KF_Elevation(rtP.Constant_Value_l, rtP.Constant1_Value_p,
                 rtP.Constant2_Value_i1, rtP.CovProzessrauschen_Value_o,
                 rtP.CovMessrauschen_Value_l, 0.0, rtP.Constant5_Value_b,
                 rtb_thrust, rtDW.UnitDelay1_DSTATE_fj, rtDW.UnitDelay_DSTATE_i);

    // Update for DiscreteIntegrator: '<S351>/Discrete-Time Integrator' incorporates:
    //   SignalConversion generated from: '<S351>/w'
    //   Sum: '<S351>/Sum'
    //   UnitDelay: '<S680>/Unit Delay1'
    //   UnitDelay: '<S681>/Unit Delay1'
    //   UnitDelay: '<S682>/Unit Delay1'

    maxval = rtDW.DiscreteTimeIntegrator_DSTATE[0];
    tau_idx_1 = rtDW.DiscreteTimeIntegrator_DSTATE[1];
    tau_idx_2 = rtDW.DiscreteTimeIntegrator_DSTATE[2];
    rtDW.DiscreteTimeIntegrator_DSTATE[0] = (0.0 - rtDW.UnitDelay1_DSTATE_f[0]) *
      rtP.DiscreteTimeIntegrator_gainva_g + maxval;
    rtDW.DiscreteTimeIntegrator_DSTATE[1] = (0.0 - rtDW.UnitDelay1_DSTATE_e[0]) *
      rtP.DiscreteTimeIntegrator_gainva_g + tau_idx_1;
    rtDW.DiscreteTimeIntegrator_DSTATE[2] = (0.0 - rtDW.UnitDelay1_DSTATE_fj[0])
      * rtP.DiscreteTimeIntegrator_gainva_g + tau_idx_2;

    // End of Outputs for SubSystem: '<S3>/Subsystem Reference1'
  }

  // Gain: '<S217>/Filter Coefficient' incorporates:
  //   Gain: '<S207>/Derivative Gain'
  //   Integrator: '<S209>/Filter'
  //   Sum: '<S209>/SumD'

  rtDW.FilterCoefficient_e = (0.0 - rtX.Filter_CSTATE_o) * rtP.N;

  // Gain: '<S211>/Integral Gain'
  rtDW.IntegralGain_o = 0.0;

  // Gain: '<S269>/Filter Coefficient' incorporates:
  //   Gain: '<S259>/Derivative Gain'
  //   Integrator: '<S261>/Filter'
  //   Sum: '<S261>/SumD'

  rtDW.FilterCoefficient_g = (0.0 - rtX.Filter_CSTATE_n4) * rtP.N;

  // Gain: '<S263>/Integral Gain'
  rtDW.IntegralGain_i = 0.0;

  // Gain: '<S321>/Filter Coefficient' incorporates:
  //   Gain: '<S311>/Derivative Gain'
  //   Integrator: '<S313>/Filter'
  //   Sum: '<S313>/SumD'

  rtDW.FilterCoefficient_af = (0.0 - rtX.Filter_CSTATE_a) * rtP.N;

  // Gain: '<S315>/Integral Gain'
  rtDW.IntegralGain_p = 0.0;

  // Gain: '<S555>/Filter Coefficient' incorporates:
  //   Gain: '<S545>/Derivative Gain'
  //   Integrator: '<S547>/Filter'
  //   Sum: '<S547>/SumD'

  rtDW.FilterCoefficient_mw = (0.0 - rtX.Filter_CSTATE_mt) * rtP.N;

  // Gain: '<S549>/Integral Gain'
  rtDW.IntegralGain_e = 0.0;

  // Gain: '<S607>/Filter Coefficient' incorporates:
  //   Gain: '<S597>/Derivative Gain'
  //   Integrator: '<S599>/Filter'
  //   Sum: '<S599>/SumD'

  rtDW.FilterCoefficient_ma = (0.0 - rtX.Filter_CSTATE_d) * rtP.N;

  // Gain: '<S601>/Integral Gain'
  rtDW.IntegralGain_k = 0.0;

  // Gain: '<S659>/Filter Coefficient' incorporates:
  //   Gain: '<S649>/Derivative Gain'
  //   Integrator: '<S651>/Filter'
  //   Sum: '<S651>/SumD'

  rtDW.FilterCoefficient_f = (0.0 - rtX.Filter_CSTATE_g) * rtP.N;

  // Gain: '<S653>/Integral Gain'
  rtDW.IntegralGain_c = 0.0;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep() &&
        (&rtM)->Timing.TaskCounters.TID[1] == 0) {
      // Update for UnitDelay: '<S336>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_fe[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_fe[1];

      // Update for UnitDelay: '<S336>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_h[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_h[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_h[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_h[3];

      // Update for UnitDelay: '<S337>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_h[0] = rtDW.x_dach_l[0];
      rtDW.UnitDelay1_DSTATE_h[1] = rtDW.x_dach_l[1];

      // Update for UnitDelay: '<S337>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_jh[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_jh[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_jh[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_jh[3];

      // Update for UnitDelay: '<S338>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_i[0] = rtDW.x_dach_m[0];
      rtDW.UnitDelay1_DSTATE_i[1] = rtDW.x_dach_m[1];

      // Update for UnitDelay: '<S338>/Unit Delay'
      rtDW.UnitDelay_DSTATE_d[0] = rtDW.P_j[0];
      rtDW.UnitDelay_DSTATE_d[1] = rtDW.P_j[1];
      rtDW.UnitDelay_DSTATE_d[2] = rtDW.P_j[2];
      rtDW.UnitDelay_DSTATE_d[3] = rtDW.P_j[3];

      // Update for UnitDelay: '<S674>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_j[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE_j[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S674>/Unit Delay'
      rtDW.UnitDelay_DSTATE_j[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_j[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_j[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_j[3] = rtDW.P_k[3];

      // Update for UnitDelay: '<S675>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_c[0] = rtDW.x_dach_f[0];
      rtDW.UnitDelay1_DSTATE_c[1] = rtDW.x_dach_f[1];

      // Update for UnitDelay: '<S675>/Unit Delay'
      rtDW.UnitDelay_DSTATE_a[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_a[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_a[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_a[3] = rtDW.P_l[3];

      // Update for UnitDelay: '<S676>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S676>/Unit Delay'
      rtDW.UnitDelay_DSTATE_n[0] = rtDW.P_o[0];
      rtDW.UnitDelay_DSTATE_n[1] = rtDW.P_o[1];
      rtDW.UnitDelay_DSTATE_n[2] = rtDW.P_o[2];
      rtDW.UnitDelay_DSTATE_n[3] = rtDW.P_o[3];
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

    rate_scheduler((&rtM));
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void Controller6dof::controller_6dof_container_derivatives()
{
  Controller6dof::XDot *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S155>/Integrator'
  _rtXdot->Integrator_CSTATE = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S150>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S103>/Integrator'
  _rtXdot->Integrator_CSTATE_b = rtDW.IntegralGain_f;

  // Derivatives for Integrator: '<S98>/Filter'
  _rtXdot->Filter_CSTATE_b = rtDW.FilterCoefficient_n;

  // Derivatives for Integrator: '<S51>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S46>/Filter'
  _rtXdot->Filter_CSTATE_f = rtDW.FilterCoefficient_m;

  // Derivatives for Integrator: '<S175>/Integrator'
  _rtXdot->Integrator_CSTATE_a[0] = rtDW.Sum[0];
  _rtXdot->Integrator_CSTATE_a[1] = rtDW.Sum[1];
  _rtXdot->Integrator_CSTATE_a[2] = rtDW.Sum[2];
  for (i = 0; i < 6; i++) {
    // Derivatives for Integrator: '<S4>/Integrator'
    _rtXdot->Integrator_CSTATE_e[i] = rtDW.dx_c[i];

    // Derivatives for Integrator: '<S6>/Integrator'
    _rtXdot->Integrator_CSTATE_h[i] = rtDW.dx[i];
  }

  // Derivatives for Integrator: '<S493>/Integrator'
  _rtXdot->Integrator_CSTATE_bh = rtDW.IntegralGain_fl;

  // Derivatives for Integrator: '<S488>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.FilterCoefficient_a;

  // Derivatives for Integrator: '<S441>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_l4;

  // Derivatives for Integrator: '<S436>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_d;

  // Derivatives for Integrator: '<S389>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_h;

  // Derivatives for Integrator: '<S384>/Filter'
  _rtXdot->Filter_CSTATE_p = rtDW.FilterCoefficient_p;

  // Derivatives for Integrator: '<S513>/Integrator'
  _rtXdot->Integrator_CSTATE_n[0] = rtDW.Sum_j[0];
  _rtXdot->Integrator_CSTATE_n[1] = rtDW.Sum_j[1];
  _rtXdot->Integrator_CSTATE_n[2] = rtDW.Sum_j[2];

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE = rtP.TransferFcn_A * rtX.TransferFcn_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE = rtP.TransferFcn1_A * rtX.TransferFcn1_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn2'
  _rtXdot->TransferFcn2_CSTATE = rtP.TransferFcn2_A * rtX.TransferFcn2_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn3'
  _rtXdot->TransferFcn3_CSTATE = rtP.TransferFcn3_A * rtX.TransferFcn3_CSTATE;

  // Derivatives for Integrator: '<S336>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_fe[1];

  // Derivatives for Integrator: '<S337>/Integrator1'
  _rtXdot->Integrator1_CSTATE_c = rtDW.x_dach_l[1];

  // Derivatives for Integrator: '<S338>/Integrator1'
  _rtXdot->Integrator1_CSTATE_i = rtDW.x_dach_m[1];

  // Derivatives for Integrator: '<S209>/Filter'
  _rtXdot->Filter_CSTATE_o = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S214>/Integrator'
  _rtXdot->Integrator_CSTATE_bg = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S261>/Filter'
  _rtXdot->Filter_CSTATE_n4 = rtDW.FilterCoefficient_g;

  // Derivatives for Integrator: '<S266>/Integrator'
  _rtXdot->Integrator_CSTATE_fs = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S313>/Filter'
  _rtXdot->Filter_CSTATE_a = rtDW.FilterCoefficient_af;

  // Derivatives for Integrator: '<S318>/Integrator'
  _rtXdot->Integrator_CSTATE_bj = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S674>/Integrator1'
  _rtXdot->Integrator1_CSTATE_n = rtDW.x_dach_e[1];

  // Derivatives for Integrator: '<S675>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_f[1];

  // Derivatives for Integrator: '<S676>/Integrator1'
  _rtXdot->Integrator1_CSTATE_o = rtDW.x_dach[1];

  // Derivatives for Integrator: '<S547>/Filter'
  _rtXdot->Filter_CSTATE_mt = rtDW.FilterCoefficient_mw;

  // Derivatives for Integrator: '<S552>/Integrator'
  _rtXdot->Integrator_CSTATE_my = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S599>/Filter'
  _rtXdot->Filter_CSTATE_d = rtDW.FilterCoefficient_ma;

  // Derivatives for Integrator: '<S604>/Integrator'
  _rtXdot->Integrator_CSTATE_bu = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S651>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_f;

  // Derivatives for Integrator: '<S656>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain_c;
}

// Model initialize function
void Controller6dof::initialize()
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

    // InitializeConditions for UnitDelay: '<S336>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition_n[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition_n[1];

    // InitializeConditions for UnitDelay: '<S336>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition_g[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition_g[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition_g[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition_g[3];

    // InitializeConditions for UnitDelay: '<S337>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_h[0] = rtP.UnitDelay1_InitialCondition_ah[0];
    rtDW.UnitDelay1_DSTATE_h[1] = rtP.UnitDelay1_InitialCondition_ah[1];

    // InitializeConditions for UnitDelay: '<S337>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_fw[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_fw[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_fw[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_fw[3];

    // InitializeConditions for UnitDelay: '<S338>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_i[0] = rtP.UnitDelay1_InitialCondition_e[0];
    rtDW.UnitDelay1_DSTATE_i[1] = rtP.UnitDelay1_InitialCondition_e[1];

    // InitializeConditions for UnitDelay: '<S338>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_a[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_a[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_a[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_a[3];

    // InitializeConditions for Integrator: '<S155>/Integrator'
    rtX.Integrator_CSTATE = rtP.PIDController2_InitialConditi_k;

    // InitializeConditions for Integrator: '<S150>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S103>/Integrator'
    rtX.Integrator_CSTATE_b = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S98>/Filter'
    rtX.Filter_CSTATE_b = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S51>/Integrator'
    rtX.Integrator_CSTATE_m = rtP.PIDController_InitialConditio_o;

    // InitializeConditions for Integrator: '<S46>/Filter'
    rtX.Filter_CSTATE_f = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S175>/Integrator'
    rtX.Integrator_CSTATE_a[0] = rtP.Integrator_IC;
    rtX.Integrator_CSTATE_a[1] = rtP.Integrator_IC;
    rtX.Integrator_CSTATE_a[2] = rtP.Integrator_IC;
    for (i = 0; i < 6; i++) {
      // InitializeConditions for Integrator: '<S4>/Integrator'
      rtX.Integrator_CSTATE_e[i] = rtP.Integrator_IC_g[i];

      // InitializeConditions for Integrator: '<S6>/Integrator'
      rtX.Integrator_CSTATE_h[i] = rtP.Integrator_IC_b[i];
    }

    // InitializeConditions for Integrator: '<S493>/Integrator'
    rtX.Integrator_CSTATE_bh = rtP.PIDController2_InitialConditi_i;

    // InitializeConditions for Integrator: '<S488>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController2_InitialConditi_a;

    // InitializeConditions for Integrator: '<S441>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController1_InitialCondit_jr;

    // InitializeConditions for Integrator: '<S436>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S389>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController_InitialConditi_a2;

    // InitializeConditions for Integrator: '<S384>/Filter'
    rtX.Filter_CSTATE_p = rtP.PIDController_InitialConditio_m;

    // InitializeConditions for UnitDelay: '<S674>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_j[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_j[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S674>/Unit Delay'
    rtDW.UnitDelay_DSTATE_j[0] = rtP.UnitDelay_InitialCondition_b[0];
    rtDW.UnitDelay_DSTATE_j[1] = rtP.UnitDelay_InitialCondition_b[1];
    rtDW.UnitDelay_DSTATE_j[2] = rtP.UnitDelay_InitialCondition_b[2];
    rtDW.UnitDelay_DSTATE_j[3] = rtP.UnitDelay_InitialCondition_b[3];

    // InitializeConditions for UnitDelay: '<S675>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_c[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_c[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S675>/Unit Delay'
    rtDW.UnitDelay_DSTATE_a[0] = rtP.UnitDelay_InitialCondition_ht[0];
    rtDW.UnitDelay_DSTATE_a[1] = rtP.UnitDelay_InitialCondition_ht[1];
    rtDW.UnitDelay_DSTATE_a[2] = rtP.UnitDelay_InitialCondition_ht[2];
    rtDW.UnitDelay_DSTATE_a[3] = rtP.UnitDelay_InitialCondition_ht[3];

    // InitializeConditions for UnitDelay: '<S676>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_ce[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_ce[1];

    // InitializeConditions for UnitDelay: '<S676>/Unit Delay'
    rtDW.UnitDelay_DSTATE_n[0] = rtP.UnitDelay_InitialCondition_m[0];
    rtDW.UnitDelay_DSTATE_n[1] = rtP.UnitDelay_InitialCondition_m[1];
    rtDW.UnitDelay_DSTATE_n[2] = rtP.UnitDelay_InitialCondition_m[2];
    rtDW.UnitDelay_DSTATE_n[3] = rtP.UnitDelay_InitialCondition_m[3];

    // InitializeConditions for Integrator: '<S513>/Integrator'
    rtX.Integrator_CSTATE_n[0] = rtP.Integrator_IC_gx;
    rtX.Integrator_CSTATE_n[1] = rtP.Integrator_IC_gx;
    rtX.Integrator_CSTATE_n[2] = rtP.Integrator_IC_gx;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn'
    rtX.TransferFcn_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn2'
    rtX.TransferFcn2_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn3'
    rtX.TransferFcn3_CSTATE = 0.0;

    // InitializeConditions for Integrator: '<S336>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S337>/Integrator1'
    rtX.Integrator1_CSTATE_c = rtP.Integrator1_IC_n;

    // InitializeConditions for Integrator: '<S338>/Integrator1'
    rtX.Integrator1_CSTATE_i = rtP.Integrator1_IC_j;

    // InitializeConditions for Integrator: '<S209>/Filter'
    rtX.Filter_CSTATE_o = rtP.PIDController_InitialConditio_i;

    // InitializeConditions for Integrator: '<S214>/Integrator'
    rtX.Integrator_CSTATE_bg = rtP.PIDController_InitialConditi_ay;

    // InitializeConditions for Integrator: '<S261>/Filter'
    rtX.Filter_CSTATE_n4 = rtP.PIDController1_InitialConditi_n;

    // InitializeConditions for Integrator: '<S266>/Integrator'
    rtX.Integrator_CSTATE_fs = rtP.PIDController1_InitialCondit_nz;

    // InitializeConditions for Integrator: '<S313>/Filter'
    rtX.Filter_CSTATE_a = rtP.PIDController2_InitialConditi_h;

    // InitializeConditions for Integrator: '<S318>/Integrator'
    rtX.Integrator_CSTATE_bj = rtP.PIDController2_InitialConditi_n;

    // InitializeConditions for Integrator: '<S674>/Integrator1'
    rtX.Integrator1_CSTATE_n = rtP.Integrator1_IC_h;

    // InitializeConditions for Integrator: '<S675>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S676>/Integrator1'
    rtX.Integrator1_CSTATE_o = rtP.Integrator1_IC_e;

    // InitializeConditions for Integrator: '<S547>/Filter'
    rtX.Filter_CSTATE_mt = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S552>/Integrator'
    rtX.Integrator_CSTATE_my = rtP.PIDController_InitialConditio_b;

    // InitializeConditions for Integrator: '<S599>/Filter'
    rtX.Filter_CSTATE_d = rtP.PIDController1_InitialConditi_a;

    // InitializeConditions for Integrator: '<S604>/Integrator'
    rtX.Integrator_CSTATE_bu = rtP.PIDController1_InitialConditi_b;

    // InitializeConditions for Integrator: '<S651>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController2_InitialConditi_c;

    // InitializeConditions for Integrator: '<S656>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController2_InitialCondit_k5;

    // SystemInitialize for Atomic SubSystem: '<S2>/Subsystem Reference1'
    // InitializeConditions for UnitDelay: '<S342>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_o[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE_o[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S342>/Unit Delay'
    rtDW.UnitDelay_DSTATE_nf[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE_nf[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE_nf[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE_nf[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S343>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_d[0] = rtP.UnitDelay1_InitialCondition_o[0];
    rtDW.UnitDelay1_DSTATE_d[1] = rtP.UnitDelay1_InitialCondition_o[1];

    // InitializeConditions for UnitDelay: '<S343>/Unit Delay'
    rtDW.UnitDelay_DSTATE_ax[0] = rtP.UnitDelay_InitialCondition_n[0];
    rtDW.UnitDelay_DSTATE_ax[1] = rtP.UnitDelay_InitialCondition_n[1];
    rtDW.UnitDelay_DSTATE_ax[2] = rtP.UnitDelay_InitialCondition_n[2];
    rtDW.UnitDelay_DSTATE_ax[3] = rtP.UnitDelay_InitialCondition_n[3];

    // InitializeConditions for UnitDelay: '<S344>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_co[0] = rtP.UnitDelay1_InitialCondition_p[0];
    rtDW.UnitDelay1_DSTATE_co[1] = rtP.UnitDelay1_InitialCondition_p[1];

    // InitializeConditions for UnitDelay: '<S344>/Unit Delay'
    rtDW.UnitDelay_DSTATE_oo[0] = rtP.UnitDelay_InitialCondition_h[0];
    rtDW.UnitDelay_DSTATE_oo[1] = rtP.UnitDelay_InitialCondition_h[1];
    rtDW.UnitDelay_DSTATE_oo[2] = rtP.UnitDelay_InitialCondition_h[2];
    rtDW.UnitDelay_DSTATE_oo[3] = rtP.UnitDelay_InitialCondition_h[3];

    // InitializeConditions for DiscreteIntegrator: '<S13>/Discrete-Time Integrator' 
    rtDW.DiscreteTimeIntegrator_DSTATE_b[0] = rtP.DiscreteTimeIntegrator_IC;
    rtDW.DiscreteTimeIntegrator_DSTATE_b[1] = rtP.DiscreteTimeIntegrator_IC;
    rtDW.DiscreteTimeIntegrator_DSTATE_b[2] = rtP.DiscreteTimeIntegrator_IC;

    // End of SystemInitialize for SubSystem: '<S2>/Subsystem Reference1'

    // SystemInitialize for Atomic SubSystem: '<S3>/Subsystem Reference1'
    // InitializeConditions for UnitDelay: '<S680>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_c[0];
    rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_c[1];

    // InitializeConditions for UnitDelay: '<S680>/Unit Delay'
    rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_f[0];
    rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_f[1];
    rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_f[2];
    rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_f[3];

    // InitializeConditions for UnitDelay: '<S681>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_e[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_e[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S681>/Unit Delay'
    rtDW.UnitDelay_DSTATE_p[0] = rtP.UnitDelay_InitialCondition_o[0];
    rtDW.UnitDelay_DSTATE_p[1] = rtP.UnitDelay_InitialCondition_o[1];
    rtDW.UnitDelay_DSTATE_p[2] = rtP.UnitDelay_InitialCondition_o[2];
    rtDW.UnitDelay_DSTATE_p[3] = rtP.UnitDelay_InitialCondition_o[3];

    // InitializeConditions for UnitDelay: '<S682>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_fj[0] = rtP.UnitDelay1_InitialCondition_a[0];
    rtDW.UnitDelay1_DSTATE_fj[1] = rtP.UnitDelay1_InitialCondition_a[1];

    // InitializeConditions for UnitDelay: '<S682>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_c[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_c[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_c[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_c[3];

    // InitializeConditions for DiscreteIntegrator: '<S351>/Discrete-Time Integrator' 
    rtDW.DiscreteTimeIntegrator_DSTATE[0] = rtP.DiscreteTimeIntegrator_IC_b;
    rtDW.DiscreteTimeIntegrator_DSTATE[1] = rtP.DiscreteTimeIntegrator_IC_b;
    rtDW.DiscreteTimeIntegrator_DSTATE[2] = rtP.DiscreteTimeIntegrator_IC_b;

    // End of SystemInitialize for SubSystem: '<S3>/Subsystem Reference1'
  }
}

time_T** Controller6dof::RT_MODEL::getTPtrPtr()
{
  return &(Timing.t);
}

boolean_T Controller6dof::RT_MODEL::getStopRequested() const
{
  return (Timing.stopRequestedFlag);
}

void Controller6dof::RT_MODEL::setStopRequested(boolean_T aStopRequested)
{
  (Timing.stopRequestedFlag = aStopRequested);
}

const char_T* Controller6dof::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void Controller6dof::RT_MODEL::setErrorStatus(const char_T* const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

time_T* Controller6dof::RT_MODEL::getTPtr() const
{
  return (Timing.t);
}

void Controller6dof::RT_MODEL::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

boolean_T* Controller6dof::RT_MODEL::getStopRequestedPtr()
{
  return (&(Timing.stopRequestedFlag));
}

const char_T** Controller6dof::RT_MODEL::getErrorStatusPtr()
{
  return &errorStatus;
}

boolean_T Controller6dof::RT_MODEL::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

boolean_T Controller6dof::RT_MODEL::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

time_T Controller6dof::RT_MODEL::getTStart() const
{
  return (Timing.tStart);
}

// Constructor
Controller6dof::Controller6dof() :
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
Controller6dof::~Controller6dof() = default;

// Real-Time Model get method
Controller6dof::RT_MODEL * Controller6dof::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
