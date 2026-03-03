//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.h
//
// Code generated for Simulink model 'controller_3dof_container'.
//
// Model version                  : 1.466
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Mar  3 13:28:30 2026
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
class Controller final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T TmpSignalConversionAtIntegrator[3];
    real_T Sum[3];                     // '<S11>/Sum'
    real_T Sum_d[3];                   // '<S180>/Sum'
    real_T TmpSignalConversionAtIntegrat_p[3];
    real_T x_dach[2];                  // '<S179>/KF_Elevation'
    real_T P_h[4];                     // '<S179>/KF_Elevation'
    real_T x_dach_n[2];                // '<S177>/KF_Elevation'
    real_T P_d[4];                     // '<S177>/KF_Elevation'
    real_T x_dach_g[2];                // '<S176>/KF_Elevation'
    real_T P_n[4];                     // '<S176>/KF_Elevation'
    real_T x_dach_a[2];                // '<S10>/KF_Elevation'
    real_T P_j[4];                     // '<S10>/KF_Elevation'
    real_T x_dach_j[2];                // '<S8>/KF_Elevation'
    real_T P_nu[4];                    // '<S8>/KF_Elevation'
    real_T x_dach_d[2];                // '<S7>/KF_Elevation'
    real_T P_dr[4];                    // '<S7>/KF_Elevation'
    real_T dx[6];                      // '<S1>/MATLAB Function2'
    real_T UnitDelay1_DSTATE[2];       // '<S7>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S7>/Unit Delay'
    real_T UnitDelay1_DSTATE_f[2];     // '<S8>/Unit Delay1'
    real_T UnitDelay_DSTATE_i[4];      // '<S8>/Unit Delay'
    real_T UnitDelay1_DSTATE_a[2];     // '<S10>/Unit Delay1'
    real_T UnitDelay_DSTATE_d[4];      // '<S10>/Unit Delay'
    real_T UnitDelay1_DSTATE_b[2];     // '<S176>/Unit Delay1'
    real_T UnitDelay_DSTATE_o[4];      // '<S176>/Unit Delay'
    real_T UnitDelay1_DSTATE_b4[2];    // '<S177>/Unit Delay1'
    real_T UnitDelay_DSTATE_g[4];      // '<S177>/Unit Delay'
    real_T UnitDelay1_DSTATE_n[2];     // '<S179>/Unit Delay1'
    real_T UnitDelay_DSTATE_f[4];      // '<S179>/Unit Delay'
    real_T SumD;                       // '<S151>/SumD'
    real_T IntegralGain;               // '<S153>/Integral Gain'
    real_T SumD_k;                     // '<S99>/SumD'
    real_T IntegralGain_d;             // '<S101>/Integral Gain'
    real_T SumD_p;                     // '<S47>/SumD'
    real_T IntegralGain_i;             // '<S49>/Integral Gain'
    real_T SumD_kz;                    // '<S320>/SumD'
    real_T IntegralGain_p;             // '<S322>/Integral Gain'
    real_T SumD_kb;                    // '<S268>/SumD'
    real_T IntegralGain_m;             // '<S270>/Integral Gain'
    real_T SumD_e;                     // '<S216>/SumD'
    real_T IntegralGain_l;             // '<S218>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S52>/Integrator'
    real_T Filter_CSTATE;              // '<S47>/Filter'
    real_T Integrator_CSTATE_c;        // '<S104>/Integrator'
    real_T Filter_CSTATE_e;            // '<S99>/Filter'
    real_T Integrator_CSTATE_o;        // '<S156>/Integrator'
    real_T Filter_CSTATE_j;            // '<S151>/Filter'
    real_T Integrator_CSTATE_b[3];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_p[3];     // '<S11>/Integrator'
    real_T Integrator_CSTATE_i[3];     // '<S180>/Integrator'
    real_T Integrator_CSTATE_l;        // '<S221>/Integrator'
    real_T Filter_CSTATE_n;            // '<S216>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S273>/Integrator'
    real_T Filter_CSTATE_i;            // '<S268>/Filter'
    real_T Integrator_CSTATE_iq;       // '<S325>/Integrator'
    real_T Filter_CSTATE_c;            // '<S320>/Filter'
    real_T Integrator_CSTATE_f[3];     // '<S3>/Integrator'
    real_T Integrator1_CSTATE;         // '<S7>/Integrator1'
    real_T TransferFcn1_CSTATE;        // '<S7>/Transfer Fcn1'
    real_T Integrator1_CSTATE_i;       // '<S8>/Integrator1'
    real_T TransferFcn1_CSTATE_a;      // '<S8>/Transfer Fcn1'
    real_T Integrator1_CSTATE_k;       // '<S10>/Integrator1'
    real_T TransferFcn1_CSTATE_c;      // '<S10>/Transfer Fcn1'
    real_T Integrator1_CSTATE_a;       // '<S176>/Integrator1'
    real_T TransferFcn1_CSTATE_o;      // '<S176>/Transfer Fcn1'
    real_T Integrator1_CSTATE_p;       // '<S177>/Integrator1'
    real_T TransferFcn1_CSTATE_k;      // '<S177>/Transfer Fcn1'
    real_T Integrator1_CSTATE_km;      // '<S179>/Integrator1'
    real_T TransferFcn1_CSTATE_e;      // '<S179>/Transfer Fcn1'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S52>/Integrator'
    real_T Filter_CSTATE;              // '<S47>/Filter'
    real_T Integrator_CSTATE_c;        // '<S104>/Integrator'
    real_T Filter_CSTATE_e;            // '<S99>/Filter'
    real_T Integrator_CSTATE_o;        // '<S156>/Integrator'
    real_T Filter_CSTATE_j;            // '<S151>/Filter'
    real_T Integrator_CSTATE_b[3];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_p[3];     // '<S11>/Integrator'
    real_T Integrator_CSTATE_i[3];     // '<S180>/Integrator'
    real_T Integrator_CSTATE_l;        // '<S221>/Integrator'
    real_T Filter_CSTATE_n;            // '<S216>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S273>/Integrator'
    real_T Filter_CSTATE_i;            // '<S268>/Filter'
    real_T Integrator_CSTATE_iq;       // '<S325>/Integrator'
    real_T Filter_CSTATE_c;            // '<S320>/Filter'
    real_T Integrator_CSTATE_f[3];     // '<S3>/Integrator'
    real_T Integrator1_CSTATE;         // '<S7>/Integrator1'
    real_T TransferFcn1_CSTATE;        // '<S7>/Transfer Fcn1'
    real_T Integrator1_CSTATE_i;       // '<S8>/Integrator1'
    real_T TransferFcn1_CSTATE_a;      // '<S8>/Transfer Fcn1'
    real_T Integrator1_CSTATE_k;       // '<S10>/Integrator1'
    real_T TransferFcn1_CSTATE_c;      // '<S10>/Transfer Fcn1'
    real_T Integrator1_CSTATE_a;       // '<S176>/Integrator1'
    real_T TransferFcn1_CSTATE_o;      // '<S176>/Transfer Fcn1'
    real_T Integrator1_CSTATE_p;       // '<S177>/Integrator1'
    real_T TransferFcn1_CSTATE_k;      // '<S177>/Transfer Fcn1'
    real_T Integrator1_CSTATE_km;      // '<S179>/Integrator1'
    real_T TransferFcn1_CSTATE_e;      // '<S179>/Transfer Fcn1'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE[6];    // '<S1>/Integrator'
    boolean_T Integrator_CSTATE_j;     // '<S52>/Integrator'
    boolean_T Filter_CSTATE;           // '<S47>/Filter'
    boolean_T Integrator_CSTATE_c;     // '<S104>/Integrator'
    boolean_T Filter_CSTATE_e;         // '<S99>/Filter'
    boolean_T Integrator_CSTATE_o;     // '<S156>/Integrator'
    boolean_T Filter_CSTATE_j;         // '<S151>/Filter'
    boolean_T Integrator_CSTATE_b[3];  // '<S2>/Integrator'
    boolean_T Integrator_CSTATE_p[3];  // '<S11>/Integrator'
    boolean_T Integrator_CSTATE_i[3];  // '<S180>/Integrator'
    boolean_T Integrator_CSTATE_l;     // '<S221>/Integrator'
    boolean_T Filter_CSTATE_n;         // '<S216>/Filter'
    boolean_T Integrator_CSTATE_ja;    // '<S273>/Integrator'
    boolean_T Filter_CSTATE_i;         // '<S268>/Filter'
    boolean_T Integrator_CSTATE_iq;    // '<S325>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S320>/Filter'
    boolean_T Integrator_CSTATE_f[3];  // '<S3>/Integrator'
    boolean_T Integrator1_CSTATE;      // '<S7>/Integrator1'
    boolean_T TransferFcn1_CSTATE;     // '<S7>/Transfer Fcn1'
    boolean_T Integrator1_CSTATE_i;    // '<S8>/Integrator1'
    boolean_T TransferFcn1_CSTATE_a;   // '<S8>/Transfer Fcn1'
    boolean_T Integrator1_CSTATE_k;    // '<S10>/Integrator1'
    boolean_T TransferFcn1_CSTATE_c;   // '<S10>/Transfer Fcn1'
    boolean_T Integrator1_CSTATE_a;    // '<S176>/Integrator1'
    boolean_T TransferFcn1_CSTATE_o;   // '<S176>/Transfer Fcn1'
    boolean_T Integrator1_CSTATE_p;    // '<S177>/Integrator1'
    boolean_T TransferFcn1_CSTATE_k;   // '<S177>/Transfer Fcn1'
    boolean_T Integrator1_CSTATE_km;   // '<S179>/Integrator1'
    boolean_T TransferFcn1_CSTATE_e;   // '<S179>/Transfer Fcn1'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T w[4];                       // '<Root>/w'
    real_T y[3];                       // '<Root>/y'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u[4];                       // '<Root>/u'
    real_T values[6];                  // '<Root>/values'
    real_T x_pred[6];                  // '<Root>/x_pred'
  };

  // Parameters (default storage)
  struct P {
    real_T E[16];                      // Variable: E
                                          //  Referenced by:
                                          //    '<S1>/Mixer'
                                          //    '<S6>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T I[9];                       // Variable: I
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T K[18];                      // Variable: K
                                          //  Referenced by:
                                          //    '<S11>/Gain'
                                          //    '<S180>/Gain'

    real_T Ki[3];                      // Variable: Ki
                                          //  Referenced by:
                                          //    '<S11>/Gain2'
                                          //    '<S180>/Gain2'

    real_T V[9];                       // Variable: V
                                          //  Referenced by:
                                          //    '<S11>/Gain1'
                                          //    '<S180>/Gain1'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S6>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S6>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T d;                          // Variable: d
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T kd_pitch;                   // Variable: kd_pitch
                                          //  Referenced by:
                                          //    '<S97>/Derivative Gain'
                                          //    '<S266>/Derivative Gain'

    real_T kd_roll;                    // Variable: kd_roll
                                          //  Referenced by:
                                          //    '<S45>/Derivative Gain'
                                          //    '<S214>/Derivative Gain'

    real_T kd_yaw;                     // Variable: kd_yaw
                                          //  Referenced by:
                                          //    '<S149>/Derivative Gain'
                                          //    '<S318>/Derivative Gain'

    real_T ke;                         // Variable: ke
                                          //  Referenced by:
                                          //    '<S55>/Filter Coefficient'
                                          //    '<S107>/Filter Coefficient'
                                          //    '<S159>/Filter Coefficient'
                                          //    '<S224>/Filter Coefficient'
                                          //    '<S276>/Filter Coefficient'
                                          //    '<S328>/Filter Coefficient'

    real_T ki_pitch;                   // Variable: ki_pitch
                                          //  Referenced by:
                                          //    '<S101>/Integral Gain'
                                          //    '<S270>/Integral Gain'

    real_T ki_roll;                    // Variable: ki_roll
                                          //  Referenced by:
                                          //    '<S49>/Integral Gain'
                                          //    '<S218>/Integral Gain'

    real_T ki_yaw;                     // Variable: ki_yaw
                                          //  Referenced by:
                                          //    '<S153>/Integral Gain'
                                          //    '<S322>/Integral Gain'

    real_T kp_pitch;                   // Variable: kp_pitch
                                          //  Referenced by:
                                          //    '<S109>/Proportional Gain'
                                          //    '<S278>/Proportional Gain'

    real_T kp_roll;                    // Variable: kp_roll
                                          //  Referenced by:
                                          //    '<S57>/Proportional Gain'
                                          //    '<S226>/Proportional Gain'

    real_T kp_yaw;                     // Variable: kp_yaw
                                          //  Referenced by:
                                          //    '<S161>/Proportional Gain'
                                          //    '<S330>/Proportional Gain'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T p;                          // Variable: p
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S47>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S99>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S151>/Filter'

    real_T PIDController_InitialConditio_c;
                              // Mask Parameter: PIDController_InitialConditio_c
                                 //  Referenced by: '<S216>/Filter'

    real_T PIDController1_InitialConditi_k;
                              // Mask Parameter: PIDController1_InitialConditi_k
                                 //  Referenced by: '<S268>/Filter'

    real_T PIDController2_InitialConditi_j;
                              // Mask Parameter: PIDController2_InitialConditi_j
                                 //  Referenced by: '<S320>/Filter'

    real_T PIDController_InitialConditio_e;
                              // Mask Parameter: PIDController_InitialConditio_e
                                 //  Referenced by: '<S52>/Integrator'

    real_T PIDController1_InitialConditi_p;
                              // Mask Parameter: PIDController1_InitialConditi_p
                                 //  Referenced by: '<S104>/Integrator'

    real_T PIDController2_InitialConditi_p;
                              // Mask Parameter: PIDController2_InitialConditi_p
                                 //  Referenced by: '<S156>/Integrator'

    real_T PIDController_InitialConditio_a;
                              // Mask Parameter: PIDController_InitialConditio_a
                                 //  Referenced by: '<S221>/Integrator'

    real_T PIDController1_InitialConditi_j;
                              // Mask Parameter: PIDController1_InitialConditi_j
                                 //  Referenced by: '<S273>/Integrator'

    real_T PIDController2_InitialConditi_m;
                              // Mask Parameter: PIDController2_InitialConditi_m
                                 //  Referenced by: '<S325>/Integrator'

    real_T Integrator_IC[6];           // Expression: [0; 0; 0; 0; 0; 0]
                                          //  Referenced by: '<S1>/Integrator'

    real_T Constant1_Value[2];         // Expression: [1; 0]
                                          //  Referenced by: '<S7>/Constant1'

    real_T Constant2_Value[2];         // Expression: [1 0]
                                          //  Referenced by: '<S7>/Constant2'

    real_T CovMessrauschen_Value;      // Expression: 10e-4
                                          //  Referenced by: '<S7>/Cov Messrauschen'

    real_T Constant5_Value;            // Expression: 0
                                          //  Referenced by: '<S7>/Constant5'

    real_T UnitDelay1_InitialCondition[2];// Expression: [0; 0]
                                             //  Referenced by: '<S7>/Unit Delay1'

    real_T Constant_Value[4];          // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S7>/Constant'

    real_T CovProzessrauschen_Value[4];// Expression: [0.001 0; 0 800]
                                          //  Referenced by: '<S7>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition[4];// Expression: 1 * eye(2, 2)
                                            //  Referenced by: '<S7>/Unit Delay'

    real_T Constant1_Value_m[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S8>/Constant1'

    real_T Constant2_Value_a[2];       // Expression: [1 0]
                                          //  Referenced by: '<S8>/Constant2'

    real_T CovMessrauschen_Value_e;    // Expression: 10e-4
                                          //  Referenced by: '<S8>/Cov Messrauschen'

    real_T Constant5_Value_i;          // Expression: 0
                                          //  Referenced by: '<S8>/Constant5'

    real_T UnitDelay1_InitialCondition_f[2];// Expression: [0; 0]
                                               //  Referenced by: '<S8>/Unit Delay1'

    real_T Constant_Value_j[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S8>/Constant'

    real_T CovProzessrauschen_Value_o[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S8>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_d[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S8>/Unit Delay'

    real_T Constant1_Value_i[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S10>/Constant1'

    real_T Constant2_Value_p[2];       // Expression: [1 0]
                                          //  Referenced by: '<S10>/Constant2'

    real_T CovMessrauschen_Value_f;    // Expression: 10e-4
                                          //  Referenced by: '<S10>/Cov Messrauschen'

    real_T Constant5_Value_k;          // Expression: 0
                                          //  Referenced by: '<S10>/Constant5'

    real_T UnitDelay1_InitialCondition_m[2];// Expression: [0; 0]
                                               //  Referenced by: '<S10>/Unit Delay1'

    real_T Constant_Value_a[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S10>/Constant'

    real_T CovProzessrauschen_Value_h[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S10>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_e[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S10>/Unit Delay'

    real_T Saturation_UpperSat;        // Expression: 0.90
                                          //  Referenced by: '<S6>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0.15
                                          //  Referenced by: '<S6>/Saturation'

    real_T Integrator_IC_c;            // Expression: 0
                                          //  Referenced by: '<S2>/Integrator'

    real_T Integrator_IC_k;            // Expression: 0
                                          //  Referenced by: '<S11>/Integrator'

    real_T Integrator_IC_f;            // Expression: 0
                                          //  Referenced by: '<S180>/Integrator'

    real_T Constant_Value_f[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S176>/Constant'

    real_T Constant1_Value_p[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S176>/Constant1'

    real_T Constant2_Value_b[2];       // Expression: [1 0]
                                          //  Referenced by: '<S176>/Constant2'

    real_T CovMessrauschen_Value_j;    // Expression: 10e-4
                                          //  Referenced by: '<S176>/Cov Messrauschen'

    real_T Constant5_Value_d;          // Expression: 0
                                          //  Referenced by: '<S176>/Constant5'

    real_T UnitDelay1_InitialCondition_b[2];// Expression: [0; 0]
                                               //  Referenced by: '<S176>/Unit Delay1'

    real_T CovProzessrauschen_Value_h3[4];// Expression: [0.001 0; 0 800]
                                             //  Referenced by: '<S176>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_o[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S176>/Unit Delay'

    real_T Constant_Value_i[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S177>/Constant'

    real_T Constant1_Value_b[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S177>/Constant1'

    real_T Constant2_Value_ph[2];      // Expression: [1 0]
                                          //  Referenced by: '<S177>/Constant2'

    real_T CovMessrauschen_Value_i;    // Expression: 10e-4
                                          //  Referenced by: '<S177>/Cov Messrauschen'

    real_T Constant5_Value_b;          // Expression: 0
                                          //  Referenced by: '<S177>/Constant5'

    real_T UnitDelay1_InitialCondition_d[2];// Expression: [0; 0]
                                               //  Referenced by: '<S177>/Unit Delay1'

    real_T CovProzessrauschen_Value_d[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S177>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_p[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S177>/Unit Delay'

    real_T Constant_Value_p[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S179>/Constant'

    real_T Constant1_Value_d[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S179>/Constant1'

    real_T Constant2_Value_j[2];       // Expression: [1 0]
                                          //  Referenced by: '<S179>/Constant2'

    real_T CovMessrauschen_Value_o;    // Expression: 10e-4
                                          //  Referenced by: '<S179>/Cov Messrauschen'

    real_T Constant5_Value_bx;         // Expression: 0
                                          //  Referenced by: '<S179>/Constant5'

    real_T UnitDelay1_InitialCondition_mp[2];// Expression: [0; 0]
                                                //  Referenced by: '<S179>/Unit Delay1'

    real_T CovProzessrauschen_Value_i[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S179>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_eq[4];// Expression: 1 * eye(2, 2)
                                               //  Referenced by: '<S179>/Unit Delay'

    real_T Saturation_UpperSat_l;      // Expression: 0.90
                                          //  Referenced by: '<S175>/Saturation'

    real_T Saturation_LowerSat_d;      // Expression: 0.15
                                          //  Referenced by: '<S175>/Saturation'

    real_T Integrator_IC_fv;           // Expression: 0
                                          //  Referenced by: '<S3>/Integrator'

    real_T Integrator1_IC;             // Expression: 0
                                          //  Referenced by: '<S7>/Integrator1'

    real_T TransferFcn1_A;             // Computed Parameter: TransferFcn1_A
                                          //  Referenced by: '<S7>/Transfer Fcn1'

    real_T TransferFcn1_C;             // Computed Parameter: TransferFcn1_C
                                          //  Referenced by: '<S7>/Transfer Fcn1'

    real_T Integrator1_IC_e;           // Expression: 0
                                          //  Referenced by: '<S8>/Integrator1'

    real_T TransferFcn1_A_h;           // Computed Parameter: TransferFcn1_A_h
                                          //  Referenced by: '<S8>/Transfer Fcn1'

    real_T TransferFcn1_C_f;           // Computed Parameter: TransferFcn1_C_f
                                          //  Referenced by: '<S8>/Transfer Fcn1'

    real_T Integrator1_IC_e4;          // Expression: 0
                                          //  Referenced by: '<S10>/Integrator1'

    real_T TransferFcn1_A_c;           // Computed Parameter: TransferFcn1_A_c
                                          //  Referenced by: '<S10>/Transfer Fcn1'

    real_T TransferFcn1_C_n;           // Computed Parameter: TransferFcn1_C_n
                                          //  Referenced by: '<S10>/Transfer Fcn1'

    real_T Integrator1_IC_g;           // Expression: 0
                                          //  Referenced by: '<S176>/Integrator1'

    real_T TransferFcn1_A_d;           // Computed Parameter: TransferFcn1_A_d
                                          //  Referenced by: '<S176>/Transfer Fcn1'

    real_T TransferFcn1_C_g;           // Computed Parameter: TransferFcn1_C_g
                                          //  Referenced by: '<S176>/Transfer Fcn1'

    real_T Integrator1_IC_l;           // Expression: 0
                                          //  Referenced by: '<S177>/Integrator1'

    real_T TransferFcn1_A_a;           // Computed Parameter: TransferFcn1_A_a
                                          //  Referenced by: '<S177>/Transfer Fcn1'

    real_T TransferFcn1_C_h;           // Computed Parameter: TransferFcn1_C_h
                                          //  Referenced by: '<S177>/Transfer Fcn1'

    real_T Integrator1_IC_o;           // Expression: 0
                                          //  Referenced by: '<S179>/Integrator1'

    real_T TransferFcn1_A_hf;          // Computed Parameter: TransferFcn1_A_hf
                                          //  Referenced by: '<S179>/Transfer Fcn1'

    real_T TransferFcn1_C_j;           // Computed Parameter: TransferFcn1_C_j
                                          //  Referenced by: '<S179>/Transfer Fcn1'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[42];
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
    real_T odeF[1][42];
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
  Controller(Controller const&) = delete;

  // Assignment Operator
  Controller& operator= (Controller const&) & = delete;

  // Move Constructor
  Controller(Controller &&) = delete;

  // Move Assignment Operator
  Controller& operator= (Controller &&) = delete;

  // Real-Time Model get method
  Controller::RT_MODEL * getRTM();

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
  Controller();

  // Destructor
  ~Controller();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Block continuous states
  X rtX;

  // Block Continuous state disabled vector
  XDis rtXDis;

  // private member function(s) for subsystem '<S7>/KF_Elevation'
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
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S6>/Scope1' : Unused code path elimination
//  Block '<S7>/Scope' : Unused code path elimination
//  Block '<S8>/Scope' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination
//  Block '<S175>/Scope' : Unused code path elimination
//  Block '<S175>/Scope1' : Unused code path elimination
//  Block '<S176>/Scope' : Unused code path elimination
//  Block '<S177>/Scope' : Unused code path elimination
//  Block '<S179>/Scope' : Unused code path elimination


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
//  '<S4>'   : 'controller_3dof_container/Subsystem Reference/MATLAB Function1'
//  '<S5>'   : 'controller_3dof_container/Subsystem Reference/MATLAB Function2'
//  '<S6>'   : 'controller_3dof_container/Subsystem1/Subsystem'
//  '<S7>'   : 'controller_3dof_container/Subsystem1/Subsystem1'
//  '<S8>'   : 'controller_3dof_container/Subsystem1/Subsystem2'
//  '<S9>'   : 'controller_3dof_container/Subsystem1/Subsystem3'
//  '<S10>'  : 'controller_3dof_container/Subsystem1/Subsystem4'
//  '<S11>'  : 'controller_3dof_container/Subsystem1/Subsystem6'
//  '<S12>'  : 'controller_3dof_container/Subsystem1/Subsystem/MATLAB Function'
//  '<S13>'  : 'controller_3dof_container/Subsystem1/Subsystem1/KF_Elevation'
//  '<S14>'  : 'controller_3dof_container/Subsystem1/Subsystem2/KF_Elevation'
//  '<S15>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller'
//  '<S16>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1'
//  '<S17>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2'
//  '<S18>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup'
//  '<S19>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain'
//  '<S20>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative'
//  '<S21>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter'
//  '<S22>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs'
//  '<S23>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain'
//  '<S24>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain'
//  '<S25>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S26>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator'
//  '<S27>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs'
//  '<S28>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy'
//  '<S29>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain'
//  '<S30>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy'
//  '<S31>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain'
//  '<S32>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal'
//  '<S33>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation'
//  '<S34>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S35>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum'
//  '<S36>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk'
//  '<S37>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode'
//  '<S38>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S39>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S40>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S41>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal'
//  '<S42>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal'
//  '<S43>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal'
//  '<S44>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S45>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S46>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative/External Ydot'
//  '<S47>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter/Cont. Filter Only'
//  '<S48>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S49>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S50>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S51>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S52>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S53>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S54>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S55>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S56>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S57>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S58>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S59>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S60>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S61>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S62>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S63>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S64>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S65>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S66>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S67>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S68>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S69>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S70>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup'
//  '<S71>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain'
//  '<S72>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative'
//  '<S73>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter'
//  '<S74>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs'
//  '<S75>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain'
//  '<S76>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S77>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S78>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator'
//  '<S79>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs'
//  '<S80>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy'
//  '<S81>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain'
//  '<S82>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy'
//  '<S83>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S84>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal'
//  '<S85>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation'
//  '<S86>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S87>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum'
//  '<S88>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S89>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode'
//  '<S90>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S91>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S92>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S93>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal'
//  '<S94>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal'
//  '<S95>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal'
//  '<S96>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S97>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S98>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative/External Ydot'
//  '<S99>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter/Cont. Filter Only'
//  '<S100>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S101>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S102>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S103>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S104>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S105>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S106>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S107>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S108>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S109>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S110>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S111>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S112>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S113>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S114>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S115>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S116>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S117>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S118>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S119>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S120>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S121>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S122>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup'
//  '<S123>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain'
//  '<S124>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative'
//  '<S125>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter'
//  '<S126>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs'
//  '<S127>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain'
//  '<S128>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S129>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S130>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator'
//  '<S131>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs'
//  '<S132>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy'
//  '<S133>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain'
//  '<S134>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy'
//  '<S135>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S136>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal'
//  '<S137>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation'
//  '<S138>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S139>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum'
//  '<S140>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S141>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode'
//  '<S142>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S143>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S144>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S145>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal'
//  '<S146>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal'
//  '<S147>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal'
//  '<S148>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S149>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S150>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative/External Ydot'
//  '<S151>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter/Cont. Filter Only'
//  '<S152>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S153>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S154>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S155>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S156>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S157>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S158>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S159>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S160>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S161>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S162>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S163>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S164>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S165>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S166>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S167>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S168>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S169>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S170>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S171>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S172>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S173>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S174>' : 'controller_3dof_container/Subsystem1/Subsystem4/KF_Elevation'
//  '<S175>' : 'controller_3dof_container/Subsystem7/Subsystem'
//  '<S176>' : 'controller_3dof_container/Subsystem7/Subsystem1'
//  '<S177>' : 'controller_3dof_container/Subsystem7/Subsystem2'
//  '<S178>' : 'controller_3dof_container/Subsystem7/Subsystem3'
//  '<S179>' : 'controller_3dof_container/Subsystem7/Subsystem4'
//  '<S180>' : 'controller_3dof_container/Subsystem7/Subsystem6'
//  '<S181>' : 'controller_3dof_container/Subsystem7/Subsystem/MATLAB Function'
//  '<S182>' : 'controller_3dof_container/Subsystem7/Subsystem1/KF_Elevation'
//  '<S183>' : 'controller_3dof_container/Subsystem7/Subsystem2/KF_Elevation'
//  '<S184>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller'
//  '<S185>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1'
//  '<S186>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2'
//  '<S187>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Anti-windup'
//  '<S188>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/D Gain'
//  '<S189>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/External Derivative'
//  '<S190>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter'
//  '<S191>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter ICs'
//  '<S192>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/I Gain'
//  '<S193>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain'
//  '<S194>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S195>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator'
//  '<S196>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator ICs'
//  '<S197>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Copy'
//  '<S198>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Gain'
//  '<S199>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/P Copy'
//  '<S200>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Parallel P Gain'
//  '<S201>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Reset Signal'
//  '<S202>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation'
//  '<S203>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S204>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum'
//  '<S205>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum Fdbk'
//  '<S206>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode'
//  '<S207>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S208>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S209>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S210>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/postSat Signal'
//  '<S211>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preInt Signal'
//  '<S212>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preSat Signal'
//  '<S213>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S214>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S215>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/External Derivative/External Ydot'
//  '<S216>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter/Cont. Filter Only'
//  '<S217>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S218>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S219>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S220>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S221>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S222>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S223>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S224>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S225>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S226>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S227>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S228>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S229>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S230>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S231>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S232>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S233>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S234>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S235>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S236>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S237>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S238>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S239>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Anti-windup'
//  '<S240>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/D Gain'
//  '<S241>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/External Derivative'
//  '<S242>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter'
//  '<S243>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter ICs'
//  '<S244>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/I Gain'
//  '<S245>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S246>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S247>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator'
//  '<S248>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator ICs'
//  '<S249>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Copy'
//  '<S250>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Gain'
//  '<S251>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/P Copy'
//  '<S252>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S253>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Reset Signal'
//  '<S254>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation'
//  '<S255>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S256>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum'
//  '<S257>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S258>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode'
//  '<S259>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S260>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S261>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S262>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/postSat Signal'
//  '<S263>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preInt Signal'
//  '<S264>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preSat Signal'
//  '<S265>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S266>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S267>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/External Derivative/External Ydot'
//  '<S268>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter/Cont. Filter Only'
//  '<S269>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S270>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S271>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S272>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S273>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S274>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S275>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S276>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S277>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S278>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S279>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S280>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S281>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S282>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S283>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S284>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S285>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S286>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S287>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S288>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S289>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S290>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S291>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Anti-windup'
//  '<S292>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/D Gain'
//  '<S293>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/External Derivative'
//  '<S294>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter'
//  '<S295>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter ICs'
//  '<S296>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/I Gain'
//  '<S297>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S298>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S299>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator'
//  '<S300>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator ICs'
//  '<S301>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Copy'
//  '<S302>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Gain'
//  '<S303>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/P Copy'
//  '<S304>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S305>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Reset Signal'
//  '<S306>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation'
//  '<S307>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S308>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum'
//  '<S309>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S310>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode'
//  '<S311>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S312>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S313>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S314>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/postSat Signal'
//  '<S315>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preInt Signal'
//  '<S316>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preSat Signal'
//  '<S317>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S318>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S319>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/External Derivative/External Ydot'
//  '<S320>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter/Cont. Filter Only'
//  '<S321>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S322>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S323>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S324>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S325>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S326>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S327>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S328>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S329>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S330>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S331>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S332>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S333>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S334>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S335>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S336>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S337>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S338>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S339>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S340>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S341>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S342>' : 'controller_3dof_container/Subsystem7/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S343>' : 'controller_3dof_container/Subsystem7/Subsystem4/KF_Elevation'

#endif                                 // controller_3dof_container_h_

//
// File trailer for generated code.
//
// [EOF]
//
