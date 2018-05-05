#version 120

uniform vec3 lightPos;
uniform vec3 lightPos2;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec3 vNor;
varying vec4 vPos;

void main()
{
	vec3 n = normalize(vNor);
	vec3 ca1 = ka;
	vec3 ca2 = ka;
	
	vec3 lightNorm = normalize(lightPos-vPos.xyz);
	vec3 lightNorm2 = normalize(lightPos2-vPos.xyz);
	vec3 cd1 = kd*max(0,dot(lightNorm,n));
	vec3 cd2 = kd*max(0,dot(lightNorm2, n));
	
	vec3 cameraPos = vec3(0,0,0) - normalize(vPos.xyz);
	vec3 cameraNorm= normalize(cameraPos);
	vec3 hVec = cameraNorm+lightNorm;
	vec3 hVec2 = cameraNorm+lightNorm2;
	vec3 hNorm = normalize(hVec);
	vec3 hNorm2 = normalize(hVec2);
	
	vec3 cs1 = ks*pow(max(0,dot(hNorm,vNor)),s);
	vec3 cs2 = ks*pow(max(0,dot(hNorm2,vNor)),s);
	
	vec3 c1 = (ca1+ cd1 + cs1)*0.8;
	vec3 c2 = (ca2 + cd2 + cs2)*0.2;
	vec3 c = c1 + c2;
	gl_FragColor = vec4(c, 1.0);
}