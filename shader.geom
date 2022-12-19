#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 6) out;

in vec3 pass_colour[];
in float angle[];

out vec3 finalColour;
out vec4 center;

uniform mat4 projectionViewMatrix;
//uniform vec3 boidColour;

const float size = 0.1;
void createVertex(vec3 offset, vec3 colour, float z = 0.0) {
	vec4 actualOffset = vec4(offset, z);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	//gl_Position = projectionViewMatrix * worldPosition;
	gl_Position = worldPosition;
	finalColour = colour;
	vec4 pointPosition = gl_in[0].gl_Position;
	center = pointPosition;
	EmitVertex();
}

// const float PI = 3.141592;
// const float wings = 0.4;
void main(void) {
	vec4 boidColour = vec4(0.5, 0.5, 0.0, 1.0);

	float corner = 0.3;
	createVertex(vec3(-corner, -corner, 0.0), vec3(angle[0], 0.0, 1.0), 0.0);
	createVertex(vec3(corner, -corner, 0.0), vec3(angle[0], 0.0, 1.0),0.0);
	createVertex(vec3(-corner, corner, 0.0), vec3(angle[0], 0.0, 1.0),0.0);

	createVertex(vec3(corner, corner, 0.0), vec3(angle[0], 0.0, 1.0),0.0);
	createVertex(vec3(corner, -corner, 0.0), vec3(angle[0], 0.0, 1.0), 0.0);
	createVertex(vec3(-corner, corner, 0.0), vec3(angle[0], 0.0, 1.0), 0.0);

	EndPrimitive();

	// center = vec4(gl_in[0].gl_Position.xyz, 1.0);
	// createVertex(vec3(cos(angle[0])*size, sin(angle[0])*size, 0.0), boidColour.rgb, 0.0);
    // createVertex(vec3(cos(angle[0] + PI - wings)*size, sin(angle[0] + PI - wings)*size, 0.0), boidColour.rgb, 0.0);
    // createVertex(vec3(cos(angle[0] + PI + wings)*size, sin(angle[0] + PI + wings)*size, 0.0), boidColour.rgb, 0.0);
	// EndPrimitive();
}
