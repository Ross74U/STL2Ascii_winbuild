#ifndef LOG_H
#define LOG_H

#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_ERROR 0

// ANSI color codes
#define C_INFO "\033[94m"
#define C_WARNING "\033[93m"
#define C_FAIL "\033[91m"
#define ENDC "\033[0m"

class Logging{

private:
    int LogLevel;

public:
    Logging();
    void SetLogLevel(int log_level);
    void Info(const char* message);
    void Warning(const char* message);
    void Error(const char* message);
};

#endif
