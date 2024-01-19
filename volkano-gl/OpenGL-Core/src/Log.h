#pragma once
#include <string>

namespace glcore
{
	enum class LogType {
		INFO,
		DEBUG,
		WARNING,
		ERROR
	};

	class Log
	{
	public:
		static void PrintLog(LogType type, const char *format, ...);
	};
}

#define GLCORE_WARN(...) ::glcore::Log::PrintLog(glcore::LogType::WARNING, __VA_ARGS__)
#define GLCORE_ERR(...) ::glcore::Log::PrintLog(glcore::LogType::ERROR, __VA_ARGS__)
#define GLCORE_INFO(...) ::glcore::Log::PrintLog(glcore::LogType::INFO, __VA_ARGS__)

// Remove Debug and Info logs on release mode
#ifdef _DEBUG
#define GLCORE_DEBUG(...) ::glcore::Log::PrintLog(glcore::LogType::DEBUG, __VA_ARGS__)
#else
#define GLCORE_DEBUG(...)
#endif
