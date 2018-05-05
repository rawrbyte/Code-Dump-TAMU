#include <iostream>
#include <fstream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "ShapeSkin.h"
#include "GLSL.h"
#include "Program.h"
#include "Vertex.h"

using namespace std;

vector<Vertex*> stage2;

ShapeSkin::ShapeSkin() :
	prog(NULL),
	elemBufID(0),
	posBufID(0),
	norBufID(0),
	texBufID(0)
{}

ShapeSkin::~ShapeSkin()
{
}

void ShapeSkin::loadMesh(const string &meshName)
{
	// Load geometry
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		posBuf = attrib.vertices;
		norBuf = attrib.normals;
		nBuf = attrib.normals;
		texBuf = attrib.texcoords;
		assert(posBuf.size() == norBuf.size());
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			const tinyobj::mesh_t &mesh = shapes[s].mesh;
			size_t index_offset = 0;
			for(size_t f = 0; f < mesh.num_face_vertices.size(); f++) {
				size_t fv = mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = mesh.indices[index_offset + v];
					elemBuf.push_back(idx.vertex_index);
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}
}

void ShapeSkin::loadAttachment(const std::string &filename)
{
	int nverts, nbones;
	ifstream in;
	in.open(filename);
	if(!in.good()) {
		cout << "Cannot read " << filename << endl;
		return;
	}
	string line;
	getline(in, line); // comment
	getline(in, line); // comment
	getline(in, line);
	stringstream ss0(line);
	ss0 >> nverts;
	ss0 >> nbones;
	int nvertw = nverts * 18;
	float value;
	assert(nverts == posBuf.size()/3);
	while(1) {
		int setPos = 0;
		getline(in, line);
		if(in.eof()) {
			break;
		}
		// Parse line
		stringstream ss(line);
		Vertex* vertex = new Vertex();
		for (int i = 0; i < 18; ++i) {
			ss >> value;
			atrBuf.push_back(value);
			if (value > 0.0f) {
				vertex->W[setPos] = value;
				vertex->I[setPos] = i;
				setPos++;
			}
		}
		stage2.push_back(vertex);
	}
	assert(atrBuf.size() == nvertw);
	in.close();
}


void ShapeSkin::init()
{
	// Send the position array to the GPU
	glGenBuffers(1, &posBufID);
	glBindBuffer(GL_ARRAY_BUFFER, posBufID);
	glBufferData(GL_ARRAY_BUFFER, posBuf.size()*sizeof(float), &posBuf[0], GL_STATIC_DRAW);
	
	// Send the normal array to the GPU
	glGenBuffers(1, &norBufID);
	glBindBuffer(GL_ARRAY_BUFFER, norBufID);
	glBufferData(GL_ARRAY_BUFFER, norBuf.size()*sizeof(float), &norBuf[0], GL_STATIC_DRAW);


	// No texture info
	texBufID = 0;
	
	// Send the element array to the GPU
	glGenBuffers(1, &elemBufID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBufID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elemBuf.size()*sizeof(unsigned int), &elemBuf[0], GL_STATIC_DRAW);
	
	// Unbind the arrays
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	assert(glGetError() == GL_NO_ERROR);
}

void ShapeSkin::draw() const
{
	assert(prog);
	vector<float> pBuf = posBuf;
	vector<float> nBuf = norBuf;
	int nverts = atrBuf.size() / 18;
	for (int i = 0; i < nverts; ++i) {
		glm::vec4 pos(0, 0, 0, 1);
		glm::vec4 nor(0, 0, 0, 0);
		glm::vec4 tpos = glm::vec4(posBuf[i * 3], posBuf[(i * 3) + 1], posBuf[(i * 3) + 2], 1.0f);
		glm::vec4 tnor = glm::vec4(norBuf[i * 3], norBuf[(i * 3) + 1], norBuf[(i * 3) + 2], 0.0f);
		int position = 0;

		// STAGE 2 Subset Skinning
		while (stage2[i]->W[position] > 0) {
			float weight = stage2[i]->W[position];
			int index = stage2[i]->I[position];
			pos += (weight * cheB->getChebby()[index]->E[framee] * cheB->getChebby()[index]->inverseE * tpos);
			nor += (weight * cheB->getChebby()[index]->E[framee] * cheB->getChebby()[index]->inverseE * tnor);
			position++;
		}

		/*
		// STAGE 1 Skinning
		for (int j = 0; j < cheB->getChebby().size(); ++j) {
			pos += (atrBuf[(i * 18) + j] * cheB->getChebby()[j]->E[framee] * cheB->getChebby()[j]->inverseE * tpos);
			nor += (atrBuf[(i * 18) + j] * cheB->getChebby()[j]->E[framee] * cheB->getChebby()[j]->inverseE * tnor);
		}
		*/

		pBuf[i * 3] = pos.x;
		pBuf[(i * 3) + 1] = pos.y;
		pBuf[(i * 3) + 2] = pos.z;
		nBuf[i * 3] = nor.x;
		nBuf[(i * 3) + 1] = nor.y;
		nBuf[(i * 3) + 2] = nor.z;
		
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, posBufID);
	glBufferData(GL_ARRAY_BUFFER, pBuf.size() * sizeof(float), &pBuf[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, norBufID);
	glBufferData(GL_ARRAY_BUFFER, nBuf.size() * sizeof(float), &nBuf[0], GL_DYNAMIC_DRAW);

	int h_pos = prog->getAttribute("aPos");
	glEnableVertexAttribArray(h_pos);
	glBindBuffer(GL_ARRAY_BUFFER, posBufID);
	glVertexAttribPointer(h_pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
	
	int h_nor = prog->getAttribute("aNor");
	glEnableVertexAttribArray(h_nor);
	glBindBuffer(GL_ARRAY_BUFFER, norBufID);
	glVertexAttribPointer(h_nor, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
	
	// Draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elemBufID);
	glDrawElements(GL_TRIANGLES, (int)elemBuf.size(), GL_UNSIGNED_INT, (const void *)0);
	
	glDisableVertexAttribArray(h_nor);
	glDisableVertexAttribArray(h_pos);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



