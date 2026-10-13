#include "spamFilterPlugin.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace seneca
{
	SpamFilterPlugin::SpamFilterPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (!file)
			throw std::runtime_error(std::string("Cannot open file [") + filename + "]");

		std::string line;
		while (m_numPatterns < MAX_PATTERNS && std::getline(file, line))
		{
			// files created on Windows may end their lines with "\r\n"
			if (!line.empty() && line.back() == '\r')
				line.pop_back();

			// an empty string would match every subject, so skip blank lines
			if (!line.empty())
				m_patterns[m_numPatterns++] = line;
		}
	}

	void SpamFilterPlugin::operator()(Message& msg)
	{
		for (size_t i = 0; i < m_numPatterns; ++i)
		{
			if (msg.m_subject.find(m_patterns[i]) != std::string::npos)
			{
				msg.m_subject.insert(0, "[SPAM] ");
				++m_spamCount;   // count the message once, even if several patterns match
				break;
			}
		}
	}

	void SpamFilterPlugin::showStats() const
	{
		std::cout << "[Spam Filter Plugin] Identified " << m_spamCount << " spam messages.\n";
	}
}
