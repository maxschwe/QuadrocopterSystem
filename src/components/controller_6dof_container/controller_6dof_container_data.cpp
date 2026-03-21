//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container_data.cpp
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

// Block parameters (default storage)
Controller6dof::P Controller6dof::rtP{
  // Variable: B_eff
  //  Referenced by:
  //    '<S5>/B_Eff'
  //    '<S173>/MATLAB Function'
  //    '<S505>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S6>/MATLAB Function2'

  { 0.0276, 0.0, 0.0, 0.0, 0.0295, 0.0, 0.0, 0.0, 0.0551 },

  // Variable: N
  //  Referenced by:
  //    '<S217>/Filter Coefficient'
  //    '<S269>/Filter Coefficient'
  //    '<S321>/Filter Coefficient'
  //    '<S549>/Filter Coefficient'
  //    '<S601>/Filter Coefficient'
  //    '<S653>/Filter Coefficient'

  100.0,

  // Variable: N_pos
  //  Referenced by:
  //    '<S54>/Filter Coefficient'
  //    '<S106>/Filter Coefficient'
  //    '<S158>/Filter Coefficient'
  //    '<S386>/Filter Coefficient'
  //    '<S438>/Filter Coefficient'
  //    '<S490>/Filter Coefficient'

  10.0,

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S173>/MATLAB Function'
  //    '<S505>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S173>/MATLAB Function'
  //    '<S505>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by:
  //    '<S2>/MATLAB Function2'
  //    '<S3>/MATLAB Function2'
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'

  9.81,

  // Variable: h
  //  Referenced by: '<S6>/MATLAB Function2'

  0.0421,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S259>/Derivative Gain'
  //    '<S591>/Derivative Gain'

  0.4,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S207>/Derivative Gain'
  //    '<S539>/Derivative Gain'

  0.38,

  // Variable: kd_x
  //  Referenced by:
  //    '<S44>/Derivative Gain'
  //    '<S376>/Derivative Gain'

  0.4,

  // Variable: kd_y
  //  Referenced by:
  //    '<S96>/Derivative Gain'
  //    '<S428>/Derivative Gain'

  0.4,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S311>/Derivative Gain'
  //    '<S643>/Derivative Gain'

  0.3,

  // Variable: kd_z
  //  Referenced by:
  //    '<S148>/Derivative Gain'
  //    '<S480>/Derivative Gain'

  3.8,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S263>/Integral Gain'
  //    '<S595>/Integral Gain'

  0.8,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S211>/Integral Gain'
  //    '<S543>/Integral Gain'

  0.8,

  // Variable: ki_x
  //  Referenced by:
  //    '<S48>/Integral Gain'
  //    '<S380>/Integral Gain'

  0.3,

  // Variable: ki_y
  //  Referenced by:
  //    '<S100>/Integral Gain'
  //    '<S432>/Integral Gain'

  0.3,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S315>/Integral Gain'
  //    '<S647>/Integral Gain'

  0.3,

  // Variable: ki_z
  //  Referenced by:
  //    '<S152>/Integral Gain'
  //    '<S484>/Integral Gain'

  4.0,

  // Variable: kp_pitch
  //  Referenced by:
  //    '<S271>/Proportional Gain'
  //    '<S603>/Proportional Gain'

  1.6,

  // Variable: kp_roll
  //  Referenced by:
  //    '<S219>/Proportional Gain'
  //    '<S551>/Proportional Gain'

  1.6,

  // Variable: kp_x
  //  Referenced by:
  //    '<S56>/Proportional Gain'
  //    '<S388>/Proportional Gain'

  0.3,

  // Variable: kp_y
  //  Referenced by:
  //    '<S108>/Proportional Gain'
  //    '<S440>/Proportional Gain'

  0.3,

  // Variable: kp_yaw
  //  Referenced by:
  //    '<S323>/Proportional Gain'
  //    '<S655>/Proportional Gain'

  0.5,

  // Variable: kp_z
  //  Referenced by:
  //    '<S160>/Proportional Gain'
  //    '<S492>/Proportional Gain'

  2.5,

  // Variable: m
  //  Referenced by:
  //    '<S2>/MATLAB Function2'
  //    '<S3>/MATLAB Function2'
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'

  1.21,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S541>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S593>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S645>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_i
  //  Referenced by: '<S209>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_n
  //  Referenced by: '<S261>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_h
  //  Referenced by: '<S313>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_b
  //  Referenced by: '<S546>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_b
  //  Referenced by: '<S598>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S650>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S214>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_nz
  //  Referenced by: '<S266>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S318>/Integrator'

  0.0,

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S3>/Rate Transition'

  0.0,

  // Expression: zeros(6, 1)
  //  Referenced by: '<S6>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0.90
  //  Referenced by: '<S505>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S505>/Saturation'

  0.15,

  // Expression: [0;0]
  //  Referenced by: '<S3>/Constant1'

  { 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S2>/Rate Transition'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S173>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S173>/Saturation'

  0.15,

  // Expression: [0;0]
  //  Referenced by: '<S2>/Constant1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S336>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S336>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S336>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S336>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S336>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S336>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S336>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S336>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S337>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S337>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S337>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S337>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S337>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S337>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S337>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S337>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S338>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S338>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S338>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S338>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S338>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S338>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S338>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S338>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S668>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S668>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S668>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S668>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S668>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S668>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S668>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S668>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S669>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S669>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S669>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S669>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S669>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S669>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S669>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S669>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S670>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S670>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S670>/Constant2'

  { 1.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S670>/Constant5'

  0.0,

  // Expression: 10e-6
  //  Referenced by: '<S670>/Cov Messrauschen'

  1.0E-5,

  // Expression: [0; 0]
  //  Referenced by: '<S670>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S670>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S670>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S175>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S507>/Integrator'

  0.0,

  // Computed Parameter: TransferFcn_A
  //  Referenced by: '<S5>/Transfer Fcn'

  -50.0,

  // Computed Parameter: TransferFcn_C
  //  Referenced by: '<S5>/Transfer Fcn'

  50.0,

  // Computed Parameter: TransferFcn1_A
  //  Referenced by: '<S5>/Transfer Fcn1'

  -50.0,

  // Computed Parameter: TransferFcn1_C
  //  Referenced by: '<S5>/Transfer Fcn1'

  50.0,

  // Computed Parameter: TransferFcn2_A
  //  Referenced by: '<S5>/Transfer Fcn2'

  -50.0,

  // Computed Parameter: TransferFcn2_C
  //  Referenced by: '<S5>/Transfer Fcn2'

  50.0,

  // Computed Parameter: TransferFcn3_A
  //  Referenced by: '<S5>/Transfer Fcn3'

  -50.0,

  // Computed Parameter: TransferFcn3_C
  //  Referenced by: '<S5>/Transfer Fcn3'

  50.0,

  // Expression: 0
  //  Referenced by: '<S336>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S337>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S338>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S668>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S669>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S670>/Integrator1'

  0.0,

  // Expression: false
  //  Referenced by: '<S1>/Constant'

  false,

  // Start of '<S3>/Subsystem'
  {
    // Mask Parameter: PIDController_InitialConditionF
    //  Referenced by: '<S378>/Filter'

    0.0,

    // Mask Parameter: PIDController1_InitialCondition
    //  Referenced by: '<S430>/Filter'

    0.0,

    // Mask Parameter: PIDController2_InitialCondition
    //  Referenced by: '<S482>/Filter'

    0.0,

    // Mask Parameter: PIDController_InitialConditio_o
    //  Referenced by: '<S383>/Integrator'

    0.0,

    // Mask Parameter: PIDController1_InitialConditi_j
    //  Referenced by: '<S435>/Integrator'

    0.0,

    // Mask Parameter: PIDController2_InitialConditi_k
    //  Referenced by: '<S487>/Integrator'

    0.0,

    // Mask Parameter: PIDController_LowerIntegratorSa
    //  Referenced by: '<S383>/Integrator'

    -0.087266462599716474,

    // Mask Parameter: PIDController1_LowerIntegratorS
    //  Referenced by: '<S435>/Integrator'

    -0.087266462599716474,

    // Mask Parameter: PIDController_UpperIntegratorSa
    //  Referenced by: '<S383>/Integrator'

    0.087266462599716474,

    // Mask Parameter: PIDController1_UpperIntegratorS
    //  Referenced by: '<S435>/Integrator'

    0.087266462599716474,

    // Computed Parameter: Filter_gainval
    //  Referenced by: '<S378>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval
    //  Referenced by: '<S383>/Integrator'

    0.02,

    // Computed Parameter: Filter_gainval_m
    //  Referenced by: '<S430>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval_c
    //  Referenced by: '<S435>/Integrator'

    0.02,

    // Computed Parameter: Filter_gainval_n
    //  Referenced by: '<S482>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval_d
    //  Referenced by: '<S487>/Integrator'

    0.02
  }
  ,

  // End of '<S3>/Subsystem'

  // Start of '<S2>/Subsystem'
  {
    // Mask Parameter: PIDController_InitialConditionF
    //  Referenced by: '<S46>/Filter'

    0.0,

    // Mask Parameter: PIDController1_InitialCondition
    //  Referenced by: '<S98>/Filter'

    0.0,

    // Mask Parameter: PIDController2_InitialCondition
    //  Referenced by: '<S150>/Filter'

    0.0,

    // Mask Parameter: PIDController_InitialConditio_o
    //  Referenced by: '<S51>/Integrator'

    0.0,

    // Mask Parameter: PIDController1_InitialConditi_j
    //  Referenced by: '<S103>/Integrator'

    0.0,

    // Mask Parameter: PIDController2_InitialConditi_k
    //  Referenced by: '<S155>/Integrator'

    0.0,

    // Mask Parameter: PIDController_LowerIntegratorSa
    //  Referenced by: '<S51>/Integrator'

    -0.087266462599716474,

    // Mask Parameter: PIDController1_LowerIntegratorS
    //  Referenced by: '<S103>/Integrator'

    -0.087266462599716474,

    // Mask Parameter: PIDController_UpperIntegratorSa
    //  Referenced by: '<S51>/Integrator'

    0.087266462599716474,

    // Mask Parameter: PIDController1_UpperIntegratorS
    //  Referenced by: '<S103>/Integrator'

    0.087266462599716474,

    // Computed Parameter: Filter_gainval
    //  Referenced by: '<S46>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval
    //  Referenced by: '<S51>/Integrator'

    0.02,

    // Computed Parameter: Filter_gainval_m
    //  Referenced by: '<S98>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval_c
    //  Referenced by: '<S103>/Integrator'

    0.02,

    // Computed Parameter: Filter_gainval_n
    //  Referenced by: '<S150>/Filter'

    0.02,

    // Computed Parameter: Integrator_gainval_d
    //  Referenced by: '<S155>/Integrator'

    0.02
  }
  // End of '<S2>/Subsystem'
};

//
// File trailer for generated code.
//
// [EOF]
//
