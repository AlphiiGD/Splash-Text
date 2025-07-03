#pragma once
#include <Geode/Geode.hpp>
#include <filesystem>
#include <fstream>

class SplashRead
{
private:
	std::ifstream m_FileStream;
	std::vector<std::string> m_Lines;
public:
	bool loadFile(std::filesystem::path filePath);
	SplashRead();
	std::string getRandomLine();
};