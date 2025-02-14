#ifndef VERTEX_TENSOR
#define VERTEX_TENSOR
#include <cmath>

class VertexTensor{
public:
    float x;
    float y;
    float z;
    float norm_x;
    float norm_y;
    float norm_z;

public:
    VertexTensor();
    void FromFacet(float* vertex1, float* vertex2, float* vertex3, float* normal);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);

private:
    float* _centroid(float* vertex1, float* vertex2, float* vertex3);
};

#endif
