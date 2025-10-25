//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: controller.h
//
// Code generated for Simulink model 'controller'.
//
// Model version                  : 1.207
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sat Oct 25 12:33:16 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Custom Processor->Custom Processor
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#ifndef controller_h_
#define controller_h_
#include "rtwtypes.h"
#define controller_M                   (rtM)

// Class declaration for model controller
class Model
{
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T a_f;                        // '<Root>/MATLAB Function1'
    real_T b_f;                        // '<Root>/MATLAB Function1'
    real_T c_f;                        // '<Root>/MATLAB Function1'
    real_T force_minimum;              // '<Root>/MATLAB Function1'
    real_T a_t;                        // '<Root>/MATLAB Function1'
    real_T b_t;                        // '<Root>/MATLAB Function1'
    real_T distance;                   // '<Root>/MATLAB Function1'
    real_T torque_minimum;             // '<Root>/MATLAB Function1'
    boolean_T a_f_not_empty;           // '<Root>/MATLAB Function1'
  };

  // External inputs (root inport signals with default storage)
  struct ExtU {
    real32_T x;                        // '<Root>/x'
    real32_T y;                        // '<Root>/y'
    real32_T z;                        // '<Root>/z'
    real32_T roll;                     // '<Root>/roll'
    real32_T pitch;                    // '<Root>/pitch'
    real32_T yaw;                      // '<Root>/yaw'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY {
    real_T Out1;                       // '<Root>/Out1'
    real_T Out2;                       // '<Root>/Out2'
    real_T Out3;                       // '<Root>/Out3'
    real_T Out4;                       // '<Root>/Out4'
  };

  // Parameters (default storage)
  struct P {
    real_T Constant_Value;             // Expression: 10
                                          //  Referenced by: '<Root>/Constant'

    real_T Constant1_Value;            // Expression: 0.2
                                          //  Referenced by: '<Root>/Constant1'

    real_T Constant2_Value;            // Expression: 0
                                          //  Referenced by: '<Root>/Constant2'

    real_T Constant3_Value;            // Expression: 0
                                          //  Referenced by: '<Root>/Constant3'

  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Real-Time Model get method
  Model::RT_MODEL * getRTM();

  // External inputs
  ExtU rtU;

  // External outputs
  ExtY rtY;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  Model();

  // Destructor
  ~Model();

  // private data and function members
 private:
  // Block states
  DW rtDW;

  // Tunable parameters
  static P rtP;

  // Real-Time Model
  RT_MODEL rtM;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S31>/Derivative Gain' : Unused code path elimination
//  Block '<S33>/DTDup' : Unused code path elimination
//  Block '<S33>/Diff' : Unused code path elimination
//  Block '<S35>/Tsamp' : Unused code path elimination
//  Block '<S33>/UD' : Unused code path elimination
//  Block '<S37>/Integral Gain' : Unused code path elimination
//  Block '<S40>/Integrator' : Unused code path elimination
//  Block '<S45>/Proportional Gain' : Unused code path elimination
//  Block '<S49>/Sum' : Unused code path elimination
//  Block '<S85>/Derivative Gain' : Unused code path elimination
//  Block '<S87>/DTDup' : Unused code path elimination
//  Block '<S87>/Diff' : Unused code path elimination
//  Block '<S89>/Tsamp' : Unused code path elimination
//  Block '<S87>/UD' : Unused code path elimination
//  Block '<S91>/Integral Gain' : Unused code path elimination
//  Block '<S94>/Integrator' : Unused code path elimination
//  Block '<S99>/Proportional Gain' : Unused code path elimination
//  Block '<S103>/Sum' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<Root>/Sum' : Unused code path elimination
//  Block '<Root>/Sum1' : Unused code path elimination
//  Block '<Root>/target_pitch' : Unused code path elimination
//  Block '<Root>/target_roll' : Unused code path elimination


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
//  '<Root>' : 'controller'
//  '<S1>'   : 'controller/Discrete PID Controller'
//  '<S2>'   : 'controller/Discrete PID Controller1'
//  '<S3>'   : 'controller/MATLAB Function1'
//  '<S4>'   : 'controller/Discrete PID Controller/Anti-windup'
//  '<S5>'   : 'controller/Discrete PID Controller/D Gain'
//  '<S6>'   : 'controller/Discrete PID Controller/External Derivative'
//  '<S7>'   : 'controller/Discrete PID Controller/Filter'
//  '<S8>'   : 'controller/Discrete PID Controller/Filter ICs'
//  '<S9>'   : 'controller/Discrete PID Controller/I Gain'
//  '<S10>'  : 'controller/Discrete PID Controller/Ideal P Gain'
//  '<S11>'  : 'controller/Discrete PID Controller/Ideal P Gain Fdbk'
//  '<S12>'  : 'controller/Discrete PID Controller/Integrator'
//  '<S13>'  : 'controller/Discrete PID Controller/Integrator ICs'
//  '<S14>'  : 'controller/Discrete PID Controller/N Copy'
//  '<S15>'  : 'controller/Discrete PID Controller/N Gain'
//  '<S16>'  : 'controller/Discrete PID Controller/P Copy'
//  '<S17>'  : 'controller/Discrete PID Controller/Parallel P Gain'
//  '<S18>'  : 'controller/Discrete PID Controller/Reset Signal'
//  '<S19>'  : 'controller/Discrete PID Controller/Saturation'
//  '<S20>'  : 'controller/Discrete PID Controller/Saturation Fdbk'
//  '<S21>'  : 'controller/Discrete PID Controller/Sum'
//  '<S22>'  : 'controller/Discrete PID Controller/Sum Fdbk'
//  '<S23>'  : 'controller/Discrete PID Controller/Tracking Mode'
//  '<S24>'  : 'controller/Discrete PID Controller/Tracking Mode Sum'
//  '<S25>'  : 'controller/Discrete PID Controller/Tsamp - Integral'
//  '<S26>'  : 'controller/Discrete PID Controller/Tsamp - Ngain'
//  '<S27>'  : 'controller/Discrete PID Controller/postSat Signal'
//  '<S28>'  : 'controller/Discrete PID Controller/preInt Signal'
//  '<S29>'  : 'controller/Discrete PID Controller/preSat Signal'
//  '<S30>'  : 'controller/Discrete PID Controller/Anti-windup/Passthrough'
//  '<S31>'  : 'controller/Discrete PID Controller/D Gain/Internal Parameters'
//  '<S32>'  : 'controller/Discrete PID Controller/External Derivative/Error'
//  '<S33>'  : 'controller/Discrete PID Controller/Filter/Differentiator'
//  '<S34>'  : 'controller/Discrete PID Controller/Filter/Differentiator/Tsamp'
//  '<S35>'  : 'controller/Discrete PID Controller/Filter/Differentiator/Tsamp/Internal Ts'
//  '<S36>'  : 'controller/Discrete PID Controller/Filter ICs/Internal IC - Differentiator'
//  '<S37>'  : 'controller/Discrete PID Controller/I Gain/Internal Parameters'
//  '<S38>'  : 'controller/Discrete PID Controller/Ideal P Gain/Passthrough'
//  '<S39>'  : 'controller/Discrete PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S40>'  : 'controller/Discrete PID Controller/Integrator/Discrete'
//  '<S41>'  : 'controller/Discrete PID Controller/Integrator ICs/Internal IC'
//  '<S42>'  : 'controller/Discrete PID Controller/N Copy/Disabled wSignal Specification'
//  '<S43>'  : 'controller/Discrete PID Controller/N Gain/Passthrough'
//  '<S44>'  : 'controller/Discrete PID Controller/P Copy/Disabled'
//  '<S45>'  : 'controller/Discrete PID Controller/Parallel P Gain/Internal Parameters'
//  '<S46>'  : 'controller/Discrete PID Controller/Reset Signal/Disabled'
//  '<S47>'  : 'controller/Discrete PID Controller/Saturation/Passthrough'
//  '<S48>'  : 'controller/Discrete PID Controller/Saturation Fdbk/Disabled'
//  '<S49>'  : 'controller/Discrete PID Controller/Sum/Sum_PID'
//  '<S50>'  : 'controller/Discrete PID Controller/Sum Fdbk/Disabled'
//  '<S51>'  : 'controller/Discrete PID Controller/Tracking Mode/Disabled'
//  '<S52>'  : 'controller/Discrete PID Controller/Tracking Mode Sum/Passthrough'
//  '<S53>'  : 'controller/Discrete PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S54>'  : 'controller/Discrete PID Controller/Tsamp - Ngain/Passthrough'
//  '<S55>'  : 'controller/Discrete PID Controller/postSat Signal/Forward_Path'
//  '<S56>'  : 'controller/Discrete PID Controller/preInt Signal/Internal PreInt'
//  '<S57>'  : 'controller/Discrete PID Controller/preSat Signal/Forward_Path'
//  '<S58>'  : 'controller/Discrete PID Controller1/Anti-windup'
//  '<S59>'  : 'controller/Discrete PID Controller1/D Gain'
//  '<S60>'  : 'controller/Discrete PID Controller1/External Derivative'
//  '<S61>'  : 'controller/Discrete PID Controller1/Filter'
//  '<S62>'  : 'controller/Discrete PID Controller1/Filter ICs'
//  '<S63>'  : 'controller/Discrete PID Controller1/I Gain'
//  '<S64>'  : 'controller/Discrete PID Controller1/Ideal P Gain'
//  '<S65>'  : 'controller/Discrete PID Controller1/Ideal P Gain Fdbk'
//  '<S66>'  : 'controller/Discrete PID Controller1/Integrator'
//  '<S67>'  : 'controller/Discrete PID Controller1/Integrator ICs'
//  '<S68>'  : 'controller/Discrete PID Controller1/N Copy'
//  '<S69>'  : 'controller/Discrete PID Controller1/N Gain'
//  '<S70>'  : 'controller/Discrete PID Controller1/P Copy'
//  '<S71>'  : 'controller/Discrete PID Controller1/Parallel P Gain'
//  '<S72>'  : 'controller/Discrete PID Controller1/Reset Signal'
//  '<S73>'  : 'controller/Discrete PID Controller1/Saturation'
//  '<S74>'  : 'controller/Discrete PID Controller1/Saturation Fdbk'
//  '<S75>'  : 'controller/Discrete PID Controller1/Sum'
//  '<S76>'  : 'controller/Discrete PID Controller1/Sum Fdbk'
//  '<S77>'  : 'controller/Discrete PID Controller1/Tracking Mode'
//  '<S78>'  : 'controller/Discrete PID Controller1/Tracking Mode Sum'
//  '<S79>'  : 'controller/Discrete PID Controller1/Tsamp - Integral'
//  '<S80>'  : 'controller/Discrete PID Controller1/Tsamp - Ngain'
//  '<S81>'  : 'controller/Discrete PID Controller1/postSat Signal'
//  '<S82>'  : 'controller/Discrete PID Controller1/preInt Signal'
//  '<S83>'  : 'controller/Discrete PID Controller1/preSat Signal'
//  '<S84>'  : 'controller/Discrete PID Controller1/Anti-windup/Passthrough'
//  '<S85>'  : 'controller/Discrete PID Controller1/D Gain/Internal Parameters'
//  '<S86>'  : 'controller/Discrete PID Controller1/External Derivative/Error'
//  '<S87>'  : 'controller/Discrete PID Controller1/Filter/Differentiator'
//  '<S88>'  : 'controller/Discrete PID Controller1/Filter/Differentiator/Tsamp'
//  '<S89>'  : 'controller/Discrete PID Controller1/Filter/Differentiator/Tsamp/Internal Ts'
//  '<S90>'  : 'controller/Discrete PID Controller1/Filter ICs/Internal IC - Differentiator'
//  '<S91>'  : 'controller/Discrete PID Controller1/I Gain/Internal Parameters'
//  '<S92>'  : 'controller/Discrete PID Controller1/Ideal P Gain/Passthrough'
//  '<S93>'  : 'controller/Discrete PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S94>'  : 'controller/Discrete PID Controller1/Integrator/Discrete'
//  '<S95>'  : 'controller/Discrete PID Controller1/Integrator ICs/Internal IC'
//  '<S96>'  : 'controller/Discrete PID Controller1/N Copy/Disabled wSignal Specification'
//  '<S97>'  : 'controller/Discrete PID Controller1/N Gain/Passthrough'
//  '<S98>'  : 'controller/Discrete PID Controller1/P Copy/Disabled'
//  '<S99>'  : 'controller/Discrete PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S100>' : 'controller/Discrete PID Controller1/Reset Signal/Disabled'
//  '<S101>' : 'controller/Discrete PID Controller1/Saturation/Passthrough'
//  '<S102>' : 'controller/Discrete PID Controller1/Saturation Fdbk/Disabled'
//  '<S103>' : 'controller/Discrete PID Controller1/Sum/Sum_PID'
//  '<S104>' : 'controller/Discrete PID Controller1/Sum Fdbk/Disabled'
//  '<S105>' : 'controller/Discrete PID Controller1/Tracking Mode/Disabled'
//  '<S106>' : 'controller/Discrete PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S107>' : 'controller/Discrete PID Controller1/Tsamp - Integral/TsSignalSpecification'
//  '<S108>' : 'controller/Discrete PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S109>' : 'controller/Discrete PID Controller1/postSat Signal/Forward_Path'
//  '<S110>' : 'controller/Discrete PID Controller1/preInt Signal/Internal PreInt'
//  '<S111>' : 'controller/Discrete PID Controller1/preSat Signal/Forward_Path'

#endif                                 // controller_h_

//
// File trailer for generated code.
//
// [EOF]
//
