// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <adf.h>
#include "kernels.hpp"

#define STREAM

#ifdef STREAM
#define CONNECTION stream
#endif

using namespace adf;

class simpleGraph : public graph {
    private:
        kernel node00, node01, node10;

    public:
        input_plio p_s0, p_s1, p_s2, p_s3;
        output_plio p_s4; //,p_s5;

simpleGraph() {
            // create kernel & define source code
#ifdef STREAM
            node00 = kernel::create(contraction00);
            node01 = kernel::create(contraction01);
            node10 = kernel::create(contraction10);
            source(node00) = "contractions/contraction00.cpp";
            source(node01) = "contractions/contraction01.cpp";
            source(node10) = "contractions/contraction10.cpp";
#endif
            // Define connection names and text file source/sink
            p_s0 = input_plio::create("StreamIn0", plio_128_bits,"/home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/data/input0.txt");
            p_s1 = input_plio::create("StreamIn1", plio_128_bits,"/home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/data/input1.txt");
            p_s2 = input_plio::create("StreamIn2", plio_128_bits,"/home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/data/input2.txt");
            p_s3 = input_plio::create("StreamIn3", plio_128_bits,"/home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/data/input3.txt");            
           
           
            p_s4 = output_plio::create("StreamOut0", plio_128_bits, "output.txt");
            //p_s5 = output_plio::create("StreamOut1", plio_128_bits, "output1.txt");

           connect<CONNECTION>(p_s0.out[0], node00.in[0]);
           connect<CONNECTION>(p_s1.out[0], node00.in[1]);
           connect<CONNECTION>(p_s2.out[0], node01.in[0]);
           connect<CONNECTION>(p_s3.out[0], node01.in[1]);

           connect<CONNECTION>(node00.out[0], node10.in[0]);
           connect<CONNECTION>(node01.out[0], node10.in[1]);

           connect<CONNECTION>(node10.out[0], p_s4.in[0]);
           // Define kernel runtime ratio
           runtime<ratio>(node00) = 1;
           runtime<ratio>(node01) = 1;
           runtime<ratio>(node10) = 1;
        };
};

#endif /**********__GRAPH_H__**********/
