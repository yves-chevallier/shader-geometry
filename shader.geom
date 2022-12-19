#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in float angle[];

out vec4 finalColour;

uniform mat4 projectionViewMatrix;

void createVertex(vec3 offset) {
	vec4 actualOffset = vec4(offset, 1.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	gl_Position = worldPosition;
	EmitVertex();
}

void createAngularVertex(vec3 offset, float angle, float radius) {
	vec4 actualOffset = vec4(offset, 1.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
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

void triangle(vec3 offset, float angle, float radius) {
	float pi = 3.1415;
	float angleOffset = 0.5;
	createAngularVertex(offset, angle, radius);
	createAngularVertex(offset, angle + pi + angleOffset, radius);
	createAngularVertex(offset, angle + pi - angleOffset, radius);
	EndPrimitive();
}

void main(void) {
	finalColour = vec4(1.0, 0.5, 0.5, 1.0);
	square(1.0, 0.0);

	finalColour = vec4(0.0, 1.0, 1.0, 0.0);
	triangle(vec3(0.0, 0.0, 0.0), angle[0], 1.0);
	EndPrimitive();
}
