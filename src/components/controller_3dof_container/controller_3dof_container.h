//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof_container.h
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
    real_T TmpSignalConversionAtIntegrator[3];
    real_T TmpSignalConversionAtIntegrat_p[3];
    real_T x_dach[2];                  // '<S180>/KF_Elevation'
    real_T P_h[4];                     // '<S180>/KF_Elevation'
    real_T x_dach_n[2];                // '<S178>/KF_Elevation'
    real_T P_d[4];                     // '<S178>/KF_Elevation'
    real_T x_dach_g[2];                // '<S177>/KF_Elevation'
    real_T P_n[4];                     // '<S177>/KF_Elevation'
    real_T x_dach_a[2];                // '<S12>/KF_Elevation'
    real_T P_j[4];                     // '<S12>/KF_Elevation'
    real_T x_dach_j[2];                // '<S10>/KF_Elevation'
    real_T P_nu[4];                    // '<S10>/KF_Elevation'
    real_T x_dach_d[2];                // '<S9>/KF_Elevation'
    real_T P_dr[4];                    // '<S9>/KF_Elevation'
    real_T dx[6];                      // '<S4>/MATLAB Function2'
    real_T UnitDelay1_DSTATE[2];       // '<S9>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S9>/Unit Delay'
    real_T UnitDelay1_DSTATE_f[2];     // '<S10>/Unit Delay1'
    real_T UnitDelay_DSTATE_i[4];      // '<S10>/Unit Delay'
    real_T UnitDelay1_DSTATE_a[2];     // '<S12>/Unit Delay1'
    real_T UnitDelay_DSTATE_d[4];      // '<S12>/Unit Delay'
    real_T UnitDelay1_DSTATE_b[2];     // '<S177>/Unit Delay1'
    real_T UnitDelay_DSTATE_o[4];      // '<S177>/Unit Delay'
    real_T UnitDelay1_DSTATE_b4[2];    // '<S178>/Unit Delay1'
    real_T UnitDelay_DSTATE_g[4];      // '<S178>/Unit Delay'
    real_T UnitDelay1_DSTATE_n[2];     // '<S180>/Unit Delay1'
    real_T UnitDelay_DSTATE_f[4];      // '<S180>/Unit Delay'
    real_T SumD;                       // '<S152>/SumD'
    real_T IntegralGain;               // '<S154>/Integral Gain'
    real_T SumD_k;                     // '<S100>/SumD'
    real_T IntegralGain_d;             // '<S102>/Integral Gain'
    real_T SumD_p;                     // '<S48>/SumD'
    real_T IntegralGain_i;             // '<S50>/Integral Gain'
    real_T SumD_kz;                    // '<S320>/SumD'
    real_T IntegralGain_p;             // '<S322>/Integral Gain'
    real_T SumD_kb;                    // '<S268>/SumD'
    real_T IntegralGain_m;             // '<S270>/Integral Gain'
    real_T SumD_e;                     // '<S216>/SumD'
    real_T IntegralGain_l;             // '<S218>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE[6];       // '<S4>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S53>/Integrator'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_c;        // '<S105>/Integrator'
    real_T Filter_CSTATE_e;            // '<S100>/Filter'
    real_T Integrator_CSTATE_o;        // '<S157>/Integrator'
    real_T Filter_CSTATE_j;            // '<S152>/Filter'
    real_T Integrator_CSTATE_b[3];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_l;        // '<S221>/Integrator'
    real_T Filter_CSTATE_n;            // '<S216>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S273>/Integrator'
    real_T Filter_CSTATE_i;            // '<S268>/Filter'
    real_T Integrator_CSTATE_i;        // '<S325>/Integrator'
    real_T Filter_CSTATE_c;            // '<S320>/Filter'
    real_T Integrator_CSTATE_f[3];     // '<S3>/Integrator'
    real_T Integrator1_CSTATE;         // '<S9>/Integrator1'
    real_T Integrator1_CSTATE_i;       // '<S10>/Integrator1'
    real_T Integrator1_CSTATE_k;       // '<S12>/Integrator1'
    real_T Integrator1_CSTATE_a;       // '<S177>/Integrator1'
    real_T Integrator1_CSTATE_p;       // '<S178>/Integrator1'
    real_T Integrator1_CSTATE_km;      // '<S180>/Integrator1'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE[6];       // '<S4>/Integrator'
    real_T Integrator_CSTATE_j;        // '<S53>/Integrator'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_c;        // '<S105>/Integrator'
    real_T Filter_CSTATE_e;            // '<S100>/Filter'
    real_T Integrator_CSTATE_o;        // '<S157>/Integrator'
    real_T Filter_CSTATE_j;            // '<S152>/Filter'
    real_T Integrator_CSTATE_b[3];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_l;        // '<S221>/Integrator'
    real_T Filter_CSTATE_n;            // '<S216>/Filter'
    real_T Integrator_CSTATE_ja;       // '<S273>/Integrator'
    real_T Filter_CSTATE_i;            // '<S268>/Filter'
    real_T Integrator_CSTATE_i;        // '<S325>/Integrator'
    real_T Filter_CSTATE_c;            // '<S320>/Filter'
    real_T Integrator_CSTATE_f[3];     // '<S3>/Integrator'
    real_T Integrator1_CSTATE;         // '<S9>/Integrator1'
    real_T Integrator1_CSTATE_i;       // '<S10>/Integrator1'
    real_T Integrator1_CSTATE_k;       // '<S12>/Integrator1'
    real_T Integrator1_CSTATE_a;       // '<S177>/Integrator1'
    real_T Integrator1_CSTATE_p;       // '<S178>/Integrator1'
    real_T Integrator1_CSTATE_km;      // '<S180>/Integrator1'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE[6];    // '<S4>/Integrator'
    boolean_T Integrator_CSTATE_j;     // '<S53>/Integrator'
    boolean_T Filter_CSTATE;           // '<S48>/Filter'
    boolean_T Integrator_CSTATE_c;     // '<S105>/Integrator'
    boolean_T Filter_CSTATE_e;         // '<S100>/Filter'
    boolean_T Integrator_CSTATE_o;     // '<S157>/Integrator'
    boolean_T Filter_CSTATE_j;         // '<S152>/Filter'
    boolean_T Integrator_CSTATE_b[3];  // '<S2>/Integrator'
    boolean_T Integrator_CSTATE_l;     // '<S221>/Integrator'
    boolean_T Filter_CSTATE_n;         // '<S216>/Filter'
    boolean_T Integrator_CSTATE_ja;    // '<S273>/Integrator'
    boolean_T Filter_CSTATE_i;         // '<S268>/Filter'
    boolean_T Integrator_CSTATE_i;     // '<S325>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S320>/Filter'
    boolean_T Integrator_CSTATE_f[3];  // '<S3>/Integrator'
    boolean_T Integrator1_CSTATE;      // '<S9>/Integrator1'
    boolean_T Integrator1_CSTATE_i;    // '<S10>/Integrator1'
    boolean_T Integrator1_CSTATE_k;    // '<S12>/Integrator1'
    boolean_T Integrator1_CSTATE_a;    // '<S177>/Integrator1'
    boolean_T Integrator1_CSTATE_p;    // '<S178>/Integrator1'
    boolean_T Integrator1_CSTATE_km;   // '<S180>/Integrator1'
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
    real_T B_eff[16];                  // Variable: B_eff
                                          //  Referenced by:
                                          //    '<S5>/B_Eff'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S176>/MATLAB Function'

    real_T J[9];                       // Variable: J
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T N;                          // Variable: N
                                          //  Referenced by:
                                          //    '<S56>/Filter Coefficient'
                                          //    '<S108>/Filter Coefficient'
                                          //    '<S160>/Filter Coefficient'
                                          //    '<S224>/Filter Coefficient'
                                          //    '<S276>/Filter Coefficient'
                                          //    '<S328>/Filter Coefficient'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S5>/MATLAB Function1'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S176>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S5>/MATLAB Function1'
                                          //    '<S8>/MATLAB Function'
                                          //    '<S176>/MATLAB Function'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T h;                          // Variable: h
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T kd_pitch;                   // Variable: kd_pitch
                                          //  Referenced by:
                                          //    '<S98>/Derivative Gain'
                                          //    '<S266>/Derivative Gain'

    real_T kd_roll;                    // Variable: kd_roll
                                          //  Referenced by:
                                          //    '<S46>/Derivative Gain'
                                          //    '<S214>/Derivative Gain'

    real_T kd_yaw;                     // Variable: kd_yaw
                                          //  Referenced by:
                                          //    '<S150>/Derivative Gain'
                                          //    '<S318>/Derivative Gain'

    real_T ki_pitch;                   // Variable: ki_pitch
                                          //  Referenced by:
                                          //    '<S102>/Integral Gain'
                                          //    '<S270>/Integral Gain'

    real_T ki_roll;                    // Variable: ki_roll
                                          //  Referenced by:
                                          //    '<S50>/Integral Gain'
                                          //    '<S218>/Integral Gain'

    real_T ki_yaw;                     // Variable: ki_yaw
                                          //  Referenced by:
                                          //    '<S154>/Integral Gain'
                                          //    '<S322>/Integral Gain'

    real_T kp_pitch;                   // Variable: kp_pitch
                                          //  Referenced by:
                                          //    '<S110>/Proportional Gain'
                                          //    '<S278>/Proportional Gain'

    real_T kp_roll;                    // Variable: kp_roll
                                          //  Referenced by:
                                          //    '<S58>/Proportional Gain'
                                          //    '<S226>/Proportional Gain'

    real_T kp_yaw;                     // Variable: kp_yaw
                                          //  Referenced by:
                                          //    '<S162>/Proportional Gain'
                                          //    '<S330>/Proportional Gain'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T p[3];                       // Variable: p
                                          //  Referenced by: '<S4>/MATLAB Function2'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S48>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S100>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S152>/Filter'

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
                                 //  Referenced by: '<S53>/Integrator'

    real_T PIDController1_InitialConditi_p;
                              // Mask Parameter: PIDController1_InitialConditi_p
                                 //  Referenced by: '<S105>/Integrator'

    real_T PIDController2_InitialConditi_p;
                              // Mask Parameter: PIDController2_InitialConditi_p
                                 //  Referenced by: '<S157>/Integrator'

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
                                          //  Referenced by: '<S4>/Integrator'

    real_T Constant1_Value[2];         // Expression: [1; 0]
                                          //  Referenced by: '<S9>/Constant1'

    real_T Constant2_Value[2];         // Expression: [1 0]
                                          //  Referenced by: '<S9>/Constant2'

    real_T CovMessrauschen_Value;      // Expression: 10e-4
                                          //  Referenced by: '<S9>/Cov Messrauschen'

    real_T Constant5_Value;            // Expression: 0
                                          //  Referenced by: '<S9>/Constant5'

    real_T UnitDelay1_InitialCondition[2];// Expression: [0; 0]
                                             //  Referenced by: '<S9>/Unit Delay1'

    real_T Constant_Value[4];          // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S9>/Constant'

    real_T CovProzessrauschen_Value[4];// Expression: [0.001 0; 0 800]
                                          //  Referenced by: '<S9>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition[4];// Expression: 1 * eye(2, 2)
                                            //  Referenced by: '<S9>/Unit Delay'

    real_T Constant1_Value_m[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S10>/Constant1'

    real_T Constant2_Value_a[2];       // Expression: [1 0]
                                          //  Referenced by: '<S10>/Constant2'

    real_T CovMessrauschen_Value_e;    // Expression: 10e-4
                                          //  Referenced by: '<S10>/Cov Messrauschen'

    real_T Constant5_Value_i;          // Expression: 0
                                          //  Referenced by: '<S10>/Constant5'

    real_T UnitDelay1_InitialCondition_f[2];// Expression: [0; 0]
                                               //  Referenced by: '<S10>/Unit Delay1'

    real_T Constant_Value_j[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S10>/Constant'

    real_T CovProzessrauschen_Value_o[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S10>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_d[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S10>/Unit Delay'

    real_T Constant1_Value_i[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S12>/Constant1'

    real_T Constant2_Value_p[2];       // Expression: [1 0]
                                          //  Referenced by: '<S12>/Constant2'

    real_T CovMessrauschen_Value_f;    // Expression: 10e-4
                                          //  Referenced by: '<S12>/Cov Messrauschen'

    real_T Constant5_Value_k;          // Expression: 0
                                          //  Referenced by: '<S12>/Constant5'

    real_T UnitDelay1_InitialCondition_m[2];// Expression: [0; 0]
                                               //  Referenced by: '<S12>/Unit Delay1'

    real_T Constant_Value_a[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S12>/Constant'

    real_T CovProzessrauschen_Value_h[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S12>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_e[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S12>/Unit Delay'

    real_T Saturation_UpperSat;        // Expression: 0.90
                                          //  Referenced by: '<S8>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0.15
                                          //  Referenced by: '<S8>/Saturation'

    real_T Integrator_IC_c;            // Expression: 0
                                          //  Referenced by: '<S2>/Integrator'

    real_T Constant_Value_f[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S177>/Constant'

    real_T Constant1_Value_p[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S177>/Constant1'

    real_T Constant2_Value_b[2];       // Expression: [1 0]
                                          //  Referenced by: '<S177>/Constant2'

    real_T CovMessrauschen_Value_j;    // Expression: 10e-4
                                          //  Referenced by: '<S177>/Cov Messrauschen'

    real_T Constant5_Value_d;          // Expression: 0
                                          //  Referenced by: '<S177>/Constant5'

    real_T UnitDelay1_InitialCondition_b[2];// Expression: [0; 0]
                                               //  Referenced by: '<S177>/Unit Delay1'

    real_T CovProzessrauschen_Value_h3[4];// Expression: [0.001 0; 0 800]
                                             //  Referenced by: '<S177>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_o[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S177>/Unit Delay'

    real_T Constant_Value_i[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S178>/Constant'

    real_T Constant1_Value_b[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S178>/Constant1'

    real_T Constant2_Value_ph[2];      // Expression: [1 0]
                                          //  Referenced by: '<S178>/Constant2'

    real_T CovMessrauschen_Value_i;    // Expression: 10e-4
                                          //  Referenced by: '<S178>/Cov Messrauschen'

    real_T Constant5_Value_b;          // Expression: 0
                                          //  Referenced by: '<S178>/Constant5'

    real_T UnitDelay1_InitialCondition_d[2];// Expression: [0; 0]
                                               //  Referenced by: '<S178>/Unit Delay1'

    real_T CovProzessrauschen_Value_d[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S178>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_p[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S178>/Unit Delay'

    real_T Constant_Value_p[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S180>/Constant'

    real_T Constant1_Value_d[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S180>/Constant1'

    real_T Constant2_Value_j[2];       // Expression: [1 0]
                                          //  Referenced by: '<S180>/Constant2'

    real_T CovMessrauschen_Value_o;    // Expression: 10e-4
                                          //  Referenced by: '<S180>/Cov Messrauschen'

    real_T Constant5_Value_bx;         // Expression: 0
                                          //  Referenced by: '<S180>/Constant5'

    real_T UnitDelay1_InitialCondition_mp[2];// Expression: [0; 0]
                                                //  Referenced by: '<S180>/Unit Delay1'

    real_T CovProzessrauschen_Value_i[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S180>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_eq[4];// Expression: 1 * eye(2, 2)
                                               //  Referenced by: '<S180>/Unit Delay'

    real_T Saturation_UpperSat_l;      // Expression: 0.90
                                          //  Referenced by: '<S176>/Saturation'

    real_T Saturation_LowerSat_d;      // Expression: 0.15
                                          //  Referenced by: '<S176>/Saturation'

    real_T Integrator_IC_f;            // Expression: 0
                                          //  Referenced by: '<S3>/Integrator'

    real_T Integrator1_IC;             // Expression: 0
                                          //  Referenced by: '<S9>/Integrator1'

    real_T Integrator1_IC_e;           // Expression: 0
                                          //  Referenced by: '<S10>/Integrator1'

    real_T Integrator1_IC_e4;          // Expression: 0
                                          //  Referenced by: '<S12>/Integrator1'

    real_T Integrator1_IC_g;           // Expression: 0
                                          //  Referenced by: '<S177>/Integrator1'

    real_T Integrator1_IC_l;           // Expression: 0
                                          //  Referenced by: '<S178>/Integrator1'

    real_T Integrator1_IC_o;           // Expression: 0
                                          //  Referenced by: '<S180>/Integrator1'

    boolean_T Constant_Value_c;        // Expression: true
                                          //  Referenced by: '<S1>/Constant'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[30];
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
    real_T odeF[1][30];
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

  // private member function(s) for subsystem '<S9>/KF_Elevation'
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
//  Block '<S8>/Scope' : Unused code path elimination
//  Block '<S8>/Scope1' : Unused code path elimination
//  Block '<S9>/Scope' : Unused code path elimination
//  Block '<S10>/Scope' : Unused code path elimination
//  Block '<S12>/Scope' : Unused code path elimination
//  Block '<S176>/Scope' : Unused code path elimination
//  Block '<S176>/Scope1' : Unused code path elimination
//  Block '<S177>/Scope' : Unused code path elimination
//  Block '<S178>/Scope' : Unused code path elimination
//  Block '<S180>/Scope' : Unused code path elimination


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
//  '<S9>'   : 'controller_3dof_container/Subsystem1/Subsystem1'
//  '<S10>'  : 'controller_3dof_container/Subsystem1/Subsystem2'
//  '<S11>'  : 'controller_3dof_container/Subsystem1/Subsystem3'
//  '<S12>'  : 'controller_3dof_container/Subsystem1/Subsystem4'
//  '<S13>'  : 'controller_3dof_container/Subsystem1/Subsystem/MATLAB Function'
//  '<S14>'  : 'controller_3dof_container/Subsystem1/Subsystem1/KF_Elevation'
//  '<S15>'  : 'controller_3dof_container/Subsystem1/Subsystem2/KF_Elevation'
//  '<S16>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller'
//  '<S17>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1'
//  '<S18>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2'
//  '<S19>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup'
//  '<S20>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain'
//  '<S21>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative'
//  '<S22>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter'
//  '<S23>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs'
//  '<S24>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain'
//  '<S25>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain'
//  '<S26>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S27>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator'
//  '<S28>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs'
//  '<S29>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy'
//  '<S30>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain'
//  '<S31>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy'
//  '<S32>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain'
//  '<S33>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal'
//  '<S34>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation'
//  '<S35>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S36>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum'
//  '<S37>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk'
//  '<S38>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode'
//  '<S39>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S40>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S41>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S42>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal'
//  '<S43>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal'
//  '<S44>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal'
//  '<S45>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S46>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S47>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/External Derivative/External Ydot'
//  '<S48>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter/Cont. Filter Only'
//  '<S49>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S50>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S51>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S52>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S53>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S54>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S55>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S56>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S57>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S58>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S59>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S60>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S61>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S62>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S63>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S64>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S65>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S66>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S67>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S68>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S69>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S70>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S71>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup'
//  '<S72>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain'
//  '<S73>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative'
//  '<S74>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter'
//  '<S75>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs'
//  '<S76>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain'
//  '<S77>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S78>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S79>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator'
//  '<S80>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs'
//  '<S81>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy'
//  '<S82>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain'
//  '<S83>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy'
//  '<S84>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S85>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal'
//  '<S86>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation'
//  '<S87>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S88>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum'
//  '<S89>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S90>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode'
//  '<S91>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S92>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S93>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S94>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal'
//  '<S95>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal'
//  '<S96>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal'
//  '<S97>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S98>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S99>'  : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/External Derivative/External Ydot'
//  '<S100>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter/Cont. Filter Only'
//  '<S101>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S102>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S103>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S104>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S105>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S106>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S107>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S108>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S109>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S110>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S111>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S112>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S113>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S114>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S115>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S116>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S117>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S118>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S119>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S120>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S121>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S122>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S123>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup'
//  '<S124>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain'
//  '<S125>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative'
//  '<S126>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter'
//  '<S127>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs'
//  '<S128>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain'
//  '<S129>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S130>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S131>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator'
//  '<S132>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs'
//  '<S133>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy'
//  '<S134>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain'
//  '<S135>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy'
//  '<S136>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S137>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal'
//  '<S138>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation'
//  '<S139>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S140>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum'
//  '<S141>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S142>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode'
//  '<S143>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S144>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S145>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S146>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal'
//  '<S147>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal'
//  '<S148>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal'
//  '<S149>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S150>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S151>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/External Derivative/External Ydot'
//  '<S152>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter/Cont. Filter Only'
//  '<S153>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S154>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S155>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S156>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S157>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S158>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S159>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S160>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S161>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S162>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S163>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S164>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S165>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S166>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S167>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S168>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S169>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S170>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S171>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S172>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S173>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S174>' : 'controller_3dof_container/Subsystem1/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S175>' : 'controller_3dof_container/Subsystem1/Subsystem4/KF_Elevation'
//  '<S176>' : 'controller_3dof_container/Subsystem7/Subsystem'
//  '<S177>' : 'controller_3dof_container/Subsystem7/Subsystem1'
//  '<S178>' : 'controller_3dof_container/Subsystem7/Subsystem2'
//  '<S179>' : 'controller_3dof_container/Subsystem7/Subsystem3'
//  '<S180>' : 'controller_3dof_container/Subsystem7/Subsystem4'
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
