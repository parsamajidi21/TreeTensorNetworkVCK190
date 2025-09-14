// Copyright (C) 2025 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <adf/stream/types.h>

void contraction30(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction31(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction32(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction33(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction34(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction35(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction36(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction37(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);

void contraction20(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction21(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction22(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction23(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);

void contraction10(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);
void contraction11(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);

void contraction00(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out);

#endif /**********__KERNELS_H__**********/
