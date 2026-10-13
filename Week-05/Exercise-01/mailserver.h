#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H

#include <string>
#include <cstddef>
#include "message.h"
#include "plugin.h"

namespace seneca
{
	using Observer_fn  = void(const Message&);     // the function type
	using Observer_pfn = void(*)(const Message&);  // the pointer-to-function type

	/// <summary>
	/// Manages the inbox of a single user.
	///  - the Messages in the inbox are in COMPOSITION with the server
	///    (the server owns them and makes deep copies);
	///  - the Plugins are in AGGREGATION with the server (the server only
	///    stores their addresses; it never copies or deletes them).
	/// </summary>
	class MailServer
	{
		std::string  m_userName{};
		std::string  m_userAddress{};
		Message*     m_inbox{ nullptr };
		size_t       m_cnt{};
		Observer_pfn onNewMailArrived{ nullptr };
		Plugin*      m_plugins[2]{ nullptr, nullptr };

		void copyData(const MailServer& src);

	public:
		MailServer(const char* name, const char* address);

		MailServer(const MailServer& src);
		MailServer(MailServer&& src) noexcept;
		MailServer& operator=(const MailServer& src);
		MailServer& operator=(MailServer&& src) noexcept;
		~MailServer();

		/// <summary>
		/// Adds the message to the inbox if it is addressed to this user (then runs
		/// the plugins on it and notifies the observer). Otherwise throws a
		/// std::string containing the destination address of the message.
		/// </summary>
		void receiveMail(Message msg);

		/// <summary>Stores the plugin's address in the first free slot (if any).</summary>
		void addPlugin(Plugin* thePlugin);

		void setObserver(Observer_pfn observer);

		/// <summary>Throws std::out_of_range if idx is not a valid index.</summary>
		Message& operator[](size_t idx);

		size_t getInboxSize() const;
		void showInbox() const;
	};
}

#endif
