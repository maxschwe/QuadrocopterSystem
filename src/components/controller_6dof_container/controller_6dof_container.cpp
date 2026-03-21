//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container.cpp
//
// Code generated for Simulink model 'controller_6dof_container'.
//
// Model version                  : 1.545
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Mar 21 21:34:57 2026
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
  int_T nXc { 40 };

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
void Controller6dof::MATLABFunction(const real_T rtu_u[4], real_T rty_y[4])
{
  rty_y[0] = 0.0;
  rty_y[1] = 0.0;
  rty_y[2] = 0.0;
  rty_y[3] = 0.0;
  rty_y[0] = std::fmin(std::fmax(rtu_u[0], -15.0), 15.0);
  rty_y[1] = std::fmin(std::fmax(rtu_u[1], -0.087266462599716474),
                       0.087266462599716474);
  rty_y[2] = std::fmin(std::fmax(rtu_u[2], -0.087266462599716474),
                       0.087266462599716474);
}

//
// Output and update for atomic system:
//    '<S2>/MATLAB Function2'
//    '<S3>/MATLAB Function2'
//
void Controller6dof::MATLABFunction2(const real_T rtu_eta[3], real_T rty_u[4])
  const
{
  rty_u[0] = rtP.m * rtP.g / std::abs(std::cos(rtu_eta[0]) * std::cos(rtu_eta[1]));
  rty_u[1] = 0.0;
  rty_u[2] = 0.0;
  rty_u[3] = 0.0;
}

//
// System initialize for atomic system:
//    '<S2>/Subsystem'
//    '<S3>/Subsystem'
//
void Controller6dof::Subsystem_Init(DW_Subsystem *localDW, P_Subsystem *localP)
{
  // InitializeConditions for DiscreteIntegrator: '<S46>/Filter'
  localDW->Filter_DSTATE = localP->PIDController_InitialConditionF;

  // InitializeConditions for DiscreteIntegrator: '<S51>/Integrator'
  localDW->Integrator_DSTATE = localP->PIDController_InitialConditio_o;

  // InitializeConditions for DiscreteIntegrator: '<S98>/Filter'
  localDW->Filter_DSTATE_j = localP->PIDController1_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S103>/Integrator'
  localDW->Integrator_DSTATE_n = localP->PIDController1_InitialConditi_j;

  // InitializeConditions for DiscreteIntegrator: '<S150>/Filter'
  localDW->Filter_DSTATE_l = localP->PIDController2_InitialCondition;

  // InitializeConditions for DiscreteIntegrator: '<S155>/Integrator'
  localDW->Integrator_DSTATE_k = localP->PIDController2_InitialConditi_k;
}

//
// Output and update for atomic system:
//    '<S2>/Subsystem'
//    '<S3>/Subsystem'
//
void Controller6dof::Subsystem(const real_T rtu_w[3], const real_T rtu_y[3],
  real_T *rty_u, real_T *rty_u_b, real_T *rty_u_k, DW_Subsystem *localDW,
  P_Subsystem *localP) const
{
  real_T rtb_FilterCoefficient;
  real_T rtb_FilterCoefficient_h;
  real_T rtb_FilterCoefficient_p;
  real_T rtb_IntegralGain;
  real_T rtb_IntegralGain_oz;
  real_T rtb_Sum2_p;

  // Sum: '<S12>/Sum'
  rtb_Sum2_p = rtu_w[0] - rtu_y[0];

  // Gain: '<S54>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S46>/Filter'
  //   Gain: '<S44>/Derivative Gain'
  //   Sum: '<S46>/SumD'

  rtb_FilterCoefficient = (rtP.kd_x * rtb_Sum2_p - localDW->Filter_DSTATE) *
    rtP.N_pos;

  // Sum: '<S60>/Sum' incorporates:
  //   DiscreteIntegrator: '<S51>/Integrator'
  //   Gain: '<S56>/Proportional Gain'

  *rty_u_k = (rtP.kp_x * rtb_Sum2_p + localDW->Integrator_DSTATE) +
    rtb_FilterCoefficient;

  // Gain: '<S48>/Integral Gain'
  rtb_IntegralGain = rtP.ki_x * rtb_Sum2_p;

  // Sum: '<S12>/Sum1'
  rtb_Sum2_p = rtu_y[1] - rtu_w[1];

  // Gain: '<S106>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S98>/Filter'
  //   Gain: '<S96>/Derivative Gain'
  //   Sum: '<S98>/SumD'

  rtb_FilterCoefficient_p = (rtP.kd_y * rtb_Sum2_p - localDW->Filter_DSTATE_j) *
    rtP.N_pos;

  // Sum: '<S112>/Sum' incorporates:
  //   DiscreteIntegrator: '<S103>/Integrator'
  //   Gain: '<S108>/Proportional Gain'

  *rty_u_b = (rtP.kp_y * rtb_Sum2_p + localDW->Integrator_DSTATE_n) +
    rtb_FilterCoefficient_p;

  // Gain: '<S100>/Integral Gain'
  rtb_IntegralGain_oz = rtP.ki_y * rtb_Sum2_p;

  // Sum: '<S12>/Sum2'
  rtb_Sum2_p = rtu_w[2] - rtu_y[2];

  // Gain: '<S158>/Filter Coefficient' incorporates:
  //   DiscreteIntegrator: '<S150>/Filter'
  //   Gain: '<S148>/Derivative Gain'
  //   Sum: '<S150>/SumD'

  rtb_FilterCoefficient_h = (rtP.kd_z * rtb_Sum2_p - localDW->Filter_DSTATE_l) *
    rtP.N_pos;

  // Sum: '<S164>/Sum' incorporates:
  //   DiscreteIntegrator: '<S155>/Integrator'
  //   Gain: '<S160>/Proportional Gain'

  *rty_u = (rtP.kp_z * rtb_Sum2_p + localDW->Integrator_DSTATE_k) +
    rtb_FilterCoefficient_h;

  // Update for DiscreteIntegrator: '<S46>/Filter'
  localDW->Filter_DSTATE += localP->Filter_gainval * rtb_FilterCoefficient;

  // Update for DiscreteIntegrator: '<S51>/Integrator'
  localDW->Integrator_DSTATE += localP->Integrator_gainval * rtb_IntegralGain;
  if (localDW->Integrator_DSTATE > localP->PIDController_UpperIntegratorSa) {
    localDW->Integrator_DSTATE = localP->PIDController_UpperIntegratorSa;
  } else if (localDW->Integrator_DSTATE <
             localP->PIDController_LowerIntegratorSa) {
    localDW->Integrator_DSTATE = localP->PIDController_LowerIntegratorSa;
  }

  // End of Update for DiscreteIntegrator: '<S51>/Integrator'

  // Update for DiscreteIntegrator: '<S98>/Filter'
  localDW->Filter_DSTATE_j += localP->Filter_gainval_m * rtb_FilterCoefficient_p;

  // Update for DiscreteIntegrator: '<S103>/Integrator'
  localDW->Integrator_DSTATE_n += localP->Integrator_gainval_c *
    rtb_IntegralGain_oz;
  if (localDW->Integrator_DSTATE_n > localP->PIDController1_UpperIntegratorS) {
    localDW->Integrator_DSTATE_n = localP->PIDController1_UpperIntegratorS;
  } else if (localDW->Integrator_DSTATE_n <
             localP->PIDController1_LowerIntegratorS) {
    localDW->Integrator_DSTATE_n = localP->PIDController1_LowerIntegratorS;
  }

  // End of Update for DiscreteIntegrator: '<S103>/Integrator'

  // Update for DiscreteIntegrator: '<S150>/Filter'
  localDW->Filter_DSTATE_l += localP->Filter_gainval_n * rtb_FilterCoefficient_h;

  // Update for DiscreteIntegrator: '<S155>/Integrator' incorporates:
  //   Gain: '<S152>/Integral Gain'

  localDW->Integrator_DSTATE_k += rtP.ki_z * rtb_Sum2_p *
    localP->Integrator_gainval_d;
}

