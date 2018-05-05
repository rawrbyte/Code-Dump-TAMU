#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Light
{
public:
	int value;
	glm::vec3 l;
	Light(glm::vec3 L, int lv);
	void updateLight(int lv, bool x, bool y, bool X, bool Y);
private:

};
#endif
