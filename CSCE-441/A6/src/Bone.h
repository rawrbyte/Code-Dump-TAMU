#pragma once
#ifndef _BONE_H_
#define _BONE_H_
#include <iostream>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Bone
{
public:
	Bone();
	glm::quat bindQ;
	glm::vec3 bindP;
	glm::mat4 bindE;
	glm::mat4 inverseE;
	std::vector<glm::quat> Q;
	std::vector<glm::vec3> P;
	std::vector<glm::mat4> E;
private:

};
#endif
