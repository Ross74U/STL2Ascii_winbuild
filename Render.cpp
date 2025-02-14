#include "Render.h"
#include <cstdlib>
#include <cstdio>

Render::Render(
    uint32_t w,
    uint32_t h,
    float disp_z,
    float proj_z)
:   width(w), 
    height(h),
    displacement_z(disp_z),
    projection_z(proj_z)
{
    SetLighting(lighting_x, lighting_y, lighting_z);
}




void Render::Interpolate(void){
    // set zbuffer and interpolation back to zero.
    Zbuffer.resize(height, std::vector<float>(width, 0.00f));
    Interpolation.resize(height, std::vector<float>(width, 0.00f));

    // get projection according to disp_z and proj_z
    TensorArray Projection = tensors.GetProjection(
        displacement_z,
        projection_z);

   // std::cout << size_x << " " << size_y << "\n";

    for (uint32_t i = 0; i < Projection.current_size; i++)
    {
        VertexTensor tensor = Projection.GetTensor(i);
        //std::cout << tensor.x << " " << tensor.y << "\n";
        float rel_x = size_x/2.0 + tensor.x;
        float rel_y = size_y/2.0 + tensor.y;
        //std::cout << rel_x<< " " << rel_y << "\n";
        uint32_t w = _divideAndRound(rel_x, delta_x);
        uint32_t h = _divideAndRound(rel_y, delta_y);

        //std::cout << w << " " << h << "\n";
        float shifted_z = tensor.z - 1000.0f; // shifts z tbs it's all negative;

        if (Zbuffer[h][w] >= shifted_z){
            Interpolation[h][w] = _NormLuminence(tensor);
            Zbuffer[h][w] = shifted_z;
        }
    }

    //std::cout << "finished\n";
}



void Render::ToConsole(void){
    std::cout << "\x1b[H";
    std::cout << ANSI_PINK;
    for (uint32_t h = 0; h < height; h++)
    {
        for (uint32_t w = 0; w < width; w++)
        {
            if (Interpolation[h][w] == 0.0f){
                std::putchar(' ');
            }
            else{
                //std::cout << Interpolation[h][w];
                int lumenIndex = (Interpolation[h][w] * 10.0 + 10.0); //ensure everything is positive
                std::putchar("  ..,,,---~:;=!*##$$@@@"[lumenIndex]);
            }
            Interpolation[h][w] = 0.0f;
            Zbuffer[h][w] = 0.0f;
        }
        std::putchar('\n');
    }
}





void Render::SetProjectionZ(float proj_z){
    projection_z = proj_z;
}




void Render::SetDisplacementZ(float disp_z){
    displacement_z = disp_z;
}



void Render::SetLighting(float lx, float ly, float lz){
    float mag = sqrtf(lx*lx + ly*lx + lz*lz);
    lighting_x = lx/mag;
    lighting_y = ly/mag;
    lighting_z = lz/mag;
}




void Render::setSize(float multiplierX, float multiplierY){
    TensorArray projected_tensors = tensors.GetProjection(displacement_z, projection_z);
    size_x = _getSizeX(projected_tensors) * multiplierX;
    size_y = _getSizeY(projected_tensors) * multiplierY;
    delta_x = size_x/width;
    delta_y = size_y/height;
}





/* WORKER METHODS */


float Render::_NormLuminence(VertexTensor face){
    float dot = face.norm_x*lighting_x + face.norm_y*lighting_y + face.norm_z*lighting_z;
    return -1.0f*dot;
}



float Render::_getSizeX(TensorArray tensors){
    float max_x = tensors.GetTensor(0).x;
    float min_x = tensors.GetTensor(0).x;

    for (uint32_t i = 1; i < tensors.current_size; i++)
    {
        if (tensors.GetTensor(i).x > max_x) max_x = tensors.GetTensor(i).x;
        if (tensors.GetTensor(i).x < min_x) min_x = tensors.GetTensor(i).x;
    }
    return max_x - min_x;
}


float Render::_getSizeY(TensorArray tensors){
    float max_y = tensors.GetTensor(0).y;
    float min_y = tensors.GetTensor(0).y;

    for (uint32_t i = 1; i < tensors.current_size; i++)
    {
        if (tensors.GetTensor(i).x > max_y) max_y = tensors.GetTensor(i).y;
        if (tensors.GetTensor(i).x < min_y) min_y = tensors.GetTensor(i).y;
    }

    return max_y - min_y;
}

uint32_t Render::_divideAndRound(float numerator, float denominator) {
    float result = numerator / denominator;
    return static_cast<uint32_t>(std::round(result));
}