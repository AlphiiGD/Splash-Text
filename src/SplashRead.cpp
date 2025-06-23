#include <random>
#include "SplashRead.hpp"

using namespace geode::prelude;

// Loads the file into a std::vector<string>, returns false if it fails.
bool SplashRead::loadFile()
{
	if (!m_FileStream.is_open())
	{
		log::error("Attempting to load a file from unopened stream!");
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

		// Non-alphanumeric characters are not allowed, if we see one, we fail.
		// Algorithm provided by undefined06855 on Discord and Git
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == '\0') continue;
			if (line[i] < ' ' || line[i] > '~')
			{
				if (line[i] != '\n' && line[i] != '\r')
				{
					log::error("Non-alphanumeric character detected at col {} of line {}", i + 1, lineNum);
					return false;
				}
			}
		}

		// If our file stream fails during loading then we gotta return false
		if (m_FileStream.fail())
		{
			log::error("File stream failed during load.");
			return false;
		}

		// Finally we can push back our processed string
		m_Lines.push_back(line);
		lineNum++;
	}

	return true;
}

SplashRead::SplashRead(std::string filePath)
{
	m_FileStream.open(Mod::get()->getResourcesDir() / filePath);
	if (m_FileStream.fail())
	{
		log::error("Failed to open file {}", Mod::get()->getResourcesDir() / filePath);
		m_FileStream.close();
	}
	
	if (!loadFile())
	{
		log::error("Failed to load file {}", filePath);
		m_Lines.clear();
	}

	m_FileStream.close();
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
	return m_Lines[dis(gen)];
}