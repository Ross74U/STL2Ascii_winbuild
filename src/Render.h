/* Singleton class to package main rendering tasks*/
// Interporlate: Vertex Array -> Float** discrete array
//      ->_NormLuminence
// _NormLuminence(params: vector parallel to light direction)
#ifndef RENDER_H
#define RENDER_H
#include "TensorArray.h"
#include <vector>
#include <cmath>
#include <iostream>


#define ANSI_PINK "\e[38;5;212m" // https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124

class Render{

private:

    uint32_t width;
    uint32_t height;

    float size_x;
    float size_y;

    // how much of the relative space each ASCII takes up
    float delta_x;
    float delta_y;

    /* Projection paramters that will be applied onto the tensor array during interpolation*/
    float displacement_z;
    float projection_z;

    /* Lighting Norm vectors */
    float lighting_x;
    float lighting_y;
    float lighting_z;

    /* holds the final product of interpolation, 2 dimensional vector with luminence values*/
    std::vector<std::vector<float>> Interpolation;

    /* holds the z value of the closest vertexTensor to the user, mirrors Interpolation*/
    std::vector<std::vector<float>> Zbuffer;

public:
    // unaltered tensors of the original object
    TensorArray tensors;



private:
    float _NormLuminence(VertexTensor face);

    /* _getSize -> sets size to 2x the x and y range of the input TensorArray
    in it's current state (should be after projection) */
    float _getSizeX(TensorArray tensors);
    float _getSizeY(TensorArray tensors);

    uint32_t _divideAndRound(float numerator, float denominator);


public:
    /* rendering window size (in number of chars in width and length) */
    Render(
        uint32_t w, uint32_t h,
        float disp_z,
        float proj_z
    );

    /* Gets projection of current tensors onto plane
    and interpolates it onto the interpolation vector[2] with luminence*/
    void Interpolate(void);

    void ToConsole(void); // prints the interpolation in ascii to console;


    void SetProjectionZ(float proj_z);
    void SetDisplacementZ(float disp_z);

    // Normalize before setting
    void SetLighting(float x, float y, float z);

    /* sets the size of the canvas.
    multiplier: the ratio of the canvas to the x,y range of the stl
    this should be run once the tensors have been set
    */
    void setSize(float multiplierX, float multiplierY);
};

#endif
