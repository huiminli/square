#version 410 core

const float tileSize = 32.0;

uniform vec2 worldPosition;
uniform mat4 worldToScreen;
uniform vec2 spriteGridSize;
layout(location = 0) in vec2 quad;
out vec2 fBackgroundUV;
out vec2 fTileUV;

void main(){
  gl_Position = vec4(worldPosition * tileSize + quad * spriteGridSize * tileSize, 0.0, 1.0) * worldToScreen;
  fBackgroundUV = quad;
  fTileUV = quad * spriteGridSize;
}
