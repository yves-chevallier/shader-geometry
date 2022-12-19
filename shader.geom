#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

in float angle[];
out vec4 centerPosition;
out vec4 finalColour;

uniform mat4 projectionViewMatrix;


vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void createVertex(vec3 offset) {
	vec4 actualOffset = vec4(offset, 1.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	gl_Position = worldPosition;
	EmitVertex();
}

void createAngularVertex(float angle, float radius) {
	vec4 worldPosition = gl_in[0].gl_Position;
	gl_Position = worldPosition;
	gl_Position.x += cos(angle) * radius;
	gl_Position.y += sin(angle) * radius;
	EmitVertex();
}

void square(float size, float z) {
	createVertex(vec3(-size, -size, z));
	createVertex(vec3(size, -size, z));
	createVertex(vec3(-size, size, z));
	createVertex(vec3(size, size, z));
	createVertex(vec3(size, -size, z));
	createVertex(vec3(-size, size, z));
	EndPrimitive();
}

void triangle(float angle, float radius) {
	float pi = 3.1415;
	float angleOffset = 0.5;
	createAngularVertex(angle, radius);
	createAngularVertex(angle + pi + angleOffset, radius);
	createAngularVertex(angle + pi - angleOffset, radius);
	EndPrimitive();
}

void main(void) {
    vec3 colour = hsv2rgb(vec3(angle[0], 1.0, 1.0));
    finalColour = vec4(colour, 1.0);
	centerPosition = gl_in[0].gl_Position;
	square(2.0, 0.0);

	finalColour = vec4(0.0, 1.0, 1.0, 0.0);
	triangle(angle[0], 0.1);
}
