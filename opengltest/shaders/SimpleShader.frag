#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
  //ambient
  float ambientStrenght = 0;
  vec3 ambient = lightColor * ambientStrenght;

  vec4 finalColor = vec4(0 * objectColor, 1.0);

  FragColor = vec4(0);
  //FragColor = texture(texture1, TexCoord) * 0;
}