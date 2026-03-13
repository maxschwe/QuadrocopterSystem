//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container_data.cpp
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

// Block parameters (default storage)
Controller6dof::P Controller6dof::rtP{
  // Variable: B_eff
  //  Referenced by:
  //    '<S5>/B_Eff'
  //    '<S173>/MATLAB Function'
  //    '<S511>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S6>/MATLAB Function2'

  { 0.0304, 0.0, 0.0, 0.0, 0.0315, 0.0, 0.0, 0.0, 0.0476 },

  // Variable: K_free_rot
  //  Referenced by:
  //    '<S175>/Gain'
  //    '<S513>/Gain'

  { 1.4658808426730352, -1.3178719364900466E-16, -5.0003184913000655E-16,
    1.2340210771938578E-15, 1.4701419835502234, -5.3238671917005261E-16,
    1.1195725953743822E-16, -4.0476920385327121E-17, 1.5236753327298915,
    0.4266672213053575, -4.5158131768681759E-17, -5.6899585532842519E-17,
    -1.0318007996304637E-16, 0.43093467888750181, -4.7892474575655336E-17,
    2.1093120464431523E-17, 1.9611881654182336E-17, 0.48959816801547795 },

  // Variable: K_trans
  //  Referenced by:
  //    '<S13>/Gain'
  //    '<S351>/Gain'

  { -2.9959286894540317E-15, -3.5231389930068649E-17, 0.473945095980733,
    2.3591311323926019E-17, -0.47394509598073326, -7.9638512571646389E-17,
    3.0897518205234555, 3.8087448573868891E-15, -2.8439325951851134E-14,
    -8.2047065381355278E-15, 2.502195597078797E-19, 0.40859767447687945,
    2.28073676868918E-17, -0.40859767447687872, -6.8279450341441591E-17,
    2.7631469021834349, 1.821344479024897E-15, -2.0041777166354979E-14 },

  // Variable: Ki_free_rot
  //  Referenced by:
  //    '<S175>/Gain2'
  //    '<S513>/Gain2'

  { -1.1000454440814511, 4.0381856701262286E-17, 1.2318751913849034E-15,
    -6.6757575844800025E-16, -1.1010647170865533, 6.912699716282514E-16,
    7.9657011498682125E-18, -8.76354170340842E-18, -1.1108058077650047 },

  // Variable: Ki_trans
  //  Referenced by:
  //    '<S13>/Gain2'
  //    '<S351>/Gain2'

  { -9.1096234148767587E-15, 8.8285075638692E-17, -0.26620035397537239,
    -4.3871524208757143E-17, 0.26620035397538006, 8.1196078464423474E-17,
    -1.3819160786979658, -2.4937062690067767E-15, 1.2204588711216398E-14 },

  // Variable: N
  //  Referenced by:
  //    '<S217>/Filter Coefficient'
  //    '<S269>/Filter Coefficient'
  //    '<S321>/Filter Coefficient'
  //    '<S555>/Filter Coefficient'
  //    '<S607>/Filter Coefficient'
  //    '<S659>/Filter Coefficient'

  100.0,

  // Variable: N_pos
  //  Referenced by:
  //    '<S54>/Filter Coefficient'
  //    '<S106>/Filter Coefficient'
  //    '<S158>/Filter Coefficient'
  //    '<S392>/Filter Coefficient'
  //    '<S444>/Filter Coefficient'
  //    '<S496>/Filter Coefficient'

  100.0,

  // Variable: S_free_rot
  //  Referenced by:
  //    '<S175>/Gain1'
  //    '<S513>/Gain1'

  { 1.4658808426730354, -1.3178719364900466E-16, -5.0003184913000665E-16,
    1.234021077193858E-15, 1.4701419835502234, -5.3238671917005252E-16,
    1.1195725953743824E-16, -4.0476920385327115E-17, 1.5236753327298915 },

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S173>/MATLAB Function'
  //    '<S511>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S173>/MATLAB Function'
  //    '<S511>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by:
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'
  //    '<S11>/Constant'
  //    '<S349>/Constant'

  9.81,

  // Variable: h
  //  Referenced by: '<S6>/MATLAB Function2'

  0.044,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S259>/Derivative Gain'
  //    '<S597>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S207>/Derivative Gain'
  //    '<S545>/Derivative Gain'

  0.33,

  // Variable: kd_x
  //  Referenced by:
  //    '<S44>/Derivative Gain'
  //    '<S382>/Derivative Gain'

  0.5,

  // Variable: kd_y
  //  Referenced by:
  //    '<S96>/Derivative Gain'
  //    '<S434>/Derivative Gain'

  0.5,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S311>/Derivative Gain'
  //    '<S649>/Derivative Gain'

  0.5,

  // Variable: kd_z
  //  Referenced by:
  //    '<S148>/Derivative Gain'
  //    '<S486>/Derivative Gain'

  2.0,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S263>/Integral Gain'
  //    '<S601>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S211>/Integral Gain'
  //    '<S549>/Integral Gain'

  1.18,

  // Variable: ki_x
  //  Referenced by:
  //    '<S48>/Integral Gain'
  //    '<S386>/Integral Gain'

  0.2,

  // Variable: ki_y
  //  Referenced by:
  //    '<S100>/Integral Gain'
  //    '<S438>/Integral Gain'

  0.2,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S315>/Integral Gain'
  //    '<S653>/Integral Gain'

  0.7,

  // Variable: ki_z
  //  Referenced by:
  //    '<S152>/Integral Gain'
  //    '<S490>/Integral Gain'

  2.5,

  // Variable: kp_x
  //  Referenced by:
  //    '<S56>/Proportional Gain'
  //    '<S394>/Proportional Gain'

  0.2,

  // Variable: kp_y
  //  Referenced by:
  //    '<S108>/Proportional Gain'
  //    '<S446>/Proportional Gain'

  0.2,

  // Variable: kp_z
  //  Referenced by:
  //    '<S160>/Proportional Gain'
  //    '<S498>/Proportional Gain'

  3.5,

  // Variable: m
  //  Referenced by:
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'
  //    '<S11>/Constant'
  //    '<S349>/Constant'

  1.21,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S150>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S98>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S46>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_a
  //  Referenced by: '<S488>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S436>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_m
  //  Referenced by: '<S384>/Filter'

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

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S547>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S599>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_c
  //  Referenced by: '<S651>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_k
  //  Referenced by: '<S155>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S103>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_o
  //  Referenced by: '<S51>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_i
  //  Referenced by: '<S493>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_jr
  //  Referenced by: '<S441>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_a2
  //  Referenced by: '<S389>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_ay
  //  Referenced by: '<S214>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_nz
  //  Referenced by: '<S266>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S318>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_b
  //  Referenced by: '<S552>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_b
  //  Referenced by: '<S604>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_k5
  //  Referenced by: '<S656>/Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S342>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S342>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S342>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S342>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S342>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S342>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S342>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S342>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S343>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S343>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S343>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S343>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S343>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S343>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S343>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S343>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S344>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S344>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S344>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S344>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S344>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S344>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S344>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S344>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: -inv(C_trans*inv((A_trans-B_trans*K_trans))* B_trans)
  //  Referenced by: '<S13>/Gain1'

  { -2.9959286894540321E-15, -3.5231389930068643E-17, 0.473945095980733,
    2.3591311323926019E-17, -0.47394509598073326, -7.9638512571646376E-17,
    3.0897518205234555, 3.8087448573868891E-15, -2.8439325951851128E-14 },

  // Expression: [m * g; 0; 0]
  //  Referenced by: '<S13>/Constant'

  { 11.8701, 0.0, 0.0 },

  // Computed Parameter: DiscreteTimeIntegrator_gainval
  //  Referenced by: '<S13>/Discrete-Time Integrator'

  0.02,

  // Expression: 0
  //  Referenced by: '<S13>/Discrete-Time Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S680>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S680>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S680>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S680>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S680>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S680>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S680>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S680>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S681>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S681>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S681>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S681>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S681>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S681>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S681>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S681>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S682>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S682>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S682>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S682>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S682>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.02; 0 1]
  //  Referenced by: '<S682>/Constant'

  { 1.0, 0.0, 0.02, 1.0 },

  // Expression: [0.001 0; 0 1000]
  //  Referenced by: '<S682>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 1000.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S682>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: -inv(C_trans*inv((A_trans-B_trans*K_trans))* B_trans)
  //  Referenced by: '<S351>/Gain1'

  { -2.9959286894540321E-15, -3.5231389930068643E-17, 0.473945095980733,
    2.3591311323926019E-17, -0.47394509598073326, -7.9638512571646376E-17,
    3.0897518205234555, 3.8087448573868891E-15, -2.8439325951851128E-14 },

  // Expression: [m * g; 0; 0]
  //  Referenced by: '<S351>/Constant'

  { 11.8701, 0.0, 0.0 },

  // Computed Parameter: DiscreteTimeIntegrator_gainva_g
  //  Referenced by: '<S351>/Discrete-Time Integrator'

  0.02,

  // Expression: 0
  //  Referenced by: '<S351>/Discrete-Time Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S336>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S336>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S336>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S336>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S336>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S336>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S336>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S336>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S337>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S337>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S337>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S337>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S337>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S337>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S337>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S337>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S338>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S338>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S338>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S338>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S338>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S338>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S338>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S338>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S175>/Integrator'

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

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: zeros(6, 1)
  //  Referenced by: '<S6>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S674>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S674>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S674>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S674>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S674>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S674>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S674>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S674>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S675>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S675>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S675>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S675>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S675>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S675>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S675>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S675>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S676>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S676>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-6
  //  Referenced by: '<S676>/Cov Messrauschen'

  1.0E-5,

  // Expression: 0
  //  Referenced by: '<S676>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S676>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S676>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S676>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S676>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S513>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S511>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S511>/Saturation'

  0.15,

  // Expression: [0;0]
  //  Referenced by: '<S3>/Constant1'

  { 0.0, 0.0 },

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
  //  Referenced by: '<S674>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S675>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S676>/Integrator1'

  0.0,

  // Expression: false
  //  Referenced by: '<S1>/Constant'

  false
};

//
// File trailer for generated code.
//
// [EOF]
//