//
// Output and update for atomic system:
//    '<S336>/KF_Elevation'
//    '<S337>/KF_Elevation'
//    '<S338>/KF_Elevation'
//    '<S668>/KF_Elevation'
//    '<S669>/KF_Elevation'
//    '<S670>/KF_Elevation'
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
  // local block i/o variables
  real_T rtb_RateTransition1[3];
  real_T rtb_RateTransition1_f[3];
  real_T A[16];
  real_T dx_c_tmp_5[9];
  real_T dx_c_tmp_6[9];
  real_T dx_c_tmp_7[9];
  real_T VectorConcatenate2[6];
  real_T B_0[4];
  real_T B_2[4];
  real_T rtb_Saturation_a[4];
  real_T rtb_Sum[4];
  real_T rtb_thrust[4];
  real_T B_1[3];
  real_T tmp_1[3];
  real_T dx_c_tmp;
  real_T dx_c_tmp_0;
  real_T dx_c_tmp_1;
  real_T dx_c_tmp_2;
  real_T dx_c_tmp_3;
  real_T dx_c_tmp_4;
  real_T rtb_Filter;
  real_T rtb_Saturation_k;
  real_T rtb_Sum1;
  real_T rtb_Sum2;
  real_T s;
  real_T smax;
  real_T tau_idx_0;
  real_T tau_idx_2;
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
  boolean_T tmp_0;
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

  // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
  //   Integrator: '<S4>/Integrator'
  //   Outport: '<Root>/x_pred'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i] = rtX.Integrator_CSTATE[i];
  }

  // SignalConversion generated from: '<S1>/Vector Concatenate2' incorporates:
  //   Concatenate: '<S1>/Vector Concatenate2'
  //   Integrator: '<S4>/Integrator'

  VectorConcatenate2[0] = rtX.Integrator_CSTATE[0];
  VectorConcatenate2[1] = rtX.Integrator_CSTATE[1];
  VectorConcatenate2[2] = rtX.Integrator_CSTATE[2];

  // RateTransition: '<S3>/Rate Transition' incorporates:
  //   Concatenate: '<S3>/Vector Concatenate1'
  //   RateTransition: '<S2>/Rate Transition'
  //   RateTransition: '<S2>/Rate Transition1'
  //   RateTransition: '<S2>/Rate Transition2'
  //   RateTransition: '<S3>/Rate Transition1'
  //   RateTransition: '<S3>/Rate Transition2'

  tmp = ((&rtM)->isMajorTimeStep() &&
         (&rtM)->Timing.TaskCounters.TID[1] == 0);
  if (tmp && ((&rtM)->isMajorTimeStep() &&
              (&rtM)->Timing.TaskCounters.TID[2] == 0)) {
    rtDW.VectorConcatenate1[0] = rtDW.RateTransition_Buffer0[0];
    rtDW.VectorConcatenate1[1] = rtDW.RateTransition_Buffer0[1];
    rtDW.VectorConcatenate1[2] = rtDW.RateTransition_Buffer0[2];
  }

  // End of RateTransition: '<S3>/Rate Transition'

  // SignalConversion generated from: '<S3>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S3>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtDW.VectorConcatenate1[3] = rtU.w[3];

  // SignalConversion generated from: '<S1>/Vector Concatenate2' incorporates:
  //   Concatenate: '<S1>/Vector Concatenate2'
  //   Integrator: '<S6>/Integrator'

  VectorConcatenate2[3] = rtX.Integrator_CSTATE_h[0];
  VectorConcatenate2[4] = rtX.Integrator_CSTATE_h[1];
  VectorConcatenate2[5] = rtX.Integrator_CSTATE_h[2];

  // MATLAB Function: '<S3>/MATLAB Function2' incorporates:
  //   Concatenate: '<S1>/Vector Concatenate2'

  MATLABFunction2(&VectorConcatenate2[3], rtb_Saturation_a);

  // Sum: '<S3>/Sum' incorporates:
  //   Saturate: '<S173>/Saturation'

  rtb_Sum[0] = rtb_Saturation_a[0] + rtDW.VectorConcatenate1[0];
  rtb_Sum[1] = rtb_Saturation_a[1] + rtDW.VectorConcatenate1[1];
  rtb_Sum[2] = rtb_Saturation_a[2] + rtDW.VectorConcatenate1[2];
  rtb_Sum[3] = rtb_Saturation_a[3] + rtDW.VectorConcatenate1[3];

  // MATLAB Function: '<S3>/MATLAB Function'
  MATLABFunction(rtb_Sum, rtb_Saturation_a);

  // SignalConversion generated from: '<S345>/Vector Concatenate1' incorporates:
  //   MATLAB Function: '<S505>/MATLAB Function'

  B_0[0] = rtb_Saturation_a[0];

  // Sum: '<S506>/Sum' incorporates:
  //   Integrator: '<S6>/Integrator'

  rtb_Filter = rtb_Saturation_a[1] - rtX.Integrator_CSTATE_h[0];

  // Gain: '<S549>/Filter Coefficient' incorporates:
  //   Gain: '<S539>/Derivative Gain'
  //   Integrator: '<S541>/Filter'
  //   Sum: '<S541>/SumD'

  rtDW.FilterCoefficient = (rtP.kd_roll * rtb_Filter - rtX.Filter_CSTATE) *
    rtP.N;

  // Sum: '<S506>/Sum1' incorporates:
  //   Integrator: '<S6>/Integrator'

  rtb_Sum2 = rtb_Saturation_a[2] - rtX.Integrator_CSTATE_h[1];

  // Gain: '<S601>/Filter Coefficient' incorporates:
  //   Gain: '<S591>/Derivative Gain'
  //   Integrator: '<S593>/Filter'
  //   Sum: '<S593>/SumD'

  rtDW.FilterCoefficient_m = (rtP.kd_pitch * rtb_Sum2 - rtX.Filter_CSTATE_d) *
    rtP.N;

  // Sum: '<S506>/Sum2' incorporates:
  //   Integrator: '<S6>/Integrator'

  rtb_Sum1 = rtb_Saturation_a[3] - rtX.Integrator_CSTATE_h[2];

  // Gain: '<S653>/Filter Coefficient' incorporates:
  //   Gain: '<S643>/Derivative Gain'
  //   Integrator: '<S645>/Filter'
  //   Sum: '<S645>/SumD'

  rtDW.FilterCoefficient_f = (rtP.kd_yaw * rtb_Sum1 - rtX.Filter_CSTATE_g) *
    rtP.N;

  // SignalConversion generated from: '<S345>/Vector Concatenate1' incorporates:
  //   Gain: '<S551>/Proportional Gain'
  //   Gain: '<S603>/Proportional Gain'
  //   Gain: '<S655>/Proportional Gain'
  //   Integrator: '<S546>/Integrator'
  //   Integrator: '<S598>/Integrator'
  //   Integrator: '<S650>/Integrator'
  //   MATLAB Function: '<S505>/MATLAB Function'
  //   Sum: '<S555>/Sum'
  //   Sum: '<S607>/Sum'
  //   Sum: '<S659>/Sum'

  B_0[1] = (rtP.kp_roll * rtb_Filter + rtX.Integrator_CSTATE_m) +
    rtDW.FilterCoefficient;
  B_0[2] = (rtP.kp_pitch * rtb_Sum2 + rtX.Integrator_CSTATE_b) +
    rtDW.FilterCoefficient_m;
  B_0[3] = (rtP.kp_yaw * rtb_Sum1 + rtX.Integrator_CSTATE_l) +
    rtDW.FilterCoefficient_f;

  // MATLAB Function: '<S505>/MATLAB Function'
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

  rtb_Saturation_a[0] = 0.0;
  rtb_Saturation_a[1] = 0.0;
  rtb_Saturation_a[2] = 0.0;
  rtb_Saturation_a[3] = 0.0;
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
    rtb_Sum[jj] = B_0[tmp_data[jj]] / rtP.a;
    rtb_Sum[jj] = std::sqrt(rtb_Sum[jj]);
    rtb_Saturation_a[tmp_data[jj]] = rtb_Sum[jj] + rtP.b;
  }

  // Saturate: '<S505>/Saturation'
  if (rtb_Saturation_a[0] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[0] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[0];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S505>/Saturation'

  rtb_Saturation_k = smax - rtP.b;
  rtb_thrust[0] = rtb_Saturation_k * rtb_Saturation_k;

  // Saturate: '<S505>/Saturation'
  if (rtb_Saturation_a[1] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[1] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[1];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S505>/Saturation'

  rtb_Saturation_k = smax - rtP.b;
  rtb_thrust[1] = rtb_Saturation_k * rtb_Saturation_k;

  // Saturate: '<S505>/Saturation'
  if (rtb_Saturation_a[2] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[2] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[2];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S505>/Saturation'

  rtb_Saturation_k = smax - rtP.b;
  rtb_thrust[2] = rtb_Saturation_k * rtb_Saturation_k;

  // Saturate: '<S505>/Saturation'
  if (rtb_Saturation_a[3] > rtP.Saturation_UpperSat) {
    smax = rtP.Saturation_UpperSat;
  } else if (rtb_Saturation_a[3] < rtP.Saturation_LowerSat) {
    smax = rtP.Saturation_LowerSat;
  } else {
    smax = rtb_Saturation_a[3];
  }

  // MATLAB Function: '<S5>/MATLAB Function1' incorporates:
  //   Saturate: '<S505>/Saturation'

  rtb_Saturation_k = smax - rtP.b;
  rtb_thrust[3] = rtb_Saturation_k * rtb_Saturation_k;

  // Gain: '<S5>/B_Eff' incorporates:
  //   MATLAB Function: '<S5>/MATLAB Function1'

  rtb_Saturation_k = 0.0;
  tau_idx_0 = 0.0;
  s = 0.0;
  tau_idx_2 = 0.0;
  for (i = 0; i < 4; i++) {
    smax = rtP.a * rtb_thrust[i];
    jj = i << 2;
    rtb_Saturation_k += rtP.B_eff[jj] * smax;
    tau_idx_0 += rtP.B_eff[jj + 1] * smax;
    s += rtP.B_eff[jj + 2] * smax;
    tau_idx_2 += rtP.B_eff[jj + 3] * smax;
  }

  rtb_Saturation_a[3] = tau_idx_2;
  rtb_Saturation_a[2] = s;
  rtb_Saturation_a[1] = tau_idx_0;
  rtb_Saturation_a[0] = rtb_Saturation_k;

  // MATLAB Function: '<S4>/MATLAB Function2' incorporates:
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S4>/Integrator'
  //   Integrator: '<S6>/Integrator'

  dx_c_tmp = std::sin(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_0 = std::cos(rtX.Integrator_CSTATE_h[2]);
  dx_c_tmp_1 = std::sin(rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_2 = std::cos(rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_3 = std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_4 = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_5[0] = dx_c_tmp_0;
  dx_c_tmp_5[3] = -dx_c_tmp;
  dx_c_tmp_5[6] = 0.0;
  dx_c_tmp_5[1] = dx_c_tmp;
  dx_c_tmp_5[4] = dx_c_tmp_0;
  dx_c_tmp_5[7] = 0.0;
  dx_c_tmp_6[0] = dx_c_tmp_2;
  dx_c_tmp_6[3] = 0.0;
  dx_c_tmp_6[6] = dx_c_tmp_1;
  dx_c_tmp_6[2] = -dx_c_tmp_1;
  dx_c_tmp_6[5] = 0.0;
  dx_c_tmp_6[8] = dx_c_tmp_2;
  for (i = 0; i < 3; i++) {
    jj = 3 * i + 2;
    dx_c_tmp_5[jj] = b[i];
    jA = 3 * i + 1;
    dx_c_tmp_6[jA] = c[i];
    dx_c_tmp_7[3 * i] = 0.0;
    dx_c_tmp_7[jA] = 0.0;
    dx_c_tmp_7[jj] = 0.0;
  }

  for (i = 0; i < 3; i++) {
    dx_c_tmp = dx_c_tmp_7[3 * i];
    jj = 3 * i + 1;
    dx_c_tmp_0 = dx_c_tmp_7[jj];
    jA = 3 * i + 2;
    dx_c_tmp_1 = dx_c_tmp_7[jA];
    for (rtemp = 0; rtemp < 3; rtemp++) {
      smax = dx_c_tmp_6[3 * i + rtemp];
      dx_c_tmp += dx_c_tmp_5[3 * rtemp] * smax;
      dx_c_tmp_0 += dx_c_tmp_5[3 * rtemp + 1] * smax;
      dx_c_tmp_1 += dx_c_tmp_5[3 * rtemp + 2] * smax;
    }

    dx_c_tmp_7[jA] = dx_c_tmp_1;
    dx_c_tmp_7[jj] = dx_c_tmp_0;
    dx_c_tmp_7[3 * i] = dx_c_tmp;
  }

  dx_c_tmp_6[1] = 0.0;
  dx_c_tmp_6[4] = dx_c_tmp_4;
  dx_c_tmp_6[7] = -dx_c_tmp_3;
  dx_c_tmp_6[2] = 0.0;
  dx_c_tmp_6[5] = dx_c_tmp_3;
  dx_c_tmp_6[8] = dx_c_tmp_4;
  tmp_1[0] = 0.0;
  tmp_1[1] = 0.0;
  tmp_1[2] = rtb_Saturation_k / rtP.m;
  dx_c_tmp = 0.0;
  dx_c_tmp_0 = 0.0;
  dx_c_tmp_1 = 0.0;
  for (i = 0; i < 3; i++) {
    dx_c_tmp_6[3 * i] = d[i];
    dx_c_tmp_2 = 0.0;
    dx_c_tmp_3 = 0.0;
    dx_c_tmp_4 = 0.0;
    for (rtemp = 0; rtemp < 3; rtemp++) {
      smax = dx_c_tmp_6[3 * i + rtemp];
      dx_c_tmp_2 += dx_c_tmp_7[3 * rtemp] * smax;
      dx_c_tmp_3 += dx_c_tmp_7[3 * rtemp + 1] * smax;
      dx_c_tmp_4 += dx_c_tmp_7[3 * rtemp + 2] * smax;
    }

    jj = 3 * i + 2;
    dx_c_tmp_5[jj] = dx_c_tmp_4;
    jA = 3 * i + 1;
    dx_c_tmp_5[jA] = dx_c_tmp_3;
    dx_c_tmp_5[3 * i] = dx_c_tmp_2;
    smax = tmp_1[i];
    dx_c_tmp += dx_c_tmp_5[3 * i] * smax;
    dx_c_tmp_0 += dx_c_tmp_5[jA] * smax;
    dx_c_tmp_1 += dx_c_tmp_5[jj] * smax;
    rtDW.dx_c[i] = rtX.Integrator_CSTATE[i + 3];
  }

  rtDW.dx_c[3] = dx_c_tmp;
  rtDW.dx_c[4] = dx_c_tmp_0;
  rtDW.dx_c[5] = -rtP.g + dx_c_tmp_1;

  // End of MATLAB Function: '<S4>/MATLAB Function2'

  // MATLAB Function: '<S6>/MATLAB Function2' incorporates:
  //   Constant: '<S1>/Constant'
  //   Gain: '<S5>/B_Eff'
  //   Integrator: '<S6>/Integrator'

  if (rtP.Constant_Value_c) {
    tau_idx_0 += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[0]) * std::cos
      (rtX.Integrator_CSTATE_h[1]) * rtP.h;
    s += rtP.m * rtP.g * std::sin(rtX.Integrator_CSTATE_h[1]) * rtP.h;
  }

  rtb_Saturation_k = 0.0;
  dx_c_tmp = 0.0;
  dx_c_tmp_0 = 0.0;
  for (i = 0; i < 3; i++) {
    smax = rtX.Integrator_CSTATE_h[i + 3];
    rtb_Saturation_k += rtP.J[3 * i] * smax;
    dx_c_tmp += rtP.J[3 * i + 1] * smax;
    dx_c_tmp_0 += rtP.J[3 * i + 2] * smax;
  }

  std::memcpy(&dx_c_tmp_5[0], &rtP.J[0], 9U * sizeof(real_T));
  B_1[0] = tau_idx_0 - (dx_c_tmp_0 * rtX.Integrator_CSTATE_h[4] - dx_c_tmp *
                        rtX.Integrator_CSTATE_h[5]);
  B_1[1] = s - (rtb_Saturation_k * rtX.Integrator_CSTATE_h[5] - dx_c_tmp_0 *
                rtX.Integrator_CSTATE_h[3]);
  B_1[2] = tau_idx_2 - (dx_c_tmp * rtX.Integrator_CSTATE_h[3] - rtb_Saturation_k
                        * rtX.Integrator_CSTATE_h[4]);
  jj = 0;
  i = 1;
  jA = 2;
  smax = std::abs(rtP.J[0]);
  s = std::abs(rtP.J[1]);
  if (s > smax) {
    smax = s;
    jj = 1;
    i = 0;
  }

  if (std::abs(rtP.J[2]) > smax) {
    jj = 2;
    i = 1;
    jA = 0;
  }

  dx_c_tmp_5[i] = rtP.J[i] / rtP.J[jj];
  dx_c_tmp_5[jA] /= dx_c_tmp_5[jj];
  dx_c_tmp_5[i + 3] -= dx_c_tmp_5[jj + 3] * dx_c_tmp_5[i];
  dx_c_tmp_5[jA + 3] -= dx_c_tmp_5[jj + 3] * dx_c_tmp_5[jA];
  dx_c_tmp_5[i + 6] -= dx_c_tmp_5[jj + 6] * dx_c_tmp_5[i];
  dx_c_tmp_5[jA + 6] -= dx_c_tmp_5[jj + 6] * dx_c_tmp_5[jA];
  if (std::abs(dx_c_tmp_5[jA + 3]) > std::abs(dx_c_tmp_5[i + 3])) {
    rtemp = i;
    i = jA;
    jA = rtemp;
  }

  dx_c_tmp_5[jA + 3] /= dx_c_tmp_5[i + 3];
  dx_c_tmp_5[jA + 6] -= dx_c_tmp_5[jA + 3] * dx_c_tmp_5[i + 6];
  s = B_1[i] - B_1[jj] * dx_c_tmp_5[i];
  tau_idx_2 = ((B_1[jA] - B_1[jj] * dx_c_tmp_5[jA]) - dx_c_tmp_5[jA + 3] * s) /
    dx_c_tmp_5[jA + 6];
  s = (s - dx_c_tmp_5[i + 6] * tau_idx_2) / dx_c_tmp_5[i + 3];
  dx_c_tmp_7[0] = 1.0;
  dx_c_tmp_7[3] = std::sin(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_7[6] = std::cos(rtX.Integrator_CSTATE_h[0]) * std::tan
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_7[1] = 0.0;
  dx_c_tmp_7[4] = std::cos(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_7[7] = -std::sin(rtX.Integrator_CSTATE_h[0]);
  dx_c_tmp_7[2] = 0.0;
  dx_c_tmp_7[5] = std::sin(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  dx_c_tmp_7[8] = std::cos(rtX.Integrator_CSTATE_h[0]) / std::cos
    (rtX.Integrator_CSTATE_h[1]);
  tau_idx_0 = 0.0;
  rtb_Saturation_k = 0.0;
  dx_c_tmp = 0.0;
  for (i = 0; i < 3; i++) {
    smax = rtX.Integrator_CSTATE_h[i + 3];
    tau_idx_0 += dx_c_tmp_7[3 * i] * smax;
    rtb_Saturation_k += dx_c_tmp_7[3 * i + 1] * smax;
    dx_c_tmp += dx_c_tmp_7[3 * i + 2] * smax;
  }

  rtDW.dx[0] = tau_idx_0;
  rtDW.dx[3] = ((B_1[jj] - dx_c_tmp_5[jj + 6] * tau_idx_2) - dx_c_tmp_5[jj + 3] *
                s) / dx_c_tmp_5[jj];
  rtDW.dx[1] = rtb_Saturation_k;
  rtDW.dx[4] = s;
  rtDW.dx[2] = dx_c_tmp;
  rtDW.dx[5] = tau_idx_2;

  // End of MATLAB Function: '<S6>/MATLAB Function2'

  // SignalConversion generated from: '<S1>/Vector Concatenate1' incorporates:
  //   Integrator: '<S6>/Integrator'
  //   Outport: '<Root>/x_pred'

  for (i = 0; i < 6; i++) {
    rtY.x_pred[i + 6] = rtX.Integrator_CSTATE_h[i];
  }

  // RateTransition: '<S3>/Rate Transition1' incorporates:
  //   Inport: '<Root>/w'
  //   RateTransition: '<S2>/Rate Transition'
  //   RateTransition: '<S2>/Rate Transition1'
  //   RateTransition: '<S2>/Rate Transition2'
  //   RateTransition: '<S3>/Rate Transition2'

  if (tmp && ((&rtM)->isMajorTimeStep() &&
              (&rtM)->Timing.TaskCounters.TID[2] == 0)) {
    rtDW.RateTransition1_Buffer[0] = rtU.w[0];
    rtDW.RateTransition1_Buffer[1] = rtU.w[1];
    rtDW.RateTransition1_Buffer[2] = rtU.w[2];
  }

  tmp_0 = ((&rtM)->isMajorTimeStep() &&
           (&rtM)->Timing.TaskCounters.TID[2] == 0);
  if (tmp_0) {
    // RateTransition: '<S3>/Rate Transition1'
    rtb_RateTransition1[0] = rtDW.RateTransition1_Buffer[0];
    rtb_RateTransition1[1] = rtDW.RateTransition1_Buffer[1];
    rtb_RateTransition1[2] = rtDW.RateTransition1_Buffer[2];
  }

  // RateTransition: '<S3>/Rate Transition2' incorporates:
  //   Integrator: '<S4>/Integrator'

  if (tmp && tmp_0) {
    rtDW.RateTransition2_Buffer[0] = rtX.Integrator_CSTATE[0];
    rtDW.RateTransition2_Buffer[1] = rtX.Integrator_CSTATE[1];
    rtDW.RateTransition2_Buffer[2] = rtX.Integrator_CSTATE[2];
  }

  if (tmp_0) {
    // Outputs for Atomic SubSystem: '<S3>/Subsystem'
    Subsystem(rtb_RateTransition1, rtDW.RateTransition2_Buffer, &rtDW.Sum_k,
              &rtDW.Sum_a, &rtDW.Sum_d, &rtDW.Subsystem_gq, &rtP.Subsystem_gq);

    // End of Outputs for SubSystem: '<S3>/Subsystem'
  }

  // Gain: '<S647>/Integral Gain'
  rtDW.IntegralGain = rtP.ki_yaw * rtb_Sum1;

  // Gain: '<S595>/Integral Gain'
  rtDW.IntegralGain_k = rtP.ki_pitch * rtb_Sum2;

  // Gain: '<S543>/Integral Gain'
  rtDW.IntegralGain_e = rtP.ki_roll * rtb_Filter;

  // MATLAB Function: '<S2>/MATLAB Function2' incorporates:
  //   Inport: '<Root>/y'

  MATLABFunction2(&rtU.y[3], rtb_Saturation_a);

  // RateTransition: '<S2>/Rate Transition' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate1'

  if (tmp && tmp_0) {
    rtDW.VectorConcatenate1_j[0] = rtDW.RateTransition_Buffer0_g[0];
    rtDW.VectorConcatenate1_j[1] = rtDW.RateTransition_Buffer0_g[1];
    rtDW.VectorConcatenate1_j[2] = rtDW.RateTransition_Buffer0_g[2];
  }

  // SignalConversion generated from: '<S2>/Vector Concatenate1' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate1'
  //   Inport: '<Root>/w'

  rtDW.VectorConcatenate1_j[3] = rtU.w[3];

  // Sum: '<S2>/Sum' incorporates:
  //   Saturate: '<S173>/Saturation'

  rtb_thrust[0] = rtb_Saturation_a[0] + rtDW.VectorConcatenate1_j[0];
  rtb_thrust[1] = rtb_Saturation_a[1] + rtDW.VectorConcatenate1_j[1];
  rtb_thrust[2] = rtb_Saturation_a[2] + rtDW.VectorConcatenate1_j[2];
  rtb_thrust[3] = rtb_Saturation_a[3] + rtDW.VectorConcatenate1_j[3];

  // MATLAB Function: '<S2>/MATLAB Function'
  MATLABFunction(rtb_thrust, rtb_Saturation_a);

  // SignalConversion generated from: '<S13>/Vector Concatenate1' incorporates:
  //   MATLAB Function: '<S173>/MATLAB Function'

  B_2[0] = rtb_Saturation_a[0];

  // SignalConversion generated from: '<S2>/Vector Concatenate' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'
  //   Saturate: '<S173>/Saturation'

  rtDW.VectorConcatenate_l[0] = rtb_Saturation_a[0];
  rtDW.VectorConcatenate_l[1] = rtb_Saturation_a[1];
  rtDW.VectorConcatenate_l[2] = rtb_Saturation_a[2];
  rtDW.VectorConcatenate_l[3] = rtb_Saturation_a[3];

  // Sum: '<S174>/Sum' incorporates:
  //   Inport: '<Root>/y'

  rtb_Filter = rtb_Saturation_a[1] - rtU.y[3];

  // Gain: '<S217>/Filter Coefficient' incorporates:
  //   Gain: '<S207>/Derivative Gain'
  //   Integrator: '<S209>/Filter'
  //   Sum: '<S209>/SumD'

  rtDW.FilterCoefficient_e = (rtP.kd_roll * rtb_Filter - rtX.Filter_CSTATE_o) *
    rtP.N;

  // Sum: '<S174>/Sum1' incorporates:
  //   Inport: '<Root>/y'

  rtb_Sum1 = rtb_Saturation_a[2] - rtU.y[4];

  // Gain: '<S269>/Filter Coefficient' incorporates:
  //   Gain: '<S259>/Derivative Gain'
  //   Integrator: '<S261>/Filter'
  //   Sum: '<S261>/SumD'

  rtDW.FilterCoefficient_g = (rtP.kd_pitch * rtb_Sum1 - rtX.Filter_CSTATE_n) *
    rtP.N;

  // Sum: '<S174>/Sum2' incorporates:
  //   Inport: '<Root>/y'

  rtb_Sum2 = rtb_Saturation_a[3] - rtU.y[5];

  // Gain: '<S321>/Filter Coefficient' incorporates:
  //   Gain: '<S311>/Derivative Gain'
  //   Integrator: '<S313>/Filter'
  //   Sum: '<S313>/SumD'

  rtDW.FilterCoefficient_a = (rtP.kd_yaw * rtb_Sum2 - rtX.Filter_CSTATE_a) *
    rtP.N;

  // SignalConversion generated from: '<S13>/Vector Concatenate1' incorporates:
  //   Gain: '<S219>/Proportional Gain'
  //   Gain: '<S271>/Proportional Gain'
  //   Gain: '<S323>/Proportional Gain'
  //   Integrator: '<S214>/Integrator'
  //   Integrator: '<S266>/Integrator'
  //   Integrator: '<S318>/Integrator'
  //   MATLAB Function: '<S173>/MATLAB Function'
  //   Sum: '<S223>/Sum'
  //   Sum: '<S275>/Sum'
  //   Sum: '<S327>/Sum'

  B_2[1] = (rtP.kp_roll * rtb_Filter + rtX.Integrator_CSTATE_bg) +
    rtDW.FilterCoefficient_e;
  B_2[2] = (rtP.kp_pitch * rtb_Sum1 + rtX.Integrator_CSTATE_f) +
    rtDW.FilterCoefficient_g;
  B_2[3] = (rtP.kp_yaw * rtb_Sum2 + rtX.Integrator_CSTATE_bj) +
    rtDW.FilterCoefficient_a;

  // MATLAB Function: '<S173>/MATLAB Function' incorporates:
  //   MATLAB Function: '<S505>/MATLAB Function'

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
      smax = B_2[i];
      B_2[i] = B_2[ipiv_0 - 1];
      B_2[ipiv_0 - 1] = smax;
    }
  }

  for (i = 0; i < 4; i++) {
    jj = i << 2;
    if (B_2[i] != 0.0) {
      for (jA = i + 2; jA < 5; jA++) {
        B_2[jA - 1] -= A[(jA + jj) - 1] * B_2[i];
      }
    }
  }

  for (i = 3; i >= 0; i--) {
    jj = i << 2;
    smax = B_2[i];
    if (smax != 0.0) {
      B_2[i] = smax / A[i + jj];
      for (jA = 0; jA < i; jA++) {
        B_2[jA] -= A[jA + jj] * B_2[i];
      }
    }
  }

  rtb_thrust[0] = 0.0;
  rtb_thrust[1] = 0.0;
  rtb_thrust[2] = 0.0;
  rtb_thrust[3] = 0.0;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_2[i] / rtP.a >= 0.0) {
      jj++;
    }
  }

  jA = jj;
  jj = 0;
  for (i = 0; i < 4; i++) {
    if (B_2[i] / rtP.a >= 0.0) {
      tmp_data_0[jj] = static_cast<int8_T>(i);
      jj++;
    }
  }

  for (jj = 0; jj < jA; jj++) {
    rtb_Sum[jj] = B_2[tmp_data_0[jj]] / rtP.a;
    rtb_Sum[jj] = std::sqrt(rtb_Sum[jj]);
    rtb_thrust[tmp_data_0[jj]] = rtb_Sum[jj] + rtP.b;
  }

  // Saturate: '<S173>/Saturation' incorporates:
  //   MATLAB Function: '<S173>/MATLAB Function'

  if (rtb_thrust[0] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[0] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[0] = rtb_thrust[0];
  }

  if (rtb_thrust[1] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[1] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[1] = rtb_thrust[1];
  }

  if (rtb_thrust[2] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[2] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[2] = rtb_thrust[2];
  }

  if (rtb_thrust[3] > rtP.Saturation_UpperSat_k) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_UpperSat_k;
  } else if (rtb_thrust[3] < rtP.Saturation_LowerSat_a) {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtP.Saturation_LowerSat_a;
  } else {
    // Outport: '<Root>/throttles'
    rtY.throttles[3] = rtb_thrust[3];
  }

  // End of Saturate: '<S173>/Saturation'

  // Gain: '<S315>/Integral Gain'
  rtDW.IntegralGain_p = rtP.ki_yaw * rtb_Sum2;

  // Gain: '<S263>/Integral Gain'
  rtDW.IntegralGain_i = rtP.ki_pitch * rtb_Sum1;

  // Gain: '<S211>/Integral Gain'
  rtDW.IntegralGain_o = rtP.ki_roll * rtb_Filter;
  if (tmp) {
    // Constant: '<S2>/Constant1' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate'

    rtDW.VectorConcatenate_l[4] = rtP.Constant1_Value_o[0];
    rtDW.VectorConcatenate_l[5] = rtP.Constant1_Value_o[1];
  }

  // Outport: '<Root>/values' incorporates:
  //   Concatenate: '<S2>/Vector Concatenate'

  for (i = 0; i < 6; i++) {
    rtY.values[i] = rtDW.VectorConcatenate_l[i];
  }

  // End of Outport: '<Root>/values'
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
    //   UnitDelay: '<S336>/Unit Delay'

    KF_Elevation(rtP.Constant_Value, rtP.Constant1_Value_e, rtP.Constant2_Value,
                 rtP.CovProzessrauschen_Value, rtP.CovMessrauschen_Value, 0.0,
                 rtP.Constant5_Value, rtDW.UnitDelay_DSTATE, rtDW.x_dach_fe,
                 rtDW.P_h);

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
    //   UnitDelay: '<S337>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_f, rtP.Constant1_Value_o1,
                 rtP.Constant2_Value_j, rtP.CovProzessrauschen_Value_c,
                 rtP.CovMessrauschen_Value_m, 0.0, rtP.Constant5_Value_e,
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
    //   UnitDelay: '<S338>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_g, rtP.Constant1_Value_f,
                 rtP.Constant2_Value_l, rtP.CovProzessrauschen_Value_h,
                 rtP.CovMessrauschen_Value_k, 0.0, rtP.Constant5_Value_c,
                 rtDW.UnitDelay_DSTATE_d, rtDW.x_dach_m, rtDW.P_j);
  }

  // Sum: '<S175>/Sum'
  rtDW.Sum[0] = 0.0 - rtDW.x_dach_fe[0];
  rtDW.Sum[1] = 0.0 - rtDW.x_dach_l[0];
  rtDW.Sum[2] = 0.0 - rtDW.x_dach_m[0];

  // RateTransition: '<S2>/Rate Transition1' incorporates:
  //   Inport: '<Root>/w'

  if (tmp) {
    // UnitDelay: '<S668>/Unit Delay1'
    rtDW.x_dach_e[0] = rtDW.UnitDelay1_DSTATE_j[0];
    rtDW.x_dach_e[1] = rtDW.UnitDelay1_DSTATE_j[1];

    // MATLAB Function: '<S668>/KF_Elevation' incorporates:
    //   Constant: '<S668>/Constant'
    //   Constant: '<S668>/Constant1'
    //   Constant: '<S668>/Constant2'
    //   Constant: '<S668>/Constant5'
    //   Constant: '<S668>/Cov Messrauschen'
    //   Constant: '<S668>/Cov Prozessrauschen'
    //   UnitDelay: '<S668>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_n, rtP.Constant1_Value_d,
                 rtP.Constant2_Value_e, rtP.CovProzessrauschen_Value_b,
                 rtP.CovMessrauschen_Value_a, 0.0, rtP.Constant5_Value_a,
                 rtDW.UnitDelay_DSTATE_j, rtDW.x_dach_e, rtDW.P_k);

    // UnitDelay: '<S669>/Unit Delay1'
    rtDW.x_dach_f[0] = rtDW.UnitDelay1_DSTATE_c[0];
    rtDW.x_dach_f[1] = rtDW.UnitDelay1_DSTATE_c[1];

    // MATLAB Function: '<S669>/KF_Elevation' incorporates:
    //   Constant: '<S669>/Constant'
    //   Constant: '<S669>/Constant1'
    //   Constant: '<S669>/Constant2'
    //   Constant: '<S669>/Constant5'
    //   Constant: '<S669>/Cov Messrauschen'
    //   Constant: '<S669>/Cov Prozessrauschen'
    //   UnitDelay: '<S669>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_e, rtP.Constant1_Value_et,
                 rtP.Constant2_Value_g, rtP.CovProzessrauschen_Value_a,
                 rtP.CovMessrauschen_Value_h, 0.0, rtP.Constant5_Value_ek,
                 rtDW.UnitDelay_DSTATE_a, rtDW.x_dach_f, rtDW.P_l);

    // UnitDelay: '<S670>/Unit Delay1'
    rtDW.x_dach[0] = rtDW.UnitDelay1_DSTATE_k[0];
    rtDW.x_dach[1] = rtDW.UnitDelay1_DSTATE_k[1];

    // MATLAB Function: '<S670>/KF_Elevation' incorporates:
    //   Constant: '<S670>/Constant'
    //   Constant: '<S670>/Constant1'
    //   Constant: '<S670>/Constant2'
    //   Constant: '<S670>/Constant5'
    //   Constant: '<S670>/Cov Messrauschen'
    //   Constant: '<S670>/Cov Prozessrauschen'
    //   UnitDelay: '<S670>/Unit Delay'

    KF_Elevation(rtP.Constant_Value_h, rtP.Constant1_Value_j,
                 rtP.Constant2_Value_jg, rtP.CovProzessrauschen_Value_g,
                 rtP.CovMessrauschen_Value_j, 0.0, rtP.Constant5_Value_i,
                 rtDW.UnitDelay_DSTATE_n, rtDW.x_dach, rtDW.P_o);
    if (tmp_0) {
      rtDW.RateTransition1_Buffer_g[0] = rtU.w[0];
      rtDW.RateTransition1_Buffer_g[1] = rtU.w[1];
      rtDW.RateTransition1_Buffer_g[2] = rtU.w[2];
    }
  }

  // Sum: '<S507>/Sum'
  rtDW.Sum_j[0] = 0.0 - rtDW.x_dach_e[0];
  rtDW.Sum_j[1] = 0.0 - rtDW.x_dach_f[0];
  rtDW.Sum_j[2] = 0.0 - rtDW.x_dach[0];

  // RateTransition: '<S2>/Rate Transition1'
  if (tmp_0) {
    // RateTransition: '<S2>/Rate Transition1'
    rtb_RateTransition1_f[0] = rtDW.RateTransition1_Buffer_g[0];
    rtb_RateTransition1_f[1] = rtDW.RateTransition1_Buffer_g[1];
    rtb_RateTransition1_f[2] = rtDW.RateTransition1_Buffer_g[2];
  }

  // RateTransition: '<S2>/Rate Transition2' incorporates:
  //   Inport: '<Root>/y'

  if (tmp && tmp_0) {
    rtDW.RateTransition2_Buffer_b[0] = rtU.y[0];
    rtDW.RateTransition2_Buffer_b[1] = rtU.y[1];
    rtDW.RateTransition2_Buffer_b[2] = rtU.y[2];
  }

  if (tmp_0) {
    // Outputs for Atomic SubSystem: '<S2>/Subsystem'
    Subsystem(rtb_RateTransition1_f, rtDW.RateTransition2_Buffer_b, &rtDW.Sum_f,
              &rtDW.Sum_n, &rtDW.Sum_k2, &rtDW.Subsystem_g, &rtP.Subsystem_g);

    // End of Outputs for SubSystem: '<S2>/Subsystem'
  }

  if ((&rtM)->isMajorTimeStep()) {
    // Update for RateTransition: '<S3>/Rate Transition'
    if ((&rtM)->isMajorTimeStep() &&
        (&rtM)->Timing.TaskCounters.TID[2] == 0) {
      rtDW.RateTransition_Buffer0[0] = rtDW.Sum_k;
      rtDW.RateTransition_Buffer0[1] = rtDW.Sum_a;
      rtDW.RateTransition_Buffer0[2] = rtDW.Sum_d;

      // Update for RateTransition: '<S2>/Rate Transition'
      rtDW.RateTransition_Buffer0_g[0] = rtDW.Sum_f;
      rtDW.RateTransition_Buffer0_g[1] = rtDW.Sum_n;
      rtDW.RateTransition_Buffer0_g[2] = rtDW.Sum_k2;
    }

    // End of Update for RateTransition: '<S3>/Rate Transition'
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

      // Update for UnitDelay: '<S668>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_j[0] = rtDW.x_dach_e[0];
      rtDW.UnitDelay1_DSTATE_j[1] = rtDW.x_dach_e[1];

      // Update for UnitDelay: '<S668>/Unit Delay'
      rtDW.UnitDelay_DSTATE_j[0] = rtDW.P_k[0];
      rtDW.UnitDelay_DSTATE_j[1] = rtDW.P_k[1];
      rtDW.UnitDelay_DSTATE_j[2] = rtDW.P_k[2];
      rtDW.UnitDelay_DSTATE_j[3] = rtDW.P_k[3];

      // Update for UnitDelay: '<S669>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_c[0] = rtDW.x_dach_f[0];
      rtDW.UnitDelay1_DSTATE_c[1] = rtDW.x_dach_f[1];

      // Update for UnitDelay: '<S669>/Unit Delay'
      rtDW.UnitDelay_DSTATE_a[0] = rtDW.P_l[0];
      rtDW.UnitDelay_DSTATE_a[1] = rtDW.P_l[1];
      rtDW.UnitDelay_DSTATE_a[2] = rtDW.P_l[2];
      rtDW.UnitDelay_DSTATE_a[3] = rtDW.P_l[3];

      // Update for UnitDelay: '<S670>/Unit Delay1'
      rtDW.UnitDelay1_DSTATE_k[0] = rtDW.x_dach[0];
      rtDW.UnitDelay1_DSTATE_k[1] = rtDW.x_dach[1];

      // Update for UnitDelay: '<S670>/Unit Delay'
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
  for (i = 0; i < 6; i++) {
    // Derivatives for Integrator: '<S4>/Integrator'
    _rtXdot->Integrator_CSTATE[i] = rtDW.dx_c[i];

    // Derivatives for Integrator: '<S6>/Integrator'
    _rtXdot->Integrator_CSTATE_h[i] = rtDW.dx[i];
  }

  // Derivatives for Integrator: '<S546>/Integrator'
  _rtXdot->Integrator_CSTATE_m = rtDW.IntegralGain_e;

  // Derivatives for Integrator: '<S541>/Filter'
  _rtXdot->Filter_CSTATE = rtDW.FilterCoefficient;

  // Derivatives for Integrator: '<S598>/Integrator'
  _rtXdot->Integrator_CSTATE_b = rtDW.IntegralGain_k;

  // Derivatives for Integrator: '<S593>/Filter'
  _rtXdot->Filter_CSTATE_d = rtDW.FilterCoefficient_m;

  // Derivatives for Integrator: '<S650>/Integrator'
  _rtXdot->Integrator_CSTATE_l = rtDW.IntegralGain;

  // Derivatives for Integrator: '<S645>/Filter'
  _rtXdot->Filter_CSTATE_g = rtDW.FilterCoefficient_f;

  // Derivatives for Integrator: '<S214>/Integrator'
  _rtXdot->Integrator_CSTATE_bg = rtDW.IntegralGain_o;

  // Derivatives for Integrator: '<S209>/Filter'
  _rtXdot->Filter_CSTATE_o = rtDW.FilterCoefficient_e;

  // Derivatives for Integrator: '<S266>/Integrator'
  _rtXdot->Integrator_CSTATE_f = rtDW.IntegralGain_i;

  // Derivatives for Integrator: '<S261>/Filter'
  _rtXdot->Filter_CSTATE_n = rtDW.FilterCoefficient_g;

  // Derivatives for Integrator: '<S318>/Integrator'
  _rtXdot->Integrator_CSTATE_bj = rtDW.IntegralGain_p;

  // Derivatives for Integrator: '<S313>/Filter'
  _rtXdot->Filter_CSTATE_a = rtDW.FilterCoefficient_a;

  // Derivatives for Integrator: '<S175>/Integrator'
  _rtXdot->Integrator_CSTATE_a[0] = rtDW.Sum[0];

  // Derivatives for Integrator: '<S507>/Integrator'
  _rtXdot->Integrator_CSTATE_n[0] = rtDW.Sum_j[0];

  // Derivatives for Integrator: '<S175>/Integrator'
  _rtXdot->Integrator_CSTATE_a[1] = rtDW.Sum[1];

  // Derivatives for Integrator: '<S507>/Integrator'
  _rtXdot->Integrator_CSTATE_n[1] = rtDW.Sum_j[1];

  // Derivatives for Integrator: '<S175>/Integrator'
  _rtXdot->Integrator_CSTATE_a[2] = rtDW.Sum[2];

  // Derivatives for Integrator: '<S507>/Integrator'
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

  // Derivatives for Integrator: '<S668>/Integrator1'
  _rtXdot->Integrator1_CSTATE_n = rtDW.x_dach_e[1];

  // Derivatives for Integrator: '<S669>/Integrator1'
  _rtXdot->Integrator1_CSTATE_p = rtDW.x_dach_f[1];

  // Derivatives for Integrator: '<S670>/Integrator1'
  _rtXdot->Integrator1_CSTATE_o = rtDW.x_dach[1];
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

    // Start for RateTransition: '<S3>/Rate Transition' incorporates:
    //   Concatenate: '<S3>/Vector Concatenate1'

    rtDW.VectorConcatenate1[0] = rtP.RateTransition_InitialCondition;

    // Start for RateTransition: '<S2>/Rate Transition' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate1'

    rtDW.VectorConcatenate1_j[0] = rtP.RateTransition_InitialConditi_f;

    // Start for RateTransition: '<S3>/Rate Transition' incorporates:
    //   Concatenate: '<S3>/Vector Concatenate1'

    rtDW.VectorConcatenate1[1] = rtP.RateTransition_InitialCondition;

    // Start for RateTransition: '<S2>/Rate Transition' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate1'

    rtDW.VectorConcatenate1_j[1] = rtP.RateTransition_InitialConditi_f;

    // Start for RateTransition: '<S3>/Rate Transition' incorporates:
    //   Concatenate: '<S3>/Vector Concatenate1'

    rtDW.VectorConcatenate1[2] = rtP.RateTransition_InitialCondition;

    // Start for RateTransition: '<S2>/Rate Transition' incorporates:
    //   Concatenate: '<S2>/Vector Concatenate1'

    rtDW.VectorConcatenate1_j[2] = rtP.RateTransition_InitialConditi_f;

    // InitializeConditions for RateTransition: '<S3>/Rate Transition'
    rtDW.RateTransition_Buffer0[0] = rtP.RateTransition_InitialCondition;
    rtDW.RateTransition_Buffer0[1] = rtP.RateTransition_InitialCondition;
    rtDW.RateTransition_Buffer0[2] = rtP.RateTransition_InitialCondition;
    for (i = 0; i < 6; i++) {
      // InitializeConditions for Integrator: '<S4>/Integrator'
      rtX.Integrator_CSTATE[i] = rtP.Integrator_IC[i];

      // InitializeConditions for Integrator: '<S6>/Integrator'
      rtX.Integrator_CSTATE_h[i] = rtP.Integrator_IC_b[i];
    }

    // InitializeConditions for Integrator: '<S546>/Integrator'
    rtX.Integrator_CSTATE_m = rtP.PIDController_InitialConditio_b;

    // InitializeConditions for Integrator: '<S541>/Filter'
    rtX.Filter_CSTATE = rtP.PIDController_InitialConditionF;

    // InitializeConditions for Integrator: '<S598>/Integrator'
    rtX.Integrator_CSTATE_b = rtP.PIDController1_InitialConditi_b;

    // InitializeConditions for Integrator: '<S593>/Filter'
    rtX.Filter_CSTATE_d = rtP.PIDController1_InitialCondition;

    // InitializeConditions for Integrator: '<S650>/Integrator'
    rtX.Integrator_CSTATE_l = rtP.PIDController2_InitialConditi_k;

    // InitializeConditions for Integrator: '<S645>/Filter'
    rtX.Filter_CSTATE_g = rtP.PIDController2_InitialCondition;

    // InitializeConditions for RateTransition: '<S2>/Rate Transition'
    rtDW.RateTransition_Buffer0_g[0] = rtP.RateTransition_InitialConditi_f;
    rtDW.RateTransition_Buffer0_g[1] = rtP.RateTransition_InitialConditi_f;
    rtDW.RateTransition_Buffer0_g[2] = rtP.RateTransition_InitialConditi_f;

    // InitializeConditions for Integrator: '<S214>/Integrator'
    rtX.Integrator_CSTATE_bg = rtP.PIDController_InitialConditio_a;

    // InitializeConditions for Integrator: '<S209>/Filter'
    rtX.Filter_CSTATE_o = rtP.PIDController_InitialConditio_i;

    // InitializeConditions for Integrator: '<S266>/Integrator'
    rtX.Integrator_CSTATE_f = rtP.PIDController1_InitialCondit_nz;

    // InitializeConditions for Integrator: '<S261>/Filter'
    rtX.Filter_CSTATE_n = rtP.PIDController1_InitialConditi_n;

    // InitializeConditions for Integrator: '<S318>/Integrator'
    rtX.Integrator_CSTATE_bj = rtP.PIDController2_InitialConditi_n;

    // InitializeConditions for Integrator: '<S313>/Filter'
    rtX.Filter_CSTATE_a = rtP.PIDController2_InitialConditi_h;

    // InitializeConditions for UnitDelay: '<S336>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE[0] = rtP.UnitDelay1_InitialCondition[0];
    rtDW.UnitDelay1_DSTATE[1] = rtP.UnitDelay1_InitialCondition[1];

    // InitializeConditions for UnitDelay: '<S336>/Unit Delay'
    rtDW.UnitDelay_DSTATE[0] = rtP.UnitDelay_InitialCondition[0];
    rtDW.UnitDelay_DSTATE[1] = rtP.UnitDelay_InitialCondition[1];
    rtDW.UnitDelay_DSTATE[2] = rtP.UnitDelay_InitialCondition[2];
    rtDW.UnitDelay_DSTATE[3] = rtP.UnitDelay_InitialCondition[3];

    // InitializeConditions for UnitDelay: '<S337>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_h[0] = rtP.UnitDelay1_InitialCondition_a[0];
    rtDW.UnitDelay1_DSTATE_h[1] = rtP.UnitDelay1_InitialCondition_a[1];

    // InitializeConditions for UnitDelay: '<S337>/Unit Delay'
    rtDW.UnitDelay_DSTATE_o[0] = rtP.UnitDelay_InitialCondition_f[0];
    rtDW.UnitDelay_DSTATE_o[1] = rtP.UnitDelay_InitialCondition_f[1];
    rtDW.UnitDelay_DSTATE_o[2] = rtP.UnitDelay_InitialCondition_f[2];
    rtDW.UnitDelay_DSTATE_o[3] = rtP.UnitDelay_InitialCondition_f[3];

    // InitializeConditions for UnitDelay: '<S338>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_i[0] = rtP.UnitDelay1_InitialCondition_e[0];
    rtDW.UnitDelay1_DSTATE_i[1] = rtP.UnitDelay1_InitialCondition_e[1];

    // InitializeConditions for UnitDelay: '<S338>/Unit Delay'
    rtDW.UnitDelay_DSTATE_d[0] = rtP.UnitDelay_InitialCondition_a[0];
    rtDW.UnitDelay_DSTATE_d[1] = rtP.UnitDelay_InitialCondition_a[1];
    rtDW.UnitDelay_DSTATE_d[2] = rtP.UnitDelay_InitialCondition_a[2];
    rtDW.UnitDelay_DSTATE_d[3] = rtP.UnitDelay_InitialCondition_a[3];

    // InitializeConditions for UnitDelay: '<S668>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_j[0] = rtP.UnitDelay1_InitialCondition_d[0];
    rtDW.UnitDelay1_DSTATE_j[1] = rtP.UnitDelay1_InitialCondition_d[1];

    // InitializeConditions for UnitDelay: '<S668>/Unit Delay'
    rtDW.UnitDelay_DSTATE_j[0] = rtP.UnitDelay_InitialCondition_b[0];
    rtDW.UnitDelay_DSTATE_j[1] = rtP.UnitDelay_InitialCondition_b[1];
    rtDW.UnitDelay_DSTATE_j[2] = rtP.UnitDelay_InitialCondition_b[2];
    rtDW.UnitDelay_DSTATE_j[3] = rtP.UnitDelay_InitialCondition_b[3];

    // InitializeConditions for UnitDelay: '<S669>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_c[0] = rtP.UnitDelay1_InitialCondition_f[0];
    rtDW.UnitDelay1_DSTATE_c[1] = rtP.UnitDelay1_InitialCondition_f[1];

    // InitializeConditions for UnitDelay: '<S669>/Unit Delay'
    rtDW.UnitDelay_DSTATE_a[0] = rtP.UnitDelay_InitialCondition_h[0];
    rtDW.UnitDelay_DSTATE_a[1] = rtP.UnitDelay_InitialCondition_h[1];
    rtDW.UnitDelay_DSTATE_a[2] = rtP.UnitDelay_InitialCondition_h[2];
    rtDW.UnitDelay_DSTATE_a[3] = rtP.UnitDelay_InitialCondition_h[3];

    // InitializeConditions for UnitDelay: '<S670>/Unit Delay1'
    rtDW.UnitDelay1_DSTATE_k[0] = rtP.UnitDelay1_InitialCondition_c[0];
    rtDW.UnitDelay1_DSTATE_k[1] = rtP.UnitDelay1_InitialCondition_c[1];

    // InitializeConditions for UnitDelay: '<S670>/Unit Delay'
    rtDW.UnitDelay_DSTATE_n[0] = rtP.UnitDelay_InitialCondition_m[0];
    rtDW.UnitDelay_DSTATE_n[1] = rtP.UnitDelay_InitialCondition_m[1];
    rtDW.UnitDelay_DSTATE_n[2] = rtP.UnitDelay_InitialCondition_m[2];
    rtDW.UnitDelay_DSTATE_n[3] = rtP.UnitDelay_InitialCondition_m[3];

    // InitializeConditions for Integrator: '<S175>/Integrator'
    rtX.Integrator_CSTATE_a[0] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S507>/Integrator'
    rtX.Integrator_CSTATE_n[0] = rtP.Integrator_IC_g;

    // InitializeConditions for Integrator: '<S175>/Integrator'
    rtX.Integrator_CSTATE_a[1] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S507>/Integrator'
    rtX.Integrator_CSTATE_n[1] = rtP.Integrator_IC_g;

    // InitializeConditions for Integrator: '<S175>/Integrator'
    rtX.Integrator_CSTATE_a[2] = rtP.Integrator_IC_p;

    // InitializeConditions for Integrator: '<S507>/Integrator'
    rtX.Integrator_CSTATE_n[2] = rtP.Integrator_IC_g;

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

    // InitializeConditions for Integrator: '<S668>/Integrator1'
    rtX.Integrator1_CSTATE_n = rtP.Integrator1_IC_h;

    // InitializeConditions for Integrator: '<S669>/Integrator1'
    rtX.Integrator1_CSTATE_p = rtP.Integrator1_IC_g;

    // InitializeConditions for Integrator: '<S670>/Integrator1'
    rtX.Integrator1_CSTATE_o = rtP.Integrator1_IC_e;

    // SystemInitialize for Atomic SubSystem: '<S3>/Subsystem'
    Subsystem_Init(&rtDW.Subsystem_gq, &rtP.Subsystem_gq);

    // End of SystemInitialize for SubSystem: '<S3>/Subsystem'

    // SystemInitialize for Atomic SubSystem: '<S2>/Subsystem'
    Subsystem_Init(&rtDW.Subsystem_g, &rtP.Subsystem_g);

    // End of SystemInitialize for SubSystem: '<S2>/Subsystem'
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
