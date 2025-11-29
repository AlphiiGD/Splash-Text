#pragma once
#include <Geode/Geode.hpp>
#include <filesystem>
#include <fstream>

#include "DateRange.hpp"

class SplashRead
{
private:
    std::ifstream m_FileStream;
    std::vector<std::string> m_Lines;
    std::vector<DateRange> m_DateRanges;
    size_t getNextWord(std::string_view line, size_t initPos = 0);
    bool parseKeyword(const std::string& line);
public:
    bool loadFile(std::filesystem::path filePath);
    SplashRead();
    std::string getRandomLine();
};