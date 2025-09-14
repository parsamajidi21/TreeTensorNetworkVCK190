/*
Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
SPDX-License-Identifier: X11
*/

#include <cstdint>
#include <fstream>
#include <cstring>

#include "experimental/xrt_kernel.h"
#include "experimental/xrt_graph.h"
#include "dataIn.h" //Contains input and golden output data 
#include "math.h"
#define SAMPLES 100

int main(int argc, char* argv[])
{
	//////////////////////////////////////////
	// Open xclbin
	//////////////////////////////////////////	

	char* xclbinFile=argv[1];
	auto device = xrt::device(0);
    	if(device == nullptr)
		throw std::runtime_error("No valid device handle found. Make sure using right xclOpen index.");
    	auto xclbin_uuid = device.load_xclbin(xclbinFile);

    int sizeIn = SAMPLES;
	int sizeOut = SAMPLES;

	//////////////////////////////////////////
	// input memory
	// Allocating the input size of sizeIn to MM2S
	// MM2S module transfers input data from PL to the AI Engine
	//////////////////////////////////////////
    auto mm2s_khdl1 = xrt::kernel(device, xclbin_uuid, "pl_mm2s:{pl_mm2s_1}");
    auto mm2s_khdl2 = xrt::kernel(device, xclbin_uuid, "pl_mm2s:{pl_mm2s_2}");
    auto mm2s_khdl3 = xrt::kernel(device, xclbin_uuid, "pl_mm2s:{pl_mm2s_3}");
    auto mm2s_khdl4 = xrt::kernel(device, xclbin_uuid, "pl_mm2s:{pl_mm2s_4}");

	auto in_bohdl1 = xrt::bo(device, 400 * sizeof(int32_t), mm2s_khdl1.group_id(0));
	auto in_bomapped1 = in_bohdl1.map<int32_t*>();
	memcpy(in_bomapped1, int32Input1, 400 * sizeof(int32_t));

	auto in_bohdl2 = xrt::bo(device, 400 * sizeof(int32_t), mm2s_khdl2.group_id(0));
	auto in_bomapped2 = in_bohdl2.map<int32_t*>();
	memcpy(in_bomapped2, int32Input2, 400 * sizeof(int32_t));

	auto in_bohdl3 = xrt::bo(device, 400 * sizeof(int32_t), mm2s_khdl3.group_id(0));
	auto in_bomapped3 = in_bohdl3.map<int32_t*>();
	memcpy(in_bomapped3, int32Input3, 400 * sizeof(int32_t));

	auto in_bohdl4 = xrt::bo(device, 400 * sizeof(int32_t), mm2s_khdl4.group_id(0));
	auto in_bomapped4 = in_bohdl4.map<int32_t*>();
	memcpy(in_bomapped4, int32Input4, 400 * sizeof(int32_t));

    auto *DataOutput = new int [100];
    
    /*in_bohdl1.write(in_bomapped1);
    in_bohdl2.write(in_bomapped2);
    in_bohdl3.write(in_bomapped3);
    in_bohdl4.write(in_bomapped4);*/

	in_bohdl1.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_bohdl2.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_bohdl3.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    in_bohdl4.sync(XCL_BO_SYNC_BO_TO_DEVICE);
	//////////////////////////////////////////
	// output memory
	// Allocating the output size of sizeOut to S2MM
	// S2MM module receives the output data from AI Engine 
	//////////////////////////////////////////
	
	auto out_bohdl = xrt::bo(device, 400* sizeof(int32_t), 0, 0);
	auto out_bomapped = out_bohdl.map<int32_t*>();
	memset(out_bomapped, 0xABCDEF00, 400* sizeof(int32_t));

	////////////////////////////////////////////////////////
	// mm2s ip - Creating kernel handle using xrt::kernel API
	///////////////////////////////////////////////////////	
	
	auto mm2s_rhdl1 = mm2s_khdl1(in_bohdl1, nullptr, 400);
	std::cout << "run pl_mm2s_1" << std::endl;

	auto mm2s_rhdl2 = mm2s_khdl2(in_bohdl2, nullptr, 400);
	std::cout << "run pl_mm2s_2" << std::endl;

	auto mm2s_rhdl3 = mm2s_khdl3(in_bohdl3, nullptr, 400);
	std::cout << "run pl_mm2s_3" << std::endl;

	auto mm2s_rhdl4 = mm2s_khdl4(in_bohdl4, nullptr, 400);
	std::cout << "run pl_mm2s_4" << std::endl;

	////////////////////////////////////////////////////////
	// s2mm ip - Creating kernel handle using xrt::kernel API
	///////////////////////////////////////////////////////		
	
	auto s2mm_khdl = xrt::kernel(device, xclbin_uuid, "pl_s2mm");
	auto s2mm_rhdl = s2mm_khdl(out_bohdl, nullptr, 400);
	printf("run s2mm\n");

	//////////////////////////////////////////
	// graph execution for AIE
	//////////////////////////////////////////	
	
	//Obtains the graph handle from the XCLBIN that is loaded into the device
	auto cghdl = xrt::graph(device,xclbin_uuid,"vadd_graph");
	
	
	//Run th graph for 1 iteration
	cghdl.run(1);
	printf("graph run\n");
	//Graph end
	cghdl.end();
	printf("graph end\n");	
	
	
	//////////////////////////////////////////
	// wait for mm2s done
	//////////////////////////////////////////	
	
	mm2s_rhdl1.wait();
    std::cout << "mm2s_rhdl1 end" << std::endl;
    mm2s_rhdl2.wait();
    std::cout << "mm2s_rhdl2 end" << std::endl;
    mm2s_rhdl3.wait();
    std::cout << "mm2s_rhdl3 end" << std::endl;
    mm2s_rhdl4.wait();
    std::cout << "mm2s_rhdl4 end" << std::endl;
	//////////////////////////////////////////
	// wait for s2mm done
	//////////////////////////////////////////	
	
	s2mm_rhdl.wait();

	out_bohdl.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    out_bohdl.read(DataOutput);

    std::cout << "Input:396 " <<  in_bomapped1[1] << std::endl;
    std::cout << "Out:50 " <<  DataOutput[1] << std::endl;
	//////////////////////////////////////////
	// Comparing the execution data to the golden data
	//////////////////////////////////////////	
	
	int errorCount = 0;
	{
		for (int i = 0; i < sizeOut; i++)
		{
            std::cout << "Dataout found @" << i << ": " << out_bomapped[i*4] << std::endl;
            int32_t diff_squared = std::pow(golden[i] - out_bomapped[i*4], 2);
				if (diff_squared > 50.0) {
					std::cout << "Error found @" << i << ": " << out_bomapped[i*4] << " != " << golden[i] << std::endl;
					errorCount++;
				}
		}

		if (errorCount)
			std::cout << "Test failed with "  << errorCount << "errors" << std::endl;
		else
			std::cout << "Test Passed " << std::endl;
	}
	
    
	std::cout << "Releasing remaining XRT objects...\n";
	
	return errorCount;
}