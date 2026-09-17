#include "ProteinDatabase.h"
#include <fstream>
#include <utility>

namespace seneca
{
	void ProteinDatabase::clear()
	{
		delete[] m_arr;
		m_arr = nullptr;
		m_size = 0;
	}

	void ProteinDatabase::copyFrom(const ProteinDatabase& src)
	{
		m_size = src.m_size;
		m_arr = m_size ? new Protein[m_size] : nullptr;
		for (size_t i = 0; i < m_size; ++i)
			m_arr[i] = src.m_arr[i];
	}

	ProteinDatabase::ProteinDatabase()
		: m_arr(nullptr), m_size(0)
	{
	}

	ProteinDatabase::ProteinDatabase(const std::string& filename)
		: m_arr(nullptr), m_size(0)
	{
		std::ifstream in(filename);
		if (!in)
			return;

		size_t capacity = 0;
		std::string line;
		std::string curUid;
		std::string curSeq;
		bool haveCurrent = false;

		auto flush = [&]()
		{
			if (!haveCurrent)
				return;

			if (m_size == capacity)
			{
				capacity = capacity ? capacity * 2 : 64;
				Protein* newArr = new Protein[capacity];
				for (size_t i = 0; i < m_size; ++i)
					newArr[i] = std::move(m_arr[i]);
				delete[] m_arr;
				m_arr = newArr;
			}
			m_arr[m_size].m_uid = curUid;
			m_arr[m_size].m_sequence = curSeq;
			++m_size;
		};

		while (std::getline(in, line))
		{
			if (!line.empty() && line.back() == '\r')
				line.pop_back();

			if (!line.empty() && line[0] == '>')
			{
				flush();
				haveCurrent = true;
				curSeq.clear();
				curUid.clear();

				size_t first = line.find('|');
				size_t second = (first == std::string::npos) ? std::string::npos : line.find('|', first + 1);
				if (first != std::string::npos && second != std::string::npos)
					curUid = line.substr(first + 1, second - first - 1);
			}
			else
			{
				curSeq += line;
			}
		}
		flush();
	}

	ProteinDatabase::ProteinDatabase(const ProteinDatabase& src)
		: m_arr(nullptr), m_size(0)
	{
		copyFrom(src);
	}

	ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) noexcept
		: m_arr(src.m_arr), m_size(src.m_size)
	{
		src.m_arr = nullptr;
		src.m_size = 0;
	}

	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& src)
	{
		if (this != &src)
		{
			clear();
			copyFrom(src);
		}
		return *this;
	}

	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& src) noexcept
	{
		if (this != &src)
		{
			clear();
			m_arr = src.m_arr;
			m_size = src.m_size;
			src.m_arr = nullptr;
			src.m_size = 0;
		}
		return *this;
	}

	ProteinDatabase::~ProteinDatabase()
	{
		clear();
	}

	size_t ProteinDatabase::size() const
	{
		return m_size;
	}

	std::string ProteinDatabase::getUID(size_t index) const
	{
		if (index >= m_size)
			return "None";
		return m_arr[index].m_uid;
	}

	const std::string& ProteinDatabase::operator[](size_t index) const
	{
		static const std::string empty;
		if (index >= m_size)
			return empty;
		return m_arr[index].m_sequence;
	}
}
