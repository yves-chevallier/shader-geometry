#version 150
in vec4 finalColour;
out vec4 out_Colour;

void main(void){
    out_Colour = vec4(finalColour.rgb, 1.0);
}
