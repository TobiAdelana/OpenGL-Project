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
	using namespace std;
	ifstream file(filepath);
	if (!file.is_open())
	{
		cout << "[ERROR] Could not open OBJ File " << filepath << endl;
		return 1;
	}
	string line;
	while (getline(file, line))
	{
		switch (line[0])
		{
		case 'v':
			switch (line[1])
			{
			case 't':
				output.m_textures.push_back({ 3, "" });

			}
			break;
		case 'f':
		default:
			break;
		}

	}
}