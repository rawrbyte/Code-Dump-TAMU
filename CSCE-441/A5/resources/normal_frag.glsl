#version 120

uniform vec3 lightPos;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec3 vNor;
varying vec4 vPos;

void main()
{
	vec3 n = normalize(vNor);
	vec3 ca = ka;
	
	vec3 lightNorm = normalize(lightPos.xyz-vPos.xyz);
	vec3 cd = kd*max(0,dot(lightNorm,n));
	
	vec3 cameraPos = vec3(0,0,0) - normalize(vPos.xyz);
	vec3 cameraNorm= normalize(cameraPos);
	vec3 hVec = cameraNorm+lightNorm;
	vec3 hNorm = normalize(hVec);
	
	vec3 cs = ks*pow(max(0,dot(hNorm,vNor)),s);
	
	vec3 c = (ca + cd + cs)*0.8;
	gl_FragColor = vec4(c, 1.0);
}
