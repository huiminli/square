#version 410 core

uniform vec2 worldPosition;
uniform vec2 worldTexCoord;

layout(location = 0) in vec2 localPosition;
layout(location = 1) in vec2 texCoord;

out vec2 fragTexCoord;

mat4 projectionMatrix = mat4(2.0/800.0, 0.0,       0.0, -1.0,
                             0.0,       2.0/640.0, 0.0, -1.0,
                             0.0,       0.0,       1.0,  0.0,
                             0.0,       0.0,       0.0,  1.0);  

void main(){
  fragTexCoord = texCoord + worldTexCoord;

  vec4 vertexPosition;
  vertexPosition.xy = worldPosition + localPosition;
  vertexPosition.z = 0.0;
  vertexPosition.w = 1.0;

  gl_Position = vertexPosition * projectionMatrix;
}
