#include <iostream>
#include "Light.h"

#define factor 0.5

using namespace std;
using namespace glm;

Light::Light(vec3 L, int lv) {
	l = L;
	value = lv;
}

void Light::updateLight(int lv, bool x, bool y, bool X, bool Y) {
	if (lv == value) {
		if (x == true) {
			l.x = l.x - factor;
		}
		else if (y == true) {
			l.y = l.y - factor;
		}
		else if (X == true) {
			l.x = l.x + factor;
		}
		else if (Y == true) {
			l.y = l.y + factor;
		}
	}
}