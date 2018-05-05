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

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "GLSL.h"
#include "MatrixStack.h"

#include "Shape.h"
#include "Program.h"
#include "Component.h"

#define GLFW_MOD_ALT   0x0004
#define GLFW_MOD_CONTROL   0x0002
#define GLFW_MOD_SHIFT   0x0001
#define GLFW_MOD_SUPER   0x0008

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from

GLuint progID;
map<string, GLint> attrIDs;
map<string, GLint> unifIDs;
map<string, GLuint> bufIDs;
shared_ptr<Program> prog;
shared_ptr<Shape> shape;
vector<Component> robot;
int indCount;
int pos = 0;
bool x = false, X = false, y = false, Y = false, z = false, Z = false;

// This function is called when a GLFW error occurs
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_COMMA && action == GLFW_PRESS) {
		if (pos > 0) {
			pos--;
		}
	}
	if (key == GLFW_KEY_PERIOD && action == GLFW_PRESS) {
		if (pos < 9) {
			pos++;
		}
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		if (mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) {
			X = true;
		}
		else {
			x = true;
		}
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		if (mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) {
			Y = true;
		}
		else {
			y = true;
		}
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		if (mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) {
			Z = true;
		}
		else {
			z = true;
		}
	}
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void init()
{
	GLSL::checkVersion();

	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	// Initialize mesh.
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "cube.obj");
	shape->init();

	// Initialize the GLSL program.
	prog = make_shared<Program>();
	prog->setVerbose(false); // Set this to true when debugging.
	prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag.glsl");
	prog->init();
	prog->addUniform("P");
	prog->addUniform("MV");
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");

	//Torso
	float angle = 0;
	int bodypart = 0;
	vec3 torsoScale(0.6, 1, 0.4);
	vec3 torsoAngle(0, 0, 0);
	vec3 torsoMeshT(0, 0, 0);
	vec3 torsoTrans(0, 0, 0);
	Component torso = Component(torsoTrans, torsoAngle, torsoMeshT, torsoScale, angle, bodypart);

	//Head
	bodypart = 1;
	vec3 headScale(0.3, 0.3, 0.25);
	vec3 headAngle(0, 0, 0);
	vec3 headMeshT(0, 0.15, 0);
	vec3 headTrans(torsoTrans.x + 0, torsoTrans.y + 0.5, torsoTrans.z + 0);
	Component head = Component(headTrans, headAngle, headMeshT, headScale, angle, bodypart);

	//Right Arm
	bodypart = 4;
	vec3 rBigArmScale(0.6, 0.25, 0.2);
	vec3 rBigArmAngle(0, 0, 0);
	vec3 rBigArmMeshT(0.3, 0, 0);
	vec3 rBigArmTrans(torsoTrans.x + 0.3, torsoTrans.y + 0.35, torsoTrans.z + 0);
	Component rBigArm = Component(rBigArmTrans, rBigArmAngle, rBigArmMeshT, rBigArmScale, angle, bodypart);

	bodypart = 5;
	vec3 rSmallArmScale(0.5, 0.18, 0.15);
	vec3 rSmallArmAngle(0, 0, 0);
	vec3 rSmallArmMeshT(0.25, 0, 0);
	vec3 rSmallArmTrans(torsoTrans.x + 0.6, torsoTrans.y + 0, torsoTrans.z + 0);
	Component rSmallArm = Component(rSmallArmTrans, rSmallArmAngle, rSmallArmMeshT, rSmallArmScale, angle, bodypart);

	//Left Arm
	bodypart = 2;
	vec3 lBigArmScale(0.6, 0.25, 0.2);
	vec3 lBigArmAngle(0, 0, 0);
	vec3 lBigArmMeshT(-0.3, 0, 0);
	vec3 lBigArmTrans(torsoTrans.x + -0.3, torsoTrans.y + 0.35, torsoTrans.z + 0);
	Component lBigArm = Component(lBigArmTrans, lBigArmAngle, lBigArmMeshT, lBigArmScale, angle, bodypart);

	bodypart = 3;
	vec3 lSmallArmScale(0.5, 0.18, 0.15);
	vec3 lSmallArmAngle(0, 0, 0);
	vec3 lSmallArmMeshT(-0.25, 0, 0);
	vec3 lSmallArmTrans(torsoTrans.x + -0.6, torsoTrans.y + 0, torsoTrans.z + 0);
	Component lSmallArm = Component(lSmallArmTrans, lSmallArmAngle, lSmallArmMeshT, lSmallArmScale, angle, bodypart);

	//Right Leg
	bodypart = 8;
	vec3 rBigLegScale(0.25, 0.5, 0.3);
	vec3 rBigLegAngle(0, 0, 0);
	vec3 rBigLegMeshT(0, -0.25, 0);
	vec3 rBigLegTrans(torsoTrans.x + 0.15, torsoTrans.y + -0.5, torsoTrans.z + 0);
	Component rBigLeg = Component(rBigLegTrans, rBigLegAngle, rBigLegMeshT, rBigLegScale, angle, bodypart);

	bodypart = 9;
	vec3 rSmallLegScale(0.2, 0.55, 0.2);
	vec3 rSmallLegAngle(0, 0, 0);
	vec3 rSmallLegMeshT(0, -0.25, 0);
	vec3 rSmallLegTrans(torsoTrans.x + 0, torsoTrans.y + -0.5, torsoTrans.z + 0);
	Component rSmallLeg = Component(rSmallLegTrans, rSmallLegAngle, rSmallLegMeshT, rSmallLegScale, angle, bodypart);

	//Left Leg
	bodypart = 6;
	vec3 lBigLegScale(0.25, 0.5, 0.3);
	vec3 lBigLegAngle(0, 0, 0);
	vec3 lBigLegMeshT(0, -0.25, 0);
	vec3 lBigLegTrans(torsoTrans.x + -0.15, torsoTrans.y + -0.5, torsoTrans.z + 0);
	Component lBigLeg = Component(lBigLegTrans, lBigLegAngle, lBigLegMeshT, lBigLegScale, angle, bodypart);

	bodypart = 7;
	vec3 lSmallLegScale(0.2, 0.55, 0.2);
	vec3 lSmallLegAngle(0, 0, 0);
	vec3 lSmallLegMeshT(0, -0.25, 0);
	vec3 lSmallLegTrans(torsoTrans.x + 0, torsoTrans.y + -0.5, torsoTrans.z + 0);
	Component lSmallLeg = Component(lSmallLegTrans, lSmallLegAngle, lSmallLegMeshT, lSmallLegScale, angle, bodypart);

	//Creation
	head.setParent(torso);
	lBigArm.setParent(torso);
	rBigArm.setParent(torso);
	lBigLeg.setParent(torso);
	rBigLeg.setParent(torso);

	lSmallArm.setParent(lBigArm);
	rSmallArm.setParent(rBigArm);
	lSmallLeg.setParent(lBigLeg);
	rSmallLeg.setParent(rBigLeg);

	lBigArm.setChild(lSmallArm);
	rBigArm.setChild(rSmallArm);
	lBigLeg.setChild(lSmallLeg);
	rBigLeg.setChild(rSmallLeg);

	torso.setChild(head);
	torso.setChild(lBigArm);
	torso.setChild(rBigArm);
	torso.setChild(lBigLeg);
	torso.setChild(rBigLeg);

	robot.push_back(torso);


	// If there were any OpenGL errors, this will print something.
	// You can intersperse this line in your code to find the exact location
	// of your OpenGL error.
	GLSL::checkError(GET_FILE_LINE);
}

void Draw(Component component)
{

}

static void render()
{
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float aspect = width / (float)height;
	glViewport(0, 0, width, height);

	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Create matrix stacks.
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	// Apply projection.
	P->pushMatrix();
	P->multMatrix(glm::perspective((float)(45.0*M_PI / 180.0), aspect, 0.01f, 100.0f));
	// Apply camera transform.
	MV->loadIdentity();
	MV->pushMatrix();
	MV->translate(glm::vec3(0, 0, -4.5));
	MatrixStack p = *P;
	MatrixStack mv = *MV;
	robot[0].DrawComponent(mv, p, prog, shape, pos, x, X, y, Y, z, Z);

	MV->popMatrix();
	P->popMatrix();

	x = false;
	X = false;
	y = false;
	Y = false;
	z = false;
	Z = false;

	GLSL::checkError(GET_FILE_LINE);
}


int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if (!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "YOUR NAME", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	GLSL::checkVersion();
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while (!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();

	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
