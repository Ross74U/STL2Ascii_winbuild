// TODO
// GetProject (for params see https://www.a1k0n.net/2011/07/20/donut-math.html)

#ifndef TENSOR_ARRAY
#define TENSOR_ARRAY
#include <cstdint>
#include <vector>
#include "VertexTensor.h"
#include "log.h"


class TensorArray{
private:
    std::vector<VertexTensor> array;
public:
    uint32_t current_size;
public:
    TensorArray();
    TensorArray(int len);
    void AddTensor(VertexTensor* tensor);
    VertexTensor GetTensor(uint32_t index);
    void RotateArray(float angle_x, float angle_y, float angle_z);

    TensorArray GetProjection(float disp_z, float proj_z);
    /* generates new tensor array with new x, y, z (norms unchanged) */
    // Params: disp_z: distance amount the model will be displaced away from the origin
    //         proj_z: distance of the projection away from the user.
    // for more info on params see https://www.a1k0n.net/2011/07/20/donut-math.html

    void setMid(void);
};

#endif