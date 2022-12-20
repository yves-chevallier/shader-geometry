#version 150
in vec4 finalColour;
in vec4 centerPosition;
out vec4 out_Colour;

uniform float screenWidth;
uniform float radius;

void main(void){
    vec2 resolution = vec2(screenWidth, screenWidth) / 2.0;
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    float dist = length(uv - (centerPosition.xy + 1.0));
    float col = 1.0 - smoothstep(radius*0.7, radius, dist);
    out_Colour = vec4(finalColour.rgb , col * 0.1);
}