#version 130

uniform vec2 worldPosition;

in vec2 localPosition;
in vec2 texCoord;

out vec2 fragTexCoord;

mat4 projectionMatrix = mat4(2.0/800.0, 0.0,       0.0, -1.0,
                             0.0,       2.0/640.0, 0.0, -1.0,
                             0.0,       0.0,       1.0,  0.0,
                             0.0,       0.0,       0.0,  1.0);  

void main(){
  fragTexCoord = texCoord;
  gl_Position.xy = worldPosition + localPosition;
  gl_Position.z = 0.0;
  gl_Position.w = 1.0;
  gl_Position = gl_Position * projectionMatrix;
}
