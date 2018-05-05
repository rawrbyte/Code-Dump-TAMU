#include <iostream>
#include <string>
#include <memory>
#include <ctime>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Image.h"
#include "Triangle.h"

using namespace std;

void meshMax(vector<float> &posBuf, float &x, float &y, float &z) {
	x = posBuf[0];
	y = posBuf[1];
	z = posBuf[2];
	for (size_t i = 0; i < posBuf.size(); i += 3) {
		if (posBuf[i] > x) { x = posBuf[i]; }
		if (posBuf[i + 1] > y) { y = posBuf[i + 1]; }
		if (posBuf[i + 2] > z) { z = posBuf[i + 2]; }
	}
}

void meshMin(vector<float> &posBuf, float &x, float &y, float &z) {
	x = posBuf[0];
	y = posBuf[1];
	z = posBuf[2];
	for (size_t i = 0; i < posBuf.size(); i += 3) {
		if (posBuf[i] < x) { x = posBuf[i]; }
		if (posBuf[i + 1] < y) { y = posBuf[i + 1]; }
		if (posBuf[i + 2] < z) { z = posBuf[i + 2]; }
	}
}

void meshScale(float xmax, float xmin, float ymax, float ymin, float &scale, int height, int width) {
	float xscale = (float) width / (xmax - xmin);
	float yscale = (float) height / (ymax - ymin);

	if (xscale < yscale) {
		scale = xscale;
	}
	else {
		scale = yscale;
	}
}

float area(float x1, float y1, float x2, float y2, float x3, float y3) {
	return (float) ((0.5)*((x1 - x3)*(y2 - y3) + (x3 - x2)*(y1 - y3)));
}

void Barycentric2(float px, float py, float x1, float y1, float x2, float y2, float x3, float y3, float &u, float &v, float &w, bool &check) {
	float totalarea = area(x1, y1, x2, y2, x3, y3);
	float areaOfA = area(px, py, x2, y2, x3, y3);
	float areaOfB = area(px, py, x3, y3, x1, y1);
	float areaOfC = area(px, py, x1, y1, x2, y2);
	u = areaOfA / totalarea;
	v = areaOfB / totalarea;
	w = areaOfC / totalarea;

	if (((u >= 0) && (v >= 0) && (w >= 0))) { check = true; }
	else { check = false; }
}

