#include "log.h"
#include <iostream>

Logging::Logging(){
    LogLevel = LOG_LEVEL_INFO;
}

void Logging::SetLogLevel(int log_level){
    LogLevel = log_level;
}

void Logging::Info(const char* message){
    if (LogLevel >= LOG_LEVEL_INFO){
        std::cout << C_INFO << "[INFO] " << ENDC << message << "\n";
    }
}

void Logging::Warning(const char* message){
    if (LogLevel >= LOG_LEVEL_WARNING){
        std::cout << C_WARNING << "[WARNING] " << ENDC << message << "\n";
    }
}

void Logging::Error(const char* message){
    std::cout << C_FAIL << "[ERROR] " << ENDC << message << "\n";
}