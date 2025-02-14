#include "TensorArray.h"



/* Default constructor*/
TensorArray::TensorArray() : current_size(0){
    array = std::vector<VertexTensor>();
}

TensorArray::TensorArray(int len) : current_size(0){
    array = std::vector<VertexTensor>(len);
}



void TensorArray::AddTensor(VertexTensor* tensor){
    if (current_size >= array.size()){
        return;
    }

    array[current_size] = *tensor;
    current_size ++;
}




VertexTensor TensorArray::GetTensor(uint32_t index){
    VertexTensor tensor = array[index];
    return tensor;
}




void TensorArray::RotateArray(float angle_x, float angle_y, float angle_z){
    if (angle_x != 0){
        for (uint32_t i = 0; i<current_size; i++){
            array[i].RotateX(angle_x);
        }
    }
    if (angle_y != 0){
        for (uint32_t i = 0; i<current_size; i++){
            array[i].RotateY(angle_y);
        }
    }
    if (angle_z != 0){
        for (uint32_t i = 0; i<current_size; i++){
            array[i].RotateZ(angle_z);
        }
    }
}




TensorArray TensorArray::GetProjection(float disp_z, float proj_z){
    TensorArray new_array = TensorArray(current_size);

    for (uint16_t i = 0; i < current_size; i++){
        VertexTensor new_tensor = VertexTensor();

        new_tensor.z = array[i].z;
        new_tensor.x = array[i].x * (array[i].z + disp_z) / proj_z;
        new_tensor.y = array[i].y * (array[i].z + disp_z) / proj_z;
        new_tensor.norm_x = array[i].norm_x;
        new_tensor.norm_y = array[i].norm_y;
        new_tensor.norm_z = array[i].norm_z;

        new_array.AddTensor(&new_tensor);
    }

    new_array.current_size = current_size;

    return new_array;
}



void TensorArray::setMid(void){
    float max_x = array[0].x;
    float min_x = array[0].x;

    for (uint32_t i = 1; i < current_size; i++)
    {
        if (array[i].x > max_x) max_x = array[i].x;
        if (array[i].x < min_x) min_x = array[i].x;
    }


    float max_y = array[0].y;
    float min_y = array[0].y;

    for (uint32_t i = 1; i < current_size; i++)
    {
        if (array[i].y > max_y) max_y = array[i].y;
        if (array[i].y < min_y) min_y = array[i].y;
    }

    float max_z = array[0].z;
    float min_z = array[0].z;

    for (uint32_t i = 1; i < current_size; i++)
    {
        if (array[i].z > max_z) max_z = array[i].z;
        if (array[i].z < min_z) min_z = array[i].z;
    }


    for (uint32_t i = 1; i < current_size; i++){
        array[i].x = array[i].x - (min_x + max_x)*0.5f;
        array[i].y = array[i].y - (min_y + max_y)*0.5f;
        array[i].z = array[i].z - (min_z + max_z)*0.5f;
    }
}
