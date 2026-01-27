//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.128
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Tue Jan 27 11:00:42 2026
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
#include <cstring>
#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
struct ODE3_IntgData {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
};

#endif

// Class declaration for model controller_3dof
class Controller final
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T FilterCoefficient;          // '<S42>/Filter Coefficient'
    real_T FilterCoefficient_p;        // '<S94>/Filter Coefficient'
    real_T FilterCoefficient_d;        // '<S146>/Filter Coefficient'
    real_T IntegralGain;               // '<S140>/Integral Gain'
    real_T IntegralGain_i;             // '<S88>/Integral Gain'
    real_T IntegralGain_d;             // '<S36>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE;          // '<S39>/Integrator'
    real_T Filter_CSTATE;              // '<S34>/Filter'
    real_T Integrator_CSTATE_f;        // '<S91>/Integrator'
    real_T Filter_CSTATE_d;            // '<S86>/Filter'
    real_T Integrator_CSTATE_j;        // '<S143>/Integrator'
    real_T Filter_CSTATE_j;            // '<S138>/Filter'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE;          // '<S39>/Integrator'
    real_T Filter_CSTATE;              // '<S34>/Filter'
    real_T Integrator_CSTATE_f;        // '<S91>/Integrator'
    real_T Filter_CSTATE_d;            // '<S86>/Filter'
    real_T Integrator_CSTATE_j;        // '<S143>/Integrator'
    real_T Filter_CSTATE_j;            // '<S138>/Filter'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE;       // '<S39>/Integrator'
    boolean_T Filter_CSTATE;           // '<S34>/Filter'
    boolean_T Integrator_CSTATE_f;     // '<S91>/Integrator'
    boolean_T Filter_CSTATE_d;         // '<S86>/Filter'
    boolean_T Integrator_CSTATE_j;     // '<S143>/Integrator'
    boolean_T Filter_CSTATE_j;         // '<S138>/Filter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T roll;                       // '<Root>/roll'
    real_T pitch;                      // '<Root>/pitch'
    real_T yaw;                        // '<Root>/yaw'
    real_T roll_target;                // '<Root>/roll_target'
    real_T pitch_target;               // '<Root>/pitch_target'
    real_T yaw_target;                 // '<Root>/yaw_target'
    real_T throttle;                   // '<Root>/throttle'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T throttle_1;                 // '<Root>/throttle_1'
    real_T throttle_2;                 // '<Root>/throttle_2'
    real_T throttle_3;                 // '<Root>/throttle_3'
    real_T throttle_4;                 // '<Root>/throttle_4'
  };

  // Parameters (default storage)
  struct P {
    real_T PIDController_D;            // Mask Parameter: PIDController_D
                                          //  Referenced by: '<S32>/Derivative Gain'

    real_T PIDController1_D;           // Mask Parameter: PIDController1_D
                                          //  Referenced by: '<S84>/Derivative Gain'

    real_T PIDController2_D;           // Mask Parameter: PIDController2_D
                                          //  Referenced by: '<S136>/Derivative Gain'

    real_T PIDController2_I;           // Mask Parameter: PIDController2_I
                                          //  Referenced by: '<S140>/Integral Gain'

    real_T PIDController1_I;           // Mask Parameter: PIDController1_I
                                          //  Referenced by: '<S88>/Integral Gain'

    real_T PIDController_I;            // Mask Parameter: PIDController_I
                                          //  Referenced by: '<S36>/Integral Gain'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S34>/Filter'

    real_T PIDController1_InitialCondition;
                              // Mask Parameter: PIDController1_InitialCondition
                                 //  Referenced by: '<S86>/Filter'

    real_T PIDController2_InitialCondition;
                              // Mask Parameter: PIDController2_InitialCondition
                                 //  Referenced by: '<S138>/Filter'

    real_T PIDController_InitialConditio_i;
                              // Mask Parameter: PIDController_InitialConditio_i
                                 //  Referenced by: '<S39>/Integrator'

    real_T PIDController1_InitialConditi_l;
                              // Mask Parameter: PIDController1_InitialConditi_l
                                 //  Referenced by: '<S91>/Integrator'

    real_T PIDController2_InitialConditi_k;
                              // Mask Parameter: PIDController2_InitialConditi_k
                                 //  Referenced by: '<S143>/Integrator'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S42>/Filter Coefficient'

    real_T PIDController1_N;           // Mask Parameter: PIDController1_N
                                          //  Referenced by: '<S94>/Filter Coefficient'

    real_T PIDController2_N;           // Mask Parameter: PIDController2_N
                                          //  Referenced by: '<S146>/Filter Coefficient'

    real_T PIDController_P;            // Mask Parameter: PIDController_P
                                          //  Referenced by: '<S44>/Proportional Gain'

    real_T PIDController1_P;           // Mask Parameter: PIDController1_P
                                          //  Referenced by: '<S96>/Proportional Gain'

    real_T PIDController2_P;           // Mask Parameter: PIDController2_P
                                          //  Referenced by: '<S148>/Proportional Gain'

    real_T Saturation_UpperSat;        // Expression: 90
                                          //  Referenced by: '<Root>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 15
                                          //  Referenced by: '<Root>/Saturation'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[6];
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
    real_T odeY[6];
    real_T odeF[3][6];
    ODE3_IntgData intgData;

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

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  Controller();

  // Destructor
  ~Controller();
  static P rtP;

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Tunable parameters
  

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
//  Block '<Root>/Scope' : Unused code path elimination


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
//  '<S1>'   : 'controller_3dof/MATLAB Function'
//  '<S2>'   : 'controller_3dof/PID Controller'
//  '<S3>'   : 'controller_3dof/PID Controller1'
//  '<S4>'   : 'controller_3dof/PID Controller2'
//  '<S5>'   : 'controller_3dof/PID Controller/Anti-windup'
//  '<S6>'   : 'controller_3dof/PID Controller/D Gain'
//  '<S7>'   : 'controller_3dof/PID Controller/External Derivative'
//  '<S8>'   : 'controller_3dof/PID Controller/Filter'
//  '<S9>'   : 'controller_3dof/PID Controller/Filter ICs'
//  '<S10>'  : 'controller_3dof/PID Controller/I Gain'
//  '<S11>'  : 'controller_3dof/PID Controller/Ideal P Gain'
//  '<S12>'  : 'controller_3dof/PID Controller/Ideal P Gain Fdbk'
//  '<S13>'  : 'controller_3dof/PID Controller/Integrator'
//  '<S14>'  : 'controller_3dof/PID Controller/Integrator ICs'
//  '<S15>'  : 'controller_3dof/PID Controller/N Copy'
//  '<S16>'  : 'controller_3dof/PID Controller/N Gain'
//  '<S17>'  : 'controller_3dof/PID Controller/P Copy'
//  '<S18>'  : 'controller_3dof/PID Controller/Parallel P Gain'
//  '<S19>'  : 'controller_3dof/PID Controller/Reset Signal'
//  '<S20>'  : 'controller_3dof/PID Controller/Saturation'
//  '<S21>'  : 'controller_3dof/PID Controller/Saturation Fdbk'
//  '<S22>'  : 'controller_3dof/PID Controller/Sum'
//  '<S23>'  : 'controller_3dof/PID Controller/Sum Fdbk'
//  '<S24>'  : 'controller_3dof/PID Controller/Tracking Mode'
//  '<S25>'  : 'controller_3dof/PID Controller/Tracking Mode Sum'
//  '<S26>'  : 'controller_3dof/PID Controller/Tsamp - Integral'
//  '<S27>'  : 'controller_3dof/PID Controller/Tsamp - Ngain'
//  '<S28>'  : 'controller_3dof/PID Controller/postSat Signal'
//  '<S29>'  : 'controller_3dof/PID Controller/preInt Signal'
//  '<S30>'  : 'controller_3dof/PID Controller/preSat Signal'
//  '<S31>'  : 'controller_3dof/PID Controller/Anti-windup/Passthrough'
//  '<S32>'  : 'controller_3dof/PID Controller/D Gain/Internal Parameters'
//  '<S33>'  : 'controller_3dof/PID Controller/External Derivative/Error'
//  '<S34>'  : 'controller_3dof/PID Controller/Filter/Cont. Filter'
//  '<S35>'  : 'controller_3dof/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S36>'  : 'controller_3dof/PID Controller/I Gain/Internal Parameters'
//  '<S37>'  : 'controller_3dof/PID Controller/Ideal P Gain/Passthrough'
//  '<S38>'  : 'controller_3dof/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S39>'  : 'controller_3dof/PID Controller/Integrator/Continuous'
//  '<S40>'  : 'controller_3dof/PID Controller/Integrator ICs/Internal IC'
//  '<S41>'  : 'controller_3dof/PID Controller/N Copy/Disabled'
//  '<S42>'  : 'controller_3dof/PID Controller/N Gain/Internal Parameters'
//  '<S43>'  : 'controller_3dof/PID Controller/P Copy/Disabled'
//  '<S44>'  : 'controller_3dof/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S45>'  : 'controller_3dof/PID Controller/Reset Signal/Disabled'
//  '<S46>'  : 'controller_3dof/PID Controller/Saturation/Passthrough'
//  '<S47>'  : 'controller_3dof/PID Controller/Saturation Fdbk/Disabled'
//  '<S48>'  : 'controller_3dof/PID Controller/Sum/Sum_PID'
//  '<S49>'  : 'controller_3dof/PID Controller/Sum Fdbk/Disabled'
//  '<S50>'  : 'controller_3dof/PID Controller/Tracking Mode/Disabled'
//  '<S51>'  : 'controller_3dof/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S52>'  : 'controller_3dof/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S53>'  : 'controller_3dof/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S54>'  : 'controller_3dof/PID Controller/postSat Signal/Forward_Path'
//  '<S55>'  : 'controller_3dof/PID Controller/preInt Signal/Internal PreInt'
//  '<S56>'  : 'controller_3dof/PID Controller/preSat Signal/Forward_Path'
//  '<S57>'  : 'controller_3dof/PID Controller1/Anti-windup'
//  '<S58>'  : 'controller_3dof/PID Controller1/D Gain'
//  '<S59>'  : 'controller_3dof/PID Controller1/External Derivative'
//  '<S60>'  : 'controller_3dof/PID Controller1/Filter'
//  '<S61>'  : 'controller_3dof/PID Controller1/Filter ICs'
//  '<S62>'  : 'controller_3dof/PID Controller1/I Gain'
//  '<S63>'  : 'controller_3dof/PID Controller1/Ideal P Gain'
//  '<S64>'  : 'controller_3dof/PID Controller1/Ideal P Gain Fdbk'
//  '<S65>'  : 'controller_3dof/PID Controller1/Integrator'
//  '<S66>'  : 'controller_3dof/PID Controller1/Integrator ICs'
//  '<S67>'  : 'controller_3dof/PID Controller1/N Copy'
//  '<S68>'  : 'controller_3dof/PID Controller1/N Gain'
//  '<S69>'  : 'controller_3dof/PID Controller1/P Copy'
//  '<S70>'  : 'controller_3dof/PID Controller1/Parallel P Gain'
//  '<S71>'  : 'controller_3dof/PID Controller1/Reset Signal'
//  '<S72>'  : 'controller_3dof/PID Controller1/Saturation'
//  '<S73>'  : 'controller_3dof/PID Controller1/Saturation Fdbk'
//  '<S74>'  : 'controller_3dof/PID Controller1/Sum'
//  '<S75>'  : 'controller_3dof/PID Controller1/Sum Fdbk'
//  '<S76>'  : 'controller_3dof/PID Controller1/Tracking Mode'
//  '<S77>'  : 'controller_3dof/PID Controller1/Tracking Mode Sum'
//  '<S78>'  : 'controller_3dof/PID Controller1/Tsamp - Integral'
//  '<S79>'  : 'controller_3dof/PID Controller1/Tsamp - Ngain'
//  '<S80>'  : 'controller_3dof/PID Controller1/postSat Signal'
//  '<S81>'  : 'controller_3dof/PID Controller1/preInt Signal'
//  '<S82>'  : 'controller_3dof/PID Controller1/preSat Signal'
//  '<S83>'  : 'controller_3dof/PID Controller1/Anti-windup/Passthrough'
//  '<S84>'  : 'controller_3dof/PID Controller1/D Gain/Internal Parameters'
//  '<S85>'  : 'controller_3dof/PID Controller1/External Derivative/Error'
//  '<S86>'  : 'controller_3dof/PID Controller1/Filter/Cont. Filter'
//  '<S87>'  : 'controller_3dof/PID Controller1/Filter ICs/Internal IC - Filter'
//  '<S88>'  : 'controller_3dof/PID Controller1/I Gain/Internal Parameters'
//  '<S89>'  : 'controller_3dof/PID Controller1/Ideal P Gain/Passthrough'
//  '<S90>'  : 'controller_3dof/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S91>'  : 'controller_3dof/PID Controller1/Integrator/Continuous'
//  '<S92>'  : 'controller_3dof/PID Controller1/Integrator ICs/Internal IC'
//  '<S93>'  : 'controller_3dof/PID Controller1/N Copy/Disabled'
//  '<S94>'  : 'controller_3dof/PID Controller1/N Gain/Internal Parameters'
//  '<S95>'  : 'controller_3dof/PID Controller1/P Copy/Disabled'
//  '<S96>'  : 'controller_3dof/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S97>'  : 'controller_3dof/PID Controller1/Reset Signal/Disabled'
//  '<S98>'  : 'controller_3dof/PID Controller1/Saturation/Passthrough'
//  '<S99>'  : 'controller_3dof/PID Controller1/Saturation Fdbk/Disabled'
//  '<S100>' : 'controller_3dof/PID Controller1/Sum/Sum_PID'
//  '<S101>' : 'controller_3dof/PID Controller1/Sum Fdbk/Disabled'
//  '<S102>' : 'controller_3dof/PID Controller1/Tracking Mode/Disabled'
//  '<S103>' : 'controller_3dof/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S104>' : 'controller_3dof/PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S105>' : 'controller_3dof/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S106>' : 'controller_3dof/PID Controller1/postSat Signal/Forward_Path'
//  '<S107>' : 'controller_3dof/PID Controller1/preInt Signal/Internal PreInt'
//  '<S108>' : 'controller_3dof/PID Controller1/preSat Signal/Forward_Path'
//  '<S109>' : 'controller_3dof/PID Controller2/Anti-windup'
//  '<S110>' : 'controller_3dof/PID Controller2/D Gain'
//  '<S111>' : 'controller_3dof/PID Controller2/External Derivative'
//  '<S112>' : 'controller_3dof/PID Controller2/Filter'
//  '<S113>' : 'controller_3dof/PID Controller2/Filter ICs'
//  '<S114>' : 'controller_3dof/PID Controller2/I Gain'
//  '<S115>' : 'controller_3dof/PID Controller2/Ideal P Gain'
//  '<S116>' : 'controller_3dof/PID Controller2/Ideal P Gain Fdbk'
//  '<S117>' : 'controller_3dof/PID Controller2/Integrator'
//  '<S118>' : 'controller_3dof/PID Controller2/Integrator ICs'
//  '<S119>' : 'controller_3dof/PID Controller2/N Copy'
//  '<S120>' : 'controller_3dof/PID Controller2/N Gain'
//  '<S121>' : 'controller_3dof/PID Controller2/P Copy'
//  '<S122>' : 'controller_3dof/PID Controller2/Parallel P Gain'
//  '<S123>' : 'controller_3dof/PID Controller2/Reset Signal'
//  '<S124>' : 'controller_3dof/PID Controller2/Saturation'
//  '<S125>' : 'controller_3dof/PID Controller2/Saturation Fdbk'
//  '<S126>' : 'controller_3dof/PID Controller2/Sum'
//  '<S127>' : 'controller_3dof/PID Controller2/Sum Fdbk'
//  '<S128>' : 'controller_3dof/PID Controller2/Tracking Mode'
//  '<S129>' : 'controller_3dof/PID Controller2/Tracking Mode Sum'
//  '<S130>' : 'controller_3dof/PID Controller2/Tsamp - Integral'
//  '<S131>' : 'controller_3dof/PID Controller2/Tsamp - Ngain'
//  '<S132>' : 'controller_3dof/PID Controller2/postSat Signal'
//  '<S133>' : 'controller_3dof/PID Controller2/preInt Signal'
//  '<S134>' : 'controller_3dof/PID Controller2/preSat Signal'
//  '<S135>' : 'controller_3dof/PID Controller2/Anti-windup/Passthrough'
//  '<S136>' : 'controller_3dof/PID Controller2/D Gain/Internal Parameters'
//  '<S137>' : 'controller_3dof/PID Controller2/External Derivative/Error'
//  '<S138>' : 'controller_3dof/PID Controller2/Filter/Cont. Filter'
//  '<S139>' : 'controller_3dof/PID Controller2/Filter ICs/Internal IC - Filter'
//  '<S140>' : 'controller_3dof/PID Controller2/I Gain/Internal Parameters'
//  '<S141>' : 'controller_3dof/PID Controller2/Ideal P Gain/Passthrough'
//  '<S142>' : 'controller_3dof/PID Controller2/Ideal P Gain Fdbk/Disabled'
//  '<S143>' : 'controller_3dof/PID Controller2/Integrator/Continuous'
//  '<S144>' : 'controller_3dof/PID Controller2/Integrator ICs/Internal IC'
//  '<S145>' : 'controller_3dof/PID Controller2/N Copy/Disabled'
//  '<S146>' : 'controller_3dof/PID Controller2/N Gain/Internal Parameters'
//  '<S147>' : 'controller_3dof/PID Controller2/P Copy/Disabled'
//  '<S148>' : 'controller_3dof/PID Controller2/Parallel P Gain/Internal Parameters'
//  '<S149>' : 'controller_3dof/PID Controller2/Reset Signal/Disabled'
//  '<S150>' : 'controller_3dof/PID Controller2/Saturation/Passthrough'
//  '<S151>' : 'controller_3dof/PID Controller2/Saturation Fdbk/Disabled'
//  '<S152>' : 'controller_3dof/PID Controller2/Sum/Sum_PID'
//  '<S153>' : 'controller_3dof/PID Controller2/Sum Fdbk/Disabled'
//  '<S154>' : 'controller_3dof/PID Controller2/Tracking Mode/Disabled'
//  '<S155>' : 'controller_3dof/PID Controller2/Tracking Mode Sum/Passthrough'
//  '<S156>' : 'controller_3dof/PID Controller2/Tsamp - Integral/TsSignalSpecification'
//  '<S157>' : 'controller_3dof/PID Controller2/Tsamp - Ngain/Passthrough'
//  '<S158>' : 'controller_3dof/PID Controller2/postSat Signal/Forward_Path'
//  '<S159>' : 'controller_3dof/PID Controller2/preInt Signal/Internal PreInt'
//  '<S160>' : 'controller_3dof/PID Controller2/preSat Signal/Forward_Path'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
