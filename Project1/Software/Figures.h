#pragma once
#include "figure.h"
#include "lib.h"

using namespace std;
using namespace glm;

class Triangle : public Figure
{
public:
    Triangle(unsigned int numberOfTriangles, GLuint MatModel);       // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Circle : public Figure
{
public:
    Circle(unsigned int numberOfTriangles, GLuint MatModel); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Butterfly : public Figure
{
public:
    Butterfly(unsigned int numberOfTriangles, GLuint MatModel); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};

class Heart : public Figure
{
public:
    Heart(unsigned int numberOfTriangles, GLuint MatModel); // Add MatModel to the constructor
    void initFigure(int TypeOfDraw) override;
};


class Rettangle : public Figure
{
	public:
	Rettangle(unsigned int numberOfTriangles, GLuint MatModel); // Add MatModel to the constructor
	void initFigure(int TypeOfDraw) override;
};