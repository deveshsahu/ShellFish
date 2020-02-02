#pragma once

#include <cstdint>
#include <mutex>

using ID = uint32_t;

/**
 * @brief Generates unique id by simply incrementing the counter
 * the upper limited by uint32_t's size. 
 * 
 * Create a static object of this type to create the required ID pool and 
 * call generate to return the required ID
 */
class UniqueIDGenerator
{
public:
	//ID 
	ID generate()
	{
		mMutex.lock();
		ID newid = ++mCounter;
		mMutex.unlock();
		return newid;
	}
private:
	uint32_t mCounter = 0;
	std::mutex mMutex;
};