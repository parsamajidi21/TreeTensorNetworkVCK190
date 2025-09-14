#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction10(input_stream_int32* in1, input_stream_int32* in2, output_stream_int32* out) {

    v4int32 in0_v, in1_v;
    v8acc80 mul0_a, mul1_a;
    v16int32 mul_v;
    v4acc80 out_a;
    v16int32 out_v;
    v16int32 Wv = *((v16int32*)W10);

    for (int i = 0; i < 100; i++) {
        in0_v = readincr_v4(in1);
        in1_v = readincr_v4(in2);

        out_a = null_v4acc80();

        mul0_a = lmul8(yset_v(0,in0_v),0,0x11110000,wset_v(0,in1_v),0,0x32103210);
        mul1_a = lmul8(yset_v(0,in0_v),0,0x33332222,wset_v(0,in1_v),0,0x32103210);
        /*printf("mul = ");
        for(int elem=0;elem<16;elem++) {
            printf("%d ", ext_elem(mul_v,elem));
        }
        printf("\n"); */
        for(int j=0;j<4;j++) {
            out_a = lmac4(out_a, Wv, j*2, 0x0000, 1, srs(mul0_a, 0), j*2, 0x0000, 1);
        }

        for(int j=0;j<4;j++) {
            out_a = lmac4(out_a, Wv, j*2+8, 0x0000, 1, srs(mul1_a, 0), j*2, 0x0000, 1);
        }
        //printf("%d\n", ext_elem(srs(out_a,28),0));
            
        writeincr(out,srs(out_a,28));
    }
}