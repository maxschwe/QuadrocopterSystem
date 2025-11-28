//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.86
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Fri Nov 28 17:24:05 2025
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
    real_T ProportionalGain;           // '<S43>/Proportional Gain'
    real_T DerivativeGain;             // '<S31>/Derivative Gain'
    real_T FilterCoefficient;          // '<S41>/Filter Coefficient'
    real_T IntegralGain;               // '<S35>/Integral Gain'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator_CSTATE;          // '<S38>/Integrator'
    real_T Filter_CSTATE;              // '<S33>/Filter'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator_CSTATE;          // '<S38>/Integrator'
    real_T Filter_CSTATE;              // '<S33>/Filter'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator_CSTATE;       // '<S38>/Integrator'
    boolean_T Filter_CSTATE;           // '<S33>/Filter'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real_T roll;                       // '<Root>/roll'
    real_T pitch;                      // '<Root>/pitch'
    real_T yaw;                        // '<Root>/yaw'
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
                                          //  Referenced by: '<S31>/Derivative Gain'

    real_T PIDController_I;            // Mask Parameter: PIDController_I
                                          //  Referenced by: '<S35>/Integral Gain'

    real_T PIDController_InitialConditionF;
                              // Mask Parameter: PIDController_InitialConditionF
                                 //  Referenced by: '<S33>/Filter'

    real_T PIDController_InitialConditio_d;
                              // Mask Parameter: PIDController_InitialConditio_d
                                 //  Referenced by: '<S38>/Integrator'

    real_T PIDController_N;            // Mask Parameter: PIDController_N
                                          //  Referenced by: '<S41>/Filter Coefficient'

    real_T PIDController_P;            // Mask Parameter: PIDController_P
                                          //  Referenced by: '<S43>/Proportional Gain'

    real_T CheckStaticRange_max;       // Mask Parameter: CheckStaticRange_max
                                          //  Referenced by: '<S1>/max_val'

    real_T CheckStaticRange_min;       // Mask Parameter: CheckStaticRange_min
                                          //  Referenced by: '<S1>/min_val'

    real_T Constant2_Value;            // Expression: 5
                                          //  Referenced by: '<Root>/Constant2'

    real_T Constant3_Value;            // Expression: 0
                                          //  Referenced by: '<Root>/Constant3'

    real_T Constant_Value;             // Expression: 0
                                          //  Referenced by: '<Root>/Constant'

    real_T Constant1_Value;            // Expression: 0
                                          //  Referenced by: '<Root>/Constant1'

    real_T Saturation_UpperSat;        // Expression: 85
                                          //  Referenced by: '<Root>/Saturation'

    real_T Saturation_LowerSat;        // Expression: 20
                                          //  Referenced by: '<Root>/Saturation'

    boolean_T Assertion_Enabled;       // Computed Parameter: Assertion_Enabled
                                          //  Referenced by: '<S1>/Assertion'

  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[2];
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
    real_T odeY[2];
    real_T odeF[3][2];
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

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Tunable parameters
  static P rtP;

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
//  Block '<Root>/Constant4' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination


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
//  '<S1>'   : 'controller_3dof/Check  Static Range'
//  '<S2>'   : 'controller_3dof/MATLAB Function'
//  '<S3>'   : 'controller_3dof/PID Controller'
//  '<S4>'   : 'controller_3dof/PID Controller/Anti-windup'
//  '<S5>'   : 'controller_3dof/PID Controller/D Gain'
//  '<S6>'   : 'controller_3dof/PID Controller/External Derivative'
//  '<S7>'   : 'controller_3dof/PID Controller/Filter'
//  '<S8>'   : 'controller_3dof/PID Controller/Filter ICs'
//  '<S9>'   : 'controller_3dof/PID Controller/I Gain'
//  '<S10>'  : 'controller_3dof/PID Controller/Ideal P Gain'
//  '<S11>'  : 'controller_3dof/PID Controller/Ideal P Gain Fdbk'
//  '<S12>'  : 'controller_3dof/PID Controller/Integrator'
//  '<S13>'  : 'controller_3dof/PID Controller/Integrator ICs'
//  '<S14>'  : 'controller_3dof/PID Controller/N Copy'
//  '<S15>'  : 'controller_3dof/PID Controller/N Gain'
//  '<S16>'  : 'controller_3dof/PID Controller/P Copy'
//  '<S17>'  : 'controller_3dof/PID Controller/Parallel P Gain'
//  '<S18>'  : 'controller_3dof/PID Controller/Reset Signal'
//  '<S19>'  : 'controller_3dof/PID Controller/Saturation'
//  '<S20>'  : 'controller_3dof/PID Controller/Saturation Fdbk'
//  '<S21>'  : 'controller_3dof/PID Controller/Sum'
//  '<S22>'  : 'controller_3dof/PID Controller/Sum Fdbk'
//  '<S23>'  : 'controller_3dof/PID Controller/Tracking Mode'
//  '<S24>'  : 'controller_3dof/PID Controller/Tracking Mode Sum'
//  '<S25>'  : 'controller_3dof/PID Controller/Tsamp - Integral'
//  '<S26>'  : 'controller_3dof/PID Controller/Tsamp - Ngain'
//  '<S27>'  : 'controller_3dof/PID Controller/postSat Signal'
//  '<S28>'  : 'controller_3dof/PID Controller/preInt Signal'
//  '<S29>'  : 'controller_3dof/PID Controller/preSat Signal'
//  '<S30>'  : 'controller_3dof/PID Controller/Anti-windup/Passthrough'
//  '<S31>'  : 'controller_3dof/PID Controller/D Gain/Internal Parameters'
//  '<S32>'  : 'controller_3dof/PID Controller/External Derivative/Error'
//  '<S33>'  : 'controller_3dof/PID Controller/Filter/Cont. Filter'
//  '<S34>'  : 'controller_3dof/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S35>'  : 'controller_3dof/PID Controller/I Gain/Internal Parameters'
//  '<S36>'  : 'controller_3dof/PID Controller/Ideal P Gain/Passthrough'
//  '<S37>'  : 'controller_3dof/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S38>'  : 'controller_3dof/PID Controller/Integrator/Continuous'
//  '<S39>'  : 'controller_3dof/PID Controller/Integrator ICs/Internal IC'
//  '<S40>'  : 'controller_3dof/PID Controller/N Copy/Disabled'
//  '<S41>'  : 'controller_3dof/PID Controller/N Gain/Internal Parameters'
//  '<S42>'  : 'controller_3dof/PID Controller/P Copy/Disabled'
//  '<S43>'  : 'controller_3dof/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S44>'  : 'controller_3dof/PID Controller/Reset Signal/Disabled'
//  '<S45>'  : 'controller_3dof/PID Controller/Saturation/Passthrough'
//  '<S46>'  : 'controller_3dof/PID Controller/Saturation Fdbk/Disabled'
//  '<S47>'  : 'controller_3dof/PID Controller/Sum/Sum_PID'
//  '<S48>'  : 'controller_3dof/PID Controller/Sum Fdbk/Disabled'
//  '<S49>'  : 'controller_3dof/PID Controller/Tracking Mode/Disabled'
//  '<S50>'  : 'controller_3dof/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S51>'  : 'controller_3dof/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S52>'  : 'controller_3dof/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S53>'  : 'controller_3dof/PID Controller/postSat Signal/Forward_Path'
//  '<S54>'  : 'controller_3dof/PID Controller/preInt Signal/Internal PreInt'
//  '<S55>'  : 'controller_3dof/PID Controller/preSat Signal/Forward_Path'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
