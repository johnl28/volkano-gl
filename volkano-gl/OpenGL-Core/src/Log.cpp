#include <iostream>
#include <cstdarg>
#include <cstdio>

#include "Log.h"


namespace glcore
{

	void Log::PrintLog(LogType type, const char* format, ...)
	{
        va_list args;
        va_start(args, format);

        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), format, args);

        switch (type) 
        {
        case LogType::INFO:
            std::cout << "[INFO] ";
            break;
        case LogType::WARNING:
            std::cout << "\033[33m[WARNING] ";
            break;
        case LogType::ERROR:
            std::cout << "\033[31m[ERROR] ";
            break;
        }

        std::cout << buffer << "\033[0m" << std::endl;

        va_end(args);
	}


}


