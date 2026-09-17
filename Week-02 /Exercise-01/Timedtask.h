#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <chrono>
#include <string>
#include <vector>
#include <ostream>

namespace seneca
{
	/// <summary>
	/// Measures and reports the elapsed time (in nanoseconds) of a series of tasks.
	/// </summary>
	class TimedTask
	{
		struct Entry
		{
			std::string label;
			long long   duration_ns;
		};

		std::chrono::high_resolution_clock::time_point m_start;
		long long m_lastDuration;
		std::vector<Entry> m_tasks;

	public:
		TimedTask();

		/// <summary>Marks the beginning of a timed section.</summary>
		void startClock();

		/// <summary>Marks the end of a timed section and records the elapsed time.</summary>
		void stopClock();

		/// <summary>Stores the most recently measured duration under the given label.</summary>
		void addTask(const std::string& label);

		friend std::ostream& operator<<(std::ostream& os, const TimedTask& t);
	};
}

#endif
