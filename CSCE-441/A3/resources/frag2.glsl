#version 120


varying vec3 vNor;
varying vec4 vPos;

void main()
{	
	vec3 n = normalize(vNor);
	vec3 c = vec3(1.0,1.0,1.0);
	vec3 vPosNorm = normalize(vPos.xyz);
	
	float rightAngle = dot(n, vPosNorm);
	if(rightAngle <= 0.3 && rightAngle >= -0.3){
		c = vec3(0,0,0);
	}
	gl_FragColor = vec4(c, 1.0);
}