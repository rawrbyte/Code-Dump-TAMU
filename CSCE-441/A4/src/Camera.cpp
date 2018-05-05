#include "Camera.h"
#include "MatrixStack.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Camera::Camera() :
	aspect(1.0f),
	fovy(45.0f),
	znear(0.1f),
	zfar(1000.0f),
	rotations(0.0, 0.0),
	translations(0.0f, 1.0f, -5.0f)
{
}

Camera::~Camera()
{
}

void Camera::cameraMovement(int direction) 
{
	if (direction == UP)
		cEye += speed * cFront;
		cEye.y = -1.0f;
	if (direction == DOWN)
		cEye -= speed * cFront;
		cEye.y = -1.0f;
	if (direction == LEFT)
		cEye -= glm::normalize(glm::cross(cFront, cUp)) * speed;
	if (direction == RIGHT)
		cEye += glm::normalize(glm::cross(cFront, cUp)) * speed;
}

void Camera::applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const
{
	// Modify provided MatrixStack
	P->multMatrix(glm::perspective(fovy, aspect, znear, zfar));
}

void Camera::applyViewMatrix(std::shared_ptr<MatrixStack> MV) const
{
	glm::vec3 cTarget = cEye + cFront;
	glm::mat4 cView = glm::lookAt(cEye, cTarget, cUp);
	MV->multMatrix(cView);
	MV->rotate(rotations.y, glm::vec3(1.0f, 0.0f, 0.0f));
	MV->rotate(rotations.x, glm::vec3(0.0f, 1.0f, 0.0f));
}
