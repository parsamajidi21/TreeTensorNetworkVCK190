#include "adf/window/types.h"
#include <aie_api/aie.hpp>
#include "luts.h"
using namespace adf;


void contraction10(input_stream<int32>* in1, input_stream<int32>* in2, output_stream<int32>* out) {


    aie::vector<int32_t, 4> in0_v;
    aie::vector<int32_t, 4> in1_v;
    aie::accum<acc80, 4> mul_a;
    aie::vector <int32_t, 4> mul_v[4];
    aie::vector<int32_t, 8> outer_prod1;
    aie::vector<int32_t, 8> outer_prod2;
    aie::accum<acc64, 8> out_a;
    aie::vector<int32_t, 16> Wv = *((aie::vector<int32_t, 16>*)W10);
    for (int l = 0; l < 100; l++) {
        in0_v = readincr_v<4>(in1);
        in1_v = readincr_v<4>(in2);
        //Outer Product
        mul_a = aie::zeros<acc80, 4>();
        for (int i = 0; i < 4; i++) {
            aie::vector<int32_t, 4> in10_elem = aie::broadcast<int32_t, 4>(in0_v[i]);
            mul_a = aie::mul(in10_elem, in1_v);
            mul_v[i] = srs(mul_a,0);
        }
        outer_prod1 = aie::concat(mul_v[0],mul_v[1]);
        outer_prod2 = aie::concat(mul_v[2],mul_v[3]);
        int32_t Wv_arr[8];
        int32_t Wv_arr1[8];
        for (int i = 0; i < 8; i++) {
            Wv_arr[i] = ext_elem(Wv, i);
            Wv_arr1[i] = ext_elem(Wv, i+8);
        }
        out_a = aie::zeros<acc80, 8>();
        aie::vector<int32_t, 8>Wv1(Wv_arr[0],Wv_arr[1],Wv_arr[2],Wv_arr[3],Wv_arr[4],Wv_arr[5],Wv_arr[6],Wv_arr[7]);
        aie::vector<int32_t, 8>Wv2(Wv_arr1[0],Wv_arr1[1],Wv_arr1[2],Wv_arr1[3],Wv_arr1[4],Wv_arr1[5],Wv_arr1[6],Wv_arr1[7]);
        out_a = aie::mac(out_a, outer_prod1, Wv1);
        out_a = aie::mac(out_a, Wv2, outer_prod2);
        int32_t output = ext_elem(srs(out_a,28),0)+ ext_elem(srs(out_a,28),1)+ ext_elem(srs(out_a,28),2)+
        ext_elem(srs(out_a,28),3)+ ext_elem(srs(out_a,28),4)+ ext_elem(srs(out_a,28),5)+ ext_elem(srs(out_a,28),6)+ ext_elem(srs(out_a,28),7);

        printf("OUTPUT2 Final_%d = %d\n",l+1, output);
        writeincr(out,output);
    }
}