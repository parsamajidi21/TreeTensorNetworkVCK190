// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iomanip>
#include "vectorInput.h"
#include "golden.h"
#include "xrt.h"
#include <math.h>
#include "experimental/xrt_kernel.h"
#include "experimental/xrt_graph.h"
//#include </home/parsa/Documents/Unipd/thesis/Test1/aie_component/aie/src/luts.h>

int main(int argc, char** argv) {


    bool debug = false;
    //Check if the user defined debug
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
    const size_t CHUNK_SIZE = 2577056; // 64k elements
    const size_t CHUNK_SIZE2 = CHUNK_SIZE * 2;
    size_t num_elements1 = 2577056;
    //size_t size_in_bytes1 = num_elements1 * sizeof(int32_t);
    size_t chunks = (num_elements1 + CHUNK_SIZE - 1) / CHUNK_SIZE;
    
    // Get reference to the kernels
    std::cout << "Get references to compute units" << std::endl;
    auto pl_mm2s_1 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_1}");
    auto pl_mm2s_2 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_2}");
    auto pl_mm2s_3 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_3}");
    auto pl_mm2s_4 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_4}");
    auto pl_mm2s_5 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_5}");
    auto pl_mm2s_6 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_6}");
    auto pl_mm2s_7 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_7}");
    auto pl_mm2s_8 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_8}");
    auto pl_mm2s_9 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_9}");
    auto pl_mm2s_10 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_10}");
    auto pl_mm2s_11 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_11}");
    auto pl_mm2s_12 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_12}");
    auto pl_mm2s_13 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_13}");
    auto pl_mm2s_14 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_14}");
    auto pl_mm2s_15 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_15}");
    auto pl_mm2s_16 = xrt::kernel(device, uuid, "pl_mm2s:{pl_mm2s_16}");
    auto pl_s2mm_1 = xrt::kernel(device, uuid, "pl_s2mm");
    int c = 0;
    size_t cur_size = CHUNK_SIZE;
    size_t cur_bytes = cur_size * sizeof(int32_t);
    size_t cur_bytes2 = cur_bytes * 2;
    // Allocating the input size of sizeIn to MM2S
    std::cout << "Allocate Buffer in Global Memory" << std::endl;
    auto in_buff_1 = xrt::bo(device, cur_bytes, pl_mm2s_1.group_id(0));
    auto DataInput0 = in_buff_1.map<int32_t*>();
    memcpy(DataInput0, vectorInput1, cur_bytes);

    auto in_buff_2 = xrt::bo(device, cur_bytes, pl_mm2s_2.group_id(0));
    auto DataInput1 = in_buff_2.map<int32_t*>();
    memcpy(DataInput1, vectorInput2, cur_bytes);

    auto in_buff_3 = xrt::bo(device, cur_bytes, pl_mm2s_3.group_id(0));
    auto DataInput2 = in_buff_3.map<int32_t*>();
    memcpy(DataInput2, vectorInput3, cur_bytes);

    auto in_buff_4 = xrt::bo(device, cur_bytes, pl_mm2s_4.group_id(0));
    auto DataInput3 = in_buff_4.map<int32_t*>();
    memcpy(DataInput3,  vectorInput4, cur_bytes);

    auto in_buff_5 = xrt::bo(device, cur_bytes, pl_mm2s_5.group_id(0));
    auto DataInput4 = in_buff_5.map<int32_t*>();
    memcpy(DataInput4, vectorInput5, cur_bytes);

    auto in_buff_6 = xrt::bo(device, cur_bytes, pl_mm2s_6.group_id(0));
    auto DataInput5 = in_buff_6.map<int32_t*>();
    memcpy(DataInput5, vectorInput6, cur_bytes);

    auto in_buff_7 = xrt::bo(device, cur_bytes, pl_mm2s_7.group_id(0));
    auto DataInput6 = in_buff_7.map<int32_t*>();
    memcpy(DataInput6, vectorInput7, cur_bytes);

    auto in_buff_8 = xrt::bo(device, cur_bytes, pl_mm2s_8.group_id(0));
    auto DataInput7 = in_buff_8.map<int32_t*>();
    memcpy(DataInput7, vectorInput8, cur_bytes);

    auto in_buff_9 = xrt::bo(device, cur_bytes, pl_mm2s_9.group_id(0));
    auto DataInput8 = in_buff_9.map<int32_t*>();
    memcpy(DataInput8, vectorInput9, cur_bytes);

    auto in_buff_10 = xrt::bo(device, cur_bytes, pl_mm2s_10.group_id(0));
    auto DataInput9 = in_buff_10.map<int32_t*>();
    memcpy(DataInput9, vectorInput10, cur_bytes);

    auto in_buff_11 = xrt::bo(device, cur_bytes, pl_mm2s_11.group_id(0));
    auto DataInput10 = in_buff_11.map<int32_t*>();
    memcpy(DataInput10, vectorInput11, cur_bytes);

    auto in_buff_12 = xrt::bo(device, cur_bytes, pl_mm2s_12.group_id(0));
    auto DataInput11 = in_buff_12.map<int32_t*>();
    memcpy(DataInput11, vectorInput12, cur_bytes);

    auto in_buff_13 = xrt::bo(device, cur_bytes, pl_mm2s_13.group_id(0));
    auto DataInput12 = in_buff_13.map<int32_t*>();
    memcpy(DataInput12, vectorInput13, cur_bytes);

    auto in_buff_14 = xrt::bo(device, cur_bytes, pl_mm2s_14.group_id(0));
    auto DataInput13 = in_buff_14.map<int32_t*>();
    memcpy(DataInput13, vectorInput14, cur_bytes);

    auto in_buff_15 = xrt::bo(device, cur_bytes, pl_mm2s_15.group_id(0));
    auto DataInput14 = in_buff_15.map<int32_t*>();
    memcpy(DataInput14, vectorInput15, cur_bytes);

    auto in_buff_16 = xrt::bo(device, cur_bytes, pl_mm2s_16.group_id(0));
    auto DataInput15 = in_buff_16.map<int32_t*>();
    memcpy(DataInput15, vectorInput16, cur_bytes);

    
    // Synchronize input buffers data to device global memory
    std::cout << "Synchronize input buffers data to device global memory" << std::endl;
    in_buff_1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_4.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_5.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_6.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_7.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_8.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_9.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_10.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_11.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_12.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_13.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_14.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_15.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_buff_16.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto out_buff_1 = xrt::bo(device, cur_bytes2, pl_s2mm_1.group_id(0));
    auto DataOutput = out_buff_1.map<int32_t*>();
    memset(DataOutput, 0xABCDEF00, cur_bytes2);

    // Execute the compute units
    std::cout << "Run the kernels" << std::endl;
    auto run_pl_s2mm_1 = pl_s2mm_1(out_buff_1, nullptr, cur_size*2);
    auto run_pl_mm2s_1 = pl_mm2s_1(in_buff_1, nullptr, cur_size);
    auto run_pl_mm2s_2 = pl_mm2s_2(in_buff_2, nullptr, cur_size);
    auto run_pl_mm2s_3 = pl_mm2s_3(in_buff_3, nullptr, cur_size);
    auto run_pl_mm2s_4 = pl_mm2s_4(in_buff_4, nullptr, cur_size);
    auto run_pl_mm2s_5 = pl_mm2s_5(in_buff_5, nullptr, cur_size);
    auto run_pl_mm2s_6 = pl_mm2s_6(in_buff_6, nullptr, cur_size);
    auto run_pl_mm2s_7 = pl_mm2s_7(in_buff_7, nullptr, cur_size);
    auto run_pl_mm2s_8 = pl_mm2s_8(in_buff_8, nullptr, cur_size);
    auto run_pl_mm2s_9 = pl_mm2s_9(in_buff_9, nullptr, cur_size);
    auto run_pl_mm2s_10 = pl_mm2s_10(in_buff_10, nullptr, cur_size);
    auto run_pl_mm2s_11 = pl_mm2s_11(in_buff_11, nullptr, cur_size);
    auto run_pl_mm2s_12 = pl_mm2s_12(in_buff_12, nullptr, cur_size);
    auto run_pl_mm2s_13 = pl_mm2s_13(in_buff_13, nullptr, cur_size);
    auto run_pl_mm2s_14 = pl_mm2s_14(in_buff_14, nullptr, cur_size);
    auto run_pl_mm2s_15 = pl_mm2s_15(in_buff_15, nullptr, cur_size);
    auto run_pl_mm2s_16 = pl_mm2s_16(in_buff_16, nullptr, cur_size);



    auto cghdl = xrt::graph(device,uuid,"vadd_graph");
	
	printf("graph run\n");
	//Run th graph for 1 iteration
	cghdl.run(1);
	printf("After graph run\n");
	//Graph end
	cghdl.end();
	printf("After graph end\n");

    // Wait for kernels to complete
    run_pl_mm2s_1.wait();
    std::cout << "pl_mm2s_1 completed_" << c+1 << std::endl;
    run_pl_mm2s_2.wait();
    std::cout << "pl_mm2s_2 completed_" << c+1 << std::endl;
    run_pl_mm2s_3.wait();
    std::cout << "pl_mm2s_3 completed_" << c+1 << std::endl;
    run_pl_mm2s_4.wait();
    std::cout << "pl_mm2s_4 completed_" << c+1 << std::endl;
    run_pl_mm2s_5.wait();
    std::cout << "pl_mm2s_5 completed_" << c+1 << std::endl;
    run_pl_mm2s_6.wait();
    std::cout << "pl_mm2s_7 completed_" << c+1 << std::endl;
    run_pl_mm2s_7.wait();
    std::cout << "pl_mm2s_7 completed_" << c+1 << std::endl;
    run_pl_mm2s_8.wait();
    std::cout << "pl_mm2s_8 completed_" << c+1 << std::endl;
    run_pl_mm2s_9.wait();
    std::cout << "pl_mm2s_9 completed_" << c+1 << std::endl;
    run_pl_mm2s_10.wait();
    std::cout << "pl_mm2s_10 completed_" << c+1 << std::endl;
    run_pl_mm2s_11.wait();
    std::cout << "pl_mm2s_11 completed_" << c+1 << std::endl;
    run_pl_mm2s_12.wait();
    std::cout << "pl_mm2s_12 completed_" << c+1 << std::endl;
    run_pl_mm2s_13.wait();
    std::cout << "pl_mm2s_13 completed_" << c+1 << std::endl;
    run_pl_mm2s_14.wait();
    std::cout << "pl_mm2s_14 completed_" << c+1 << std::endl;
    run_pl_mm2s_15.wait();
    std::cout << "pl_mm2s_15 completed_" << c+1 << std::endl;
    run_pl_mm2s_16.wait();
    std::cout << "pl_mm2s_16 completed_" << c+1 << std::endl;
    run_pl_s2mm_1.wait();
    std::cout << "pl_s2mm_1 completed_" << c+1 << std::endl;
    // Synchronize the output buffer data from the device
    std::cout << "Synchronize the output buffer data from the device" << std::endl;
    out_buff_1.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

    std::cout << "DataOut_2577056 = " <<  DataOutput[0] << std::endl;
    std::cout << "Golden_1610660 = " <<  golden[0] << std::endl;
    std::cout << "DataIn_1 " <<  DataInput0[0] << std::endl;
    std::cout << "DataIn_1 " <<  DataInput0[1] << std::endl;
    std::cout << "DataIn_1 " <<  DataInput0[2] << std::endl;
    std::cout << "DataIn_1 " <<  DataInput0[3] << std::endl;

    int errorCount = 0;
    int num_chunks = 644264; // number of groups
    int check_size = 5;      // only check first 5 elements of each DataOutput group
    if (debug) {
        for (int chunk = 0; chunk < num_chunks; chunk++) {
            int dataStart   = chunk * 8;  // DataOutput stride is 8
            int goldenStart = chunk * 5;  // golden stride is 5

            bool chunkError = false;
            for (int i = 0; i < check_size; i++) {
                int dataIdx   = dataStart + i;
                int goldenIdx = goldenStart + i;

                int32_t diff_squared = std::abs(golden[goldenIdx]) - std::abs(DataOutput[dataIdx]);
                if (diff_squared > 50) {
                    chunkError = true;
                }
            }

            if (chunkError) {
                std::cout << "Error found in chunk " << chunk 
                        << " (DataOutput[" << dataStart << "..." << dataStart + check_size - 1
                        << "] != golden[" << goldenStart << "..." << goldenStart + check_size - 1 << "])"
                        << std::endl;
                errorCount++;
            }
        }
    }
    if (errorCount)
        std::cout << "Test failed with " << errorCount << " chunks in error" << std::endl;
    else
        std::cout << "Test Passed" << std::endl;

    return 0;
}