#version 120

uniform sampler2D texture0;
varying vec2 vTex0;

void main()
{
	vec4 color0 = texture2D(texture0, vTex0);
	gl_FragColor = color0;
}
