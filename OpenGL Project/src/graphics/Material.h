#pragma once
#include "../maths/vec4.h"

//template <typename diffType  = vec4,typename specType = vec3, typename roughType = float>
//struct Material
//{
//	Material<diffType,specType,roughType>(diffType albedo,specType specular, roughType roughness);
//	diffType m_albedoColour;
//	specType m_specColour;
//	roughType m_roughness;
//private:
//	bool init();
//	//vec3 emmisiveColour, specularColour;
//	//float roughness, shininess;
//};



struct Material
{
	/*
	Material& SetAlbedo(Texture albedo);
	Material& SetAlbedo(vec4 albedo);
	Material& SetSpecular(Texture specular);
	Material& SetSpecular(vec3 specular);
	Material& SetRoughness(float roughness);
	Material& SetRoughness(Texture roughness);
	*/
	auto GetAlbedo();
	auto GetRoughness();
	auto GetSpecular();
private:
	

};


