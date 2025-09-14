#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"

using namespace adf;

void contraction00(input_stream_int32* in0, input_stream_int32* in1, output_stream_int32* out) {

    aie::vector<int32_t, 4> in0_v;
    aie::vector<int32_t, 4> in1_v;
    aie::accum<acc80, 4> mul_a;
    aie::vector <int32_t, 4> mul_v[2];
    aie::vector<int32_t, 8> outer_prod;
    alignas(32) int32_t temp[4];
    aie::vector<int32_t, 4> outer_prod1;
    aie::accum<acc80, 4> out_a;
    aie::vector<int32_t, 16> Wv = *((aie::vector<int32_t, 16>*)W00);

    for (int l = 0; l < 100; l++) {
        in0_v = readincr_v<4>(in0);
        in1_v = readincr_v<4>(in1);
        mul_a = aie::zeros<acc80, 4>();
        //Outer Product
        for (int i = 0; i < 2; i++) {
            aie::vector<int32_t, 4> in0_elem = aie::broadcast<int32_t, 4>(in0_v[i]);
            mul_a = aie::mul(in0_elem, in1_v);
            mul_v[i] = srs(mul_a,0);
        }
        outer_prod = aie::concat(mul_v[0],mul_v[1]);
        int count = 0;
        for (int i = 0; i < 8 && count < 4; i++) {
            int val = ext_elem(outer_prod, i);
            if (val != 0) {
                temp[count++] = val;
            }
        }
        outer_prod1 = aie::load_v<4>(temp);
        //printf("outer_prod1 = %d,%d,%d,%d\n", ext_elem(outer_prod1,0),ext_elem(outer_prod1,1),ext_elem(outer_prod1,2),ext_elem(outer_prod1,3));
        //MAC
        out_a = null_v4acc80();
        int32_t Wv_arr[4];
        int countq = 0;
        for (int j = 0; j < 16; j+=4) {
            out_a = null_v4acc80();
            for (int i = 0; i < 4; i++) {
                Wv_arr[i] = ext_elem(Wv, i+j);
            }
            aie::vector<int32_t, 4> Wv_4(Wv_arr[0], Wv_arr[1], Wv_arr[2], Wv_arr[3]);
            //printf("Wv_4 = %d,%d,%d,%d\n", ext_elem(Wv_4,0),ext_elem(Wv_4,1),ext_elem(Wv_4,2),ext_elem(Wv_4,3));
            out_a = aie::mac(out_a, outer_prod1, Wv_4);
            //printf("out_a = %d %d %d %d \n", ext_elem(srs(out_a,28),0), ext_elem(srs(out_a,28),1),
            //                                ext_elem(srs(out_a,28),2), ext_elem(srs(out_a,28),3));
            temp[countq++] = ext_elem(srs(out_a,28),0) + ext_elem(srs(out_a,28),1) +
                            ext_elem(srs(out_a,28),2) + ext_elem(srs(out_a,28),3);
        }
        aie::vector<int32_t, 4> out_mac_00(temp[0],temp[1],temp[2],temp[3]); 
        //printf("out_mac_00 = %d %d %d %d \n", ext_elem(out_mac_00,0), ext_elem(out_mac_00,1),
        //                                   ext_elem(out_mac_00,2), ext_elem(out_mac_00,3));
        writeincr_v4(out, out_mac_00);
    }
}