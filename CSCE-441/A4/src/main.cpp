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
#include "Texture.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define ANGLE 60.0f

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = "./"; // Where the resources are loaded from

shared_ptr<Camera> camera;
shared_ptr<Program> prog;
shared_ptr<Program> prog2;
shared_ptr<Texture> texture0;
shared_ptr<Shape> shape;
shared_ptr<Shape> sphere;
shared_ptr<Shape> bunny;
shared_ptr<Shape> teapot;

vector<float> posBuf;
vector<float> texBuf;
vector<unsigned int> indBuf;
map<string, GLuint> bufIDs;
int indCount;

mat3 T1;

vector<Material> population;

bool keyToggles[256] = {false}; // only for English keyboards

bool mouseinit = true;
float pX = 400;
float pY = 300;
float xV = -90.0f;
float yV = 0.0f;

// This function is called when a GLFW error occurss
static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

// This function is called when a key is pressed
static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W) {
		camera->cameraMovement(UP);
	}
	if (key == GLFW_KEY_S) {
		camera->cameraMovement(DOWN);
	}
	if (key == GLFW_KEY_A) {
		camera->cameraMovement(LEFT);
	}
	if (key == GLFW_KEY_D) {
		camera->cameraMovement(RIGHT);
	}

	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// This function is called when the mouse is clicked
static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods){}

