#version 410 core

const vec2 tileUV = vec2(1.0 / 16, 1.0 / 16);

uniform sampler2D tileTexture;
uniform usampler2D spriteGridTilesTexture;

in vec2 fBackgroundUV;
in vec2 fTileUV;
out vec4 color;
 
void main(){
	uint tileIndex = texture(spriteGridTilesTexture, vec2(fBackgroundUV.x, 1 - fBackgroundUV.y)).x;

	vec2 tilePosition = vec2(mod(tileIndex, 16), tileIndex / 16) + vec2(fract(fTileUV).x, 1 - fract(fTileUV).y);
    color = texture(tileTexture, tilePosition * tileUV);
}
