//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller_3dof.h
//
// Code generated for Simulink model 'controller_3dof'.
//
// Model version                  : 1.52
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Nov 19 17:56:25 2025
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

// Class declaration for model controller_3dof
class Controller final
{
  // public data and function members
 public:
  // External inputs (root inport signals with default storage)
  struct ExtU {
    real32_T roll;                     // '<Root>/roll'
    real32_T pitch;                    // '<Root>/pitch'
    real32_T yaw;                      // '<Root>/yaw'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real32_T throttle_1;               // '<Root>/throttle_1'
    real32_T throttle_2;               // '<Root>/throttle_2'
    real32_T throttle_3;               // '<Root>/throttle_3'
    real32_T throttle_4;               // '<Root>/throttle_4'
  };

  // Parameters (default storage)
  struct P {
    real32_T tau_Value[4];             // Computed Parameter: tau_Value
                                          //  Referenced by: '<Root>/tau'

  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
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
  static void initialize();

  // model step function
  void step();

  // Constructor
  Controller();

  // Destructor
  ~Controller();

  // private data and function members
 private:
  // Tunable parameters
  static P rtP;

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S30>/Derivative Gain' : Unused code path elimination
//  Block '<S32>/Filter' : Unused code path elimination
//  Block '<S32>/SumD' : Unused code path elimination
//  Block '<S34>/Integral Gain' : Unused code path elimination
//  Block '<S37>/Integrator' : Unused code path elimination
//  Block '<S40>/Filter Coefficient' : Unused code path elimination
//  Block '<S42>/Proportional Gain' : Unused code path elimination
//  Block '<S46>/Sum' : Unused code path elimination


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
//  '<S1>'   : 'controller_3dof/Discrete PID Controller'
//  '<S2>'   : 'controller_3dof/MATLAB Function'
//  '<S3>'   : 'controller_3dof/Discrete PID Controller/Anti-windup'
//  '<S4>'   : 'controller_3dof/Discrete PID Controller/D Gain'
//  '<S5>'   : 'controller_3dof/Discrete PID Controller/External Derivative'
//  '<S6>'   : 'controller_3dof/Discrete PID Controller/Filter'
//  '<S7>'   : 'controller_3dof/Discrete PID Controller/Filter ICs'
//  '<S8>'   : 'controller_3dof/Discrete PID Controller/I Gain'
//  '<S9>'   : 'controller_3dof/Discrete PID Controller/Ideal P Gain'
//  '<S10>'  : 'controller_3dof/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S11>'  : 'controller_3dof/Discrete PID Controller/Integrator'
//  '<S12>'  : 'controller_3dof/Discrete PID Controller/Integrator ICs'
//  '<S13>'  : 'controller_3dof/Discrete PID Controller/N Copy'
//  '<S14>'  : 'controller_3dof/Discrete PID Controller/N Gain'
//  '<S15>'  : 'controller_3dof/Discrete PID Controller/P Copy'
//  '<S16>'  : 'controller_3dof/Discrete PID Controller/Parallel P Gain'
//  '<S17>'  : 'controller_3dof/Discrete PID Controller/Reset Signal'
//  '<S18>'  : 'controller_3dof/Discrete PID Controller/Saturation'
//  '<S19>'  : 'controller_3dof/Discrete PID Controller/Saturation Fdbk'
//  '<S20>'  : 'controller_3dof/Discrete PID Controller/Sum'
//  '<S21>'  : 'controller_3dof/Discrete PID Controller/Sum Fdbk'
//  '<S22>'  : 'controller_3dof/Discrete PID Controller/Tracking Mode'
//  '<S23>'  : 'controller_3dof/Discrete PID Controller/Tracking Mode Sum'
//  '<S24>'  : 'controller_3dof/Discrete PID Controller/Tsamp - Integral'
//  '<S25>'  : 'controller_3dof/Discrete PID Controller/Tsamp - Ngain'
//  '<S26>'  : 'controller_3dof/Discrete PID Controller/postSat Signal'
//  '<S27>'  : 'controller_3dof/Discrete PID Controller/preInt Signal'
//  '<S28>'  : 'controller_3dof/Discrete PID Controller/preSat Signal'
//  '<S29>'  : 'controller_3dof/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S30>'  : 'controller_3dof/Discrete PID Controller/D Gain/Internal Parameters'
//  '<S31>'  : 'controller_3dof/Discrete PID Controller/External Derivative/Error'
//  '<S32>'  : 'controller_3dof/Discrete PID Controller/Filter/Disc. Forward Euler Filter'
//  '<S33>'  : 'controller_3dof/Discrete PID Controller/Filter ICs/Internal IC - Filter'
//  '<S34>'  : 'controller_3dof/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S35>'  : 'controller_3dof/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S36>'  : 'controller_3dof/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S37>'  : 'controller_3dof/Discrete PID Controller/Integrator/Discrete'
//  '<S38>'  : 'controller_3dof/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S39>'  : 'controller_3dof/Discrete PID Controller/N Copy/Disabled'
//  '<S40>'  : 'controller_3dof/Discrete PID Controller/N Gain/Internal Parameters'
//  '<S41>'  : 'controller_3dof/Discrete PID Controller/P Copy/Disabled'
//  '<S42>'  : 'controller_3dof/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S43>'  : 'controller_3dof/Discrete PID Controller/Reset Signal/Disabled'
//  '<S44>'  : 'controller_3dof/Discrete PID Controller/Saturation/Passthrough'
//  '<S45>'  : 'controller_3dof/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S46>'  : 'controller_3dof/Discrete PID Controller/Sum/Sum_PID'
//  '<S47>'  : 'controller_3dof/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S48>'  : 'controller_3dof/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S49>'  : 'controller_3dof/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S50>'  : 'controller_3dof/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S51>'  : 'controller_3dof/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S52>'  : 'controller_3dof/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S53>'  : 'controller_3dof/Discrete PID Controller/preInt Signal/Internal PreInt'
//  '<S54>'  : 'controller_3dof/Discrete PID Controller/preSat Signal/Forward_Path'

#endif                                 // controller_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
