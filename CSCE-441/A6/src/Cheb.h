#pragma once
#ifndef _CHEB_H_
#define _CHEB_H_
#include <iostream>
#include <vector>
#include "Bone.h"
#include <memory>


#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cheb
{
public:
	Cheb();
	void loadSkeleton(const std::string &filename);
	std::vector<Bone*> getChebby();
private:
	std::vector<Bone*> chebby;
};
#endif
