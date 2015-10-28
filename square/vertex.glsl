#version 410 core

uniform vec2 worldPosition;
uniform vec2 tileTextureUV;

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vTextureUV;

out vec2 fTextureUV;

mat4 projectionMatrix = mat4(2.0/800.0, 0.0,       0.0, -1.0,
                             0.0,       2.0/640.0, 0.0, -1.0,
                             0.0,       0.0,       1.0,  0.0,
                             0.0,       0.0,       0.0,  1.0);  

void main(){
  gl_Position = vec4(worldPosition + vPosition, 0.0, 1.0) * projectionMatrix;
  fTextureUV = vTextureUV + tileTextureUV;
}
