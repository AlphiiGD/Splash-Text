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