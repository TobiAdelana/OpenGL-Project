#include "fileUtils.h"
std::string FileUtils::LoadTextFile(const char* filePath)
{

	std::string line, result;
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cout << "Could not open: " << filePath << std::endl;
		throw std::invalid_argument("File not found");
		return "";
	}
	while (std::getline(file, line))
	{
		result += line + '\n';
	}
	file.close();
	return result;
}

int FileUtils::LoadObjFile(const std::string& filepath, Mesh& output)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		std::cout << "[ERROR] Could not open OBJ File " << filepath << std::endl;
		return 1;
	}
	std::string line;
	while (getline(file, line))
	{
		if(line[0] == 'v' && line[1] == 't')
		{
			output.m_textures.push_back({ 3, "" });
		}

	}
}