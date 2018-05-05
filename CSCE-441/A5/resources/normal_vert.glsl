#version 120

attribute vec4 aPos;
attribute vec3 aNor;
uniform mat4 P;
uniform mat4 MV;
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
