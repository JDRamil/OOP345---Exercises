#include "TimedTask.h"
#include <iomanip>

namespace seneca
{
	TimedTask::TimedTask()
		: m_lastDuration(0)
	{
	}

	void TimedTask::startClock()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	void TimedTask::stopClock()
	{
		auto end = std::chrono::high_resolution_clock::now();
		m_lastDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_start).count();
	}

	void TimedTask::addTask(const std::string& label)
	{
		m_tasks.push_back({ label, m_lastDuration });
	}

	std::ostream& operator<<(std::ostream& os, const TimedTask& t)
	{
		os << "--------------------------\n";
		os << "Execution Times:\n";
		os << "--------------------------\n";
		for (const auto& entry : t.m_tasks)
			os << entry.label << std::setw(16) << entry.duration_ns << " nanoseconds\n";
		os << "--------------------------\n";
		return os;
	}
}
