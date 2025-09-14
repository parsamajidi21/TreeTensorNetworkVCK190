// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <adf/stream/types.h>

void contraction30(input_stream<int32>* in0, input_stream<int32>* in1, output_stream<int32>* out);
void contraction31(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction32(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction33(input_stream<int32>* in0, input_stream<int32>* in1, output_stream<int32>* out);
void contraction34(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction35(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction36(input_stream<int32>* in0, input_stream<int32>* in1, output_stream<int32>* out);
void contraction37(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction20(input_stream<int32>* in0, input_stream<int32>* in1, output_stream<int32>* out);
void contraction21(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction22(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction23(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction10(input_stream<int32>* in0, input_stream<int32>* in1, output_stream<int32>* out);
void contraction11(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);
void contraction00(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out);

#endif /**********__KERNELS_H__**********/
