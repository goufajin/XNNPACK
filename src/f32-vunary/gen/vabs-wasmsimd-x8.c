// Auto-generated file. Do not edit!
//   Template: src/f32-vunary/wasmsimd.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f32_vabs_ukernel__wasmsimd_x8(
    size_t batch,
    const float* input,
    float* output,
    const union xnn_f32_abs_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const v128_t vnonsign_mask = wasm_v128_load64_splat(&params->wasmsimd.nonsign_mask);
  for (; batch >= 8 * sizeof(float); batch -= 8 * sizeof(float)) {
    const v128_t vx0123 = wasm_v128_load(input);
    const v128_t vx4567 = wasm_v128_load(input + 4);
    input += 8;

    const v128_t vy0123 = wasm_v128_and(vx0123, vnonsign_mask);
    const v128_t vy4567 = wasm_v128_and(vx4567, vnonsign_mask);

    wasm_v128_store(output, vy0123);
    wasm_v128_store(output + 4, vy4567);
    output += 8;
  }
  for (; batch >= 4 * sizeof(float); batch -= 4 * sizeof(float)) {
    const v128_t vx = wasm_v128_load(input);
    input += 4;

    const v128_t vy = wasm_v128_and(vx, vnonsign_mask);

    wasm_v128_store(output, vy);
    output += 4;
  }
  if XNN_UNLIKELY(batch != 0) {
    const v128_t vx = wasm_v128_load(input);
    v128_t vy = wasm_v128_and(vx, vnonsign_mask);
    if (batch & (2 * sizeof(float))) {
      *((double*) output) = wasm_f64x2_extract_lane(vy, 0);
      vy = wasm_v32x4_shuffle(vy, vy, 2, 3, 2, 3);
      output += 2;
    }
    if (batch & (1 * sizeof(float))) {
      *output = wasm_f32x4_extract_lane(vy, 0);
    }
  }
}
