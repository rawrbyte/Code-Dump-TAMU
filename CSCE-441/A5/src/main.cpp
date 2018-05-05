#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Camera.h"
#include "GLSL.h"
#include "Program.h"
#include "MatrixStack.h"
#include "Shape.h"

using namespace std;

bool keyToggles[256] = {false}; // only for English keyboards!

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from

shared_ptr<Program> progNormal;
shared_ptr<Program> progSimple;
shared_ptr<Camera> camera;
shared_ptr<Shape> body1;
shared_ptr<Shape> body2;
shared_ptr<Shape> prop1;
shared_ptr<Shape> prop2;

int k = 0;

// Control points
vector<glm::vec3> cps;
vector<glm::quat> quatb;
vector<glm::mat4> rots;

glm::mat4 Bcr;

vector<pair<float, float> > usTable;

void buildTable();

static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
}

static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved(xmouse, ymouse);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = mods & GLFW_MOD_SHIFT;
		bool ctrl  = mods & GLFW_MOD_CONTROL;
		bool alt   = mods & GLFW_MOD_ALT;
		camera->mouseClicked(xmouse, ymouse, shift, ctrl, alt);
	}
}

void buildTable()
{
	if (cps.size() >= 4) {
		glm::mat4 B = Bcr;
		glm::mat4 Gk;
		float uu = 0.0;
		usTable.push_back(make_pair(0.0f, 0.0f));
		for (int k = 0; k < cps.size() - 3; ++k) {
			for (int i = 0; i < 4; ++i) {
				Gk[i] = glm::vec4(cps[k + i], 0.0f);
			}
			for (float u = 0.2; u <= 1.0; u += 0.2) {
				float ua = u - 0.2f;
				float ub = u;
				glm::vec4 uaVec(1.0f, ua, ua*ua, ua*ua*ua);
				glm::vec4 ubVec(1.0f, ub, ub*ub, ub*ub*ub);
				glm::vec3 pa(Gk *(B * uaVec));
				glm::vec3 pb(Gk *(B * ubVec));
				float s = glm::distance(pb, pa);
				uu += s;
				usTable.push_back(make_pair(ub + k, uu));
			}
		}
	}
	for (int i = 0; i < usTable.size(); i++) {
		cout << usTable[i].first << ", " << usTable[i].second << endl;
	}
}

float s2u(float s)
{
	int index = 0;
	for (int i = 0; i < usTable.size(); i++) {
		if (s < usTable[i].second) {
			index = i;
			break;
		}
	}
	float alpha = (s - usTable[index - 1].second) / (usTable[index].second - usTable[index - 1].second);
	float u = (1 - alpha) * usTable[index - 1].first + alpha * usTable[index].first;
	return u;
}

