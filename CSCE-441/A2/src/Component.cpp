#include <iostream>
#include "Component.h"

using namespace std;
using namespace glm;

#define FACTOR 10
#define PI 3.1415926

vec3 xA(1, 0, 0);
vec3 yA(0, 1, 0);
vec3 zA(0, 0, 1);

void Draw(MatrixStack &mv, MatrixStack &p, shared_ptr<Program> prog, shared_ptr<Shape> shape) {
	prog->bind();
	glUniformMatrix4fv(prog->getUniform("P"), 1, GL_FALSE, &p.topMatrix()[0][0]);
	glUniformMatrix4fv(prog->getUniform("MV"), 1, GL_FALSE, &mv.topMatrix()[0][0]);
	shape->draw(prog);
	prog->unbind();
}

Component::Component(vec3 transJ, vec3 angleJ, vec3 tmeshJ, vec3 scaleF, float Ang, int bodypart) {
	tJoint = transJ;
	aJoint = angleJ;
	tmJoint = tmeshJ;
	sFactor = scaleF;
	angle = Ang;
	body = bodypart;
};

void Component::setChild(Component child) {
	children.push_back(child);
}
void Component::setParent(Component parent) {
	Parent.push_back(parent);
}

void Component::DrawComponent(MatrixStack &mv, MatrixStack &p, shared_ptr<Program> prog, shared_ptr<Shape> shape, int pos, bool x, bool X, bool y, bool Y, bool z, bool Z){
	if (x == true) {
		if (pos == body) {
			aJoint.x = aJoint.x - FACTOR;
		}
	}
	else if (X == true) {
		if (pos == body) {
			aJoint.x = aJoint.x + FACTOR;
		}
	}
	else if (y == true) {
		if (pos == body) {
			aJoint.y = aJoint.y - FACTOR;
		}
	}
	else if (Y == true) {
		if (pos == body) {
			aJoint.y = aJoint.y + FACTOR;
		}
	}
	else if (z == true) {
		if (pos == body) {
			aJoint.z = aJoint.z - FACTOR;
		}
	}
	else if (Z == true) {
		if (pos == body) {
			aJoint.z = aJoint.z + FACTOR;
		}
	}

	mv.pushMatrix();
	mv.translate(tJoint);
	mv.rotate(aJoint.x*((float)(PI / 180)), xA);
	mv.rotate(aJoint.y*((float)(PI / 180)), yA);
	mv.rotate(aJoint.z*((float)(PI / 180)), zA);
	mv.pushMatrix();
	mv.translate(tmJoint);
	mv.scale(sFactor);

	if (pos == body) {
		vec3 sizeup(1.05, 1.05, 1);
		mv.scale(sizeup);
	}

	Draw(mv, p, prog, shape);
	mv.popMatrix();

	for (size_t i = 0; i < children.size(); i++) {
		children[i].DrawComponent(mv, p, prog, shape, pos, x, X, y, Y, z, Z);
	}

	mv.popMatrix();
}
