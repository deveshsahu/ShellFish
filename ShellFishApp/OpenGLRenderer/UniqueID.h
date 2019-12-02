#pragma once

#include <cstdint>
#include <mutex>

using ID = uint32_t;

class UniqueIDGenerator
{
public:
	//ID 
private:
	ID increment()
	{
		mMutex.lock();

	}
	uint32_t mCounter;
	std::mutex mMutex;
};