// This function is called when the mouse moves
static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	if (mouseinit) {
		pX = (float) xmouse;
		pY = (float) ymouse;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		mouseinit = false;
	}

	float xM = (float) xmouse - pX;
	float yM = (float) ymouse - pY;
	pX = (float) xmouse;
	pY = (float) ymouse;

	float sens = 0.05f;
	xM = xM * sens;
	yM = yM * sens;

	xV += xM;
	yV += yM;
	if (yV > ANGLE) {
		yV = ANGLE;
	}
	if (yV < -ANGLE) {
		yV = -ANGLE;
	}
	vec3 f;
	f.x = cos(radians(yV)) * cos(radians(xV));
	f.y = -sin(radians(yV));
	f.z = sin(radians(xV)) * cos(radians(yV));
	camera->cFront = normalize(f);
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

	prog = make_shared<Program>();
	prog->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag.glsl");
	prog->setVerbose(true);
	prog->init();
	prog->addAttribute("aPos");
	prog->addAttribute("aNor");
	prog->addAttribute("aTex");
	prog->addUniform("MV");
	prog->addUniform("L");
	prog->addUniform("P");
	prog->addUniform("ka");
	prog->addUniform("kd");
	prog->addUniform("ks");
	prog->addUniform("s");

	prog2 = make_shared<Program>();
	prog2->setShaderNames(RESOURCE_DIR + "vert.glsl", RESOURCE_DIR + "frag2.glsl");
	prog2->setVerbose(true);
	prog2->init();
	prog2->addAttribute("aPos");
	prog2->addAttribute("aTex");
	prog2->addUniform("MV");
	prog2->addUniform("P");
	prog2->addUniform("T1");
	prog2->addUniform("texture0");
	
	camera = make_shared<Camera>();
	camera->setInitDistance(2.0f);

	sphere = make_shared<Shape>();
	sphere->loadMesh(RESOURCE_DIR + "sphere.obj");
	sphere->fitToUnitBox();
	sphere->init();
	
	bunny = make_shared<Shape>();
	bunny->loadMesh(RESOURCE_DIR + "bunny.obj");
	bunny->fitToUnitBox();
	bunny->init();

	teapot = make_shared<Shape>();
	teapot->loadMesh(RESOURCE_DIR + "teapot.obj");
	teapot->fitToUnitBox();
	teapot->init();

	texture0 = make_shared<Texture>();
	texture0->setFilename(RESOURCE_DIR + "green1.jpg");
	texture0->init();
	texture0->setUnit(0);
	texture0->setWrapModes(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

	T1[0][0] = 1.0f;

	posBuf.push_back(-1.0f);
	posBuf.push_back(-1.0f);
	posBuf.push_back(0.0f);
	texBuf.push_back(0.0f);
	texBuf.push_back(0.0f);
	// 1
	posBuf.push_back(1.0f);
	posBuf.push_back(-1.0f);
	posBuf.push_back(0.0f);
	texBuf.push_back(1.0f);
	texBuf.push_back(0.0f);
	// 2
	posBuf.push_back(-1.0f);
	posBuf.push_back(1.0f);
	posBuf.push_back(0.0f);
	texBuf.push_back(0.0f);
	texBuf.push_back(1.0f);
	// 3
	posBuf.push_back(1.0f);
	posBuf.push_back(1.0f);
	posBuf.push_back(0.0f);
	texBuf.push_back(1.0f);
	texBuf.push_back(1.0f);
	// Index
	indBuf.push_back(0);
	indBuf.push_back(1);
	indBuf.push_back(2);
	indBuf.push_back(3);
	indBuf.push_back(2);
	indBuf.push_back(1);
	indCount = (int)indBuf.size();

	// Generate 3 buffer IDs and put them in the bufIDs map.
	GLuint tmp[3];
	glGenBuffers(3, tmp);
	bufIDs["bPos"] = tmp[0];
	bufIDs["bTex"] = tmp[1];
	bufIDs["bInd"] = tmp[2];

	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bPos"]);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size() * sizeof(float), &posBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bTex"]);
	glBufferData(GL_ARRAY_BUFFER, texBuf.size() * sizeof(float), &texBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIDs["bInd"]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indBuf.size() * sizeof(unsigned int), &indBuf[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	vec3 KA = vec3(0.2f, 0.2f, 0.2f);
	vec3 KS = vec3(1.0f, 0.9f, 0.8f);
	vec3 rot = vec3(0.0f, 1.0f, 0.0f);

	for (int x = -5; x < 6; ++x) {
		for (int z = -5; z < 6; z++) {
			float r = (float) ((rand() % 255) / 255.0);
			float g = (float) ((rand() % 255) / 255.0);
			float b = (float) ((rand() % 255) / 255.0);
			vec3 rando = vec3(r, g, b);
			if (x % 2 == 0) {
				vec3 t = vec3(1.5f * x, -1.0f, 1.5f * -z);
				vec3 s = vec3(1.0f, 1.0f, 1.0f);
				Material mode(bunny, KA, rando, KS, t, rot, s);
				population.push_back(mode);
			}
			else {
				vec3 t = vec3(1.5f * x, -1.25f, 1.5f * -z);
				vec3 s = vec3(1.0f, 1.0f, 1.0f);
				Material mode(teapot, KA, rando, KS, t, rot, s);
				population.push_back(mode);
			}
		}
	}
	GLSL::checkError(GET_FILE_LINE);
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
	auto L = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);
	L->pushMatrix();
	camera->applyViewMatrix(L);

	MV->pushMatrix();
		MV->translate(0, -1.5, 0);
		MV->rotate(90.0f * (float) (M_PI/180), vec3(1, 0, 0));
		MV->scale(8, 8, 8);
		prog2->bind();
			texture0->bind(prog2->getUniform("texture0"));
			glUniformMatrix4fv(prog2->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
			glUniformMatrix4fv(prog2->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
			glUniformMatrix3fv(prog2->getUniform("T1"), 1, GL_FALSE, glm::value_ptr(T1));
			glEnableVertexAttribArray(prog2->getAttribute("aPos"));
			glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bPos"]);
			glVertexAttribPointer(prog2->getAttribute("aPos"), 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			glEnableVertexAttribArray(prog2->getAttribute("aTex"));
			glBindBuffer(GL_ARRAY_BUFFER, bufIDs["bTex"]);
			glVertexAttribPointer(prog2->getAttribute("aTex"), 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIDs["bInd"]);
			glDrawElements(GL_TRIANGLES, indCount, GL_UNSIGNED_INT, (void *)0);
			texture0->unbind();
		prog2->unbind();
	MV->popMatrix();

	MV->pushMatrix();
		MV->translate(9.0f, 5.0f,-6.0f);
		MV->topMatrix();
		prog->bind();
			glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
			glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
			glUniformMatrix4fv(prog->getUniform("L"), 1, GL_FALSE, glm::value_ptr(L->topMatrix()));
			glUniform3f(prog->getUniform("ka"), 1.0f, 1.0f, 0.0f);
			glUniform3f(prog->getUniform("kd"), 1.0f, 1.0f, 0.0f);
			glUniform3f(prog->getUniform("ks"), 1.0f, 1.0f, 0.0f);
			glUniform1f(prog->getUniform("s"), 200.0f);
		sphere->draw(prog);
		prog->unbind();
	MV->popMatrix();

	for (size_t x = 0; x < population.size(); ++x) {
		MV->pushMatrix();
			MV->translate(population[x].translate);
			MV->rotate(population[x].angle * (float)(M_PI / 180), population[x].rotate);
			MV->scale(population[x].scale);
			shape = population[x].obj;
			prog->bind();
				glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glUniformMatrix4fv(prog->getUniform("L"), 1, GL_FALSE, glm::value_ptr(L->topMatrix()));
				glUniform3f(prog->getUniform("ka"), population[x].ka.x, population[x].ka.y, population[x].ka.z);
				glUniform3f(prog->getUniform("kd"), population[x].kd.x, population[x].kd.y, population[x].kd.z);
				glUniform3f(prog->getUniform("ks"), population[x].ks.x, population[x].ks.y, population[x].ks.z);
				glUniform1f(prog->getUniform("s"), 200.0f);
				shape->draw(prog);
			prog->unbind();
		MV->popMatrix();
	}

	L->popMatrix();
	MV->popMatrix();
	P->popMatrix();
	
	GLSL::checkError(GET_FILE_LINE);
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
