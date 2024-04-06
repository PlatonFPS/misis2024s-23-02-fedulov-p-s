#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
  //ambient
  float ambient = 0.1;

  //diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDirection = normalize(lightPos - FragPos);
  float diffuse = max(dot(norm, lightDirection), 0.0);

  //specular
  float specularStrenght = 0.5;
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDirection, norm);
  float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32);

  vec3 finalColor = (ambient + diffuse + specular) * lightColor * objectColor;

  //FragColor = (texture(texture2, TexCoord)) * vec4(finalColor, 1.0);
  //FragColor = (texture(texture1, TexCoord) + texture(texture2, TexCoord)) / 2 * vec4(finalColor, 1.0);
  FragColor = vec4(finalColor, 1.0);
}