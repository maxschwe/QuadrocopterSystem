//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container_data.cpp
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

// Block parameters (default storage)
Controller3dof::P Controller3dof::rtP{
  // Variable: B_eff
  //  Referenced by:
  //    '<S5>/B_Eff'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  { 1.0, 0.2, 0.0, 0.0351, 1.0, 0.0, 0.2, -0.0351, 1.0, -0.2, 0.0, 0.0351, 1.0,
    0.0, -0.2, -0.0351 },

  // Variable: J
  //  Referenced by: '<S4>/MATLAB Function2'

  { 0.0258, 0.0, 0.0, 0.0, 0.0268, 0.0, 0.0, 0.0, 0.068 },

  // Variable: K
  //  Referenced by:
  //    '<S13>/Gain'
  //    '<S182>/Gain'

  { 1.6142259582794287, 1.2711870143100486E-15, 5.36115150372202E-16,
    9.1084845953510463E-16, 1.6142259582794254, -1.1979866809554318E-16,
    -1.2195293884720441E-16, -3.9067046768301071E-16, 1.0000000000000002,
    0.30544076258289282, 3.2400802708150655E-16, -6.363238227525555E-17,
    -4.6860780500689764E-16, 0.3106807225493351, 5.71499884074483E-17,
    2.9516739831244427E-17, 1.8317276333373346E-17, 0.38209946349085644 },

  // Variable: Ki
  //  Referenced by:
  //    '<S13>/Gain2'
  //    '<S182>/Gain2'

  { 1.0, 1.0, 1.0 },

  // Variable: N
  //  Referenced by:
  //    '<S57>/Filter Coefficient'
  //    '<S109>/Filter Coefficient'
  //    '<S161>/Filter Coefficient'
  //    '<S226>/Filter Coefficient'
  //    '<S278>/Filter Coefficient'
  //    '<S330>/Filter Coefficient'

  100.0,

  // Variable: V
  //  Referenced by:
  //    '<S13>/Gain1'
  //    '<S182>/Gain1'

  { 1.1168589582794288, 1.2711870143100484E-15, 5.3611515037220214E-16,
    9.1084845953510463E-16, 1.1168589582794253, -1.1979866809554321E-16,
    -1.2195293884720443E-16, -3.9067046768301076E-16, 1.0000000000000002 },

  // Variable: a
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  13.06,

  // Variable: b
  //  Referenced by:
  //    '<S5>/MATLAB Function1'
  //    '<S8>/MATLAB Function'
  //    '<S177>/MATLAB Function'

  0.0859,

  // Variable: g
  //  Referenced by: '<S4>/MATLAB Function2'

  9.81,

  // Variable: h
  //  Referenced by: '<S4>/MATLAB Function2'

  0.05,

  // Variable: kd_pitch
  //  Referenced by:
  //    '<S99>/Derivative Gain'
  //    '<S268>/Derivative Gain'

  0.35,

  // Variable: kd_roll
  //  Referenced by:
  //    '<S47>/Derivative Gain'
  //    '<S216>/Derivative Gain'

  0.33,

  // Variable: kd_yaw
  //  Referenced by:
  //    '<S151>/Derivative Gain'
  //    '<S320>/Derivative Gain'

  0.5,

  // Variable: ki_pitch
  //  Referenced by:
  //    '<S103>/Integral Gain'
  //    '<S272>/Integral Gain'

  1.21,

  // Variable: ki_roll
  //  Referenced by:
  //    '<S51>/Integral Gain'
  //    '<S220>/Integral Gain'

  1.18,

  // Variable: ki_yaw
  //  Referenced by:
  //    '<S155>/Integral Gain'
  //    '<S324>/Integral Gain'

  0.7,

  // Variable: m
  //  Referenced by: '<S4>/MATLAB Function2'

  1.014,

  // Variable: p
  //  Referenced by: '<S4>/MATLAB Function2'

  { 0.0, 0.0, 0.0 },

  // Mask Parameter: PIDController_InitialConditionF
  //  Referenced by: '<S49>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialCondition
  //  Referenced by: '<S101>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialCondition
  //  Referenced by: '<S153>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_c
  //  Referenced by: '<S218>/Filter'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_k
  //  Referenced by: '<S270>/Filter'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_j
  //  Referenced by: '<S322>/Filter'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_e
  //  Referenced by: '<S54>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_p
  //  Referenced by: '<S106>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_p
  //  Referenced by: '<S158>/Integrator'

  0.0,

  // Mask Parameter: PIDController_InitialConditio_a
  //  Referenced by: '<S223>/Integrator'

  0.0,

  // Mask Parameter: PIDController1_InitialConditi_j
  //  Referenced by: '<S275>/Integrator'

  0.0,

  // Mask Parameter: PIDController2_InitialConditi_m
  //  Referenced by: '<S327>/Integrator'

  0.0,

  // Expression: [1; 0]
  //  Referenced by: '<S178>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S178>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S178>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S178>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S178>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S178>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S178>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S178>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S179>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S179>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S179>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S179>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S179>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S179>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S179>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S179>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S181>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S181>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S181>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S181>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S181>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S181>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S181>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S181>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S182>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S177>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S177>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S3>/Integrator'

  0.0,

  // Expression: [0; 0; 0; 0; 0; 0]
  //  Referenced by: '<S4>/Integrator'

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S9>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S9>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S9>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S9>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S9>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S9>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S9>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S9>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S10>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S10>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S10>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S10>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S10>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S10>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S10>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S10>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: [1; 0]
  //  Referenced by: '<S12>/Constant1'

  { 1.0, 0.0 },

  // Expression: [1 0]
  //  Referenced by: '<S12>/Constant2'

  { 1.0, 0.0 },

  // Expression: 10e-4
  //  Referenced by: '<S12>/Cov Messrauschen'

  0.001,

  // Expression: 0
  //  Referenced by: '<S12>/Constant5'

  0.0,

  // Expression: [0; 0]
  //  Referenced by: '<S12>/Unit Delay1'

  { 0.0, 0.0 },

  // Expression: [1 0.005; 0 1]
  //  Referenced by: '<S12>/Constant'

  { 1.0, 0.0, 0.005, 1.0 },

  // Expression: [0.001 0; 0 800]
  //  Referenced by: '<S12>/Cov Prozessrauschen'

  { 0.001, 0.0, 0.0, 800.0 },

  // Expression: 1 * eye(2, 2)
  //  Referenced by: '<S12>/Unit Delay'

  { 1.0, 0.0, 0.0, 1.0 },

  // Expression: 0
  //  Referenced by: '<S13>/Integrator'

  0.0,

  // Expression: 0.90
  //  Referenced by: '<S8>/Saturation'

  0.9,

  // Expression: 0.15
  //  Referenced by: '<S8>/Saturation'

  0.15,

  // Expression: 0
  //  Referenced by: '<S2>/Integrator'

  0.0,

  // Expression: 0
  //  Referenced by: '<S9>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S10>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S12>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S178>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S179>/Integrator1'

  0.0,

  // Expression: 0
  //  Referenced by: '<S181>/Integrator1'

  0.0,

  // Expression: true
  //  Referenced by: '<S1>/Constant'

  true
};

//
// File trailer for generated code.
//
// [EOF]
//
