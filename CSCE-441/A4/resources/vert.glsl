#version 120

uniform mat4 P;
uniform mat4 MV;
uniform mat4 L;
uniform mat3 T1;

attribute vec2 aTex;
attribute vec4 aPos;
attribute vec3 aNor;

varying vec2 vTex0;
varying vec3 vNor;
varying vec4 vPos;
varying vec4 light;

void main()
{
	gl_Position = P * MV * aPos;
	vec4 tmp = vec4(aNor,0);
	vec4 tmp2 = MV*tmp;
	vNor = tmp2.xyz;
	
	vTex0 = aTex;

	vPos = MV*aPos;
	light = L*vec4(10,5,-5,1);
}
