#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <string>
#include <cstddef>

namespace seneca
{
	/// <summary>
	/// Stores a collection of proteins (Unique ID + amino acid sequence) parsed
	/// from a FASTA-like text file.
	/// </summary>
	class ProteinDatabase
	{
		struct Protein
		{
			std::string m_uid;
			std::string m_sequence;
		};

		Protein* m_arr;
		size_t   m_size;

		void clear();
		void copyFrom(const ProteinDatabase& src);

	public:
		ProteinDatabase();
		explicit ProteinDatabase(const std::string& filename);

		ProteinDatabase(const ProteinDatabase& src);
		ProteinDatabase(ProteinDatabase&& src) noexcept;

		ProteinDatabase& operator=(const ProteinDatabase& src);
		ProteinDatabase& operator=(ProteinDatabase&& src) noexcept;

		~ProteinDatabase();

		size_t size() const;

		/// <summary>Returns the Unique ID of the protein at `index`, or "None" if out of range.</summary>
		std::string getUID(size_t index) const;

		/// <summary>Returns the amino acid sequence of the protein at `index`, or "" if out of range.</summary>
		const std::string& operator[](size_t index) const;
	};
}

#endif
