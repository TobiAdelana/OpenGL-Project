#pragma once
#include "../graphics/Mesh.h"
#include <iostream>
#include <fstream>
#include <string>
#include <exception>
struct FileUtils
{
	static std::string LoadTextFile(const char* filePath);
	int LoadObjFile(const std::string& filepath, Mesh& output);
};