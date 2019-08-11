vec4 calcColour (vec3 normal, vec3 light, vec3 view)
{
	
	vec3 half = normalize(normal + view);
	float NDotH = clamp(dot(normal, half), 0,1);
	float NDotV = clamp(dot(normal, view), 0,1);
	float VDotH = clamp(dot(view, half), 0,1);
	float NDotL = clamp(dot(normal, light), 0,1);
	float roughness = 0.0f;
	float rSqr = roughness * roughness;

	float geometric = 0.0f;
	geo_a = 2 * NDotH * NDotV;
	geo_b = 2 * NDotH * NDotL;
	geometric = min(1, min(geo_a/ VDotH, geo_b / VDotH));


	#ifdef BECKMANN
	float NDotHSqr = NDotH * NDotH;
	roughness = (1.0f / (NDotHSqr * NDotHSqr)) * exp((NDotHSqr - 1) / (rSqr * NDotHSqr) );

	#endif

	#ifdef GAUSSIAN
	float c = 1.0f;
	roughness = c * exp(-( NDotH/ rSqr));

	#endif


	float startF = 1.0f;
	float fresnel = pow(1 - HDotV, 5);
	fresnel *= 1-starF;
	fresnel += startF;

	float Rs = (fresnel * roughness * geometrix) / (NDotV * NDotL);
	vec3 final = nDotL * (specular * Rs + diffuse);

	return vec4(final, 1.0f);


}