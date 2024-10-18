#pragma once
#include "strutture.h"


#define _USE_MATH_DEFINES
#include "math.h"

void INIT_TRIANGLE(Figura* fig) 
{
    fig->vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.5f, -0.5f, 0.0f));
    fig->vertices.push_back(vec3(0.0f, 0.5f, 0.0f));

    fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 1.0, 0.0, 1.0));
    fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0));
    fig->nv = 3;
    fig->render = GL_TRIANGLES;
}


void INIT_CIRCLE(Figura *fig, float cx, float cy,float raggiox, float raggioy ) 
{

    float stepA = (2 * M_PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));
    fig->colors.push_back(vec4(1.0,1.0,1.0,1.0)); //colore bianco vertice centrale

    float t;
    float xx;
    float yy;
    for (int i = 0; i <= fig->nTriangles; i++) 
    {
        t = (float)i * stepA;
        xx = cx + raggiox * cos(t);
        yy = cy + raggioy * sin(t);
        fig->vertices.push_back(vec3(xx,yy,0.0));
        fig->colors.push_back(vec4(0.0, 0.0, 1.0, 1.0)); //blu gli altri
    }

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}


void INIT_HEART(Figura* fig,float scale, float cx, float cy)
{

    float stepA = (2 * M_PI) / fig->nTriangles;
    fig->vertices.push_back(vec3(cx, cy, 0.0));
    fig->colors.push_back(vec4(1.0, 1.0, 1.0, 1.0)); //colore bianco vertice centrale

    float t;
    float xx;
    float yy;
    for (int i = 0; i <= fig->nTriangles; i++)
    {
        t = (float)i * stepA;
        xx = scale* (16 * std::pow(std::sin(t), 3));
        yy = scale* (13 * std::cos(t) - 5 * std::cos(2 * t) - 2 * std::cos(3 * t) - std::cos(4 * t));
        fig->vertices.push_back(vec3(xx, yy, 0.0));
        fig->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0)); //rosso gli altri
    }

    fig->nv = fig->vertices.size();
    fig->render = GL_TRIANGLE_FAN;
}