//http://stackoverflow.com/questions/19372145/checking-if-argvi-is-a-valid-integer-passing-arguments-in-main
bool legal_int(char *str) {
	while (*str)
		if (!isdigit(*str++))
			return false;
	return true;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}

	cout << "Command Line Argument Example: \n> ./A1 bunny.obj output.png 700 700 1\n\n";

	string meshName(argv[1]);
	string fileName(argv[2]);
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);
	int mode = atoi(argv[5]);
	int input = -1;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());

	while (!rc) {
		cout << "[" << meshName << "] Does Not Exist. Input An Existing File.\n OBJ File: ";
		cin >> meshName;
		rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	}

	if (legal_int(argv[3]) == false) {
		do {
			input = -1;
			cout << "Invalid value. Input A Postive Integer.\n Width: ";
			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (input > 0) {
				width = input;
			}
		} while (input < 0);
	}

	if (legal_int(argv[4]) == false) {
		do {
			input = -1;
			cout << "Invalid value. Input A Postive Integer.\n Height: ";
			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (input > 0) {
				height = input;
			}
		} while (input < 0);
	}

	if (legal_int(argv[5]) == true) {
		while (mode < 0 || mode > 2) {
			input = -1;
			cout << "Invalid value. Input A Postive Integer Between 0 - 2.\n Mode: ";
			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (input >= 0 && input <= 2) {
				mode = input;
			}
		}
	}

	if (legal_int(argv[5]) == false){
		do {
			input = -1;
			cout << "Invalid value. Input A Postive Integer Between 0 - 2.\n Mode: ";
			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (input >= 0 && input <= 2) {
				mode = input;
			}
		} while (input < 0 || input > 2);
	}

	cout << "\nLoaded:\t[" << meshName << "]" << endl;
	cout << "Output:\t[" << fileName << "]" << endl;
	cout << " Width:\t[" << width << "]" << endl;
	cout << "Height:\t[" << height << "]" << endl;
	cout << "  Mode:\t[" << mode << "]\n\n";

	srand((unsigned int) time(NULL));

	float xmax{ 0.0 }, ymax{ 0.0 }, xmin{ 0.0 }, ymin{ 0.0 }, zmax{ 0.0 }, zmin{ 0.0 }, scale{ 0.0 };
	vector<Triangle> triangles;
	auto image = make_shared<Image>(width, height);
	vector<float> posBuf;

	if(rc) {
		for (size_t s = 0; s < shapes.size(); s++) {
			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				for (size_t v = 0; v < fv; v++) {
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 0]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 1]);
					posBuf.push_back(attrib.vertices[3 * idx.vertex_index + 2]);
				}
				index_offset += fv;
				shapes[s].mesh.material_ids[f];
			}
		}
	}

	meshMax(posBuf, xmax, ymax, zmax);
	meshMin(posBuf, xmin, ymin, zmin);
	meshScale(xmax, xmin, ymax, ymin, scale, height, width);

	float tx = (float) ((0.5)*width - scale*((0.5)*(xmin + xmax)));
	float ty = (float) ((0.5)*height - scale*((0.5)*(ymin + ymax)));

	for (size_t j = 0; j < posBuf.size(); j += 9) {
		vector<float> vert;
		for (int k = 0; k < 9; k++) {
			vert.push_back(posBuf[j + k]);
		}
		Triangle tri(vert, scale, tx, ty);
		triangles.push_back(tri);
	}

	float u{ 0.0 }, v{ 0.0 }, w{ 0.0 };
	if (mode == 0) {
		bool check = false;
		for (size_t d = 0; d < triangles.size(); ++d) {
			for (int y = (int) triangles[d].yIMin; y < triangles[d].yIMax; ++y) {
				for (int x = (int) triangles[d].xIMin; x < triangles[d].xIMax; ++x) {
					Barycentric2( (float) x, (float) y, triangles[d].getIVert(0), triangles[d].getIVert(1), triangles[d].getIVert(3),
						triangles[d].getIVert(4), triangles[d].getIVert(6), triangles[d].getIVert(7), u, v, w, check);
					if (check == true) {
						unsigned char r = (unsigned char) (triangles[d].r1*u + triangles[d].r2*v + triangles[d].r3*w);
						unsigned char g = (unsigned char) (triangles[d].g1*u + triangles[d].g2*v + triangles[d].g3*w);
						unsigned char b = (unsigned char) (triangles[d].b1*u + triangles[d].b2*v + triangles[d].b3*w);
						image->setPixel(x, y, r, g, b);
					}
				}
			}
		}
	}

	if (mode == 1) {
		vector<vector<float>> zbuffer;
		for (int k = 0; k < width; ++k) {
			vector<float> row;
			for (int l = 0; l < height; l++) {
				row.push_back(-99999.0);
			}
			zbuffer.push_back(row);
		}
		bool check = false;
		float zscale = 255 / ((zmax - zmin));

		for (size_t d = 0; d < triangles.size(); ++d) {
			for (int y = (int) triangles[d].yIMin; y < triangles[d].yIMax; ++y) {
				for (int x = (int) triangles[d].xIMin; x < triangles[d].xIMax; ++x) {
					Barycentric2( (float) x, (float) y, triangles[d].getIVert(0), triangles[d].getIVert(1), triangles[d].getIVert(3),
						triangles[d].getIVert(4), triangles[d].getIVert(6), triangles[d].getIVert(7), u, v, w, check);
					if (check) {
						float zvalue = triangles[d].z1*u + triangles[d].z2*v + triangles[d].z3*w;
						if (zvalue > zbuffer[x][y]) {
							zbuffer[x][y] = zvalue;
							unsigned char r = (unsigned char) ((zvalue - zmin)*zscale);
							unsigned char g = 0;
							unsigned char b = 0;
							image->setPixel(x, y, r, g, b);
						}
					}
				}
			}
		}
	}

	if (mode == 2) {
		bool check = false;
		unsigned char r1 = 255, g1 = 0, b1 = 0;
		unsigned char r2 = 0, g2 = 255, b2 = 255;
		float yminS = ymin*scale + ty;
		float ymaxS = ymax*scale + ty;

		for (size_t d = 0; d < triangles.size(); ++d) {
			for (int y = (int) triangles[d].yIMin; y < triangles[d].yIMax; ++y) {
				for (int x = (int) triangles[d].xIMin; x < triangles[d].xIMax; ++x) {
					Barycentric2((float) x, (float) y, triangles[d].getIVert(0), triangles[d].getIVert(1), triangles[d].getIVert(3),
						triangles[d].getIVert(4), triangles[d].getIVert(6), triangles[d].getIVert(7), u, v, w, check);
					if (check == true) {
						float yscale = (( float) y - (yminS)) / ((ymaxS) - (yminS));
						unsigned char r = (unsigned char) ((1 - yscale)*r1 + yscale*r2);
						unsigned char g = (unsigned char) ((1 - yscale)*g1 + yscale*g2);
						unsigned char b = (unsigned char) ((1 - yscale)*b1 + yscale*b2);
						image->setPixel(x, y, r, g, b);
					}
				}
			}
		}
	}

	image->writeToFile(fileName);
	return 0;
}
