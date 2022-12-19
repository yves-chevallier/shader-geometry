#version 150
in vec4 finalColour;
in vec4 centerPosition;
in float radius;
out vec4 out_Colour;

uniform float screenWidth;
void main(void){
    // out_Colour = vec4(1.0, 1.0, 0.0, 0.0);

    // if (finalColour.w == 0.0) {
    //     out_Colour = vec4(finalColour.rgb, 1.0);
    //     return;
    // }

    vec2 resolution = vec2(screenWidth/2.0, screenWidth/2.0);
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 p = vec2(1.0, 1.0) + centerPosition.xy;
    vec2 uvc = p;
    float dist = length(uv - uvc);
    float col = 1.0 - smoothstep(radius/10, radius/5, dist);
    //float col = dist;
    out_Colour = vec4(finalColour.rgb , col * 0.1);

}