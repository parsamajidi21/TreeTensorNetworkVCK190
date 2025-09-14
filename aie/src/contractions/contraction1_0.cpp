#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction10(input_stream_int32* __restrict in1, input_stream_int32* __restrict in2, output_stream_int32* __restrict out) {

    constexpr int TILE_SIZE = 8192; // <8k> elements per tile
    for (int tile = 0; tile < 644264; tile += TILE_SIZE) chess_prepare_for_pipelining {
        int end = std::min(tile + TILE_SIZE, 644264);
        for(int o = tile; o < end; o++) chess_prepare_for_pipelining {

    v16int32 in0_v_0;
    v16int32 in1_v_0;
    
    v8acc80 mul_a;
    v8int32 mul_v[20];
    v8acc80 out_a, out_a_1;
    out_a = null_v8acc80();
    out_a_1 = null_v8acc80();
        mul_a = null_v8acc80();

        in0_v_0 = readincr_v<16, aie_stream_resource_in::a>(in1);
        in1_v_0 = readincr_v<16, aie_stream_resource_in::b>(in2);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 2; j++){
                mul_a = lmul8(in0_v_0/*xbuff*/, i/*xstart*/, 0x00000000/*xoffset*/, in1_v_0/*zbuff*/, j*8/*zstart*/, 0x76543210/*zoffset*/);
                mul_v[(i*2)+j] = srs(mul_a, 0);
            }
        }
        int l=0;
        int m=0;
        int k=0;
        int n=0;
        for (int v = 0; v < 1600; v += 16) {
            alignas(64) aie::vector<int32_t, 16> Wv = aie::load_v<16>(&W10[v]);
            if (l < 8){
                switch (l){
                    case 0: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 0, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 0, 0x00000000);
                            break;
                    case 1: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 1, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 1, 0x00000000);
                            break;
                    case 2: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 2, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 2, 0x00000000);
                            break;
                    case 3: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 3, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 3, 0x00000000);
                            break;
                    case 4: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 4, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 4, 0x00000000);
                            break;
                    case 5: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 5, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 5, 0x00000000);
                            break;
                    case 6: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 6, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 6, 0x00000000);
                            break;
                    case 7: 
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[k*2], 7, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[k*2], 7, 0x00000000);
                            break;
                    default: break;   
                }
                l++;
            }
            else {
                switch(m){
                    case 0:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 0, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 0, 0x00000000);
                            break;
                    case 1:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 1, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 1, 0x00000000);
                            break;
                    case 2:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 2, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 2, 0x00000000);
                            break;
                    case 3:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 3, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 3, 0x00000000);
                            break;
                    case 4:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 4, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 4, 0x00000000);
                            break;
                    case 5:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 5, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 5, 0x00000000);
                            break;
                    case 6:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 6, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 6, 0x00000000);
                            break;
                    case 7:
                            out_a = lmac8(out_a, yset_x(0,Wv)/**/, 0, 0x76543210, mul_v[(k*2)+1], 7, 0x00000000);
                            out_a_1 = lmac8(out_a_1, yset_x(0,Wv)/**/, 8, 0x76543210, mul_v[(k*2)+1], 7, 0x00000000);
                            break;
                    default: break;
                }
                m++;
            }
            n++;
            if (n == 10){k++; l=m=0; n=0;}
            // if(l >= 8 && m > 8){l=0;m=0; k++;}
        }
        aie::vector<int32_t, 16>out_10(ext_elem(srs(out_a,28),0),  ext_elem(srs(out_a,28),1),  ext_elem(srs(out_a,28),2),ext_elem(srs(out_a,28),3),
                                ext_elem(srs(out_a,28),4), ext_elem(srs(out_a,28),5), ext_elem(srs(out_a,28),6), ext_elem(srs(out_a,28),7),
                                ext_elem(srs(out_a_1,28),0), ext_elem(srs(out_a_1,28),1), 0, 0, 0, 0, 0, 0);
        v8int32 tmp = srs(out_a, 28);
        v8int32 tmp1 = srs(out_a_1, 28);
        for (int l = 0; l < 10; l++){
            if (l < 8)
                writeincr<aie_stream_resource_out::a>(out, ext_elem(tmp, l)); 
            else
                writeincr<aie_stream_resource_out::a>(out, ext_elem(tmp1, l-8));
        }
        //writeincr(out,out_10);
    }
    }
}