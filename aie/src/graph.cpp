// Copyright (C) 2025 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#include <iostream>
#include <fstream>
#include "graph.hpp"

treeTensor tree_tensor;

#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char** argv) {
    tree_tensor.init();
    tree_tensor.run(1);
    tree_tensor.end();
    
    return 0;
}
#endif
