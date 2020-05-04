#version 410 core

const float tileSize = 32.0;
const vec2 tileUV = vec2(1.0 / 16, 1.0 / 16);

uniform vec2 worldPosition;
uniform mat4 worldToScreen;
uniform uint tileIndex;
layout(location = 0) in vec2 quad;
out vec2 fTextureUV;

void main(){
  gl_Position = vec4((worldPosition + quad) * tileSize, 0.0, 1.0) * worldToScreen;

  vec2 tileIndex2D = vec2(mod(tileIndex, 16), tileIndex / 16);
  vec2 tileQuadOffset = vec2(quad.x, 1 - quad.y);
  fTextureUV = tileUV * (tileQuadOffset + tileIndex2D);
}
