#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H

#include <string>
#include <cstddef>
#include "plugin.h"
#include "message.h"

namespace seneca
{
	/// <summary>
	/// A plugin (functor) that marks a message as coming from a trusted
	/// sender when the sender's address is in the list loaded from a file.
	/// </summary>
	class VerifyIdentityPlugin : public Plugin
	{
		// Maximum number of trusted addresses kept (extra lines in the file are ignored).
		static const size_t MAX_TRUSTED = 10;

		std::string m_trusted[MAX_TRUSTED];
		size_t      m_numTrusted{};

	public:
		/// <summary>Loads the trusted addresses (one per line). Throws if the file can't be opened.</summary>
		VerifyIdentityPlugin(const char* filename);

		/// <summary>If the sender is trusted, prefixes the subject with "[TRUSTED] ".</summary>
		void operator()(Message& msg) override;

		void showStats() const override;
	};
}

#endif
