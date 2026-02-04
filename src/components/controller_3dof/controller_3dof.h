//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.281
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Feb  4 17:22:20 2026
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
    real_T dx[6];                      // '<S1>/MATLAB Function2'
    real_T FilterCoefficient;          // '<S47>/Filter Coefficient'
    real_T FilterCoefficient_g;        // '<S99>/Filter Coefficient'
    real_T FilterCoefficient_e;        // '<S151>/Filter Coefficient'
    real_T IntegralGain;               // '<S145>/Integral Gain'
    real_T IntegralGain_b;             // '<S93>/Integral Gain'
    real_T IntegralGain_f;             // '<S41>/Integral Gain'
    real_T FilterCoefficient_b;        // '<S208>/Filter Coefficient'
    real_T FilterCoefficient_bz;       // '<S260>/Filter Coefficient'
    real_T FilterCoefficient_a;        // '<S312>/Filter Coefficient'
    real_T IntegralGain_p;             // '<S306>/Integral Gain'
    real_T IntegralGain_o;             // '<S254>/Integral Gain'
    real_T IntegralGain_od;            // '<S202>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_b;        // '<S44>/Integrator'
    real_T Filter_CSTATE;              // '<S39>/Filter'
    real_T Integrator_CSTATE_n;        // '<S96>/Integrator'
    real_T Filter_CSTATE_d;            // '<S91>/Filter'
    real_T Integrator_CSTATE_f;        // '<S148>/Integrator'
    real_T Filter_CSTATE_a;            // '<S143>/Filter'
    real_T Integrator_CSTATE_p;        // '<S205>/Integrator'
    real_T Filter_CSTATE_g;            // '<S200>/Filter'
    real_T Integrator_CSTATE_i;        // '<S257>/Integrator'
    real_T Filter_CSTATE_m;            // '<S252>/Filter'
    real_T Integrator_CSTATE_j;        // '<S309>/Integrator'
    real_T Filter_CSTATE_c;            // '<S304>/Filter'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE[6];       // '<S1>/Integrator'
    real_T Integrator_CSTATE_b;        // '<S44>/Integrator'
    real_T Filter_CSTATE;              // '<S39>/Filter'
    real_T Integrator_CSTATE_n;        // '<S96>/Integrator'
    real_T Filter_CSTATE_d;            // '<S91>/Filter'
    real_T Integrator_CSTATE_f;        // '<S148>/Integrator'
    real_T Filter_CSTATE_a;            // '<S143>/Filter'
    real_T Integrator_CSTATE_p;        // '<S205>/Integrator'
    real_T Filter_CSTATE_g;            // '<S200>/Filter'
    real_T Integrator_CSTATE_i;        // '<S257>/Integrator'
    real_T Filter_CSTATE_m;            // '<S252>/Filter'
    real_T Integrator_CSTATE_j;        // '<S309>/Integrator'
    real_T Filter_CSTATE_c;            // '<S304>/Filter'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE[6];    // '<S1>/Integrator'
    boolean_T Integrator_CSTATE_b;     // '<S44>/Integrator'
    boolean_T Filter_CSTATE;           // '<S39>/Filter'
    boolean_T Integrator_CSTATE_n;     // '<S96>/Integrator'
    boolean_T Filter_CSTATE_d;         // '<S91>/Filter'
    boolean_T Integrator_CSTATE_f;     // '<S148>/Integrator'
    boolean_T Filter_CSTATE_a;         // '<S143>/Filter'
    boolean_T Integrator_CSTATE_p;     // '<S205>/Integrator'
    boolean_T Filter_CSTATE_g;         // '<S200>/Filter'
    boolean_T Integrator_CSTATE_i;     // '<S257>/Integrator'
    boolean_T Filter_CSTATE_m;         // '<S252>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S309>/Integrator'
    boolean_T Filter_CSTATE_c;         // '<S304>/Filter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T w[4];                       // '<Root>/w'
    real_T y[3];                       // '<Root>/y'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T u[4];                       // '<Root>/u'
    real_T y_pred[3];                  // '<Root>/y_pred'
  };

  // Parameters (default storage)
  struct P {
    real_T E[16];                      // Variable: E
                                          //  Referenced by:
                                          //    '<S1>/Mixer'
                                          //    '<S9>/MATLAB Function'
                                          //    '<S170>/MATLAB Function'

    real_T I[9];                       // Variable: I
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T a;                          // Variable: a
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S9>/MATLAB Function'
                                          //    '<S170>/MATLAB Function'

    real_T b;                          // Variable: b
                                          //  Referenced by:
                                          //    '<S1>/MATLAB Function1'
                                          //    '<S9>/MATLAB Function'
                                          //    '<S170>/MATLAB Function'

    real_T d;                          // Variable: d
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T g;                          // Variable: g
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T guenther;                   // Variable: guenther
                                          //  Referenced by: '<S1>/MATLAB Function1'

    real_T m;                          // Variable: m
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T p;                          // Variable: p
                                          //  Referenced by: '<S1>/MATLAB Function2'

    real_T PIDController_D;            // Mask Parameter: PIDController_D
                                          //  Referenced by: '<S37>/Derivative Gain'

    real_T PIDController1_D;           // Mask Parameter: PIDController1_D
                                          //  Referenced by: '<S89>/Derivative Gain'

    real_T PIDController2_D;           // Mask Parameter: PIDController2_D
                                          //  Referenced by: '<S141>/Derivative Gain'

    real_T PIDController_D_c;          // Mask Parameter: PIDController_D_c
                                          //  Referenced by: '<S198>/Derivative Gain'

    real_T PIDController1_D_k;         // Mask Parameter: PIDController1_D_k
                                          //  Referenced by: '<S250>/Derivative Gain'

    real_T PIDController2_D_m;         // Mask Parameter: PIDController2_D_m
                                          //  Referenced by: '<S302>/Derivative Gain'

    real_T PIDController2_I;           // Mask Parameter: PIDController2_I
                                          //  Referenced by: '<S145>/Integral Gain'

    real_T PIDController1_I;           // Mask Parameter: PIDController1_I
                                          //  Referenced by: '<S93>/Integral Gain'

    real_T PIDController_I;            // Mask Parameter: PIDController_I
                                          //  Referenced by: '<S41>/Integral Gain'

    real_T PIDController2_I_i;         // Mask Parameter: PIDController2_I_i
                                          //  Referenced by: '<S306>/Integral Gain'

    real_T PIDController1_I_m;         // Mask Parameter: PIDController1_I_m
                                          //  Referenced by: '<S254>/Integral Gain'

    real_T PIDController_I_a;          // Mask Parameter: PIDController_I_a
                                          //  Referenced by: '<S202>/Integral Gain'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S39>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S91>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S143>/Filter'

    real_T PIDController_InitialConditio_e;
                              // Mask Parameter: PIDController_InitialConditio_e
                                 //  Referenced by: '<S200>/Filter'

    real_T PIDController1_InitialConditi_j;
                              // Mask Parameter: PIDController1_InitialConditi_j
                                 //  Referenced by: '<S252>/Filter'

    real_T PIDController2_InitialConditi_e;
                              // Mask Parameter: PIDController2_InitialConditi_e
                                 //  Referenced by: '<S304>/Filter'

    real_T PIDController_InitialConditio_g;
                              // Mask Parameter: PIDController_InitialConditio_g
                                 //  Referenced by: '<S44>/Integrator'

    real_T PIDController1_InitialConditi_k;
                              // Mask Parameter: PIDController1_InitialConditi_k
                                 //  Referenced by: '<S96>/Integrator'

    real_T PIDController2_InitialConditi_p;
                              // Mask Parameter: PIDController2_InitialConditi_p
                                 //  Referenced by: '<S148>/Integrator'

    real_T PIDController_InitialConditio_d;
                              // Mask Parameter: PIDController_InitialConditio_d
                                 //  Referenced by: '<S205>/Integrator'

    real_T PIDController1_InitialConditi_m;
                              // Mask Parameter: PIDController1_InitialConditi_m
                                 //  Referenced by: '<S257>/Integrator'

    real_T PIDController2_InitialConditi_o;
                              // Mask Parameter: PIDController2_InitialConditi_o
                                 //  Referenced by: '<S309>/Integrator'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S47>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S99>/Filter Coefficient'

    real_T PIDController2_N;           // Mask Parameter: PIDController2_N
                                          //  Referenced by: '<S151>/Filter Coefficient'

    real_T PIDController_N_o;          // Mask Parameter: PIDController_N_o
                                          //  Referenced by: '<S208>/Filter Coefficient'

    real_T PIDController1_N_l;         // Mask Parameter: PIDController1_N_l
                                          //  Referenced by: '<S260>/Filter Coefficient'

    real_T PIDController2_N_b;         // Mask Parameter: PIDController2_N_b
                                          //  Referenced by: '<S312>/Filter Coefficient'

    real_T PIDController_P;            // Mask Parameter: PIDController_P
                                          //  Referenced by: '<S49>/Proportional Gain'

    real_T PIDController1_P;           // Mask Parameter: PIDController1_P
                                          //  Referenced by: '<S101>/Proportional Gain'

    real_T PIDController2_P;           // Mask Parameter: PIDController2_P
                                          //  Referenced by: '<S153>/Proportional Gain'

    real_T PIDController_P_f;          // Mask Parameter: PIDController_P_f
                                          //  Referenced by: '<S210>/Proportional Gain'

    real_T PIDController1_P_k;         // Mask Parameter: PIDController1_P_k
                                          //  Referenced by: '<S262>/Proportional Gain'

    real_T PIDController2_P_n;         // Mask Parameter: PIDController2_P_n
                                          //  Referenced by: '<S314>/Proportional Gain'

    real_T Integrator_IC;              // Expression: 0
                                          //  Referenced by: '<S1>/Integrator'

    real_T Saturation_UpperSat;        // Expression: 90
                                          //  Referenced by: '<S9>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 15
                                          //  Referenced by: '<S9>/Saturation'

    real_T TransferFcn_D;              // Computed Parameter: TransferFcn_D
                                          //  Referenced by: '<S1>/Transfer Fcn'

    real_T TransferFcn1_D;             // Computed Parameter: TransferFcn1_D
                                          //  Referenced by: '<S1>/Transfer Fcn1'

    real_T TransferFcn2_D;             // Computed Parameter: TransferFcn2_D
                                          //  Referenced by: '<S1>/Transfer Fcn2'

    real_T TransferFcn3_D;             // Computed Parameter: TransferFcn3_D
                                          //  Referenced by: '<S1>/Transfer Fcn3'

    real_T Saturation_UpperSat_o;      // Expression: 90
                                          //  Referenced by: '<S170>/Saturation'

    real_T Saturation_LowerSat_g;      // Expression: 15
                                          //  Referenced by: '<S170>/Saturation'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[18];
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
    real_T odeF[1][18];
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
//  Block '<S9>/Scope' : Unused code path elimination
//  Block '<S9>/Scope1' : Unused code path elimination
//  Block '<S170>/Scope' : Unused code path elimination
//  Block '<S170>/Scope1' : Unused code path elimination


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
//  '<S2>'   : 'controller_3dof/Subsystem1'
//  '<S3>'   : 'controller_3dof/Subsystem3'
//  '<S4>'   : 'controller_3dof/Subsystem Reference/MATLAB Function1'
//  '<S5>'   : 'controller_3dof/Subsystem Reference/MATLAB Function2'
//  '<S6>'   : 'controller_3dof/Subsystem1/PID Controller'
//  '<S7>'   : 'controller_3dof/Subsystem1/PID Controller1'
//  '<S8>'   : 'controller_3dof/Subsystem1/PID Controller2'
//  '<S9>'   : 'controller_3dof/Subsystem1/Subsystem'
//  '<S10>'  : 'controller_3dof/Subsystem1/PID Controller/Anti-windup'
//  '<S11>'  : 'controller_3dof/Subsystem1/PID Controller/D Gain'
//  '<S12>'  : 'controller_3dof/Subsystem1/PID Controller/External Derivative'
//  '<S13>'  : 'controller_3dof/Subsystem1/PID Controller/Filter'
//  '<S14>'  : 'controller_3dof/Subsystem1/PID Controller/Filter ICs'
//  '<S15>'  : 'controller_3dof/Subsystem1/PID Controller/I Gain'
//  '<S16>'  : 'controller_3dof/Subsystem1/PID Controller/Ideal P Gain'
//  '<S17>'  : 'controller_3dof/Subsystem1/PID Controller/Ideal P Gain Fdbk'
//  '<S18>'  : 'controller_3dof/Subsystem1/PID Controller/Integrator'
//  '<S19>'  : 'controller_3dof/Subsystem1/PID Controller/Integrator ICs'
//  '<S20>'  : 'controller_3dof/Subsystem1/PID Controller/N Copy'
//  '<S21>'  : 'controller_3dof/Subsystem1/PID Controller/N Gain'
//  '<S22>'  : 'controller_3dof/Subsystem1/PID Controller/P Copy'
//  '<S23>'  : 'controller_3dof/Subsystem1/PID Controller/Parallel P Gain'
//  '<S24>'  : 'controller_3dof/Subsystem1/PID Controller/Reset Signal'
//  '<S25>'  : 'controller_3dof/Subsystem1/PID Controller/Saturation'
//  '<S26>'  : 'controller_3dof/Subsystem1/PID Controller/Saturation Fdbk'
//  '<S27>'  : 'controller_3dof/Subsystem1/PID Controller/Sum'
//  '<S28>'  : 'controller_3dof/Subsystem1/PID Controller/Sum Fdbk'
//  '<S29>'  : 'controller_3dof/Subsystem1/PID Controller/Tracking Mode'
//  '<S30>'  : 'controller_3dof/Subsystem1/PID Controller/Tracking Mode Sum'
//  '<S31>'  : 'controller_3dof/Subsystem1/PID Controller/Tsamp - Integral'
//  '<S32>'  : 'controller_3dof/Subsystem1/PID Controller/Tsamp - Ngain'
//  '<S33>'  : 'controller_3dof/Subsystem1/PID Controller/postSat Signal'
//  '<S34>'  : 'controller_3dof/Subsystem1/PID Controller/preInt Signal'
//  '<S35>'  : 'controller_3dof/Subsystem1/PID Controller/preSat Signal'
//  '<S36>'  : 'controller_3dof/Subsystem1/PID Controller/Anti-windup/Passthrough'
//  '<S37>'  : 'controller_3dof/Subsystem1/PID Controller/D Gain/Internal Parameters'
//  '<S38>'  : 'controller_3dof/Subsystem1/PID Controller/External Derivative/Error'
//  '<S39>'  : 'controller_3dof/Subsystem1/PID Controller/Filter/Cont. Filter'
//  '<S40>'  : 'controller_3dof/Subsystem1/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S41>'  : 'controller_3dof/Subsystem1/PID Controller/I Gain/Internal Parameters'
//  '<S42>'  : 'controller_3dof/Subsystem1/PID Controller/Ideal P Gain/Passthrough'
//  '<S43>'  : 'controller_3dof/Subsystem1/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S44>'  : 'controller_3dof/Subsystem1/PID Controller/Integrator/Continuous'
//  '<S45>'  : 'controller_3dof/Subsystem1/PID Controller/Integrator ICs/Internal IC'
//  '<S46>'  : 'controller_3dof/Subsystem1/PID Controller/N Copy/Disabled'
//  '<S47>'  : 'controller_3dof/Subsystem1/PID Controller/N Gain/Internal Parameters'
//  '<S48>'  : 'controller_3dof/Subsystem1/PID Controller/P Copy/Disabled'
//  '<S49>'  : 'controller_3dof/Subsystem1/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S50>'  : 'controller_3dof/Subsystem1/PID Controller/Reset Signal/Disabled'
//  '<S51>'  : 'controller_3dof/Subsystem1/PID Controller/Saturation/Passthrough'
//  '<S52>'  : 'controller_3dof/Subsystem1/PID Controller/Saturation Fdbk/Disabled'
//  '<S53>'  : 'controller_3dof/Subsystem1/PID Controller/Sum/Sum_PID'
//  '<S54>'  : 'controller_3dof/Subsystem1/PID Controller/Sum Fdbk/Disabled'
//  '<S55>'  : 'controller_3dof/Subsystem1/PID Controller/Tracking Mode/Disabled'
//  '<S56>'  : 'controller_3dof/Subsystem1/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S57>'  : 'controller_3dof/Subsystem1/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S58>'  : 'controller_3dof/Subsystem1/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S59>'  : 'controller_3dof/Subsystem1/PID Controller/postSat Signal/Forward_Path'
//  '<S60>'  : 'controller_3dof/Subsystem1/PID Controller/preInt Signal/Internal PreInt'
//  '<S61>'  : 'controller_3dof/Subsystem1/PID Controller/preSat Signal/Forward_Path'
//  '<S62>'  : 'controller_3dof/Subsystem1/PID Controller1/Anti-windup'
//  '<S63>'  : 'controller_3dof/Subsystem1/PID Controller1/D Gain'
//  '<S64>'  : 'controller_3dof/Subsystem1/PID Controller1/External Derivative'
//  '<S65>'  : 'controller_3dof/Subsystem1/PID Controller1/Filter'
//  '<S66>'  : 'controller_3dof/Subsystem1/PID Controller1/Filter ICs'
//  '<S67>'  : 'controller_3dof/Subsystem1/PID Controller1/I Gain'
//  '<S68>'  : 'controller_3dof/Subsystem1/PID Controller1/Ideal P Gain'
//  '<S69>'  : 'controller_3dof/Subsystem1/PID Controller1/Ideal P Gain Fdbk'
//  '<S70>'  : 'controller_3dof/Subsystem1/PID Controller1/Integrator'
//  '<S71>'  : 'controller_3dof/Subsystem1/PID Controller1/Integrator ICs'
//  '<S72>'  : 'controller_3dof/Subsystem1/PID Controller1/N Copy'
//  '<S73>'  : 'controller_3dof/Subsystem1/PID Controller1/N Gain'
//  '<S74>'  : 'controller_3dof/Subsystem1/PID Controller1/P Copy'
//  '<S75>'  : 'controller_3dof/Subsystem1/PID Controller1/Parallel P Gain'
//  '<S76>'  : 'controller_3dof/Subsystem1/PID Controller1/Reset Signal'
//  '<S77>'  : 'controller_3dof/Subsystem1/PID Controller1/Saturation'
//  '<S78>'  : 'controller_3dof/Subsystem1/PID Controller1/Saturation Fdbk'
//  '<S79>'  : 'controller_3dof/Subsystem1/PID Controller1/Sum'
//  '<S80>'  : 'controller_3dof/Subsystem1/PID Controller1/Sum Fdbk'
//  '<S81>'  : 'controller_3dof/Subsystem1/PID Controller1/Tracking Mode'
//  '<S82>'  : 'controller_3dof/Subsystem1/PID Controller1/Tracking Mode Sum'
//  '<S83>'  : 'controller_3dof/Subsystem1/PID Controller1/Tsamp - Integral'
//  '<S84>'  : 'controller_3dof/Subsystem1/PID Controller1/Tsamp - Ngain'
//  '<S85>'  : 'controller_3dof/Subsystem1/PID Controller1/postSat Signal'
//  '<S86>'  : 'controller_3dof/Subsystem1/PID Controller1/preInt Signal'
//  '<S87>'  : 'controller_3dof/Subsystem1/PID Controller1/preSat Signal'
//  '<S88>'  : 'controller_3dof/Subsystem1/PID Controller1/Anti-windup/Passthrough'
//  '<S89>'  : 'controller_3dof/Subsystem1/PID Controller1/D Gain/Internal Parameters'
//  '<S90>'  : 'controller_3dof/Subsystem1/PID Controller1/External Derivative/Error'
//  '<S91>'  : 'controller_3dof/Subsystem1/PID Controller1/Filter/Cont. Filter'
//  '<S92>'  : 'controller_3dof/Subsystem1/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S93>'  : 'controller_3dof/Subsystem1/PID Controller1/I Gain/Internal Parameters'
//  '<S94>'  : 'controller_3dof/Subsystem1/PID Controller1/Ideal P Gain/Passthrough'
//  '<S95>'  : 'controller_3dof/Subsystem1/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S96>'  : 'controller_3dof/Subsystem1/PID Controller1/Integrator/Continuous'
//  '<S97>'  : 'controller_3dof/Subsystem1/PID Controller1/Integrator ICs/Internal IC'
//  '<S98>'  : 'controller_3dof/Subsystem1/PID Controller1/N Copy/Disabled'
//  '<S99>'  : 'controller_3dof/Subsystem1/PID Controller1/N Gain/Internal Parameters'
//  '<S100>' : 'controller_3dof/Subsystem1/PID Controller1/P Copy/Disabled'
//  '<S101>' : 'controller_3dof/Subsystem1/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S102>' : 'controller_3dof/Subsystem1/PID Controller1/Reset Signal/Disabled'
//  '<S103>' : 'controller_3dof/Subsystem1/PID Controller1/Saturation/Passthrough'
//  '<S104>' : 'controller_3dof/Subsystem1/PID Controller1/Saturation Fdbk/Disabled'
//  '<S105>' : 'controller_3dof/Subsystem1/PID Controller1/Sum/Sum_PID'
//  '<S106>' : 'controller_3dof/Subsystem1/PID Controller1/Sum Fdbk/Disabled'
//  '<S107>' : 'controller_3dof/Subsystem1/PID Controller1/Tracking Mode/Disabled'
//  '<S108>' : 'controller_3dof/Subsystem1/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S109>' : 'controller_3dof/Subsystem1/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S110>' : 'controller_3dof/Subsystem1/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S111>' : 'controller_3dof/Subsystem1/PID Controller1/postSat Signal/Forward_Path'
//  '<S112>' : 'controller_3dof/Subsystem1/PID Controller1/preInt Signal/Internal PreInt'
//  '<S113>' : 'controller_3dof/Subsystem1/PID Controller1/preSat Signal/Forward_Path'
//  '<S114>' : 'controller_3dof/Subsystem1/PID Controller2/Anti-windup'
//  '<S115>' : 'controller_3dof/Subsystem1/PID Controller2/D Gain'
//  '<S116>' : 'controller_3dof/Subsystem1/PID Controller2/External Derivative'
//  '<S117>' : 'controller_3dof/Subsystem1/PID Controller2/Filter'
//  '<S118>' : 'controller_3dof/Subsystem1/PID Controller2/Filter ICs'
//  '<S119>' : 'controller_3dof/Subsystem1/PID Controller2/I Gain'
//  '<S120>' : 'controller_3dof/Subsystem1/PID Controller2/Ideal P Gain'
//  '<S121>' : 'controller_3dof/Subsystem1/PID Controller2/Ideal P Gain Fdbk'
//  '<S122>' : 'controller_3dof/Subsystem1/PID Controller2/Integrator'
//  '<S123>' : 'controller_3dof/Subsystem1/PID Controller2/Integrator ICs'
//  '<S124>' : 'controller_3dof/Subsystem1/PID Controller2/N Copy'
//  '<S125>' : 'controller_3dof/Subsystem1/PID Controller2/N Gain'
//  '<S126>' : 'controller_3dof/Subsystem1/PID Controller2/P Copy'
//  '<S127>' : 'controller_3dof/Subsystem1/PID Controller2/Parallel P Gain'
//  '<S128>' : 'controller_3dof/Subsystem1/PID Controller2/Reset Signal'
//  '<S129>' : 'controller_3dof/Subsystem1/PID Controller2/Saturation'
//  '<S130>' : 'controller_3dof/Subsystem1/PID Controller2/Saturation Fdbk'
//  '<S131>' : 'controller_3dof/Subsystem1/PID Controller2/Sum'
//  '<S132>' : 'controller_3dof/Subsystem1/PID Controller2/Sum Fdbk'
//  '<S133>' : 'controller_3dof/Subsystem1/PID Controller2/Tracking Mode'
//  '<S134>' : 'controller_3dof/Subsystem1/PID Controller2/Tracking Mode Sum'
//  '<S135>' : 'controller_3dof/Subsystem1/PID Controller2/Tsamp - Integral'
//  '<S136>' : 'controller_3dof/Subsystem1/PID Controller2/Tsamp - Ngain'
//  '<S137>' : 'controller_3dof/Subsystem1/PID Controller2/postSat Signal'
//  '<S138>' : 'controller_3dof/Subsystem1/PID Controller2/preInt Signal'
//  '<S139>' : 'controller_3dof/Subsystem1/PID Controller2/preSat Signal'
//  '<S140>' : 'controller_3dof/Subsystem1/PID Controller2/Anti-windup/Passthrough'
//  '<S141>' : 'controller_3dof/Subsystem1/PID Controller2/D Gain/Internal Parameters'
//  '<S142>' : 'controller_3dof/Subsystem1/PID Controller2/External Derivative/Error'
//  '<S143>' : 'controller_3dof/Subsystem1/PID Controller2/Filter/Cont. Filter'
//  '<S144>' : 'controller_3dof/Subsystem1/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S145>' : 'controller_3dof/Subsystem1/PID Controller2/I Gain/Internal Parameters'
//  '<S146>' : 'controller_3dof/Subsystem1/PID Controller2/Ideal P Gain/Passthrough'
//  '<S147>' : 'controller_3dof/Subsystem1/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S148>' : 'controller_3dof/Subsystem1/PID Controller2/Integrator/Continuous'
//  '<S149>' : 'controller_3dof/Subsystem1/PID Controller2/Integrator ICs/Internal IC'
//  '<S150>' : 'controller_3dof/Subsystem1/PID Controller2/N Copy/Disabled'
//  '<S151>' : 'controller_3dof/Subsystem1/PID Controller2/N Gain/Internal Parameters'
//  '<S152>' : 'controller_3dof/Subsystem1/PID Controller2/P Copy/Disabled'
//  '<S153>' : 'controller_3dof/Subsystem1/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S154>' : 'controller_3dof/Subsystem1/PID Controller2/Reset Signal/Disabled'
//  '<S155>' : 'controller_3dof/Subsystem1/PID Controller2/Saturation/Passthrough'
//  '<S156>' : 'controller_3dof/Subsystem1/PID Controller2/Saturation Fdbk/Disabled'
//  '<S157>' : 'controller_3dof/Subsystem1/PID Controller2/Sum/Sum_PID'
//  '<S158>' : 'controller_3dof/Subsystem1/PID Controller2/Sum Fdbk/Disabled'
//  '<S159>' : 'controller_3dof/Subsystem1/PID Controller2/Tracking Mode/Disabled'
//  '<S160>' : 'controller_3dof/Subsystem1/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S161>' : 'controller_3dof/Subsystem1/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S162>' : 'controller_3dof/Subsystem1/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S163>' : 'controller_3dof/Subsystem1/PID Controller2/postSat Signal/Forward_Path'
//  '<S164>' : 'controller_3dof/Subsystem1/PID Controller2/preInt Signal/Internal PreInt'
//  '<S165>' : 'controller_3dof/Subsystem1/PID Controller2/preSat Signal/Forward_Path'
//  '<S166>' : 'controller_3dof/Subsystem1/Subsystem/MATLAB Function'
//  '<S167>' : 'controller_3dof/Subsystem3/PID Controller'
//  '<S168>' : 'controller_3dof/Subsystem3/PID Controller1'
//  '<S169>' : 'controller_3dof/Subsystem3/PID Controller2'
//  '<S170>' : 'controller_3dof/Subsystem3/Subsystem'
//  '<S171>' : 'controller_3dof/Subsystem3/PID Controller/Anti-windup'
//  '<S172>' : 'controller_3dof/Subsystem3/PID Controller/D Gain'
//  '<S173>' : 'controller_3dof/Subsystem3/PID Controller/External Derivative'
//  '<S174>' : 'controller_3dof/Subsystem3/PID Controller/Filter'
//  '<S175>' : 'controller_3dof/Subsystem3/PID Controller/Filter ICs'
//  '<S176>' : 'controller_3dof/Subsystem3/PID Controller/I Gain'
//  '<S177>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain'
//  '<S178>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk'
//  '<S179>' : 'controller_3dof/Subsystem3/PID Controller/Integrator'
//  '<S180>' : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs'
//  '<S181>' : 'controller_3dof/Subsystem3/PID Controller/N Copy'
//  '<S182>' : 'controller_3dof/Subsystem3/PID Controller/N Gain'
//  '<S183>' : 'controller_3dof/Subsystem3/PID Controller/P Copy'
//  '<S184>' : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain'
//  '<S185>' : 'controller_3dof/Subsystem3/PID Controller/Reset Signal'
//  '<S186>' : 'controller_3dof/Subsystem3/PID Controller/Saturation'
//  '<S187>' : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk'
//  '<S188>' : 'controller_3dof/Subsystem3/PID Controller/Sum'
//  '<S189>' : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk'
//  '<S190>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode'
//  '<S191>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum'
//  '<S192>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral'
//  '<S193>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain'
//  '<S194>' : 'controller_3dof/Subsystem3/PID Controller/postSat Signal'
//  '<S195>' : 'controller_3dof/Subsystem3/PID Controller/preInt Signal'
//  '<S196>' : 'controller_3dof/Subsystem3/PID Controller/preSat Signal'
//  '<S197>' : 'controller_3dof/Subsystem3/PID Controller/Anti-windup/Passthrough'
//  '<S198>' : 'controller_3dof/Subsystem3/PID Controller/D Gain/Internal Parameters'
//  '<S199>' : 'controller_3dof/Subsystem3/PID Controller/External Derivative/Error'
//  '<S200>' : 'controller_3dof/Subsystem3/PID Controller/Filter/Cont. Filter'
//  '<S201>' : 'controller_3dof/Subsystem3/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S202>' : 'controller_3dof/Subsystem3/PID Controller/I Gain/Internal Parameters'
//  '<S203>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain/Passthrough'
//  '<S204>' : 'controller_3dof/Subsystem3/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S205>' : 'controller_3dof/Subsystem3/PID Controller/Integrator/Continuous'
//  '<S206>' : 'controller_3dof/Subsystem3/PID Controller/Integrator ICs/Internal IC'
//  '<S207>' : 'controller_3dof/Subsystem3/PID Controller/N Copy/Disabled'
//  '<S208>' : 'controller_3dof/Subsystem3/PID Controller/N Gain/Internal Parameters'
//  '<S209>' : 'controller_3dof/Subsystem3/PID Controller/P Copy/Disabled'
//  '<S210>' : 'controller_3dof/Subsystem3/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S211>' : 'controller_3dof/Subsystem3/PID Controller/Reset Signal/Disabled'
//  '<S212>' : 'controller_3dof/Subsystem3/PID Controller/Saturation/Passthrough'
//  '<S213>' : 'controller_3dof/Subsystem3/PID Controller/Saturation Fdbk/Disabled'
//  '<S214>' : 'controller_3dof/Subsystem3/PID Controller/Sum/Sum_PID'
//  '<S215>' : 'controller_3dof/Subsystem3/PID Controller/Sum Fdbk/Disabled'
//  '<S216>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode/Disabled'
//  '<S217>' : 'controller_3dof/Subsystem3/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S218>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S219>' : 'controller_3dof/Subsystem3/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S220>' : 'controller_3dof/Subsystem3/PID Controller/postSat Signal/Forward_Path'
//  '<S221>' : 'controller_3dof/Subsystem3/PID Controller/preInt Signal/Internal PreInt'
//  '<S222>' : 'controller_3dof/Subsystem3/PID Controller/preSat Signal/Forward_Path'
//  '<S223>' : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup'
//  '<S224>' : 'controller_3dof/Subsystem3/PID Controller1/D Gain'
//  '<S225>' : 'controller_3dof/Subsystem3/PID Controller1/External Derivative'
//  '<S226>' : 'controller_3dof/Subsystem3/PID Controller1/Filter'
//  '<S227>' : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs'
//  '<S228>' : 'controller_3dof/Subsystem3/PID Controller1/I Gain'
//  '<S229>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain'
//  '<S230>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk'
//  '<S231>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator'
//  '<S232>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs'
//  '<S233>' : 'controller_3dof/Subsystem3/PID Controller1/N Copy'
//  '<S234>' : 'controller_3dof/Subsystem3/PID Controller1/N Gain'
//  '<S235>' : 'controller_3dof/Subsystem3/PID Controller1/P Copy'
//  '<S236>' : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain'
//  '<S237>' : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal'
//  '<S238>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation'
//  '<S239>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk'
//  '<S240>' : 'controller_3dof/Subsystem3/PID Controller1/Sum'
//  '<S241>' : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk'
//  '<S242>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode'
//  '<S243>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum'
//  '<S244>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral'
//  '<S245>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain'
//  '<S246>' : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal'
//  '<S247>' : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal'
//  '<S248>' : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal'
//  '<S249>' : 'controller_3dof/Subsystem3/PID Controller1/Anti-windup/Passthrough'
//  '<S250>' : 'controller_3dof/Subsystem3/PID Controller1/D Gain/Internal Parameters'
//  '<S251>' : 'controller_3dof/Subsystem3/PID Controller1/External Derivative/Error'
//  '<S252>' : 'controller_3dof/Subsystem3/PID Controller1/Filter/Cont. Filter'
//  '<S253>' : 'controller_3dof/Subsystem3/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S254>' : 'controller_3dof/Subsystem3/PID Controller1/I Gain/Internal Parameters'
//  '<S255>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain/Passthrough'
//  '<S256>' : 'controller_3dof/Subsystem3/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S257>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator/Continuous'
//  '<S258>' : 'controller_3dof/Subsystem3/PID Controller1/Integrator ICs/Internal IC'
//  '<S259>' : 'controller_3dof/Subsystem3/PID Controller1/N Copy/Disabled'
//  '<S260>' : 'controller_3dof/Subsystem3/PID Controller1/N Gain/Internal Parameters'
//  '<S261>' : 'controller_3dof/Subsystem3/PID Controller1/P Copy/Disabled'
//  '<S262>' : 'controller_3dof/Subsystem3/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S263>' : 'controller_3dof/Subsystem3/PID Controller1/Reset Signal/Disabled'
//  '<S264>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation/Passthrough'
//  '<S265>' : 'controller_3dof/Subsystem3/PID Controller1/Saturation Fdbk/Disabled'
//  '<S266>' : 'controller_3dof/Subsystem3/PID Controller1/Sum/Sum_PID'
//  '<S267>' : 'controller_3dof/Subsystem3/PID Controller1/Sum Fdbk/Disabled'
//  '<S268>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode/Disabled'
//  '<S269>' : 'controller_3dof/Subsystem3/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S270>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S271>' : 'controller_3dof/Subsystem3/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S272>' : 'controller_3dof/Subsystem3/PID Controller1/postSat Signal/Forward_Path'
//  '<S273>' : 'controller_3dof/Subsystem3/PID Controller1/preInt Signal/Internal PreInt'
//  '<S274>' : 'controller_3dof/Subsystem3/PID Controller1/preSat Signal/Forward_Path'
//  '<S275>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup'
//  '<S276>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain'
//  '<S277>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative'
//  '<S278>' : 'controller_3dof/Subsystem3/PID Controller2/Filter'
//  '<S279>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs'
//  '<S280>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain'
//  '<S281>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain'
//  '<S282>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk'
//  '<S283>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator'
//  '<S284>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs'
//  '<S285>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy'
//  '<S286>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain'
//  '<S287>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy'
//  '<S288>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain'
//  '<S289>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal'
//  '<S290>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation'
//  '<S291>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk'
//  '<S292>' : 'controller_3dof/Subsystem3/PID Controller2/Sum'
//  '<S293>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk'
//  '<S294>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode'
//  '<S295>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum'
//  '<S296>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral'
//  '<S297>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain'
//  '<S298>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal'
//  '<S299>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal'
//  '<S300>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal'
//  '<S301>' : 'controller_3dof/Subsystem3/PID Controller2/Anti-windup/Passthrough'
//  '<S302>' : 'controller_3dof/Subsystem3/PID Controller2/D Gain/Internal Parameters'
//  '<S303>' : 'controller_3dof/Subsystem3/PID Controller2/External Derivative/Error'
//  '<S304>' : 'controller_3dof/Subsystem3/PID Controller2/Filter/Cont. Filter'
//  '<S305>' : 'controller_3dof/Subsystem3/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S306>' : 'controller_3dof/Subsystem3/PID Controller2/I Gain/Internal Parameters'
//  '<S307>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain/Passthrough'
//  '<S308>' : 'controller_3dof/Subsystem3/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S309>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator/Continuous'
//  '<S310>' : 'controller_3dof/Subsystem3/PID Controller2/Integrator ICs/Internal IC'
//  '<S311>' : 'controller_3dof/Subsystem3/PID Controller2/N Copy/Disabled'
//  '<S312>' : 'controller_3dof/Subsystem3/PID Controller2/N Gain/Internal Parameters'
//  '<S313>' : 'controller_3dof/Subsystem3/PID Controller2/P Copy/Disabled'
//  '<S314>' : 'controller_3dof/Subsystem3/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S315>' : 'controller_3dof/Subsystem3/PID Controller2/Reset Signal/Disabled'
//  '<S316>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation/Passthrough'
//  '<S317>' : 'controller_3dof/Subsystem3/PID Controller2/Saturation Fdbk/Disabled'
//  '<S318>' : 'controller_3dof/Subsystem3/PID Controller2/Sum/Sum_PID'
//  '<S319>' : 'controller_3dof/Subsystem3/PID Controller2/Sum Fdbk/Disabled'
//  '<S320>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode/Disabled'
//  '<S321>' : 'controller_3dof/Subsystem3/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S322>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S323>' : 'controller_3dof/Subsystem3/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S324>' : 'controller_3dof/Subsystem3/PID Controller2/postSat Signal/Forward_Path'
//  '<S325>' : 'controller_3dof/Subsystem3/PID Controller2/preInt Signal/Internal PreInt'
//  '<S326>' : 'controller_3dof/Subsystem3/PID Controller2/preSat Signal/Forward_Path'
//  '<S327>' : 'controller_3dof/Subsystem3/Subsystem/MATLAB Function'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
