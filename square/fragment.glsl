#version 410 core

uniform sampler2D texture2D;
in vec2 textureUV;

out vec4 color;
 
void main(){
    color.rg = textureUV;
    color.ba = vec2(0,0);
}
