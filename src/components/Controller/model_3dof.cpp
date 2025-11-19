//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: model_3dof.cpp
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
#include "model_3dof.h"
#include <cstring>
#include <cmath>
#include <emmintrin.h>
#include "rtwtypes.h"

// Model step function
void model_3dof::step()
{
  __m128d tmp;
  real_T A[16];
  real_T rtb_u[4];
  real_T tmp_0[2];
  real_T s;
  real_T smax;
  int32_T b_i;
  int32_T c_k;
  int32_T ijA;
  int32_T j;
  int32_T jA;
  int32_T jj;
  int32_T n;
  int8_T ipiv[4];
  int8_T ipiv_0;
  static const real_T d[16]{ 1.0, 0.0, 0.2, 0.0351, 1.0, -0.2, 0.0, -0.0351, 1.0,
    0.0, -0.2, 0.0351, 1.0, 0.2, 0.0, -0.0351 };

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   Constant: '<Root>/tau'

  rtb_u[0] = 2.0;
  rtb_u[1] = -0.01;
  rtb_u[2] = 0.05;
  rtb_u[3] = 0.0;
  std::memcpy(&A[0], &d[0], sizeof(real_T) << 4U);
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  for (j = 0; j < 3; j++) {
    jj = j * 5;
    n = 5 - j;
    jA = 0;
    smax = std::abs(A[jj]);
    for (c_k = 2; c_k < n; c_k++) {
      s = std::abs(A[(jj + c_k) - 1]);
      if (s > smax) {
        jA = c_k - 1;
        smax = s;
      }
    }

    if (A[jj + jA] != 0.0) {
      if (jA != 0) {
        n = j + jA;
        ipiv[j] = static_cast<int8_T>(n + 1);
        smax = A[j];
        A[j] = A[n];
        A[n] = smax;
        smax = A[j + 4];
        A[j + 4] = A[n + 4];
        A[n + 4] = smax;
        smax = A[j + 8];
        A[j + 8] = A[n + 8];
        A[n + 8] = smax;
        smax = A[j + 12];
        A[j + 12] = A[n + 12];
        A[n + 12] = smax;
      }

      n = (jj - j) + 4;
      jA = (((((n - jj) - 1) / 2) << 1) + jj) + 2;
      c_k = jA - 2;
      for (b_i = jj + 2; b_i <= c_k; b_i += 2) {
        tmp = _mm_loadu_pd(&A[b_i - 1]);
        _mm_storeu_pd(&A[b_i - 1], _mm_div_pd(tmp, _mm_set1_pd(A[jj])));
      }

      for (b_i = jA; b_i <= n; b_i++) {
        A[b_i - 1] /= A[jj];
      }
    }

    n = 2 - j;
    jA = jj + 6;
    for (c_k = 0; c_k <= n; c_k++) {
      smax = A[((c_k << 2) + jj) + 4];
      if (smax != 0.0) {
        b_i = (jA - j) + 2;
        for (ijA = jA; ijA <= b_i; ijA++) {
          A[ijA - 1] += A[((jj + ijA) - jA) + 1] * -smax;
        }
      }

      jA += 4;
    }

    ipiv_0 = ipiv[j];
    if (j + 1 != ipiv_0) {
      smax = rtb_u[j];
      rtb_u[j] = rtb_u[ipiv_0 - 1];
      rtb_u[ipiv_0 - 1] = smax;
    }
  }

  for (j = 0; j < 4; j++) {
    jj = j << 2;
    if (rtb_u[j] != 0.0) {
      for (n = j + 2; n < 5; n++) {
        rtb_u[n - 1] -= A[(n + jj) - 1] * rtb_u[j];
      }
    }
  }

  for (j = 3; j >= 0; j--) {
    jj = j << 2;
    smax = rtb_u[j];
    if (smax != 0.0) {
      rtb_u[j] = smax / A[j + jj];
      for (n = 0; n < j; n++) {
        rtb_u[n] -= A[n + jj] * rtb_u[j];
      }
    }
  }

  tmp = _mm_set1_pd(8.5908);
  _mm_storeu_pd(&tmp_0[0], _mm_add_pd(_mm_set_pd(std::sqrt(rtb_u[1] / 0.0013),
    std::sqrt(rtb_u[0] / 0.0013)), tmp));

  // Outport: '<Root>/throttle1'
  model_3dof_Y.throttle1 = tmp_0[0];

  // Outport: '<Root>/throttle2'
  model_3dof_Y.throttle2 = tmp_0[1];

  // MATLAB Function: '<Root>/MATLAB Function'
  _mm_storeu_pd(&tmp_0[0], _mm_add_pd(_mm_set_pd(std::sqrt(rtb_u[3] / 0.0013),
    std::sqrt(rtb_u[2] / 0.0013)), tmp));

  // Outport: '<Root>/throttle3'
  model_3dof_Y.throttle3 = tmp_0[0];

  // Outport: '<Root>/throttle4'
  model_3dof_Y.throttle4 = tmp_0[1];
}

// Model initialize function
void model_3dof::initialize()
{
  // (no initialization code required)
}

// Model terminate function
void model_3dof::terminate()
{
  // (no terminate code required)
}

const char_T* model_3dof::RT_MODEL_model_3dof_T::getErrorStatus() const
{
  return (errorStatus);
}

void model_3dof::RT_MODEL_model_3dof_T::setErrorStatus(const char_T* const
  volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
model_3dof::model_3dof() :
  model_3dof_Y(),
  model_3dof_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
model_3dof::~model_3dof() = default;

// Real-Time Model get method
model_3dof::RT_MODEL_model_3dof_T * model_3dof::getRTM()
{
  return (&model_3dof_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
