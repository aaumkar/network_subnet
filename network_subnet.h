
#include <furi.h>
#include <gui/gui.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/submenu.h>
#include <gui/view.h>

#define TAG "--NetworkSubnet--"

typedef struct {
    uint32_t network_addr; // first address  (host bits zeroed)
    uint32_t broadcast_addr; // last address
    uint32_t host_count; // usable hosts
    uint8_t cidr; // prefix length
} SubnetResult;

typedef enum {
    InputModeIpSubnet,
    InputModeMask
} InputMode;

// View IDs — registered with ViewDispatcher
typedef enum {
    ViewIdMenu,
    ViewIdIpInput,
    ViewIdResult,
    // ViewIdMaskList,
} ViewId;

// Custom events — fired from views upward to scenes
typedef enum {
    EventMenuIpSelected,
    EventMenuMaskSelected,
    EventIpConfirmed,
    // EventBackFromResult,
} AppEvent;

typedef struct {
    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Submenu* submenu;
    View* result_view;
    View* ip_input_view;
    // View* mask_list;

    uint8_t ip[4];
    uint8_t cidr;
    uint8_t active_digit;
    SubnetResult subnet_result;
} NetworkSubnetApp;
