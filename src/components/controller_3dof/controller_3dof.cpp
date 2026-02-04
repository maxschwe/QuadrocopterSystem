//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.cpp
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.281
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Feb  4 17:22:20 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "controller_3dof.h"
#include <cstring>
#include <cmath>
#include "rtwtypes.h"

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
  int_T nXc { 18 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  controller_3dof_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void Controller::step()
{
  real_T A[16];
  real_T A_0[9];
  real_T tmp[9];
  real_T c_data[4];
  real_T rtb_Saturation[4];
  real_T rtb_thrust[4];
  real_T rtb_u_f[4];
  real_T B_0[3];
  real_T a21;
  real_T b_idx_0;
  real_T b_idx_1;
  real_T b_idx_2;
  real_T omega_dot_idx_2;
  real_T omega_dot_tmp;
  real_T rtb_Filter;
  real_T rtb_Saturation_0;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T s;
  real_T smax;
  int32_T c_k;
  int32_T f;
  int32_T ijA;
  int32_T jA;
  int32_T jj;
  int32_T r1;
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

  rtY.y_pred[0] = rtX.Integrator_CSTATE[0];
  rtY.y_pred[1] = rtX.Integrator_CSTATE[1];
  rtY.y_pred[2] = rtX.Integrator_CSTATE[2];

  // Sum: '<S2>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_Filter = rtU.w[1] - rtX.Integrator_CSTATE[0];

  // Gain: '<S47>/Filter Coefficient' incorporates:
  //   Gain: '<S37>/Derivative Gain'
  //   Integrator: '<S39>/Filter'
  //   Sum: '<S39>/SumD'

  rtDW.FilterCoefficient = (rtP.PIDController_D * rtb_Filter - rtX.Filter_CSTATE)
    * rtP.PIDController_N;

  // Sum: '<S2>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_Sum2 = rtU.w[2] - rtX.Integrator_CSTATE[1];

  // Gain: '<S99>/Filter Coefficient' incorporates:
  //   Gain: '<S89>/Derivative Gain'
  //   Integrator: '<S91>/Filter'
  //   Sum: '<S91>/SumD'

  rtDW.FilterCoefficient_g = (rtP.PIDController1_D * rtb_Sum2 -
    rtX.Filter_CSTATE_d) * rtP.PIDController1_N;

  // Sum: '<S2>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Integrator: '<S1>/Integrator'

  rtb_Sum1 = rtU.w[3] - rtX.Integrator_CSTATE[2];

  // Gain: '<S151>/Filter Coefficient' incorporates:
  //   Gain: '<S141>/Derivative Gain'
  //   Integrator: '<S143>/Filter'
  //   Sum: '<S143>/SumD'

  rtDW.FilterCoefficient_e = (rtP.PIDController2_D * rtb_Sum1 -
    rtX.Filter_CSTATE_a) * rtP.PIDController2_N;

  // MATLAB Function: '<S9>/MATLAB Function' incorporates:
  //   Gain: '<S101>/Proportional Gain'
  //   Gain: '<S153>/Proportional Gain'
  //   Gain: '<S49>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S148>/Integrator'
  //   Integrator: '<S44>/Integrator'
  //   Integrator: '<S96>/Integrator'
  //   SignalConversion generated from: '<S166>/ SFunction '
  //   Sum: '<S105>/Sum'
  //   Sum: '<S157>/Sum'
  //   Sum: '<S53>/Sum'

  rtb_Saturation[0] = rtU.w[0];
  rtb_Saturation[1] = (rtP.PIDController_P * rtb_Filter +
                       rtX.Integrator_CSTATE_b) + rtDW.FilterCoefficient;
  rtb_Saturation[2] = (rtP.PIDController1_P * rtb_Sum2 + rtX.Integrator_CSTATE_n)
    + rtDW.FilterCoefficient_g;
  rtb_Saturation[3] = (rtP.PIDController2_P * rtb_Sum1 + rtX.Integrator_CSTATE_f)
    + rtDW.FilterCoefficient_e;
  std::memcpy(&A[0], &rtP.E[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (r1 = 0; r1 < 3; r1++) {
    jj = r1 * 5;
    jA = 5 - r1;
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
        jA = r1 + rtemp;
        ipiv[r1] = static_cast<int8_T>(jA + 1);
        smax = A[r1];
        A[r1] = A[jA];
        A[jA] = smax;
        smax = A[r1 + 4];
        A[r1 + 4] = A[jA + 4];
        A[jA + 4] = smax;
        smax = A[r1 + 8];
        A[r1 + 8] = A[jA + 8];
        A[jA + 8] = smax;
        smax = A[r1 + 12];
        A[r1 + 12] = A[jA + 12];
        A[jA + 12] = smax;
      }

      jA = (jj - r1) + 4;
      for (rtemp = jj + 2; rtemp <= jA; rtemp++) {
        A[rtemp - 1] /= A[jj];
      }
    }

    jA = jj + 6;
    rtemp = 2 - r1;
    for (c_k = 0; c_k <= rtemp; c_k++) {
      smax = A[((c_k << 2) + jj) + 4];
      if (smax != 0.0) {
        f = (jA - r1) + 2;
        for (ijA = jA; ijA <= f; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[r1];
    if (r1 + 1 != ipiv_0) {
      smax = rtb_Saturation[r1];
      rtb_Saturation[r1] = rtb_Saturation[ipiv_0 - 1];
      rtb_Saturation[ipiv_0 - 1] = smax;
    }
  }

  for (r1 = 0; r1 < 4; r1++) {
    jj = r1 << 2;
    if (rtb_Saturation[r1] != 0.0) {
      for (jA = r1 + 2; jA < 5; jA++) {
        rtb_Saturation[jA - 1] -= A[(jA + jj) - 1] * rtb_Saturation[r1];
      }
    }
  }

  for (r1 = 3; r1 >= 0; r1--) {
    jj = r1 << 2;
    smax = rtb_Saturation[r1];
    if (smax != 0.0) {
      rtb_Saturation[r1] = smax / A[r1 + jj];
      for (jA = 0; jA < r1; jA++) {
        rtb_Saturation[jA] -= A[jA + jj] * rtb_Saturation[r1];
      }
    }
  }

  rtb_u_f[0] = 0.0;
  rtb_u_f[1] = 0.0;
  rtb_u_f[2] = 0.0;
  rtb_u_f[3] = 0.0;
  jj = 0;
  for (r1 = 0; r1 < 4; r1++) {
    if (rtb_Saturation[r1] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (r1 = 0; r1 < 4; r1++) {
    if (rtb_Saturation[r1] / rtP.a >= 0.0) {
      tmp_data[jj] = static_cast<int8_T>(r1);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = rtb_Saturation[tmp_data[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_u_f[tmp_data[jj]] = c_data[jj] + rtP.b;
  }

  // MATLAB Function: '<S1>/MATLAB Function1'
  s = rtP.guenther * rtP.a;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[0] > rtP.Saturation_UpperSat) {
    a21 = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[0] < rtP.Saturation_LowerSat) {
    a21 = rtP.Saturation_LowerSat;
  } else {
    a21 = rtb_u_f[0];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'
  //   TransferFcn: '<S1>/Transfer Fcn'

  rtb_Saturation[0] = rtP.TransferFcn_D * a21 - rtP.b;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[1] > rtP.Saturation_UpperSat) {
    a21 = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[1] < rtP.Saturation_LowerSat) {
    a21 = rtP.Saturation_LowerSat;
  } else {
    a21 = rtb_u_f[1];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'
  //   TransferFcn: '<S1>/Transfer Fcn1'

  rtb_Saturation[1] = rtP.TransferFcn1_D * a21 - rtP.b;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[2] > rtP.Saturation_UpperSat) {
    a21 = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[2] < rtP.Saturation_LowerSat) {
    a21 = rtP.Saturation_LowerSat;
  } else {
    a21 = rtb_u_f[2];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'
  //   TransferFcn: '<S1>/Transfer Fcn2'

  rtb_Saturation[2] = rtP.TransferFcn2_D * a21 - rtP.b;

  // Saturate: '<S9>/Saturation'
  if (rtb_u_f[3] > rtP.Saturation_UpperSat) {
    a21 = rtP.Saturation_UpperSat;
  } else if (rtb_u_f[3] < rtP.Saturation_LowerSat) {
    a21 = rtP.Saturation_LowerSat;
  } else {
    a21 = rtb_u_f[3];
  }

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Saturate: '<S9>/Saturation'
  //   TransferFcn: '<S1>/Transfer Fcn3'

  rtb_Saturation[3] = rtP.TransferFcn3_D * a21 - rtP.b;
  rtb_thrust[0] = rtb_Saturation[0] * rtb_Saturation[0];
  rtb_thrust[1] = rtb_Saturation[1] * rtb_Saturation[1];
  rtb_thrust[2] = rtb_Saturation[2] * rtb_Saturation[2];
  rtb_thrust[3] = rtb_Saturation[3] * rtb_Saturation[3];

  // Gain: '<S1>/Mixer' incorporates:
  //   MATLAB Function: '<S1>/MATLAB Function1'

  smax = 0.0;
  omega_dot_idx_2 = 0.0;
  rtb_Saturation_0 = 0.0;
  for (jj = 0; jj < 4; jj++) {
    a21 = s * rtb_thrust[jj];
    r1 = jj << 2;
    smax += rtP.E[r1 + 1] * a21;
    omega_dot_idx_2 += rtP.E[r1 + 2] * a21;
    rtb_Saturation_0 += rtP.E[r1 + 3] * a21;
  }

  // MATLAB Function: '<S1>/MATLAB Function2' incorporates:
  //   Gain: '<S1>/Mixer'
  //   Integrator: '<S1>/Integrator'

  s = std::sin(rtX.Integrator_CSTATE[0]);
  omega_dot_tmp = std::cos(rtX.Integrator_CSTATE[1]);
  b_idx_0 = 0.0;
  b_idx_1 = 0.0;
  b_idx_2 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    a21 = rtX.Integrator_CSTATE[jj + 3];
    b_idx_0 += rtP.I[3 * jj] * a21;
    b_idx_1 += rtP.I[3 * jj + 1] * a21;
    b_idx_2 += rtP.I[3 * jj + 2] * a21;
  }

  std::memcpy(&A_0[0], &rtP.I[0], 9U * sizeof(real_T));
  a21 = rtP.m * rtP.g;
  B_0[0] = ((a21 * s * omega_dot_tmp * rtP.d + smax) - rtP.p *
            rtX.Integrator_CSTATE[3]) - (b_idx_2 * rtX.Integrator_CSTATE[4] -
    b_idx_1 * rtX.Integrator_CSTATE[5]);
  B_0[1] = (a21 * std::sin(rtX.Integrator_CSTATE[1]) * rtP.d + omega_dot_idx_2)
    - (b_idx_0 * rtX.Integrator_CSTATE[5] - b_idx_2 * rtX.Integrator_CSTATE[3]);
  B_0[2] = rtb_Saturation_0 - (b_idx_1 * rtX.Integrator_CSTATE[3] - b_idx_0 *
    rtX.Integrator_CSTATE[4]);
  r1 = 0;
  jj = 1;
  jA = 2;
  smax = std::abs(rtP.I[0]);
  a21 = std::abs(rtP.I[1]);
  if (a21 > smax) {
    smax = a21;
    r1 = 1;
    jj = 0;
  }

  if (std::abs(rtP.I[2]) > smax) {
    r1 = 2;
    jj = 1;
    jA = 0;
  }

  A_0[jj] = rtP.I[jj] / rtP.I[r1];
  A_0[jA] /= A_0[r1];
  A_0[jj + 3] -= A_0[r1 + 3] * A_0[jj];
  A_0[jA + 3] -= A_0[r1 + 3] * A_0[jA];
  A_0[jj + 6] -= A_0[r1 + 6] * A_0[jj];
  A_0[jA + 6] -= A_0[r1 + 6] * A_0[jA];
  if (std::abs(A_0[jA + 3]) > std::abs(A_0[jj + 3])) {
    rtemp = jj;
    jj = jA;
    jA = rtemp;
  }

  A_0[jA + 3] /= A_0[jj + 3];
  A_0[jA + 6] -= A_0[jA + 3] * A_0[jj + 6];
  smax = B_0[jj] - B_0[r1] * A_0[jj];
  omega_dot_idx_2 = ((B_0[jA] - B_0[r1] * A_0[jA]) - A_0[jA + 3] * smax) /
    A_0[jA + 6];
  smax = (smax - A_0[jj + 6] * omega_dot_idx_2) / A_0[jj + 3];
  a21 = std::tan(rtX.Integrator_CSTATE[1]);
  rtb_Saturation_0 = std::cos(rtX.Integrator_CSTATE[0]);
  tmp[0] = 1.0;
  tmp[3] = s * a21;
  tmp[6] = rtb_Saturation_0 * a21;
  tmp[1] = 0.0;
  tmp[4] = rtb_Saturation_0;
  tmp[7] = -s;
  tmp[2] = 0.0;
  tmp[5] = s / omega_dot_tmp;
  tmp[8] = rtb_Saturation_0 / omega_dot_tmp;
  s = 0.0;
  omega_dot_tmp = 0.0;
  rtb_Saturation_0 = 0.0;
  for (jj = 0; jj < 3; jj++) {
    a21 = rtX.Integrator_CSTATE[jj + 3];
    s += tmp[3 * jj] * a21;
    omega_dot_tmp += tmp[3 * jj + 1] * a21;
    rtb_Saturation_0 += tmp[3 * jj + 2] * a21;
  }

  rtDW.dx[0] = s;
  rtDW.dx[3] = ((B_0[r1] - A_0[r1 + 6] * omega_dot_idx_2) - A_0[r1 + 3] * smax) /
    A_0[r1];
  rtDW.dx[1] = omega_dot_tmp;
  rtDW.dx[4] = smax;
  rtDW.dx[2] = rtb_Saturation_0;
  rtDW.dx[5] = omega_dot_idx_2;

  // End of MATLAB Function: '<S1>/MATLAB Function2'

  // Gain: '<S145>/Integral Gain'
  rtDW.IntegralGain = rtP.PIDController2_I * rtb_Sum1;

  // Gain: '<S93>/Integral Gain'
  rtDW.IntegralGain_b = rtP.PIDController1_I * rtb_Sum2;

  // Gain: '<S41>/Integral Gain'
  rtDW.IntegralGain_f = rtP.PIDController_I * rtb_Filter;

  // Sum: '<S3>/Sum' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Filter = rtU.w[1] - rtU.y[0];

  // Gain: '<S208>/Filter Coefficient' incorporates:
  //   Gain: '<S198>/Derivative Gain'
  //   Integrator: '<S200>/Filter'
  //   Sum: '<S200>/SumD'

  rtDW.FilterCoefficient_b = (rtP.PIDController_D_c * rtb_Filter -
    rtX.Filter_CSTATE_g) * rtP.PIDController_N_o;

  // Sum: '<S3>/Sum1' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum1 = rtU.w[2] - rtU.y[1];

  // Gain: '<S260>/Filter Coefficient' incorporates:
  //   Gain: '<S250>/Derivative Gain'
  //   Integrator: '<S252>/Filter'
  //   Sum: '<S252>/SumD'

  rtDW.FilterCoefficient_bz = (rtP.PIDController1_D_k * rtb_Sum1 -
    rtX.Filter_CSTATE_m) * rtP.PIDController1_N_l;

  // Sum: '<S3>/Sum2' incorporates:
  //   Inport: '<Root>/w'
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtU.w[3] - rtU.y[2];

  // Gain: '<S312>/Filter Coefficient' incorporates:
  //   Gain: '<S302>/Derivative Gain'
  //   Integrator: '<S304>/Filter'
  //   Sum: '<S304>/SumD'

  rtDW.FilterCoefficient_a = (rtP.PIDController2_D_m * rtb_Sum2 -
    rtX.Filter_CSTATE_c) * rtP.PIDController2_N_b;

  // MATLAB Function: '<S170>/MATLAB Function' incorporates:
  //   Gain: '<S210>/Proportional Gain'
  //   Gain: '<S262>/Proportional Gain'
  //   Gain: '<S314>/Proportional Gain'
  //   Inport: '<Root>/w'
  //   Integrator: '<S205>/Integrator'
  //   Integrator: '<S257>/Integrator'
  //   Integrator: '<S309>/Integrator'
  //   MATLAB Function: '<S9>/MATLAB Function'
  //   SignalConversion generated from: '<S327>/ SFunction '
  //   Sum: '<S214>/Sum'
  //   Sum: '<S266>/Sum'
  //   Sum: '<S318>/Sum'

  rtb_Saturation[0] = rtU.w[0];
  rtb_Saturation[1] = (rtP.PIDController_P_f * rtb_Filter +
                       rtX.Integrator_CSTATE_p) + rtDW.FilterCoefficient_b;
  rtb_Saturation[2] = (rtP.PIDController1_P_k * rtb_Sum1 +
                       rtX.Integrator_CSTATE_i) + rtDW.FilterCoefficient_bz;
  rtb_Saturation[3] = (rtP.PIDController2_P_n * rtb_Sum2 +
                       rtX.Integrator_CSTATE_j) + rtDW.FilterCoefficient_a;
  std::memcpy(&A[0], &rtP.E[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (r1 = 0; r1 < 3; r1++) {
    jj = r1 * 5;
    jA = 5 - r1;
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
        jA = r1 + rtemp;
        ipiv[r1] = static_cast<int8_T>(jA + 1);
        smax = A[r1];
        A[r1] = A[jA];
        A[jA] = smax;
        smax = A[r1 + 4];
        A[r1 + 4] = A[jA + 4];
        A[jA + 4] = smax;
        smax = A[r1 + 8];
        A[r1 + 8] = A[jA + 8];
        A[jA + 8] = smax;
        smax = A[r1 + 12];
        A[r1 + 12] = A[jA + 12];
        A[jA + 12] = smax;
      }

      jA = (jj - r1) + 4;
      for (rtemp = jj + 2; rtemp <= jA; rtemp++) {
        A[rtemp - 1] /= A[jj];
      }
    }

    jA = jj + 6;
    rtemp = 2 - r1;
    for (c_k = 0; c_k <= rtemp; c_k++) {
      smax = A[((c_k << 2) + jj) + 4];
      if (smax != 0.0) {
        f = (jA - r1) + 2;
        for (ijA = jA; ijA <= f; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[r1];
    if (r1 + 1 != ipiv_0) {
      smax = rtb_Saturation[r1];
      rtb_Saturation[r1] = rtb_Saturation[ipiv_0 - 1];
      rtb_Saturation[ipiv_0 - 1] = smax;
    }
  }

  for (r1 = 0; r1 < 4; r1++) {
    jj = r1 << 2;
    if (rtb_Saturation[r1] != 0.0) {
      for (jA = r1 + 2; jA < 5; jA++) {
        rtb_Saturation[jA - 1] -= A[(jA + jj) - 1] * rtb_Saturation[r1];
      }
    }
  }

  for (r1 = 3; r1 >= 0; r1--) {
    jj = r1 << 2;
    smax = rtb_Saturation[r1];
    if (smax != 0.0) {
      rtb_Saturation[r1] = smax / A[r1 + jj];
      for (jA = 0; jA < r1; jA++) {
        rtb_Saturation[jA] -= A[jA + jj] * rtb_Saturation[r1];
      }
    }
  }

  rtb_thrust[0] = 0.0;
  rtb_thrust[1] = 0.0;
  rtb_thrust[2] = 0.0;
  rtb_thrust[3] = 0.0;
  jj = 0;
  for (r1 = 0; r1 < 4; r1++) {
    if (rtb_Saturation[r1] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (r1 = 0; r1 < 4; r1++) {
    if (rtb_Saturation[r1] / rtP.a >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(r1);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    c_data[jj] = rtb_Saturation[tmp_data_0[jj]] / rtP.a;
    c_data[jj] = std::sqrt(c_data[jj]);
    rtb_thrust[tmp_data_0[jj]] = c_data[jj] + rtP.b;
  }

  // Saturate: '<S170>/Saturation' incorporates:
  //   MATLAB Function: '<S170>/MATLAB Function'

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

  // End of Saturate: '<S170>/Saturation'

  // Gain: '<S306>/Integral Gain'
  rtDW.IntegralGain_p = rtP.PIDController2_I_i * rtb_Sum2;

  // Gain: '<S254>/Integral Gain'
  rtDW.IntegralGain_o = rtP.PIDController1_I_m * rtb_Sum1;

  // Gain: '<S202>/Integral Gain'
  rtDW.IntegralGain_od = rtP.PIDController_I_a * rtb_Filter;
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
      // Update absolute timer for sample time: [0.01s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.01, which is the step size
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

  // Derivatives for Integrator: '<S44>/Integrator'
  _rtXdot->Integrator_CSTATE_b = rtDW.IntegralGain_f;

  // Derivatives for Integrator: '<S39>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S96>/Integrator'
  _rtXdot->Integrator_CSTATE_n = rtDW.IntegralGain_b;

  // Derivatives for Integrator: '<S91>/Filter'
  _rtXdot->Filter_CSTATE_d = rtDW.FilterCoefficient_g;

  // Derivatives for Integrator: '<S148>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S143>/Filter'
  _rtXdot->Filter_CSTATE_a = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S205>/Integrator'
  _rtXdot->Integrator_CSTATE_p = rtDW.IntegralGain_od;

  // Derivatives for Integrator: '<S200>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_b;

  // Derivatives for Integrator: '<S257>/Integrator'
  _rtXdot->Integrator_CSTATE_i = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S252>/Filter'
  _rtXdot->Filter_CSTATE_m = rtDW.FilterCoefficient_bz;

  // Derivatives for Integrator: '<S309>/Integrator'
  _rtXdot->Integrator_CSTATE_j = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S304>/Filter'
  _rtXdot->Filter_CSTATE_c = rtDW.FilterCoefficient_a;
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
  (&rtM)->Timing.stepSize0 = 0.01;

  {
    int32_T i;

    // InitializeConditions for Integrator: '<S1>/Integrator'
    for (i = 0; i < 6; i++) {
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC;
    }

    // End of InitializeConditions for Integrator: '<S1>/Integrator'

    // InitializeConditions for Integrator: '<S44>/Integrator'
    rtX.Integrator_CSTATE_b = rtP.PIDController_InitialConditio_g;

    // InitializeConditions for Integrator: '<S39>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S96>/Integrator'
    rtX.Integrator_CSTATE_n = rtP.PIDController1_InitialConditi_k;

    // InitializeConditions for Integrator: '<S91>/Filter'
    rtX.Filter_CSTATE_d = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S148>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController2_InitialConditi_p;

    // InitializeConditions for Integrator: '<S143>/Filter'
    rtX.Filter_CSTATE_a = rtP.PIDController2_InitialCondition;

    // InitializeConditions for Integrator: '<S205>/Integrator'
    rtX.Integrator_CSTATE_p = rtP.PIDController_InitialConditio_d;

    // InitializeConditions for Integrator: '<S200>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController_InitialConditio_e;

    // InitializeConditions for Integrator: '<S257>/Integrator'
    rtX.Integrator_CSTATE_i = rtP.PIDController1_InitialConditi_m;

    // InitializeConditions for Integrator: '<S252>/Filter'
    rtX.Filter_CSTATE_m = rtP.PIDController1_InitialConditi_j;

    // InitializeConditions for Integrator: '<S309>/Integrator'
    rtX.Integrator_CSTATE_j = rtP.PIDController2_InitialConditi_o;

    // InitializeConditions for Integrator: '<S304>/Filter'
    rtX.Filter_CSTATE_c = rtP.PIDController2_InitialConditi_e;
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
