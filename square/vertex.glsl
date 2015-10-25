#version 330 core

in vec3 vertexPosition;
in vec2 vertTexCoord;
out vec2 fragTexCoord;

void main(){
  fragTexCoord = vertTexCoord;
  gl_Position.xyz = vertexPosition;
  gl_Position.w = 1.0;
}
