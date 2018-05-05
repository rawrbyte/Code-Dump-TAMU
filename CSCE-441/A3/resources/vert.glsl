#version 120

uniform mat4 P;
uniform mat4 MV;

attribute vec2 aTex;
attribute vec4 aPos; // in object space
attribute vec3 aNor; // in object space

varying vec3 vNor;
varying vec4 vPos;

void main()
{
	gl_Position = P * MV * aPos;
	vec4 tmp = vec4(aNor,0);
	vec4 tmp2 = MV*tmp;
	vNor = tmp2.xyz;
	
	vPos = MV*aPos;
}
