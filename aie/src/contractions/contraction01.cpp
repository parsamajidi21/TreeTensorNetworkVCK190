#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction01(input_stream_int32* in1, input_stream_int32* in2, output_stream_int32* out) {

    v4int32 in0_v, in1_v;
    v8acc80 mul_a;
    v4int32 mul_v;
    v4acc80 out_a;
    v16int32 Wv = *((v16int32*)W01);

    for (int i = 0; i < 100; i++) {
        in0_v = readincr_v4(in1);
        in1_v = readincr_v4(in2);

        out_a = null_v4acc80();

        mul_a = lmul8(yset_v(0,in0_v)/*xbuff*/, 0/*xstart*/, 0x1100/*xoffset*/, wset_v(0,in1_v)/*zbuff*/, 0/*zstart*/, 0x1010/*zoffset*/);
        mul_v = srs(ext_lo(mul_a),0);
        //printf("mu_contraction_01l = %d,%d,%d,%d \n", ext_elem(mul_v,0),ext_elem(mul_v,1),ext_elem(mul_v,2),ext_elem(mul_v,3) );
        for(int j=0;j<2;j++) {
            out_a = lmac4(out_a,yset_x(0,Wv),j*2,0xC840,1,wset_v(0,mul_v),j*2,0x0000,1);
            //printf("out_a_contraction01_%d = %d %d %d %d \n", i,ext_elem(srs(out_a,28),0), ext_elem(srs(out_a,28),1),
            //                                                ext_elem(srs(out_a,28),2), ext_elem(srs(out_a,28),3));
        }

        writeincr_v4(out,srs(out_a,28));
    }
}
