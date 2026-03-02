//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.432
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Mar  2 17:08:49 2026
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
  int_T nXc { 27 };

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
//    '<S1>/MATLAB Function'
//    '<S7>/MATLAB Function'
//
void Controller::MATLABFunction(const real_T rtu_tau[4], real_T rty_u[4])
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
  std::memcpy(&A[0], &rtP.E[0], sizeof(real_T) << 4U);
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
  real_T A[9];
  real_T tmp_0[9];
  real_T tmp[6];
  real_T rtb_VectorConcatenate1[4];
  real_T rtb_thrust[4];
  real_T rtb_u[4];
  real_T B_1[3];
  real_T a21;
  real_T b_idx_2;
  real_T maxval;
  real_T omega_dot_idx_1;
  real_T omega_dot_idx_2;
  real_T rtb_Sum2;
  real_T rtb_TransferFcn;
  real_T rtb_TransferFcn_a;
  real_T tmp_1;
  real_T tmp_2;
  int32_T r1;
  int32_T r2;
  int32_T r3;
  int32_T rtemp;
  if ((&rtM)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&rtM)->isMinorTimeStep()) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  if ((&rtM)->isMajorTimeStep()) {
    // UnitDelay: '<S3>/Unit Delay1'
    rtDW.x_dach_h[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_h[1] = rtDW.UnitDelay1_DSTATE[1];

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
                 [0], rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_h,
                 rtDW.P_i);

    // UnitDelay: '<S4>/Unit Delay1'
    rtDW.x_dach_l[0] = rtDW.UnitDelay1_DSTATE_n[0];
    rtDW.x_dach_l[1] = rtDW.UnitDelay1_DSTATE_n[1];

    // MATLAB Function: '<S4>/KF_Elevation' incorporates:
    //   Constant: '<S4>/Constant'
    //   Constant: '<S4>/Constant1'
    //   Constant: '<S4>/Constant2'
    //   Constant: '<S4>/Constant5'
    //   Constant: '<S4>/Cov Messrauschen'
    //   Constant: '<S4>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S4>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_i, rtP.Constant1_Value_n,
                 rtP.Constant2_Value_e, rtP.CovProzessrauschen_Value_n,
                 rtP.CovMessrauschen_Value_n, rtU.y[1], rtP.Constant5_Value_l,
                 rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_l, rtDW.P_l);

    // UnitDelay: '<S6>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_p[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_p[1];

    // MATLAB Function: '<S6>/KF_Elevation' incorporates:
    //   Constant: '<S6>/Constant'
    //   Constant: '<S6>/Constant1'
    //   Constant: '<S6>/Constant2'
    //   Constant: '<S6>/Constant5'
    //   Constant: '<S6>/Cov Messrauschen'
    //   Constant: '<S6>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S6>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_d, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_m, rtP.CovProzessrauschen_Value_i,
                 rtP.CovMessrauschen_Value_j, rtU.y[2], rtP.Constant5_Value_n,
                 rtDW.UnitDelay_DSTATE_d, rtDW.x_dach, rtDW.P_g);
  }

  // TransferFcn: '<S3>/Transfer Fcn'
  rtb_TransferFcn = rtP.TransferFcn_C * rtX.TransferFcn_CSTATE;

  // TransferFcn: '<S4>/Transfer Fcn'
  rtb_TransferFcn_a = rtP.TransferFcn_C_a * rtX.TransferFcn_CSTATE_p;

  // TransferFcn: '<S6>/Transfer Fcn'
  rtb_Sum2 = rtP.TransferFcn_C_n * rtX.TransferFcn_CSTATE_k;

  // SignalConversion generated from: '<S8>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S8>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[0] = rtU.w[0];

  // SignalConversion generated from: '<S8>/Gain'
  tmp[0] = rtDW.x_dach_h[0];
  tmp[1] = rtDW.x_dach_l[0];
  tmp[2] = rtDW.x_dach[0];
  tmp[3] = rtb_TransferFcn;
  tmp[4] = rtb_TransferFcn_a;
  tmp[5] = rtb_Sum2;

  // Gain: '<S8>/Gain1' incorporates:
  //   Inport: '<Root>/w'

  a21 = 0.0;
  tmp_1 = 0.0;
  tmp_2 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtU.w[r2 + 1];
    a21 += rtP.V[3 * r2] * maxval;
    tmp_1 += rtP.V[3 * r2 + 1] * maxval;
    tmp_2 += rtP.V[3 * r2 + 2] * maxval;
  }

  // End of Gain: '<S8>/Gain1'

  // Gain: '<S8>/Gain'
  maxval = 0.0;
  omega_dot_idx_1 = 0.0;
  omega_dot_idx_2 = 0.0;
  for (r2 = 0; r2 < 6; r2++) {
    b_idx_2 = tmp[r2];
    maxval += rtP.K[3 * r2] * b_idx_2;
    omega_dot_idx_1 += rtP.K[3 * r2 + 1] * b_idx_2;
    omega_dot_idx_2 += rtP.K[3 * r2 + 2] * b_idx_2;
  }

  // Sum: '<S8>/Sum2' incorporates:
  //   Concatenate: '<S8>/Vector Concatenate1'
  //   Gain: '<S8>/Gain'
  //   Gain: '<S8>/Gain2'
  //   Integrator: '<S8>/Integrator'

  rtb_VectorConcatenate1[1] = (a21 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE[0];
  rtb_VectorConcatenate1[2] = (tmp_1 - omega_dot_idx_1) + rtP.Ki[1] *
    rtX.Integrator_CSTATE[1];
  rtb_VectorConcatenate1[3] = (tmp_2 - omega_dot_idx_2) + rtP.Ki[2] *
    rtX.Integrator_CSTATE[2];

  // MATLAB Function: '<S1>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1, rtb_u);

  // Saturate: '<S1>/Saturation'
  if (rtb_u[0] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_UpperSat;
  } else if (rtb_u[0] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[0] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[0] = rtb_u[0];
  }

  if (rtb_u[1] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_UpperSat;
  } else if (rtb_u[1] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[1] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[1] = rtb_u[1];
  }

  if (rtb_u[2] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_UpperSat;
  } else if (rtb_u[2] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[2] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[2] = rtb_u[2];
  }

  if (rtb_u[3] > rtP.Saturation_UpperSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_UpperSat;
  } else if (rtb_u[3] < rtP.Saturation_LowerSat) {
    // Outport: '<Root>/u'
    rtY.u[3] = rtP.Saturation_LowerSat;
  } else {
    // Outport: '<Root>/u'
    rtY.u[3] = rtb_u[3];
  }

  // End of Saturate: '<S1>/Saturation'

  // SignalConversion generated from: '<Root>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtb_TransferFcn;
  rtDW.TmpSignalConversionAtIntegrator[1] = rtb_TransferFcn_a;
  rtDW.TmpSignalConversionAtIntegrator[2] = rtb_Sum2;

  // Sum: '<S8>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum[0] = rtU.w[1] - rtDW.x_dach_h[0];
  rtDW.Sum[1] = rtU.w[2] - rtDW.x_dach_l[0];
  rtDW.Sum[2] = rtU.w[3] - rtDW.x_dach[0];

  // SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[3] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Integrator: '<Root>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[0] = rtX.Integrator_CSTATE_p[0];

  // SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[4] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Integrator: '<Root>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[1] = rtX.Integrator_CSTATE_p[1];

  // SignalConversion generated from: '<Root>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[5] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Integrator: '<Root>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[2] = rtX.Integrator_CSTATE_p[2];

  // MATLAB Function: '<S2>/MATLAB Function' incorporates:
  //   Integrator: '<S2>/Integrator'

  tmp_0[0] = 1.0;
  tmp_0[3] = std::sin(rtX.Integrator_CSTATE_o[0]) * std::tan
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[6] = std::cos(rtX.Integrator_CSTATE_o[0]) * std::tan
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[1] = 0.0;
  tmp_0[4] = std::cos(rtX.Integrator_CSTATE_o[0]);
  tmp_0[7] = -std::sin(rtX.Integrator_CSTATE_o[0]);
  tmp_0[2] = 0.0;
  tmp_0[5] = std::sin(rtX.Integrator_CSTATE_o[0]) / std::cos
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[8] = std::cos(rtX.Integrator_CSTATE_o[0]) / std::cos
    (rtX.Integrator_CSTATE_o[1]);
  rtY.y_pred[0] = rtX.Integrator_CSTATE_o[0];
  a21 = 0.0;
  rtY.y_pred[1] = rtX.Integrator_CSTATE_o[1];
  tmp_1 = 0.0;
  rtY.y_pred[2] = rtX.Integrator_CSTATE_o[2];
  tmp_2 = 0.0;

  // SignalConversion generated from: '<S9>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S9>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[0] = rtU.w[0];

  // Gain: '<S9>/Gain1'
  rtb_TransferFcn = 0.0;
  rtb_TransferFcn_a = 0.0;
  rtb_Sum2 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    // MATLAB Function: '<S2>/MATLAB Function' incorporates:
    //   Gain: '<S9>/Gain1'
    //   Integrator: '<S2>/Integrator'

    maxval = rtX.Integrator_CSTATE_o[r2 + 3];
    a21 += tmp_0[3 * r2] * maxval;
    r1 = 3 * r2 + 1;
    tmp_1 += tmp_0[r1] * maxval;
    r3 = 3 * r2 + 2;
    tmp_2 += tmp_0[r3] * maxval;

    // Gain: '<S9>/Gain1' incorporates:
    //   Inport: '<Root>/w'

    maxval = rtU.w[r2 + 1];
    rtb_TransferFcn += rtP.V[3 * r2] * maxval;
    rtb_TransferFcn_a += rtP.V[r1] * maxval;
    rtb_Sum2 += rtP.V[r3] * maxval;
  }

  // MATLAB Function: '<S2>/MATLAB Function'
  rtY.y_pred[3] = a21;
  rtY.y_pred[4] = tmp_1;
  rtY.y_pred[5] = tmp_2;

  // Gain: '<S9>/Gain'
  maxval = 0.0;
  omega_dot_idx_1 = 0.0;
  omega_dot_idx_2 = 0.0;
  for (r2 = 0; r2 < 6; r2++) {
    b_idx_2 = rtY.y_pred[r2];
    maxval += rtP.K[3 * r2] * b_idx_2;
    omega_dot_idx_1 += rtP.K[3 * r2 + 1] * b_idx_2;
    omega_dot_idx_2 += rtP.K[3 * r2 + 2] * b_idx_2;
  }

  // Sum: '<S9>/Sum2' incorporates:
  //   Concatenate: '<S9>/Vector Concatenate1'
  //   Gain: '<S9>/Gain'
  //   Gain: '<S9>/Gain2'
  //   Integrator: '<S9>/Integrator'

  rtb_VectorConcatenate1[1] = (rtb_TransferFcn - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE_c[0];
  rtb_VectorConcatenate1[2] = (rtb_TransferFcn_a - omega_dot_idx_1) + rtP.Ki[1] *
    rtX.Integrator_CSTATE_c[1];
  rtb_VectorConcatenate1[3] = (rtb_Sum2 - omega_dot_idx_2) + rtP.Ki[2] *
    rtX.Integrator_CSTATE_c[2];

  // MATLAB Function: '<S7>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1, rtb_u);

  // Saturate: '<S7>/Saturation'
  if (rtb_u[0] > rtP.Saturation_UpperSat_o) {
    maxval = rtP.Saturation_UpperSat_o;
  } else if (rtb_u[0] < rtP.Saturation_LowerSat_g) {
    maxval = rtP.Saturation_LowerSat_g;
  } else {
    maxval = rtb_u[0];
  }

  // MATLAB Function: '<S2>/MATLAB Function1' incorporates:
  //   Saturate: '<S7>/Saturation'

  a21 = maxval - rtP.b;
  rtb_thrust[0] = a21 * a21;

  // Saturate: '<S7>/Saturation'
  if (rtb_u[1] > rtP.Saturation_UpperSat_o) {
    maxval = rtP.Saturation_UpperSat_o;
  } else if (rtb_u[1] < rtP.Saturation_LowerSat_g) {
    maxval = rtP.Saturation_LowerSat_g;
  } else {
    maxval = rtb_u[1];
  }

  // MATLAB Function: '<S2>/MATLAB Function1' incorporates:
  //   Saturate: '<S7>/Saturation'

  a21 = maxval - rtP.b;
  rtb_thrust[1] = a21 * a21;

  // Saturate: '<S7>/Saturation'
  if (rtb_u[2] > rtP.Saturation_UpperSat_o) {
    maxval = rtP.Saturation_UpperSat_o;
  } else if (rtb_u[2] < rtP.Saturation_LowerSat_g) {
    maxval = rtP.Saturation_LowerSat_g;
  } else {
    maxval = rtb_u[2];
  }

  // MATLAB Function: '<S2>/MATLAB Function1' incorporates:
  //   Saturate: '<S7>/Saturation'

  a21 = maxval - rtP.b;
  rtb_thrust[2] = a21 * a21;

  // Saturate: '<S7>/Saturation'
  if (rtb_u[3] > rtP.Saturation_UpperSat_o) {
    maxval = rtP.Saturation_UpperSat_o;
  } else if (rtb_u[3] < rtP.Saturation_LowerSat_g) {
    maxval = rtP.Saturation_LowerSat_g;
  } else {
    maxval = rtb_u[3];
  }

  // MATLAB Function: '<S2>/MATLAB Function1' incorporates:
  //   Saturate: '<S7>/Saturation'

  a21 = maxval - rtP.b;
  rtb_thrust[3] = a21 * a21;

  // Gain: '<S2>/Mixer' incorporates:
  //   MATLAB Function: '<S2>/MATLAB Function1'

  a21 = 0.0;
  tmp_1 = 0.0;
  tmp_2 = 0.0;
  for (r2 = 0; r2 < 4; r2++) {
    maxval = rtP.a * rtb_thrust[r2];
    r1 = r2 << 2;
    a21 += rtP.E[r1 + 1] * maxval;
    tmp_1 += rtP.E[r1 + 2] * maxval;
    tmp_2 += rtP.E[r1 + 3] * maxval;
  }

  // MATLAB Function: '<S2>/MATLAB Function2' incorporates:
  //   Gain: '<S2>/Mixer'
  //   Integrator: '<S2>/Integrator'

  omega_dot_idx_1 = 0.0;
  omega_dot_idx_2 = 0.0;
  b_idx_2 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtX.Integrator_CSTATE_o[r2 + 3];
    omega_dot_idx_1 += rtP.I[3 * r2] * maxval;
    omega_dot_idx_2 += rtP.I[3 * r2 + 1] * maxval;
    b_idx_2 += rtP.I[3 * r2 + 2] * maxval;
  }

  std::memcpy(&A[0], &rtP.I[0], 9U * sizeof(real_T));
  B_1[0] = ((rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_o[0]) * std::cos
             (rtX.Integrator_CSTATE_o[1]) * rtP.d + a21) + -rtP.p *
            rtX.Integrator_CSTATE_o[3]) - (b_idx_2 * rtX.Integrator_CSTATE_o[4]
    - omega_dot_idx_2 * rtX.Integrator_CSTATE_o[5]);
  B_1[1] = ((rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_o[1]) * rtP.d +
             tmp_1) + -rtP.p * rtX.Integrator_CSTATE_o[4]) - (omega_dot_idx_1 *
    rtX.Integrator_CSTATE_o[5] - b_idx_2 * rtX.Integrator_CSTATE_o[3]);
  B_1[2] = (-rtP.p * rtX.Integrator_CSTATE_o[5] + tmp_2) - (omega_dot_idx_2 *
    rtX.Integrator_CSTATE_o[3] - omega_dot_idx_1 * rtX.Integrator_CSTATE_o[4]);
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = std::abs(rtP.I[0]);
  a21 = std::abs(rtP.I[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (std::abs(rtP.I[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  A[r2] = rtP.I[r2] / rtP.I[r1];
  A[r3] /= A[r1];
  A[r2 + 3] -= A[r1 + 3] * A[r2];
  A[r3 + 3] -= A[r1 + 3] * A[r3];
  A[r2 + 6] -= A[r1 + 6] * A[r2];
  A[r3 + 6] -= A[r1 + 6] * A[r3];
  if (std::abs(A[r3 + 3]) > std::abs(A[r2 + 3])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  A[r3 + 3] /= A[r2 + 3];
  A[r3 + 6] -= A[r3 + 3] * A[r2 + 6];
  omega_dot_idx_1 = B_1[r2] - B_1[r1] * A[r2];
  omega_dot_idx_2 = ((B_1[r3] - B_1[r1] * A[r3]) - A[r3 + 3] * omega_dot_idx_1) /
    A[r3 + 6];
  omega_dot_idx_1 = (omega_dot_idx_1 - A[r2 + 6] * omega_dot_idx_2) / A[r2 + 3];
  tmp_0[0] = 1.0;
  tmp_0[3] = std::sin(rtX.Integrator_CSTATE_o[0]) * std::tan
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[6] = std::cos(rtX.Integrator_CSTATE_o[0]) * std::tan
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[1] = 0.0;
  tmp_0[4] = std::cos(rtX.Integrator_CSTATE_o[0]);
  tmp_0[7] = -std::sin(rtX.Integrator_CSTATE_o[0]);
  tmp_0[2] = 0.0;
  tmp_0[5] = std::sin(rtX.Integrator_CSTATE_o[0]) / std::cos
    (rtX.Integrator_CSTATE_o[1]);
  tmp_0[8] = std::cos(rtX.Integrator_CSTATE_o[0]) / std::cos
    (rtX.Integrator_CSTATE_o[1]);
  a21 = 0.0;
  tmp_1 = 0.0;
  tmp_2 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtX.Integrator_CSTATE_o[r2 + 3];
    a21 += tmp_0[3 * r2] * maxval;
    tmp_1 += tmp_0[3 * r2 + 1] * maxval;
    tmp_2 += tmp_0[3 * r2 + 2] * maxval;
  }

  rtDW.dx[0] = a21;
  rtDW.dx[3] = ((B_1[r1] - A[r1 + 6] * omega_dot_idx_2) - A[r1 + 3] *
                omega_dot_idx_1) / A[r1];

  // Sum: '<S9>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_m[0] = rtU.w[1] - rtY.y_pred[0];

  // MATLAB Function: '<S2>/MATLAB Function2'
  rtDW.dx[1] = tmp_1;
  rtDW.dx[4] = omega_dot_idx_1;

  // Sum: '<S9>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_m[1] = rtU.w[2] - rtY.y_pred[1];

  // MATLAB Function: '<S2>/MATLAB Function2'
  rtDW.dx[2] = tmp_2;
  rtDW.dx[5] = omega_dot_idx_2;

  // Sum: '<S9>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_m[2] = rtU.w[3] - rtY.y_pred[2];

  // Sum: '<S48>/SumD' incorporates:
  //   Gain: '<S56>/Filter Coefficient'
  //   Integrator: '<S48>/Filter'
  //   UnaryMinus: '<S47>/Unary Minus'

  rtDW.SumD = 0.0 - rtP.ke * rtX.Filter_CSTATE;

  // Gain: '<S50>/Integral Gain' incorporates:
  //   Sum: '<S5>/Sum'

  rtDW.IntegralGain = 0.0;

  // Sum: '<S100>/SumD' incorporates:
  //   Gain: '<S108>/Filter Coefficient'
  //   Integrator: '<S100>/Filter'
  //   UnaryMinus: '<S99>/Unary Minus'

  rtDW.SumD_o = 0.0 - rtP.ke * rtX.Filter_CSTATE_h;

  // Gain: '<S102>/Integral Gain' incorporates:
  //   Sum: '<S5>/Sum1'

  rtDW.IntegralGain_o = 0.0;

  // Sum: '<S152>/SumD' incorporates:
  //   Gain: '<S160>/Filter Coefficient'
  //   Integrator: '<S152>/Filter'
  //   UnaryMinus: '<S151>/Unary Minus'

  rtDW.SumD_j = 0.0 - rtP.ke * rtX.Filter_CSTATE_a;

  // Gain: '<S154>/Integral Gain' incorporates:
  //   Sum: '<S5>/Sum2'

  rtDW.IntegralGain_p = 0.0;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S3>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_h[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_h[1];

      // Update for UnitDelay: '<S3>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_i[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_i[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_i[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_i[3];

      // Update for UnitDelay: '<S4>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_n[0] = rtDW.x_dach_l[0];
      rtDW.UnitDelay1_DSTATE_n[1] = rtDW.x_dach_l[1];

      // Update for UnitDelay: '<S4>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_l[3];

      // Update for UnitDelay: '<S6>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_p[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_p[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S6>/Unit Delay'
      rtDW.UnitDelay_DSTATE_d[0] = rtDW.P_g[0];
      rtDW.UnitDelay_DSTATE_d[1] = rtDW.P_g[1];
      rtDW.UnitDelay_DSTATE_d[2] = rtDW.P_g[2];
      rtDW.UnitDelay_DSTATE_d[3] = rtDW.P_g[3];
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

  // Derivatives for TransferFcn: '<S3>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE = rtP.TransferFcn_A * rtX.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += rtDW.x_dach_h[1];

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE_p = rtP.TransferFcn_A_c * rtX.TransferFcn_CSTATE_p;
  _rtXdot->TransferFcn_CSTATE_p += rtDW.x_dach_l[1];

  // Derivatives for TransferFcn: '<S6>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE_k = rtP.TransferFcn_A_o * rtX.TransferFcn_CSTATE_k;
  _rtXdot->TransferFcn_CSTATE_k += rtDW.x_dach[1];

  // Derivatives for Integrator: '<S8>/Integrator'
  _rtXdot->Integrator_CSTATE[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S8>/Integrator'
  _rtXdot->Integrator_CSTATE[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S8>/Integrator'
  _rtXdot->Integrator_CSTATE[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S2>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE_o[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S2>/Integrator'

  // Derivatives for Integrator: '<S9>/Integrator'
  _rtXdot->Integrator_CSTATE_c[0] = rtDW.Sum_m[0];
  _rtXdot->Integrator_CSTATE_c[1] = rtDW.Sum_m[1];
  _rtXdot->Integrator_CSTATE_c[2] = rtDW.Sum_m[2];

  // Derivatives for Integrator: '<S3>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_h[1];

  // Derivatives for Integrator: '<S4>/Integrator1'
  _rtXdot->Integrator1_CSTATE_o = rtDW.x_dach_l[1];

  // Derivatives for Integrator: '<S6>/Integrator1'
  _rtXdot->Integrator1_CSTATE_j = rtDW.x_dach[1];

  // Derivatives for Integrator: '<S48>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD;

  // Derivatives for Integrator: '<S53>/Integrator'
  _rtXdot->Integrator_CSTATE_pg = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S100>/Filter'
  _rtXdot->Filter_CSTATE_h = rtDW.SumD_o;

  // Derivatives for Integrator: '<S105>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S152>/Filter'
  _rtXdot->Filter_CSTATE_a = rtDW.SumD_j;

  // Derivatives for Integrator: '<S157>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_p;
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

    // InitializeConditions for UnitDelay: '<S3>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S3>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S4>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_n[0] = rtP.UnitDelay1_InitialCondition_c[0];
    rtDW.UnitDelay1_DSTATE_n[1] = rtP.UnitDelay1_InitialCondition_c[1];

    // InitializeConditions for UnitDelay: '<S4>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_c[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_c[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_c[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_c[3];

    // InitializeConditions for UnitDelay: '<S6>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_p[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_p[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S6>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_cm[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_cm[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_cm[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_cm[3];

    // InitializeConditions for TransferFcn: '<S3>/Transfer Fcn'
    rtX.TransferFcn_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn'
    rtX.TransferFcn_CSTATE_p = 0.0;

    // InitializeConditions for TransferFcn: '<S6>/Transfer Fcn'
    rtX.TransferFcn_CSTATE_k = 0.0;

    // InitializeConditions for Integrator: '<S8>/Integrator'
    rtX.Integrator_CSTATE[0] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<Root>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S8>/Integrator'
    rtX.Integrator_CSTATE[1] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<Root>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S8>/Integrator'
    rtX.Integrator_CSTATE[2] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<Root>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE_o[i] = rtP.Integrator_IC_m[i];
    }

    // End of InitializeConditions for Integrator: '<S2>/Integrator'

    // InitializeConditions for Integrator: '<S9>/Integrator'
    rtX.Integrator_CSTATE_c[0] = rtP.Integrator_IC_cm;
    rtX.Integrator_CSTATE_c[1] = rtP.Integrator_IC_cm;
    rtX.Integrator_CSTATE_c[2] = rtP.Integrator_IC_cm;

    // InitializeConditions for Integrator: '<S3>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S4>/Integrator1'
    rtX.Integrator1_CSTATE_o = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S6>/Integrator1'
    rtX.Integrator1_CSTATE_j = rtP.Integrator1_IC_l;

    // InitializeConditions for Integrator: '<S48>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S53>/Integrator'
    rtX.Integrator_CSTATE_pg = rtP.PIDController_InitialConditio_d;

    // InitializeConditions for Integrator: '<S100>/Filter'
    rtX.Filter_CSTATE_h = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S105>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S152>/Filter'
    rtX.Filter_CSTATE_a = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S157>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController2_InitialConditi_o;
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
