#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

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

#include "tiny_obj_loader.h"

#include "GLSL.h"
#include "MatrixStack.h"

#include "Shape.h"
#include "Program.h"

class Component
{
public:
	float angle;
	int body;
	glm::vec3 tJoint;
	glm::vec3 aJoint;
	glm::vec3 tmJoint;
	glm::vec3 sFactor;

	std::vector<Component> children;
	std::vector<Component> Parent;

	Component(glm::vec3 transJ, glm::vec3 angleJ, glm::vec3 tmeshJ, glm::vec3 scaleF, float Ang, int bodypart);
	void setChild(Component child);
	void setParent(Component parent);
	void DrawComponent(MatrixStack &mv, MatrixStack &p, std::shared_ptr<Program> prog, std::shared_ptr<Shape> shape, int pos, bool x, bool X, bool y, bool Y, bool z, bool Z);
private:

};
#endif