static void init()
{
	GLSL::checkVersion();
	
	// Set background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test
	glEnable(GL_DEPTH_TEST);
	
	keyToggles[(unsigned)'c'] = true;
	
	// For drawing the bunny
	progNormal = make_shared<Program>();
	progNormal->setShaderNames(RESOURCE_DIR + "normal_vert.glsl", RESOURCE_DIR + "normal_frag.glsl");
	progNormal->setVerbose(true);
	progNormal->init();
	progNormal->addUniform("P");
	progNormal->addUniform("MV");
	progNormal->addAttribute("aPos");
	progNormal->addAttribute("aNor");
	progNormal->addUniform("lightPos");
	progNormal->addUniform("ka");
	progNormal->addUniform("kd");
	progNormal->addUniform("ks");
	progNormal->addUniform("s");
	progNormal->setVerbose(false);
	
	// For drawing the frames
	progSimple = make_shared<Program>();
	progSimple->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	progSimple->setVerbose(true);
	progSimple->init();
	progSimple->addUniform("P");
	progSimple->addUniform("MV");
	progSimple->setVerbose(false);

	body1 = make_shared<Shape>();
	body1->loadMesh(RESOURCE_DIR + "helicopter_body1.obj");
	body1->init();

	body2 = make_shared<Shape>();
	body2->loadMesh(RESOURCE_DIR + "helicopter_body2.obj");
	body2->init();

	prop1 = make_shared<Shape>();
	prop1->loadMesh(RESOURCE_DIR + "helicopter_prop1.obj");
	prop1->init();

	prop2 = make_shared<Shape>();
	prop2->loadMesh(RESOURCE_DIR + "helicopter_prop2.obj");
	prop2->init();
	
	camera = make_shared<Camera>();

	Bcr[0] = glm::vec4(0.0f, 2.0f, 0.0f, 0.0f);
	Bcr[1] = glm::vec4(-1.0f, 0.0f, 1.0f, 0.0f);
	Bcr[2] = glm::vec4(2.0f, -5.0f, 4.0f, -1.0f);
	Bcr[3] = glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f);
	Bcr *= 0.5;
	
	cps.push_back(glm::vec3(0, 0, 0));
	cps.push_back(glm::vec3(0, 0, 0));
	cps.push_back(glm::vec3(4, 2, 3));
	cps.push_back(glm::vec3(3, 5, -3));
	cps.push_back(glm::vec3(-3, 7, 2));
	cps.push_back(glm::vec3(-4, 1, -2));
	cps.push_back(glm::vec3(0, 0, 0));
	cps.push_back(glm::vec3(4, 2, 3));


	glm::vec3 axis0, axis1, axis2, axis3, axis4;
	glm::quat q0, q1, q2, q3, q4;

	axis0 = glm::vec3(0, -1, 0);
	axis0 = glm::normalize(axis0);
	q0 = glm::angleAxis((float)(90.0f / 180.0f*M_PI), axis0);

	axis1 = glm::vec3(0, 0, -1);
	axis1 = glm::normalize(axis1);
	q1 = glm::angleAxis((float)(45.0f / 180.0f*M_PI), axis1);

	axis2 = glm::vec3(0, 0, 1);
	axis2 = glm::normalize(axis2);
	q2 = glm::angleAxis((float)(45.0f / 180.0f*M_PI), axis2);

	axis3 = glm::vec3(0, -1, 1);
	axis3 = glm::normalize(axis3);
	q3 = glm::angleAxis((float)(90.0f / 180.0f*M_PI), axis3);

	axis4 = glm::vec3(0, -1, 0);
	axis4 = glm::normalize(axis4);
	q4 = glm::angleAxis((float)(180.0f / 180.0f*M_PI), axis4);

	quatb.push_back(q4);
	quatb.push_back(q4);
	quatb.push_back(q0);
	quatb.push_back(q1);
	quatb.push_back(q2);
	quatb.push_back(q3);
	quatb.push_back(q4);
	quatb.push_back(q0);

	for (int g = 1; g < 8; ++g) {
		if (glm::dot(quatb[g - 1], quatb[g]) < 0) {
			quatb[g] = -quatb[g];
		}
	}

	// Initialize time.
	glfwSetTime(0.0);

	buildTable();
	
	// If there were any OpenGL errors, this will print something.
	// You can intersperse this line in your code to find the exact location
	// of your OpenGL error.
	GLSL::checkError(GET_FILE_LINE);
}

