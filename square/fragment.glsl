#version 410 core

uniform sampler2D tex;
in vec2 fragTexCoord;

out vec4 color;
 
void main(){
    color = vec4(1,0,0,0);
}
