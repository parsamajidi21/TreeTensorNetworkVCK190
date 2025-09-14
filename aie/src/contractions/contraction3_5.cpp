#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"

using namespace adf;

void contraction35(input_stream_int32* __restrict in0, input_stream_int32* __restrict in1, output_stream_int32* __restrict out) {

    v4int32 in0_v;
    v4int32 in1_v;
    v8acc80 mul_a;
    v4int32 mul_v;
    v4acc80 out_a;

    constexpr int TILE_SIZE = 8192; // <8k> elements per tile
    alignas(64) v16int32 Wv = *((v16int32*)W35);
    for (int tile = 0; tile < 644264; tile += TILE_SIZE) chess_prepare_for_pipelining {
        int end = std::min(tile + TILE_SIZE, 644264);
        for(int o = tile; o < end; o++) chess_prepare_for_pipelining {
        in0_v = readincr_v<4, aie_stream_resource_in::a>(in0);
        in1_v = readincr_v<4, aie_stream_resource_in::b>(in1);
        mul_a = null_v8acc80();
        //Outer Product
        mul_a = lmul8(yset_v(0,in0_v)/*xbuff*/, 0/*xstart*/, 0x1100/*xoffset*/, wset_v(0,in1_v)/*zbuff*/, 0/*zstart*/, 0x1010/*zoffset*/);
        mul_v = srs(ext_lo(mul_a),0); /*Convert accumulator to vector*/
        
        out_a = null_v4acc80();
        //MAC

        out_a = lmac4(out_a, yset_x(0,Wv)/**/, 0, 0xC840, 1, wset_v(0,mul_v), 0, 0x0000, 1);
        out_a = lmac4(out_a, yset_x(0,Wv)/**/, 2, 0xC840, 1, wset_v(0,mul_v), 2, 0x0000, 1);
        //printf("out_a_contraction00_%d = %d %d %d %d \n", i+1, ext_elem(srs(out_a,28),0), ext_elem(srs(out_a,28),1),
        //                                                ext_elem(srs(out_a,28),2), ext_elem(srs(out_a,28),3));
        writeincr_v4<aie_stream_resource_out::a>(out,srs(out_a,28));
    }
    }
}