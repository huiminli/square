#version 410 core

uniform sampler2D tileTexture;
in vec2 fTextureUV;
out vec4 color;
 
void main(){
    color = texture(tileTexture, fTextureUV);
}
