#version 410 core

uniform vec2 worldPosition;
uniform uint tileIndex;
layout(location = 0) in vec2 vPosition;
out vec2 fTextureUV;

const vec2 tileUV = vec2(1.0 / 16, 1.0 / 16);
const mat4 projectionMatrix = mat4(
  2.0/800.0, 0.0,       0.0, -1.0,
  0.0,       2.0/640.0, 0.0, -1.0,
  0.0,       0.0,       1.0,  0.0,
  0.0,       0.0,       0.0,  1.0);  

void main(){
  gl_Position = vec4(worldPosition + vPosition * 32, 0.0, 1.0) * projectionMatrix;

  vec2 tileIndex2D = vec2(mod(tileIndex, 16), tileIndex / 16);
  vec2 tileQuadOffset = vec2(vPosition.x, 1 - vPosition.y);
  fTextureUV = tileUV * (tileQuadOffset + tileIndex2D);
}
