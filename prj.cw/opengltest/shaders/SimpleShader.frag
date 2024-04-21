#version 460 core

struct Material{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light{
  vec3 position;
  
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform Material material;
uniform Light pointLight;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{

  //diffuse + ambient
  vec3 norm = normalize(Normal);
  vec3 pointLightDirection = normalize(pointLight.position - FragPos);
  float diff = max(dot(norm, pointLightDirection), 0.0);

  vec3 pointLightDiffuse;
  pointLightDiffuse.x = max(pointLight.diffuse.x + pointLight.ambient.x, 1.0);
  pointLightDiffuse.y = max(pointLight.diffuse.y + pointLight.ambient.y, 1.0);
  pointLightDiffuse.z = max(pointLight.diffuse.z + pointLight.ambient.z, 1.0);

  vec3 diffuse = pointLightDiffuse * vec3(texture(material.diffuse, TexCoord)) * diff;

  //specular
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-pointLightDirection, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = pointLight.specular * vec3(texture(material.specular, TexCoord)) * spec;

  FragColor = vec4(diffuse + specular, 1.0);
}