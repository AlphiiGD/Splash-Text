#include <random>
#include "SplashRead.hpp"

using namespace geode::prelude;

// Loads the file into a std::vector<string>, returns false if it fails.
bool SplashRead::loadFile(std::filesystem::path filePath)
{
    if (filePath.empty()) return false;

    m_FileStream.open(filePath);
    if (!m_FileStream.is_open())
    {
        log::error("File failed to open! May not exist!");
        return false;
    }

    std::optional<std::chrono::month_day> dateRangeStart = std::nullopt;
    std::optional<std::chrono::month_day> dateRangeEnd = std::nullopt;

    std::string line;
    int lineNum = 1;
    while (std::getline(m_FileStream, line))
    {
        // Skip over any empty lines or comment lines
        if (line.front() == '#' || line.empty())
        {
            log::debug("Skipping line {}; it is a comment or empty", lineNum);
            lineNum++;
            continue;
        }

        // Remove inline comments.
        if (size_t pos = line.find('#');
            pos != std::string::npos)
        {
            log::debug("Erasing all characters past col {} of line {}; it is a comment", pos + 1, lineNum);
            line.erase(pos);

            // If the line becomes only spaces from this action, we should skip it.
            if (std::all_of(
                line.begin(),
                line.end(),
                [](char c)
                {
                    return std::isspace(static_cast<unsigned char>(c));
                }))
            {
                log::debug("Removing line {}, it is empty", lineNum);
                lineNum++;
                continue;
            }
        }

        // Replace __LINE__ with the line number
        std::string lineMacro = "__LINE__";
        if (size_t pos = line.find(lineMacro);
            pos != std::string::npos)
        {
            line.replace(pos, lineMacro.length(), std::to_string(lineNum));
        }

        // Replace __PLAYER_USERNAME__ with player name
        std::string playerMacro = "__PLAYER_USERNAME__";
        if (size_t pos = line.find(playerMacro);
            pos != std::string::npos)
        {
            line.replace(pos, playerMacro.length(), GJAccountManager::get()->m_username);
        }

        // If our line begins with a . it must be an important keyword that affects the state of the reader.
        if (line[0] == '.')
        {
            parseKeyword(line);
            continue;
        }

        // If we are using a date range we must check if the current date is within that date range
        if (!m_DateRanges.empty())
        {
            auto now = std::chrono::floor<std::chrono::days>(std::chrono::system_clock::now());
            bool shouldNotAdd = false;
            for (const auto& dr : m_DateRanges) 
            {
                if (!dr.inRange(now))
                {
                    shouldNotAdd = true;
                    break;
                }
            }

            // Skip if out of range.
            if (shouldNotAdd) continue;
        }

        // Algorithm provided by undefined06855 on Discord and Git
        std::string trimmedLine;
        trimmedLine.reserve(line.length());
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '\0' || line[i] == '\n' || line[i] == '\r' || line[i] < ' ' || line[i] > '~') continue;
            trimmedLine += line[i];
        }

        // If our file stream fails during loading then we gotta return false
        if (m_FileStream.fail())
        {
            log::error("File stream failed during load.");
            m_FileStream.close();
            return false;
        }

        // Finally we can push back our processed string
        m_Lines.push_back(trimmedLine);
        lineNum++;
    }

    m_FileStream.close();
    return true;
}

SplashRead::SplashRead()
{
}

size_t SplashRead::getNextWord(std::string_view line, size_t initPos)
{
    size_t pos = line.find(' ', initPos);
    if (pos == std::string::npos) 
        return std::string::npos;
    while (line[++pos] == ' ' || line[pos] == '\t');
    return (line[pos] == '\0' || line[pos] == '\n') ? std::string::npos : pos;
}

bool SplashRead::parseKeyword(const std::string& line)
{
    if (line.starts_with(".DATERANGE"))
    {
        DateRange dr;
        auto res = dr.parse(line.substr(getNextWord(line, 0)));
        if (!res)
        {
            log::error("Failed to parse date range: ({}{}, {}{})\n{}!", dr.getStart().month(), dr.getStart().day(), dr.getEnd().month(), dr.getEnd().day(), res.unwrapErr());
            return false;
        }

        m_DateRanges.emplace_back(dr);
    }

    if (line.starts_with("./DATERANGE"))
    {
        if (m_DateRanges.empty())
        {
            log::error("Attempted to end date range that does not exist!");
            return false;
        }

        m_DateRanges.pop_back();
    }

    return true;
}

std::string SplashRead::getRandomLine()
{
    if (m_Lines.empty())
    {
        log::error("SplashRead lines are empty!");
        return "";
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, m_Lines.size() - 1);

    std::string selected = m_Lines[dis(gen)];
    std::string splashText(selected); // Copy to avoid modifying original
	
    std::string randMacro = "__RANDOM__";
    if (size_t pos = splashText.find(randMacro);
        pos != std::string::npos)
    {
        std::uniform_int_distribution<> dis0_100(0, 100);
        splashText.replace(pos, randMacro.length(), std::to_string(dis0_100(gen)));
    }

    return splashText;
}