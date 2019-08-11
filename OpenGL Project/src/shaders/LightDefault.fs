#version 330
#define MAX_LIGHTS 10
uniform mat4 ModelViewProjMatrix;
layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;


uniform struct Light 
{
	vec4 position;
	vec3 colour;	
	float attenuation;
	float ambientCoefficient;
	float coneaAngle;
	vec3 coneDirection;

} allLights[MAX_LIGHTS];

vec3 ApplyLight(Light light, vec3 surfaceColour, vec3 normal, vec3 surfacePosition, vec3 surfaceToCamera)
{
	vec3 surfaceToLight;
	float attenuation = 1.0f;
	if(light.position.x == 0.0f)
	{
		// directional light
		surfaceToLight = normalize(light.position.xyz);
	}
	else 
	{
		surfaceToLight = normalize(light.position.xyz - surfacePosition)
		float distanceToLight = length(surfaceToLight);
		attenuation = 1.0f / (1.0f + light.attenuation * pow(distanceToLight,2));
		
		//cone
		float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
		if(lightToSurfaceAngle > light.coneAngle)
			attenuation = 0.0f;
	}

	vec3 ambient = light.ambientCoefficient * surfaceColour.rgb * light.colour;
	float diffuseCoefficient = max(0.0f, dot(normal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * surfaceColour.rgb * light.colour;


	// specular

	float specularCoefficient = 0.0f;
	if(diffuseCoefficient > 0.0f)
		specularCoefficient = pow(max(0.0f, dot(surfaceToCamera, reflect(-surfaceToLight,normal))), materialShininess);
	vec3 specular = specularCoefficient * materialSpecularColour * light.colour;
	return ambient + attenuation * (diffuse + specular); 




}


void main()
{



}
