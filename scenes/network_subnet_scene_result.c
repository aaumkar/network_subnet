#include "network_subnet.h"
#include "../views/result_view.h"

void network_subnet_scene_result_on_enter(void* context) {
    furi_assert(context);
    NetworkSubnetApp* app = context;
    with_view_model(
        app->result_view,
        ResultViewModel * m,
        {
            // format from raw app state into display strings
            snprintf(
                m->network,
                sizeof(m->network),
                "%u.%u.%u.%u",
                (uint8_t)(app->subnet_result.network_addr >> 24) & 0xFF,
                (uint8_t)(app->subnet_result.network_addr >> 16) & 0xFF,
                (uint8_t)(app->subnet_result.network_addr >> 8) & 0xFF,
                (uint8_t)app->subnet_result.network_addr & 0xFF);

            snprintf(
                m->broadcast,
                sizeof(m->broadcast),
                "%u.%u.%u.%u",
                (uint8_t)(app->subnet_result.broadcast_addr >> 24) & 0xFF,
                (uint8_t)(app->subnet_result.broadcast_addr >> 16) & 0xFF,
                (uint8_t)(app->subnet_result.broadcast_addr >> 8) & 0xFF,
                (uint8_t)app->subnet_result.broadcast_addr & 0xFF);

            m->host_count = app->subnet_result.host_count;
            m->cidr = app->subnet_result.cidr;
        },
        true);
    view_dispatcher_switch_to_view(app->view_dispatcher, ViewIdResult);
}

bool network_subnet_scene_result_on_event(void* context, SceneManagerEvent event) {
    furi_assert(context);
    NetworkSubnetApp* app = context;
    UNUSED(app);
    UNUSED(event);
    return false;
}
void network_subnet_scene_result_on_exit(void* context) {
    furi_assert(context);
    NetworkSubnetApp* app = context;
    UNUSED(app);
}
