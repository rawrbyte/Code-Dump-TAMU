#pragma  once
#ifndef __Camera__
#define __Camera__

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class MatrixStack;

class Camera
{
public:
	Camera();
	virtual ~Camera();
	void setInitDistance(float z) { translations.z = -std::abs(z); }
	void setAspect(float a) { aspect = a; };
	void cameraMovement(int direction);
	void applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const;
	void applyViewMatrix(std::shared_ptr<MatrixStack> MV) const;

	glm::vec3 cEye = glm::vec3(0.0f, -1.0f, 1.0f);
	glm::vec3 cFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float speed = 0.05f;
	
private:
	float aspect;
	float fovy;
	float znear;
	float zfar;
	glm::vec2 rotations;
	glm::vec3 translations;
};

#endif
