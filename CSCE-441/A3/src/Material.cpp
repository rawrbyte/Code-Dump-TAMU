#include <iostream>
#include "Material.h"

using namespace std;
using namespace glm;

Material::Material(vec3 KA, vec3 KD, vec3 KS, int Mode) {
	ka = KA;
	kd = KD;
	ks = KS;
	mode = Mode;
}

