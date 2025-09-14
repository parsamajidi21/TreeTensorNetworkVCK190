// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iomanip>
#include "dataIn.h"
#include "xrt.h"
#include "experimental/xrt_kernel.h"
#include </home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/luts.h>

int main(int argc, char** argv) {

    // Check input arguments
    if (argc < 2 || argc > 4) {
        std::cout << "Usage: " << argv[0] << " <XCLBIN File> <#elements(optional)> <debug(optional)>" << std::endl;
        return EXIT_FAILURE;
    }
    unsigned int num_elements = 100;
    if (argc >= 3){
        unsigned int val;
        try {
            val = std::stoi(argv[2]);
        }
        catch (std::invalid_argument &val) {
            std::cerr << "Invalid argument in position 2 (" << argv[2] << ") program expects an integer as number of elements" << std::endl;
            return EXIT_FAILURE;
        }
        catch (std::out_of_range &val) {
            std::cerr << "Number of elements out of range, try with a number lower than 2147483648" << std::endl;
            return EXIT_FAILURE;
        }
        if ((val%4) !=0){
            val = (val/4) * 4;
            std::cout << "Number of elements (" << val << ") rounded to the closest multiple of 4" << std::endl;
        } 
        num_elements = val;
        std::cout << "User number of elements enabled" << std::endl;
    }

    bool debug = false;
    // Check if the user defined debug
    if (argc == 4){
        std::string debug_arg = argv[3];
        if(debug_arg.compare("debug") == 0)
            debug = true;
        std::cout << "Debug enabled" << std::endl;
    }

    // Get device index and download xclbin
    std::cout << "Open the device" << std::endl;
    auto device = xrt::device(0);
    std::string binaryFile = argv[1];
    std::cout << "Load the xclbin " << binaryFile << std::endl;
    auto uuid = device.load_xclbin(binaryFile);

    // Get reference to the kernels
    std::cout << "Get references to compute units" << std::endl;
    auto pl_mm2s_1 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_1}");
    auto pl_mm2s_2 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_2}");
    auto pl_mm2s_3 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_3}");
    auto pl_mm2s_4 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_4}");
    auto pl_s2mm_1 = xrt::kernel(device, uuid, "pl_s2mm");

    // Allocating the input size of sizeIn to MM2S
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    size_t size_in_bytes = sizeof(int) * num_elements;
    auto in_buff_1 = xrt::bo(device, size_in_bytes, pl_mm2s_1.group_id(0));
    auto in_buff_2 = xrt::bo(device, size_in_bytes, pl_mm2s_2.group_id(0));
    auto in_buff_3 = xrt::bo(device, size_in_bytes, pl_mm2s_3.group_id(0));
    auto in_buff_4 = xrt::bo(device, size_in_bytes, pl_mm2s_4.group_id(0));
    auto out_buff_1 = xrt::bo(device, size_in_bytes, pl_s2mm_1.group_id(0));

    auto DataInput0 = in_buff_1.map<int32_t*>();
    memcpy(DataInput0, int32Input1, size_in_bytes);

    auto DataInput1 = in_buff_2.map<int32_t*>();
    memcpy(DataInput1, int32Input2, size_in_bytes);

    auto DataInput2 = in_buff_3.map<int32_t*>();
    memcpy(DataInput2, int32Input3, size_in_bytes);

    auto DataInput3 = in_buff_4.map<int32_t*>();
    memcpy(DataInput3, int32Input4, size_in_bytes);

    auto DataOutput = out_buff_1.map<int32_t*>();
    memset(DataOutput, 0xABCDEF00, size_in_bytes);
    
    in_buff_1.write(DataInput0);
    in_buff_2.write(DataInput1);
    in_buff_3.write(DataInput2);
    in_buff_4.write(DataInput3);
    
    // Synchronize input buffers data to device global memory
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    in_buff_1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_4.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    // Execute the compute units
    std::cout << "Run the kernels" << std::endl;
    auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, num_elements);
    auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1, nullptr, num_elements);
    auto run_pl_mm2s_2 = pl_mm2s_2(in_buff_2, nullptr, num_elements);
    auto run_pl_mm2s_3 = pl_mm2s_3(in_buff_3, nullptr, num_elements);
    auto run_pl_mm2s_4 = pl_mm2s_4(in_buff_4, nullptr, num_elements);
    // Wait for kernels to complete
    run_pl_mm2s_1.wait();
    std::cout << "pl_mm2s_1 completed" << std::endl;
    run_pl_mm2s_2.wait();
    std::cout << "pl_mm2s_2 completed" << std::endl;
    run_pl_mm2s_3.wait();
    std::cout << "pl_mm2s_3 completed" << std::endl;
    run_pl_mm2s_4.wait();
    std::cout << "pl_mm2s_4 completed" << std::endl;
    run_pl_s2mm_1.wait();
    std::cout << "pl_s2mm_1 completed" << std::endl;

    // Synchronize the output buffer data from the device
    std::cout << "Synchronize the output buffer data from the device" << std::endl;
    out_buff_1.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    // Read output buffer data to local buffer
    out_buff_1.read(DataOutput);
    std::ofstream outFile("/home/parsa/Documents/Unipd/thesis/Test1/aie_output.txt");
    for (int n = 0, m = 0; n < 100 && m < 100; n++, m++) {
        std::vector<std::pair<int, int>> index_pairs_00 = {{(n*4), (m*4)}, {(n*4), (m*4)+1}, {(n*4)+1, (m*4)}, {(n*4)+1, (m*4)+1}};

        // Compute the specified products
        std::vector<long int> mul_v00;
        for (const auto& pair : index_pairs_00) {
            long int product00 = DataInput0[pair.first] * DataInput1[pair.second];
            mul_v00.push_back(product00);
        }

        // Compute the specified products
        std::vector<long int> out_a_00;
        long int product1;
        int j = 0;
        for (int i = 0; i < 4; i++) {
            product1 = mul_v00[j] * W00[(i*4)] + mul_v00[j+1] * W00[(i*4)+1] + mul_v00[j+2] * W00[(i*4)+2] + mul_v00[j+3] * W00[(i*4)+3];
            out_a_00.push_back(product1);
            j = 0;
        }
        
        for (long int& num : out_a_00){
            num = (num >> 28);
            //std::cout << "out_a_00 = " << num << std::endl;
        }

        std::vector<std::pair<int, int>> index_pairs_01 = {{(n*4), (m*4)}, {(n*4), (m*4)+1}, {(n*4)+1, (m*4)}, {(n*4)+1, (m*4)+1}};

        // Compute the specified products
        std::vector<long int> mul_v01;
        for (const auto& pair : index_pairs_01) {
            long int product01 = DataInput2[pair.first] * DataInput3[pair.second];
            mul_v01.push_back(product01);
        }
        // Compute the specified products
        std::vector<long int> out_a_01;
        long int product2;
        int l = 0;
        for (int i = 0; i < 4; i++) {
            product2 = mul_v01[l] * W01[(i*4)] + mul_v01[l+1] * W01[(i*4)+1] + mul_v01[l+2] * W01[(i*4)+2] + mul_v01[l+3] * W01[(i*4)+3];
            out_a_01.push_back(product2);
            l = 0;
        }

        for (long int& num1 : out_a_01){
            num1 = (num1 >> 28); 
            //std::cout << "out_a_01 = " << num1 << std::endl;
        }
        /*{{0, 0}, {0, 1}, {0, 2}, {0, 3},
        {1, 0}, {1, 1}, {1, 2}, {1, 3},
        {2, 0}, {2, 1}, {2, 2}, {2, 3},
        {3, 0}, {3, 1}, {3, 2}, {3, 3}};*/

        std::vector<long int> mul_v10;                                                
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                long int product10 = out_a_00[i] * out_a_01[j];
                mul_v10.push_back(product10);
            }
        }  

        std::vector<long int> out_a_10;
        for (int k = 0; k < 8; k++) {
            long int product3 = W10[k*2] * mul_v10[k*2] + W10[(k*2)+1] * mul_v10[(k*2)+1];
            out_a_10.push_back(product3);
        }
        // Compute the specified products
        long int Output = 0;
        for (const auto& In : out_a_10) {
            Output += In;
        }

        Output = (Output >> 28);
        // Compare results
        //int i = 0;
        int errorCount = 0;
        long int golden = Output;
        if (DataOutput[n*4] != golden) {
                std::cout << "Error found @ " << std::dec << n;
                std::cout << ", " <<  DataOutput[n*4] << " != " << golden << std::endl;
                errorCount++;
            }
        if (debug) {
            std::cout << "Idx [" << std::setw(6) << n << "]" << std::setw(14) << DataInput0[n*4] << " * ";
            std::cout << std::setw(14) << DataInput1[m*4] <<"\tsw result" << std::setw(14);
            std::cout << golden << "\thw result" << std::setw(14) << DataOutput[n*4];
            std::cout << "\tequal "<< ((golden == DataOutput[n*4]) ? "True" : "False") << std::endl;
            if (golden == DataOutput[n*4]){
                outFile << DataOutput[n*4] << std::endl;
            }
        }
        
        if (errorCount)
            std::cout << "Test failed with " << std::dec << errorCount << " errors" << std::endl;
        else
            std::cout << "TEST PASSED with " << num_elements << " elements" << std::endl;

    }
    outFile.close();
    return 0;
}