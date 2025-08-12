#include <stdio.h>
#include "led_driver.h"

int main()
{
    if (led_init(10) != 0)
    {
        printf("Failed to initialize LED buffer.\n");
        return 1;
    }

    // Kiểm tra buffer có toàn 0 không
    const uint32_t *buf = led_get_buffer();
    for (size_t i = 0; i < led_get_pixel_count(); ++i)
    {
        if (buf[i] != 0)
        {
            printf("Pixel %zu is not initialized to 0.\n", i);
        }
    }

    // Thiết lập màu cho các pixel
    led_set_pixel_color(0, 255, 0, 0);     // Red
    led_set_pixel_color(9, 0, 0, 255);     // Blue
    led_set_pixel_color(4, 255, 255, 255); // White

    // In kết quả
    buf = led_get_buffer();
    printf("Pixel 0: 0x%08X (expected 0x0000FF00)\n", buf[0]);
    printf("Pixel 4: 0x%08X (expected 0x00FFFFFF)\n", buf[4]);
    printf("Pixel 9: 0x%08X (expected 0x000000FF)\n", buf[9]);

    // Fill màu xanh lá
    led_fill(0, 255, 0);
    buf = led_get_buffer();
    for (size_t i = 0; i < led_get_pixel_count(); ++i)
    {
        if (buf[i] != 0x00FF0000)
        {
            printf("Pixel %zu not green: 0x%08X\n", i, buf[i]);
        }
    }

    led_shutdown();
    return 0;
}
