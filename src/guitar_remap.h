#ifndef GUITAR_REMAP_H
#define GUITAR_REMAP_H

#include <stdint.h>
#include <sys/prx.h>

// Plugin information
#define PLUGIN_NAME "GuitarControllerRemap"
#define PLUGIN_VERSION "1.0.0"
#define PLUGIN_AUTHOR "PS3 HEN Plugin Developer"

// Configuration
#define CONFIG_FILE "/dev_hdd0/plugins/guitar_remap.conf"
#define MAX_BUTTONS 32
#define MAX_CONFIG_LINE 256
#define THREAD_PRIO 1000
#define THREAD_STACK_SIZE 0x4000

// Interface settings
#define MAX_CONTROLLERS 8
#define MAX_BUTTON_HISTORY 50
#define INTERFACE_UPDATE_RATE 60 // Hz

// PS3 button definitions
#define PS3_CROSS        0x00000001
#define PS3_SQUARE       0x00000002
#define PS3_TRIANGLE     0x00000004
#define PS3_CIRCLE       0x00000008
#define PS3_L1           0x00000010
#define PS3_L2           0x00000020
#define PS3_R1           0x00000040
#define PS3_R2           0x00000080
#define PS3_SELECT       0x00000100
#define PS3_START        0x00000200
#define PS3_DPAD_UP      0x00000400
#define PS3_DPAD_DOWN    0x00000800
#define PS3_DPAD_LEFT    0x00001000
#define PS3_DPAD_RIGHT   0x00002000

// Guitar button definitions
#define GUITAR_STRUM_UP      0x00000001
#define GUITAR_STRUM_DOWN    0x00000002
#define GUITAR_FRET_GREEN    0x00000004
#define GUITAR_FRET_RED      0x00000008
#define GUITAR_FRET_YELLOW   0x00000010
#define GUITAR_FRET_BLUE     0x00000020
#define GUITAR_FRET_ORANGE   0x00000040
#define GUITAR_WHAMMY        0x00000080
#define GUITAR_STAR_POWER    0x00000100

// Button mapping structure
typedef struct {
    int guitar_button;
    int ps3_button;
    char name[32];
} button_mapping_t;

// Controller information structure
typedef struct {
    int port;
    int connected;
    char name[64];
    uint32_t current_buttons;
    uint32_t previous_buttons;
    uint32_t button_history[MAX_BUTTON_HISTORY];
    int history_index;
    int is_guitar_controller;
} controller_info_t;

// Interface state structure
typedef struct {
    int interface_active;
    int selected_controller;
    controller_info_t controllers[MAX_CONTROLLERS];
    int controller_count;
    pthread_t interface_thread;
} interface_state_t;

// Function prototypes
int load_config(void);
int parse_button_name(const char *name);
int parse_ps3_button(const char *name);
void create_default_config(void);
void *remap_controller_thread(void *arg);
void remap_buttons(uint32_t *input, uint32_t *output);
int detect_guitar_controller(void);

// Interface functions
void *interface_thread(void *arg);
void update_controller_info(void);
void draw_interface(void);
void handle_interface_input(void);
int is_guitar_controller(const char *name);
const char* get_button_name(uint32_t button_code);
void add_button_to_history(int controller_port, uint32_t button_code);

// Web interface functions
int start_web_interface(void);
void stop_web_interface(void);
void *web_server_thread(void *arg);
void handle_web_client(void *client);
void generate_html_page(char *buffer, size_t buffer_size);

// Global variables (extern declarations)
extern button_mapping_t button_mappings[MAX_BUTTONS];
extern int mapping_count;
extern int plugin_running;
extern pthread_t remap_thread;
extern interface_state_t interface_state;

#endif // GUITAR_REMAP_H 