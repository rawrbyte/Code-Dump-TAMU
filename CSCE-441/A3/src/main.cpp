#include <cassert>
#include <cstring>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "GLSL.h"
#include "MatrixStack.h"
#include "Program.h"
#include "Shape.h"

#include "Material.h"
#include "Light.h"

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from

shared_ptr<Camera> camera;
shared_ptr<Program> prog1;
shared_ptr<Program> prog2;
shared_ptr<Shape> shape;

vector<Material> modes;
Light bigL(vec3(1.0, 1.0, 1.0), 1);
Light lilL(vec3(-1.0, 1.0, 1.0), 0);

char buttonPress = '0';
bool keyToggles[256] = {false}; // only for English keyboards
bool x = false, X = false, y = false, Y = false, s = true, S = false;
int modevalue = 0;
int lightvalue = 0;

// This function is called when a GLFW error occurss
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		if ((mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) || (mods == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)) {
			if (modevalue < 2) {
				modevalue++;
			}
		}
		else{
			if (modevalue > 0) {
				modevalue--;
			}
		}
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		if ((mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) || (mods == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)) {
			if (lightvalue < 1) {
				lightvalue++;
			}
		}
		else {
			if (lightvalue > 0) {
				lightvalue--;
			}
		}
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		if ((mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) || (mods == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)) {
			X = true;
		}
		else {
			x = true;
		}
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		if ((mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) || (mods == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)) {
			Y = true;
		}
		else {
			y = true;
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if ((mods == GLFW_MOD_SHIFT && action == GLFW_PRESS) || (mods == GLFW_KEY_CAPS_LOCK && action == GLFW_PRESS)) {
			S = true;
			s = false;
		}
		else {
			s = true;
			S = false;
		}
	}
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = (mods & GLFW_MOD_SHIFT) != 0;
		bool ctrl  = (mods & GLFW_MOD_CONTROL) != 0;
		bool alt   = (mods & GLFW_MOD_ALT) != 0;
		camera->mouseClicked((float)xmouse, (float)ymouse, shift, ctrl, alt);
	}
}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved((float)xmouse, (float)ymouse);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
}

// If the window is resized, capture the new size and reset the viewport
static void resize_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// This function is called once to initialize the scene and OpenGL
static void init()
{
	// Initialize time.
	glfwSetTime(0.0);
	
	// Set background color.
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test.
	glEnable(GL_DEPTH_TEST);

	prog1 = make_shared<Program>();
	prog1->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag.glsl");
	prog1->setVerbose(true);
	prog1->init();
	prog1->addAttribute("aPos");
	prog1->addAttribute("aNor");
	prog1->addAttribute("aTex");
	prog1->addUniform("MV");
	prog1->addUniform("P");
	prog1->addUniform("lightPos");
	prog1->addUniform("lightPos2");
	prog1->addUniform("ka");
	prog1->addUniform("kd");
	prog1->addUniform("ks");
	prog1->addUniform("s");

	prog2 = make_shared<Program>();
	prog2->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag2.glsl");
	prog2->setVerbose(true);
	prog2->init();
	prog2->addAttribute("aPos");
	prog2->addAttribute("aNor");
	prog2->addAttribute("aTex");
	prog2->addUniform("MV");
	prog2->addUniform("P");
	
	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f);
	
	shape = make_shared<Shape>();
	shape->loadMesh(RESOURCE_DIR + "bunny.obj");
	shape->fitToUnitBox();
	shape->init();
	
	GLSL::checkError(GET_FILE_LINE);

	Material mode1(vec3(0.2, 0.2, 0.2), vec3(0.0, 0.0, 0.8), vec3(0.0, 1.0, 0.0), 1);
	Material mode2(vec3(0.1, 0.1, 0.1), vec3(0.2, 0.31, 0.6), vec3(0.1, 0.1, 0.1), 2);
	Material mode3(vec3(0.2, 0.2, 0.2), vec3(0.8, 0.7, 0.7), vec3(1.0, 0.9, 0.8), 3);

	modes.push_back(mode1);
	modes.push_back(mode2);
	modes.push_back(mode3);
}

// This function is called every frame to draw the scene.
static void render()
{
	// Clear framebuffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'q']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	// Matrix stacks
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);


	if (s == true) {
		bigL.updateLight(lightvalue, x, y, X, Y);
		lilL.updateLight(lightvalue, x, y, X, Y);
		prog1->bind();
		glUniformMatrix4fv(prog1->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(prog1->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		glUniform3f(prog1->getUniform("lightPos"), bigL.l.x, bigL.l.y, bigL.l.z);
		glUniform3f(prog1->getUniform("lightPos2"), lilL.l.x, lilL.l.y, lilL.l.z);
		glUniform3f(prog1->getUniform("ka"), modes[modevalue].ka.x, modes[modevalue].ka.y, modes[modevalue].ka.z);
		glUniform3f(prog1->getUniform("kd"), modes[modevalue].kd.x, modes[modevalue].kd.y, modes[modevalue].kd.z);
		glUniform3f(prog1->getUniform("ks"), modes[modevalue].ks.x, modes[modevalue].ks.y, modes[modevalue].ks.z);
		glUniform1f(prog1->getUniform("s"), 200);
		shape->draw(prog1);
		prog1->unbind();
	}
	else if (S == true) {
		prog2->bind();
		glUniformMatrix4fv(prog2->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(prog2->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		shape->draw(prog2);
		prog2->unbind();
	}
	
	MV->popMatrix();
	P->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);

	x = false;
	X = false;
	y = false;
	Y = false;
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Please specify the resource directory." << endl;
		return 0;
	}
	RESOURCE_DIR = argv[1] + string("/");

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "YOUR NAME", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
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
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Set the window resize call back.
	glfwSetFramebufferSizeCallback(window, resize_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
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
