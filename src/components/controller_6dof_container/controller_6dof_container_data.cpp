//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_6dof_container_data.cpp
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

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S178>/Gain'
  //    '<S516>/Gain'

  { 1.7563670662077679, -1.2698609834614055E-16, 7.3843539275653778E-17,
    2.1850200759364754E-16, 1.7563670662077688, 1.6188710462632714E-15,
    -3.8317272026029079E-16, -2.876136846988219E-15, 1.0000000000000029,
    0.31722001925528159, 1.695022032664676E-17, 4.4901791306286382E-17,
    5.3516229243932911E-17, 0.32270927279633083, -5.0638879409143236E-16,
    -1.3622420633259404E-16, -1.5351106422209885E-16, 0.38209946349085777 },

  // Variable: K_trans
  //  Referenced by:
  //    '<S13>/Gain'
  //    '<S351>/Gain'

  { -3.4466897622412041E-16, 7.2033734718998049E-16, 0.38672574164509788,
    -7.7783699351924841E-16, -0.38672574164509749, 4.45848295193725E-16,
    3.7195407832640641, 2.0628943996749794E-16, -5.9892899673442118E-16,
    -1.7493251432970292E-16, 3.0491858590604214E-16, 0.52805602783332617,
    -2.8984191803822978E-16, -0.52805602783332639, 4.9539853447560175E-16,
    3.0824160484105736, 1.1359558774354835E-16, -4.5581893533444219E-16 },

  // Variable: Ki
  //  Referenced by:
  //    '<S178>/Gain2'
  //    '<S516>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: Ki_trans
  //  Referenced by:
  //    '<S13>/Gain2'
  //    '<S351>/Gain2'

  { 3.5211595408221149E-16, -1.5925298604027004E-16, -0.14142135623730998,
    -1.3872186704390749E-18, 0.14142135623730942, -1.4801717978270836E-16,
    -2.2360679774997942, -1.5221331261496206E-16, 2.7121351916188709E-16 },

  // Variable: N
  //  Referenced by:
  //    '<S222>/Filter Coefficient'
  //    '<S274>/Filter Coefficient'
  //    '<S326>/Filter Coefficient'
  //    '<S560>/Filter Coefficient'
  //    '<S612>/Filter Coefficient'
  //    '<S664>/Filter Coefficient'

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

  // Variable: V
  //  Referenced by:
  //    '<S178>/Gain1'
  //    '<S516>/Gain1'

  { 1.1628620662077678, -1.2698609834614055E-16, 7.3843539275653766E-17,
    2.1850200759364756E-16, 1.1628620662077689, 1.6188710462632716E-15,
    -3.8317272026029079E-16, -2.876136846988219E-15, 1.0000000000000029 },

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

  9.81,

  // Variable: h
  //  Referenced by: '<S6>/MATLAB Function2'

  0.05,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S264>/Derivative Gain'
  //    '<S602>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S212>/Derivative Gain'
  //    '<S550>/Derivative Gain'

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
  //    '<S316>/Derivative Gain'
  //    '<S654>/Derivative Gain'

  0.5,

  // Variable: kd_z
  //  Referenced by:
  //    '<S148>/Derivative Gain'
  //    '<S486>/Derivative Gain'

  2.0,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S268>/Integral Gain'
  //    '<S606>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S216>/Integral Gain'
  //    '<S554>/Integral Gain'

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
  //    '<S320>/Integral Gain'
  //    '<S658>/Integral Gain'

  0.7,

  // Variable: ki_z
  //  Referenced by:
  //    '<S152>/Integral Gain'
  //    '<S490>/Integral Gain'

  2.5,

  // Variable: m
  //  Referenced by:
  //    '<S4>/MATLAB Function2'
  //    '<S6>/MATLAB Function2'

  1.21,

  // Variable: p
  //  Referenced by: '<S6>/MATLAB Function2'

  { 0.0, 0.0, 0.0 },

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S214>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S266>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S318>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_k
  //  Referenced by: '<S46>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_m
  //  Referenced by: '<S98>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_n
  //  Referenced by: '<S150>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S552>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_a
  //  Referenced by: '<S604>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_c
  //  Referenced by: '<S656>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_m
  //  Referenced by: '<S384>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_ms
  //  Referenced by: '<S436>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_a
  //  Referenced by: '<S488>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_ay
  //  Referenced by: '<S219>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_n
  //  Referenced by: '<S271>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_ng
  //  Referenced by: '<S323>/Integrator'

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

  // Mask Parameter: PIDController_InitialConditio_b
  //  Referenced by: '<S557>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_b
  //  Referenced by: '<S609>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialCondit_k5
  //  Referenced by: '<S661>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditi_a2
  //  Referenced by: '<S389>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialCondit_jr
  //  Referenced by: '<S441>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_i
  //  Referenced by: '<S493>/Integrator'

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

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S342>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S342>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

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

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S343>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S343>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

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

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S344>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S344>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S344>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S174>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S174>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S174>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S174>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S174>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S174>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S174>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S174>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S175>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S175>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S175>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S175>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S175>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S175>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S175>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S175>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S177>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S177>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S177>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S177>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S177>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S177>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S177>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S177>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: -inv(C_trans*inv((A_trans-B_trans*K_trans))* B_trans)
  //  Referenced by: '<S13>/Gain1'

  { -3.4466897622412041E-16, 7.2033734718998059E-16, 0.38672574164509788,
    -7.778369935192485E-16, -0.38672574164509749, 4.45848295193725E-16,
    3.7195407832640646, 2.06289439967498E-16, -5.9892899673442127E-16 },

  // Expression: [m * g; 0; 0]
  //  Referenced by: '<S13>/Constant'

  { 11.8701, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S13>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S178>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S173>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S173>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S12>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S2>/Constant1'

  { 0.0, 0.0 },

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: -inv(C_trans*inv((A_trans-B_trans*K_trans))* B_trans)
  //  Referenced by: '<S351>/Gain1'

  { -3.4466897622412041E-16, 7.2033734718998059E-16, 0.38672574164509788,
    -7.778369935192485E-16, -0.38672574164509749, 4.45848295193725E-16,
    3.7195407832640646, 2.06289439967498E-16, -5.9892899673442127E-16 },

  // Expression: [m * g; 0; 0]
  //  Referenced by: '<S351>/Constant'

  { 11.8701, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S680>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S680>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S680>/Cov Messrauschen'

  0.001,

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S6>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S680>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S680>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S680>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S680>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

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

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S681>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S681>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

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

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S682>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 50]
  //  Referenced by: '<S682>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 50.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S682>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S351>/Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S512>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S512>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S512>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S512>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S512>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S512>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S512>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S512>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S513>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S513>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S513>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S513>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S513>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S513>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S513>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S513>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S515>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S515>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S515>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S515>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S515>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S515>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S515>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S515>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S516>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S511>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S511>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S350>/Integrator'

  0.0,

  // Expression: [0;0]
  //  Referenced by: '<S3>/Constant1'

  { 0.0, 0.0 },

  // Expression: 0
  //  Referenced by: '<S174>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S175>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S177>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S342>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S343>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S344>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S512>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S513>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S515>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S680>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S681>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S682>/Integrator1'

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
