#version 410 core

const float tileSize = 32.0;

uniform mat4 worldToScreen;
uniform vec2 backgorundSize;
layout(location = 0) in vec2 quad;
out vec2 fBackgoundUV;
out vec2 fTileUV;

void main(){
  gl_Position = vec4(quad * backgorundSize * tileSize, 0.0, 1.0) * worldToScreen;
  fBackgoundUV = quad;
  fTileUV = quad * backgorundSize;
}
