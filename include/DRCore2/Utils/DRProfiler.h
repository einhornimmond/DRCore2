/*!
*
* \author: einhornimmond
*
* \date: 08.03.19
*
* \brief: easy to use time profiler
*/

#ifndef DR_LUA_WEB_MODULE_CORE_LIB_PROFILER_H
#define DR_LUA_WEB_MODULE_CORE_LIB_PROFILER_H

#include <chrono>
#include <string>
#include "DRCore2/export.h"

class DRCORE2_EXPORT DRProfiler
{
public:
	DRProfiler();
	DRProfiler(const DRProfiler& copy);
	~DRProfiler();

	inline void reset() { mStartTick = std::chrono::high_resolution_clock::now(); }
	inline auto duration() const {
		return std::chrono::high_resolution_clock::now() - mStartTick;
	};
	double millis() const;
	double micros() const;
	double nanos() const;
	double seconds() const;
	std::string string() const;

protected:
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTick;
};

#endif //DR_LUA_WEB_MODULE_CORE_LIB_PROFILER_H
