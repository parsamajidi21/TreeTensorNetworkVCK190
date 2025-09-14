#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction00(input_stream_float* __restrict in1, input_stream_float* __restrict in2, output_stream_float* __restrict out) {


    v16float in0_v_0;
    v16float in1_v_0;
    
    v8float mul_a;
    v8float mul_v[20];
    v8float out_a, out_a_1;
    for(int k = 0; k < 644264; k++) chess_prepare_for_pipelining{

        in0_v_0 = readincr_v<16>(in1);
        in1_v_0 = readincr_v<16>(in2);
        v4float in1_v_lo0 = ext_v(in1_v_0, 0);
        v4float in1_v_hi0 = ext_v(in1_v_0, 1);
        v4float in1_v_lo1 = ext_v(in1_v_0, 2);
        v4float in1_v_hi1 = ext_v(in1_v_0, 3);
        v8float in1_v[2];
        in1_v[0] = concat(in1_v_lo0, in1_v_hi0);
        in1_v[1] = concat(in1_v_lo1, in1_v_hi1);
        v8float scale_vec = aie::broadcast<float, 8>(1.0f / 268435456.0f);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 2; j++){
                mul_a = fpmul(in0_v_0,i,0x00000000,in1_v[j] ,0,0x76543210);
                mul_v[(i*2)+j] = mul_a;
            }
        }
        int l=0;
        int m=0;
        int k=0;
        int n=0;
        for (int v = 0; v < 800; v += 8) {
            aie::vector<float, 8> Wv = aie::load_v<8>(&W00[v]);
            if (l < 8){ 
                switch (l) {
                case 0:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 0, 0x00000000); break;
                case 1:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 1, 0x00000000); break;
                case 2:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 2, 0x00000000); break;
                case 3:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 3, 0x00000000); break;
                case 4:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 4, 0x00000000); break;
                case 5:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 5, 0x00000000); break;
                case 6:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 6, 0x00000000); break;
                case 7:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 7, 0x00000000); break;
                }
                l++;
            }
            else {
                switch (m) {
                case 0:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 0, 0x00000000); break;
                case 1:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 1, 0x00000000); break;
                case 2:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 2, 0x00000000); break;
                case 3:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 3, 0x00000000); break;
                case 4:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 4, 0x00000000); break;
                case 5:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 5, 0x00000000); break;
                case 6:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 6, 0x00000000); break;
                case 7:
                    out_a = fpmac(out_a, yset_w(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 7, 0x00000000); break;
                }
                m++;
            }
            n++;
            if (n == 10){k++; l=m=0; n=0;}
        }
       
        aie::vector<float, 8>out_00(ext_elem(out_a,0),  ext_elem(out_a,1), ext_elem(out_a,2),ext_elem(out_a,3),ext_elem(out_a,4));
        out_00 = fpmul(out_00, scale_vec);
        printf("out_00: %f %f %f %f %f\n", ext_elem(out_00,0),  ext_elem(out_00,1),  ext_elem(out_00,2), ext_elem(out_00,3),
                        ext_elem(out_00,4));
        writeincr(out,out_00);
    }
}
