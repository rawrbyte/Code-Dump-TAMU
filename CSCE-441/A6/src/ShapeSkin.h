#pragma once
#ifndef _SHAPESKIN_H_
#define _SHAPESKIN_H_

#include <memory>
#include <vector>
#include "Cheb.h"

class MatrixStack;
class Program;

class ShapeSkin
{
public:
	ShapeSkin();
	virtual ~ShapeSkin();
	void loadMesh(const std::string &meshName);
	void loadAttachment(const std::string &filename);
	void setProgram(std::shared_ptr<Program> p) { prog = p; }
	void init();
	void draw() const;
	Cheb* cheB = new Cheb();
	int framee;
	
private:
	std::shared_ptr<Program> prog;
	std::vector<unsigned int> elemBuf;
	std::vector<float> posBuf;
	std::vector<float> norBuf;
	std::vector<float> texBuf;
	std::vector<float> atrBuf;
	std::vector<float> pBuf;
	std::vector<float> nBuf;
	unsigned elemBufID;
	unsigned posBufID;
	unsigned norBufID;
	unsigned texBufID;
	unsigned pBufID;
	unsigned nBufID;
};

#endif
