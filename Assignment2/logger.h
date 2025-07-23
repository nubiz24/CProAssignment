#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>

// Các cấp độ log theo chuẩn syslog
typedef enum
{
    LOG_EMERGENCY = 0,
    LOG_ALERT,
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

// Khởi tạo logger với mức lọc và đường dẫn tệp log (NULL nếu không ghi file)
bool logger_init(LogLevel min_level, const char *file_path);

// Dọn dẹp tài nguyên logger (đóng file nếu có)
void logger_cleanup();

// Ghi log chính (nội bộ - không gọi trực tiếp)
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...);

// Đặt mức lọc log mới tại runtime
void logger_set_level(LogLevel new_level);

// Macro tiện lợi để ghi log, tự động điền __FILE__ và __LINE__
#define log_message(level, fmt, ...) \
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // LOGGER_H
