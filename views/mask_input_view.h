
#include <furi.h>
#include <gui/gui.h>
#include <gui/view.h>

typedef struct {
    char octect_digits[12]; // each digit in ip/cidr format
    uint8_t active_digit; // 0 ... 14 (12 of ip + 2 of CIDR)
} MaskInputViewModel;

View* mask_input_view_alloc(void* context);
void mask_input_view_free(View* view);
