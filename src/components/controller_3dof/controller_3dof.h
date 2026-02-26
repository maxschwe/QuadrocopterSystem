//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.337
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Feb 26 11:30:56 2026
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
    real_T x_dach[2];                  // '<S6>/KF_Elevation'
    real_T P_p[4];                     // '<S6>/KF_Elevation'
    real_T x_dach_f[2];                // '<S4>/KF_Elevation'
    real_T P_n[4];                     // '<S4>/KF_Elevation'
    real_T x_dach_n[2];                // '<S3>/KF_Elevation'
    real_T P_o[4];                     // '<S3>/KF_Elevation'
    real_T dx[6];                      // '<S1>/MATLAB Function2'
    real_T UnitDelay1_DSTATE[2];       // '<S3>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S3>/Unit Delay'
    real_T UnitDelay1_DSTATE_j[2];     // '<S4>/Unit Delay1'
    real_T UnitDelay_DSTATE_k[4];      // '<S4>/Unit Delay'
    real_T UnitDelay1_DSTATE_k[2];     // '<S6>/Unit Delay1'
    real_T UnitDelay_DSTATE_m[4];      // '<S6>/Unit Delay'
    real_T FilterCoefficient;          // '<S102>/Filter Coefficient'
    real_T FilterCoefficient_o;        // '<S154>/Filter Coefficient'
    real_T IntegralGain;               // '<S148>/Integral Gain'
    real_T IntegralGain_e;             // '<S96>/Integral Gain'
    real_T SumD;                       // '<S42>/SumD'
    real_T IntegralGain_j;             // '<S44>/Integral Gain'
    real_T FilterCoefficient_b;        // '<S265>/Filter Coefficient'
    real_T FilterCoefficient_a;        // '<S317>/Filter Coefficient'
    real_T IntegralGain_p;             // '<S311>/Integral Gain'
    real_T IntegralGain_o;             // '<S259>/Integral Gain'
    real_T SumD_p;                     // '<S205>/SumD'
    real_T IntegralGain_od;            // '<S207>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_c;        // '<S47>/Integrator'
    real_T Filter_CSTATE;              // '<S42>/Filter'
    real_T Integrator_CSTATE_e;        // '<S99>/Integrator'
    real_T Filter_CSTATE_g;            // '<S94>/Filter'
    real_T Integrator_CSTATE_i;        // '<S151>/Integrator'
    real_T Filter_CSTATE_e;            // '<S146>/Filter'
    real_T Integrator_CSTATE_p;        // '<S210>/Integrator'
    real_T Filter_CSTATE_b;            // '<S205>/Filter'
    real_T Integrator_CSTATE_iz;       // '<S262>/Integrator'
    real_T Filter_CSTATE_m;            // '<S257>/Filter'
    real_T Integrator_CSTATE_j;        // '<S314>/Integrator'
    real_T Filter_CSTATE_c;            // '<S309>/Filter'
    real_T Integrator_CSTATE_pz[3];    // '<Root>/Integrator'
    real_T Integrator1_CSTATE;         // '<S3>/Integrator1'
    real_T Integrator1_CSTATE_o;       // '<S4>/Integrator1'
    real_T Integrator1_CSTATE_g;       // '<S6>/Integrator1'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_c;        // '<S47>/Integrator'
    real_T Filter_CSTATE;              // '<S42>/Filter'
    real_T Integrator_CSTATE_e;        // '<S99>/Integrator'
    real_T Filter_CSTATE_g;            // '<S94>/Filter'
    real_T Integrator_CSTATE_i;        // '<S151>/Integrator'
    real_T Filter_CSTATE_e;            // '<S146>/Filter'
    real_T Integrator_CSTATE_p;        // '<S210>/Integrator'
    real_T Filter_CSTATE_b;            // '<S205>/Filter'
    real_T Integrator_CSTATE_iz;       // '<S262>/Integrator'
    real_T Filter_CSTATE_m;            // '<S257>/Filter'
    real_T Integrator_CSTATE_j;        // '<S314>/Integrator'
    real_T Filter_CSTATE_c;            // '<S309>/Filter'
    real_T Integrator_CSTATE_pz[3];    // '<Root>/Integrator'
    real_T Integrator1_CSTATE;         // '<S3>/Integrator1'
    real_T Integrator1_CSTATE_o;       // '<S4>/Integrator1'
    real_T Integrator1_CSTATE_g;       // '<S6>/Integrator1'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE[6];    // '<S1>/Integrator'
    boolean_T Integrator_CSTATE_c;     // '<S47>/Integrator'
    boolean_T Filter_CSTATE;           // '<S42>/Filter'
    boolean_T Integrator_CSTATE_e;     // '<S99>/Integrator'
    boolean_T Filter_CSTATE_g;         // '<S94>/Filter'
    boolean_T Integrator_CSTATE_i;     // '<S151>/Integrator'
    boolean_T Filter_CSTATE_e;         // '<S146>/Filter'
    boolean_T Integrator_CSTATE_p;     // '<S210>/Integrator'
    boolean_T Filter_CSTATE_b;         // '<S205>/Filter'
    boolean_T Integrator_CSTATE_iz;    // '<S262>/Integrator'
    boolean_T Filter_CSTATE_m;         // '<S257>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S314>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S309>/Filter'
    boolean_T Integrator_CSTATE_pz[3]; // '<Root>/Integrator'
    boolean_T Integrator1_CSTATE;      // '<S3>/Integrator1'
    boolean_T Integrator1_CSTATE_o;    // '<S4>/Integrator1'
    boolean_T Integrator1_CSTATE_g;    // '<S6>/Integrator1'
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
                                          //    '<S1>/Mixer'
                                          //    '<S12>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T I[9];                       // Variable: I
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S12>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S12>/MATLAB Function'
                                          //    '<S175>/MATLAB Function'

    real_T d;                          // Variable: d
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T p;                          // Variable: p
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T PIDController1_D;           // Mask Parameter: PIDController1_D
                                          //  Referenced by: '<S92>/Derivative Gain'

    real_T PIDController2_D;           // Mask Parameter: PIDController2_D
                                          //  Referenced by: '<S144>/Derivative Gain'

    real_T PIDController_D;            // Mask Parameter: PIDController_D
                                          //  Referenced by: '<S40>/Derivative Gain'

    real_T PIDController1_D_k;         // Mask Parameter: PIDController1_D_k
                                          //  Referenced by: '<S255>/Derivative Gain'

    real_T PIDController2_D_m;         // Mask Parameter: PIDController2_D_m
                                          //  Referenced by: '<S307>/Derivative Gain'

    real_T PIDController_D_c;          // Mask Parameter: PIDController_D_c
                                          //  Referenced by: '<S203>/Derivative Gain'

    real_T PIDController2_I;           // Mask Parameter: PIDController2_I
                                          //  Referenced by: '<S148>/Integral Gain'

    real_T PIDController1_I;           // Mask Parameter: PIDController1_I
                                          //  Referenced by: '<S96>/Integral Gain'

    real_T PIDController_I;            // Mask Parameter: PIDController_I
                                          //  Referenced by: '<S44>/Integral Gain'

    real_T PIDController2_I_i;         // Mask Parameter: PIDController2_I_i
                                          //  Referenced by: '<S311>/Integral Gain'

    real_T PIDController1_I_m;         // Mask Parameter: PIDController1_I_m
                                          //  Referenced by: '<S259>/Integral Gain'

    real_T PIDController_I_a;          // Mask Parameter: PIDController_I_a
                                          //  Referenced by: '<S207>/Integral Gain'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S42>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S94>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S146>/Filter'

    real_T PIDController_InitialConditio_e;
                              // Mask Parameter: PIDController_InitialConditio_e
                                 //  Referenced by: '<S205>/Filter'

    real_T PIDController1_InitialConditi_j;
                              // Mask Parameter: PIDController1_InitialConditi_j
                                 //  Referenced by: '<S257>/Filter'

    real_T PIDController2_InitialConditi_e;
                              // Mask Parameter: PIDController2_InitialConditi_e
                                 //  Referenced by: '<S309>/Filter'

    real_T PIDController_InitialConditio_l;
                              // Mask Parameter: PIDController_InitialConditio_l
                                 //  Referenced by: '<S47>/Integrator'

    real_T PIDController1_InitialConditi_d;
                              // Mask Parameter: PIDController1_InitialConditi_d
                                 //  Referenced by: '<S99>/Integrator'

    real_T PIDController2_InitialConditi_n;
                              // Mask Parameter: PIDController2_InitialConditi_n
                                 //  Referenced by: '<S151>/Integrator'

    real_T PIDController_InitialConditio_d;
                              // Mask Parameter: PIDController_InitialConditio_d
                                 //  Referenced by: '<S210>/Integrator'

    real_T PIDController1_InitialConditi_m;
                              // Mask Parameter: PIDController1_InitialConditi_m
                                 //  Referenced by: '<S262>/Integrator'

    real_T PIDController2_InitialConditi_o;
                              // Mask Parameter: PIDController2_InitialConditi_o
                                 //  Referenced by: '<S314>/Integrator'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S50>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S102>/Filter Coefficient'

    real_T PIDController2_N;           // Mask Parameter: PIDController2_N
                                          //  Referenced by: '<S154>/Filter Coefficient'

    real_T PIDController_N_o;          // Mask Parameter: PIDController_N_o
                                          //  Referenced by: '<S213>/Filter Coefficient'

    real_T PIDController1_N_l;         // Mask Parameter: PIDController1_N_l
                                          //  Referenced by: '<S265>/Filter Coefficient'

    real_T PIDController2_N_b;         // Mask Parameter: PIDController2_N_b
                                          //  Referenced by: '<S317>/Filter Coefficient'

    real_T PIDController_P;            // Mask Parameter: PIDController_P
                                          //  Referenced by: '<S52>/Proportional Gain'

    real_T PIDController1_P;           // Mask Parameter: PIDController1_P
                                          //  Referenced by: '<S104>/Proportional Gain'

    real_T PIDController2_P;           // Mask Parameter: PIDController2_P
                                          //  Referenced by: '<S156>/Proportional Gain'

    real_T PIDController_P_f;          // Mask Parameter: PIDController_P_f
                                          //  Referenced by: '<S215>/Proportional Gain'

    real_T PIDController1_P_k;         // Mask Parameter: PIDController1_P_k
                                          //  Referenced by: '<S267>/Proportional Gain'

    real_T PIDController2_P_n;         // Mask Parameter: PIDController2_P_n
                                          //  Referenced by: '<S319>/Proportional Gain'

    real_T Integrator_IC;              // Expression: 0
                                          //  Referenced by: '<S1>/Integrator'

    real_T Saturation_UpperSat;        // Expression: 0.90
                                          //  Referenced by: '<S12>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 0.15
                                          //  Referenced by: '<S12>/Saturation'

    real_T Constant_Value[4];          // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S3>/Constant'

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

    real_T CovProzessrauschen_Value[4];// Expression: [0.001 0; 0 100]
                                          //  Referenced by: '<S3>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition[4];// Expression: 1 * eye(2, 2)
                                            //  Referenced by: '<S3>/Unit Delay'

    real_T Constant_Value_b[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S4>/Constant'

    real_T Constant1_Value_p[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S4>/Constant1'

    real_T Constant2_Value_d[2];       // Expression: [1 0]
                                          //  Referenced by: '<S4>/Constant2'

    real_T CovMessrauschen_Value_c;    // Expression: 10e-6
                                          //  Referenced by: '<S4>/Cov Messrauschen'

    real_T Constant5_Value_c;          // Expression: 0
                                          //  Referenced by: '<S4>/Constant5'

    real_T UnitDelay1_InitialCondition_m[2];// Expression: [0; 0]
                                               //  Referenced by: '<S4>/Unit Delay1'

    real_T CovProzessrauschen_Value_l[4];// Expression: [1 0; 0 10e-3]
                                            //  Referenced by: '<S4>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_p[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S4>/Unit Delay'

    real_T Constant_Value_e[4];        // Expression: [1 0.005; 0 1]
                                          //  Referenced by: '<S6>/Constant'

    real_T Constant1_Value_n[2];       // Expression: [1; 0]
                                          //  Referenced by: '<S6>/Constant1'

    real_T Constant2_Value_g[2];       // Expression: [1 0]
                                          //  Referenced by: '<S6>/Constant2'

    real_T CovMessrauschen_Value_n;    // Expression: 10e-6
                                          //  Referenced by: '<S6>/Cov Messrauschen'

    real_T Constant5_Value_d;          // Expression: 0
                                          //  Referenced by: '<S6>/Constant5'

    real_T UnitDelay1_InitialCondition_i[2];// Expression: [0; 0]
                                               //  Referenced by: '<S6>/Unit Delay1'

    real_T CovProzessrauschen_Value_p[4];// Expression: [1 0; 0 10e-3]
                                            //  Referenced by: '<S6>/Cov Prozessrauschen'

    real_T UnitDelay_InitialCondition_m[4];// Expression: 1 * eye(2, 2)
                                              //  Referenced by: '<S6>/Unit Delay'

    real_T Saturation_UpperSat_o;      // Expression: 0.90
                                          //  Referenced by: '<S175>/Saturation'

    real_T Saturation_LowerSat_g;      // Expression: 0.15
                                          //  Referenced by: '<S175>/Saturation'

    real_T Integrator_IC_c;            // Expression: 0
                                          //  Referenced by: '<Root>/Integrator'

    real_T Integrator1_IC;             // Expression: 0
                                          //  Referenced by: '<S3>/Integrator1'

    real_T Integrator1_IC_n;           // Expression: 0
                                          //  Referenced by: '<S4>/Integrator1'

    real_T Integrator1_IC_e;           // Expression: 0
                                          //  Referenced by: '<S6>/Integrator1'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[24];
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
    real_T odeF[1][24];
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
//  Block '<S1>/Transfer Fcn' : Unused code path elimination
//  Block '<S1>/Transfer Fcn1' : Unused code path elimination
//  Block '<S1>/Transfer Fcn2' : Unused code path elimination
//  Block '<S1>/Transfer Fcn3' : Unused code path elimination
//  Block '<S12>/Scope' : Unused code path elimination
//  Block '<S12>/Scope1' : Unused code path elimination
//  Block '<S3>/Scope' : Unused code path elimination
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S175>/Scope' : Unused code path elimination
//  Block '<S175>/Scope1' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination


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
//  '<S1>'   : 'controller_3dof/Subsystem Reference'
//  '<S2>'   : 'controller_3dof/Subsystem Reference1'
//  '<S3>'   : 'controller_3dof/Subsystem1'
//  '<S4>'   : 'controller_3dof/Subsystem2'
//  '<S5>'   : 'controller_3dof/Subsystem3'
//  '<S6>'   : 'controller_3dof/Subsystem4'
//  '<S7>'   : 'controller_3dof/Subsystem Reference/MATLAB Function1'
//  '<S8>'   : 'controller_3dof/Subsystem Reference/MATLAB Function2'
//  '<S9>'   : 'controller_3dof/Subsystem Reference1/PID Controller'
//  '<S10>'  : 'controller_3dof/Subsystem Reference1/PID Controller1'
//  '<S11>'  : 'controller_3dof/Subsystem Reference1/PID Controller2'
//  '<S12>'  : 'controller_3dof/Subsystem Reference1/Subsystem'
//  '<S13>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Anti-windup'
//  '<S14>'  : 'controller_3dof/Subsystem Reference1/PID Controller/D Gain'
//  '<S15>'  : 'controller_3dof/Subsystem Reference1/PID Controller/External Derivative'
//  '<S16>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Filter'
//  '<S17>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Filter ICs'
//  '<S18>'  : 'controller_3dof/Subsystem Reference1/PID Controller/I Gain'
//  '<S19>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Ideal P Gain'
//  '<S20>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Ideal P Gain Fdbk'
//  '<S21>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Integrator'
//  '<S22>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Integrator ICs'
//  '<S23>'  : 'controller_3dof/Subsystem Reference1/PID Controller/N Copy'
//  '<S24>'  : 'controller_3dof/Subsystem Reference1/PID Controller/N Gain'
//  '<S25>'  : 'controller_3dof/Subsystem Reference1/PID Controller/P Copy'
//  '<S26>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Parallel P Gain'
//  '<S27>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Reset Signal'
//  '<S28>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Saturation'
//  '<S29>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Saturation Fdbk'
//  '<S30>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Sum'
//  '<S31>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Sum Fdbk'
//  '<S32>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tracking Mode'
//  '<S33>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tracking Mode Sum'
//  '<S34>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tsamp - Integral'
//  '<S35>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tsamp - Ngain'
//  '<S36>'  : 'controller_3dof/Subsystem Reference1/PID Controller/postSat Signal'
//  '<S37>'  : 'controller_3dof/Subsystem Reference1/PID Controller/preInt Signal'
//  '<S38>'  : 'controller_3dof/Subsystem Reference1/PID Controller/preSat Signal'
//  '<S39>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Anti-windup/Passthrough'
//  '<S40>'  : 'controller_3dof/Subsystem Reference1/PID Controller/D Gain/Internal Parameters'
//  '<S41>'  : 'controller_3dof/Subsystem Reference1/PID Controller/External Derivative/External Ydot'
//  '<S42>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Filter/Cont. Filter Only'
//  '<S43>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S44>'  : 'controller_3dof/Subsystem Reference1/PID Controller/I Gain/Internal Parameters'
//  '<S45>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Ideal P Gain/Passthrough'
//  '<S46>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S47>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Integrator/Continuous'
//  '<S48>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Integrator ICs/Internal IC'
//  '<S49>'  : 'controller_3dof/Subsystem Reference1/PID Controller/N Copy/Disabled'
//  '<S50>'  : 'controller_3dof/Subsystem Reference1/PID Controller/N Gain/Internal Parameters'
//  '<S51>'  : 'controller_3dof/Subsystem Reference1/PID Controller/P Copy/Disabled'
//  '<S52>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S53>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Reset Signal/Disabled'
//  '<S54>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Saturation/Passthrough'
//  '<S55>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Saturation Fdbk/Disabled'
//  '<S56>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Sum/Sum_PID'
//  '<S57>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Sum Fdbk/Disabled'
//  '<S58>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tracking Mode/Disabled'
//  '<S59>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S60>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S61>'  : 'controller_3dof/Subsystem Reference1/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S62>'  : 'controller_3dof/Subsystem Reference1/PID Controller/postSat Signal/Forward_Path'
//  '<S63>'  : 'controller_3dof/Subsystem Reference1/PID Controller/preInt Signal/Internal PreInt'
//  '<S64>'  : 'controller_3dof/Subsystem Reference1/PID Controller/preSat Signal/Forward_Path'
//  '<S65>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Anti-windup'
//  '<S66>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/D Gain'
//  '<S67>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/External Derivative'
//  '<S68>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Filter'
//  '<S69>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Filter ICs'
//  '<S70>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/I Gain'
//  '<S71>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Ideal P Gain'
//  '<S72>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Ideal P Gain Fdbk'
//  '<S73>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Integrator'
//  '<S74>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Integrator ICs'
//  '<S75>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/N Copy'
//  '<S76>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/N Gain'
//  '<S77>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/P Copy'
//  '<S78>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Parallel P Gain'
//  '<S79>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Reset Signal'
//  '<S80>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Saturation'
//  '<S81>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Saturation Fdbk'
//  '<S82>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Sum'
//  '<S83>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Sum Fdbk'
//  '<S84>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Tracking Mode'
//  '<S85>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Tracking Mode Sum'
//  '<S86>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Tsamp - Integral'
//  '<S87>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Tsamp - Ngain'
//  '<S88>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/postSat Signal'
//  '<S89>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/preInt Signal'
//  '<S90>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/preSat Signal'
//  '<S91>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Anti-windup/Passthrough'
//  '<S92>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/D Gain/Internal Parameters'
//  '<S93>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/External Derivative/Error'
//  '<S94>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Filter/Cont. Filter'
//  '<S95>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S96>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/I Gain/Internal Parameters'
//  '<S97>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Ideal P Gain/Passthrough'
//  '<S98>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S99>'  : 'controller_3dof/Subsystem Reference1/PID Controller1/Integrator/Continuous'
//  '<S100>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Integrator ICs/Internal IC'
//  '<S101>' : 'controller_3dof/Subsystem Reference1/PID Controller1/N Copy/Disabled'
//  '<S102>' : 'controller_3dof/Subsystem Reference1/PID Controller1/N Gain/Internal Parameters'
//  '<S103>' : 'controller_3dof/Subsystem Reference1/PID Controller1/P Copy/Disabled'
//  '<S104>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S105>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Reset Signal/Disabled'
//  '<S106>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Saturation/Passthrough'
//  '<S107>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Saturation Fdbk/Disabled'
//  '<S108>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Sum/Sum_PID'
//  '<S109>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Sum Fdbk/Disabled'
//  '<S110>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Tracking Mode/Disabled'
//  '<S111>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S112>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S113>' : 'controller_3dof/Subsystem Reference1/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S114>' : 'controller_3dof/Subsystem Reference1/PID Controller1/postSat Signal/Forward_Path'
//  '<S115>' : 'controller_3dof/Subsystem Reference1/PID Controller1/preInt Signal/Internal PreInt'
//  '<S116>' : 'controller_3dof/Subsystem Reference1/PID Controller1/preSat Signal/Forward_Path'
//  '<S117>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Anti-windup'
//  '<S118>' : 'controller_3dof/Subsystem Reference1/PID Controller2/D Gain'
//  '<S119>' : 'controller_3dof/Subsystem Reference1/PID Controller2/External Derivative'
//  '<S120>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Filter'
//  '<S121>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Filter ICs'
//  '<S122>' : 'controller_3dof/Subsystem Reference1/PID Controller2/I Gain'
//  '<S123>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Ideal P Gain'
//  '<S124>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Ideal P Gain Fdbk'
//  '<S125>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Integrator'
//  '<S126>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Integrator ICs'
//  '<S127>' : 'controller_3dof/Subsystem Reference1/PID Controller2/N Copy'
//  '<S128>' : 'controller_3dof/Subsystem Reference1/PID Controller2/N Gain'
//  '<S129>' : 'controller_3dof/Subsystem Reference1/PID Controller2/P Copy'
//  '<S130>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Parallel P Gain'
//  '<S131>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Reset Signal'
//  '<S132>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Saturation'
//  '<S133>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Saturation Fdbk'
//  '<S134>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Sum'
//  '<S135>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Sum Fdbk'
//  '<S136>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tracking Mode'
//  '<S137>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tracking Mode Sum'
//  '<S138>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tsamp - Integral'
//  '<S139>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tsamp - Ngain'
//  '<S140>' : 'controller_3dof/Subsystem Reference1/PID Controller2/postSat Signal'
//  '<S141>' : 'controller_3dof/Subsystem Reference1/PID Controller2/preInt Signal'
//  '<S142>' : 'controller_3dof/Subsystem Reference1/PID Controller2/preSat Signal'
//  '<S143>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Anti-windup/Passthrough'
//  '<S144>' : 'controller_3dof/Subsystem Reference1/PID Controller2/D Gain/Internal Parameters'
//  '<S145>' : 'controller_3dof/Subsystem Reference1/PID Controller2/External Derivative/Error'
//  '<S146>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Filter/Cont. Filter'
//  '<S147>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S148>' : 'controller_3dof/Subsystem Reference1/PID Controller2/I Gain/Internal Parameters'
//  '<S149>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Ideal P Gain/Passthrough'
//  '<S150>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S151>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Integrator/Continuous'
//  '<S152>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Integrator ICs/Internal IC'
//  '<S153>' : 'controller_3dof/Subsystem Reference1/PID Controller2/N Copy/Disabled'
//  '<S154>' : 'controller_3dof/Subsystem Reference1/PID Controller2/N Gain/Internal Parameters'
//  '<S155>' : 'controller_3dof/Subsystem Reference1/PID Controller2/P Copy/Disabled'
//  '<S156>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S157>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Reset Signal/Disabled'
//  '<S158>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Saturation/Passthrough'
//  '<S159>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Saturation Fdbk/Disabled'
//  '<S160>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Sum/Sum_PID'
//  '<S161>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Sum Fdbk/Disabled'
//  '<S162>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tracking Mode/Disabled'
//  '<S163>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S164>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S165>' : 'controller_3dof/Subsystem Reference1/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S166>' : 'controller_3dof/Subsystem Reference1/PID Controller2/postSat Signal/Forward_Path'
//  '<S167>' : 'controller_3dof/Subsystem Reference1/PID Controller2/preInt Signal/Internal PreInt'
//  '<S168>' : 'controller_3dof/Subsystem Reference1/PID Controller2/preSat Signal/Forward_Path'
//  '<S169>' : 'controller_3dof/Subsystem Reference1/Subsystem/MATLAB Function'
//  '<S170>' : 'controller_3dof/Subsystem1/KF_Elevation'
//  '<S171>' : 'controller_3dof/Subsystem2/KF_Elevation'
//  '<S172>' : 'controller_3dof/Subsystem3/PID Controller'
//  '<S173>' : 'controller_3dof/Subsystem3/PID Controller1'
//  '<S174>' : 'controller_3dof/Subsystem3/PID Controller2'
//  '<S175>' : 'controller_3dof/Subsystem3/Subsystem'
//  '<S176>' : 'controller_3dof/Subsystem3/PID Controller/Anti-windup'
//  '<S177>' : 'controller_3dof/Subsystem3/PID Controller/D Gain'
//  '<S178>' : 'controller_3dof/Subsystem3/PID Controller/External Derivative'
//  '<S179>' : 'controller_3dof/Subsystem3/PID Controller/Filter'
//  '<S180>' : 'controller_3dof/Subsystem3/PID Controller/Filter ICs'
//  '<S181>' : 'controller_3dof/Subsystem3/PID Controller/I Gain'
//  '<S182>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain'
//  '<S183>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S184>' : 'controller_3dof/Subsystem3/PID Controller/Integrator'
//  '<S185>' : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs'
//  '<S186>' : 'controller_3dof/Subsystem3/PID Controller/N Copy'
//  '<S187>' : 'controller_3dof/Subsystem3/PID Controller/N Gain'
//  '<S188>' : 'controller_3dof/Subsystem3/PID Controller/P Copy'
//  '<S189>' : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain'
//  '<S190>' : 'controller_3dof/Subsystem3/PID Controller/Reset Signal'
//  '<S191>' : 'controller_3dof/Subsystem3/PID Controller/Saturation'
//  '<S192>' : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S193>' : 'controller_3dof/Subsystem3/PID Controller/Sum'
//  '<S194>' : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk'
//  '<S195>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode'
//  '<S196>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S197>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S198>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S199>' : 'controller_3dof/Subsystem3/PID Controller/postSat Signal'
//  '<S200>' : 'controller_3dof/Subsystem3/PID Controller/preInt Signal'
//  '<S201>' : 'controller_3dof/Subsystem3/PID Controller/preSat Signal'
//  '<S202>' : 'controller_3dof/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S203>' : 'controller_3dof/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S204>' : 'controller_3dof/Subsystem3/PID Controller/External Derivative/External Ydot'
//  '<S205>' : 'controller_3dof/Subsystem3/PID Controller/Filter/Cont. Filter Only'
//  '<S206>' : 'controller_3dof/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S207>' : 'controller_3dof/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S208>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S209>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S210>' : 'controller_3dof/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S211>' : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S212>' : 'controller_3dof/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S213>' : 'controller_3dof/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S214>' : 'controller_3dof/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S215>' : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S216>' : 'controller_3dof/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S217>' : 'controller_3dof/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S218>' : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S219>' : 'controller_3dof/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S220>' : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S221>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S222>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S223>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S224>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S225>' : 'controller_3dof/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S226>' : 'controller_3dof/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S227>' : 'controller_3dof/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S228>' : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup'
//  '<S229>' : 'controller_3dof/Subsystem3/PID Controller1/D Gain'
//  '<S230>' : 'controller_3dof/Subsystem3/PID Controller1/External Derivative'
//  '<S231>' : 'controller_3dof/Subsystem3/PID Controller1/Filter'
//  '<S232>' : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs'
//  '<S233>' : 'controller_3dof/Subsystem3/PID Controller1/I Gain'
//  '<S234>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S235>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S236>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator'
//  '<S237>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs'
//  '<S238>' : 'controller_3dof/Subsystem3/PID Controller1/N Copy'
//  '<S239>' : 'controller_3dof/Subsystem3/PID Controller1/N Gain'
//  '<S240>' : 'controller_3dof/Subsystem3/PID Controller1/P Copy'
//  '<S241>' : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S242>' : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal'
//  '<S243>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation'
//  '<S244>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S245>' : 'controller_3dof/Subsystem3/PID Controller1/Sum'
//  '<S246>' : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S247>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode'
//  '<S248>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S249>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S250>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S251>' : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal'
//  '<S252>' : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal'
//  '<S253>' : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal'
//  '<S254>' : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S255>' : 'controller_3dof/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S256>' : 'controller_3dof/Subsystem3/PID Controller1/External Derivative/Error'
//  '<S257>' : 'controller_3dof/Subsystem3/PID Controller1/Filter/Cont. Filter'
//  '<S258>' : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S259>' : 'controller_3dof/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S260>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S261>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S262>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S263>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S264>' : 'controller_3dof/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S265>' : 'controller_3dof/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S266>' : 'controller_3dof/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S267>' : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S268>' : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S269>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S270>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S271>' : 'controller_3dof/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S272>' : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S273>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S274>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S275>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S276>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S277>' : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S278>' : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S279>' : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S280>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup'
//  '<S281>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain'
//  '<S282>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative'
//  '<S283>' : 'controller_3dof/Subsystem3/PID Controller2/Filter'
//  '<S284>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs'
//  '<S285>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain'
//  '<S286>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S287>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S288>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator'
//  '<S289>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs'
//  '<S290>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy'
//  '<S291>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain'
//  '<S292>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy'
//  '<S293>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S294>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal'
//  '<S295>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation'
//  '<S296>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S297>' : 'controller_3dof/Subsystem3/PID Controller2/Sum'
//  '<S298>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S299>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode'
//  '<S300>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S301>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S302>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S303>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal'
//  '<S304>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal'
//  '<S305>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal'
//  '<S306>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S307>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S308>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative/Error'
//  '<S309>' : 'controller_3dof/Subsystem3/PID Controller2/Filter/Cont. Filter'
//  '<S310>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S311>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S312>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S313>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S314>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S315>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S316>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S317>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S318>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S319>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S320>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S321>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S322>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S323>' : 'controller_3dof/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S324>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S325>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S326>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S327>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S328>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S329>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S330>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S331>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S332>' : 'controller_3dof/Subsystem3/Subsystem/MATLAB Function'
//  '<S333>' : 'controller_3dof/Subsystem4/KF_Elevation'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
