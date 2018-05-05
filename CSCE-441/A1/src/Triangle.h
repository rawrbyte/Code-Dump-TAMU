#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <string>
#include <vector>

class Triangle
{
public:
	float xmax, xmin, ymax, ymin, scale, tX, tY, xIMax, xIMin, yIMax, yIMin;
	unsigned char r1, g1, b1, r2, g2, b2, r3, g3, b3;
	float z1, z2, z3;

	Triangle(std::vector<float> vert, float s, float tx, float ty);

	float xMax(std::vector<float> vert);
	float yMax(std::vector<float> vert);
	float xMin(std::vector<float> vert);
	float yMin(std::vector<float> vert);
	std::vector<float> transform(std::vector<float> vert, float s, float tX, float tY);
	float getIVert(int x) { return Iverticies[x]; }

private:
	std::vector<float> verticies;
	std::vector<float> Iverticies;
	
};

#endif
