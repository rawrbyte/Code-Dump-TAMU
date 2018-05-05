#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Vertex
{
public:
	Vertex();
	float W[16] = {};
	int I[16] = {};
private:

};
#endif
