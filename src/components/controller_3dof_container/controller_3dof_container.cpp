//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.480
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Mar  7 19:10:15 2026
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
#include <cstring>
#include <cmath>

// private model entry point functions
extern void controller_3dof_container_derivatives();

//
// This function updates continuous states using the ODE1 fixed-step
// solver algorithm
//
void Controller3dof::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE1_IntgData *id { static_cast<ODE1_IntgData *>(rtsiGetSolverData(si)) };

  real_T *f0 { id->f[0] };

  int_T i;
  int_T nXc { 36 };

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
//    '<S8>/MATLAB Function'
//    '<S177>/MATLAB Function'
//
void Controller3dof::MATLABFunction(const real_T rtu_tau[4], real_T rty_u[4])
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
//    '<S9>/KF_Elevation'
//    '<S10>/KF_Elevation'
//    '<S12>/KF_Elevation'
//
void Controller3dof::KF_Elevation(const real_T rtu_A[4], const real_T rtu_B[2],
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
void Controller3dof::step()
{
  real_T A[9];
  real_T tmp_1[9];
  real_T tmp_0[6];
  real_T rtb_VectorConcatenate1[4];
  real_T rtb_thrust[4];
  real_T rtb_u[4];
  real_T B_1[3];
  real_T a21;
  real_T b_idx_1;
  real_T b_idx_2;
  real_T maxval;
  real_T tau_idx_0;
  real_T tau_idx_1;
  real_T tmp_2;
  real_T tmp_3;
  int32_T i;
  int32_T r2;
  int32_T r3;
  int32_T rtemp;
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

  tmp = ((&rtM)->isMajorTimeStep());
  if (tmp) {
    // UnitDelay: '<S178>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S178>/KF_Elevation' incorporates:
    //   Constant: '<S178>/Constant'
    //   Constant: '<S178>/Constant1'
    //   Constant: '<S178>/Constant2'
    //   Constant: '<S178>/Constant5'
    //   Constant: '<S178>/Cov Messrauschen'
    //   Constant: '<S178>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S178>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, rtU.y
                 [0], rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_g,
                 rtDW.P_n);

    // UnitDelay: '<S179>/Unit Delay1'
    rtDW.x_dach_n[0] = rtDW.UnitDelay1_DSTATE_b[0];
    rtDW.x_dach_n[1] = rtDW.UnitDelay1_DSTATE_b[1];

    // MATLAB Function: '<S179>/KF_Elevation' incorporates:
    //   Constant: '<S179>/Constant'
    //   Constant: '<S179>/Constant1'
    //   Constant: '<S179>/Constant2'
    //   Constant: '<S179>/Constant5'
    //   Constant: '<S179>/Cov Messrauschen'
    //   Constant: '<S179>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S179>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_i, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_d,
                 rtP.CovMessrauschen_Value_i, rtU.y[1], rtP.Constant5_Value_b,
                 rtDW.UnitDelay_DSTATE_g, rtDW.x_dach_n, rtDW.P_d);

    // UnitDelay: '<S181>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_n[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_n[1];

    // MATLAB Function: '<S181>/KF_Elevation' incorporates:
    //   Constant: '<S181>/Constant'
    //   Constant: '<S181>/Constant1'
    //   Constant: '<S181>/Constant2'
    //   Constant: '<S181>/Constant5'
    //   Constant: '<S181>/Cov Messrauschen'
    //   Constant: '<S181>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S181>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_d,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_i,
                 rtP.CovMessrauschen_Value_o, rtU.y[2], rtP.Constant5_Value_bx,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach, rtDW.P_h);
  }

  // SignalConversion generated from: '<S182>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S182>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[0] = rtU.w[0];

  // SignalConversion generated from: '<S182>/Gain'
  tmp_0[0] = rtDW.x_dach_g[0];
  tmp_0[1] = rtDW.x_dach_n[0];
  tmp_0[2] = rtDW.x_dach[0];
  tmp_0[3] = rtDW.x_dach_g[1];
  tmp_0[4] = rtDW.x_dach_n[1];
  tmp_0[5] = rtDW.x_dach[1];

  // Gain: '<S182>/Gain1' incorporates:
  //   Inport: '<Root>/w'

  tmp_2 = 0.0;
  tau_idx_0 = 0.0;
  tmp_3 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtU.w[r2 + 1];
    tmp_2 += rtP.V[3 * r2] * maxval;
    tau_idx_0 += rtP.V[3 * r2 + 1] * maxval;
    tmp_3 += rtP.V[3 * r2 + 2] * maxval;
  }

  // End of Gain: '<S182>/Gain1'

  // Gain: '<S182>/Gain'
  maxval = 0.0;
  a21 = 0.0;
  tau_idx_1 = 0.0;
  for (r2 = 0; r2 < 6; r2++) {
    b_idx_1 = tmp_0[r2];
    maxval += rtP.K[3 * r2] * b_idx_1;
    a21 += rtP.K[3 * r2 + 1] * b_idx_1;
    tau_idx_1 += rtP.K[3 * r2 + 2] * b_idx_1;
  }

  // Sum: '<S182>/Sum2' incorporates:
  //   Concatenate: '<S182>/Vector Concatenate1'
  //   Gain: '<S182>/Gain'
  //   Gain: '<S182>/Gain2'
  //   Integrator: '<S182>/Integrator'

  rtb_VectorConcatenate1[1] = (tmp_2 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE[0];
  rtb_VectorConcatenate1[2] = (tau_idx_0 - a21) + rtP.Ki[1] *
    rtX.Integrator_CSTATE[1];
  rtb_VectorConcatenate1[3] = (tmp_3 - tau_idx_1) + rtP.Ki[2] *
    rtX.Integrator_CSTATE[2];

  // MATLAB Function: '<S177>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1, rtb_u);

  // Saturate: '<S177>/Saturation'
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

  // End of Saturate: '<S177>/Saturation'

  // SignalConversion generated from: '<S3>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_g[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_n[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach[1];

  // Sum: '<S182>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum[0] = rtU.w[1] - rtDW.x_dach_g[0];
  rtDW.Sum[1] = rtU.w[2] - rtDW.x_dach_n[0];
  rtDW.Sum[2] = rtU.w[3] - rtDW.x_dach[0];

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[3] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[0] = rtX.Integrator_CSTATE_f[0];

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[4] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[1] = rtX.Integrator_CSTATE_f[1];

  // SignalConversion generated from: '<S3>/Vector Concatenate' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[5] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Integrator: '<S3>/Integrator' incorporates:
  //   Outport: '<Root>/values'

  rtY.values[2] = rtX.Integrator_CSTATE_f[2];

  // Outport: '<Root>/x_pred' incorporates:
  //   Integrator: '<S4>/Integrator'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i] = rtX.Integrator_CSTATE_j[i];
  }

  // End of Outport: '<Root>/x_pred'

  // SignalConversion generated from: '<S13>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S13>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtb_VectorConcatenate1[0] = rtU.w[0];
  if (tmp) {
    // UnitDelay: '<S9>/Unit Delay1'
    rtDW.x_dach_d[0] = rtDW.UnitDelay1_DSTATE_m[0];
    rtDW.x_dach_d[1] = rtDW.UnitDelay1_DSTATE_m[1];

    // MATLAB Function: '<S9>/KF_Elevation' incorporates:
    //   Constant: '<S9>/Constant'
    //   Constant: '<S9>/Constant1'
    //   Constant: '<S9>/Constant2'
    //   Constant: '<S9>/Constant5'
    //   Constant: '<S9>/Cov Messrauschen'
    //   Constant: '<S9>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S9>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p3, rtP.Constant1_Value_e,
                 rtP.Constant2_Value_i, rtP.CovProzessrauschen_Value_j,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE_j[0],
                 rtP.Constant5_Value_m, rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_d,
                 rtDW.P_dr);

    // UnitDelay: '<S10>/Unit Delay1'
    rtDW.x_dach_j[0] = rtDW.UnitDelay1_DSTATE_f[0];
    rtDW.x_dach_j[1] = rtDW.UnitDelay1_DSTATE_f[1];

    // MATLAB Function: '<S10>/KF_Elevation' incorporates:
    //   Constant: '<S10>/Constant'
    //   Constant: '<S10>/Constant1'
    //   Constant: '<S10>/Constant2'
    //   Constant: '<S10>/Constant5'
    //   Constant: '<S10>/Cov Messrauschen'
    //   Constant: '<S10>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S10>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_j, rtP.Constant1_Value_m,
                 rtP.Constant2_Value_a, rtP.CovProzessrauschen_Value_o,
                 rtP.CovMessrauschen_Value_e, rtX.Integrator_CSTATE_j[1],
                 rtP.Constant5_Value_i, rtDW.UnitDelay_DSTATE_i, rtDW.x_dach_j,
                 rtDW.P_nu);

    // UnitDelay: '<S12>/Unit Delay1'
    rtDW.x_dach_a[0] = rtDW.UnitDelay1_DSTATE_a[0];
    rtDW.x_dach_a[1] = rtDW.UnitDelay1_DSTATE_a[1];

    // MATLAB Function: '<S12>/KF_Elevation' incorporates:
    //   Constant: '<S12>/Constant'
    //   Constant: '<S12>/Constant1'
    //   Constant: '<S12>/Constant2'
    //   Constant: '<S12>/Constant5'
    //   Constant: '<S12>/Cov Messrauschen'
    //   Constant: '<S12>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S12>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a, rtP.Constant1_Value_i,
                 rtP.Constant2_Value_pn, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_fj, rtX.Integrator_CSTATE_j[2],
                 rtP.Constant5_Value_k, rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_a,
                 rtDW.P_j);
  }

  // SignalConversion generated from: '<S13>/Gain'
  tmp_0[0] = rtDW.x_dach_d[0];
  tmp_0[1] = rtDW.x_dach_j[0];
  tmp_0[2] = rtDW.x_dach_a[0];
  tmp_0[3] = rtDW.x_dach_d[1];
  tmp_0[4] = rtDW.x_dach_j[1];
  tmp_0[5] = rtDW.x_dach_a[1];

  // Gain: '<S13>/Gain1' incorporates:
  //   Inport: '<Root>/w'

  tmp_2 = 0.0;
  tau_idx_0 = 0.0;
  tmp_3 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtU.w[r2 + 1];
    tmp_2 += rtP.V[3 * r2] * maxval;
    tau_idx_0 += rtP.V[3 * r2 + 1] * maxval;
    tmp_3 += rtP.V[3 * r2 + 2] * maxval;
  }

  // End of Gain: '<S13>/Gain1'

  // Gain: '<S13>/Gain'
  maxval = 0.0;
  a21 = 0.0;
  tau_idx_1 = 0.0;
  for (r2 = 0; r2 < 6; r2++) {
    b_idx_1 = tmp_0[r2];
    maxval += rtP.K[3 * r2] * b_idx_1;
    a21 += rtP.K[3 * r2 + 1] * b_idx_1;
    tau_idx_1 += rtP.K[3 * r2 + 2] * b_idx_1;
  }

  // Sum: '<S13>/Sum2' incorporates:
  //   Concatenate: '<S13>/Vector Concatenate1'
  //   Gain: '<S13>/Gain'
  //   Gain: '<S13>/Gain2'
  //   Integrator: '<S13>/Integrator'

  rtb_VectorConcatenate1[1] = (tmp_2 - maxval) + rtP.Ki[0] *
    rtX.Integrator_CSTATE_p[0];
  rtb_VectorConcatenate1[2] = (tau_idx_0 - a21) + rtP.Ki[1] *
    rtX.Integrator_CSTATE_p[1];
  rtb_VectorConcatenate1[3] = (tmp_3 - tau_idx_1) + rtP.Ki[2] *
    rtX.Integrator_CSTATE_p[2];

  // MATLAB Function: '<S8>/MATLAB Function'
  MATLABFunction(rtb_VectorConcatenate1, rtb_u);

  // Saturate: '<S8>/Saturation'
  if (rtb_u[0] > rtP.Saturation_UpperSat_l) {
    maxval = rtP.Saturation_UpperSat_l;
  } else if (rtb_u[0] < rtP.Saturation_LowerSat_m) {
    maxval = rtP.Saturation_LowerSat_m;
  } else {
    maxval = rtb_u[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  maxval -= rtP.b;
  rtb_thrust[0] = maxval * maxval;

  // Saturate: '<S8>/Saturation'
  if (rtb_u[1] > rtP.Saturation_UpperSat_l) {
    maxval = rtP.Saturation_UpperSat_l;
  } else if (rtb_u[1] < rtP.Saturation_LowerSat_m) {
    maxval = rtP.Saturation_LowerSat_m;
  } else {
    maxval = rtb_u[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  maxval -= rtP.b;
  rtb_thrust[1] = maxval * maxval;

  // Saturate: '<S8>/Saturation'
  if (rtb_u[2] > rtP.Saturation_UpperSat_l) {
    maxval = rtP.Saturation_UpperSat_l;
  } else if (rtb_u[2] < rtP.Saturation_LowerSat_m) {
    maxval = rtP.Saturation_LowerSat_m;
  } else {
    maxval = rtb_u[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  maxval -= rtP.b;
  rtb_thrust[2] = maxval * maxval;

  // Saturate: '<S8>/Saturation'
  if (rtb_u[3] > rtP.Saturation_UpperSat_l) {
    maxval = rtP.Saturation_UpperSat_l;
  } else if (rtb_u[3] < rtP.Saturation_LowerSat_m) {
    maxval = rtP.Saturation_LowerSat_m;
  } else {
    maxval = rtb_u[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  maxval -= rtP.b;
  rtb_thrust[3] = maxval * maxval;

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Integrator: '<S4>/Integrator'

  maxval = (-rtP.p[0] * rtX.Integrator_CSTATE_j[3] + -rtP.p[1] *
            rtX.Integrator_CSTATE_j[4]) + -rtP.p[2] * rtX.Integrator_CSTATE_j[5];

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  tau_idx_0 = 0.0;
  tmp_3 = 0.0;
  tmp_2 = 0.0;
  for (r2 = 0; r2 < 4; r2++) {
    a21 = rtP.a * rtb_thrust[r2];
    i = r2 << 2;
    tau_idx_0 += rtP.B_eff[i + 1] * a21;
    tmp_3 += rtP.B_eff[i + 2] * a21;
    tmp_2 += rtP.B_eff[i + 3] * a21;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'

  tau_idx_0 += maxval;
  tau_idx_1 = tmp_3 + maxval;
  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_j[0]) * std::cos
      (rtX.Integrator_CSTATE_j[1]) * rtP.h;
    tau_idx_1 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_j[1]) * rtP.h;
  }

  tmp_3 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    a21 = rtX.Integrator_CSTATE_j[r2 + 3];
    tmp_3 += rtP.J[3 * r2] * a21;
    b_idx_1 += rtP.J[3 * r2 + 1] * a21;
    b_idx_2 += rtP.J[3 * r2 + 2] * a21;
  }

  std::memcpy(&A[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = (tau_idx_0 + maxval) - (b_idx_2 * rtX.Integrator_CSTATE_j[4] -
    b_idx_1 * rtX.Integrator_CSTATE_j[5]);
  B_1[1] = (tau_idx_1 + maxval) - (tmp_3 * rtX.Integrator_CSTATE_j[5] - b_idx_2 *
    rtX.Integrator_CSTATE_j[3]);
  B_1[2] = ((tmp_2 + maxval) + maxval) - (b_idx_1 * rtX.Integrator_CSTATE_j[3] -
    tmp_3 * rtX.Integrator_CSTATE_j[4]);
  i = 0;
  r2 = 1;
  r3 = 2;
  maxval = std::abs(rtP.J[0]);
  a21 = std::abs(rtP.J[1]);
  if (a21 > maxval) {
    maxval = a21;
    i = 1;
    r2 = 0;
  }

  if (std::abs(rtP.J[2]) > maxval) {
    i = 2;
    r2 = 1;
    r3 = 0;
  }

  A[r2] = rtP.J[r2] / rtP.J[i];
  A[r3] /= A[i];
  A[r2 + 3] -= A[i + 3] * A[r2];
  A[r3 + 3] -= A[i + 3] * A[r3];
  A[r2 + 6] -= A[i + 6] * A[r2];
  A[r3 + 6] -= A[i + 6] * A[r3];
  if (std::abs(A[r3 + 3]) > std::abs(A[r2 + 3])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }

  A[r3 + 3] /= A[r2 + 3];
  A[r3 + 6] -= A[r3 + 3] * A[r2 + 6];
  tau_idx_1 = B_1[r2] - B_1[i] * A[r2];
  a21 = ((B_1[r3] - B_1[i] * A[r3]) - A[r3 + 3] * tau_idx_1) / A[r3 + 6];
  tau_idx_1 = (tau_idx_1 - A[r2 + 6] * a21) / A[r2 + 3];
  tmp_1[0] = 1.0;
  tmp_1[3] = std::sin(rtX.Integrator_CSTATE_j[0]) * std::tan
    (rtX.Integrator_CSTATE_j[1]);
  tmp_1[6] = std::cos(rtX.Integrator_CSTATE_j[0]) * std::tan
    (rtX.Integrator_CSTATE_j[1]);
  tmp_1[1] = 0.0;
  tmp_1[4] = std::cos(rtX.Integrator_CSTATE_j[0]);
  tmp_1[7] = -std::sin(rtX.Integrator_CSTATE_j[0]);
  tmp_1[2] = 0.0;
  tmp_1[5] = std::sin(rtX.Integrator_CSTATE_j[0]) / std::cos
    (rtX.Integrator_CSTATE_j[1]);
  tmp_1[8] = std::cos(rtX.Integrator_CSTATE_j[0]) / std::cos
    (rtX.Integrator_CSTATE_j[1]);
  tmp_2 = 0.0;
  tau_idx_0 = 0.0;
  tmp_3 = 0.0;
  for (r2 = 0; r2 < 3; r2++) {
    maxval = rtX.Integrator_CSTATE_j[r2 + 3];
    tmp_2 += tmp_1[3 * r2] * maxval;
    tau_idx_0 += tmp_1[3 * r2 + 1] * maxval;
    tmp_3 += tmp_1[3 * r2 + 2] * maxval;
  }

  rtDW.dx[0] = tmp_2;
  rtDW.dx[3] = ((B_1[i] - A[i + 6] * a21) - A[i + 3] * tau_idx_1) / A[i];
  rtDW.dx[1] = tau_idx_0;
  rtDW.dx[4] = tau_idx_1;
  rtDW.dx[2] = tmp_3;
  rtDW.dx[5] = a21;

  // SignalConversion generated from: '<S2>/Integrator'
  rtDW.TmpSignalConversionAtIntegrat_j[0] = rtDW.x_dach_d[1];
  rtDW.TmpSignalConversionAtIntegrat_j[1] = rtDW.x_dach_j[1];
  rtDW.TmpSignalConversionAtIntegrat_j[2] = rtDW.x_dach_a[1];

  // Sum: '<S13>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtDW.Sum_f[0] = rtU.w[1] - rtDW.x_dach_d[0];
  rtDW.Sum_f[1] = rtU.w[2] - rtDW.x_dach_j[0];
  rtDW.Sum_f[2] = rtU.w[3] - rtDW.x_dach_a[0];

  // Sum: '<S49>/SumD' incorporates:
  //   Gain: '<S57>/Filter Coefficient'
  //   Integrator: '<S49>/Filter'
  //   UnaryMinus: '<S48>/Unary Minus'

  rtDW.SumD = 0.0 - rtP.N * rtX.Filter_CSTATE;

  // Gain: '<S51>/Integral Gain' incorporates:
  //   Sum: '<S11>/Sum'

  rtDW.IntegralGain = 0.0;

  // Sum: '<S101>/SumD' incorporates:
  //   Gain: '<S109>/Filter Coefficient'
  //   Integrator: '<S101>/Filter'
  //   UnaryMinus: '<S100>/Unary Minus'

  rtDW.SumD_k = 0.0 - rtP.N * rtX.Filter_CSTATE_e;

  // Gain: '<S103>/Integral Gain' incorporates:
  //   Sum: '<S11>/Sum1'

  rtDW.IntegralGain_d = 0.0;

  // Sum: '<S153>/SumD' incorporates:
  //   Gain: '<S161>/Filter Coefficient'
  //   Integrator: '<S153>/Filter'
  //   UnaryMinus: '<S152>/Unary Minus'

  rtDW.SumD_e = 0.0 - rtP.N * rtX.Filter_CSTATE_j;

  // Gain: '<S155>/Integral Gain' incorporates:
  //   Sum: '<S11>/Sum2'

  rtDW.IntegralGain_k = 0.0;

  // Sum: '<S218>/SumD' incorporates:
  //   Gain: '<S226>/Filter Coefficient'
  //   Integrator: '<S218>/Filter'
  //   UnaryMinus: '<S217>/Unary Minus'

  rtDW.SumD_el = 0.0 - rtP.N * rtX.Filter_CSTATE_n;

  // Gain: '<S220>/Integral Gain' incorporates:
  //   Sum: '<S180>/Sum'

  rtDW.IntegralGain_l = 0.0;

  // Sum: '<S270>/SumD' incorporates:
  //   Gain: '<S278>/Filter Coefficient'
  //   Integrator: '<S270>/Filter'
  //   UnaryMinus: '<S269>/Unary Minus'

  rtDW.SumD_kb = 0.0 - rtP.N * rtX.Filter_CSTATE_i;

  // Gain: '<S272>/Integral Gain' incorporates:
  //   Sum: '<S180>/Sum1'

  rtDW.IntegralGain_m = 0.0;

  // Sum: '<S322>/SumD' incorporates:
  //   Gain: '<S330>/Filter Coefficient'
  //   Integrator: '<S322>/Filter'
  //   UnaryMinus: '<S321>/Unary Minus'

  rtDW.SumD_kz = 0.0 - rtP.N * rtX.Filter_CSTATE_c;

  // Gain: '<S324>/Integral Gain' incorporates:
  //   Sum: '<S180>/Sum2'

  rtDW.IntegralGain_p = 0.0;
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S178>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S178>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S179>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b[0] = rtDW.x_dach_n[0];
      rtDW.UnitDelay1_DSTATE_b[1] = rtDW.x_dach_n[1];

      // Update for UnitDelay: '<S179>/Unit Delay'
      rtDW.UnitDelay_DSTATE_g[0] = rtDW.P_d[0];
      rtDW.UnitDelay_DSTATE_g[1] = rtDW.P_d[1];
      rtDW.UnitDelay_DSTATE_g[2] = rtDW.P_d[2];
      rtDW.UnitDelay_DSTATE_g[3] = rtDW.P_d[3];

      // Update for UnitDelay: '<S181>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_n[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_n[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S181>/Unit Delay'
      rtDW.UnitDelay_DSTATE_f[0] = rtDW.P_h[0];
      rtDW.UnitDelay_DSTATE_f[1] = rtDW.P_h[1];
      rtDW.UnitDelay_DSTATE_f[2] = rtDW.P_h[2];
      rtDW.UnitDelay_DSTATE_f[3] = rtDW.P_h[3];

      // Update for UnitDelay: '<S9>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_m[0] = rtDW.x_dach_d[0];
      rtDW.UnitDelay1_DSTATE_m[1] = rtDW.x_dach_d[1];

      // Update for UnitDelay: '<S9>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_dr[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_dr[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_dr[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_dr[3];

      // Update for UnitDelay: '<S10>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_f[0] = rtDW.x_dach_j[0];
      rtDW.UnitDelay1_DSTATE_f[1] = rtDW.x_dach_j[1];

      // Update for UnitDelay: '<S10>/Unit Delay'
      rtDW.UnitDelay_DSTATE_i[0] = rtDW.P_nu[0];
      rtDW.UnitDelay_DSTATE_i[1] = rtDW.P_nu[1];
      rtDW.UnitDelay_DSTATE_i[2] = rtDW.P_nu[2];
      rtDW.UnitDelay_DSTATE_i[3] = rtDW.P_nu[3];

      // Update for UnitDelay: '<S12>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_a[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_a[1];

      // Update for UnitDelay: '<S12>/Unit Delay'
      rtDW.UnitDelay_DSTATE_d[0] = rtDW.P_j[0];
      rtDW.UnitDelay_DSTATE_d[1] = rtDW.P_j[1];
      rtDW.UnitDelay_DSTATE_d[2] = rtDW.P_j[2];
      rtDW.UnitDelay_DSTATE_d[3] = rtDW.P_j[3];
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
void Controller3dof::controller_3dof_container_derivatives()
{
  Controller3dof::XDot *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S182>/Integrator'
  _rtXdot->Integrator_CSTATE[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S182>/Integrator'
  _rtXdot->Integrator_CSTATE[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S182>/Integrator'
  _rtXdot->Integrator_CSTATE[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S4>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE_j[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S4>/Integrator'

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.Sum_f[0];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[0] = rtDW.TmpSignalConversionAtIntegrat_j[0];

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.Sum_f[1];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[1] = rtDW.TmpSignalConversionAtIntegrat_j[1];

  // Derivatives for Integrator: '<S13>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.Sum_f[2];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[2] = rtDW.TmpSignalConversionAtIntegrat_j[2];

  // Derivatives for Integrator: '<S9>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_d[1];

  // Derivatives for Integrator: '<S10>/Integrator1'
  _rtXdot->Integrator1_CSTATE_i = rtDW.x_dach_j[1];

  // Derivatives for Integrator: '<S12>/Integrator1'
  _rtXdot->Integrator1_CSTATE_k = rtDW.x_dach_a[1];

  // Derivatives for Integrator: '<S49>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD;

  // Derivatives for Integrator: '<S54>/Integrator'
  _rtXdot->Integrator_CSTATE_jb = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S101>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_k;

  // Derivatives for Integrator: '<S106>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S153>/Filter'
  _rtXdot->Filter_CSTATE_j = rtDW.SumD_e;

  // Derivatives for Integrator: '<S158>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S178>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach_g[1];

  // Derivatives for Integrator: '<S179>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_n[1];

  // Derivatives for Integrator: '<S181>/Integrator1'
  _rtXdot->Integrator1_CSTATE_km = rtDW.x_dach[1];

  // Derivatives for Integrator: '<S218>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.SumD_el;

  // Derivatives for Integrator: '<S223>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S270>/Filter'
  _rtXdot->Filter_CSTATE_i = rtDW.SumD_kb;

  // Derivatives for Integrator: '<S275>/Integrator'
  _rtXdot->Integrator_CSTATE_ja = rtDW.IntegralGain_m;

  // Derivatives for Integrator: '<S322>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.SumD_kz;

  // Derivatives for Integrator: '<S327>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_p;
}

// Model initialize function
void Controller3dof::initialize()
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

    // InitializeConditions for UnitDelay: '<S178>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S178>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S179>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_b[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S179>/Unit Delay'
    rtDW.UnitDelay_DSTATE_g[0] = rtP.UnitDelay_InitialCondition_p[0];
    rtDW.UnitDelay_DSTATE_g[1] = rtP.UnitDelay_InitialCondition_p[1];
    rtDW.UnitDelay_DSTATE_g[2] = rtP.UnitDelay_InitialCondition_p[2];
    rtDW.UnitDelay_DSTATE_g[3] = rtP.UnitDelay_InitialCondition_p[3];

    // InitializeConditions for UnitDelay: '<S181>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_n[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_n[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S181>/Unit Delay'
    rtDW.UnitDelay_DSTATE_f[0] = rtP.UnitDelay_InitialCondition_e[0];
    rtDW.UnitDelay_DSTATE_f[1] = rtP.UnitDelay_InitialCondition_e[1];
    rtDW.UnitDelay_DSTATE_f[2] = rtP.UnitDelay_InitialCondition_e[2];
    rtDW.UnitDelay_DSTATE_f[3] = rtP.UnitDelay_InitialCondition_e[3];

    // InitializeConditions for Integrator: '<S182>/Integrator'
    rtX.Integrator_CSTATE[0] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S3>/Integrator'
    rtX.Integrator_CSTATE_f[0] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S182>/Integrator'
    rtX.Integrator_CSTATE[1] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S3>/Integrator'
    rtX.Integrator_CSTATE_f[1] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S182>/Integrator'
    rtX.Integrator_CSTATE[2] = rtP.Integrator_IC;

    // InitializeConditions for Integrator: '<S3>/Integrator'
    rtX.Integrator_CSTATE_f[2] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S4>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE_j[i] = rtP.Integrator_IC_k[i];
    }

    // End of InitializeConditions for Integrator: '<S4>/Integrator'

    // InitializeConditions for UnitDelay: '<S9>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_m[0] = rtP.UnitDelay1_InitialCondition_e[0];
    rtDW.UnitDelay1_DSTATE_m[1] = rtP.UnitDelay1_InitialCondition_e[1];

    // InitializeConditions for UnitDelay: '<S9>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_m[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_m[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_m[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_m[3];

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_d[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_d[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_d[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_d[3];

    // InitializeConditions for UnitDelay: '<S12>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_m2[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_m2[1];

    // InitializeConditions for UnitDelay: '<S12>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_e2[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_e2[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_e2[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_e2[3];

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_kc;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[0] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_kc;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[1] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S13>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_kc;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[2] = rtP.Integrator_IC_c;

    // InitializeConditions for Integrator: '<S9>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S10>/Integrator1'
    rtX.Integrator1_CSTATE_i = rtP.Integrator1_IC_e;

    // InitializeConditions for Integrator: '<S12>/Integrator1'
    rtX.Integrator1_CSTATE_k = rtP.Integrator1_IC_e4;

    // InitializeConditions for Integrator: '<S49>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S54>/Integrator'
    rtX.Integrator_CSTATE_jb = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S101>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S106>/Integrator'
    rtX.Integrator_CSTATE_c = rtP.PIDController1_InitialConditi_p;

    // InitializeConditions for Integrator: '<S153>/Filter'
    rtX.Filter_CSTATE_j = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S158>/Integrator'
    rtX.Integrator_CSTATE_o = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S178>/Integrator1'
    rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S179>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_l;

    // InitializeConditions for Integrator: '<S181>/Integrator1'
    rtX.Integrator1_CSTATE_km = rtP.Integrator1_IC_o;

    // InitializeConditions for Integrator: '<S218>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController_InitialConditio_c;

    // InitializeConditions for Integrator: '<S223>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S270>/Filter'
    rtX.Filter_CSTATE_i = rtP.PIDController1_InitialConditi_k;

    // InitializeConditions for Integrator: '<S275>/Integrator'
    rtX.Integrator_CSTATE_ja = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S322>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_j;

    // InitializeConditions for Integrator: '<S327>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController2_InitialConditi_m;
  }
}

time_T** Controller3dof::RT_MODEL::getTPtrPtr()
{
  return &(Timing.t);
}

boolean_T Controller3dof::RT_MODEL::getStopRequested() const
{
  return (Timing.stopRequestedFlag);
}

void Controller3dof::RT_MODEL::setStopRequested(boolean_T aStopRequested)
{
  (Timing.stopRequestedFlag = aStopRequested);
}

const char_T* Controller3dof::RT_MODEL::getErrorStatus() const
{
  return (errorStatus);
}

void Controller3dof::RT_MODEL::setErrorStatus(const char_T* const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

time_T* Controller3dof::RT_MODEL::getTPtr() const
{
  return (Timing.t);
}

void Controller3dof::RT_MODEL::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

boolean_T* Controller3dof::RT_MODEL::getStopRequestedPtr()
{
  return (&(Timing.stopRequestedFlag));
}

const char_T** Controller3dof::RT_MODEL::getErrorStatusPtr()
{
  return &errorStatus;
}

boolean_T Controller3dof::RT_MODEL::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

boolean_T Controller3dof::RT_MODEL::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

time_T Controller3dof::RT_MODEL::getTStart() const
{
  return (Timing.tStart);
}

// Constructor
Controller3dof::Controller3dof() :
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
Controller3dof::~Controller3dof() = default;

// Real-Time Model get method
Controller3dof::RT_MODEL * Controller3dof::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
