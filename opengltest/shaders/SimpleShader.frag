#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;

void main()
{
  //ambient
  float ambient = 0.1;

  //diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);
  float diffuse = max(dot(norm, lightDirection), 0.0);

  vec3 finalColor = (ambient + diffuse) * lightColor * objectColor;

  FragColor = texture(texture1, TexCoord) * vec4(finalColor, 1.0);
}