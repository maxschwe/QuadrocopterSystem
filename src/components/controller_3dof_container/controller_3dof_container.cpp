//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.cpp
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.490
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Mar 13 18:06:58 2026
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
  int_T nXc { 34 };

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
//    '<S171>/KF_Elevation'
//    '<S172>/KF_Elevation'
//    '<S173>/KF_Elevation'
//    '<S340>/KF_Elevation'
//    '<S341>/KF_Elevation'
//    '<S342>/KF_Elevation'
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
  real_T B_1[4];
  real_T c_data[4];
  real_T rtb_B_Eff[4];
  real_T rtb_thrust[4];
  real_T rtb_u_e[4];
  real_T B_0[3];
  real_T b_idx_0;
  real_T b_idx_1;
  real_T b_idx_2;
  real_T rtb_Filter;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T rtb_Sum_idx_0;
  real_T rtb_Sum_idx_2;
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
  for (i = 0; i < 6; i++) {
    if (tmp) {
      // Outport: '<Root>/values' incorporates:
      //   Constant: '<S3>/Constant'

      rtY.values[i] = rtP.Constant_Value[i];
    }

    // Outport: '<Root>/x_pred' incorporates:
    //   Integrator: '<S4>/Integrator'

    rtY.x_pred[i] = rtX.Integrator_CSTATE[i];
  }

  // SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
  //   Inport: '<Root>/w'
  //   MATLAB Function: '<S8>/MATLAB Function'

  rtb_B_Eff[0] = rtU.w[0];

  // Sum: '<S9>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Filter = rtU.w[1] - rtX.Integrator_CSTATE[0];

  // Gain: '<S52>/Filter Coefficient' incorporates:
  //   Gain: '<S42>/Derivative Gain'
  //   Integrator: '<S44>/Filter'
  //   Sum: '<S44>/SumD'

  rtDW.FilterCoefficient = (rtP.kd_roll * rtb_Filter - rtX.Filter_CSTATE) *
    rtP.N;

  // Sum: '<S9>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Sum2 = rtU.w[2] - rtX.Integrator_CSTATE[1];

  // Gain: '<S104>/Filter Coefficient' incorporates:
  //   Gain: '<S94>/Derivative Gain'
  //   Integrator: '<S96>/Filter'
  //   Sum: '<S96>/SumD'

  rtDW.FilterCoefficient_k = (rtP.kd_pitch * rtb_Sum2 - rtX.Filter_CSTATE_i) *
    rtP.N;

  // Sum: '<S9>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S4>/Integrator'

  rtb_Sum1 = rtU.w[3] - rtX.Integrator_CSTATE[2];

  // Gain: '<S156>/Filter Coefficient' incorporates:
  //   Gain: '<S146>/Derivative Gain'
  //   Integrator: '<S148>/Filter'
  //   Sum: '<S148>/SumD'

  rtDW.FilterCoefficient_j = (rtP.kd_yaw * rtb_Sum1 - rtX.Filter_CSTATE_n) *
    rtP.N;

  // SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
  //   Gain: '<S106>/Proportional Gain'
  //   Gain: '<S158>/Proportional Gain'
  //   Gain: '<S54>/Proportional Gain'
  //   Integrator: '<S101>/Integrator'
  //   Integrator: '<S153>/Integrator'
  //   Integrator: '<S49>/Integrator'
  //   MATLAB Function: '<S8>/MATLAB Function'
  //   Sum: '<S110>/Sum'
  //   Sum: '<S162>/Sum'
  //   Sum: '<S58>/Sum'

  rtb_B_Eff[1] = (rtP.kp_roll * rtb_Filter + rtX.Integrator_CSTATE_j) +
    rtDW.FilterCoefficient;
  rtb_B_Eff[2] = (rtP.kp_pitch * rtb_Sum2 + rtX.Integrator_CSTATE_c) +
    rtDW.FilterCoefficient_k;
  rtb_B_Eff[3] = (rtP.kp_yaw * rtb_Sum1 + rtX.Integrator_CSTATE_o) +
    rtDW.FilterCoefficient_j;

  // MATLAB Function: '<S8>/MATLAB Function'
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
      smax = rtb_B_Eff[i];
      rtb_B_Eff[i] = rtb_B_Eff[ipiv_0 - 1];
      rtb_B_Eff[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (rtb_B_Eff[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        rtb_B_Eff[jA - 1] -= A[(jA + jj) - 1] * rtb_B_Eff[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = rtb_B_Eff[i];
    if (smax != 0.0) {
      rtb_B_Eff[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        rtb_B_Eff[jA] -= A[jA + jj] * rtb_B_Eff[i];
      }
    }
  }

  rtb_u_e[0] = 0.0;
  rtb_u_e[1] = 0.0;
  rtb_u_e[2] = 0.0;
  rtb_u_e[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_B_Eff[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (rtb_B_Eff[i] / rtP.a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = rtb_B_Eff[tmp_data[jj]] / rtP.a;
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

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  rtb_Sum_idx_0 = 0.0;
  s = 0.0;
  rtb_Sum_idx_2 = 0.0;
  for (jj = 0; jj < 4; jj++) {
    smax = rtP.a * rtb_thrust[jj];
    i = jj << 2;
    rtb_Sum_idx_0 += rtP.B_eff[i + 1] * smax;
    s += rtP.B_eff[i + 2] * smax;
    rtb_Sum_idx_2 += rtP.B_eff[i + 3] * smax;
  }

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'

  if (rtP.Constant_Value_c) {
    rtb_Sum_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[0]) * std::
      cos(rtX.Integrator_CSTATE[1]) * rtP.h;
    s += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE[1]) * rtP.h;
  }

  b_idx_0 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    smax = rtX.Integrator_CSTATE[jj + 3];
    b_idx_0 += rtP.J[3 * jj] * smax;
    b_idx_1 += rtP.J[3 * jj + 1] * smax;
    b_idx_2 += rtP.J[3 * jj + 2] * smax;
  }

  std::memcpy(&A_0[0], &rtP.J[0], 9U * sizeof(real_T));
  B_0[0] = rtb_Sum_idx_0 - (b_idx_2 * rtX.Integrator_CSTATE[4] - b_idx_1 *
    rtX.Integrator_CSTATE[5]);
  B_0[1] = s - (b_idx_0 * rtX.Integrator_CSTATE[5] - b_idx_2 *
                rtX.Integrator_CSTATE[3]);
  B_0[2] = rtb_Sum_idx_2 - (b_idx_1 * rtX.Integrator_CSTATE[3] - b_idx_0 *
    rtX.Integrator_CSTATE[4]);
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
  s = B_0[jj] - B_0[i] * A_0[jj];
  rtb_Sum_idx_2 = ((B_0[jA] - B_0[i] * A_0[jA]) - A_0[jA + 3] * s) / A_0[jA + 6];
  s = (s - A_0[jj + 6] * rtb_Sum_idx_2) / A_0[jj + 3];
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
  rtb_Sum_idx_0 = 0.0;
  b_idx_0 = 0.0;
  b_idx_1 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    smax = rtX.Integrator_CSTATE[jj + 3];
    rtb_Sum_idx_0 += tmp_0[3 * jj] * smax;
    b_idx_0 += tmp_0[3 * jj + 1] * smax;
    b_idx_1 += tmp_0[3 * jj + 2] * smax;
  }

  rtDW.dx[0] = rtb_Sum_idx_0;
  rtDW.dx[3] = ((B_0[i] - A_0[i + 6] * rtb_Sum_idx_2) - A_0[i + 3] * s) / A_0[i];
  rtDW.dx[1] = b_idx_0;
  rtDW.dx[4] = s;
  rtDW.dx[2] = b_idx_1;
  rtDW.dx[5] = rtb_Sum_idx_2;

  // End of MATLAB Function: '<S4>/MATLAB Function2'

  // Gain: '<S150>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_yaw * rtb_Sum1;

  // Gain: '<S98>/Integral Gain'
  rtDW.IntegralGain_d = rtP.ki_pitch * rtb_Sum2;

  // Gain: '<S46>/Integral Gain'
  rtDW.IntegralGain_i = rtP.ki_roll * rtb_Filter;

  // SignalConversion generated from: '<S3>/Vector Concatenate1' incorporates:
  //   Inport: '<Root>/w'
  //   MATLAB Function: '<S177>/MATLAB Function'

  B_1[0] = rtU.w[0];

  // Sum: '<S178>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Filter = rtU.w[1] - rtU.y[0];

  // Gain: '<S221>/Filter Coefficient' incorporates:
  //   Gain: '<S211>/Derivative Gain'
  //   Integrator: '<S213>/Filter'
  //   Sum: '<S213>/SumD'

  rtDW.FilterCoefficient_b = (rtP.kd_roll * rtb_Filter - rtX.Filter_CSTATE_g) *
    rtP.N;

  // Sum: '<S178>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum1 = rtU.w[2] - rtU.y[1];

  // Gain: '<S273>/Filter Coefficient' incorporates:
  //   Gain: '<S263>/Derivative Gain'
  //   Integrator: '<S265>/Filter'
  //   Sum: '<S265>/SumD'

  rtDW.FilterCoefficient_o = (rtP.kd_pitch * rtb_Sum1 - rtX.Filter_CSTATE_h) *
    rtP.N;

  // Sum: '<S178>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtU.w[3] - rtU.y[2];

  // Gain: '<S325>/Filter Coefficient' incorporates:
  //   Gain: '<S315>/Derivative Gain'
  //   Integrator: '<S317>/Filter'
  //   Sum: '<S317>/SumD'

  rtDW.FilterCoefficient_e = (rtP.kd_yaw * rtb_Sum2 - rtX.Filter_CSTATE_c) *
    rtP.N;

  // SignalConversion generated from: '<S3>/Vector Concatenate1' incorporates:
  //   Gain: '<S223>/Proportional Gain'
  //   Gain: '<S275>/Proportional Gain'
  //   Gain: '<S327>/Proportional Gain'
  //   Integrator: '<S218>/Integrator'
  //   Integrator: '<S270>/Integrator'
  //   Integrator: '<S322>/Integrator'
  //   MATLAB Function: '<S177>/MATLAB Function'
  //   Sum: '<S227>/Sum'
  //   Sum: '<S279>/Sum'
  //   Sum: '<S331>/Sum'

  B_1[1] = (rtP.kp_roll * rtb_Filter + rtX.Integrator_CSTATE_l) +
    rtDW.FilterCoefficient_b;
  B_1[2] = (rtP.kp_pitch * rtb_Sum1 + rtX.Integrator_CSTATE_ja) +
    rtDW.FilterCoefficient_o;
  B_1[3] = (rtP.kp_yaw * rtb_Sum2 + rtX.Integrator_CSTATE_i) +
    rtDW.FilterCoefficient_e;

  // MATLAB Function: '<S177>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S8>/MATLAB Function'

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
      smax = B_1[i];
      B_1[i] = B_1[ipiv_0 - 1];
      B_1[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (B_1[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        B_1[jA - 1] -= A[(jA + jj) - 1] * B_1[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = B_1[i];
    if (smax != 0.0) {
      B_1[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        B_1[jA] -= A[jA + jj] * B_1[i];
      }
    }
  }

  rtb_thrust[0] = 0.0;
  rtb_thrust[1] = 0.0;
  rtb_thrust[2] = 0.0;
  rtb_thrust[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_1[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_1[i] / rtP.a >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = B_1[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S177>/Saturation' incorporates:
  //   MATLAB Function: '<S177>/MATLAB Function'

  if (rtb_thrust[0] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[0] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtb_thrust[0];
  }

  if (rtb_thrust[1] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[1] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtb_thrust[1];
  }

  if (rtb_thrust[2] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[2] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtb_thrust[2];
  }

  if (rtb_thrust[3] > rtP.Saturation_UpperSat_l) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_UpperSat_l;
  } else if (rtb_thrust[3] < rtP.Saturation_LowerSat_d) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_LowerSat_d;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtb_thrust[3];
  }

  // End of Saturate: '<S177>/Saturation'

  // Gain: '<S319>/Integral Gain'
  rtDW.IntegralGain_p = rtP.ki_yaw * rtb_Sum2;

  // Gain: '<S267>/Integral Gain'
  rtDW.IntegralGain_m = rtP.ki_pitch * rtb_Sum1;

  // Gain: '<S215>/Integral Gain'
  rtDW.IntegralGain_l = rtP.ki_roll * rtb_Filter;
  if (tmp) {
    // UnitDelay: '<S171>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE[1];

    // MATLAB Function: '<S171>/KF_Elevation' incorporates:
    //   Constant: '<S171>/Constant'
    //   Constant: '<S171>/Constant1'
    //   Constant: '<S171>/Constant2'
    //   Constant: '<S171>/Constant5'
    //   Constant: '<S171>/Cov Messrauschen'
    //   Constant: '<S171>/Cov Prozessrauschen'
    //   UnitDelay: '<S171>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_a, rtP.Constant1_Value, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, 0.0,
                 rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_e,
                 rtDW.P_j);

    // UnitDelay: '<S172>/Unit Delay1'
    rtDW.x_dach_g[0] = rtDW.UnitDelay1_DSTATE_p[0];
    rtDW.x_dach_g[1] = rtDW.UnitDelay1_DSTATE_p[1];

    // MATLAB Function: '<S172>/KF_Elevation' incorporates:
    //   Constant: '<S172>/Constant'
    //   Constant: '<S172>/Constant1'
    //   Constant: '<S172>/Constant2'
    //   Constant: '<S172>/Constant5'
    //   Constant: '<S172>/Cov Messrauschen'
    //   Constant: '<S172>/Cov Prozessrauschen'
    //   UnitDelay: '<S172>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p, rtP.Constant1_Value_h,
                 rtP.Constant2_Value_a, rtP.CovProzessrauschen_Value_l,
                 rtP.CovMessrauschen_Value_o, 0.0, rtP.Constant5_Value_f,
                 rtDW.UnitDelay_DSTATE_l, rtDW.x_dach_g, rtDW.P_k);

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
    //   UnitDelay: '<S173>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_d, rtP.Constant1_Value_c,
                 rtP.Constant2_Value_b, rtP.CovProzessrauschen_Value_a,
                 rtP.CovMessrauschen_Value_g, 0.0, rtP.Constant5_Value_d,
                 rtDW.UnitDelay_DSTATE_i, rtDW.x_dach_k, rtDW.P_o);
  }

  // Sum: '<S10>/Sum'
  rtDW.Sum[0] = 0.0 - rtDW.x_dach_e[0];
  rtDW.Sum[1] = 0.0 - rtDW.x_dach_g[0];
  rtDW.Sum[2] = 0.0 - rtDW.x_dach_k[0];
  if (tmp) {
    // UnitDelay: '<S340>/Unit Delay1'
    rtDW.x_dach_o[0] = rtDW.UnitDelay1_DSTATE_e[0];
    rtDW.x_dach_o[1] = rtDW.UnitDelay1_DSTATE_e[1];

    // MATLAB Function: '<S340>/KF_Elevation' incorporates:
    //   Constant: '<S340>/Constant'
    //   Constant: '<S340>/Constant1'
    //   Constant: '<S340>/Constant2'
    //   Constant: '<S340>/Constant5'
    //   Constant: '<S340>/Cov Messrauschen'
    //   Constant: '<S340>/Cov Prozessrauschen'
    //   UnitDelay: '<S340>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_p1, rtP.Constant1_Value_h4,
                 rtP.Constant2_Value_k, rtP.CovProzessrauschen_Value_p,
                 rtP.CovMessrauschen_Value_m, 0.0, rtP.Constant5_Value_e,
                 rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_o, rtDW.P_g);

    // UnitDelay: '<S341>/Unit Delay1'
    rtDW.x_dach_a[0] = rtDW.UnitDelay1_DSTATE_j[0];
    rtDW.x_dach_a[1] = rtDW.UnitDelay1_DSTATE_j[1];

    // MATLAB Function: '<S341>/KF_Elevation' incorporates:
    //   Constant: '<S341>/Constant'
    //   Constant: '<S341>/Constant1'
    //   Constant: '<S341>/Constant2'
    //   Constant: '<S341>/Constant5'
    //   Constant: '<S341>/Cov Messrauschen'
    //   Constant: '<S341>/Cov Prozessrauschen'
    //   UnitDelay: '<S341>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_m, rtP.Constant1_Value_i,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_p, 0.0, rtP.Constant5_Value_k,
                 rtDW.UnitDelay_DSTATE_db, rtDW.x_dach_a, rtDW.P_l);

    // UnitDelay: '<S342>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S342>/KF_Elevation' incorporates:
    //   Constant: '<S342>/Constant'
    //   Constant: '<S342>/Constant1'
    //   Constant: '<S342>/Constant2'
    //   Constant: '<S342>/Constant5'
    //   Constant: '<S342>/Cov Messrauschen'
    //   Constant: '<S342>/Cov Prozessrauschen'
    //   UnitDelay: '<S342>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_pv, rtP.Constant1_Value_b,
                 rtP.Constant2_Value_p, rtP.CovProzessrauschen_Value_g,
                 rtP.CovMessrauschen_Value_i, 0.0, rtP.Constant5_Value_k1,
                 rtDW.UnitDelay_DSTATE_k, rtDW.x_dach, rtDW.P_p);
  }

  // Sum: '<S179>/Sum'
  rtDW.Sum_d[0] = 0.0 - rtDW.x_dach_o[0];
  rtDW.Sum_d[1] = 0.0 - rtDW.x_dach_a[0];
  rtDW.Sum_d[2] = 0.0 - rtDW.x_dach[0];
  if ((&rtM)->isMajorTimeStep()) {
    if ((&rtM)->isMajorTimeStep()) {
      // Update for UnitDelay: '<S171>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S171>/Unit Delay'
      rtDW.UnitDelay_DSTATE[0] = rtDW.P_j[0];
      rtDW.UnitDelay_DSTATE[1] = rtDW.P_j[1];
      rtDW.UnitDelay_DSTATE[2] = rtDW.P_j[2];
      rtDW.UnitDelay_DSTATE[3] = rtDW.P_j[3];

      // Update for UnitDelay: '<S172>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_p[0] = rtDW.x_dach_g[0];
      rtDW.UnitDelay1_DSTATE_p[1] = rtDW.x_dach_g[1];

      // Update for UnitDelay: '<S172>/Unit Delay'
      rtDW.UnitDelay_DSTATE_l[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_l[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_l[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_l[3] = rtDW.P_k[3];

      // Update for UnitDelay: '<S173>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_a[0] = rtDW.x_dach_k[0];
      rtDW.UnitDelay1_DSTATE_a[1] = rtDW.x_dach_k[1];

      // Update for UnitDelay: '<S173>/Unit Delay'
      rtDW.UnitDelay_DSTATE_i[0] = rtDW.P_o[0];
      rtDW.UnitDelay_DSTATE_i[1] = rtDW.P_o[1];
      rtDW.UnitDelay_DSTATE_i[2] = rtDW.P_o[2];
      rtDW.UnitDelay_DSTATE_i[3] = rtDW.P_o[3];

      // Update for UnitDelay: '<S340>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_e[0] = rtDW.x_dach_o[0];
      rtDW.UnitDelay1_DSTATE_e[1] = rtDW.x_dach_o[1];

      // Update for UnitDelay: '<S340>/Unit Delay'
      rtDW.UnitDelay_DSTATE_d[0] = rtDW.P_g[0];
      rtDW.UnitDelay_DSTATE_d[1] = rtDW.P_g[1];
      rtDW.UnitDelay_DSTATE_d[2] = rtDW.P_g[2];
      rtDW.UnitDelay_DSTATE_d[3] = rtDW.P_g[3];

      // Update for UnitDelay: '<S341>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_j[0] = rtDW.x_dach_a[0];
      rtDW.UnitDelay1_DSTATE_j[1] = rtDW.x_dach_a[1];

      // Update for UnitDelay: '<S341>/Unit Delay'
      rtDW.UnitDelay_DSTATE_db[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_db[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_db[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_db[3] = rtDW.P_l[3];

      // Update for UnitDelay: '<S342>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S342>/Unit Delay'
      rtDW.UnitDelay_DSTATE_k[0] = rtDW.P_p[0];
      rtDW.UnitDelay_DSTATE_k[1] = rtDW.P_p[1];
      rtDW.UnitDelay_DSTATE_k[2] = rtDW.P_p[2];
      rtDW.UnitDelay_DSTATE_k[3] = rtDW.P_p[3];
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

  // Derivatives for Integrator: '<S49>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S44>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S101>/Integrator'
  _rtXdot->Integrator_CSTATE_c = rtDW.IntegralGain_d;

  // Derivatives for Integrator: '<S96>/Filter'
  _rtXdot->Filter_CSTATE_i = rtDW.FilterCoefficient_k;

  // Derivatives for Integrator: '<S153>/Integrator'
  _rtXdot->Integrator_CSTATE_o = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S148>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.FilterCoefficient_j;

  // Derivatives for Integrator: '<S218>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain_l;

  // Derivatives for Integrator: '<S213>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_b;

  // Derivatives for Integrator: '<S270>/Integrator'
  _rtXdot->Integrator_CSTATE_ja = rtDW.IntegralGain_m;

  // Derivatives for Integrator: '<S265>/Filter'
  _rtXdot->Filter_CSTATE_h = rtDW.FilterCoefficient_o;

  // Derivatives for Integrator: '<S322>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S317>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_p[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S179>/Integrator'
  _rtXdot->Integrator_CSTATE_if[0] = rtDW.Sum_d[0];

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_p[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S179>/Integrator'
  _rtXdot->Integrator_CSTATE_if[1] = rtDW.Sum_d[1];

  // Derivatives for Integrator: '<S10>/Integrator'
  _rtXdot->Integrator_CSTATE_p[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S179>/Integrator'
  _rtXdot->Integrator_CSTATE_if[2] = rtDW.Sum_d[2];

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE = rtP.TransferFcn_A * rtX.TransferFcn_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn1'
  _rtXdot->TransferFcn1_CSTATE = rtP.TransferFcn1_A * rtX.TransferFcn1_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn2'
  _rtXdot->TransferFcn2_CSTATE = rtP.TransferFcn2_A * rtX.TransferFcn2_CSTATE;

  // Derivatives for TransferFcn: '<S5>/Transfer Fcn3'
  _rtXdot->TransferFcn3_CSTATE = rtP.TransferFcn3_A * rtX.TransferFcn3_CSTATE;

  // Derivatives for Integrator: '<S171>/Integrator1'
  _rtXdot->Integrator1_CSTATE = rtDW.x_dach_e[1];

  // Derivatives for Integrator: '<S172>/Integrator1'
  _rtXdot->Integrator1_CSTATE_k = rtDW.x_dach_g[1];

  // Derivatives for Integrator: '<S173>/Integrator1'
  _rtXdot->Integrator1_CSTATE_l = rtDW.x_dach_k[1];

  // Derivatives for Integrator: '<S340>/Integrator1'
  _rtXdot->Integrator1_CSTATE_b = rtDW.x_dach_o[1];

  // Derivatives for Integrator: '<S341>/Integrator1'
  _rtXdot->Integrator1_CSTATE_h = rtDW.x_dach_a[1];

  // Derivatives for Integrator: '<S342>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach[1];
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

    // InitializeConditions for Integrator: '<S49>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S44>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S101>/Integrator'
    rtX.Integrator_CSTATE_c = rtP.PIDController1_InitialConditi_p;

    // InitializeConditions for Integrator: '<S96>/Filter'
    rtX.Filter_CSTATE_i = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S153>/Integrator'
    rtX.Integrator_CSTATE_o = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S148>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S218>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S213>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController_InitialConditio_c;

    // InitializeConditions for Integrator: '<S270>/Integrator'
    rtX.Integrator_CSTATE_ja = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S265>/Filter'
    rtX.Filter_CSTATE_h = rtP.PIDController1_InitialConditi_k;

    // InitializeConditions for Integrator: '<S322>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController2_InitialConditi_m;

    // InitializeConditions for Integrator: '<S317>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_j;

    // InitializeConditions for UnitDelay: '<S171>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S171>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S172>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_p[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_p[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S172>/Unit Delay'
    rtDW.UnitDelay_DSTATE_l[0] = rtP.UnitDelay_InitialCondition_e[0];
    rtDW.UnitDelay_DSTATE_l[1] = rtP.UnitDelay_InitialCondition_e[1];
    rtDW.UnitDelay_DSTATE_l[2] = rtP.UnitDelay_InitialCondition_e[2];
    rtDW.UnitDelay_DSTATE_l[3] = rtP.UnitDelay_InitialCondition_e[3];

    // InitializeConditions for UnitDelay: '<S173>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_a[0] = rtP.UnitDelay1_InitialCondition_i[0];
    rtDW.UnitDelay1_DSTATE_a[1] = rtP.UnitDelay1_InitialCondition_i[1];

    // InitializeConditions for UnitDelay: '<S173>/Unit Delay'
    rtDW.UnitDelay_DSTATE_i[0] = rtP.UnitDelay_InitialCondition_ew[0];
    rtDW.UnitDelay_DSTATE_i[1] = rtP.UnitDelay_InitialCondition_ew[1];
    rtDW.UnitDelay_DSTATE_i[2] = rtP.UnitDelay_InitialCondition_ew[2];
    rtDW.UnitDelay_DSTATE_i[3] = rtP.UnitDelay_InitialCondition_ew[3];

    // InitializeConditions for UnitDelay: '<S340>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_e[0] = rtP.UnitDelay1_InitialCondition_h[0];
    rtDW.UnitDelay1_DSTATE_e[1] = rtP.UnitDelay1_InitialCondition_h[1];

    // InitializeConditions for UnitDelay: '<S340>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_j[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_j[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_j[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_j[3];

    // InitializeConditions for UnitDelay: '<S341>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_j[0] = rtP.UnitDelay1_InitialCondition_m[0];
    rtDW.UnitDelay1_DSTATE_j[1] = rtP.UnitDelay1_InitialCondition_m[1];

    // InitializeConditions for UnitDelay: '<S341>/Unit Delay'
    rtDW.UnitDelay_DSTATE_db[0] = rtP.UnitDelay_InitialCondition_n[0];
    rtDW.UnitDelay_DSTATE_db[1] = rtP.UnitDelay_InitialCondition_n[1];
    rtDW.UnitDelay_DSTATE_db[2] = rtP.UnitDelay_InitialCondition_n[2];
    rtDW.UnitDelay_DSTATE_db[3] = rtP.UnitDelay_InitialCondition_n[3];

    // InitializeConditions for UnitDelay: '<S342>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_l[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_l[1];

    // InitializeConditions for UnitDelay: '<S342>/Unit Delay'
    rtDW.UnitDelay_DSTATE_k[0] = rtP.UnitDelay_InitialCondition_i[0];
    rtDW.UnitDelay_DSTATE_k[1] = rtP.UnitDelay_InitialCondition_i[1];
    rtDW.UnitDelay_DSTATE_k[2] = rtP.UnitDelay_InitialCondition_i[2];
    rtDW.UnitDelay_DSTATE_k[3] = rtP.UnitDelay_InitialCondition_i[3];

    // InitializeConditions for Integrator: '<S10>/Integrator'
    rtX.Integrator_CSTATE_p[0] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S179>/Integrator'
    rtX.Integrator_CSTATE_if[0] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S10>/Integrator'
    rtX.Integrator_CSTATE_p[1] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S179>/Integrator'
    rtX.Integrator_CSTATE_if[1] = rtP.Integrator_IC_f;

    // InitializeConditions for Integrator: '<S10>/Integrator'
    rtX.Integrator_CSTATE_p[2] = rtP.Integrator_IC_k;

    // InitializeConditions for Integrator: '<S179>/Integrator'
    rtX.Integrator_CSTATE_if[2] = rtP.Integrator_IC_f;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn'
    rtX.TransferFcn_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn1'
    rtX.TransferFcn1_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn2'
    rtX.TransferFcn2_CSTATE = 0.0;

    // InitializeConditions for TransferFcn: '<S5>/Transfer Fcn3'
    rtX.TransferFcn3_CSTATE = 0.0;

    // InitializeConditions for Integrator: '<S171>/Integrator1'
    rtX.Integrator1_CSTATE = rtP.Integrator1_IC;

    // InitializeConditions for Integrator: '<S172>/Integrator1'
    rtX.Integrator1_CSTATE_k = rtP.Integrator1_IC_j;

    // InitializeConditions for Integrator: '<S173>/Integrator1'
    rtX.Integrator1_CSTATE_l = rtP.Integrator1_IC_i;

    // InitializeConditions for Integrator: '<S340>/Integrator1'
    rtX.Integrator1_CSTATE_b = rtP.Integrator1_IC_d;

    // InitializeConditions for Integrator: '<S341>/Integrator1'
    rtX.Integrator1_CSTATE_h = rtP.Integrator1_IC_a;

    // InitializeConditions for Integrator: '<S342>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_k;
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
