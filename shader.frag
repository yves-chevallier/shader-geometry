#version 140
in vec3 finalColour;
out vec4 out_Colour;
in vec4 center;

void main(void){
    out_Colour = vec4(1.0, 0.0,0.0, 0.8);
    // if (center.w > 0.0){
    //     out_Colour = vec4(finalColour, 0.8);
    // }
    // else {
    //     vec2 resolution = vec2(800.0, 800.0);
    //     vec2 uv = gl_FragCoord.xy / resolution.xy;
    //     uv.x -= 0.5;
    //     uv.y -= 0.5;
    //     // float dist = distance(uv, center.xy);
    //     // //float dist = distance(vec2(0.0, 0.0), gl_FragCoord.xy);
    //     // //dist = dist ;
    //     // //float dist = center.x/800.0 + gl_FragCoord.x/800.0;
    //     // if (dist < 0){
    //     //     dist = 0.0;
    //     // }

    //     float distance = length(uv);
    //     if (distance > 0.2) {
    //         out_Colour = vec4(0.0, 0.0, 0.0, 0.0);
    //     }
    //     else {
    //         out_Colour = vec4(1.0, 1.0, 1.0, 1.0);
    //     }
    //     //out_Colour.r = length(uv);
	//     //out_Colour = vec4(dist, 0.0, 0.0, 0.5);
    // }
    //out_Colour = boid_colour;
}
