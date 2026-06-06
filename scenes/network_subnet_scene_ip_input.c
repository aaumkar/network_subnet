#include "network_subnet.h"
#include "../views/ip_input_view.h"
#include "../scenes/scenes.h"

void network_subnet_scene_ip_input_on_enter(void* context) {
    FURI_LOG_D(TAG, "In on_enter of ip_input");
    furi_assert(context);
    NetworkSubnetApp* app = context;
    with_view_model(
        app->ip_input_view,
        IpInputViewModel * m,
        {
            m->octects_and_cidr_digits[0] = 1;
            m->octects_and_cidr_digits[1] = 9;
            m->octects_and_cidr_digits[2] = 2;
            m->octects_and_cidr_digits[3] = 1;
            m->octects_and_cidr_digits[4] = 6;
            m->octects_and_cidr_digits[5] = 8;
            m->octects_and_cidr_digits[6] = 0;
            m->octects_and_cidr_digits[7] = 0;
            m->octects_and_cidr_digits[8] = 1;
            m->octects_and_cidr_digits[9] = 0;
            m->octects_and_cidr_digits[10] = 0;
            m->octects_and_cidr_digits[11] = 1;
            m->octects_and_cidr_digits[12] = 2;
            m->octects_and_cidr_digits[13] = 4;
            m->active_digit = app->active_digit;
        },
        true);
    view_dispatcher_switch_to_view(app->view_dispatcher, ViewIdIpInput);
}

bool network_subnet_scene_ip_input_on_event(void* context, SceneManagerEvent event) {
    furi_assert(context);
    NetworkSubnetApp* app = context;
    bool consumed = false;
    switch(event.type) {
    case SceneManagerEventTypeCustom:
        switch(event.event) {
        case EventIpConfirmed:
            FURI_LOG_D(TAG, "received eventIpConfirmed event");
            with_view_model(
                app->ip_input_view,
                IpInputViewModel * m,
                {
                    uint8_t three_counter = 0;
                    uint8_t octet_counter = 0;
                    uint8_t temp_octet = 0;
                    uint8_t hundred = 100;
                    for(int i = 0; i < 13; i++) {
                        if(three_counter == 3) {
                            hundred = 100;
                            app->ip[octet_counter] = temp_octet;
                            three_counter = 0;
                            FURI_LOG_D(
                                TAG, "calculated octect %d to be %d", octet_counter, temp_octet);
                            octet_counter += 1;
                            temp_octet = 0;
                        }
                        temp_octet = temp_octet + m->octects_and_cidr_digits[i] * hundred;
                        hundred = hundred / 10;
                        three_counter += 1;
                    }
                    app->cidr =
                        m->octects_and_cidr_digits[12] * 10 + m->octects_and_cidr_digits[13];
                    FURI_LOG_D(TAG, "calculated cidr %d", app->cidr);
                },
                false);
            scene_manager_next_scene(app->scene_manager, NetworkSubnetSceneResult);
            consumed = true;
            break;
        }
        break;
    default:
        consumed = false;
    }
    return consumed;
}
void network_subnet_scene_ip_input_on_exit(void* context) {
    furi_assert(context);
    NetworkSubnetApp* app = context;
    UNUSED(app);
}
