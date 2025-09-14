// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <fstream>
#include "graph.hpp"

simpleGraph vadd_graph;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {
    vadd_graph.init();
#ifdef STREAM
    vadd_graph.run(1);
#else
    vadd_graph.run(1);
#endif
    vadd_graph.end();
    std::ifstream golden_file, aie_file;
    golden_file.open("/home/kynetics/Documents/AI_Engine/aie_component/aie/src/data/golden.txt");
    if(golden_file.fail()){
      std::cerr << "Error opening golden file." << std::endl;
      golden_file.close();
      return -1;
    }

#if defined(__X86SIM__)
    aie_file.open("x86simulator_output/output.txt");
#else
    aie_file.open("aiesimulator_output/output.txt");
#endif
    if(aie_file.fail()){
      std::cerr<<"Error opening produced file."<< std::endl;
      return -1;
    }


    std::vector<double> golden_values, aie_values;
    std::string line;

    // Read and parse golden file values
    while (std::getline(golden_file, line)) {
        std::stringstream ss(line);
        double value;
        while (ss >> value) {
            golden_values.push_back(value);
        }
    }

    // Read and parse aie file values
    while (std::getline(aie_file, line)) {
        std::stringstream ss(line);
        double value;
        while (ss >> value) {
            aie_values.push_back(value);
        }
    }

    size_t min_size = std::min(golden_values.size(), aie_values.size());
    bool match = true;

    for (size_t i = 0; i < min_size; ++i) {
        double diff_squared = std::pow(golden_values[i] - aie_values[i*4], 2);
        if (diff_squared > 50.0) {
            std::cout << "Mismatch at index " << i << ": golden = "
                      << golden_values[i] << ", aie = " << aie_values[i*4]
                      << ", diff^2 = " << diff_squared << std::endl;
            match = false;
        }
        std::cout << "Match at index " << i << ": golden = "
                      << golden_values[i] << ", aie = " << aie_values[i*4]
                      << ", diff^2 = " << diff_squared << std::endl;
    }

    if (golden_values.size() != aie_values.size()) {
        std::cerr << "Warning: Size mismatch. golden has " << golden_values.size()
                  << ", aie has " << aie_values.size() << std::endl;
    }

    if (match) {
        std::cout << "All values match within tolerance." << std::endl;
    } else {
        std::cout << "Some values mismatched." << std::endl;
    }
    golden_file.close();
    aie_file.close();
    return 0;
}
#endif