void render()
{
	// Update time.
	float t = glfwGetTime();
	
	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	// Use the window size for camera.
	glfwGetWindowSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'l']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	MV->translate(0.0, 0, -2.0);
	if (keyToggles[(unsigned)' ']) {
		camera->applyHeliView(MV);
	}
	else {
		camera->applyViewMatrix(MV);
	}

	
	// Draw origin frame
	progSimple->bind();
	glUniformMatrix4fv(progSimple->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
	glUniformMatrix4fv(progSimple->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glLineWidth(1);
	progSimple->unbind();
	GLSL::checkError(GET_FILE_LINE);

	progSimple->bind();
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	for (int x = -30; x < 30; x+=2) {
			glVertex3f(x, 0, -30);
			glVertex3f(x, 0, 30);
		}
	for (int z = -30; z < 30; z+=2) {
			glVertex3f(-30, 0, z);
			glVertex3f(30, 0, z);
	}
	glEnd();

	int ncps = (int)cps.size();

	if (keyToggles[(unsigned)'k']) {
		if (ncps > 3) {
			glColor3f(1.0f, 0.5f, 0.5f);
			for (int j = 0; j < 1 + (ncps - 4); ++j) {
				glBegin(GL_LINE_STRIP);
				for (float u = 0.0; u <= 1.0; u += 0.01) {
					glm::mat4 G;
					G[0] = glm::vec4(cps[j], 0.0f);
					G[1] = glm::vec4(cps[j + 1], 0.0f);
					G[2] = glm::vec4(cps[j + 2], 0.0f);
					G[3] = glm::vec4(cps[j + 3], 0.0f);
					glm::vec4 uVec(1.0f, u, u*u, u*u*u);
					glm::vec4 p = G*(Bcr*uVec);
					glVertex3f(p.x, p.y, p.z);
				}
				glEnd();
			}
		}
	}
	progSimple->unbind();

	progNormal->bind();
	glUniformMatrix4fv(progNormal->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));

	// KEYFRAMES
	if (keyToggles[(unsigned)'k']) {
		int ncps = (int)cps.size();
		for (int i = 0; i < ncps-3; ++i) {
			MV->pushMatrix();
				glm::mat4 G;
				float u = 1.0;
				G[0] = glm::vec4(cps[i], 0.0f);
				G[1] = glm::vec4(cps[i + 1], 0.0f);
				G[2] = glm::vec4(cps[i + 2], 0.0f);
				G[3] = glm::vec4(cps[i + 3], 0.0f);
				glm::vec4 uVec(1.0f, u, u*u, u*u*u);
				glm::vec4 p = G*(Bcr*uVec);
				MV->translate(p.x, p.y, p.z);
				MV->pushMatrix();
					MV->multMatrix(glm::toMat4(quatb[i+2]));
					glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
					glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
					glUniform3f(progNormal->getUniform("ka"), 0.6f, 0.0f, 0.0f);
					glUniform3f(progNormal->getUniform("kd"), 1.0f, 0.0f, 0.0f);
					glUniform3f(progNormal->getUniform("ks"), 7.0f, 0.0f, 0.0f);
					glUniform1f(progNormal->getUniform("s"), 200.0f);
					body1->draw(progNormal);
					glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
					glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
					glUniform3f(progNormal->getUniform("ka"), 0.6f, 0.6f, 0.0f);
					glUniform3f(progNormal->getUniform("kd"), 1.0f, 1.0f, 0.0f);
					glUniform3f(progNormal->getUniform("ks"), 7.0f, 7.0f, 0.0f);
					glUniform1f(progNormal->getUniform("s"), 200.0f);
					body2->draw(progNormal);
					MV->pushMatrix();
						MV->translate(glm::vec3(0.0, 0.4819, 0.0));
						MV->rotate(t, glm::vec3(0, 1, 0));
						MV->translate(glm::vec3(0.0, -0.4819, 0.0));
						glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
						glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
						glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
						glUniform3f(progNormal->getUniform("kd"), 0.5f, 0.5f, 0.5f);
						glUniform3f(progNormal->getUniform("ks"), 0.5f, 0.5f, 0.5f);
						glUniform1f(progNormal->getUniform("s"), 200.0f);
						prop1->draw(progNormal);
					MV->popMatrix();
					MV->pushMatrix();
						MV->translate(glm::vec3(0.6228, 0.1179, 0.1365));
						MV->rotate(t, glm::vec3(0, 0, 1));
						MV->translate(glm::vec3(-0.6228, -0.1179, -0.1365));
						glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
						glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
						glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
						glUniform3f(progNormal->getUniform("kd"), 0.5f, 0.5f, 0.5f);
						glUniform3f(progNormal->getUniform("ks"), 0.5f, 0.5f, 0.5f);
						glUniform1f(progNormal->getUniform("s"), 200.0f);
						prop2->draw(progNormal);
					MV->popMatrix();
				MV->popMatrix();
			MV->popMatrix();
		}
	}
	
	// INTERPOLATED HELICOPTER

	float umax = ncps - 3;
	float u = std::fmod(t, umax);

	float tmax = 7.0f;
	float smax = usTable[25].second;
	float tNorm = std::fmod(t, tmax) / tmax;
	float sNorm = tNorm;

	float s = smax*sNorm;
	float su = s2u(s);

	if (keyToggles[(unsigned)'s']) {
		k = floor(su);
		su = su - k;
	}
	else {
		k = floor(u);
		su = u - k;
	}

	if (ncps >= 4) {
		// Draw spline
		glm::mat4 B = Bcr;
		glm::mat4 Gk;
		glm::mat4 Gq;

		for (int j = 0; j < 4; ++j) {
			Gk[j] = glm::vec4(cps[j + k], 0.0f);
			Gq[j] = glm::vec4(quatb[j + k].x, quatb[j + k].y, quatb[j + k].z, quatb[j + k].w);
		}

		MV->pushMatrix();
			glm::vec4 uVec(1.0f, su, su*su, su*su*su);

			glm::vec4 qVec = Gq * (Bcr * uVec);
			glm::quat q(qVec[3], qVec[0], qVec[1], qVec[2]); // (w, x, y, z)
			glm::mat4 E = glm::toMat4(glm::normalize(q));
			glm::vec3 P(Gk * (B * uVec));
			E[3] = glm::vec4(P, 1.0f);

			camera->helipos = E;

			MV->multMatrix(E);
			glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
			glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
			glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
			glUniform3f(progNormal->getUniform("kd"), 1.0f, 0.0f, 0.0f);
			glUniform3f(progNormal->getUniform("ks"), 1.0f, 0.0f, 0.0f);
			glUniform1f(progNormal->getUniform("s"), 200.0f);
			body1->draw(progNormal);
			glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
			glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
			glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
			glUniform3f(progNormal->getUniform("kd"), 1.0f, 1.0f, 0.0f);
			glUniform3f(progNormal->getUniform("ks"), 1.0f, 1.0f, 0.0f);
			glUniform1f(progNormal->getUniform("s"), 200.0f);
			body2->draw(progNormal);
			MV->pushMatrix();
				MV->translate(glm::vec3(0.0, 0.4819, 0.0));
				MV->rotate(t, glm::vec3(0, 1, 0));
				MV->translate(glm::vec3(0.0, -0.4819, 0.0));
				glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
				glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
				glUniform3f(progNormal->getUniform("kd"), 0.5f, 0.5f, 0.5f);
				glUniform3f(progNormal->getUniform("ks"), 0.5f, 0.5f, 0.5f);
				glUniform1f(progNormal->getUniform("s"), 200.0f);
				prop1->draw(progNormal);
			MV->popMatrix();
			MV->pushMatrix();
				MV->translate(glm::vec3(0.6228, 0.1179, 0.1365));
				MV->rotate(t, glm::vec3(0, 0, 1));
				MV->translate(glm::vec3(-0.6228, -0.1179, -0.1365));
				glUniformMatrix4fv(progNormal->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glUniform3f(progNormal->getUniform("lightPos"), 1.0f, 1.0f, 1.0f);
				glUniform3f(progNormal->getUniform("ka"), 0.5f, 0.5f, 0.5f);
				glUniform3f(progNormal->getUniform("kd"), 0.5f, 0.5f, 0.5f);
				glUniform3f(progNormal->getUniform("ks"), 0.5f, 0.5f, 0.5f);
				glUniform1f(progNormal->getUniform("s"), 200.0f);
				prop2->draw(progNormal);
			MV->popMatrix();
		MV->popMatrix();
	}

	progNormal->unbind();
	
	// Pop stacks
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
