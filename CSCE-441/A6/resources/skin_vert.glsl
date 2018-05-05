#version 120

attribute vec4 aPos;
attribute vec3 aNor;

uniform mat4 P;
uniform mat4 MV;

varying vec3 vColor;

void main()
{
	gl_Position = P * (MV * aPos);
	vColor = 0.5*aNor + 0.5;
}
