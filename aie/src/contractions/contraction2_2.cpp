#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction22(input_stream_float* __restrict in0, input_stream_float* __restrict in1, output_stream_float* __restrict out) {

    v4float in0_v, in1_v;
    v8float mul0_a, mul1_a;
    v16float mul_v;
    v8float out_a, out_a_1;
    v16float out_v;
    v8float scale_vec = aie::broadcast<float, 8>(1.0f / 268435456.0f);

    for(int k = 0; k < 644264; k++)chess_prepare_for_pipelining{
        in0_v = readincr_v4<aie_stream_resource_in::a>(in0);
        in1_v = readincr_v4<aie_stream_resource_in::a>(in1);

        out_a = null_v8float();

        mul0_a = fpmul(yset_v(0,in0_v),0,0x11110000,wset_v(0,in1_v),0,0x32103210);
        mul1_a = fpmul(yset_v(0,in0_v),0,0x33332222,wset_v(0,in1_v),0,0x32103210);
        int l=0;
        int m=0;
        for (int v = 0; v < 256; v += 16) {
            aie::vector<float, 16> Wv = aie::load_v<16>(&W22[v]);
            if (l < 8){
                switch (l) {
                case 0: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 0, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 0, 0x00000000);
                break;
                case 1: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 1, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 1, 0x00000000);
                break;
                case 2: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 2, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 2, 0x00000000);
                break;
                case 3: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 3, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 3, 0x00000000);
                break;
                case 4: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 4, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 4, 0x00000000);
                break;
                case 5: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 5, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 5, 0x00000000);
                break;
                case 6: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 6, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 6, 0x00000000);
                break;
                case 7: 
                        out_a = fpmac(out_a, Wv, 0, 0x76543210, mul0_a, 7, 0x00000000);
                        out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul0_a, 7, 0x00000000);
                break;
                default: break;
                }

                l++;
            }
            else {
                switch (m) {
                case 0:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 0, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 0, 0x00000000);
                break;
                case 1:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 1, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 1, 0x00000000);
                break;
                case 2:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 2, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 2, 0x00000000);
                break;
                case 3:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 3, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 3, 0x00000000);
                break;
                case 4:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 4, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 4, 0x00000000);
                break;
                case 5:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 5, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 5, 0x00000000);
                break;
                case 6:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 6, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 6, 0x00000000);
                break;
                case 7:
                out_a = fpmac(out_a, Wv, 0, 0x76543210, mul1_a, 7, 0x00000000);
                out_a_1 = fpmac(out_a_1, Wv, 8, 0x76543210, mul1_a, 7, 0x00000000);
                break;
                default: break;
                } 
                m++;
            }
        }
        aie::vector<float, 8>out_22_0(ext_elem(out_a,0),  ext_elem(out_a,1),  ext_elem(out_a,2), ext_elem(out_a,3),
                        ext_elem(out_a,4), ext_elem(out_a,5), ext_elem(out_a,6), ext_elem(out_a,7));
        aie::vector<float, 8>out_22_1(ext_elem(out_a_1,0), ext_elem(out_a_1,1), 0, 0, 0, 0, 0, 0);

        out_22_0 = fpmul(out_22_0, scale_vec);
        out_22_1 = fpmul(out_22_1, scale_vec);
        aie::vector<float, 16>out_22 = concat(out_22_0,out_22_1);
        
        writeincr(out,out_22);
    }
}
