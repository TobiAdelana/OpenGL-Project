#pragma once
#include <iostream>
#include <fstream>
#include <string>
class FileUtils
{
public:
	static char* LoadTextFile(const char* filePath)
	{
		
		std::string line, final;
		std::ifstream file(filePath);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				final += line + '\n';
			}
			file.close();
		}
		else 
		{
			std::cout << "Could not open: " << filePath << std::endl;
			return "";
		}
		char * cstr = new char[final.length() + 1];
		strcpy(cstr, final.c_str());
		return cstr;
		

		

	}

};