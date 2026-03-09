//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.515
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Mar  9 18:46:51 2026
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
#include <cstring>
#include <cmath>

// private model entry point functions
extern void controller_6dof_container_derivatives();

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
  int_T nXc { 66 };

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
//    '<S173>/MATLAB Function'
//    '<S511>/MATLAB Function'
//
void Controller6dof::MATLABFunction(const real_T rtu_tau[4], real_T rty_u[4])
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
//    '<S174>/KF_Elevation'
//    '<S175>/KF_Elevation'
//    '<S177>/KF_Elevation'
//    '<S342>/KF_Elevation'
//    '<S343>/KF_Elevation'
//    '<S344>/KF_Elevation'
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
  real_T tmp_1[6];
  real_T rtb_VectorConcatenate1[4];
  real_T rtb_VectorConcatenate1_m[4];
  real_T rtb_thrust[4];
  real_T rtb_y_i[4];
  real_T B_1[3];
  real_T tmp_0[3];
  real_T Gain;
  real_T Gain_0;
  real_T a21;
  real_T dx_c_tmp;
  real_T dx_c_tmp_0;
  real_T dx_c_tmp_1;
  real_T dx_c_tmp_2;
  real_T maxval;
  real_T tau_idx_0;
  real_T tau_idx_1;
  real_T tmp_2;
  real_T w;
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

  tmp = ((&rtM)->isMajorTimeStep());
  if (tmp) {
    // UnitDelay: '<S342>/Unit Delay1'
    rtDW.x_dach_mn[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_mn[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S342>/KF_Elevation' incorporates:
    //   Constant: '<S342>/Constant'
    //   Constant: '<S342>/Constant1'
    //   Constant: '<S342>/Constant2'
    //   Constant: '<S342>/Constant5'
    //   Constant: '<S342>/Cov Messrauschen'
    //   Constant: '<S342>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S342>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, rtU.y
                 [0], rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_mn,
                 rtDW.P_m);

    // UnitDelay: '<S343>/Unit Delay1'
    rtDW.x_dach_mj[0] = rtDW.UnitDelay1_DSTATE_d[0];
    rtDW.x_dach_mj[1] = rtDW.UnitDelay1_DSTATE_d[1];

    // MATLAB Function: '<S343>/KF_Elevation' incorporates:
    //   Constant: '<S343>/Constant'
    //   Constant: '<S343>/Constant1'
    //   Constant: '<S343>/Constant2'
    //   Constant: '<S343>/Constant5'
    //   Constant: '<S343>/Cov Messrauschen'
    //   Constant: '<S343>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S343>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_j,
                 rtP.Constant2_Value_i, rtP.CovProzessrauschen_Value_f,
                 rtP.CovMessrauschen_Value_a, rtU.y[1], rtP.Constant5_Value_p,
                 rtDW.UnitDelay_DSTATE_a, rtDW.x_dach_mj, rtDW.P_a);

    // UnitDelay: '<S344>/Unit Delay1'
    rtDW.x_dach_b[0] = rtDW.UnitDelay1_DSTATE_c[0];
    rtDW.x_dach_b[1] = rtDW.UnitDelay1_DSTATE_c[1];

    // MATLAB Function: '<S344>/KF_Elevation' incorporates:
    //   Constant: '<S344>/Constant'
    //   Constant: '<S344>/Constant1'
    //   Constant: '<S344>/Constant2'
    //   Constant: '<S344>/Constant5'
    //   Constant: '<S344>/Cov Messrauschen'
    //   Constant: '<S344>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S344>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_n, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_g, rtP.CovProzessrauschen_Value_c,
                 rtP.CovMessrauschen_Value_e, rtU.y[2], rtP.Constant5_Value_o,
                 rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_b, rtDW.P_p);

    // UnitDelay: '<S174>/Unit Delay1'
    rtDW.x_dach_es[0] = rtDW.UnitDelay1_DSTATE_f[0];
    rtDW.x_dach_es[1] = rtDW.UnitDelay1_DSTATE_f[1];

    // MATLAB Function: '<S174>/KF_Elevation' incorporates:
    //   Constant: '<S174>/Constant'
    //   Constant: '<S174>/Constant1'
    //   Constant: '<S174>/Constant2'
    //   Constant: '<S174>/Constant5'
    //   Constant: '<S174>/Cov Messrauschen'
    //   Constant: '<S174>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S174>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_o, rtP.Constant1_Value_mx,
                 rtP.Constant2_Value_c, rtP.CovProzessrauschen_Value_a,
                 rtP.CovMessrauschen_Value_k, rtU.y[3], rtP.Constant5_Value_d,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach_es, rtDW.P_i);

    // UnitDelay: '<S175>/Unit Delay1'
    rtDW.x_dach_k[0] = rtDW.UnitDelay1_DSTATE_a[0];
    rtDW.x_dach_k[1] = rtDW.UnitDelay1_DSTATE_a[1];

    // MATLAB Function: '<S175>/KF_Elevation' incorporates:
    //   Constant: '<S175>/Constant'
    //   Constant: '<S175>/Constant1'
    //   Constant: '<S175>/Constant2'
    //   Constant: '<S175>/Constant5'
    //   Constant: '<S175>/Cov Messrauschen'
    //   Constant: '<S175>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S175>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_o,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_fr,
                 rtP.CovMessrauschen_Value_n, rtU.y[4], rtP.Constant5_Value_e,
                 rtDW.UnitDelay_DSTATE_fb, rtDW.x_dach_k, rtDW.P_kl);

    // UnitDelay: '<S177>/Unit Delay1'
    rtDW.x_dach_gh[0] = rtDW.UnitDelay1_DSTATE_o[0];
    rtDW.x_dach_gh[1] = rtDW.UnitDelay1_DSTATE_o[1];

    // MATLAB Function: '<S177>/KF_Elevation' incorporates:
    //   Constant: '<S177>/Constant'
    //   Constant: '<S177>/Constant1'
    //   Constant: '<S177>/Constant2'
    //   Constant: '<S177>/Constant5'
    //   Constant: '<S177>/Cov Messrauschen'
    //   Constant: '<S177>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S177>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_px, rtP.Constant1_Value_f,
                 rtP.Constant2_Value_k, rtP.CovProzessrauschen_Value_j,
                 rtP.CovMessrauschen_Value_k4, rtU.y[5], rtP.Constant5_Value_m,
                 rtDW.UnitDelay_DSTATE_k, rtDW.x_dach_gh, rtDW.P_k);

    // SignalConversion generated from: '<S13>/Gain'
    tmp_1[0] = rtDW.x_dach_mn[0];
    tmp_1[1] = rtDW.x_dach_mj[0];
    tmp_1[2] = rtDW.x_dach_b[0];
    tmp_1[3] = rtDW.x_dach_mn[1];
    tmp_1[4] = rtDW.x_dach_mj[1];
    tmp_1[5] = rtDW.x_dach_b[1];

    // Gain: '<S13>/Gain'
    Gain = 0.0;
    a21 = 0.0;
    Gain_0 = 0.0;
    for (i = 0; i < 6; i++) {
      maxval = tmp_1[i];
      Gain += rtP.K_trans[3 * i] * maxval;
      a21 += rtP.K_trans[3 * i + 1] * maxval;
      Gain_0 += rtP.K_trans[3 * i + 2] * maxval;
    }

    rtDW.Gain[2] = Gain_0;
    rtDW.Gain[1] = a21;
    rtDW.Gain[0] = Gain;

    // End of Gain: '<S13>/Gain'
  }

  // Sum: '<S13>/Sum2' incorporates:
  //   Gain: '<S13>/Gain1'
  //   Inport: '<Root>/w'

  Gain = rtU.w[1];
  tau_idx_0 = rtU.w[0];
  w = rtU.w[2];

  // Gain: '<S13>/Gain2'
  maxval = 0.0;
  Gain_0 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 3; i++) {
    // Sum: '<S13>/Sum2' incorporates:
    //   Constant: '<S13>/Constant'
    //   Gain: '<S13>/Gain1'
    //   Sum: '<S13>/Sum1'

    tmp_0[i] = (((rtP.Gain1_Gain[i + 3] * Gain + rtP.Gain1_Gain[i] * tau_idx_0)
                 + rtP.Gain1_Gain[i + 6] * w) + rtP.Constant_Value_a[i]) -
      rtDW.Gain[i];

    // Gain: '<S13>/Gain2' incorporates:
    //   Integrator: '<S13>/Integrator'

    tau_idx_1 = rtX.Integrator_CSTATE[i];
    maxval += rtP.Ki_trans[3 * i] * tau_idx_1;
    Gain_0 += rtP.Ki_trans[3 * i + 1] * tau_idx_1;
    a21 += rtP.Ki_trans[3 * i + 2] * tau_idx_1;
  }

  // Sum: '<S13>/Sum2' incorporates:
  //   Gain: '<S13>/Gain2'

  rtb_VectorConcatenate1[0] = tmp_0[0] - maxval;
  rtb_VectorConcatenate1[1] = tmp_0[1] - Gain_0;
  rtb_VectorConcatenate1[2] = tmp_0[2] - a21;

  // SignalConversion generated from: '<S13>/Vector Concatenate1' incorporates:
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[3] = rtU.w[3];

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Inport: '<Root>/w'
  //   SignalConversion generated from: '<S13>/Vector Concatenate1'

  rtb_y_i[0] = std::fmin(std::fmax(rtb_VectorConcatenate1[0], 0.0), 13.0);
  rtb_y_i[1] = std::fmin(std::fmax(rtb_VectorConcatenate1[1],
    -0.087266462599716474), 0.087266462599716474);
  Gain = std::fmin(std::fmax(rtb_VectorConcatenate1[2], -0.087266462599716474),
                   0.087266462599716474);
  rtb_y_i[2] = Gain;
  rtb_y_i[3] = rtU.w[3];

  // SignalConversion generated from: '<S178>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S178>/Vector Concatenate1'

  rtb_VectorConcatenate1_m[0] = rtb_y_i[0];

  // SignalConversion generated from: '<S2>/Vector Concatenate' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'
  //   Inport: '<Root>/w'
  //   MATLAB Function: '<S2>/MATLAB Function'
  //   SignalConversion generated from: '<S13>/Vector Concatenate1'

  rtDW.VectorConcatenate[0] = rtb_y_i[0];
  rtDW.VectorConcatenate[1] = rtb_y_i[1];
  rtDW.VectorConcatenate[2] = Gain;
  rtDW.VectorConcatenate[3] = rtU.w[3];

  // SignalConversion generated from: '<S178>/Gain'
  tmp_1[0] = rtDW.x_dach_es[0];
  tmp_1[1] = rtDW.x_dach_k[0];
  tmp_1[2] = rtDW.x_dach_gh[0];
  tmp_1[3] = rtDW.x_dach_es[1];
  tmp_1[4] = rtDW.x_dach_k[1];
  tmp_1[5] = rtDW.x_dach_gh[1];

  // Gain: '<S178>/Gain1'
  tau_idx_0 = 0.0;
  w = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtb_y_i[i + 1];
    tau_idx_0 += rtP.V[3 * i] * maxval;
    w += rtP.V[3 * i + 1] * maxval;
    tmp_2 += rtP.V[3 * i + 2] * maxval;
  }

  // End of Gain: '<S178>/Gain1'

  // Gain: '<S178>/Gain'
  maxval = 0.0;
  Gain_0 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 6; i++) {
    tau_idx_1 = tmp_1[i];
    maxval += rtP.K[3 * i] * tau_idx_1;
    Gain_0 += rtP.K[3 * i + 1] * tau_idx_1;
    a21 += rtP.K[3 * i + 2] * tau_idx_1;
  }

  // Sum: '<S178>/Sum2' incorporates:
  //   Concatenate: '<S178>/Vector Concatenate1'
  //   Gain: '<S178>/Gain'
  //   Gain: '<S178>/Gain2'
  //   Integrator: '<S178>/Integrator'

  rtb_VectorConcatenate1_m[1] = (tau_idx_0 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE_a[0];
  rtb_VectorConcatenate1_m[2] = (w - Gain_0) + rtP.Ki[1] *
    rtX.Integrator_CSTATE_a[1];
  rtb_VectorConcatenate1_m[3] = (tmp_2 - a21) + rtP.Ki[2] *
    rtX.Integrator_CSTATE_a[2];

  // MATLAB Function: '<S173>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1_m, rtb_VectorConcatenate1);

  // Saturate: '<S173>/Saturation'
  if (rtb_VectorConcatenate1[0] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat;
  } else if (rtb_VectorConcatenate1[0] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_VectorConcatenate1[0];
  }

  if (rtb_VectorConcatenate1[1] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat;
  } else if (rtb_VectorConcatenate1[1] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_VectorConcatenate1[1];
  }

  if (rtb_VectorConcatenate1[2] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat;
  } else if (rtb_VectorConcatenate1[2] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_VectorConcatenate1[2];
  }

  if (rtb_VectorConcatenate1[3] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat;
  } else if (rtb_VectorConcatenate1[3] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_VectorConcatenate1[3];
  }

  // End of Saturate: '<S173>/Saturation'

  // Sum: '<S178>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   MATLAB Function: '<S2>/MATLAB Function'
  //   SignalConversion generated from: '<S13>/Vector Concatenate1'

  rtDW.Sum[0] = rtb_y_i[1] - rtDW.x_dach_es[0];
  rtDW.Sum[1] = Gain - rtDW.x_dach_k[0];
  rtDW.Sum[2] = rtU.w[3] - rtDW.x_dach_gh[0];

  // SignalConversion generated from: '<S12>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_es[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_k[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach_gh[1];

  // Sum: '<S13>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_l[0] = rtU.w[0] - rtDW.x_dach_mn[0];
  rtDW.Sum_l[1] = rtU.w[1] - rtDW.x_dach_mj[0];
  rtDW.Sum_l[2] = rtU.w[2] - rtDW.x_dach_b[0];
  if (tmp) {
    // Constant: '<S2>/Constant1' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate'

    rtDW.VectorConcatenate[4] = rtP.Constant1_Value_ot[0];
    rtDW.VectorConcatenate[5] = rtP.Constant1_Value_ot[1];
  }

  for (i = 0; i < 6; i++) {
    // Outport: '<Root>/values' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate'

    rtY.values[i] = rtDW.VectorConcatenate[i];

    // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
    //   Integrator: '<S4>/Integrator'
    //   Outport: '<Root>/x_pred'

    rtY.x_pred[i] = rtX.Integrator_CSTATE_e[i];
  }

  if (tmp) {
    // UnitDelay: '<S680>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_ff[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_ff[1];

    // MATLAB Function: '<S680>/KF_Elevation' incorporates:
    //   Constant: '<S680>/Constant'
    //   Constant: '<S680>/Constant1'
    //   Constant: '<S680>/Constant2'
    //   Constant: '<S680>/Constant5'
    //   Constant: '<S680>/Cov Messrauschen'
    //   Constant: '<S680>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S680>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_b, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_f, rtP.CovProzessrauschen_Value_d,
                 rtP.CovMessrauschen_Value_i, rtX.Integrator_CSTATE_e[0],
                 rtP.Constant5_Value_c, rtDW.UnitDelay_DSTATE_kb, rtDW.x_dach_g,
                 rtDW.P_f);

    // UnitDelay: '<S681>/Unit Delay1'
    rtDW.x_dach_l[0] = rtDW.UnitDelay1_DSTATE_e[0];
    rtDW.x_dach_l[1] = rtDW.UnitDelay1_DSTATE_e[1];

    // MATLAB Function: '<S681>/KF_Elevation' incorporates:
    //   Constant: '<S681>/Constant'
    //   Constant: '<S681>/Constant1'
    //   Constant: '<S681>/Constant2'
    //   Constant: '<S681>/Constant5'
    //   Constant: '<S681>/Cov Messrauschen'
    //   Constant: '<S681>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S681>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_n1, rtP.Constant1_Value_n,
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_dl,
                 rtP.CovMessrauschen_Value_m, rtX.Integrator_CSTATE_e[1],
                 rtP.Constant5_Value_i, rtDW.UnitDelay_DSTATE_p, rtDW.x_dach_l,
                 rtDW.P_c);

    // UnitDelay: '<S682>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_fj[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_fj[1];

    // MATLAB Function: '<S682>/KF_Elevation' incorporates:
    //   Constant: '<S682>/Constant'
    //   Constant: '<S682>/Constant1'
    //   Constant: '<S682>/Constant2'
    //   Constant: '<S682>/Constant5'
    //   Constant: '<S682>/Cov Messrauschen'
    //   Constant: '<S682>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S682>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_l, rtP.Constant1_Value_p,
                 rtP.Constant2_Value_i1, rtP.CovProzessrauschen_Value_o,
                 rtP.CovMessrauschen_Value_l, rtX.Integrator_CSTATE_e[2],
                 rtP.Constant5_Value_b, rtDW.UnitDelay_DSTATE_i, rtDW.x_dach,
                 rtDW.P_b);

    // SignalConversion generated from: '<S351>/Gain'
    tmp_1[0] = rtDW.x_dach_g[0];
    tmp_1[1] = rtDW.x_dach_l[0];
    tmp_1[2] = rtDW.x_dach[0];
    tmp_1[3] = rtDW.x_dach_g[1];
    tmp_1[4] = rtDW.x_dach_l[1];
    tmp_1[5] = rtDW.x_dach[1];

    // Gain: '<S351>/Gain'
    Gain = 0.0;
    a21 = 0.0;
    Gain_0 = 0.0;
    for (i = 0; i < 6; i++) {
      maxval = tmp_1[i];
      Gain += rtP.K_trans[3 * i] * maxval;
      a21 += rtP.K_trans[3 * i + 1] * maxval;
      Gain_0 += rtP.K_trans[3 * i + 2] * maxval;
    }

    rtDW.Gain_m[2] = Gain_0;
    rtDW.Gain_m[1] = a21;
    rtDW.Gain_m[0] = Gain;

    // End of Gain: '<S351>/Gain'
  }

  // Sum: '<S351>/Sum2' incorporates:
  //   Gain: '<S351>/Gain1'
  //   Inport: '<Root>/w'

  Gain = rtU.w[1];
  tau_idx_0 = rtU.w[0];
  w = rtU.w[2];

  // Gain: '<S351>/Gain2'
  maxval = 0.0;
  Gain_0 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 3; i++) {
    // Sum: '<S351>/Sum2' incorporates:
    //   Constant: '<S351>/Constant'
    //   Gain: '<S351>/Gain1'
    //   Sum: '<S351>/Sum1'

    tmp_0[i] = (((rtP.Gain1_Gain_d[i + 3] * Gain + rtP.Gain1_Gain_d[i] *
                  tau_idx_0) + rtP.Gain1_Gain_d[i + 6] * w) +
                rtP.Constant_Value_j[i]) - rtDW.Gain_m[i];

    // Gain: '<S351>/Gain2' incorporates:
    //   Integrator: '<S351>/Integrator'

    tau_idx_1 = rtX.Integrator_CSTATE_ee[i];
    maxval += rtP.Ki_trans[3 * i] * tau_idx_1;
    Gain_0 += rtP.Ki_trans[3 * i + 1] * tau_idx_1;
    a21 += rtP.Ki_trans[3 * i + 2] * tau_idx_1;
  }

  // Sum: '<S351>/Sum2' incorporates:
  //   Gain: '<S351>/Gain2'

  rtb_VectorConcatenate1[0] = tmp_0[0] - maxval;
  rtb_VectorConcatenate1[1] = tmp_0[1] - Gain_0;
  rtb_VectorConcatenate1[2] = tmp_0[2] - a21;

  // SignalConversion generated from: '<S351>/Vector Concatenate1' incorporates:
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[3] = rtU.w[3];

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   Inport: '<Root>/w'
  //   SignalConversion generated from: '<S351>/Vector Concatenate1'

  rtb_y_i[0] = std::fmin(std::fmax(rtb_VectorConcatenate1[0], 0.0), 13.0);
  rtb_y_i[1] = std::fmin(std::fmax(rtb_VectorConcatenate1[1],
    -0.087266462599716474), 0.087266462599716474);
  Gain = std::fmin(std::fmax(rtb_VectorConcatenate1[2], -0.087266462599716474),
                   0.087266462599716474);
  rtb_y_i[2] = Gain;
  rtb_y_i[3] = rtU.w[3];

  // SignalConversion generated from: '<S516>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S516>/Vector Concatenate1'

  rtb_VectorConcatenate1_m[0] = rtb_y_i[0];
  if (tmp) {
    // UnitDelay: '<S512>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE_b[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE_b[1];

    // MATLAB Function: '<S512>/KF_Elevation' incorporates:
    //   Constant: '<S512>/Constant'
    //   Constant: '<S512>/Constant1'
    //   Constant: '<S512>/Constant2'
    //   Constant: '<S512>/Constant5'
    //   Constant: '<S512>/Cov Messrauschen'
    //   Constant: '<S512>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S512>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_oi, rtP.Constant1_Value_n0,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_b,
                 rtP.CovMessrauschen_Value_g, rtX.Integrator_CSTATE_h[0],
                 rtP.Constant5_Value_cw, rtDW.UnitDelay_DSTATE_kf, rtDW.x_dach_e,
                 rtDW.P_bo);

    // UnitDelay: '<S513>/Unit Delay1'
    rtDW.x_dach_o[0] = rtDW.UnitDelay1_DSTATE_as[0];
    rtDW.x_dach_o[1] = rtDW.UnitDelay1_DSTATE_as[1];

    // MATLAB Function: '<S513>/KF_Elevation' incorporates:
    //   Constant: '<S513>/Constant'
    //   Constant: '<S513>/Constant1'
    //   Constant: '<S513>/Constant2'
    //   Constant: '<S513>/Constant5'
    //   Constant: '<S513>/Cov Messrauschen'
    //   Constant: '<S513>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S513>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a5, rtP.Constant1_Value_jg,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_e,
                 rtP.CovMessrauschen_Value_o, rtX.Integrator_CSTATE_h[1],
                 rtP.Constant5_Value_da, rtDW.UnitDelay_DSTATE_m, rtDW.x_dach_o,
                 rtDW.P_n);

    // UnitDelay: '<S515>/Unit Delay1'
    rtDW.x_dach_m[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach_m[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S515>/KF_Elevation' incorporates:
    //   Constant: '<S515>/Constant'
    //   Constant: '<S515>/Constant1'
    //   Constant: '<S515>/Constant2'
    //   Constant: '<S515>/Constant5'
    //   Constant: '<S515>/Cov Messrauschen'
    //   Constant: '<S515>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S515>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p4, rtP.Constant1_Value_a,
                 rtP.Constant2_Value_lz, rtP.CovProzessrauschen_Value_p,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE_h[2],
                 rtP.Constant5_Value_g, rtDW.UnitDelay_DSTATE_j, rtDW.x_dach_m,
                 rtDW.P_l);
  }

  // SignalConversion generated from: '<S516>/Gain'
  tmp_1[0] = rtDW.x_dach_e[0];
  tmp_1[1] = rtDW.x_dach_o[0];
  tmp_1[2] = rtDW.x_dach_m[0];
  tmp_1[3] = rtDW.x_dach_e[1];
  tmp_1[4] = rtDW.x_dach_o[1];
  tmp_1[5] = rtDW.x_dach_m[1];

  // Gain: '<S516>/Gain1'
  tau_idx_0 = 0.0;
  w = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtb_y_i[i + 1];
    tau_idx_0 += rtP.V[3 * i] * maxval;
    w += rtP.V[3 * i + 1] * maxval;
    tmp_2 += rtP.V[3 * i + 2] * maxval;
  }

  // End of Gain: '<S516>/Gain1'

  // Gain: '<S516>/Gain'
  maxval = 0.0;
  Gain_0 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 6; i++) {
    tau_idx_1 = tmp_1[i];
    maxval += rtP.K[3 * i] * tau_idx_1;
    Gain_0 += rtP.K[3 * i + 1] * tau_idx_1;
    a21 += rtP.K[3 * i + 2] * tau_idx_1;
  }

  // Sum: '<S516>/Sum2' incorporates:
  //   Concatenate: '<S516>/Vector Concatenate1'
  //   Gain: '<S516>/Gain'
  //   Gain: '<S516>/Gain2'
  //   Integrator: '<S516>/Integrator'

  rtb_VectorConcatenate1_m[1] = (tau_idx_0 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE_n[0];
  rtb_VectorConcatenate1_m[2] = (w - Gain_0) + rtP.Ki[1] *
    rtX.Integrator_CSTATE_n[1];
  rtb_VectorConcatenate1_m[3] = (tmp_2 - a21) + rtP.Ki[2] *
    rtX.Integrator_CSTATE_n[2];

  // MATLAB Function: '<S511>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1_m, rtb_VectorConcatenate1);

  // Saturate: '<S511>/Saturation'
  if (rtb_VectorConcatenate1[0] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[0] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[0] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S511>/Saturation'
  if (rtb_VectorConcatenate1[1] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[1] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[1] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S511>/Saturation'
  if (rtb_VectorConcatenate1[2] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[2] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[2] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S511>/Saturation'
  if (rtb_VectorConcatenate1[3] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[3] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S511>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[3] = tau_idx_0 * tau_idx_0;

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  tau_idx_0 = 0.0;
  tau_idx_1 = 0.0;
  Gain_0 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 4; i++) {
    maxval = rtP.a * rtb_thrust[i];
    r1 = i << 2;
    tau_idx_0 += rtP.B_eff[r1] * maxval;
    tau_idx_1 += rtP.B_eff[r1 + 1] * maxval;
    Gain_0 += rtP.B_eff[r1 + 2] * maxval;
    a21 += rtP.B_eff[r1 + 3] * maxval;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'
  //   Integrator: '<S6>/Integrator'

  w = 1.0 / rtP.m;
  tmp_2 = std::sin(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp = std::cos(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_0 = std::sin(rtX.Integrator_CSTATE_h[1]);
  maxval = std::cos(rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_1 = std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_2 = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_3[0] = dx_c_tmp;
  dx_c_tmp_3[3] = -tmp_2;
  dx_c_tmp_3[6] = 0.0;
  dx_c_tmp_3[1] = tmp_2;
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
    tmp_2 = dx_c_tmp_5[3 * i];
    r1 = 3 * i + 1;
    dx_c_tmp = dx_c_tmp_5[r1];
    r3 = 3 * i + 2;
    dx_c_tmp_0 = dx_c_tmp_5[r3];
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_4[3 * i + rtemp];
      tmp_2 += dx_c_tmp_3[3 * rtemp] * maxval;
      dx_c_tmp += dx_c_tmp_3[3 * rtemp + 1] * maxval;
      dx_c_tmp_0 += dx_c_tmp_3[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_5[r3] = dx_c_tmp_0;
    dx_c_tmp_5[r1] = dx_c_tmp;
    dx_c_tmp_5[3 * i] = tmp_2;
  }

  dx_c_tmp_4[1] = 0.0;
  dx_c_tmp_4[4] = dx_c_tmp_2;
  dx_c_tmp_4[7] = -dx_c_tmp_1;
  dx_c_tmp_4[2] = 0.0;
  dx_c_tmp_4[5] = dx_c_tmp_1;
  dx_c_tmp_4[8] = dx_c_tmp_2;
  for (i = 0; i < 3; i++) {
    dx_c_tmp_4[3 * i] = d[i];
    tmp_2 = 0.0;
    dx_c_tmp = 0.0;
    dx_c_tmp_0 = 0.0;
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_4[3 * i + rtemp];
      tmp_2 += dx_c_tmp_5[3 * rtemp] * maxval;
      dx_c_tmp += dx_c_tmp_5[3 * rtemp + 1] * maxval;
      dx_c_tmp_0 += dx_c_tmp_5[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_3[3 * i + 2] = dx_c_tmp_0;
    dx_c_tmp_3[3 * i + 1] = dx_c_tmp;
    dx_c_tmp_3[3 * i] = tmp_2;
  }

  for (i = 0; i < 9; i++) {
    dx_c_tmp_5[i] = w * dx_c_tmp_3[i];
  }

  tmp_0[0] = 0.0;
  tmp_0[1] = 0.0;
  tmp_0[2] = tau_idx_0;
  tau_idx_0 = 0.0;
  w = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = tmp_0[i];
    tau_idx_0 += dx_c_tmp_5[3 * i] * maxval;
    w += dx_c_tmp_5[3 * i + 1] * maxval;
    tmp_2 += dx_c_tmp_5[3 * i + 2] * maxval;
    rtDW.dx_c[i] = rtX.Integrator_CSTATE_e[i + 3];
  }

  rtDW.dx_c[3] = tau_idx_0;
  rtDW.dx_c[4] = w;
  rtDW.dx_c[5] = -rtP.g + tmp_2;

  // End of MATLAB Function: '<S4>/MATLAB Function2'

  // MATLAB Function: '<S6>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S6>/Integrator'

  maxval = (-rtP.p[0] * rtX.Integrator_CSTATE_h[3] + -rtP.p[1] *
            rtX.Integrator_CSTATE_h[4]) + -rtP.p[2] * rtX.Integrator_CSTATE_h[5];
  tau_idx_0 = tau_idx_1 + maxval;
  tau_idx_1 = Gain_0 + maxval;
  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[0]) * std::cos
      (rtX.Integrator_CSTATE_h[1]) * rtP.h;
    tau_idx_1 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[1]) * rtP.h;
  }

  w = 0.0;
  tmp_2 = 0.0;
  dx_c_tmp = 0.0;
  for (i = 0; i < 3; i++) {
    Gain_0 = rtX.Integrator_CSTATE_h[i + 3];
    w += rtP.J[3 * i] * Gain_0;
    tmp_2 += rtP.J[3 * i + 1] * Gain_0;
    dx_c_tmp += rtP.J[3 * i + 2] * Gain_0;
  }

  std::memcpy(&dx_c_tmp_3[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = (tau_idx_0 + maxval) - (dx_c_tmp * rtX.Integrator_CSTATE_h[4] - tmp_2
    * rtX.Integrator_CSTATE_h[5]);
  B_1[1] = (tau_idx_1 + maxval) - (w * rtX.Integrator_CSTATE_h[5] - dx_c_tmp *
    rtX.Integrator_CSTATE_h[3]);
  B_1[2] = ((a21 + maxval) + maxval) - (tmp_2 * rtX.Integrator_CSTATE_h[3] - w *
    rtX.Integrator_CSTATE_h[4]);
  r1 = 0;
  i = 1;
  r3 = 2;
  maxval = std::abs(rtP.J[0]);
  a21 = std::abs(rtP.J[1]);
  if (a21 > maxval) {
    maxval = a21;
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
  a21 = ((B_1[r3] - B_1[r1] * dx_c_tmp_3[r3]) - dx_c_tmp_3[r3 + 3] * tau_idx_1) /
    dx_c_tmp_3[r3 + 6];
  tau_idx_1 = (tau_idx_1 - dx_c_tmp_3[i + 6] * a21) / dx_c_tmp_3[i + 3];
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
  w = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtX.Integrator_CSTATE_h[i + 3];
    tau_idx_0 += dx_c_tmp_5[3 * i] * maxval;
    w += dx_c_tmp_5[3 * i + 1] * maxval;
    tmp_2 += dx_c_tmp_5[3 * i + 2] * maxval;
  }

  rtDW.dx[0] = tau_idx_0;
  rtDW.dx[3] = ((B_1[r1] - dx_c_tmp_3[r1 + 6] * a21) - dx_c_tmp_3[r1 + 3] *
                tau_idx_1) / dx_c_tmp_3[r1];
  rtDW.dx[1] = w;
  rtDW.dx[4] = tau_idx_1;
  rtDW.dx[2] = tmp_2;
  rtDW.dx[5] = a21;

  // End of MATLAB Function: '<S6>/MATLAB Function2'

  // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
  //   Integrator: '<S6>/Integrator'
  //   Outport: '<Root>/x_pred'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i + 6] = rtX.Integrator_CSTATE_h[i];
  }

  // SignalConversion generated from: '<S350>/Integrator'
  rtDW.TmpSignalConversionAtIntegrat_j[0] = rtDW.x_dach_e[1];
  rtDW.TmpSignalConversionAtIntegrat_j[1] = rtDW.x_dach_o[1];
  rtDW.TmpSignalConversionAtIntegrat_j[2] = rtDW.x_dach_m[1];

  // Sum: '<S516>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   MATLAB Function: '<S3>/MATLAB Function'
  //   SignalConversion generated from: '<S351>/Vector Concatenate1'

  rtDW.Sum_j[0] = rtb_y_i[1] - rtDW.x_dach_e[0];
  rtDW.Sum_j[1] = Gain - rtDW.x_dach_o[0];
  rtDW.Sum_j[2] = rtU.w[3] - rtDW.x_dach_m[0];

  // Sum: '<S351>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_m[0] = rtU.w[0] - rtDW.x_dach_g[0];
  rtDW.Sum_m[1] = rtU.w[1] - rtDW.x_dach_l[0];
  rtDW.Sum_m[2] = rtU.w[2] - rtDW.x_dach[0];

  // Sum: '<S214>/SumD' incorporates:
  //   Gain: '<S222>/Filter Coefficient'
  //   Integrator: '<S214>/Filter'
  //   UnaryMinus: '<S213>/Unary Minus'

  rtDW.SumD = 0.0 - rtP.N * rtX.Filter_CSTATE;

  // Gain: '<S216>/Integral Gain' incorporates:
  //   Sum: '<S176>/Sum'

  rtDW.IntegralGain = 0.0;

  // Sum: '<S266>/SumD' incorporates:
  //   Gain: '<S274>/Filter Coefficient'
  //   Integrator: '<S266>/Filter'
  //   UnaryMinus: '<S265>/Unary Minus'

  rtDW.SumD_h = 0.0 - rtP.N * rtX.Filter_CSTATE_j;

  // Gain: '<S268>/Integral Gain' incorporates:
  //   Sum: '<S176>/Sum1'

  rtDW.IntegralGain_i = 0.0;

  // Sum: '<S318>/SumD' incorporates:
  //   Gain: '<S326>/Filter Coefficient'
  //   Integrator: '<S318>/Filter'
  //   UnaryMinus: '<S317>/Unary Minus'

  rtDW.SumD_e = 0.0 - rtP.N * rtX.Filter_CSTATE_l;

  // Gain: '<S320>/Integral Gain' incorporates:
  //   Sum: '<S176>/Sum2'

  rtDW.IntegralGain_p = 0.0;
  if (tmp) {
    // Gain: '<S44>/Derivative Gain'
    rtDW.DerivativeGain = 0.0;

    // Gain: '<S48>/Integral Gain'
    rtDW.IntegralGain_g = 0.0;

    // Gain: '<S96>/Derivative Gain'
    rtDW.DerivativeGain_d = 0.0;

    // Gain: '<S100>/Integral Gain'
    rtDW.IntegralGain_f = 0.0;

    // Gain: '<S148>/Derivative Gain'
    rtDW.DerivativeGain_e = 0.0;

    // Gain: '<S152>/Integral Gain'
    rtDW.IntegralGain_l = 0.0;

    // Gain: '<S382>/Derivative Gain'
    rtDW.DerivativeGain_i = 0.0;

    // Gain: '<S386>/Integral Gain'
    rtDW.IntegralGain_h = 0.0;

    // Gain: '<S434>/Derivative Gain'
    rtDW.DerivativeGain_k = 0.0;

    // Gain: '<S438>/Integral Gain'
    rtDW.IntegralGain_l4 = 0.0;

    // Gain: '<S486>/Derivative Gain'
    rtDW.DerivativeGain_ic = 0.0;

    // Gain: '<S490>/Integral Gain'
    rtDW.IntegralGain_fl = 0.0;
  }

  // Gain: '<S54>/Filter Coefficient' incorporates:
  //   Integrator: '<S46>/Filter'
  //   Sum: '<S46>/SumD'

  rtDW.FilterCoefficient = (rtDW.DerivativeGain - rtX.Filter_CSTATE_f) *
    rtP.N_pos;

  // Gain: '<S106>/Filter Coefficient' incorporates:
  //   Integrator: '<S98>/Filter'
  //   Sum: '<S98>/SumD'

  rtDW.FilterCoefficient_n = (rtDW.DerivativeGain_d - rtX.Filter_CSTATE_b) *
    rtP.N_pos;

  // Gain: '<S158>/Filter Coefficient' incorporates:
  //   Integrator: '<S150>/Filter'
  //   Sum: '<S150>/SumD'

  rtDW.FilterCoefficient_f = (rtDW.DerivativeGain_e - rtX.Filter_CSTATE_k) *
    rtP.N_pos;

  // Sum: '<S552>/SumD' incorporates:
  //   Gain: '<S560>/Filter Coefficient'
  //   Integrator: '<S552>/Filter'
  //   UnaryMinus: '<S551>/Unary Minus'

  rtDW.SumD_d = 0.0 - rtP.N * rtX.Filter_CSTATE_n;

  // Gain: '<S554>/Integral Gain' incorporates:
  //   Sum: '<S514>/Sum'

  rtDW.IntegralGain_e = 0.0;

  // Sum: '<S604>/SumD' incorporates:
  //   Gain: '<S612>/Filter Coefficient'
  //   Integrator: '<S604>/Filter'
  //   UnaryMinus: '<S603>/Unary Minus'

  rtDW.SumD_n = 0.0 - rtP.N * rtX.Filter_CSTATE_e;

  // Gain: '<S606>/Integral Gain' incorporates:
  //   Sum: '<S514>/Sum1'

  rtDW.IntegralGain_k = 0.0;

  // Sum: '<S656>/SumD' incorporates:
  //   Gain: '<S664>/Filter Coefficient'
  //   Integrator: '<S656>/Filter'
  //   UnaryMinus: '<S655>/Unary Minus'

  rtDW.SumD_m = 0.0 - rtP.N * rtX.Filter_CSTATE_j5;

  // Gain: '<S658>/Integral Gain' incorporates:
  //   Sum: '<S514>/Sum2'

  rtDW.IntegralGain_c = 0.0;

  // Gain: '<S392>/Filter Coefficient' incorporates:
  //   Integrator: '<S384>/Filter'
  //   Sum: '<S384>/SumD'

  rtDW.FilterCoefficient_p = (rtDW.DerivativeGain_i - rtX.Filter_CSTATE_p) *
    rtP.N_pos;

  // Gain: '<S444>/Filter Coefficient' incorporates:
  //   Integrator: '<S436>/Filter'
  //   Sum: '<S436>/SumD'

  rtDW.FilterCoefficient_d = (rtDW.DerivativeGain_k - rtX.Filter_CSTATE_m) *
    rtP.N_pos;

  // Gain: '<S496>/Filter Coefficient' incorporates:
  //   Integrator: '<S488>/Filter'
  //   Sum: '<S488>/SumD'

  rtDW.FilterCoefficient_a = (rtDW.DerivativeGain_ic - rtX.Filter_CSTATE_nw) *
    rtP.N_pos;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S342>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_mn[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_mn[1];

      // Update for UnitDelay: '<S342>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_m[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_m[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_m[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_m[3];

      // Update for UnitDelay: '<S343>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_d[0] = rtDW.x_dach_mj[0];
      rtDW.UnitDelay1_DSTATE_d[1] = rtDW.x_dach_mj[1];

      // Update for UnitDelay: '<S343>/Unit Delay'
      rtDW.UnitDelay_DSTATE_a[0] = rtDW.P_a[0];
      rtDW.UnitDelay_DSTATE_a[1] = rtDW.P_a[1];
      rtDW.UnitDelay_DSTATE_a[2] = rtDW.P_a[2];
      rtDW.UnitDelay_DSTATE_a[3] = rtDW.P_a[3];

      // Update for UnitDelay: '<S344>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_c[0] = rtDW.x_dach_b[0];
      rtDW.UnitDelay1_DSTATE_c[1] = rtDW.x_dach_b[1];

      // Update for UnitDelay: '<S344>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_p[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_p[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_p[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_p[3];

      // Update for UnitDelay: '<S174>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_f[0] = rtDW.x_dach_es[0];
      rtDW.UnitDelay1_DSTATE_f[1] = rtDW.x_dach_es[1];

      // Update for UnitDelay: '<S174>/Unit Delay'
      rtDW.UnitDelay_DSTATE_f[0] = rtDW.P_i[0];
      rtDW.UnitDelay_DSTATE_f[1] = rtDW.P_i[1];
      rtDW.UnitDelay_DSTATE_f[2] = rtDW.P_i[2];
      rtDW.UnitDelay_DSTATE_f[3] = rtDW.P_i[3];

      // Update for UnitDelay: '<S175>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_k[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_k[1];

      // Update for UnitDelay: '<S175>/Unit Delay'
      rtDW.UnitDelay_DSTATE_fb[0] = rtDW.P_kl[0];
      rtDW.UnitDelay_DSTATE_fb[1] = rtDW.P_kl[1];
      rtDW.UnitDelay_DSTATE_fb[2] = rtDW.P_kl[2];
      rtDW.UnitDelay_DSTATE_fb[3] = rtDW.P_kl[3];

      // Update for UnitDelay: '<S177>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_o[0] = rtDW.x_dach_gh[0];
      rtDW.UnitDelay1_DSTATE_o[1] = rtDW.x_dach_gh[1];

      // Update for UnitDelay: '<S177>/Unit Delay'
      rtDW.UnitDelay_DSTATE_k[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_k[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_k[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_k[3] = rtDW.P_k[3];

      // Update for UnitDelay: '<S680>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_ff[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_ff[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S680>/Unit Delay'
      rtDW.UnitDelay_DSTATE_kb[0] = rtDW.P_f[0];
      rtDW.UnitDelay_DSTATE_kb[1] = rtDW.P_f[1];
      rtDW.UnitDelay_DSTATE_kb[2] = rtDW.P_f[2];
      rtDW.UnitDelay_DSTATE_kb[3] = rtDW.P_f[3];

      // Update for UnitDelay: '<S681>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_e[0] = rtDW.x_dach_l[0];
      rtDW.UnitDelay1_DSTATE_e[1] = rtDW.x_dach_l[1];

      // Update for UnitDelay: '<S681>/Unit Delay'
      rtDW.UnitDelay_DSTATE_p[0] = rtDW.P_c[0];
      rtDW.UnitDelay_DSTATE_p[1] = rtDW.P_c[1];
      rtDW.UnitDelay_DSTATE_p[2] = rtDW.P_c[2];
      rtDW.UnitDelay_DSTATE_p[3] = rtDW.P_c[3];

      // Update for UnitDelay: '<S682>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_fj[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_fj[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S682>/Unit Delay'
      rtDW.UnitDelay_DSTATE_i[0] = rtDW.P_b[0];
      rtDW.UnitDelay_DSTATE_i[1] = rtDW.P_b[1];
      rtDW.UnitDelay_DSTATE_i[2] = rtDW.P_b[2];
      rtDW.UnitDelay_DSTATE_i[3] = rtDW.P_b[3];

      // Update for UnitDelay: '<S512>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE_b[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S512>/Unit Delay'
      rtDW.UnitDelay_DSTATE_kf[0] = rtDW.P_bo[0];
      rtDW.UnitDelay_DSTATE_kf[1] = rtDW.P_bo[1];
      rtDW.UnitDelay_DSTATE_kf[2] = rtDW.P_bo[2];
      rtDW.UnitDelay_DSTATE_kf[3] = rtDW.P_bo[3];

      // Update for UnitDelay: '<S513>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_as[0] = rtDW.x_dach_o[0];
      rtDW.UnitDelay1_DSTATE_as[1] = rtDW.x_dach_o[1];

      // Update for UnitDelay: '<S513>/Unit Delay'
      rtDW.UnitDelay_DSTATE_m[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_m[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_m[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_m[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S515>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach_m[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach_m[1];

      // Update for UnitDelay: '<S515>/Unit Delay'
      rtDW.UnitDelay_DSTATE_j[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_j[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_j[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_j[3] = rtDW.P_l[3];
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
void Controller6dof::controller_6dof_container_derivatives()
{
  Controller6dof::XDot *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE[0] = rtDW.Sum_l[0];

  // Derivatives for Integrator: '<S178>/Integrator'
  _rtXdot->Integrator_CSTATE_a[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S12>/Integrator'
  _rtXdot->Integrator_CSTATE_b[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE[1] = rtDW.Sum_l[1];

  // Derivatives for Integrator: '<S178>/Integrator'
  _rtXdot->Integrator_CSTATE_a[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S12>/Integrator'
  _rtXdot->Integrator_CSTATE_b[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE[2] = rtDW.Sum_l[2];

  // Derivatives for Integrator: '<S178>/Integrator'
  _rtXdot->Integrator_CSTATE_a[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S12>/Integrator'
  _rtXdot->Integrator_CSTATE_b[2] = rtDW.TmpSignalConversionAtIntegrator[2];
  for (i = 0; i < 6; i++) {
    // Derivatives for Integrator: '<S4>/Integrator'
    _rtXdot->Integrator_CSTATE_e[i] = rtDW.dx_c[i];

    // Derivatives for Integrator: '<S6>/Integrator'
    _rtXdot->Integrator_CSTATE_h[i] = rtDW.dx[i];
  }

  // Derivatives for Integrator: '<S351>/Integrator'
  _rtXdot->Integrator_CSTATE_ee[0] = rtDW.Sum_m[0];

  // Derivatives for Integrator: '<S516>/Integrator'
  _rtXdot->Integrator_CSTATE_n[0] = rtDW.Sum_j[0];

  // Derivatives for Integrator: '<S350>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.TmpSignalConversionAtIntegrat_j[0];

  // Derivatives for Integrator: '<S351>/Integrator'
  _rtXdot->Integrator_CSTATE_ee[1] = rtDW.Sum_m[1];

  // Derivatives for Integrator: '<S516>/Integrator'
  _rtXdot->Integrator_CSTATE_n[1] = rtDW.Sum_j[1];

  // Derivatives for Integrator: '<S350>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.TmpSignalConversionAtIntegrat_j[1];

  // Derivatives for Integrator: '<S351>/Integrator'
  _rtXdot->Integrator_CSTATE_ee[2] = rtDW.Sum_m[2];

  // Derivatives for Integrator: '<S516>/Integrator'
  _rtXdot->Integrator_CSTATE_n[2] = rtDW.Sum_j[2];

  // Derivatives for Integrator: '<S350>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.TmpSignalConversionAtIntegrat_j[2];

  // Derivatives for Integrator: '<S174>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_es[1];

  // Derivatives for Integrator: '<S175>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_k[1];

  // Derivatives for Integrator: '<S177>/Integrator1'
  _rtXdot->Integrator1_CSTATE_d = rtDW.x_dach_gh[1];

  // Derivatives for Integrator: '<S214>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD;

  // Derivatives for Integrator: '<S219>/Integrator'
  _rtXdot->Integrator_CSTATE_bg = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S266>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.SumD_h;

  // Derivatives for Integrator: '<S271>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S318>/Filter'
  _rtXdot->Filter_CSTATE_l = rtDW.SumD_e;

  // Derivatives for Integrator: '<S323>/Integrator'
  _rtXdot->Integrator_CSTATE_bj = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S342>/Integrator1'
  _rtXdot->Integrator1_CSTATE_pi = rtDW.x_dach_mn[1];

  // Derivatives for Integrator: '<S343>/Integrator1'
  _rtXdot->Integrator1_CSTATE_k = rtDW.x_dach_mj[1];

  // Derivatives for Integrator: '<S344>/Integrator1'
  _rtXdot->Integrator1_CSTATE_n = rtDW.x_dach_b[1];

  // Derivatives for Integrator: '<S46>/Filter'
  _rtXdot->Filter_CSTATE_f = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S51>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtDW.IntegralGain_g;

  // Derivatives for Integrator: '<S98>/Filter'
  _rtXdot->Filter_CSTATE_b = rtDW.FilterCoefficient_n;

  // Derivatives for Integrator: '<S103>/Integrator'
  _rtXdot->Integrator_CSTATE_bn = rtDW.IntegralGain_f;

  // Derivatives for Integrator: '<S150>/Filter'
  _rtXdot->Filter_CSTATE_k = rtDW.FilterCoefficient_f;

  // Derivatives for Integrator: '<S155>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S512>/Integrator1'
  _rtXdot->Integrator1_CSTATE_g = rtDW.x_dach_e[1];

  // Derivatives for Integrator: '<S513>/Integrator1'
  _rtXdot->Integrator1_CSTATE_m = rtDW.x_dach_o[1];

  // Derivatives for Integrator: '<S515>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach_m[1];

  // Derivatives for Integrator: '<S552>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.SumD_d;

  // Derivatives for Integrator: '<S557>/Integrator'
  _rtXdot->Integrator_CSTATE_my = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S604>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_n;

  // Derivatives for Integrator: '<S609>/Integrator'
  _rtXdot->Integrator_CSTATE_bu = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S656>/Filter'
  _rtXdot->Filter_CSTATE_j5 = rtDW.SumD_m;

  // Derivatives for Integrator: '<S661>/Integrator'
  _rtXdot->Integrator_CSTATE_lw = rtDW.IntegralGain_c;

  // Derivatives for Integrator: '<S680>/Integrator1'
  _rtXdot->Integrator1_CSTATE_i = rtDW.x_dach_g[1];

  // Derivatives for Integrator: '<S681>/Integrator1'
  _rtXdot->Integrator1_CSTATE_l = rtDW.x_dach_l[1];

  // Derivatives for Integrator: '<S682>/Integrator1'
  _rtXdot->Integrator1_CSTATE_iu = rtDW.x_dach[1];

  // Derivatives for Integrator: '<S384>/Filter'
  _rtXdot->Filter_CSTATE_p = rtDW.FilterCoefficient_p;

  // Derivatives for Integrator: '<S389>/Integrator'
  _rtXdot->Integrator_CSTATE_fq = rtDW.IntegralGain_h;

  // Derivatives for Integrator: '<S436>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_d;

  // Derivatives for Integrator: '<S441>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_l4;

  // Derivatives for Integrator: '<S488>/Filter'
  _rtXdot->Filter_CSTATE_nw = rtDW.FilterCoefficient_a;

  // Derivatives for Integrator: '<S493>/Integrator'
  _rtXdot->Integrator_CSTATE_bh = rtDW.IntegralGain_fl;
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

    // InitializeConditions for UnitDelay: '<S342>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S342>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S343>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_d[0] = rtP.UnitDelay1_InitialCondition_o[0];
    rtDW.UnitDelay1_DSTATE_d[1] = rtP.UnitDelay1_InitialCondition_o[1];

    // InitializeConditions for UnitDelay: '<S343>/Unit Delay'
    rtDW.UnitDelay_DSTATE_a[0] = rtP.UnitDelay_InitialCondition_n[0];
    rtDW.UnitDelay_DSTATE_a[1] = rtP.UnitDelay_InitialCondition_n[1];
    rtDW.UnitDelay_DSTATE_a[2] = rtP.UnitDelay_InitialCondition_n[2];
    rtDW.UnitDelay_DSTATE_a[3] = rtP.UnitDelay_InitialCondition_n[3];

    // InitializeConditions for UnitDelay: '<S344>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_c[0] = rtP.UnitDelay1_InitialCondition_p[0];
    rtDW.UnitDelay1_DSTATE_c[1] = rtP.UnitDelay1_InitialCondition_p[1];

    // InitializeConditions for UnitDelay: '<S344>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_h[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_h[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_h[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_h[3];

    // InitializeConditions for UnitDelay: '<S174>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S174>/Unit Delay'
    rtDW.UnitDelay_DSTATE_f[0] = rtP.UnitDelay_InitialCondition_j[0];
    rtDW.UnitDelay_DSTATE_f[1] = rtP.UnitDelay_InitialCondition_j[1];
    rtDW.UnitDelay_DSTATE_f[2] = rtP.UnitDelay_InitialCondition_j[2];
    rtDW.UnitDelay_DSTATE_f[3] = rtP.UnitDelay_InitialCondition_j[3];

    // InitializeConditions for UnitDelay: '<S175>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_a[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_a[1];

    // InitializeConditions for UnitDelay: '<S175>/Unit Delay'
    rtDW.UnitDelay_DSTATE_fb[0] = rtP.UnitDelay_InitialCondition_i[0];
    rtDW.UnitDelay_DSTATE_fb[1] = rtP.UnitDelay_InitialCondition_i[1];
    rtDW.UnitDelay_DSTATE_fb[2] = rtP.UnitDelay_InitialCondition_i[2];
    rtDW.UnitDelay_DSTATE_fb[3] = rtP.UnitDelay_InitialCondition_i[3];

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_o[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_o[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay'
    rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_g[0];
    rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_g[1];
    rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_g[2];
    rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_g[3];

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE[0] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S178>/Integrator'
    rtX.Integrator_CSTATE_a[0] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S12>/Integrator'
    rtX.Integrator_CSTATE_b[0] = rtP.Integrator_IC_m;

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE[1] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S178>/Integrator'
    rtX.Integrator_CSTATE_a[1] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S12>/Integrator'
    rtX.Integrator_CSTATE_b[1] = rtP.Integrator_IC_m;

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE[2] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S178>/Integrator'
    rtX.Integrator_CSTATE_a[2] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S12>/Integrator'
    rtX.Integrator_CSTATE_b[2] = rtP.Integrator_IC_m;
    for (i = 0; i < 6; i++) {
      // InitializeConditions for Integrator: '<S4>/Integrator'
      rtX.Integrator_CSTATE_e[i] = rtP.Integrator_IC_g[i];

      // InitializeConditions for Integrator: '<S6>/Integrator'
      rtX.Integrator_CSTATE_h[i] = rtP.Integrator_IC_b[i];
    }

    // InitializeConditions for UnitDelay: '<S680>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_ff[0] = rtP.UnitDelay1_InitialCondition_c[0];
    rtDW.UnitDelay1_DSTATE_ff[1] = rtP.UnitDelay1_InitialCondition_c[1];

    // InitializeConditions for UnitDelay: '<S680>/Unit Delay'
    rtDW.UnitDelay_DSTATE_kb[0] = rtP.UnitDelay_InitialCondition_f[0];
    rtDW.UnitDelay_DSTATE_kb[1] = rtP.UnitDelay_InitialCondition_f[1];
    rtDW.UnitDelay_DSTATE_kb[2] = rtP.UnitDelay_InitialCondition_f[2];
    rtDW.UnitDelay_DSTATE_kb[3] = rtP.UnitDelay_InitialCondition_f[3];

    // InitializeConditions for UnitDelay: '<S681>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_e[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_e[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S681>/Unit Delay'
    rtDW.UnitDelay_DSTATE_p[0] = rtP.UnitDelay_InitialCondition_o[0];
    rtDW.UnitDelay_DSTATE_p[1] = rtP.UnitDelay_InitialCondition_o[1];
    rtDW.UnitDelay_DSTATE_p[2] = rtP.UnitDelay_InitialCondition_o[2];
    rtDW.UnitDelay_DSTATE_p[3] = rtP.UnitDelay_InitialCondition_o[3];

    // InitializeConditions for UnitDelay: '<S682>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_fj[0] = rtP.UnitDelay1_InitialCondition_ag[0];
    rtDW.UnitDelay1_DSTATE_fj[1] = rtP.UnitDelay1_InitialCondition_ag[1];

    // InitializeConditions for UnitDelay: '<S682>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_c[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_c[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_c[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_c[3];

    // InitializeConditions for Integrator: '<S351>/Integrator'
    rtX.Integrator_CSTATE_ee[0] = rtP.Integrator_IC_bf;
    rtX.Integrator_CSTATE_ee[1] = rtP.Integrator_IC_bf;
    rtX.Integrator_CSTATE_ee[2] = rtP.Integrator_IC_bf;

    // InitializeConditions for UnitDelay: '<S512>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b[0] = rtP.UnitDelay1_InitialCondition_j[0];
    rtDW.UnitDelay1_DSTATE_b[1] = rtP.UnitDelay1_InitialCondition_j[1];

    // InitializeConditions for UnitDelay: '<S512>/Unit Delay'
    rtDW.UnitDelay_DSTATE_kf[0] = rtP.UnitDelay_InitialCondition_nl[0];
    rtDW.UnitDelay_DSTATE_kf[1] = rtP.UnitDelay_InitialCondition_nl[1];
    rtDW.UnitDelay_DSTATE_kf[2] = rtP.UnitDelay_InitialCondition_nl[2];
    rtDW.UnitDelay_DSTATE_kf[3] = rtP.UnitDelay_InitialCondition_nl[3];

    // InitializeConditions for UnitDelay: '<S513>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_as[0] = rtP.UnitDelay1_InitialCondition_e[0];
    rtDW.UnitDelay1_DSTATE_as[1] = rtP.UnitDelay1_InitialCondition_e[1];

    // InitializeConditions for UnitDelay: '<S513>/Unit Delay'
    rtDW.UnitDelay_DSTATE_m[0] = rtP.UnitDelay_InitialCondition_fd[0];
    rtDW.UnitDelay_DSTATE_m[1] = rtP.UnitDelay_InitialCondition_fd[1];
    rtDW.UnitDelay_DSTATE_m[2] = rtP.UnitDelay_InitialCondition_fd[2];
    rtDW.UnitDelay_DSTATE_m[3] = rtP.UnitDelay_InitialCondition_fd[3];

    // InitializeConditions for UnitDelay: '<S515>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_ba[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_ba[1];

    // InitializeConditions for UnitDelay: '<S515>/Unit Delay'
    rtDW.UnitDelay_DSTATE_j[0] = rtP.UnitDelay_InitialCondition_k[0];
    rtDW.UnitDelay_DSTATE_j[1] = rtP.UnitDelay_InitialCondition_k[1];
    rtDW.UnitDelay_DSTATE_j[2] = rtP.UnitDelay_InitialCondition_k[2];
    rtDW.UnitDelay_DSTATE_j[3] = rtP.UnitDelay_InitialCondition_k[3];

    // InitializeConditions for Integrator: '<S516>/Integrator'
    rtX.Integrator_CSTATE_n[0] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S350>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S516>/Integrator'
    rtX.Integrator_CSTATE_n[1] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S350>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S516>/Integrator'
    rtX.Integrator_CSTATE_n[2] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S350>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S174>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S175>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S177>/Integrator1'
    rtX.Integrator1_CSTATE_d = rtP.Integrator1_IC_p;

    // InitializeConditions for Integrator: '<S214>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S219>/Integrator'
    rtX.Integrator_CSTATE_bg = rtP.PIDController_InitialConditi_ay;

    // InitializeConditions for Integrator: '<S266>/Filter'
    rtX.Filter_CSTATE_j = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S271>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController1_InitialConditi_n;

    // InitializeConditions for Integrator: '<S318>/Filter'
    rtX.Filter_CSTATE_l = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S323>/Integrator'
    rtX.Integrator_CSTATE_bj = rtP.PIDController2_InitialCondit_ng;

    // InitializeConditions for Integrator: '<S342>/Integrator1'
    rtX.Integrator1_CSTATE_pi = rtP.Integrator1_IC_ga;

    // InitializeConditions for Integrator: '<S343>/Integrator1'
    rtX.Integrator1_CSTATE_k = rtP.Integrator1_IC_l;

    // InitializeConditions for Integrator: '<S344>/Integrator1'
    rtX.Integrator1_CSTATE_n = rtP.Integrator1_IC_n;

    // InitializeConditions for Integrator: '<S46>/Filter'
    rtX.Filter_CSTATE_f = rtP.PIDController_InitialConditio_k;

    // InitializeConditions for Integrator: '<S51>/Integrator'
    rtX.Integrator_CSTATE_m = rtP.PIDController_InitialConditio_o;

    // InitializeConditions for Integrator: '<S98>/Filter'
    rtX.Filter_CSTATE_b = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S103>/Integrator'
    rtX.Integrator_CSTATE_bn = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S150>/Filter'
    rtX.Filter_CSTATE_k = rtP.PIDController2_InitialConditi_n;

    // InitializeConditions for Integrator: '<S155>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController2_InitialConditi_k;

    // InitializeConditions for Integrator: '<S512>/Integrator1'
    rtX.Integrator1_CSTATE_g = rtP.Integrator1_IC_h;

    // InitializeConditions for Integrator: '<S513>/Integrator1'
    rtX.Integrator1_CSTATE_m = rtP.Integrator1_IC_nb;

    // InitializeConditions for Integrator: '<S515>/Integrator1'
    rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_ph;

    // InitializeConditions for Integrator: '<S552>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S557>/Integrator'
    rtX.Integrator_CSTATE_my = rtP.PIDController_InitialConditio_b;

    // InitializeConditions for Integrator: '<S604>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController1_InitialConditi_a;

    // InitializeConditions for Integrator: '<S609>/Integrator'
    rtX.Integrator_CSTATE_bu = rtP.PIDController1_InitialConditi_b;

    // InitializeConditions for Integrator: '<S656>/Filter'
    rtX.Filter_CSTATE_j5 = rtP.PIDController2_InitialConditi_c;

    // InitializeConditions for Integrator: '<S661>/Integrator'
    rtX.Integrator_CSTATE_lw = rtP.PIDController2_InitialCondit_k5;

    // InitializeConditions for Integrator: '<S680>/Integrator1'
    rtX.Integrator1_CSTATE_i = rtP.Integrator1_IC_f;

    // InitializeConditions for Integrator: '<S681>/Integrator1'
    rtX.Integrator1_CSTATE_l = rtP.Integrator1_IC_b;

    // InitializeConditions for Integrator: '<S682>/Integrator1'
    rtX.Integrator1_CSTATE_iu = rtP.Integrator1_IC_d;

    // InitializeConditions for Integrator: '<S384>/Filter'
    rtX.Filter_CSTATE_p = rtP.PIDController_InitialConditio_m;

    // InitializeConditions for Integrator: '<S389>/Integrator'
    rtX.Integrator_CSTATE_fq = rtP.PIDController_InitialConditi_a2;

    // InitializeConditions for Integrator: '<S436>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialCondit_ms;

    // InitializeConditions for Integrator: '<S441>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController1_InitialCondit_jr;

    // InitializeConditions for Integrator: '<S488>/Filter'
    rtX.Filter_CSTATE_nw = rtP.PIDController2_InitialConditi_a;

    // InitializeConditions for Integrator: '<S493>/Integrator'
    rtX.Integrator_CSTATE_bh = rtP.PIDController2_InitialConditi_i;
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
