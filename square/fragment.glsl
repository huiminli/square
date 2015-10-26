#version 330 core

uniform sampler2D texture2D;
in vec2 fragTexCoord;

out vec4 color;
 
void main(){
    color = texture(texture2D, fragTexCoord);
    color.ba = fragTexCoord;
}
