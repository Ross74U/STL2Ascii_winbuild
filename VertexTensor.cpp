#include "VertexTensor.h"

VertexTensor::VertexTensor(){
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
    norm_x = 0.0f;
    norm_y = 0.0f;
    norm_z = 0.0f;
}


void VertexTensor::FromFacet(float* vertex1, float* vertex2, float* vertex3, float* normal){
    // initializes variables based on an polygon facet
    norm_x = normal[0];
    norm_y = normal[1];
    norm_z = normal[2];

    float* centroid = _centroid(vertex1, vertex2, vertex3);
    x = centroid[0];
    y = centroid[1];
    z = centroid[2];
    delete(centroid);
}



float* VertexTensor::_centroid(float* vertex1, float* vertex2, float* vertex3){
    // calculates centroid of a facet
    float* centroid = new float[3];
    centroid[0] = (vertex1[0] + vertex2[0] + vertex3[0]) / 3.0f;
    centroid[1] = (vertex1[1] + vertex2[1] + vertex3[1]) / 3.0f;
    centroid[2] = (vertex1[2] + vertex2[2] + vertex3[2]) / 3.0f;
    return centroid;

}



void VertexTensor::RotateX(float angle){
    // Rotation around X-axis
    float y_new = std::cos(angle) * y - std::sin(angle) * z;
    float z_new = std::sin(angle) * y + std::cos(angle) * z;
    y = y_new;
    z = z_new;

    float norm_y_new = std::cos(angle) * norm_y - std::sin(angle) * norm_z;
    float norm_z_new = std::sin(angle) * norm_y + std::cos(angle) * norm_z;
    norm_y = norm_y_new;
    norm_z = norm_z_new;
}



void VertexTensor::RotateY(float angle){
    // Rotation around Y-axis
    float x_new = std::cos(angle) * x + std::sin(angle) * z;
    float z_new = -std::sin(angle) * x + std::cos(angle) * z;

    x = x_new;
    z = z_new;

    float norm_x_new = std::cos(angle) * norm_x + std::sin(angle) * norm_z;
    float norm_z_new = -std::sin(angle) * norm_x + std::cos(angle) * norm_z;

    norm_x = norm_x_new;
    norm_z = norm_z_new;
}



void VertexTensor::RotateZ(float angle){
    // Rotation around Z-axis
    float x_new = std::cos(angle) * x - std::sin(angle) * y;
    float y_new = std::sin(angle) * x + std::cos(angle) * y;

    x = x_new;
    y = y_new;

    float norm_x_new = std::cos(angle) * norm_x - std::sin(angle) * norm_y;
    float norm_y_new = std::sin(angle) * norm_x + std::cos(angle) * norm_y;

    norm_x = norm_x_new;
    norm_y = norm_y_new;
}