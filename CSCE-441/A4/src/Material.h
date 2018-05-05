#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "GLSL.h"
#include "MatrixStack.h"

#include "Shape.h"
#include "Program.h"

class Material
{
public:
	int mode;
	float angle;
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;

	glm::vec3 translate;
	glm::vec3 rotate;
	glm::vec3 scale;

	std::shared_ptr<Shape> obj;

	Material(std::shared_ptr<Shape> shape, glm::vec3 KA, glm::vec3 KD, glm::vec3 KS, glm::vec3 t, glm::vec3 r, glm::vec3 s);
private:

};
#endif
