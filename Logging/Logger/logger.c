#include "logger.h"
#include <stdarg.h>
#include <string.h>
#include <time.h>

static LogLevel current_level = LOG_INFO;
static FILE *log_file = NULL;

// Map enum sang chuỗi mức log
static const char *level_strings[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
    "WARNING", "NOTICE", "INFO", "DEBUG"};

// Lấy thời gian hiện tại dạng chuỗi
static void get_timestamp(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Khởi tạo logger
bool logger_init(LogLevel min_level, const char *file_path)
{
    current_level = min_level;
    if (file_path != NULL)
    {
        log_file = fopen(file_path, "a");
        if (log_file == NULL)
            return false;
    }
    return true;
}

// Đặt lại mức lọc log
void logger_set_level(LogLevel new_level)
{
    current_level = new_level;
}

// Dọn dẹp logger
void logger_cleanup()
{
    if (log_file != NULL)
    {
        fclose(log_file);
        log_file = NULL;
    }
}

// Ghi log với thông tin mức, file, dòng
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    if (level > current_level)
        return;

    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));

    // Format log chính
    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    // Ghi định dạng chuẩn
    char final_log[1200];
    snprintf(final_log, sizeof(final_log),
             "[%s] [%s] [%s:%d] - %s\n",
             timestamp, level_strings[level], file, line, message);

    // In ra stdout hoặc stderr
    FILE *out = (level <= LOG_ERROR) ? stderr : stdout;
    fprintf(out, "%s", final_log);
    fflush(out);

    // Nếu có file log
    if (log_file)
    {
        fprintf(log_file, "%s", final_log);
        fflush(log_file);
    }
}
