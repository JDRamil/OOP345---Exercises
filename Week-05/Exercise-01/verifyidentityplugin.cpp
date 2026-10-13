#include "verifyIdentityPlugin.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace seneca
{
	VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename)
	{
		std::ifstream file(filename);
		if (!file)
			throw std::runtime_error(std::string("Cannot open file [") + filename + "]");

		std::string line;
		while (m_numTrusted < MAX_TRUSTED && std::getline(file, line))
		{
			// files created on Windows may end their lines with "\r\n"
			if (!line.empty() && line.back() == '\r')
				line.pop_back();

			if (!line.empty())
				m_trusted[m_numTrusted++] = line;
		}
	}

	void VerifyIdentityPlugin::operator()(Message& msg)
	{
		for (size_t i = 0; i < m_numTrusted; ++i)
		{
			if (msg.m_fromAddress == m_trusted[i])
			{
				msg.m_subject.insert(0, "[TRUSTED] ");
				break;
			}
		}
	}

	void VerifyIdentityPlugin::showStats() const
	{
		std::cout << "[Identity Checker Plugin] can validate identity for ";
		for (size_t i = 0; i < m_numTrusted; ++i)
		{
			if (i > 0)
				std::cout << ", ";
			std::cout << m_trusted[i];
		}
		std::cout << '\n';
	}
}
