#pragma once
#include <sstream>
#include <stdexcept>

//Error Checker
#define ERROR_CHECK(ret)		\
	if (FAILED(ret)) {			\
		std::stringstream ss;	\
		ss << "failed " #ret " " << std::hex << ret << std::endl; \
		throw std::runtime_error(ss.str().c_str());				\
		}						

//Safe Release
template<class T>
inline void safeRelease(T*& rel)
{
	if (rel != NULL)
	{
		rel->Release();
		rel = NULL;
	}
}
