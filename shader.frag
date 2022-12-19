#version 150
in vec3 finalColour;
in vec4 center;

out vec4 out_Colour;

//uniform vec3 boidColour;
void main(void){
    //out_Colour = vec4(1.0, 0.0, 0.0, 0.8);
    // if (center.w > 0.0){
    //     out_Colour = vec4(finalColour, 0.8);
    // }
    // else {
        vec2 resolution = vec2(800.0/2.0, 800.0/2.0);
        vec2 uv = gl_FragCoord.xy / resolution.xy;
        // uv.x -= 0.5;
        // uv.y -= 0.5;
        uv = uv + vec2(-1.0, -1.0) ;
        //uv += vec2(-0.5, -0.5);
        vec2 uvc = center.xy + vec2(-1.0, -1.0);
        uv += uvc;

        float dist = length(uv);//, vec2(0.0, 0.0));
        // if (dist < 0.1) {
        //     dist = 1.0;
        // }
        // else {
        //     dist = 0.0;
        // }
        out_Colour = vec4(dist, 0.0, 0.0, 1.0);
        out_Colour = vec4(uv.x * 2.0, uv.y * 2.0, 0, 1.0);
        out_Colour = vec4(finalColour * dist, 0.8);
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
