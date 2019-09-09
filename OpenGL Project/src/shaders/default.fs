#version 330
in vec3 frag_normal;
in vec3 frag_pos;

uniform struct Material
{
	vec3 ambientColour;
	vec3 specColour;
	vec3 diffuseColour;
	float shininess;

} material; 

uniform struct Light
{
	vec3 position;
	vec3 colour;

} light;

uniform vec3 cameraPos;
out vec4 outColour;


void main()
{
	vec3 norm = normalize(frag_normal);
	vec3 lightDir = normalize(light.position - frag_pos);

	// Diffuse Light
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.colour * (diff * material.diffuseColour);

	// Specular Light
	vec3 cameraDir = normalize(cameraPos - frag_pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.colour * (spec * material.specColour);

	// Ambient Light
	vec3 ambient = light.colour * material.ambientColour;

	float ambientweight = 0.3, diffuseweight = 0.2, specularweight = 0.8;
	vec3 result = (ambient * ambientweight + diffuse * diffuseweight + specular * specularweight);
	outColour = vec4(result, 1.0);
}