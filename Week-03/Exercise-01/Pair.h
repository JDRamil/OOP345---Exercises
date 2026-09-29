#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H

#include <string>
#include <iostream>
#include "Collection.h"

namespace seneca
{
	/// <summary>
	/// Represents a key-value pair (e.g. a word and its definition).
	/// Two Pairs are considered equal if they have the same key.
	/// </summary>
	class Pair
	{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() { return m_key; }
		const std::string& getValue() { return m_value; }
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value } {};

		// Needed so that Collection<Pair, CAPACITY> can default-construct its
		// internal array and its static "default object" member.
		Pair() = default;

		// Needed so that Set<Pair>::add() (inherited, generic implementation)
		// can detect duplicate keys.
		bool operator==(const Pair& other) const;

		// Needed so that Collection<Pair, CAPACITY>::display() can print a
		// Pair the same way it prints any other type (via `os << item`).
		friend std::ostream& operator<<(std::ostream& os, Pair& p);
	};

	// Specialization: for a Collection<Pair, 100> (i.e. the one used by
	// Set<Pair>), the "no such element" default object should be a
	// ("No Key", "No Value") pair instead of an empty one.
	template<>
	inline Pair Collection<Pair, 100>::stat{ "No Key", "No Value" };
}

#endif
