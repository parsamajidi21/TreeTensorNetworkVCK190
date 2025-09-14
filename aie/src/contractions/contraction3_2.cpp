#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"

using namespace adf;


void contraction32(input_stream_float* __restrict in0, input_stream_float* __restrict in1, output_stream_float* __restrict out) {

    v4float in0_v, in1_v;
    v8float mul_a;
    v4float mul_v;
    v8float out_a;
    v16float Wv = *((v16float*)W32);
    v8float scale_vec = aie::broadcast<float, 8>(1.0f / 268435456.0f);


    for (int i = 0; i < 644264; i++) {
        in0_v = readincr_v4<aie_stream_resource_in::a>(in0);
        in1_v = readincr_v4<aie_stream_resource_in::a>(in1);
        
        mul_a = fpmul(yset_v(0,in0_v)/*xbuff*/, 0/*xstart*/, 0x1100/*xoffset*/, wset_v(0,in1_v)/*zbuff*/, 0/*zstart*/, 0x1010/*zoffset*/);
        mul_v = ext_lo(mul_a); /*Convert accumulator to vector*/
        //printf("mul00_%d = %d,%d,%d,%d \n", i+1, ext_elem(mul_v,0),ext_elem(mul_v,1),ext_elem(mul_v,2),ext_elem(mul_v,3) );
    
        out_a = null_v8float();
    
        for(int j=0;j<4;j++) {
            out_a = fpmac(out_a, yset_x(0,Wv)/**/, j, 0xC840, mul_a, j, 0x0000);
            //printf("out_a_contraction00_%d = %d %d %d %d \n", i+1, ext_elem(srs(out_a,28),0), ext_elem(srs(out_a,28),1),
            //                                           ext_elem(srs(out_a,28),2), ext_elem(srs(out_a,28),3));
        }
        //out_a = fpmul(out_a,scale_vec);
        
        writeincr_v4<aie_stream_resource_out::a>(out,ext_lo(out_a));
    }
}
