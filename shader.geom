#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 7) out;

in vec3 pass_colour[];
in float angle[];

out vec3 finalColour;
out vec4 center;

uniform mat4 projectionViewMatrix;
uniform vec4 boid_colour;

const float size = 0.1;
void createVertex(vec3 offset, vec3 colour, float z = 0.0) {
	vec4 actualOffset = vec4(offset, z);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	//gl_Position = projectionViewMatrix * worldPosition;
	gl_Position = worldPosition;
	finalColour = colour;
	EmitVertex();
}

const float PI = 3.1415926535897932384626433832795;
const float wings = 0.4;
void main(void) {

	// center = vec4(gl_in[0].gl_Position.xyz, 0.0);
	// float corner = 0.5;
	// createVertex(vec3(-corner, -corner, 0.0), vec3(1.0, 1.0, 1.0), -1.0);
	// createVertex(vec3(corner, -corner, 0.0), vec3(1.0, 1.0, 1.0),-1.0);
	// createVertex(vec3(-corner, corner, 0.0), vec3(1.0, 1.0, 1.0),-1.0);

	// createVertex(vec3(corner, corner, 0.0), vec3(1.0, 1.0, 1.0),-1.0);
	// createVertex(vec3(corner, -corner, 0.0), vec3(1.0, 1.0, 1.0), -1.0);
	// createVertex(vec3(-corner, corner, 0.0), vec3(1.0, 1.0, 1.0), -1.0);

	// EndPrimitive();

	center = vec4(gl_in[0].gl_Position.xyz, 1.0);
	createVertex(vec3(cos(angle[0])*size, sin(angle[0])*size, 0.0), boid_colour.rgb, 0.0);
    createVertex(vec3(cos(angle[0] + PI - wings)*size, sin(angle[0] + PI - wings)*size, 0.0), boid_colour.rgb, 0.0);
    createVertex(vec3(cos(angle[0] + PI + wings)*size, sin(angle[0] + PI + wings)*size, 0.0), boid_colour.rgb, 0.0);
	EndPrimitive();


}
