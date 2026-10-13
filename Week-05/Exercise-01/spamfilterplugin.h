#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include <string>
#include <cstddef>
#include "plugin.h"
#include "message.h"

namespace seneca
{
	/// <summary>
	/// A plugin (functor) that marks a message as spam when its subject
	/// contains any of the strings loaded from a file.
	/// </summary>
	class SpamFilterPlugin : public Plugin
	{
		// Maximum number of spam strings kept (extra lines in the file are ignored).
		static const size_t MAX_PATTERNS = 10;

		std::string m_patterns[MAX_PATTERNS];
		size_t      m_numPatterns{};
		size_t      m_spamCount{};

	public:
		/// <summary>Loads the spam strings (one per line). Throws if the file can't be opened.</summary>
		SpamFilterPlugin(const char* filename);

		/// <summary>If the subject contains a spam string, prefixes it with "[SPAM] ".</summary>
		void operator()(Message& msg) override;

		void showStats() const override;
	};
}

#endif
