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
// C/C++ source code generated on : Sat Mar  7 15:55:02 2026
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
  int_T nXc { 30 };

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
  real_T A[16];
  real_T A_0[9];
  real_T tmp_0[9];
  real_T B_0[4];
  real_T c_data[4];
  real_T rtb_thrust[4];
  real_T rtb_u_e[4];
  real_T B_1[3];
  real_T b_idx_1;
  real_T b_idx_2;
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_gy;
  real_T rtb_FilterCoefficient_o;
  real_T rtb_Sum_l;
  real_T rtb_UnaryMinus;
  real_T rtb_UnaryMinus_a;
  real_T s;
  real_T smax;
  real_T tau_idx_0;
  real_T tau_idx_2;
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
  //   Integrator: '<S4>/Integrator'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i] = rtX.Integrator_CSTATE[i];
  }

  // End of Outport: '<Root>/x_pred'
  tmp = ((&rtM)->isMajorTimeStep());
  if (tmp) {
    // UnitDelay: '<S9>/Unit Delay1'
    rtDW.x_dach_d[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_d[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S9>/KF_Elevation' incorporates:
    //   Constant: '<S9>/Constant'
    //   Constant: '<S9>/Constant1'
    //   Constant: '<S9>/Constant2'
    //   Constant: '<S9>/Constant5'
    //   Constant: '<S9>/Cov Messrauschen'
    //   Constant: '<S9>/Cov Prozessrauschen'
    //   Integrator: '<S4>/Integrator'
    //   UnitDelay: '<S9>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value,
                 rtX.Integrator_CSTATE[0], rtP.Constant5_Value,
                 rtDW.UnitDelay_DSTATE, rtDW.x_dach_d, rtDW.P_dr);
  }

  // Sum: '<S11>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtb_FilterCoefficient = rtU.w[1] - rtDW.x_dach_d[0];

  // Gain: '<S56>/Filter Coefficient' incorporates:
  //   Integrator: '<S48>/Filter'

  rtb_FilterCoefficient_gy = rtP.N * rtX.Filter_CSTATE;
  if (tmp) {
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
                 rtP.CovMessrauschen_Value_e, rtX.Integrator_CSTATE[1],
                 rtP.Constant5_Value_i, rtDW.UnitDelay_DSTATE_i, rtDW.x_dach_j,
                 rtDW.P_nu);
  }

  // Sum: '<S11>/Sum1' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus = rtU.w[2] - rtDW.x_dach_j[0];

  // Gain: '<S108>/Filter Coefficient' incorporates:
  //   Integrator: '<S100>/Filter'

  rtb_FilterCoefficient_o = rtP.N * rtX.Filter_CSTATE_e;
  if (tmp) {
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
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_f, rtX.Integrator_CSTATE[2],
                 rtP.Constant5_Value_k, rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_a,
                 rtDW.P_j);
  }

  // Sum: '<S11>/Sum2' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus_a = rtU.w[3] - rtDW.x_dach_a[0];

  // Gain: '<S160>/Filter Coefficient' incorporates:
  //   Integrator: '<S152>/Filter'

  rtb_Sum_l = rtP.N * rtX.Filter_CSTATE_j;

  // MATLAB Function: '<S8>/MATLAB Function' incorporates:
  //   Gain: '<S110>/Proportional Gain'
  //   Gain: '<S162>/Proportional Gain'
  //   Gain: '<S58>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S105>/Integrator'
  //   Integrator: '<S157>/Integrator'
  //   Integrator: '<S53>/Integrator'
  //   SignalConversion generated from: '<S13>/ SFunction '
  //   Sum: '<S114>/Sum'
  //   Sum: '<S166>/Sum'
  //   Sum: '<S62>/Sum'

  B_0[0] = rtU.w[0];
  B_0[1] = (rtP.kp_roll * rtb_FilterCoefficient + rtX.Integrator_CSTATE_j) +
    rtb_FilterCoefficient_gy;
  B_0[2] = (rtP.kp_pitch * rtb_UnaryMinus + rtX.Integrator_CSTATE_c) +
    rtb_FilterCoefficient_o;
  B_0[3] = (rtP.kp_yaw * rtb_UnaryMinus_a + rtX.Integrator_CSTATE_o) + rtb_Sum_l;
  std::memcpy(&A[0], &rtP.B_eff[0], sizeof(real_T) << 4U);
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

  rtb_u_e[0] = 0.0;
  rtb_u_e[1] = 0.0;
  rtb_u_e[2] = 0.0;
  rtb_u_e[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = B_0[tmp_data[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_u_e[tmp_data[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S8>/Saturation'
  if (rtb_u_e[0] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[0] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  smax -= rtP.b;
  rtb_thrust[0] = smax * smax;

  // Saturate: '<S8>/Saturation'
  if (rtb_u_e[1] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[1] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  smax -= rtP.b;
  rtb_thrust[1] = smax * smax;

  // Saturate: '<S8>/Saturation'
  if (rtb_u_e[2] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[2] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  smax -= rtP.b;
  rtb_thrust[2] = smax * smax;

  // Saturate: '<S8>/Saturation'
  if (rtb_u_e[3] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_u_e[3] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_u_e[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S8>/Saturation'

  smax -= rtP.b;
  rtb_thrust[3] = smax * smax;

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Integrator: '<S4>/Integrator'

  smax = (-rtP.p[0] * rtX.Integrator_CSTATE[3] + -rtP.p[1] *
          rtX.Integrator_CSTATE[4]) + -rtP.p[2] * rtX.Integrator_CSTATE[5];

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  tau_idx_2 = 0.0;
  for (jj = 0; jj < 4; jj++) {
    tmp_1 = rtP.a * rtb_thrust[jj];
    i = jj << 2;
    tau_idx_0 += rtP.B_eff[i + 1] * tmp_1;
    tmp_2 += rtP.B_eff[i + 2] * tmp_1;
    tau_idx_2 += rtP.B_eff[i + 3] * tmp_1;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'

  tau_idx_0 += smax;
  s = tmp_2 + smax;
  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[0]) * std::cos
      (rtX.Integrator_CSTATE[1]) * rtP.h;
    s += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[1]) * rtP.h;
  }

  tmp_2 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    tmp_1 = rtX.Integrator_CSTATE[jj + 3];
    tmp_2 += rtP.J[3 * jj] * tmp_1;
    b_idx_1 += rtP.J[3 * jj + 1] * tmp_1;
    b_idx_2 += rtP.J[3 * jj + 2] * tmp_1;
  }

  std::memcpy(&A_0[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = (tau_idx_0 + smax) - (b_idx_2 * rtX.Integrator_CSTATE[4] - b_idx_1 *
    rtX.Integrator_CSTATE[5]);
  B_1[1] = (s + smax) - (tmp_2 * rtX.Integrator_CSTATE[5] - b_idx_2 *
    rtX.Integrator_CSTATE[3]);
  B_1[2] = ((tau_idx_2 + smax) + smax) - (b_idx_1 * rtX.Integrator_CSTATE[3] -
    tmp_2 * rtX.Integrator_CSTATE[4]);
  i = 0;
  jj = 1;
  jA = 2;
  smax = std::abs(rtP.J[0]);
  s = std::abs(rtP.J[1]);
  if (s > smax) {
    smax = s;
    i = 1;
    jj = 0;
  }

  if (std::abs(rtP.J[2]) > smax) {
    i = 2;
    jj = 1;
    jA = 0;
  }

  A_0[jj] = rtP.J[jj] / rtP.J[i];
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
  s = B_1[jj] - B_1[i] * A_0[jj];
  tau_idx_2 = ((B_1[jA] - B_1[i] * A_0[jA]) - A_0[jA + 3] * s) / A_0[jA + 6];
  s = (s - A_0[jj + 6] * tau_idx_2) / A_0[jj + 3];
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
  tmp_1 = 0.0;
  tau_idx_0 = 0.0;
  tmp_2 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    smax = rtX.Integrator_CSTATE[jj + 3];
    tmp_1 += tmp_0[3 * jj] * smax;
    tau_idx_0 += tmp_0[3 * jj + 1] * smax;
    tmp_2 += tmp_0[3 * jj + 2] * smax;
  }

  rtDW.dx[0] = tmp_1;
  rtDW.dx[3] = ((B_1[i] - A_0[i + 6] * tau_idx_2) - A_0[i + 3] * s) / A_0[i];
  rtDW.dx[1] = tau_idx_0;
  rtDW.dx[4] = s;
  rtDW.dx[2] = tmp_2;
  rtDW.dx[5] = tau_idx_2;

  // SignalConversion generated from: '<S2>/Integrator'
  rtDW.TmpSignalConversionAtIntegrator[0] = rtDW.x_dach_d[1];
  rtDW.TmpSignalConversionAtIntegrator[1] = rtDW.x_dach_j[1];
  rtDW.TmpSignalConversionAtIntegrator[2] = rtDW.x_dach_a[1];

  // Sum: '<S152>/SumD' incorporates:
  //   Gain: '<S150>/Derivative Gain'
  //   UnaryMinus: '<S151>/Unary Minus'

  rtDW.SumD = rtP.kd_yaw * -rtDW.x_dach_a[1] - rtb_Sum_l;

  // Gain: '<S154>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_yaw * rtb_UnaryMinus_a;

  // Sum: '<S100>/SumD' incorporates:
  //   Gain: '<S98>/Derivative Gain'
  //   UnaryMinus: '<S99>/Unary Minus'

  rtDW.SumD_k = rtP.kd_pitch * -rtDW.x_dach_j[1] - rtb_FilterCoefficient_o;

  // Gain: '<S102>/Integral Gain'
  rtDW.IntegralGain_d = rtP.ki_pitch * rtb_UnaryMinus;

  // Sum: '<S48>/SumD' incorporates:
  //   Gain: '<S46>/Derivative Gain'
  //   UnaryMinus: '<S47>/Unary Minus'

  rtDW.SumD_p = rtP.kd_roll * -rtDW.x_dach_d[1] - rtb_FilterCoefficient_gy;

  // Gain: '<S50>/Integral Gain'
  rtDW.IntegralGain_i = rtP.ki_roll * rtb_FilterCoefficient;
  if (tmp) {
    // UnitDelay: '<S177>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_b[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_b[1];

    // MATLAB Function: '<S177>/KF_Elevation' incorporates:
    //   Constant: '<S177>/Constant'
    //   Constant: '<S177>/Constant1'
    //   Constant: '<S177>/Constant2'
    //   Constant: '<S177>/Constant5'
    //   Constant: '<S177>/Cov Messrauschen'
    //   Constant: '<S177>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S177>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_p,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_h3,
                 rtP.CovMessrauschen_Value_j, rtU.y[0], rtP.Constant5_Value_d,
                 rtDW.UnitDelay_DSTATE_o, rtDW.x_dach_g, rtDW.P_n);

    // UnitDelay: '<S178>/Unit Delay1'
    rtDW.x_dach_n[0] = rtDW.UnitDelay1_DSTATE_b4[0];
    rtDW.x_dach_n[1] = rtDW.UnitDelay1_DSTATE_b4[1];

    // MATLAB Function: '<S178>/KF_Elevation' incorporates:
    //   Constant: '<S178>/Constant'
    //   Constant: '<S178>/Constant1'
    //   Constant: '<S178>/Constant2'
    //   Constant: '<S178>/Constant5'
    //   Constant: '<S178>/Cov Messrauschen'
    //   Constant: '<S178>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S178>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_i, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_ph, rtP.CovProzessrauschen_Value_d,
                 rtP.CovMessrauschen_Value_i, rtU.y[1], rtP.Constant5_Value_b,
                 rtDW.UnitDelay_DSTATE_g, rtDW.x_dach_n, rtDW.P_d);

    // UnitDelay: '<S180>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_n[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_n[1];

    // MATLAB Function: '<S180>/KF_Elevation' incorporates:
    //   Constant: '<S180>/Constant'
    //   Constant: '<S180>/Constant1'
    //   Constant: '<S180>/Constant2'
    //   Constant: '<S180>/Constant5'
    //   Constant: '<S180>/Cov Messrauschen'
    //   Constant: '<S180>/Cov Prozessrauschen'
    //   Inport: '<Root>/y'
    //   UnitDelay: '<S180>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_d,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_i,
                 rtP.CovMessrauschen_Value_o, rtU.y[2], rtP.Constant5_Value_bx,
                 rtDW.UnitDelay_DSTATE_f, rtDW.x_dach, rtDW.P_h);
  }

  // Sum: '<S179>/Sum' incorporates:
  //   Inport: '<Root>/w'

  rtb_Sum_l = rtU.w[1] - rtDW.x_dach_g[0];

  // Gain: '<S224>/Filter Coefficient' incorporates:
  //   Integrator: '<S216>/Filter'

  rtb_FilterCoefficient_o = rtP.N * rtX.Filter_CSTATE_n;

  // Sum: '<S179>/Sum1' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus = rtU.w[2] - rtDW.x_dach_n[0];

  // Gain: '<S276>/Filter Coefficient' incorporates:
  //   Integrator: '<S268>/Filter'

  rtb_FilterCoefficient_gy = rtP.N * rtX.Filter_CSTATE_i;

  // Sum: '<S179>/Sum2' incorporates:
  //   Inport: '<Root>/w'

  rtb_UnaryMinus_a = rtU.w[3] - rtDW.x_dach[0];

  // Gain: '<S328>/Filter Coefficient' incorporates:
  //   Integrator: '<S320>/Filter'

  rtb_FilterCoefficient = rtP.N * rtX.Filter_CSTATE_c;

  // MATLAB Function: '<S176>/MATLAB Function' incorporates:
  //   Gain: '<S226>/Proportional Gain'
  //   Gain: '<S278>/Proportional Gain'
  //   Gain: '<S330>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S221>/Integrator'
  //   Integrator: '<S273>/Integrator'
  //   Integrator: '<S325>/Integrator'
  //   MATLAB Function: '<S8>/MATLAB Function'
  //   SignalConversion generated from: '<S181>/ SFunction '
  //   Sum: '<S230>/Sum'
  //   Sum: '<S282>/Sum'
  //   Sum: '<S334>/Sum'

  B_0[0] = rtU.w[0];
  B_0[1] = (rtP.kp_roll * rtb_Sum_l + rtX.Integrator_CSTATE_l) +
    rtb_FilterCoefficient_o;
  B_0[2] = (rtP.kp_pitch * rtb_UnaryMinus + rtX.Integrator_CSTATE_ja) +
    rtb_FilterCoefficient_gy;
  B_0[3] = (rtP.kp_yaw * rtb_UnaryMinus_a + rtX.Integrator_CSTATE_i) +
    rtb_FilterCoefficient;
  std::memcpy(&A[0], &rtP.B_eff[0], sizeof(real_T) << 4U);
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
    if (B_0[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_0[i] / rtP.a >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = B_0[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S176>/Saturation' incorporates:
  //   MATLAB Function: '<S176>/MATLAB Function'

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

  // End of Saturate: '<S176>/Saturation'

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
      // Update for UnitDelay: '<S9>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_d[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_d[1];

      // Update for UnitDelay: '<S9>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_dr[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_dr[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_dr[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_dr[3];

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

      // Update for UnitDelay: '<S177>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_b[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S177>/Unit Delay'
      rtDW.UnitDelay_DSTATE_o[0] = rtDW.P_n[0];
      rtDW.UnitDelay_DSTATE_o[1] = rtDW.P_n[1];
      rtDW.UnitDelay_DSTATE_o[2] = rtDW.P_n[2];
      rtDW.UnitDelay_DSTATE_o[3] = rtDW.P_n[3];

      // Update for UnitDelay: '<S178>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_b4[0] = rtDW.x_dach_n[0];
      rtDW.UnitDelay1_DSTATE_b4[1] = rtDW.x_dach_n[1];

      // Update for UnitDelay: '<S178>/Unit Delay'
      rtDW.UnitDelay_DSTATE_g[0] = rtDW.P_d[0];
      rtDW.UnitDelay_DSTATE_g[1] = rtDW.P_d[1];
      rtDW.UnitDelay_DSTATE_g[2] = rtDW.P_d[2];
      rtDW.UnitDelay_DSTATE_g[3] = rtDW.P_d[3];

      // Update for UnitDelay: '<S180>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_n[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_n[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S180>/Unit Delay'
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
void Controller3dof::controller_3dof_container_derivatives()
{
  Controller3dof::XDot *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<S4>/Integrator'
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE[i] = rtDW.dx[i];
  }

  // End of Derivatives for Integrator: '<S4>/Integrator'

  // Derivatives for Integrator: '<S53>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S48>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.SumD_p;

  // Derivatives for Integrator: '<S105>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S100>/Filter'
  _rtXdot->Filter_CSTATE_e = rtDW.SumD_k;

  // Derivatives for Integrator: '<S157>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S152>/Filter'
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
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S320>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.SumD_kz;

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[0] = rtDW.TmpSignalConversionAtIntegrator[0];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[0] = rtDW.TmpSignalConversionAtIntegrat_p[0];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[1] = rtDW.TmpSignalConversionAtIntegrator[1];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[1] = rtDW.TmpSignalConversionAtIntegrat_p[1];

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE_b[2] = rtDW.TmpSignalConversionAtIntegrator[2];

  // Derivatives for Integrator: '<S3>/Integrator'
  _rtXdot->Integrator_CSTATE_f[2] = rtDW.TmpSignalConversionAtIntegrat_p[2];

  // Derivatives for Integrator: '<S9>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_d[1];

  // Derivatives for Integrator: '<S10>/Integrator1'
  _rtXdot->Integrator1_CSTATE_i = rtDW.x_dach_j[1];

  // Derivatives for Integrator: '<S12>/Integrator1'
  _rtXdot->Integrator1_CSTATE_k = rtDW.x_dach_a[1];

  // Derivatives for Integrator: '<S177>/Integrator1'
  _rtXdot->Integrator1_CSTATE_a = rtDW.x_dach_g[1];

  // Derivatives for Integrator: '<S178>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_n[1];

  // Derivatives for Integrator: '<S180>/Integrator1'
  _rtXdot->Integrator1_CSTATE_km = rtDW.x_dach[1];
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

    // InitializeConditions for Integrator: '<S4>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC[i];
    }

    // End of InitializeConditions for Integrator: '<S4>/Integrator'

    // InitializeConditions for UnitDelay: '<S9>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S9>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for Integrator: '<S53>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S48>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_f[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_f[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S10>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_d[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_d[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_d[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_d[3];

    // InitializeConditions for Integrator: '<S105>/Integrator'
    rtX.Integrator_CSTATE_c = rtP.PIDController1_InitialConditi_p;

    // InitializeConditions for Integrator: '<S100>/Filter'
    rtX.Filter_CSTATE_e = rtP.PIDController1_InitialCondition;

    // InitializeConditions for UnitDelay: '<S12>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S12>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_e[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_e[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_e[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_e[3];

    // InitializeConditions for Integrator: '<S157>/Integrator'
    rtX.Integrator_CSTATE_o = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S152>/Filter'
    rtX.Filter_CSTATE_j = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S2>/Integrator'
    rtX.Integrator_CSTATE_b[0] = rtP.Integrator_IC_c;
    rtX.Integrator_CSTATE_b[1] = rtP.Integrator_IC_c;
    rtX.Integrator_CSTATE_b[2] = rtP.Integrator_IC_c;

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b[0] = rtP.UnitDelay1_InitialCondition_b[0];
    rtDW.UnitDelay1_DSTATE_b[1] = rtP.UnitDelay1_InitialCondition_b[1];

    // InitializeConditions for UnitDelay: '<S177>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_o[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_o[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_o[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_o[3];

    // InitializeConditions for UnitDelay: '<S178>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_b4[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_b4[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S178>/Unit Delay'
    rtDW.UnitDelay_DSTATE_g[0] = rtP.UnitDelay_InitialCondition_p[0];
    rtDW.UnitDelay_DSTATE_g[1] = rtP.UnitDelay_InitialCondition_p[1];
    rtDW.UnitDelay_DSTATE_g[2] = rtP.UnitDelay_InitialCondition_p[2];
    rtDW.UnitDelay_DSTATE_g[3] = rtP.UnitDelay_InitialCondition_p[3];

    // InitializeConditions for UnitDelay: '<S180>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_n[0] = rtP.UnitDelay1_InitialCondition_mp[0];
    rtDW.UnitDelay1_DSTATE_n[1] = rtP.UnitDelay1_InitialCondition_mp[1];

    // InitializeConditions for UnitDelay: '<S180>/Unit Delay'
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
    rtX.Integrator_CSTATE_i = rtP.PIDController2_InitialConditi_m;

    // InitializeConditions for Integrator: '<S320>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_j;

    // InitializeConditions for Integrator: '<S3>/Integrator'
    rtX.Integrator_CSTATE_f[0] = rtP.Integrator_IC_f;
    rtX.Integrator_CSTATE_f[1] = rtP.Integrator_IC_f;
    rtX.Integrator_CSTATE_f[2] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S9>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S10>/Integrator1'
    rtX.Integrator1_CSTATE_i = rtP.Integrator1_IC_e;

    // InitializeConditions for Integrator: '<S12>/Integrator1'
    rtX.Integrator1_CSTATE_k = rtP.Integrator1_IC_e4;

    // InitializeConditions for Integrator: '<S177>/Integrator1'
    rtX.Integrator1_CSTATE_a = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S178>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_l;

    // InitializeConditions for Integrator: '<S180>/Integrator1'
    rtX.Integrator1_CSTATE_km = rtP.Integrator1_IC_o;
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
