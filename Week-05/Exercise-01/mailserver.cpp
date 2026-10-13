#include "mailServer.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

namespace seneca
{
	MailServer::MailServer(const char* name, const char* address)
		: m_userName{ name }, m_userAddress{ address }
	{
	}

	// Deep-copies the inbox (composition) and copies the plugins' ADDRESSES
	// (aggregation: the plugin objects themselves are shared, not duplicated).
	// The observer is deliberately not copied: it is a subscription registered
	// on one specific server object.
	void MailServer::copyData(const MailServer& src)
	{
		Message* newInbox = nullptr;
		if (src.m_cnt > 0)
		{
			newInbox = new Message[src.m_cnt];
			for (size_t i = 0; i < src.m_cnt; ++i)
				newInbox[i] = src.m_inbox[i];
		}

		delete[] m_inbox;
		m_inbox = newInbox;
		m_cnt = src.m_cnt;

		m_plugins[0] = src.m_plugins[0];
		m_plugins[1] = src.m_plugins[1];
	}

	MailServer::MailServer(const MailServer& src)
		: m_userName{ src.m_userName }, m_userAddress{ src.m_userAddress }
	{
		copyData(src);
	}

	MailServer::MailServer(MailServer&& src) noexcept
		: m_userName{ std::move(src.m_userName) }, m_userAddress{ std::move(src.m_userAddress) },
		  m_inbox{ src.m_inbox }, m_cnt{ src.m_cnt }
	{
		m_plugins[0] = src.m_plugins[0];
		m_plugins[1] = src.m_plugins[1];

		src.m_inbox = nullptr;
		src.m_cnt = 0;
		src.m_plugins[0] = src.m_plugins[1] = nullptr;
	}

	MailServer& MailServer::operator=(const MailServer& src)
	{
		if (this != &src)
		{
			m_userName = src.m_userName;
			m_userAddress = src.m_userAddress;
			copyData(src);
		}
		return *this;
	}

	MailServer& MailServer::operator=(MailServer&& src) noexcept
	{
		if (this != &src)
		{
			delete[] m_inbox;

			m_userName = std::move(src.m_userName);
			m_userAddress = std::move(src.m_userAddress);
			m_inbox = src.m_inbox;
			m_cnt = src.m_cnt;
			m_plugins[0] = src.m_plugins[0];
			m_plugins[1] = src.m_plugins[1];

			src.m_inbox = nullptr;
			src.m_cnt = 0;
			src.m_plugins[0] = src.m_plugins[1] = nullptr;
		}
		return *this;
	}

	MailServer::~MailServer()
	{
		// only the messages are owned; the plugins belong to somebody else
		delete[] m_inbox;
	}

	void MailServer::receiveMail(Message msg)
	{
		if (msg.m_toAddress != m_userAddress)
			throw msg.m_toAddress;   // a std::string: the address the message was meant for

		// grow the inbox by one element
		Message* newInbox = new Message[m_cnt + 1];
		for (size_t i = 0; i < m_cnt; ++i)
			newInbox[i] = std::move(m_inbox[i]);
		newInbox[m_cnt] = std::move(msg);

		delete[] m_inbox;
		m_inbox = newInbox;
		++m_cnt;

		Message& newest = m_inbox[m_cnt - 1];

		for (auto* plugin : m_plugins)
			if (plugin)
				(*plugin)(newest);

		if (onNewMailArrived)
			onNewMailArrived(newest);
	}

	void MailServer::addPlugin(Plugin* thePlugin)
	{
		for (auto& slot : m_plugins)
		{
			if (slot == nullptr)
			{
				slot = thePlugin;
				return;
			}
		}
	}

	void MailServer::setObserver(Observer_pfn observer)
	{
		onNewMailArrived = observer;
	}

	Message& MailServer::operator[](size_t idx)
	{
		if (idx >= m_cnt)
			throw std::out_of_range("Index " + std::to_string(idx) + " is out of bounds.");
		return m_inbox[idx];
	}

	size_t MailServer::getInboxSize() const
	{
		return m_cnt;
	}

	void MailServer::showInbox() const
	{
		// remember the stream's formatting so this function leaves no side effects
		std::ios::fmtflags flags = std::cout.flags();

		for (size_t i = 0; i < m_cnt; ++i)
		{
			const Message& msg = m_inbox[i];

			// only the date, without the time
			std::string date = msg.m_date.substr(0, msg.m_date.find(' '));

			std::cout << std::right << std::setw(20) << msg.m_fromName << "  "
			          << std::left  << std::setw(40) << msg.m_fromAddress << "  "
			          << std::setw(15) << date << "  "
			          << msg.m_subject << '\n';
		}

		std::cout.flags(flags);
	}
}
