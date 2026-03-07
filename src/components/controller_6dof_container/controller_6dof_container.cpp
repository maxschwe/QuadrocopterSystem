//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.500
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Mar  7 19:55:57 2026
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
void Controller6dof::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE1_IntgData *id { static_cast<ODE1_IntgData *>(rtsiGetSolverData(si)) };

  real_T *f0 { id->f[0] };

  int_T i;
  int_T nXc { 54 };

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
  rty_y[0] = std::fmin(std::fmax(rtu_u, 0.0), 12.0);
  rty_y[1] = std::fmin(std::fmax(rtu_u_g, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[2] = std::fmin(std::fmax(rtu_u_h, -0.087266462599716474),
                       0.087266462599716474);
  rty_y[3] = rtu_u_hc;
}

//
// Output and update for atomic system:
//    '<S171>/MATLAB Function'
//    '<S501>/MATLAB Function'
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
//    '<S172>/KF_Elevation'
//    '<S173>/KF_Elevation'
//    '<S175>/KF_Elevation'
//    '<S502>/KF_Elevation'
//    '<S503>/KF_Elevation'
//    '<S505>/KF_Elevation'
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
  real_T dx_c_tmp_4[9];
  real_T dx_c_tmp_5[9];
  real_T dx_c_tmp_6[9];
  real_T tmp_0[6];
  real_T rtb_VectorConcatenate1[4];
  real_T rtb_thrust[4];
  real_T rtb_y[4];
  real_T rtb_y_l[4];
  real_T B_1[3];
  real_T tmp_1[3];
  real_T a21;
  real_T dx_c_tmp;
  real_T dx_c_tmp_0;
  real_T dx_c_tmp_1;
  real_T dx_c_tmp_2;
  real_T dx_c_tmp_3;
  real_T maxval;
  real_T rtb_Filter;
  real_T rtb_Sum1;
  real_T rtb_Sum_a5;
  real_T tau_idx_0;
  real_T tau_idx_1;
  real_T tau_idx_2;
  real_T tmp_2;
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
    // UnitDelay: '<S172>/Unit Delay1'
    rtDW.x_dach_es[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_es[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S172>/KF_Elevation' incorporates:
    //   Constant: '<S172>/Constant'
    //   Constant: '<S172>/Constant1'
    //   Constant: '<S172>/Constant2'
    //   Constant: '<S172>/Constant5'
    //   Constant: '<S172>/Cov Messrauschen'
    //   Constant: '<S172>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S172>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, rtU.y
                 [3], rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_es,
                 rtDW.P_i);

    // UnitDelay: '<S173>/Unit Delay1'
    rtDW.x_dach_k[0] = rtDW.UnitDelay1_DSTATE_a[0];
    rtDW.x_dach_k[1] = rtDW.UnitDelay1_DSTATE_a[1];

    // MATLAB Function: '<S173>/KF_Elevation' incorporates:
    //   Constant: '<S173>/Constant'
    //   Constant: '<S173>/Constant1'
    //   Constant: '<S173>/Constant2'
    //   Constant: '<S173>/Constant5'
    //   Constant: '<S173>/Cov Messrauschen'
    //   Constant: '<S173>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S173>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_o,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_f,
                 rtP.CovMessrauschen_Value_n, rtU.y[4], rtP.Constant5_Value_e,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach_k, rtDW.P_kl);

    // UnitDelay: '<S175>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_o[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_o[1];

    // MATLAB Function: '<S175>/KF_Elevation' incorporates:
    //   Constant: '<S175>/Constant'
    //   Constant: '<S175>/Constant1'
    //   Constant: '<S175>/Constant2'
    //   Constant: '<S175>/Constant5'
    //   Constant: '<S175>/Cov Messrauschen'
    //   Constant: '<S175>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S175>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_f,
                 rtP.Constant2_Value_k, rtP.CovProzessrauschen_Value_j,
                 rtP.CovMessrauschen_Value_k, rtU.y[5], rtP.Constant5_Value_m,
                 rtDW.UnitDelay_DSTATE_k, rtDW.x_dach_g, rtDW.P_k);
  }

  // Sum: '<S2>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Filter = rtU.w[2] - rtU.y[2];

  // Gain: '<S156>/Filter Coefficient' incorporates:
  //   Gain: '<S146>/Derivative Gain'
  //   Integrator: '<S148>/Filter'
  //   Sum: '<S148>/SumD'

  rtDW.FilterCoefficient = (rtP.kd_z * rtb_Filter - rtX.Filter_CSTATE) *
    rtP.N_pos;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum_a5 = rtU.y[1] - rtU.w[1];

  // Gain: '<S104>/Filter Coefficient' incorporates:
  //   Gain: '<S94>/Derivative Gain'
  //   Integrator: '<S96>/Filter'
  //   Sum: '<S96>/SumD'

  rtDW.FilterCoefficient_j = (rtP.kd_y * rtb_Sum_a5 - rtX.Filter_CSTATE_m) *
    rtP.N_pos;

  // Sum: '<S2>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum1 = rtU.w[0] - rtU.y[0];

  // Gain: '<S52>/Filter Coefficient' incorporates:
  //   Gain: '<S42>/Derivative Gain'
  //   Integrator: '<S44>/Filter'
  //   Sum: '<S44>/SumD'

  rtDW.FilterCoefficient_l = (rtP.kd_x * rtb_Sum1 - rtX.Filter_CSTATE_l) *
    rtP.N_pos;

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Constant: '<S2>/Constant'
  //   Gain: '<S106>/Proportional Gain'
  //   Gain: '<S158>/Proportional Gain'
  //   Gain: '<S54>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S101>/Integrator'
  //   Integrator: '<S153>/Integrator'
  //   Integrator: '<S49>/Integrator'
  //   Sum: '<S110>/Sum'
  //   Sum: '<S162>/Sum'
  //   Sum: '<S2>/Sum3'
  //   Sum: '<S58>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtP.kp_z * rtb_Filter + rtX.Integrator_CSTATE)
    + rtDW.FilterCoefficient), (rtP.kp_y * rtb_Sum_a5 + rtX.Integrator_CSTATE_a)
                 + rtDW.FilterCoefficient_j, (rtP.kp_x * rtb_Sum1 +
    rtX.Integrator_CSTATE_j) + rtDW.FilterCoefficient_l, rtU.w[3], rtb_y);

  // SignalConversion generated from: '<S176>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S176>/Vector Concatenate1'

  rtb_VectorConcatenate1[0] = rtb_y[0];

  // SignalConversion generated from: '<S2>/Vector Concatenate' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'

  rtDW.VectorConcatenate[0] = rtb_y[0];
  rtDW.VectorConcatenate[1] = rtb_y[1];
  rtDW.VectorConcatenate[2] = rtb_y[2];
  rtDW.VectorConcatenate[3] = rtb_y[3];

  // SignalConversion generated from: '<S176>/Gain'
  tmp_0[0] = rtDW.x_dach_es[0];
  tmp_0[1] = rtDW.x_dach_k[0];
  tmp_0[2] = rtDW.x_dach_g[0];
  tmp_0[3] = rtDW.x_dach_es[1];
  tmp_0[4] = rtDW.x_dach_k[1];
  tmp_0[5] = rtDW.x_dach_g[1];

  // Gain: '<S176>/Gain1'
  a21 = 0.0;
  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtb_y[i + 1];
    a21 += rtP.V[3 * i] * maxval;
    tau_idx_0 += rtP.V[3 * i + 1] * maxval;
    tmp_2 += rtP.V[3 * i + 2] * maxval;
  }

  // End of Gain: '<S176>/Gain1'

  // Gain: '<S176>/Gain'
  maxval = 0.0;
  tau_idx_2 = 0.0;
  tau_idx_1 = 0.0;
  for (i = 0; i < 6; i++) {
    dx_c_tmp = tmp_0[i];
    maxval += rtP.K[3 * i] * dx_c_tmp;
    tau_idx_2 += rtP.K[3 * i + 1] * dx_c_tmp;
    tau_idx_1 += rtP.K[3 * i + 2] * dx_c_tmp;
  }

  // Sum: '<S176>/Sum2' incorporates:
  //   Concatenate: '<S176>/Vector Concatenate1'
  //   Gain: '<S176>/Gain'
  //   Gain: '<S176>/Gain2'
  //   Integrator: '<S176>/Integrator'

  rtb_VectorConcatenate1[1] = (a21 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE_ay[0];
  rtb_VectorConcatenate1[2] = (tau_idx_0 - tau_idx_2) + rtP.Ki[1] *
    rtX.Integrator_CSTATE_ay[1];
  rtb_VectorConcatenate1[3] = (tmp_2 - tau_idx_1) + rtP.Ki[2] *
    rtX.Integrator_CSTATE_ay[2];

  // MATLAB Function: '<S171>/MATLAB Function'
  MATLABFunction_e(rtb_VectorConcatenate1, rtb_y_l);

  // Saturate: '<S171>/Saturation'
  if (rtb_y_l[0] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat;
  } else if (rtb_y_l[0] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_y_l[0];
  }

  if (rtb_y_l[1] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat;
  } else if (rtb_y_l[1] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_y_l[1];
  }

  if (rtb_y_l[2] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat;
  } else if (rtb_y_l[2] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_y_l[2];
  }

  if (rtb_y_l[3] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat;
  } else if (rtb_y_l[3] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_y_l[3];
  }

  // End of Saturate: '<S171>/Saturation'

  // Sum: '<S176>/Sum'
  rtDW.Sum[0] = rtb_y[1] - rtDW.x_dach_es[0];
  rtDW.Sum[1] = rtb_y[2] - rtDW.x_dach_k[0];
  rtDW.Sum[2] = rtb_y[3] - rtDW.x_dach_g[0];

  // SignalConversion generated from: '<S14>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_es[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_k[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach_g[1];

  // Gain: '<S46>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_x * rtb_Sum1;

  // Gain: '<S98>/Integral Gain'
  rtDW.IntegralGain_l = rtP.ki_y * rtb_Sum_a5;

  // Gain: '<S150>/Integral Gain'
  rtDW.IntegralGain_d = rtP.ki_z * rtb_Filter;
  if (tmp) {
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

  // Sum: '<S3>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Filter = rtU.w[2] - rtX.Integrator_CSTATE_e[2];

  // Gain: '<S486>/Filter Coefficient' incorporates:
  //   Gain: '<S476>/Derivative Gain'
  //   Integrator: '<S478>/Filter'
  //   Sum: '<S478>/SumD'

  rtDW.FilterCoefficient_o = (rtP.kd_z * rtb_Filter - rtX.Filter_CSTATE_p) *
    rtP.N_pos;

  // Sum: '<S3>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Sum1 = rtX.Integrator_CSTATE_e[1] - rtU.w[1];

  // Gain: '<S434>/Filter Coefficient' incorporates:
  //   Gain: '<S424>/Derivative Gain'
  //   Integrator: '<S426>/Filter'
  //   Sum: '<S426>/SumD'

  rtDW.FilterCoefficient_p = (rtP.kd_y * rtb_Sum1 - rtX.Filter_CSTATE_g) *
    rtP.N_pos;

  // Sum: '<S3>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Sum_a5 = rtU.w[0] - rtX.Integrator_CSTATE_e[0];

  // Gain: '<S382>/Filter Coefficient' incorporates:
  //   Gain: '<S372>/Derivative Gain'
  //   Integrator: '<S374>/Filter'
  //   Sum: '<S374>/SumD'

  rtDW.FilterCoefficient_e = (rtP.kd_x * rtb_Sum_a5 - rtX.Filter_CSTATE_k) *
    rtP.N_pos;

  // MATLAB Function: '<S3>/MATLAB Function' incorporates:
  //   Constant: '<S3>/Constant'
  //   Gain: '<S384>/Proportional Gain'
  //   Gain: '<S436>/Proportional Gain'
  //   Gain: '<S488>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S379>/Integrator'
  //   Integrator: '<S431>/Integrator'
  //   Integrator: '<S483>/Integrator'
  //   Sum: '<S388>/Sum'
  //   Sum: '<S3>/Sum3'
  //   Sum: '<S440>/Sum'
  //   Sum: '<S492>/Sum'

  MATLABFunction(rtP.m * rtP.g + ((rtP.kp_z * rtb_Filter +
    rtX.Integrator_CSTATE_am) + rtDW.FilterCoefficient_o), (rtP.kp_y * rtb_Sum1
    + rtX.Integrator_CSTATE_j2) + rtDW.FilterCoefficient_p, (rtP.kp_x *
    rtb_Sum_a5 + rtX.Integrator_CSTATE_m) + rtDW.FilterCoefficient_e, rtU.w[3],
                 rtb_y_l);

  // SignalConversion generated from: '<S506>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S506>/Vector Concatenate1'

  rtb_y[0] = rtb_y_l[0];
  if (tmp) {
    // UnitDelay: '<S502>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE_b[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE_b[1];

    // MATLAB Function: '<S502>/KF_Elevation' incorporates:
    //   Constant: '<S502>/Constant'
    //   Constant: '<S502>/Constant1'
    //   Constant: '<S502>/Constant2'
    //   Constant: '<S502>/Constant5'
    //   Constant: '<S502>/Cov Messrauschen'
    //   Constant: '<S502>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S502>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_o, rtP.Constant1_Value_n,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_b,
                 rtP.CovMessrauschen_Value_g, rtX.Integrator_CSTATE_h[0],
                 rtP.Constant5_Value_c, rtDW.UnitDelay_DSTATE_kf, rtDW.x_dach_e,
                 rtDW.P_b);

    // UnitDelay: '<S503>/Unit Delay1'
    rtDW.x_dach_o[0] = rtDW.UnitDelay1_DSTATE_as[0];
    rtDW.x_dach_o[1] = rtDW.UnitDelay1_DSTATE_as[1];

    // MATLAB Function: '<S503>/KF_Elevation' incorporates:
    //   Constant: '<S503>/Constant'
    //   Constant: '<S503>/Constant1'
    //   Constant: '<S503>/Constant2'
    //   Constant: '<S503>/Constant5'
    //   Constant: '<S503>/Cov Messrauschen'
    //   Constant: '<S503>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S503>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a, rtP.Constant1_Value_j,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_e,
                 rtP.CovMessrauschen_Value_o, rtX.Integrator_CSTATE_h[1],
                 rtP.Constant5_Value_d, rtDW.UnitDelay_DSTATE_m, rtDW.x_dach_o,
                 rtDW.P_n);

    // UnitDelay: '<S505>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S505>/KF_Elevation' incorporates:
    //   Constant: '<S505>/Constant'
    //   Constant: '<S505>/Constant1'
    //   Constant: '<S505>/Constant2'
    //   Constant: '<S505>/Constant5'
    //   Constant: '<S505>/Cov Messrauschen'
    //   Constant: '<S505>/Cov Prozessrauschen'
    //   Integrator: '<S6>/Integrator'
    //   UnitDelay: '<S505>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p4, rtP.Constant1_Value_a,
                 rtP.Constant2_Value_lz, rtP.CovProzessrauschen_Value_p,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE_h[2],
                 rtP.Constant5_Value_g, rtDW.UnitDelay_DSTATE_j, rtDW.x_dach,
                 rtDW.P_l);
  }

  // SignalConversion generated from: '<S506>/Gain'
  tmp_0[0] = rtDW.x_dach_e[0];
  tmp_0[1] = rtDW.x_dach_o[0];
  tmp_0[2] = rtDW.x_dach[0];
  tmp_0[3] = rtDW.x_dach_e[1];
  tmp_0[4] = rtDW.x_dach_o[1];
  tmp_0[5] = rtDW.x_dach[1];

  // Gain: '<S506>/Gain1'
  a21 = 0.0;
  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtb_y_l[i + 1];
    a21 += rtP.V[3 * i] * maxval;
    tau_idx_0 += rtP.V[3 * i + 1] * maxval;
    tmp_2 += rtP.V[3 * i + 2] * maxval;
  }

  // End of Gain: '<S506>/Gain1'

  // Gain: '<S506>/Gain'
  maxval = 0.0;
  tau_idx_2 = 0.0;
  tau_idx_1 = 0.0;
  for (i = 0; i < 6; i++) {
    dx_c_tmp = tmp_0[i];
    maxval += rtP.K[3 * i] * dx_c_tmp;
    tau_idx_2 += rtP.K[3 * i + 1] * dx_c_tmp;
    tau_idx_1 += rtP.K[3 * i + 2] * dx_c_tmp;
  }

  // Sum: '<S506>/Sum2' incorporates:
  //   Concatenate: '<S506>/Vector Concatenate1'
  //   Gain: '<S506>/Gain'
  //   Gain: '<S506>/Gain2'
  //   Integrator: '<S506>/Integrator'

  rtb_y[1] = (a21 - maxval) + rtP.Ki[0] * rtX.Integrator_CSTATE_n[0];
  rtb_y[2] = (tau_idx_0 - tau_idx_2) + rtP.Ki[1] * rtX.Integrator_CSTATE_n[1];
  rtb_y[3] = (tmp_2 - tau_idx_1) + rtP.Ki[2] * rtX.Integrator_CSTATE_n[2];

  // MATLAB Function: '<S501>/MATLAB Function'
  MATLABFunction_e(rtb_y, rtb_VectorConcatenate1);

  // Saturate: '<S501>/Saturation'
  if (rtb_VectorConcatenate1[0] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[0] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S501>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[0] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S501>/Saturation'
  if (rtb_VectorConcatenate1[1] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[1] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S501>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[1] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S501>/Saturation'
  if (rtb_VectorConcatenate1[2] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[2] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S501>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[2] = tau_idx_0 * tau_idx_0;

  // Saturate: '<S501>/Saturation'
  if (rtb_VectorConcatenate1[3] > rtP.Saturation_UpperSat_d) {
    maxval = rtP.Saturation_UpperSat_d;
  } else if (rtb_VectorConcatenate1[3] < rtP.Saturation_LowerSat_l) {
    maxval = rtP.Saturation_LowerSat_l;
  } else {
    maxval = rtb_VectorConcatenate1[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S501>/Saturation'

  tau_idx_0 = maxval - rtP.b;
  rtb_thrust[3] = tau_idx_0 * tau_idx_0;

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  tau_idx_0 = 0.0;
  tau_idx_1 = 0.0;
  tau_idx_2 = 0.0;
  a21 = 0.0;
  for (i = 0; i < 4; i++) {
    maxval = rtP.a * rtb_thrust[i];
    r1 = i << 2;
    tau_idx_0 += rtP.B_eff[r1] * maxval;
    tau_idx_1 += rtP.B_eff[r1 + 1] * maxval;
    tau_idx_2 += rtP.B_eff[r1 + 2] * maxval;
    a21 += rtP.B_eff[r1 + 3] * maxval;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'
  //   Integrator: '<S6>/Integrator'

  tmp_2 = 1.0 / rtP.m;
  dx_c_tmp = std::sin(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_0 = std::cos(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_1 = std::sin(rtX.Integrator_CSTATE_h[1]);
  maxval = std::cos(rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_2 = std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_3 = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_4[0] = dx_c_tmp_0;
  dx_c_tmp_4[3] = -dx_c_tmp;
  dx_c_tmp_4[6] = 0.0;
  dx_c_tmp_4[1] = dx_c_tmp;
  dx_c_tmp_4[4] = dx_c_tmp_0;
  dx_c_tmp_4[7] = 0.0;
  dx_c_tmp_5[0] = maxval;
  dx_c_tmp_5[3] = 0.0;
  dx_c_tmp_5[6] = dx_c_tmp_1;
  dx_c_tmp_5[2] = -dx_c_tmp_1;
  dx_c_tmp_5[5] = 0.0;
  dx_c_tmp_5[8] = maxval;
  for (i = 0; i < 3; i++) {
    r1 = 3 * i + 2;
    dx_c_tmp_4[r1] = b[i];
    r3 = 3 * i + 1;
    dx_c_tmp_5[r3] = c[i];
    dx_c_tmp_6[3 * i] = 0.0;
    dx_c_tmp_6[r3] = 0.0;
    dx_c_tmp_6[r1] = 0.0;
  }

  for (i = 0; i < 3; i++) {
    dx_c_tmp = dx_c_tmp_6[3 * i];
    r1 = 3 * i + 1;
    dx_c_tmp_0 = dx_c_tmp_6[r1];
    r3 = 3 * i + 2;
    dx_c_tmp_1 = dx_c_tmp_6[r3];
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_5[3 * i + rtemp];
      dx_c_tmp += dx_c_tmp_4[3 * rtemp] * maxval;
      dx_c_tmp_0 += dx_c_tmp_4[3 * rtemp + 1] * maxval;
      dx_c_tmp_1 += dx_c_tmp_4[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_6[r3] = dx_c_tmp_1;
    dx_c_tmp_6[r1] = dx_c_tmp_0;
    dx_c_tmp_6[3 * i] = dx_c_tmp;
  }

  dx_c_tmp_5[1] = 0.0;
  dx_c_tmp_5[4] = dx_c_tmp_3;
  dx_c_tmp_5[7] = -dx_c_tmp_2;
  dx_c_tmp_5[2] = 0.0;
  dx_c_tmp_5[5] = dx_c_tmp_2;
  dx_c_tmp_5[8] = dx_c_tmp_3;
  for (i = 0; i < 3; i++) {
    dx_c_tmp_5[3 * i] = d[i];
    dx_c_tmp = 0.0;
    dx_c_tmp_0 = 0.0;
    dx_c_tmp_1 = 0.0;
    for (rtemp = 0; rtemp < 3; rtemp++) {
      maxval = dx_c_tmp_5[3 * i + rtemp];
      dx_c_tmp += dx_c_tmp_6[3 * rtemp] * maxval;
      dx_c_tmp_0 += dx_c_tmp_6[3 * rtemp + 1] * maxval;
      dx_c_tmp_1 += dx_c_tmp_6[3 * rtemp + 2] * maxval;
    }

    dx_c_tmp_4[3 * i + 2] = dx_c_tmp_1;
    dx_c_tmp_4[3 * i + 1] = dx_c_tmp_0;
    dx_c_tmp_4[3 * i] = dx_c_tmp;
  }

  for (i = 0; i < 9; i++) {
    dx_c_tmp_6[i] = tmp_2 * dx_c_tmp_4[i];
  }

  tmp_1[0] = 0.0;
  tmp_1[1] = 0.0;
  tmp_1[2] = tau_idx_0;
  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  dx_c_tmp = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = tmp_1[i];
    tau_idx_0 += dx_c_tmp_6[3 * i] * maxval;
    tmp_2 += dx_c_tmp_6[3 * i + 1] * maxval;
    dx_c_tmp += dx_c_tmp_6[3 * i + 2] * maxval;
    rtDW.dx_c[i] = rtX.Integrator_CSTATE_e[i + 3];
  }

  rtDW.dx_c[3] = tau_idx_0;
  rtDW.dx_c[4] = tmp_2;
  rtDW.dx_c[5] = -rtP.g + dx_c_tmp;

  // End of MATLAB Function: '<S4>/MATLAB Function2'

  // MATLAB Function: '<S6>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S6>/Integrator'

  maxval = (-rtP.p[0] * rtX.Integrator_CSTATE_h[3] + -rtP.p[1] *
            rtX.Integrator_CSTATE_h[4]) + -rtP.p[2] * rtX.Integrator_CSTATE_h[5];
  tau_idx_0 = tau_idx_1 + maxval;
  tau_idx_1 = tau_idx_2 + maxval;
  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[0]) * std::cos
      (rtX.Integrator_CSTATE_h[1]) * rtP.h;
    tau_idx_1 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[1]) * rtP.h;
  }

  tmp_2 = 0.0;
  dx_c_tmp = 0.0;
  dx_c_tmp_0 = 0.0;
  for (i = 0; i < 3; i++) {
    tau_idx_2 = rtX.Integrator_CSTATE_h[i + 3];
    tmp_2 += rtP.J[3 * i] * tau_idx_2;
    dx_c_tmp += rtP.J[3 * i + 1] * tau_idx_2;
    dx_c_tmp_0 += rtP.J[3 * i + 2] * tau_idx_2;
  }

  std::memcpy(&dx_c_tmp_4[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = (tau_idx_0 + maxval) - (dx_c_tmp_0 * rtX.Integrator_CSTATE_h[4] -
    dx_c_tmp * rtX.Integrator_CSTATE_h[5]);
  B_1[1] = (tau_idx_1 + maxval) - (tmp_2 * rtX.Integrator_CSTATE_h[5] -
    dx_c_tmp_0 * rtX.Integrator_CSTATE_h[3]);
  B_1[2] = ((a21 + maxval) + maxval) - (dx_c_tmp * rtX.Integrator_CSTATE_h[3] -
    tmp_2 * rtX.Integrator_CSTATE_h[4]);
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

  dx_c_tmp_4[i] = rtP.J[i] / rtP.J[r1];
  dx_c_tmp_4[r3] /= dx_c_tmp_4[r1];
  dx_c_tmp_4[i + 3] -= dx_c_tmp_4[r1 + 3] * dx_c_tmp_4[i];
  dx_c_tmp_4[r3 + 3] -= dx_c_tmp_4[r1 + 3] * dx_c_tmp_4[r3];
  dx_c_tmp_4[i + 6] -= dx_c_tmp_4[r1 + 6] * dx_c_tmp_4[i];
  dx_c_tmp_4[r3 + 6] -= dx_c_tmp_4[r1 + 6] * dx_c_tmp_4[r3];
  if (std::abs(dx_c_tmp_4[r3 + 3]) > std::abs(dx_c_tmp_4[i + 3])) {
    rtemp = i;
    i = r3;
    r3 = rtemp;
  }

  dx_c_tmp_4[r3 + 3] /= dx_c_tmp_4[i + 3];
  dx_c_tmp_4[r3 + 6] -= dx_c_tmp_4[r3 + 3] * dx_c_tmp_4[i + 6];
  tau_idx_1 = B_1[i] - B_1[r1] * dx_c_tmp_4[i];
  tau_idx_2 = ((B_1[r3] - B_1[r1] * dx_c_tmp_4[r3]) - dx_c_tmp_4[r3 + 3] *
               tau_idx_1) / dx_c_tmp_4[r3 + 6];
  tau_idx_1 = (tau_idx_1 - dx_c_tmp_4[i + 6] * tau_idx_2) / dx_c_tmp_4[i + 3];
  dx_c_tmp_6[0] = 1.0;
  dx_c_tmp_6[3] = std::sin(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_6[6] = std::cos(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_6[1] = 0.0;
  dx_c_tmp_6[4] = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_6[7] = -std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_6[2] = 0.0;
  dx_c_tmp_6[5] = std::sin(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_6[8] = std::cos(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  a21 = 0.0;
  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  for (i = 0; i < 3; i++) {
    maxval = rtX.Integrator_CSTATE_h[i + 3];
    a21 += dx_c_tmp_6[3 * i] * maxval;
    tau_idx_0 += dx_c_tmp_6[3 * i + 1] * maxval;
    tmp_2 += dx_c_tmp_6[3 * i + 2] * maxval;
  }

  rtDW.dx[0] = a21;
  rtDW.dx[3] = ((B_1[r1] - dx_c_tmp_4[r1 + 6] * tau_idx_2) - dx_c_tmp_4[r1 + 3] *
                tau_idx_1) / dx_c_tmp_4[r1];
  rtDW.dx[1] = tau_idx_0;
  rtDW.dx[4] = tau_idx_1;
  rtDW.dx[2] = tmp_2;
  rtDW.dx[5] = tau_idx_2;

  // End of MATLAB Function: '<S6>/MATLAB Function2'

  // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
  //   Integrator: '<S6>/Integrator'
  //   Outport: '<Root>/x_pred'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i + 6] = rtX.Integrator_CSTATE_h[i];
  }

  // SignalConversion generated from: '<S344>/Integrator'
  rtDW.TmpSignalConversionAtIntegrat_j[0] = rtDW.x_dach_e[1];
  rtDW.TmpSignalConversionAtIntegrat_j[1] = rtDW.x_dach_o[1];
  rtDW.TmpSignalConversionAtIntegrat_j[2] = rtDW.x_dach[1];

  // Sum: '<S506>/Sum'
  rtDW.Sum_j[0] = rtb_y_l[1] - rtDW.x_dach_e[0];
  rtDW.Sum_j[1] = rtb_y_l[2] - rtDW.x_dach_o[0];
  rtDW.Sum_j[2] = rtb_y_l[3] - rtDW.x_dach[0];

  // Gain: '<S376>/Integral Gain'
  rtDW.IntegralGain_i = rtP.ki_x * rtb_Sum_a5;

  // Gain: '<S428>/Integral Gain'
  rtDW.IntegralGain_di = rtP.ki_y * rtb_Sum1;

  // Gain: '<S480>/Integral Gain'
  rtDW.IntegralGain_lw = rtP.ki_z * rtb_Filter;

  // Sum: '<S212>/SumD' incorporates:
  //   Gain: '<S220>/Filter Coefficient'
  //   Integrator: '<S212>/Filter'
  //   UnaryMinus: '<S211>/Unary Minus'

  rtDW.SumD = 0.0 - rtP.N * rtX.Filter_CSTATE_mg;

  // Gain: '<S214>/Integral Gain' incorporates:
  //   Sum: '<S174>/Sum'

  rtDW.IntegralGain_o = 0.0;

  // Sum: '<S264>/SumD' incorporates:
  //   Gain: '<S272>/Filter Coefficient'
  //   Integrator: '<S264>/Filter'
  //   UnaryMinus: '<S263>/Unary Minus'

  rtDW.SumD_h = 0.0 - rtP.N * rtX.Filter_CSTATE_j;

  // Gain: '<S266>/Integral Gain' incorporates:
  //   Sum: '<S174>/Sum1'

  rtDW.IntegralGain_im = 0.0;

  // Sum: '<S316>/SumD' incorporates:
  //   Gain: '<S324>/Filter Coefficient'
  //   Integrator: '<S316>/Filter'
  //   UnaryMinus: '<S315>/Unary Minus'

  rtDW.SumD_e = 0.0 - rtP.N * rtX.Filter_CSTATE_lf;

  // Gain: '<S318>/Integral Gain' incorporates:
  //   Sum: '<S174>/Sum2'

  rtDW.IntegralGain_p = 0.0;

  // Sum: '<S542>/SumD' incorporates:
  //   Gain: '<S550>/Filter Coefficient'
  //   Integrator: '<S542>/Filter'
  //   UnaryMinus: '<S541>/Unary Minus'

  rtDW.SumD_d = 0.0 - rtP.N * rtX.Filter_CSTATE_n;

  // Gain: '<S544>/Integral Gain' incorporates:
  //   Sum: '<S504>/Sum'

  rtDW.IntegralGain_e = 0.0;

  // Sum: '<S594>/SumD' incorporates:
  //   Gain: '<S602>/Filter Coefficient'
  //   Integrator: '<S594>/Filter'
  //   UnaryMinus: '<S593>/Unary Minus'

  rtDW.SumD_n = 0.0 - rtP.N * rtX.Filter_CSTATE_e;

  // Gain: '<S596>/Integral Gain' incorporates:
  //   Sum: '<S504>/Sum1'

  rtDW.IntegralGain_k = 0.0;

  // Sum: '<S646>/SumD' incorporates:
  //   Gain: '<S654>/Filter Coefficient'
  //   Integrator: '<S646>/Filter'
  //   UnaryMinus: '<S645>/Unary Minus'

  rtDW.SumD_m = 0.0 - rtP.N * rtX.Filter_CSTATE_j5;

  // Gain: '<S648>/Integral Gain' incorporates:
  //   Sum: '<S504>/Sum2'

  rtDW.IntegralGain_c = 0.0;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S172>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_es[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_es[1];

      // Update for UnitDelay: '<S172>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_i[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_i[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_i[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_i[3];

      // Update for UnitDelay: '<S173>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_k[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_k[1];

      // Update for UnitDelay: '<S173>/Unit Delay'
      rtDW.UnitDelay_DSTATE_f[0] = rtDW.P_kl[0];
      rtDW.UnitDelay_DSTATE_f[1] = rtDW.P_kl[1];
      rtDW.UnitDelay_DSTATE_f[2] = rtDW.P_kl[2];
      rtDW.UnitDelay_DSTATE_f[3] = rtDW.P_kl[3];

      // Update for UnitDelay: '<S175>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_o[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_o[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S175>/Unit Delay'
      rtDW.UnitDelay_DSTATE_k[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_k[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_k[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_k[3] = rtDW.P_k[3];

      // Update for UnitDelay: '<S502>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE_b[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S502>/Unit Delay'
      rtDW.UnitDelay_DSTATE_kf[0] = rtDW.P_b[0];
      rtDW.UnitDelay_DSTATE_kf[1] = rtDW.P_b[1];
      rtDW.UnitDelay_DSTATE_kf[2] = rtDW.P_b[2];
      rtDW.UnitDelay_DSTATE_kf[3] = rtDW.P_b[3];

      // Update for UnitDelay: '<S503>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_as[0] = rtDW.x_dach_o[0];
      rtDW.UnitDelay1_DSTATE_as[1] = rtDW.x_dach_o[1];

      // Update for UnitDelay: '<S503>/Unit Delay'
      rtDW.UnitDelay_DSTATE_m[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_m[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_m[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_m[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S505>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S505>/Unit Delay'
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

  // Derivatives for Integrator: '<S153>/Integrator'
  _rtXdot->Integrator_CSTATE = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S148>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S101>/Integrator'
  _rtXdot->Integrator_CSTATE_a = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S96>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_j;

  // Derivatives for Integrator: '<S49>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S44>/Filter'
  _rtXdot->Filter_CSTATE_l = rtDW.FilterCoefficient_l;

  // Derivatives for Integrator: '<S176>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S14>/Integrator'
  _rtXdot->Integrator_CSTATE_b[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S176>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S14>/Integrator'
  _rtXdot->Integrator_CSTATE_b[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S176>/Integrator'
  _rtXdot->Integrator_CSTATE_ay[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S14>/Integrator'
  _rtXdot->Integrator_CSTATE_b[2] = rtDW.TmpSignalConversionAtIntegrator[2];
  for (i = 0; i < 6; i++) {
    // Derivatives for Integrator: '<S4>/Integrator'
    _rtXdot->Integrator_CSTATE_e[i] = rtDW.dx_c[i];

    // Derivatives for Integrator: '<S6>/Integrator'
    _rtXdot->Integrator_CSTATE_h[i] = rtDW.dx[i];
  }

  // Derivatives for Integrator: '<S483>/Integrator'
  _rtXdot->Integrator_CSTATE_am = rtDW.IntegralGain_lw;

  // Derivatives for Integrator: '<S478>/Filter'
  _rtXdot->Filter_CSTATE_p = rtDW.FilterCoefficient_o;

  // Derivatives for Integrator: '<S431>/Integrator'
  _rtXdot->Integrator_CSTATE_j2 = rtDW.IntegralGain_di;

  // Derivatives for Integrator: '<S426>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_p;

  // Derivatives for Integrator: '<S379>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S374>/Filter'
  _rtXdot->Filter_CSTATE_k = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S506>/Integrator'
  _rtXdot->Integrator_CSTATE_n[0] = rtDW.Sum_j[0];

  // Derivatives for Integrator: '<S344>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.TmpSignalConversionAtIntegrat_j[0];

  // Derivatives for Integrator: '<S506>/Integrator'
  _rtXdot->Integrator_CSTATE_n[1] = rtDW.Sum_j[1];

  // Derivatives for Integrator: '<S344>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.TmpSignalConversionAtIntegrat_j[1];

  // Derivatives for Integrator: '<S506>/Integrator'
  _rtXdot->Integrator_CSTATE_n[2] = rtDW.Sum_j[2];

  // Derivatives for Integrator: '<S344>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.TmpSignalConversionAtIntegrat_j[2];

  // Derivatives for Integrator: '<S172>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_es[1];

  // Derivatives for Integrator: '<S173>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_k[1];

  // Derivatives for Integrator: '<S175>/Integrator1'
  _rtXdot->Integrator1_CSTATE_d = rtDW.x_dach_g[1];

  // Derivatives for Integrator: '<S212>/Filter'
  _rtXdot->Filter_CSTATE_mg = rtDW.SumD;

  // Derivatives for Integrator: '<S217>/Integrator'
  _rtXdot->Integrator_CSTATE_bg = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S264>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.SumD_h;

  // Derivatives for Integrator: '<S269>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_im;

  // Derivatives for Integrator: '<S316>/Filter'
  _rtXdot->Filter_CSTATE_lf = rtDW.SumD_e;

  // Derivatives for Integrator: '<S321>/Integrator'
  _rtXdot->Integrator_CSTATE_bj = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S502>/Integrator1'
  _rtXdot->Integrator1_CSTATE_g = rtDW.x_dach_e[1];

  // Derivatives for Integrator: '<S503>/Integrator1'
  _rtXdot->Integrator1_CSTATE_m = rtDW.x_dach_o[1];

  // Derivatives for Integrator: '<S505>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach[1];

  // Derivatives for Integrator: '<S542>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.SumD_d;

  // Derivatives for Integrator: '<S547>/Integrator'
  _rtXdot->Integrator_CSTATE_my = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S594>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_n;

  // Derivatives for Integrator: '<S599>/Integrator'
  _rtXdot->Integrator_CSTATE_bu = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S646>/Filter'
  _rtXdot->Filter_CSTATE_j5 = rtDW.SumD_m;

  // Derivatives for Integrator: '<S651>/Integrator'
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

    // InitializeConditions for UnitDelay: '<S172>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S172>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S173>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_a[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_a[1];

    // InitializeConditions for UnitDelay: '<S173>/Unit Delay'
    rtDW.UnitDelay_DSTATE_f[0] = rtP.UnitDelay_InitialCondition_i[0];
    rtDW.UnitDelay_DSTATE_f[1] = rtP.UnitDelay_InitialCondition_i[1];
    rtDW.UnitDelay_DSTATE_f[2] = rtP.UnitDelay_InitialCondition_i[2];
    rtDW.UnitDelay_DSTATE_f[3] = rtP.UnitDelay_InitialCondition_i[3];

    // InitializeConditions for UnitDelay: '<S175>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_o[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_o[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S175>/Unit Delay'
    rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_g[0];
    rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_g[1];
    rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_g[2];
    rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_g[3];

    // InitializeConditions for Integrator: '<S153>/Integrator'
    rtX.Integrator_CSTATE = rtP.PIDController2_InitialCondit_cd;

    // InitializeConditions for Integrator: '<S148>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S101>/Integrator'
    rtX.Integrator_CSTATE_a = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S96>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S49>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController_InitialConditio_d;

    // InitializeConditions for Integrator: '<S44>/Filter'
    rtX.Filter_CSTATE_l = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S176>/Integrator'
    rtX.Integrator_CSTATE_ay[0] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S14>/Integrator'
    rtX.Integrator_CSTATE_b[0] = rtP.Integrator_IC_m;

    // InitializeConditions for Integrator: '<S176>/Integrator'
    rtX.Integrator_CSTATE_ay[1] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S14>/Integrator'
    rtX.Integrator_CSTATE_b[1] = rtP.Integrator_IC_m;

    // InitializeConditions for Integrator: '<S176>/Integrator'
    rtX.Integrator_CSTATE_ay[2] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S14>/Integrator'
    rtX.Integrator_CSTATE_b[2] = rtP.Integrator_IC_m;
    for (i = 0; i < 6; i++) {
      // InitializeConditions for Integrator: '<S4>/Integrator'
      rtX.Integrator_CSTATE_e[i] = rtP.Integrator_IC_g[i];

      // InitializeConditions for Integrator: '<S6>/Integrator'
      rtX.Integrator_CSTATE_h[i] = rtP.Integrator_IC_b[i];
    }

    // InitializeConditions for Integrator: '<S483>/Integrator'
    rtX.Integrator_CSTATE_am = rtP.PIDController2_InitialConditi_o;

    // InitializeConditions for Integrator: '<S478>/Filter'
    rtX.Filter_CSTATE_p = rtP.PIDController2_InitialConditi_m;

    // InitializeConditions for Integrator: '<S431>/Integrator'
    rtX.Integrator_CSTATE_j2 = rtP.PIDController1_InitialConditi_e;

    // InitializeConditions for Integrator: '<S426>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController1_InitialConditi_p;

    // InitializeConditions for Integrator: '<S379>/Integrator'
    rtX.Integrator_CSTATE_m = rtP.PIDController_InitialConditio_n;

    // InitializeConditions for Integrator: '<S374>/Filter'
    rtX.Filter_CSTATE_k = rtP.PIDController_InitialConditio_j;

    // InitializeConditions for UnitDelay: '<S502>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b[0] = rtP.UnitDelay1_InitialCondition_j[0];
    rtDW.UnitDelay1_DSTATE_b[1] = rtP.UnitDelay1_InitialCondition_j[1];

    // InitializeConditions for UnitDelay: '<S502>/Unit Delay'
    rtDW.UnitDelay_DSTATE_kf[0] = rtP.UnitDelay_InitialCondition_n[0];
    rtDW.UnitDelay_DSTATE_kf[1] = rtP.UnitDelay_InitialCondition_n[1];
    rtDW.UnitDelay_DSTATE_kf[2] = rtP.UnitDelay_InitialCondition_n[2];
    rtDW.UnitDelay_DSTATE_kf[3] = rtP.UnitDelay_InitialCondition_n[3];

    // InitializeConditions for UnitDelay: '<S503>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_as[0] = rtP.UnitDelay1_InitialCondition_e[0];
    rtDW.UnitDelay1_DSTATE_as[1] = rtP.UnitDelay1_InitialCondition_e[1];

    // InitializeConditions for UnitDelay: '<S503>/Unit Delay'
    rtDW.UnitDelay_DSTATE_m[0] = rtP.UnitDelay_InitialCondition_f[0];
    rtDW.UnitDelay_DSTATE_m[1] = rtP.UnitDelay_InitialCondition_f[1];
    rtDW.UnitDelay_DSTATE_m[2] = rtP.UnitDelay_InitialCondition_f[2];
    rtDW.UnitDelay_DSTATE_m[3] = rtP.UnitDelay_InitialCondition_f[3];

    // InitializeConditions for UnitDelay: '<S505>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S505>/Unit Delay'
    rtDW.UnitDelay_DSTATE_j[0] = rtP.UnitDelay_InitialCondition_k[0];
    rtDW.UnitDelay_DSTATE_j[1] = rtP.UnitDelay_InitialCondition_k[1];
    rtDW.UnitDelay_DSTATE_j[2] = rtP.UnitDelay_InitialCondition_k[2];
    rtDW.UnitDelay_DSTATE_j[3] = rtP.UnitDelay_InitialCondition_k[3];

    // InitializeConditions for Integrator: '<S506>/Integrator'
    rtX.Integrator_CSTATE_n[0] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S344>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S506>/Integrator'
    rtX.Integrator_CSTATE_n[1] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S344>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S506>/Integrator'
    rtX.Integrator_CSTATE_n[2] = rtP.Integrator_IC_gx;

    // InitializeConditions for Integrator: '<S344>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S172>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S173>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S175>/Integrator1'
    rtX.Integrator1_CSTATE_d = rtP.Integrator1_IC_p;

    // InitializeConditions for Integrator: '<S212>/Filter'
    rtX.Filter_CSTATE_mg = rtP.PIDController_InitialConditio_i;

    // InitializeConditions for Integrator: '<S217>/Integrator'
    rtX.Integrator_CSTATE_bg = rtP.PIDController_InitialConditi_ay;

    // InitializeConditions for Integrator: '<S264>/Filter'
    rtX.Filter_CSTATE_j = rtP.PIDController1_InitialConditi_n;

    // InitializeConditions for Integrator: '<S269>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController1_InitialCondit_nz;

    // InitializeConditions for Integrator: '<S316>/Filter'
    rtX.Filter_CSTATE_lf = rtP.PIDController2_InitialConditi_h;

    // InitializeConditions for Integrator: '<S321>/Integrator'
    rtX.Integrator_CSTATE_bj = rtP.PIDController2_InitialConditi_n;

    // InitializeConditions for Integrator: '<S502>/Integrator1'
    rtX.Integrator1_CSTATE_g = rtP.Integrator1_IC_h;

    // InitializeConditions for Integrator: '<S503>/Integrator1'
    rtX.Integrator1_CSTATE_m = rtP.Integrator1_IC_n;

    // InitializeConditions for Integrator: '<S505>/Integrator1'
    rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_ph;

    // InitializeConditions for Integrator: '<S542>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S547>/Integrator'
    rtX.Integrator_CSTATE_my = rtP.PIDController_InitialConditio_b;

    // InitializeConditions for Integrator: '<S594>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController1_InitialConditi_a;

    // InitializeConditions for Integrator: '<S599>/Integrator'
    rtX.Integrator_CSTATE_bu = rtP.PIDController1_InitialConditi_b;

    // InitializeConditions for Integrator: '<S646>/Filter'
    rtX.Filter_CSTATE_j5 = rtP.PIDController2_InitialConditi_c;

    // InitializeConditions for Integrator: '<S651>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController2_InitialConditi_k;
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
