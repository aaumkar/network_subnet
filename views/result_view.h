
#include <furi.h>
#include <gui/gui.h>
#include <gui/view.h>

typedef struct {
    char network[16]; // "192.168.1.0"
    char broadcast[16]; // "192.168.1.255"
    char hosts[12]; // "254 hosts"
    uint8_t cidr; // 24  (to display "/24")
    uint32_t host_count;
} ResultViewModel;

View* result_view_alloc(void);
void result_view_free(View* view);
