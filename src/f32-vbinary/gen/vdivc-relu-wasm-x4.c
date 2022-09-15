// Auto-generated file. Do not edit!
//   Template: src/f32-vbinary/vopc-scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vbinary.h>


void xnn_f32_vdivc_relu_ukernel__wasm_x4(
    size_t batch,
    const float* input_a,
    const float* input_b,
    float* output,
    const union xnn_f32_relu_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input_a != NULL);
  assert(input_b != NULL);
  assert(output != NULL);


  const float vb = *input_b;
  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    const float va0 = input_a[0];
    const float va1 = input_a[1];
    const float va2 = input_a[2];
    const float va3 = input_a[3];
    input_a += 4;

    float vy0 = va0 / vb;
    float vy1 = va1 / vb;
    float vy2 = va2 / vb;
    float vy3 = va3 / vb;


    vy0 = __builtin_wasm_max_f32(vy0, 0.0f);
    vy1 = __builtin_wasm_max_f32(vy1, 0.0f);
    vy2 = __builtin_wasm_max_f32(vy2, 0.0f);
    vy3 = __builtin_wasm_max_f32(vy3, 0.0f);

    output[0] = vy0;
    output[1] = vy1;
    output[2] = vy2;
    output[3] = vy3;
    output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    do {
      const float va = *input_a++;
      float vy = va / vb;
      vy = __builtin_wasm_max_f32(vy, 0.0f);
      *output++ = vy;
      batch -= sizeof(float);
    } while (batch != 0);
  }
}
