#pragma once
#include <Geode/Geode.hpp>
#include <filesystem>
#include <fstream>

class SplashRead
{
private:
	std::ifstream m_FileStream;
	std::vector<std::string> m_Lines;
	bool loadFile();
public:
	SplashRead(std::string filePath);
	std::string getRandomLine();
};