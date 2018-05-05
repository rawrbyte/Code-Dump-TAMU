#version 120

attribute vec4 aPos;
attribute vec3 aNor;
uniform mat4 P;
uniform mat4 MV;
varying vec3 vCol;

void main()
{
	gl_Position = P * MV * aPos;
	vCol = 0.5*(aNor + 1.0);
}
