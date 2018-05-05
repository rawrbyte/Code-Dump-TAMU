#include <iostream>
#include "Material.h"

using namespace std;
using namespace glm;

Material::Material(shared_ptr<Shape> sh, vec3 KA, vec3 KD, vec3 KS, vec3 t, vec3 r, vec3 s) {
	obj = sh;
	ka = KA;
	kd = KD;
	ks = KS;
	translate = t;
	rotate = r;
	scale = s;
	angle = (float) (rand() % 360);
}

