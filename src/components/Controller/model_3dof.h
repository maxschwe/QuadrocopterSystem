//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: model_3dof.h
//
// Code generated for Simulink model 'model_3dof'.
//
// Model version                  : 1.36
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Mon Nov 17 17:40:45 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef model_3dof_h_
#define model_3dof_h_
#include <cmath>
#include "rtwtypes.h"
#include "model_3dof_types.h"

// Class declaration for model model_3dof
class model_3dof final
{
  // public data and function members
 public:
  // External outputs (root outports fed by signals with default storage)
  struct ExtY_model_3dof_T {
    real_T throttle1;                  // '<Root>/throttle1'
    real_T throttle2;                  // '<Root>/throttle2'
    real_T throttle3;                  // '<Root>/throttle3'
    real_T throttle4;                  // '<Root>/throttle4'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_model_3dof_T {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Copy Constructor
  model_3dof(model_3dof const&) = delete;

  // Assignment Operator
  model_3dof& operator= (model_3dof const&) & = delete;

  // Move Constructor
  model_3dof(model_3dof &&) = delete;

  // Move Assignment Operator
  model_3dof& operator= (model_3dof &&) = delete;

  // Real-Time Model get method
  model_3dof::RT_MODEL_model_3dof_T * getRTM();

  // Root outports get method
  const ExtY_model_3dof_T &getExternalOutputs() const
  {
    return model_3dof_Y;
  }

  // model initialize function
  static void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  model_3dof();

  // Destructor
  ~model_3dof();

  // private data and function members
 private:
  // External outputs
  ExtY_model_3dof_T model_3dof_Y;

  // Real-Time Model
  RT_MODEL_model_3dof_T model_3dof_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Discrete State-Space' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
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
//  '<Root>' : 'model_3dof'
//  '<S1>'   : 'model_3dof/MATLAB Function'
//  '<S2>'   : 'model_3dof/MATLAB Function1'

#endif                                 // model_3dof_h_

//
// File trailer for generated code.
//
// [EOF]
//
