// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef __KERNELS_H__
#define __KERNELS_H__

#include <adf/stream/types.h>

void contraction00(input_stream_int32* in0, input_stream_int32* in1, output_stream_int32* out);
void contraction01(input_stream_int32* in1, input_stream_int32* in2, output_stream_int32* out);
void contraction10(input_stream_int32* in1, input_stream_int32* in2, output_stream_int32* out);

#endif /**********__KERNELS_H__**********/
