#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 pass_colour[];
in float angle[];
out vec4 finalColour;
out vec4 centerPosition;

uniform mat4 projectionViewMatrix;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void createVertex(vec3 offset, float z = 0.0) {
	vec4 actualOffset = vec4(offset, z);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	gl_Position = worldPosition;
	gl_Position.z = z;
	EmitVertex();
}

void main(void) {
	vec3 boidColour = vec3(1.0, 1.0, 1.0);
	centerPosition = gl_in[0].gl_Position;
	float corner = 0.1;
	vec3 colour = hsv2rgb(vec3(angle[0], 1.0, 1.0));
	finalColour = vec4(colour, 1.0);
	float z = 0.0;
	createVertex(vec3(-corner, -corner, 0.0), z);
	createVertex(vec3(corner, -corner, 0.0), z);
	createVertex(vec3(-corner, corner, 0.0), z);
	createVertex(vec3(corner, corner, 0.0), z);
	createVertex(vec3(corner, -corner, 0.0), z);
	createVertex(vec3(-corner, corner, 0.0), z);

	EndPrimitive();

	float radius = 0.05;
	float pi = 3.1415;
	float angleOffset = 0.5;
	finalColour = vec4(boidColour, 0.0);
	createVertex(vec3(cos(angle[0]) * radius, sin(angle[0]) * radius, 0.0), 0.1);
	createVertex(vec3(cos(angle[0] - pi + angleOffset) * radius, sin(angle[0] - pi + angleOffset) * radius, 0.0), 0.0);
	createVertex(vec3(cos(angle[0] - pi - angleOffset) * radius, sin(angle[0] - pi - angleOffset) * radius, 0.0), 0.0);
	EndPrimitive();
}
