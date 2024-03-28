#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
  vec4 color = vec4(lightColor * objectColor, 1.0);
  FragColor = texture(texture1, TexCoord) * color;
}