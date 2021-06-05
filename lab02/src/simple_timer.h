#ifndef CLASS_SIMPLE_TIMER_H
#define CLASS_SIMPLE_TIMER_H

#include <chrono>

namespace lab
{
	class simple_timer
	{
		std::chrono::steady_clock::time_point start;

	public:
		simple_timer()
		{
			reset();
		}

		void reset()
		{
			start = std::chrono::steady_clock::now();
		}
	
		long long get_elapsed_ms() const
		{
			return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
		}
	};
}

#endif