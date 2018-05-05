#include <iostream>
#include "Cheb.h"
#include <fstream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLSL.h"
#include "MatrixStack.h"

using namespace std;
using namespace glm;

Cheb::Cheb() {
		for (int i = 0; i < 18; ++i) {
			Bone* bone = new Bone();
			chebby.push_back(bone);
		}
}

vector<Bone*> Cheb::getChebby() {
	return chebby;
}

void Cheb::loadSkeleton(const std::string &filename)
{
	int nframes, nbones;
	float qx, qy, qz, qw, px, py, pz;
	ifstream in;
	in.open(filename);
	if (!in.good()) {
		cout << "Cannot read " << filename << endl;
		return;
	}
	string line;
	getline(in, line); // comment
	getline(in, line); // comment
	getline(in, line); // comment
	getline(in, line);
	stringstream ss0(line);
	ss0 >> nframes;
	ss0 >> nbones;
	getline(in, line); // bindPos
	stringstream ss1(line);
	for (int i = 0; i < 18; ++i) {
		ss1 >> qx >> qy >> qz >> qw >> px >> py >> pz;
		glm::quat q(qw, qx, qy, qz);
		glm::vec3 p(px, py, pz);
		chebby[i]->bindQ = q;
		chebby[i]->bindP = p;
		glm::mat4 EE = mat4_cast(q);
		EE[3] = vec4(p, 1.0f);
		chebby[i]->bindE = EE;
		chebby[i]->inverseE = glm::inverse(EE);
	}
	while (1) {
		getline(in, line);
		if (in.eof()) {
			break;
		}
		// Parse line
		stringstream ss(line);
		for (int i = 0; i < 18; ++i) {
			ss >> qx >> qy >> qz >> qw >> px >> py >> pz;
			glm::quat q(qw, qx, qy, qz);
			glm::vec3 p(px, py, pz);
			chebby[i]->Q.push_back(q);
			chebby[i]->P.push_back(p);
			glm::mat4 EE = mat4_cast(q);
			EE[3] = vec4(p, 1.0f);
			chebby[i]->E.push_back(EE);
		}

	}
	in.close();
}