#include <iostream>
#include "triangle.h"

using namespace std;

Triangle::Triangle(vector<float> vert, float s, float tx, float ty){
	verticies = vert;
	scale = s;
	xmax = xMax(vert);
	xmin = xMin(vert);
	ymax = yMax(vert);
	ymin = yMin(vert);
	tX = tx;
	tY = ty;
	xIMax = xmax*scale + tX;
	xIMin = xmin*scale + tX;
	yIMax = ymax*scale + tY;
	yIMin = ymin*scale + tY;
	Iverticies = transform(verticies, scale, tX, tY);
	z1 = vert[2];
	z2 = vert[5];
	z3 = vert[8];
	r1 = rand() % 255;
	g1 = rand() % 255;
	b1 = rand() % 255;
	r2 = rand() % 255;
	g2 = rand() % 255;
	b2 = rand() % 255;
	r3 = rand() % 255;
	g3 = rand() % 255;
	b3 = rand() % 255;
}

float Triangle::xMax(vector<float> vert) {
	float x = vert[0];
	for (size_t i = 0; i < vert.size(); i += 3) {
		if (vert[i] > x) { x = vert[i]; }
	}
	return x;
}

float Triangle::yMax(vector<float> vert) {
	float y = vert[1];
	for (size_t i = 0; i < vert.size(); i += 3) {
		if (vert[i+1] > y) { y = vert[i+1]; }
	}
	return y;
}

float Triangle::xMin(vector<float> vert) {
	float x = vert[0];
	for (size_t i = 0; i < vert.size(); i += 3) {
		if (vert[i] < x) { x = vert[i]; }
	}
	return x;
}

float Triangle::yMin(vector<float> vert) {
	float y = vert[1];
	for (size_t i = 0; i < vert.size(); i += 3) {
		if (vert[i+1] < y) { y = vert[i+1]; }
	}
	return y;
}

vector<float> Triangle::transform(vector<float> vert, float s, float tX, float tY) {
	vector<float> transformed;
	for (size_t i = 0; i < vert.size(); i+=3) {
		transformed.push_back(vert[i] * s + tX);
		transformed.push_back(vert[i+1] * s + tY);
		transformed.push_back(vert[i+2]);
	}
	return transformed;
}

