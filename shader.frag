#version 150
in vec4 finalColour;
in vec4 centerPosition;

out vec4 out_Colour;

void main(void){
    vec2 resolution = vec2(800.0/2.0, 800.0/2.0);
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    vec2 p = vec2(1.0, 1.0) + centerPosition.xy;
    vec2 uvc = p;

    if (finalColour.w == 0.0) {
        out_Colour = vec4(finalColour.rgb, 0.0);
    }
    else {
        float dist = length(uv - uvc);
        float col = 1.0 - smoothstep(0.0, 0.3, dist);
        out_Colour = vec4(finalColour.rgb * col, 1.0);
    }
}