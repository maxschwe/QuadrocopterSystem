//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.432
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Mar  2 17:08:49 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef controller_3dof_h_
#define controller_3dof_h_
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

// Class declaration for model controller_3dof
class Controller final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T TmpSignalConversionAtIntegrator[3];
    real_T Sum[3];                     // '<S8>/Sum'
    real_T Sum_m[3];                   // '<S9>/Sum'
    real_T x_dach[2];                  // '<S6>/KF_Elevation'
    real_T P_g[4];                     // '<S6>/KF_Elevation'
    real_T x_dach_l[2];                // '<S4>/KF_Elevation'
    real_T P_l[4];                     // '<S4>/KF_Elevation'
    real_T x_dach_h[2];                // '<S3>/KF_Elevation'
    real_T P_i[4];                     // '<S3>/KF_Elevation'
    real_T dx[6];                      // '<S2>/MATLAB Function2'
    real_T UnitDelay1_DSTATE[2];       // '<S3>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S3>/Unit Delay'
    real_T UnitDelay1_DSTATE_n[2];     // '<S4>/Unit Delay1'
    real_T UnitDelay_DSTATE_o[4];      // '<S4>/Unit Delay'
    real_T UnitDelay1_DSTATE_p[2];     // '<S6>/Unit Delay1'
    real_T UnitDelay_DSTATE_d[4];      // '<S6>/Unit Delay'
    real_T SumD;                       // '<S48>/SumD'
    real_T IntegralGain;               // '<S50>/Integral Gain'
    real_T SumD_o;                     // '<S100>/SumD'
    real_T IntegralGain_o;             // '<S102>/Integral Gain'
    real_T SumD_j;                     // '<S152>/SumD'
    real_T IntegralGain_p;             // '<S154>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T TransferFcn_CSTATE;         // '<S3>/Transfer Fcn'
    real_T TransferFcn_CSTATE_p;       // '<S4>/Transfer Fcn'
    real_T TransferFcn_CSTATE_k;       // '<S6>/Transfer Fcn'
    real_T Integrator_CSTATE[3];       // '<S8>/Integrator'
    real_T Integrator_CSTATE_p[3];     // '<Root>/Integrator'
    real_T Integrator_CSTATE_o[6];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_c[3];     // '<S9>/Integrator'
    real_T Integrator1_CSTATE;         // '<S3>/Integrator1'
    real_T Integrator1_CSTATE_o;       // '<S4>/Integrator1'
    real_T Integrator1_CSTATE_j;       // '<S6>/Integrator1'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_pg;       // '<S53>/Integrator'
    real_T Filter_CSTATE_h;            // '<S100>/Filter'
    real_T Integrator_CSTATE_i;        // '<S105>/Integrator'
    real_T Filter_CSTATE_a;            // '<S152>/Filter'
    real_T Integrator_CSTATE_j;        // '<S157>/Integrator'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T TransferFcn_CSTATE;         // '<S3>/Transfer Fcn'
    real_T TransferFcn_CSTATE_p;       // '<S4>/Transfer Fcn'
    real_T TransferFcn_CSTATE_k;       // '<S6>/Transfer Fcn'
    real_T Integrator_CSTATE[3];       // '<S8>/Integrator'
    real_T Integrator_CSTATE_p[3];     // '<Root>/Integrator'
    real_T Integrator_CSTATE_o[6];     // '<S2>/Integrator'
    real_T Integrator_CSTATE_c[3];     // '<S9>/Integrator'
    real_T Integrator1_CSTATE;         // '<S3>/Integrator1'
    real_T Integrator1_CSTATE_o;       // '<S4>/Integrator1'
    real_T Integrator1_CSTATE_j;       // '<S6>/Integrator1'
    real_T Filter_CSTATE;              // '<S48>/Filter'
    real_T Integrator_CSTATE_pg;       // '<S53>/Integrator'
    real_T Filter_CSTATE_h;            // '<S100>/Filter'
    real_T Integrator_CSTATE_i;        // '<S105>/Integrator'
    real_T Filter_CSTATE_a;            // '<S152>/Filter'
    real_T Integrator_CSTATE_j;        // '<S157>/Integrator'
  };

  // State disabled
  struct XDis {
    boolean_T TransferFcn_CSTATE;      // '<S3>/Transfer Fcn'
    boolean_T TransferFcn_CSTATE_p;    // '<S4>/Transfer Fcn'
    boolean_T TransferFcn_CSTATE_k;    // '<S6>/Transfer Fcn'
    boolean_T Integrator_CSTATE[3];    // '<S8>/Integrator'
    boolean_T Integrator_CSTATE_p[3];  // '<Root>/Integrator'
    boolean_T Integrator_CSTATE_o[6];  // '<S2>/Integrator'
    boolean_T Integrator_CSTATE_c[3];  // '<S9>/Integrator'
    boolean_T Integrator1_CSTATE;      // '<S3>/Integrator1'
    boolean_T Integrator1_CSTATE_o;    // '<S4>/Integrator1'
    boolean_T Integrator1_CSTATE_j;    // '<S6>/Integrator1'
    boolean_T Filter_CSTATE;           // '<S48>/Filter'
    boolean_T Integrator_CSTATE_pg;    // '<S53>/Integrator'
    boolean_T Filter_CSTATE_h;         // '<S100>/Filter'
    boolean_T Integrator_CSTATE_i;     // '<S105>/Integrator'
    boolean_T Filter_CSTATE_a;         // '<S152>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S157>/Integrator'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T w[4];                       // '<Root>/w'
    real_T y[6];                       // '<Root>/y'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u[4];                       // '<Root>/u'
    real_T y_pred[6];                  // '<Root>/y_pred'
    real_T values[6];                  // '<Root>/values'
  };

  // Parameters (default storage)
  struct P {
    real_T E[16];                      // Variable: E
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function'
                                          //    '<S2>/Mixer'
                                          //    '<S7>/MATLAB Function'

    real_T I[9];                       // Variable: I
                                          //  Referenced by: '<S2>/MATLAB Function2'

    real_T K[18];                      // Variable: K
                                          //  Referenced by:
                                          //    '<S8>/Gain'
                                          //    '<S9>/Gain'

    real_T Ki[3];                      // Variable: Ki
                                          //  Referenced by:
                                          //    '<S8>/Gain2'
                                          //    '<S9>/Gain2'

    real_T V[9];                       // Variable: V
                                          //  Referenced by:
                                          //    '<S8>/Gain1'
                                          //    '<S9>/Gain1'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function'
                                          //    '<S2>/MATLAB Function1'
                                          //    '<S7>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function'
                                          //    '<S2>/MATLAB Function1'
                                          //    '<S7>/MATLAB Function'

    real_T d;                          // Variable: d
                                          //  Referenced by: '<S2>/MATLAB Function2'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S2>/MATLAB Function2'

    real_T kd_pitch;                   // Variable: kd_pitch
                                          //  Referenced by: '<S98>/Derivative Gain'

    real_T kd_roll;                    // Variable: kd_roll
                                          //  Referenced by: '<S46>/Derivative Gain'

    real_T kd_yaw;                     // Variable: kd_yaw
                                          //  Referenced by: '<S150>/Derivative Gain'

    real_T ke;                         // Variable: ke
                                          //  Referenced by:
                                          //    '<S56>/Filter Coefficient'
                                          //    '<S108>/Filter Coefficient'
                                          //    '<S160>/Filter Coefficient'

    real_T ki_pitch;                   // Variable: ki_pitch
                                          //  Referenced by: '<S102>/Integral Gain'

    real_T ki_roll;                    // Variable: ki_roll
                                          //  Referenced by: '<S50>/Integral Gain'

    real_T ki_yaw;                     // Variable: ki_yaw
                                          //  Referenced by: '<S154>/Integral Gain'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S2>/MATLAB Function2'

    real_T p;                          // Variable: p
                                          //  Referenced by: '<S2>/MATLAB Function2'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S48>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S100>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S152>/Filter'

    real_T PIDController_InitialConditio_d;
                              // Mask Parameter: PIDController_InitialConditio_d
                                 //  Referenced by: '<S53>/Integrator'

    real_T PIDController1_InitialConditi_m;
                              // Mask Parameter: PIDController1_InitialConditi_m
                                 //  Referenced by: '<S105>/Integrator'

    real_T PIDController2_InitialConditi_o;
                              // Mask Parameter: PIDController2_InitialConditi_o
                                 //  Referenced by: '<S157>/Integrator'

    real_T Constant1_Value[2];         // Expression: [1; 0]
                                          //  Referenced by: '<S3>/Constant1'

    real_T Constant2_Value[2];         // Expression: [1 0]
                                          //  Referenced by: '<S3>/Constant2'

    real_T CovMessrauschen_Value;      // Expression: 10e-4
                                          //  Referenced by: '<S3>/Cov Messrauschen'

    real_T Constant5_Value;            // Expression: 0
                                          //  Referenced by: '<S3>/Constant5'

    real_T UnitDelay1_InitialCondition[2];// Expression: [0; 0]
                                             //  Referenced by: '<S3>/Unit Delay1'

    real_T Constant_Value[4];          // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S3>/Constant'

    real_T CovProzessrauschen_Value[4];// Expression: [0.001 0; 0 800]
                                          //  Referenced by: '<S3>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition[4];// Expression: 1 * eye(2, 2)
                                            //  Referenced by: '<S3>/Unit Delay'

    real_T Constant1_Value_n[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S4>/Constant1'

    real_T Constant2_Value_e[2];       // Expression: [1 0]
                                          //  Referenced by: '<S4>/Constant2'

    real_T CovMessrauschen_Value_n;    // Expression: 10e-4
                                          //  Referenced by: '<S4>/Cov Messrauschen'

    real_T Constant5_Value_l;          // Expression: 0
                                          //  Referenced by: '<S4>/Constant5'

    real_T UnitDelay1_InitialCondition_c[2];// Expression: [0; 0]
                                               //  Referenced by: '<S4>/Unit Delay1'

    real_T Constant_Value_i[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S4>/Constant'

    real_T CovProzessrauschen_Value_n[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S4>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_c[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S4>/Unit Delay'

    real_T Constant1_Value_m[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S6>/Constant1'

    real_T Constant2_Value_m[2];       // Expression: [1 0]
                                          //  Referenced by: '<S6>/Constant2'

    real_T CovMessrauschen_Value_j;    // Expression: 10e-4
                                          //  Referenced by: '<S6>/Cov Messrauschen'

    real_T Constant5_Value_n;          // Expression: 0
                                          //  Referenced by: '<S6>/Constant5'

    real_T UnitDelay1_InitialCondition_b[2];// Expression: [0; 0]
                                               //  Referenced by: '<S6>/Unit Delay1'

    real_T Constant_Value_d[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S6>/Constant'

    real_T CovProzessrauschen_Value_i[4];// Expression: [0.001 0; 0 800]
                                            //  Referenced by: '<S6>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_cm[4];// Expression: 1 * eye(2, 2)
                                               //  Referenced by: '<S6>/Unit Delay'

    real_T TransferFcn_A;              // Computed Parameter: TransferFcn_A
                                          //  Referenced by: '<S3>/Transfer Fcn'

    real_T TransferFcn_C;              // Computed Parameter: TransferFcn_C
                                          //  Referenced by: '<S3>/Transfer Fcn'

    real_T TransferFcn_A_c;            // Computed Parameter: TransferFcn_A_c
                                          //  Referenced by: '<S4>/Transfer Fcn'

    real_T TransferFcn_C_a;            // Computed Parameter: TransferFcn_C_a
                                          //  Referenced by: '<S4>/Transfer Fcn'

    real_T TransferFcn_A_o;            // Computed Parameter: TransferFcn_A_o
                                          //  Referenced by: '<S6>/Transfer Fcn'

    real_T TransferFcn_C_n;            // Computed Parameter: TransferFcn_C_n
                                          //  Referenced by: '<S6>/Transfer Fcn'

    real_T Integrator_IC;              // Expression: 0
                                          //  Referenced by: '<S8>/Integrator'

    real_T Saturation_UpperSat;        // Expression: 0.90
                                          //  Referenced by: '<S1>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0.15
                                          //  Referenced by: '<S1>/Saturation'

    real_T Integrator_IC_c;            // Expression: 0
                                          //  Referenced by: '<Root>/Integrator'

    real_T Integrator_IC_m[6];         // Expression: [0; 0; 0; 0; 0; 0]
                                          //  Referenced by: '<S2>/Integrator'

    real_T Integrator_IC_cm;           // Expression: 0
                                          //  Referenced by: '<S9>/Integrator'

    real_T Saturation_UpperSat_o;      // Expression: 0.90
                                          //  Referenced by: '<S7>/Saturation'

    real_T Saturation_LowerSat_g;      // Expression: 0.15
                                          //  Referenced by: '<S7>/Saturation'

    real_T Integrator1_IC;             // Expression: 0
                                          //  Referenced by: '<S3>/Integrator1'

    real_T Integrator1_IC_g;           // Expression: 0
                                          //  Referenced by: '<S4>/Integrator1'

    real_T Integrator1_IC_l;           // Expression: 0
                                          //  Referenced by: '<S6>/Integrator1'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[27];
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
    real_T odeF[1][27];
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

  // private member function(s) for subsystem '<S1>/MATLAB Function'
  void MATLABFunction(const real_T rtu_tau[4], real_T rty_u[4]);

  // private member function(s) for subsystem '<S3>/KF_Elevation'
  static void KF_Elevation(const real_T rtu_A[4], const real_T rtu_B[2], const
    real_T rtu_C[2], const real_T rtu_Q[4], real_T rtu_R, real_T rtu_y, real_T
    rtu_u, const real_T rtu_Pold[4], real_T rty_x_dach[2], real_T rty_P[4]);

  // Global mass matrix

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void controller_3dof_derivatives();

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S1>/Scope' : Unused code path elimination
//  Block '<S1>/Scope1' : Unused code path elimination
//  Block '<S2>/Transfer Fcn' : Unused code path elimination
//  Block '<S2>/Transfer Fcn1' : Unused code path elimination
//  Block '<S2>/Transfer Fcn2' : Unused code path elimination
//  Block '<S2>/Transfer Fcn3' : Unused code path elimination
//  Block '<S3>/Scope' : Unused code path elimination
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S58>/Proportional Gain' : Unused code path elimination
//  Block '<S62>/Sum' : Unused code path elimination
//  Block '<S110>/Proportional Gain' : Unused code path elimination
//  Block '<S114>/Sum' : Unused code path elimination
//  Block '<S162>/Proportional Gain' : Unused code path elimination
//  Block '<S166>/Sum' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S7>/Scope' : Unused code path elimination
//  Block '<S7>/Scope1' : Unused code path elimination


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
//  '<Root>' : 'controller_3dof'
//  '<S1>'   : 'controller_3dof/Subsystem'
//  '<S2>'   : 'controller_3dof/Subsystem Reference'
//  '<S3>'   : 'controller_3dof/Subsystem1'
//  '<S4>'   : 'controller_3dof/Subsystem2'
//  '<S5>'   : 'controller_3dof/Subsystem3'
//  '<S6>'   : 'controller_3dof/Subsystem4'
//  '<S7>'   : 'controller_3dof/Subsystem5'
//  '<S8>'   : 'controller_3dof/Subsystem6'
//  '<S9>'   : 'controller_3dof/Subsystem8'
//  '<S10>'  : 'controller_3dof/Subsystem/MATLAB Function'
//  '<S11>'  : 'controller_3dof/Subsystem Reference/MATLAB Function'
//  '<S12>'  : 'controller_3dof/Subsystem Reference/MATLAB Function1'
//  '<S13>'  : 'controller_3dof/Subsystem Reference/MATLAB Function2'
//  '<S14>'  : 'controller_3dof/Subsystem1/KF_Elevation'
//  '<S15>'  : 'controller_3dof/Subsystem2/KF_Elevation'
//  '<S16>'  : 'controller_3dof/Subsystem3/PID Controller'
//  '<S17>'  : 'controller_3dof/Subsystem3/PID Controller1'
//  '<S18>'  : 'controller_3dof/Subsystem3/PID Controller2'
//  '<S19>'  : 'controller_3dof/Subsystem3/PID Controller/Anti-windup'
//  '<S20>'  : 'controller_3dof/Subsystem3/PID Controller/D Gain'
//  '<S21>'  : 'controller_3dof/Subsystem3/PID Controller/External Derivative'
//  '<S22>'  : 'controller_3dof/Subsystem3/PID Controller/Filter'
//  '<S23>'  : 'controller_3dof/Subsystem3/PID Controller/Filter ICs'
//  '<S24>'  : 'controller_3dof/Subsystem3/PID Controller/I Gain'
//  '<S25>'  : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain'
//  '<S26>'  : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S27>'  : 'controller_3dof/Subsystem3/PID Controller/Integrator'
//  '<S28>'  : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs'
//  '<S29>'  : 'controller_3dof/Subsystem3/PID Controller/N Copy'
//  '<S30>'  : 'controller_3dof/Subsystem3/PID Controller/N Gain'
//  '<S31>'  : 'controller_3dof/Subsystem3/PID Controller/P Copy'
//  '<S32>'  : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain'
//  '<S33>'  : 'controller_3dof/Subsystem3/PID Controller/Reset Signal'
//  '<S34>'  : 'controller_3dof/Subsystem3/PID Controller/Saturation'
//  '<S35>'  : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S36>'  : 'controller_3dof/Subsystem3/PID Controller/Sum'
//  '<S37>'  : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk'
//  '<S38>'  : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode'
//  '<S39>'  : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S40>'  : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S41>'  : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S42>'  : 'controller_3dof/Subsystem3/PID Controller/postSat Signal'
//  '<S43>'  : 'controller_3dof/Subsystem3/PID Controller/preInt Signal'
//  '<S44>'  : 'controller_3dof/Subsystem3/PID Controller/preSat Signal'
//  '<S45>'  : 'controller_3dof/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S46>'  : 'controller_3dof/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S47>'  : 'controller_3dof/Subsystem3/PID Controller/External Derivative/External Ydot'
//  '<S48>'  : 'controller_3dof/Subsystem3/PID Controller/Filter/Cont. Filter Only'
//  '<S49>'  : 'controller_3dof/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S50>'  : 'controller_3dof/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S51>'  : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S52>'  : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S53>'  : 'controller_3dof/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S54>'  : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S55>'  : 'controller_3dof/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S56>'  : 'controller_3dof/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S57>'  : 'controller_3dof/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S58>'  : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S59>'  : 'controller_3dof/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S60>'  : 'controller_3dof/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S61>'  : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S62>'  : 'controller_3dof/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S63>'  : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S64>'  : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S65>'  : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S66>'  : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S67>'  : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S68>'  : 'controller_3dof/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S69>'  : 'controller_3dof/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S70>'  : 'controller_3dof/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S71>'  : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup'
//  '<S72>'  : 'controller_3dof/Subsystem3/PID Controller1/D Gain'
//  '<S73>'  : 'controller_3dof/Subsystem3/PID Controller1/External Derivative'
//  '<S74>'  : 'controller_3dof/Subsystem3/PID Controller1/Filter'
//  '<S75>'  : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs'
//  '<S76>'  : 'controller_3dof/Subsystem3/PID Controller1/I Gain'
//  '<S77>'  : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S78>'  : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S79>'  : 'controller_3dof/Subsystem3/PID Controller1/Integrator'
//  '<S80>'  : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs'
//  '<S81>'  : 'controller_3dof/Subsystem3/PID Controller1/N Copy'
//  '<S82>'  : 'controller_3dof/Subsystem3/PID Controller1/N Gain'
//  '<S83>'  : 'controller_3dof/Subsystem3/PID Controller1/P Copy'
//  '<S84>'  : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S85>'  : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal'
//  '<S86>'  : 'controller_3dof/Subsystem3/PID Controller1/Saturation'
//  '<S87>'  : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S88>'  : 'controller_3dof/Subsystem3/PID Controller1/Sum'
//  '<S89>'  : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S90>'  : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode'
//  '<S91>'  : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S92>'  : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S93>'  : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S94>'  : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal'
//  '<S95>'  : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal'
//  '<S96>'  : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal'
//  '<S97>'  : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S98>'  : 'controller_3dof/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S99>'  : 'controller_3dof/Subsystem3/PID Controller1/External Derivative/External Ydot'
//  '<S100>' : 'controller_3dof/Subsystem3/PID Controller1/Filter/Cont. Filter Only'
//  '<S101>' : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S102>' : 'controller_3dof/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S103>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S104>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S105>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S106>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S107>' : 'controller_3dof/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S108>' : 'controller_3dof/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S109>' : 'controller_3dof/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S110>' : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S111>' : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S112>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S113>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S114>' : 'controller_3dof/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S115>' : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S116>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S117>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S118>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S119>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S120>' : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S121>' : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S122>' : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S123>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup'
//  '<S124>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain'
//  '<S125>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative'
//  '<S126>' : 'controller_3dof/Subsystem3/PID Controller2/Filter'
//  '<S127>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs'
//  '<S128>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain'
//  '<S129>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S130>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S131>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator'
//  '<S132>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs'
//  '<S133>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy'
//  '<S134>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain'
//  '<S135>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy'
//  '<S136>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S137>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal'
//  '<S138>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation'
//  '<S139>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S140>' : 'controller_3dof/Subsystem3/PID Controller2/Sum'
//  '<S141>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S142>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode'
//  '<S143>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S144>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S145>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S146>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal'
//  '<S147>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal'
//  '<S148>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal'
//  '<S149>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S150>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S151>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative/External Ydot'
//  '<S152>' : 'controller_3dof/Subsystem3/PID Controller2/Filter/Cont. Filter Only'
//  '<S153>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S154>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S155>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S156>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S157>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S158>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S159>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S160>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S161>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S162>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S163>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S164>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S165>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S166>' : 'controller_3dof/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S167>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S168>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S169>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S170>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S171>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S172>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S173>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S174>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S175>' : 'controller_3dof/Subsystem4/KF_Elevation'
//  '<S176>' : 'controller_3dof/Subsystem5/MATLAB Function'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
