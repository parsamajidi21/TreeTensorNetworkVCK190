// Copyright (C) 2025 Advanced Micro Devices, Inc
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

class treeTensor : public graph {
    private:
        kernel node37, node36, node35, node34, node33, node32, node31, node30;
        kernel node23, node22, node21, node20;
        kernel node11, node10;
        kernel node00;
        

    public:
        input_plio p_s0, p_s1, p_s2, p_s3;
        input_plio p_s4, p_s5, p_s6, p_s7;
        input_plio p_s8, p_s9, p_s10, p_s11;
        input_plio p_s12, p_s13, p_s14, p_s15;
        output_plio p_s_out; 

simpleGraph() {
            // create kernel & define source code
#ifdef STREAM
            node30 = kernel::create(contraction30);
            node31 = kernel::create(contraction31);
            node32 = kernel::create(contraction32);
            node33 = kernel::create(contraction33);
            node34 = kernel::create(contraction34);
            node35 = kernel::create(contraction35);
            node36 = kernel::create(contraction36);
            node37 = kernel::create(contraction37);
            node20 = kernel::create(contraction20);
            node21 = kernel::create(contraction21);
            node22 = kernel::create(contraction22);
            node23 = kernel::create(contraction23);
            node10 = kernel::create(contraction10);
            node11 = kernel::create(contraction11);
            node00 = kernel::create(contraction00);
            stack_size(node30) = 2048;
            stack_size(node31) = 2048;
            stack_size(node32) = 2048;
            stack_size(node33) = 2048;
            stack_size(node34) = 2048;
            stack_size(node35) = 2048;
            stack_size(node36) = 2048;
            stack_size(node37) = 2048;

            stack_size(node20) = 2048;
            stack_size(node21) = 2048;
            stack_size(node22) = 2048;
            stack_size(node23) = 2048;

            stack_size(node10) = 2048;
            stack_size(node11) = 2048;

            stack_size(node00) = 2048;
            source(node30) = "contractions/contraction3_0.cpp";
            source(node31) = "contractions/contraction3_1.cpp";
            source(node32) = "contractions/contraction3_2.cpp";
            source(node33) = "contractions/contraction3_3.cpp";
            source(node34) = "contractions/contraction3_4.cpp";
            source(node35) = "contractions/contraction3_5.cpp";
            source(node36) = "contractions/contraction3_6.cpp";
            source(node37) = "contractions/contraction3_7.cpp";
            source(node20) = "contractions/contraction2_0.cpp";
            source(node21) = "contractions/contraction2_1.cpp";
            source(node22) = "contractions/contraction2_2.cpp";
            source(node23) = "contractions/contraction2_3.cpp";
            source(node10) = "contractions/contraction1_0.cpp";
            source(node11) = "contractions/contraction1_1.cpp";
            source(node00) = "contractions/contraction0_0.cpp";
#endif
            // Define connection names and text file source/sink
            p_s0 = input_plio::create("StreamIn0", plio_128_bits,"data/input1.txt");
            p_s1 = input_plio::create("StreamIn1", plio_128_bits,"data/input2.txt");
            p_s2 = input_plio::create("StreamIn2", plio_128_bits,"data/input3.txt");
            p_s3 = input_plio::create("StreamIn3", plio_128_bits,"data/input4.txt");
            p_s4 = input_plio::create("StreamIn4", plio_128_bits,"data/input5.txt");
            p_s5 = input_plio::create("StreamIn5", plio_128_bits,"data/input6.txt");
            p_s6 = input_plio::create("StreamIn6", plio_128_bits,"data/input7.txt");
            p_s7 = input_plio::create("StreamIn7", plio_128_bits,"data/input8.txt");
            p_s8 = input_plio::create("StreamIn8", plio_128_bits,"data/input9.txt"); 
            p_s9 = input_plio::create("StreamIn9", plio_128_bits,"data/input10.txt");
            p_s10 = input_plio::create("StreamIn10", plio_128_bits,"data/input11.txt");
            p_s11 = input_plio::create("StreamIn11", plio_128_bits,"data/input12.txt");
            p_s12 = input_plio::create("StreamIn12", plio_128_bits,"data/input13.txt"); 
            p_s13 = input_plio::create("StreamIn13", plio_128_bits,"data/input14.txt");
            p_s14 = input_plio::create("StreamIn14", plio_128_bits,"data/input15.txt");
            p_s15 = input_plio::create("StreamIn15", plio_128_bits,"data/input16.txt");
            p_s_out = output_plio::create("StreamOut0", plio_128_bits,"data/output.txt");

           connect<CONNECTION>(p_s0.out[0], node30.in[0]);
           connect<CONNECTION>(p_s1.out[0], node30.in[1]);
           connect<CONNECTION>(p_s2.out[0], node31.in[0]);
           connect<CONNECTION>(p_s3.out[0], node31.in[1]);
           connect<CONNECTION>(p_s4.out[0], node32.in[0]);
           connect<CONNECTION>(p_s5.out[0], node32.in[1]);
           connect<CONNECTION>(p_s6.out[0], node33.in[0]);
           connect<CONNECTION>(p_s7.out[0], node33.in[1]);
           connect<CONNECTION>(p_s8.out[0], node34.in[0]);
           connect<CONNECTION>(p_s9.out[0], node34.in[1]);
           connect<CONNECTION>(p_s10.out[0], node35.in[0]);
           connect<CONNECTION>(p_s11.out[0], node35.in[1]);
           connect<CONNECTION>(p_s12.out[0], node36.in[0]);
           connect<CONNECTION>(p_s13.out[0], node36.in[1]);
           connect<CONNECTION>(p_s14.out[0], node37.in[0]);
           connect<CONNECTION>(p_s15.out[0], node37.in[1]); 
           connect<CONNECTION>(node30.out[0], node20.in[0]);
           connect<CONNECTION>(node31.out[0], node20.in[1]);
           connect<CONNECTION>(node32.out[0], node21.in[0]);
           connect<CONNECTION>(node33.out[0], node21.in[1]);
           connect<CONNECTION>(node34.out[0], node22.in[0]);
           connect<CONNECTION>(node35.out[0], node22.in[1]);
           connect<CONNECTION>(node36.out[0], node23.in[0]);
           connect<CONNECTION>(node37.out[0], node23.in[1]);
           connect<CONNECTION>(node20.out[0], node10.in[0]);
           connect<CONNECTION>(node21.out[0], node10.in[1]);
           connect<CONNECTION>(node22.out[0], node11.in[0]);
           connect<CONNECTION>(node23.out[0], node11.in[1]);

           connect<CONNECTION>(node10.out[0], node00.in[0]);
           connect<CONNECTION>(node11.out[0], node00.in[1]);

           connect<CONNECTION>(node00.out[0], p_s_out.in[0]);
           // Define kernel runtime ratio
           runtime<ratio>(node30) = .3;
           runtime<ratio>(node31) = .3;
           runtime<ratio>(node32) = .3;
           runtime<ratio>(node33) = .3;
           runtime<ratio>(node34) = .3;
           runtime<ratio>(node35) = .3;
           runtime<ratio>(node36) = .3;
           runtime<ratio>(node37) = .3;
           runtime<ratio>(node20) = .7;
           runtime<ratio>(node21) = .7;
           runtime<ratio>(node22) = .7;
           runtime<ratio>(node23) = .7;
           runtime<ratio>(node10) = .8;
           runtime<ratio>(node11) = .8;
           runtime<ratio>(node00) = .9;
        };
};

#endif /**********__GRAPH_H__**********/
