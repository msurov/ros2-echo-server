#pragma once


inline int64_t get_epoch_usec()
{
	int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
	return t;
}
