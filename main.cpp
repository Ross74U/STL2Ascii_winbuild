#include <iostream>
#include <fstream>
#include <cstdint>


#include "log.h"
#include "VertexTensor.h"
#include "TensorArray.h"
#include "Render.h"
#include <chrono>
#include <thread>
#include <windows.h>

#define PI 3.14159265358979323846



struct Facet {
    float normal[3];
    float vertex1[3];
    float vertex2[3];
    float vertex3[3];
    uint16_t attributeByteCount;
};



int main() {

    Logging Log;
    Log.SetLogLevel(LOG_LEVEL_INFO);


    const char* filename = "heart_oct6.stl"; // Replace with your STL file name
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        Log.Error("Could not read file!\n");
        return 1;
    }

    // Skip the 80-byte header
    file.seekg(80, std::ios::beg);

    // Read the number of facets (4 byt wqzaes)
    uint32_t numFacets;
    file.read(reinterpret_cast<char*>(&numFacets), sizeof(uint32_t));

    // Tensor array storing all vertex tensors
    TensorArray tensor_array = TensorArray(numFacets);

    // Read facets
    for (uint32_t i = 0; i < numFacets; i++) {
        Facet facet;
        VertexTensor VT;

        file.read(reinterpret_cast<char*>(&facet.normal), 3 * sizeof(float));   // Read normal
        file.read(reinterpret_cast<char*>(&facet.vertex1), 3 * sizeof(float));  // Read vertex1
        file.read(reinterpret_cast<char*>(&facet.vertex2), 3 * sizeof(float));  // Read vertex2
        file.read(reinterpret_cast<char*>(&facet.vertex3), 3 * sizeof(float));  // Read vertex3
        file.read(reinterpret_cast<char*>(&facet.attributeByteCount), sizeof(uint16_t));                                           // skip over the attribute byte count

        VT.FromFacet(facet.vertex1, facet.vertex2, facet.vertex3, facet.normal);

        if (i < 10){
            std::cout << "Vertex" << i << ": (" << VT.x << ", " << VT.y << ", " << VT.z << ")\n";
            std::cout << "Normal: (" << VT.norm_x << ", " << VT.norm_y << ", " << VT.norm_z << ")\n";
        }

        tensor_array.AddTensor(&VT);
    }
    file.close();





    std::cout << "------------------------------------------\n";
    std::cout << "Number of facets: " << numFacets << "\n";
    std::cout << "------------------------------------------\n";

    if (numFacets >= 10000) Log.Warning("Excessive facets might eat your PC, just saying!");

    tensor_array.setMid();
    tensor_array.RotateArray(PI/2.0f, 0.0f, 0.0f); // rotate tensors by 45 degrees about the -axis

    Render MyRender = Render(150, 40, 300.0f, 100.0f);  // first two, canvas size, 2nd two, z_disp and z_proj
    MyRender.SetLighting(-1.0f, 0.0f, 1.0f);    // lighting vector
    MyRender.tensors = tensor_array;
    MyRender.setSize(3.0f, 6.0f); // mess with this value if u get segmentation fault

    while(1){
        MyRender.Interpolate();
        MyRender.ToConsole();
        MyRender.tensors.RotateArray(0.0f, PI/32.0f, PI/64.0f);
        Sleep(70);
    }


    Log.Warning("You should have run free() on all initialized arrays at this point to prevent memory leak!");
    return 0;
}