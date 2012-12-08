#version 430 core
in vec3 fragmentColor;
out vec4 color;

void main(){
    //    color.xyz = fragmentColor;
    //    color.w = 1.0;
    color = vec4(.3, .5, 0.7, 1.0);
}
