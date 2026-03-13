//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.h
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
#ifndef controller_3dof_container_h_
#define controller_3dof_container_h_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#ifndef ODE1_INTG
#define ODE1_INTG

// ODE1 Integration Data
struct ODE1_IntgData {
  real_T *f[1];                        // derivatives
};

#endif

// Class declaration for model controller_3dof_container
class Controller3dof final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Sum[3];                     // '<S10>/Sum'
    real_T Sum_d[3];                   // '<S179>/Sum'
    real_T x_dach[2];                  // '<S342>/KF_Elevation'
    real_T P_p[4];                     // '<S342>/KF_Elevation'
    real_T x_dach_a[2];                // '<S341>/KF_Elevation'
    real_T P_l[4];                     // '<S341>/KF_Elevation'
    real_T x_dach_o[2];                // '<S340>/KF_Elevation'
    real_T P_g[4];                     // '<S340>/KF_Elevation'
    real_T x_dach_k[2];                // '<S173>/KF_Elevation'
    real_T P_o[4];                     // '<S173>/KF_Elevation'
    real_T x_dach_g[2];                // '<S172>/KF_Elevation'
    real_T P_k[4];                     // '<S172>/KF_Elevation'
    real_T x_dach_e[2];                // '<S171>/KF_Elevation'
    real_T P_j[4];                     // '<S171>/KF_Elevation'
    real_T dx[6];                      // '<S4>/MATLAB Function2'
    real_T UnitDelay1_DSTATE[2];       // '<S171>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S171>/Unit Delay'
    real_T UnitDelay1_DSTATE_p[2];     // '<S172>/Unit Delay1'
    real_T UnitDelay_DSTATE_l[4];      // '<S172>/Unit Delay'
    real_T UnitDelay1_DSTATE_a[2];     // '<S173>/Unit Delay1'
    real_T UnitDelay_DSTATE_i[4];      // '<S173>/Unit Delay'
    real_T UnitDelay1_DSTATE_e[2];     // '<S340>/Unit Delay1'
    real_T UnitDelay_DSTATE_d[4];      // '<S340>/Unit Delay'
    real_T UnitDelay1_DSTATE_j[2];     // '<S341>/Unit Delay1'
    real_T UnitDelay_DSTATE_db[4];     // '<S341>/Unit Delay'
    real_T UnitDelay1_DSTATE_k[2];     // '<S342>/Unit Delay1'
    real_T UnitDelay_DSTATE_k[4];      // '<S342>/Unit Delay'
    real_T FilterCoefficient;          // '<S52>/Filter Coefficient'
    real_T FilterCoefficient_k;        // '<S104>/Filter Coefficient'
    real_T FilterCoefficient_j;        // '<S156>/Filter Coefficient'
    real_T IntegralGain;               // '<S150>/Integral Gain'
    real_T IntegralGain_d;             // '<S98>/Integral Gain'
    real_T IntegralGain_i;             // '<S46>/Integral Gain'
    real_T FilterCoefficient_b;        // '<S221>/Filter Coefficient'
    real_T FilterCoefficient_o;        // '<S273>/Filter Coefficient'
    real_T FilterCoefficient_e;        // '<S325>/Filter Coefficient'
    real_T IntegralGain_p;             // '<S319>/Integral Gain'
    real_T IntegralGain_m;             // '<S267>/Integral Gain'
    real_T IntegralGain_l;             // '<S215>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE[6];       // '<S4>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S49>/Integrator'
    real_T Filter_CSTATE;              // '<S44>/Filter'
    real_T Integrator_CSTATE_c;        // '<S101>/Integrator'
    real_T Filter_CSTATE_i;            // '<S96>/Filter'
    real_T Integrator_CSTATE_o;        // '<S153>/Integrator'
    real_T Filter_CSTATE_n;            // '<S148>/Filter'
    real_T Integrator_CSTATE_l;        // '<S218>/Integrator'
    real_T Filter_CSTATE_g;            // '<S213>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S270>/Integrator'
    real_T Filter_CSTATE_h;            // '<S265>/Filter'
    real_T Integrator_CSTATE_i;        // '<S322>/Integrator'
    real_T Filter_CSTATE_c;            // '<S317>/Filter'
    real_T Integrator_CSTATE_p[3];     // '<S10>/Integrator'
    real_T Integrator_CSTATE_if[3];    // '<S179>/Integrator'
    real_T TransferFcn_CSTATE;         // '<S5>/Transfer Fcn'
    real_T TransferFcn1_CSTATE;        // '<S5>/Transfer Fcn1'
    real_T TransferFcn2_CSTATE;        // '<S5>/Transfer Fcn2'
    real_T TransferFcn3_CSTATE;        // '<S5>/Transfer Fcn3'
    real_T Integrator1_CSTATE;         // '<S171>/Integrator1'
    real_T Integrator1_CSTATE_k;       // '<S172>/Integrator1'
    real_T Integrator1_CSTATE_l;       // '<S173>/Integrator1'
    real_T Integrator1_CSTATE_b;       // '<S340>/Integrator1'
    real_T Integrator1_CSTATE_h;       // '<S341>/Integrator1'
    real_T Integrator1_CSTATE_p;       // '<S342>/Integrator1'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE[6];       // '<S4>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S49>/Integrator'
    real_T Filter_CSTATE;              // '<S44>/Filter'
    real_T Integrator_CSTATE_c;        // '<S101>/Integrator'
    real_T Filter_CSTATE_i;            // '<S96>/Filter'
    real_T Integrator_CSTATE_o;        // '<S153>/Integrator'
    real_T Filter_CSTATE_n;            // '<S148>/Filter'
    real_T Integrator_CSTATE_l;        // '<S218>/Integrator'
    real_T Filter_CSTATE_g;            // '<S213>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S270>/Integrator'
    real_T Filter_CSTATE_h;            // '<S265>/Filter'
    real_T Integrator_CSTATE_i;        // '<S322>/Integrator'
    real_T Filter_CSTATE_c;            // '<S317>/Filter'
    real_T Integrator_CSTATE_p[3];     // '<S10>/Integrator'
    real_T Integrator_CSTATE_if[3];    // '<S179>/Integrator'
    real_T TransferFcn_CSTATE;         // '<S5>/Transfer Fcn'
    real_T TransferFcn1_CSTATE;        // '<S5>/Transfer Fcn1'
    real_T TransferFcn2_CSTATE;        // '<S5>/Transfer Fcn2'
    real_T TransferFcn3_CSTATE;        // '<S5>/Transfer Fcn3'
    real_T Integrator1_CSTATE;         // '<S171>/Integrator1'
    real_T Integrator1_CSTATE_k;       // '<S172>/Integrator1'
    real_T Integrator1_CSTATE_l;       // '<S173>/Integrator1'
    real_T Integrator1_CSTATE_b;       // '<S340>/Integrator1'
    real_T Integrator1_CSTATE_h;       // '<S341>/Integrator1'
    real_T Integrator1_CSTATE_p;       // '<S342>/Integrator1'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE[6];    // '<S4>/Integrator'
    boolean_T Integrator_CSTATE_j;     // '<S49>/Integrator'
    boolean_T Filter_CSTATE;           // '<S44>/Filter'
    boolean_T Integrator_CSTATE_c;     // '<S101>/Integrator'
    boolean_T Filter_CSTATE_i;         // '<S96>/Filter'
    boolean_T Integrator_CSTATE_o;     // '<S153>/Integrator'
    boolean_T Filter_CSTATE_n;         // '<S148>/Filter'
    boolean_T Integrator_CSTATE_l;     // '<S218>/Integrator'
    boolean_T Filter_CSTATE_g;         // '<S213>/Filter'
    boolean_T Integrator_CSTATE_ja;    // '<S270>/Integrator'
    boolean_T Filter_CSTATE_h;         // '<S265>/Filter'
    boolean_T Integrator_CSTATE_i;     // '<S322>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S317>/Filter'
    boolean_T Integrator_CSTATE_p[3];  // '<S10>/Integrator'
    boolean_T Integrator_CSTATE_if[3]; // '<S179>/Integrator'
    boolean_T TransferFcn_CSTATE;      // '<S5>/Transfer Fcn'
    boolean_T TransferFcn1_CSTATE;     // '<S5>/Transfer Fcn1'
    boolean_T TransferFcn2_CSTATE;     // '<S5>/Transfer Fcn2'
    boolean_T TransferFcn3_CSTATE;     // '<S5>/Transfer Fcn3'
    boolean_T Integrator1_CSTATE;      // '<S171>/Integrator1'
    boolean_T Integrator1_CSTATE_k;    // '<S172>/Integrator1'
    boolean_T Integrator1_CSTATE_l;    // '<S173>/Integrator1'
    boolean_T Integrator1_CSTATE_b;    // '<S340>/Integrator1'
    boolean_T Integrator1_CSTATE_h;    // '<S341>/Integrator1'
    boolean_T Integrator1_CSTATE_p;    // '<S342>/Integrator1'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T w[4];                       // '<Root>/w'
    real_T y[3];                       // '<Root>/y'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T throttles[4];               // '<Root>/throttles'
    real_T values[6];                  // '<Root>/values'
    real_T x_pred[6];                  // '<Root>/x_pred'
  };

  // Parameters (default storage)
  struct P {
    real_T B_eff[16];                  // Variable: B_eff
                                          //  Referenced by:
                                          //    '<S5>/B_Eff'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S177>/MATLAB Function'

    real_T J[9];                       // Variable: J
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T N;                          // Variable: N
                                          //  Referenced by:
                                          //    '<S52>/Filter Coefficient'
                                          //    '<S104>/Filter Coefficient'
                                          //    '<S156>/Filter Coefficient'
                                          //    '<S221>/Filter Coefficient'
                                          //    '<S273>/Filter Coefficient'
                                          //    '<S325>/Filter Coefficient'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S5>/MATLAB Function1'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S177>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S5>/MATLAB Function1'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S177>/MATLAB Function'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T h;                          // Variable: h
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T kd_pitch;                   // Variable: kd_pitch
                                          //  Referenced by:
                                          //    '<S94>/Derivative Gain'
                                          //    '<S263>/Derivative Gain'

    real_T kd_roll;                    // Variable: kd_roll
                                          //  Referenced by:
                                          //    '<S42>/Derivative Gain'
                                          //    '<S211>/Derivative Gain'

    real_T kd_yaw;                     // Variable: kd_yaw
                                          //  Referenced by:
                                          //    '<S146>/Derivative Gain'
                                          //    '<S315>/Derivative Gain'

    real_T ki_pitch;                   // Variable: ki_pitch
                                          //  Referenced by:
                                          //    '<S98>/Integral Gain'
                                          //    '<S267>/Integral Gain'

    real_T ki_roll;                    // Variable: ki_roll
                                          //  Referenced by:
                                          //    '<S46>/Integral Gain'
                                          //    '<S215>/Integral Gain'

    real_T ki_yaw;                     // Variable: ki_yaw
                                          //  Referenced by:
                                          //    '<S150>/Integral Gain'
                                          //    '<S319>/Integral Gain'

    real_T kp_pitch;                   // Variable: kp_pitch
                                          //  Referenced by:
                                          //    '<S106>/Proportional Gain'
                                          //    '<S275>/Proportional Gain'

    real_T kp_roll;                    // Variable: kp_roll
                                          //  Referenced by:
                                          //    '<S54>/Proportional Gain'
                                          //    '<S223>/Proportional Gain'

    real_T kp_yaw;                     // Variable: kp_yaw
                                          //  Referenced by:
                                          //    '<S158>/Proportional Gain'
                                          //    '<S327>/Proportional Gain'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S44>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S96>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S148>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S213>/Filter'

    real_T PIDController1_InitialConditi_k;
                              // Mask Parameter: PIDController1_InitialConditi_k
                                 //  Referenced by: '<S265>/Filter'

    real_T PIDController2_InitialConditi_j;
                              // Mask Parameter: PIDController2_InitialConditi_j
                                 //  Referenced by: '<S317>/Filter'

    real_T PIDController_InitialConditio_e;
                              // Mask Parameter: PIDController_InitialConditio_e
                                 //  Referenced by: '<S49>/Integrator'

    real_T PIDController1_InitialConditi_p;
                              // Mask Parameter: PIDController1_InitialConditi_p
                                 //  Referenced by: '<S101>/Integrator'

    real_T PIDController2_InitialConditi_p;
                              // Mask Parameter: PIDController2_InitialConditi_p
                                 //  Referenced by: '<S153>/Integrator'

    real_T PIDController_InitialConditio_a;
                              // Mask Parameter: PIDController_InitialConditio_a
                                 //  Referenced by: '<S218>/Integrator'

    real_T PIDController1_InitialConditi_j;
                              // Mask Parameter: PIDController1_InitialConditi_j
                                 //  Referenced by: '<S270>/Integrator'

    real_T PIDController2_InitialConditi_m;
                              // Mask Parameter: PIDController2_InitialConditi_m
                                 //  Referenced by: '<S322>/Integrator'

    real_T Constant_Value[6];          // Expression: zeros(6, 1)
                                          //  Referenced by: '<S3>/Constant'

    real_T Integrator_IC[6];           // Expression: zeros(6, 1)
                                          //  Referenced by: '<S4>/Integrator'

    real_T Saturation_UpperSat;        // Expression: 0.90
                                          //  Referenced by: '<S8>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0.15
                                          //  Referenced by: '<S8>/Saturation'

    real_T Saturation_UpperSat_l;      // Expression: 0.90
                                          //  Referenced by: '<S177>/Saturation'

    real_T Saturation_LowerSat_d;      // Expression: 0.15
                                          //  Referenced by: '<S177>/Saturation'

    real_T Constant_Value_a[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S171>/Constant'

    real_T Constant1_Value[2];         // Expression: [1; 0]
                                          //  Referenced by: '<S171>/Constant1'

    real_T Constant2_Value[2];         // Expression: [1 0]
                                          //  Referenced by: '<S171>/Constant2'

    real_T Constant5_Value;            // Expression: 0
                                          //  Referenced by: '<S171>/Constant5'

    real_T CovMessrauschen_Value;      // Expression: 10e-6
                                          //  Referenced by: '<S171>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition[2];// Expression: [0; 0]
                                             //  Referenced by: '<S171>/Unit Delay1'

    real_T CovProzessrauschen_Value[4];// Expression: [0.001 0; 0 50]
                                          //  Referenced by: '<S171>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition[4];// Expression: 1 * eye(2, 2)
                                            //  Referenced by: '<S171>/Unit Delay'

    real_T Constant_Value_p[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S172>/Constant'

    real_T Constant1_Value_h[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S172>/Constant1'

    real_T Constant2_Value_a[2];       // Expression: [1 0]
                                          //  Referenced by: '<S172>/Constant2'

    real_T Constant5_Value_f;          // Expression: 0
                                          //  Referenced by: '<S172>/Constant5'

    real_T CovMessrauschen_Value_o;    // Expression: 10e-6
                                          //  Referenced by: '<S172>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition_d[2];// Expression: [0; 0]
                                               //  Referenced by: '<S172>/Unit Delay1'

    real_T CovProzessrauschen_Value_l[4];// Expression: [0.001 0; 0 50]
                                            //  Referenced by: '<S172>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_e[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S172>/Unit Delay'

    real_T Constant_Value_d[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S173>/Constant'

    real_T Constant1_Value_c[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S173>/Constant1'

    real_T Constant2_Value_b[2];       // Expression: [1 0]
                                          //  Referenced by: '<S173>/Constant2'

    real_T Constant5_Value_d;          // Expression: 0
                                          //  Referenced by: '<S173>/Constant5'

    real_T CovMessrauschen_Value_g;    // Expression: 10e-6
                                          //  Referenced by: '<S173>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition_i[2];// Expression: [0; 0]
                                               //  Referenced by: '<S173>/Unit Delay1'

    real_T CovProzessrauschen_Value_a[4];// Expression: [0.001 0; 0 50]
                                            //  Referenced by: '<S173>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_ew[4];// Expression: 1 * eye(2, 2)
                                               //  Referenced by: '<S173>/Unit Delay'

    real_T Constant_Value_p1[4];       // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S340>/Constant'

    real_T Constant1_Value_h4[2];      // Expression: [1; 0]
                                          //  Referenced by: '<S340>/Constant1'

    real_T Constant2_Value_k[2];       // Expression: [1 0]
                                          //  Referenced by: '<S340>/Constant2'

    real_T Constant5_Value_e;          // Expression: 0
                                          //  Referenced by: '<S340>/Constant5'

    real_T CovMessrauschen_Value_m;    // Expression: 10e-6
                                          //  Referenced by: '<S340>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition_h[2];// Expression: [0; 0]
                                               //  Referenced by: '<S340>/Unit Delay1'

    real_T CovProzessrauschen_Value_p[4];// Expression: [0.001 0; 0 50]
                                            //  Referenced by: '<S340>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_j[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S340>/Unit Delay'

    real_T Constant_Value_m[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S341>/Constant'

    real_T Constant1_Value_i[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S341>/Constant1'

    real_T Constant2_Value_l[2];       // Expression: [1 0]
                                          //  Referenced by: '<S341>/Constant2'

    real_T Constant5_Value_k;          // Expression: 0
                                          //  Referenced by: '<S341>/Constant5'

    real_T CovMessrauschen_Value_p;    // Expression: 10e-6
                                          //  Referenced by: '<S341>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition_m[2];// Expression: [0; 0]
                                               //  Referenced by: '<S341>/Unit Delay1'

    real_T CovProzessrauschen_Value_h[4];// Expression: [0.001 0; 0 50]
                                            //  Referenced by: '<S341>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_n[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S341>/Unit Delay'

    real_T Constant_Value_pv[4];       // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S342>/Constant'

    real_T Constant1_Value_b[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S342>/Constant1'

    real_T Constant2_Value_p[2];       // Expression: [1 0]
                                          //  Referenced by: '<S342>/Constant2'

    real_T Constant5_Value_k1;         // Expression: 0
                                          //  Referenced by: '<S342>/Constant5'

    real_T CovMessrauschen_Value_i;    // Expression: 10e-6
                                          //  Referenced by: '<S342>/Cov Messrauschen'

    real_T UnitDelay1_InitialCondition_l[2];// Expression: [0; 0]
                                               //  Referenced by: '<S342>/Unit Delay1'

    real_T CovProzessrauschen_Value_g[4];// Expression: [0.001 0; 0 50]
                                            //  Referenced by: '<S342>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_i[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S342>/Unit Delay'

    real_T Integrator_IC_k;            // Expression: 0
                                          //  Referenced by: '<S10>/Integrator'

    real_T Integrator_IC_f;            // Expression: 0
                                          //  Referenced by: '<S179>/Integrator'

    real_T TransferFcn_A;              // Computed Parameter: TransferFcn_A
                                          //  Referenced by: '<S5>/Transfer Fcn'

    real_T TransferFcn_C;              // Computed Parameter: TransferFcn_C
                                          //  Referenced by: '<S5>/Transfer Fcn'

    real_T TransferFcn1_A;             // Computed Parameter: TransferFcn1_A
                                          //  Referenced by: '<S5>/Transfer Fcn1'

    real_T TransferFcn1_C;             // Computed Parameter: TransferFcn1_C
                                          //  Referenced by: '<S5>/Transfer Fcn1'

    real_T TransferFcn2_A;             // Computed Parameter: TransferFcn2_A
                                          //  Referenced by: '<S5>/Transfer Fcn2'

    real_T TransferFcn2_C;             // Computed Parameter: TransferFcn2_C
                                          //  Referenced by: '<S5>/Transfer Fcn2'

    real_T TransferFcn3_A;             // Computed Parameter: TransferFcn3_A
                                          //  Referenced by: '<S5>/Transfer Fcn3'

    real_T TransferFcn3_C;             // Computed Parameter: TransferFcn3_C
                                          //  Referenced by: '<S5>/Transfer Fcn3'

    real_T Integrator1_IC;             // Expression: 0
                                          //  Referenced by: '<S171>/Integrator1'

    real_T Integrator1_IC_j;           // Expression: 0
                                          //  Referenced by: '<S172>/Integrator1'

    real_T Integrator1_IC_i;           // Expression: 0
                                          //  Referenced by: '<S173>/Integrator1'

    real_T Integrator1_IC_d;           // Expression: 0
                                          //  Referenced by: '<S340>/Integrator1'

    real_T Integrator1_IC_a;           // Expression: 0
                                          //  Referenced by: '<S341>/Integrator1'

    real_T Integrator1_IC_k;           // Expression: 0
                                          //  Referenced by: '<S342>/Integrator1'

    boolean_T Constant_Value_c;        // Expression: true
                                          //  Referenced by: '<S1>/Constant'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[34];
  struct RT_MODEL {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeF[1][34];
    ODE1_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      time_T tStart;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;

    time_T** getTPtrPtr();
    boolean_T getStopRequested() const;
    void setStopRequested(boolean_T aStopRequested);
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const aErrorStatus);
    time_T* getTPtr() const;
    void setTPtr(time_T* aTPtr);
    boolean_T* getStopRequestedPtr();
    const char_T** getErrorStatusPtr();
    boolean_T isMajorTimeStep() const;
    boolean_T isMinorTimeStep() const;
    time_T getTStart() const;
  };

  // Copy Constructor
  Controller3dof(Controller3dof const&) = delete;

  // Assignment Operator
  Controller3dof& operator= (Controller3dof const&) & = delete;

  // Move Constructor
  Controller3dof(Controller3dof &&) = delete;

  // Move Assignment Operator
  Controller3dof& operator= (Controller3dof &&) = delete;

  // Real-Time Model get method
  Controller3dof::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // Tunable parameters
  static P rtP;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  Controller3dof();

  // Destructor
  ~Controller3dof();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Block continuous states
  X rtX;

  // Block Continuous state disabled vector
  XDis rtXDis;

  // private member function(s) for subsystem '<S171>/KF_Elevation'
  static void KF_Elevation(const real_T rtu_A[4], const real_T rtu_B[2], const
    real_T rtu_C[2], const real_T rtu_Q[4], real_T rtu_R, real_T rtu_y, real_T
    rtu_u, const real_T rtu_Pold[4], real_T rty_x_dach[2], real_T rty_P[4]);

  // Global mass matrix

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void controller_3dof_container_derivatives();

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/Constant' : Unused code path elimination
//  Block '<S2>/Scope' : Unused code path elimination
//  Block '<S8>/Scope' : Unused code path elimination
//  Block '<S8>/Scope1' : Unused code path elimination
//  Block '<S10>/Gain' : Unused code path elimination
//  Block '<S10>/Gain1' : Unused code path elimination
//  Block '<S10>/Gain2' : Unused code path elimination
//  Block '<S171>/Scope' : Unused code path elimination
//  Block '<S172>/Scope' : Unused code path elimination
//  Block '<S173>/Scope' : Unused code path elimination
//  Block '<S10>/Sum2' : Unused code path elimination
//  Block '<S3>/Scope' : Unused code path elimination
//  Block '<S177>/Scope' : Unused code path elimination
//  Block '<S177>/Scope1' : Unused code path elimination
//  Block '<S179>/Gain' : Unused code path elimination
//  Block '<S179>/Gain1' : Unused code path elimination
//  Block '<S179>/Gain2' : Unused code path elimination
//  Block '<S340>/Scope' : Unused code path elimination
//  Block '<S341>/Scope' : Unused code path elimination
//  Block '<S342>/Scope' : Unused code path elimination
//  Block '<S179>/Sum2' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'controller_3dof_container'
//  '<S1>'   : 'controller_3dof_container/Subsystem Reference'
//  '<S2>'   : 'controller_3dof_container/Subsystem1'
//  '<S3>'   : 'controller_3dof_container/Subsystem7'
//  '<S4>'   : 'controller_3dof_container/Subsystem Reference/Subsystem'
//  '<S5>'   : 'controller_3dof_container/Subsystem Reference/Subsystem1'
//  '<S6>'   : 'controller_3dof_container/Subsystem Reference/Subsystem/MATLAB Function2'
//  '<S7>'   : 'controller_3dof_container/Subsystem Reference/Subsystem1/MATLAB Function1'
//  '<S8>'   : 'controller_3dof_container/Subsystem1/Subsystem'
//  '<S9>'   : 'controller_3dof_container/Subsystem1/Subsystem3'
//  '<S10>'  : 'controller_3dof_container/Subsystem1/Subsystem6'
//  '<S11>'  : 'controller_3dof_container/Subsystem1/Subsystem/MATLAB Function'
//  '<S12>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller'
//  '<S13>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1'
//  '<S14>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2'
//  '<S15>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup'
//  '<S16>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain'
//  '<S17>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative'
//  '<S18>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter'
//  '<S19>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs'
//  '<S20>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain'
//  '<S21>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain'
//  '<S22>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S23>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator'
//  '<S24>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs'
//  '<S25>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy'
//  '<S26>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain'
//  '<S27>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy'
//  '<S28>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain'
//  '<S29>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal'
//  '<S30>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation'
//  '<S31>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S32>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum'
//  '<S33>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk'
//  '<S34>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode'
//  '<S35>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S36>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S37>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S38>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal'
//  '<S39>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal'
//  '<S40>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal'
//  '<S41>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S42>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S43>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative/Error'
//  '<S44>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter/Cont. Filter'
//  '<S45>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S46>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S47>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S48>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S49>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S50>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S51>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S52>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S53>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S54>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S55>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S56>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S57>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S58>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S59>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S60>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S61>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S62>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S63>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S64>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S65>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S66>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S67>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup'
//  '<S68>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain'
//  '<S69>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative'
//  '<S70>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter'
//  '<S71>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs'
//  '<S72>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain'
//  '<S73>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S74>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S75>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator'
//  '<S76>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs'
//  '<S77>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy'
//  '<S78>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain'
//  '<S79>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy'
//  '<S80>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S81>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal'
//  '<S82>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation'
//  '<S83>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S84>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum'
//  '<S85>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S86>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode'
//  '<S87>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S88>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S89>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S90>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal'
//  '<S91>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal'
//  '<S92>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal'
//  '<S93>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S94>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S95>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative/Error'
//  '<S96>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter/Cont. Filter'
//  '<S97>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S98>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S99>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S100>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S101>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S102>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S103>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S104>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S105>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S106>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S107>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S108>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S109>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S110>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S111>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S112>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S113>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S114>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S115>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S116>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S117>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S118>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S119>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup'
//  '<S120>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain'
//  '<S121>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative'
//  '<S122>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter'
//  '<S123>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs'
//  '<S124>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain'
//  '<S125>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S126>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S127>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator'
//  '<S128>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs'
//  '<S129>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy'
//  '<S130>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain'
//  '<S131>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy'
//  '<S132>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S133>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal'
//  '<S134>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation'
//  '<S135>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S136>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum'
//  '<S137>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S138>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode'
//  '<S139>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S140>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S141>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S142>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal'
//  '<S143>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal'
//  '<S144>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal'
//  '<S145>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S146>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S147>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative/Error'
//  '<S148>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter/Cont. Filter'
//  '<S149>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S150>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S151>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S152>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S153>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S154>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S155>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S156>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S157>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S158>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S159>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S160>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S161>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S162>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S163>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S164>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S165>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S166>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S167>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S168>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S169>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S170>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S171>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem1'
//  '<S172>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem2'
//  '<S173>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem4'
//  '<S174>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem1/KF_Elevation'
//  '<S175>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem2/KF_Elevation'
//  '<S176>' : 'controller_3dof_container/Subsystem1/Subsystem6/Subsystem4/KF_Elevation'
//  '<S177>' : 'controller_3dof_container/Subsystem7/Subsystem'
//  '<S178>' : 'controller_3dof_container/Subsystem7/Subsystem3'
//  '<S179>' : 'controller_3dof_container/Subsystem7/Subsystem6'
//  '<S180>' : 'controller_3dof_container/Subsystem7/Subsystem/MATLAB Function'
//  '<S181>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller'
//  '<S182>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1'
//  '<S183>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2'
//  '<S184>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Anti-windup'
//  '<S185>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/D Gain'
//  '<S186>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/External Derivative'
//  '<S187>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter'
//  '<S188>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter ICs'
//  '<S189>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/I Gain'
//  '<S190>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain'
//  '<S191>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S192>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator'
//  '<S193>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator ICs'
//  '<S194>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Copy'
//  '<S195>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Gain'
//  '<S196>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/P Copy'
//  '<S197>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Parallel P Gain'
//  '<S198>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Reset Signal'
//  '<S199>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation'
//  '<S200>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S201>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum'
//  '<S202>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum Fdbk'
//  '<S203>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode'
//  '<S204>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S205>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S206>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S207>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/postSat Signal'
//  '<S208>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preInt Signal'
//  '<S209>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preSat Signal'
//  '<S210>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S211>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S212>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/External Derivative/Error'
//  '<S213>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter/Cont. Filter'
//  '<S214>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S215>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S216>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S217>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S218>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S219>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S220>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S221>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S222>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S223>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S224>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S225>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S226>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S227>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S228>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S229>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S230>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S231>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S232>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S233>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S234>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S235>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S236>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Anti-windup'
//  '<S237>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/D Gain'
//  '<S238>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/External Derivative'
//  '<S239>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter'
//  '<S240>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter ICs'
//  '<S241>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/I Gain'
//  '<S242>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S243>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S244>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator'
//  '<S245>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator ICs'
//  '<S246>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Copy'
//  '<S247>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Gain'
//  '<S248>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/P Copy'
//  '<S249>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S250>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Reset Signal'
//  '<S251>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation'
//  '<S252>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S253>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum'
//  '<S254>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S255>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode'
//  '<S256>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S257>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S258>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S259>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/postSat Signal'
//  '<S260>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preInt Signal'
//  '<S261>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preSat Signal'
//  '<S262>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S263>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S264>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/External Derivative/Error'
//  '<S265>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter/Cont. Filter'
//  '<S266>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S267>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S268>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S269>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S270>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S271>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S272>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S273>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S274>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S275>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S276>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S277>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S278>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S279>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S280>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S281>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S282>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S283>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S284>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S285>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S286>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S287>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S288>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Anti-windup'
//  '<S289>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/D Gain'
//  '<S290>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/External Derivative'
//  '<S291>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter'
//  '<S292>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter ICs'
//  '<S293>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/I Gain'
//  '<S294>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S295>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S296>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator'
//  '<S297>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator ICs'
//  '<S298>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Copy'
//  '<S299>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Gain'
//  '<S300>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/P Copy'
//  '<S301>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S302>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Reset Signal'
//  '<S303>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation'
//  '<S304>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S305>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum'
//  '<S306>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S307>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode'
//  '<S308>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S309>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S310>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S311>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/postSat Signal'
//  '<S312>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preInt Signal'
//  '<S313>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preSat Signal'
//  '<S314>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S315>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S316>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/External Derivative/Error'
//  '<S317>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter/Cont. Filter'
//  '<S318>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S319>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S320>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S321>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S322>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S323>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S324>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S325>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S326>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S327>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S328>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S329>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S330>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S331>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S332>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S333>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S334>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S335>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S336>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S337>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S338>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S339>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S340>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem1'
//  '<S341>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem2'
//  '<S342>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem4'
//  '<S343>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem1/KF_Elevation'
//  '<S344>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem2/KF_Elevation'
//  '<S345>' : 'controller_3dof_container/Subsystem7/Subsystem6/Subsystem4/KF_Elevation'

#endif                                 // controller_3dof_container_h_

//
// File trailer for generated code.
//
// [EOF]
//
