#include "logger.h"

int main()
{
    if (!logger_init(LOG_DEBUG, "log_output.txt"))
    {
        fprintf(stderr, "Logger init failed\n");
        return 1;
    }

    log_message(LOG_INFO, "Application started");
    log_message(LOG_WARNING, "Low memory warning");
    log_message(LOG_ERROR, "Failed to allocate memory");
    log_message(LOG_DEBUG, "This is a debug message");

    logger_set_level(LOG_ERROR); // Đổi mức lọc tại runtime

    log_message(LOG_INFO, "This log should be filtered out");
    log_message(LOG_CRITICAL, "System critical failure");

    logger_cleanup();
    return 0;
}
