#version 460 core

struct Material{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform Material material;

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
  float diff = max(dot(norm, lightDirection), 0.0);
  vec3 diffuse = vec3(texture(material.diffuse, TexCoord)) * min(diff + ambient, 1.0);

  //specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDirection, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = vec3(texture(material.specular, TexCoord)) * spec;

  FragColor = vec4(diffuse + specular, 1.0);
}