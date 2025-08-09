#include <ppu-types.h>
#include <sys/prx.h>
#include <sys/thread.h>
#include <sysmodule/sysmodule.h>
#include <net/net.h>
#include <net/netctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// Minimal test plugin: serves a simple page on http://<ps3-ip>:8080/

static volatile int plugin_running = 0;
static sys_ppu_thread_t http_thread_id;

static void http_thread(void *arg) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) return;

    int yes = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr; memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) { close(server); return; }
    if (listen(server, 4) < 0) { close(server); return; }

    while (plugin_running) {
        struct sockaddr_in caddr; socklen_t clen = sizeof(caddr);
        int client = accept(server, (struct sockaddr *)&caddr, &clen);
        if (client < 0) continue;

        const char *body = "<html><body><h1>Guitar Remap Test</h1><p>Plugin is running.</p></body></html>";
        char header[256];
        int blen = (int)strlen(body);
        int hlen = snprintf(header, sizeof(header),
                            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",
                            blen);
        if (hlen > 0) send(client, header, (size_t)hlen, 0);
        send(client, body, (size_t)blen, 0);
        close(client);
    }

    close(server);
}

int module_start(void *arg) {
    // Initialize networking
    sysModuleLoad(SYSMODULE_NET);
    sysModuleLoad(SYSMODULE_NETCTL);
    netInitialize();
    netCtlInit();

    // Start HTTP thread
    plugin_running = 1;
    if (sysThreadCreate(&http_thread_id, http_thread, 0, 1000, 0x4000, THREAD_JOINABLE, "http_thread") != 0) {
        plugin_running = 0;
    }
    return SYS_PRX_RESIDENT;
}

int module_stop(void *arg) {
    plugin_running = 0;
    if (http_thread_id) {
        sysThreadJoin(http_thread_id, NULL);
    }
    netCtlTerm();
    netDeinitialize();
    return SYS_PRX_RESIDENT;
}

#include <ppu-types.h>
#include <sys/prx.h>
#include <sys/thread.h>
#include <sysmodule/sysmodule.h>
#include <net/net.h>
#include <net/netctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// Minimal test plugin: serves a simple page on http://<ps3-ip>:8080/

static volatile int plugin_running = 0;
static sys_ppu_thread_t http_thread_id;

static void http_thread(void *arg) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) return;

    int yes = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr; memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) { close(server); return; }
    if (listen(server, 4) < 0) { close(server); return; }

    while (plugin_running) {
        struct sockaddr_in caddr; socklen_t clen = sizeof(caddr);
        int client = accept(server, (struct sockaddr *)&caddr, &clen);
        if (client < 0) continue;

        const char *body = "<html><body><h1>Guitar Remap Test</h1><p>Plugin is running.</p></body></html>";
        char header[256];
        int blen = (int)strlen(body);
        int hlen = snprintf(header, sizeof(header),
                            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",
                            blen);
        if (hlen > 0) send(client, header, (size_t)hlen, 0);
        send(client, body, (size_t)blen, 0);
        close(client);
    }

    close(server);
}

int module_start(void *arg) {
    // Initialize networking
    sysModuleLoad(SYSMODULE_NET);
    sysModuleLoad(SYSMODULE_NETCTL);
    netInitialize();
    netCtlInit();

    // Start HTTP thread
    plugin_running = 1;
    if (sysThreadCreate(&http_thread_id, http_thread, 0, 1000, 0x4000, THREAD_JOINABLE, "http_thread") != 0) {
        plugin_running = 0;
    }
    return SYS_PRX_RESIDENT;
}

int module_stop(void *arg) {
    plugin_running = 0;
    if (http_thread_id) {
        sysThreadJoin(http_thread_id, NULL);
    }
    netCtlTerm();
    netDeinitialize();
    return SYS_PRX_RESIDENT;
}

#include <ppu-types.h>
#include <sys/prx.h>
#include <sys/thread.h>
#include <sysmodule/sysmodule.h>
#include <net/net.h>
#include <net/netctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

// Minimal test plugin: serves a simple page on http://<ps3-ip>:8080/

static volatile int plugin_running = 0;
static sys_ppu_thread_t http_thread_id;

static void http_thread(void *arg) {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) return;

    int yes = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

    struct sockaddr_in addr; memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8080);
    if (bind(server, (struct sockaddr *)&addr, sizeof(addr)) < 0) { close(server); return; }
    if (listen(server, 4) < 0) { close(server); return; }

    while (plugin_running) {
        struct sockaddr_in caddr; socklen_t clen = sizeof(caddr);
        int client = accept(server, (struct sockaddr *)&caddr, &clen);
        if (client < 0) continue;

        const char *body = "<html><body><h1>Guitar Remap Test</h1><p>Plugin is running.</p></body></html>";
        char header[256];
        int blen = (int)strlen(body);
        int hlen = snprintf(header, sizeof(header),
                            "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",
                            blen);
        if (hlen > 0) send(client, header, (size_t)hlen, 0);
        send(client, body, (size_t)blen, 0);
        close(client);
    }

    close(server);
}

int module_start(void *arg) {
    // Initialize networking
    sysModuleLoad(SYSMODULE_NET);
    sysModuleLoad(SYSMODULE_NETCTL);
    netInitialize();
    netCtlInit();

    // Start HTTP thread
    plugin_running = 1;
    if (sysThreadCreate(&http_thread_id, http_thread, 0, 1000, 0x4000, THREAD_JOINABLE, "http_thread") != 0) {
        plugin_running = 0;
    }
    return SYS_PRX_RESIDENT;
}

int module_stop(void *arg) {
    plugin_running = 0;
    if (http_thread_id) {
        sysThreadJoin(http_thread_id, NULL);
    }
    netCtlTerm();
    netDeinitialize();
    return SYS_PRX_RESIDENT;
}

#include "guitar_remap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/net.h>
#include <net/netctl.h>

// PS3 SDK (PSL1GHT) includes
#include <io/pad.h>
#include <sysmodule/sysmodule.h>
#include <sys/prx.h>
#include <ppu-types.h>
#include <sys/thread.h>
#include <sys/systime.h>

// Include web interface functions
extern int start_web_interface(void);
extern void stop_web_interface(void);

// Global variables
button_mapping_t button_mappings[MAX_BUTTONS];
int mapping_count = 0;
int plugin_running = 0;
sys_ppu_thread_t remap_thread;
interface_state_t interface_state;

// Load configuration from file
int load_config(void) {
    FILE *fp;
    char line[MAX_CONFIG_LINE];
    char *key, *value;
    
    fp = fopen(CONFIG_FILE, "r");
    if (!fp) {
        // Create default configuration
        create_default_config();
        fp = fopen(CONFIG_FILE, "r");
        if (!fp) return -1;
    }
    
    mapping_count = 0;
    
    while (fgets(line, sizeof(line), fp) && mapping_count < MAX_BUTTONS) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;
        
        // Parse key=value pairs
        key = strtok(line, "=");
        value = strtok(NULL, "=");
        
        if (key && value) {
            // Remove whitespace
            while (*key == ' ' || *key == '\t') key++;
            while (*value == ' ' || *value == '\t') value++;
            
            // Remove newline from value
            char *newline = strchr(value, '\n');
            if (newline) *newline = '\0';
            newline = strchr(value, '\r');
            if (newline) *newline = '\0';
            
            int guitar_btn = parse_button_name(key);
            int ps3_btn = parse_ps3_button(value);
            
            if (guitar_btn >= 0 && ps3_btn >= 0) {
                button_mappings[mapping_count].guitar_button = guitar_btn;
                button_mappings[mapping_count].ps3_button = ps3_btn;
                strncpy(button_mappings[mapping_count].name, key, 31);
                mapping_count++;
            }
        }
    }
    
    fclose(fp);
    return 0;
}

// Parse guitar button name to button code
int parse_button_name(const char *name) {
    if (strcmp(name, "STRUM_UP") == 0) return GUITAR_STRUM_UP;
    if (strcmp(name, "STRUM_DOWN") == 0) return GUITAR_STRUM_DOWN;
    if (strcmp(name, "FRET_GREEN") == 0) return GUITAR_FRET_GREEN;
    if (strcmp(name, "FRET_RED") == 0) return GUITAR_FRET_RED;
    if (strcmp(name, "FRET_YELLOW") == 0) return GUITAR_FRET_YELLOW;
    if (strcmp(name, "FRET_BLUE") == 0) return GUITAR_FRET_BLUE;
    if (strcmp(name, "FRET_ORANGE") == 0) return GUITAR_FRET_ORANGE;
    if (strcmp(name, "WHAMMY") == 0) return GUITAR_WHAMMY;
    if (strcmp(name, "STAR_POWER") == 0) return GUITAR_STAR_POWER;
    return -1;
}

// Parse PS3 button name to button code
int parse_ps3_button(const char *name) {
    if (strcmp(name, "CROSS") == 0) return PS3_CROSS;
    if (strcmp(name, "SQUARE") == 0) return PS3_SQUARE;
    if (strcmp(name, "TRIANGLE") == 0) return PS3_TRIANGLE;
    if (strcmp(name, "CIRCLE") == 0) return PS3_CIRCLE;
    if (strcmp(name, "L1") == 0) return PS3_L1;
    if (strcmp(name, "L2") == 0) return PS3_L2;
    if (strcmp(name, "R1") == 0) return PS3_R1;
    if (strcmp(name, "R2") == 0) return PS3_R2;
    if (strcmp(name, "SELECT") == 0) return PS3_SELECT;
    if (strcmp(name, "START") == 0) return PS3_START;
    if (strcmp(name, "DPAD_UP") == 0) return PS3_DPAD_UP;
    if (strcmp(name, "DPAD_DOWN") == 0) return PS3_DPAD_DOWN;
    if (strcmp(name, "DPAD_LEFT") == 0) return PS3_DPAD_LEFT;
    if (strcmp(name, "DPAD_RIGHT") == 0) return PS3_DPAD_RIGHT;
    return -1;
}

// Create default configuration file
void create_default_config(void) {
    FILE *fp = fopen(CONFIG_FILE, "w");
    if (!fp) return;
    
    fprintf(fp, "# Guitar Controller Remapping Configuration\n");
    fprintf(fp, "# Format: GUITAR_BUTTON=PS3_BUTTON\n\n");
    fprintf(fp, "STRUM_UP=DPAD_UP\n");
    fprintf(fp, "STRUM_DOWN=DPAD_DOWN\n");
    fprintf(fp, "FRET_GREEN=CROSS\n");
    fprintf(fp, "FRET_RED=SQUARE\n");
    fprintf(fp, "FRET_YELLOW=TRIANGLE\n");
    fprintf(fp, "FRET_BLUE=CIRCLE\n");
    fprintf(fp, "FRET_ORANGE=L1\n");
    fprintf(fp, "WHAMMY=R2\n");
    fprintf(fp, "STAR_POWER=L2\n");
    fprintf(fp, "SELECT=SELECT\n");
    fprintf(fp, "START=START\n");
    
    fclose(fp);
}

// Check if controller is a guitar controller
int is_guitar_controller(const char *name) {
    if (!name) return 0;
    
    // Check for common guitar controller identifiers
    if (strstr(name, "guitar") || strstr(name, "Guitar") ||
        strstr(name, "GUITAR") || strstr(name, "Rock Band") ||
        strstr(name, "Guitar Hero") || strstr(name, "RB") ||
        strstr(name, "GH")) {
        return 1;
    }
    return 0;
}

// Get button name from button code
const char* get_button_name(uint32_t button_code) {
    if (button_code & PS3_CROSS) return "CROSS";
    if (button_code & PS3_SQUARE) return "SQUARE";
    if (button_code & PS3_TRIANGLE) return "TRIANGLE";
    if (button_code & PS3_CIRCLE) return "CIRCLE";
    if (button_code & PS3_L1) return "L1";
    if (button_code & PS3_L2) return "L2";
    if (button_code & PS3_R1) return "R1";
    if (button_code & PS3_R2) return "R2";
    if (button_code & PS3_SELECT) return "SELECT";
    if (button_code & PS3_START) return "START";
    if (button_code & PS3_DPAD_UP) return "DPAD_UP";
    if (button_code & PS3_DPAD_DOWN) return "DPAD_DOWN";
    if (button_code & PS3_DPAD_LEFT) return "DPAD_LEFT";
    if (button_code & PS3_DPAD_RIGHT) return "DPAD_RIGHT";
    return "UNKNOWN";
}

// Add button press to history
void add_button_to_history(int controller_port, uint32_t button_code) {
    if (controller_port < 0 || controller_port >= MAX_CONTROLLERS) return;
    
    controller_info_t *controller = &interface_state.controllers[controller_port];
    controller->button_history[controller->history_index] = button_code;
    controller->history_index = (controller->history_index + 1) % MAX_BUTTON_HISTORY;
}

// Update controller information
void update_controller_info(void) {
    CellPadData pad_data;
    
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        controller_info_t *controller = &interface_state.controllers[i];
        
        // Check if controller is connected
        if (cellPadGetData(i, &pad_data) == CELL_PAD_OK) {
            if (!controller->connected) {
                controller->connected = 1;
                controller->port = i;
                strncpy(controller->name, "Generic Controller", 63);
                controller->is_guitar_controller = 0;
                controller->history_index = 0;
                memset(controller->button_history, 0, sizeof(controller->button_history));
            }
            
            // Update button states
            controller->previous_buttons = controller->current_buttons;
            controller->current_buttons = pad_data.button[0] | (pad_data.button[1] << 8) | 
                                        (pad_data.button[2] << 16) | (pad_data.button[3] << 24);
            
            // Check for new button presses
            uint32_t new_buttons = controller->current_buttons & ~controller->previous_buttons;
            if (new_buttons) {
                add_button_to_history(i, new_buttons);
            }
        } else {
            controller->connected = 0;
        }
    }
}

// Draw the interface
void draw_interface(void) {
    // Clear screen (simple approach)
    printf("\033[2J\033[H"); // Clear screen and move cursor to top
    
    printf("==========================================\n");
    printf("  PS3 HEN Guitar Controller Remapping\n");
    printf("==========================================\n\n");
    
    printf("Connected Controllers:\n");
    printf("----------------------\n");
    
    int connected_count = 0;
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        controller_info_t *controller = &interface_state.controllers[i];
        if (controller->connected) {
            connected_count++;
            printf("Port %d: %s %s\n", 
                   controller->port, 
                   controller->name,
                   controller->is_guitar_controller ? "[GUITAR]" : "");
            
            // Show current button state
            if (controller->current_buttons) {
                printf("  Current: %s (0x%08X)\n", 
                       get_button_name(controller->current_buttons),
                       controller->current_buttons);
            }
            
            // Show recent button history
            printf("  Recent presses: ");
            int history_count = 0;
            for (int j = 0; j < MAX_BUTTON_HISTORY && history_count < 5; j++) {
                int idx = (controller->history_index - 1 - j + MAX_BUTTON_HISTORY) % MAX_BUTTON_HISTORY;
                if (controller->button_history[idx]) {
                    printf("%s ", get_button_name(controller->button_history[idx]));
                    history_count++;
                }
            }
            printf("\n\n");
        }
    }
    
    if (connected_count == 0) {
        printf("No controllers connected.\n\n");
    }
    
    printf("Controls:\n");
    printf("  Press any button to see input detection\n");
    printf("  Press START to exit interface\n");
    printf("  Press SELECT to refresh\n\n");
    
    printf("Plugin Status: %s\n", plugin_running ? "ACTIVE" : "INACTIVE");
    printf("Mappings loaded: %d\n", mapping_count);
    printf("Web Interface: http://your-ps3-ip:8080\n");
}

// Handle interface input
void handle_interface_input(void) {
    // Check for START button to exit
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        controller_info_t *controller = &interface_state.controllers[i];
        if (controller->connected) {
            uint32_t new_buttons = controller->current_buttons & ~controller->previous_buttons;
            if (new_buttons & PS3_START) {
                interface_state.interface_active = 0;
                return;
            }
        }
    }
}

// Interface thread
void interface_thread(void *arg) {
    while (interface_state.interface_active) {
        update_controller_info();
        draw_interface();
        handle_interface_input();
        
        // Sleep for interface update rate
        sys_timer_usleep(1000000 / INTERFACE_UPDATE_RATE); // Convert Hz to microseconds
    }
    
    return;
}

// Main remapping thread
void remap_controller_thread(void *arg) {
    CellPadData pad_data;
    uint32_t original_buttons, remapped_buttons;
    
    while (plugin_running) {
        // Read controller input
        if (cellPadGetData(0, &pad_data) == CELL_PAD_OK) {
            original_buttons = pad_data.button[0] | (pad_data.button[1] << 8) | 
                             (pad_data.button[2] << 16) | (pad_data.button[3] << 24);
            
            // Apply remapping
            remap_buttons(&original_buttons, &remapped_buttons);
            
            // Write remapped buttons back
            pad_data.button[0] = remapped_buttons & 0xFF;
            pad_data.button[1] = (remapped_buttons >> 8) & 0xFF;
            pad_data.button[2] = (remapped_buttons >> 16) & 0xFF;
            pad_data.button[3] = (remapped_buttons >> 24) & 0xFF;
        }
        
        // Sleep for a short time
        sys_timer_usleep(1000); // 1ms
    }
    
    return;
}

// Apply button remapping
void remap_buttons(uint32_t *input, uint32_t *output) {
    *output = *input;
    
    for (int i = 0; i < mapping_count; i++) {
        if (*input & button_mappings[i].guitar_button) {
            *output |= button_mappings[i].ps3_button;
        }
    }
}

// Plugin entry point (PSL1GHT build does not require SYS_MODULE_* macros)

// Module start function
int module_start(void *arg) {
    // Initialize PS3 SDK
    cellSysmoduleLoadModule(CELL_SYSMODULE_PAD);
    sysModuleLoad(SYSMODULE_NET);
    sysModuleLoad(SYSMODULE_NETCTL);
    netInitialize();
    netCtlInit();
    
    // Initialize interface state
    memset(&interface_state, 0, sizeof(interface_state));
    interface_state.interface_active = 1;
    
    // Load configuration
    if (load_config() < 0) {
        return SYS_PRX_RESIDENT;
    }
    
    // Start remapping thread
    plugin_running = 1;
    if (sys_ppu_thread_create(&remap_thread, remap_controller_thread, 0, 
                             THREAD_PRIO, THREAD_STACK_SIZE, 
                             SYS_PPU_THREAD_CREATE_JOINABLE, "remap_thread") != 0) {
        return SYS_PRX_RESIDENT;
    }
    
    // Start interface thread
    if (sys_ppu_thread_create(&interface_state.interface_thread_id, interface_thread, 0,
                             THREAD_PRIO, THREAD_STACK_SIZE,
                             SYS_PPU_THREAD_CREATE_JOINABLE, "interface_thread") != 0) {
        return SYS_PRX_RESIDENT;
    }
    
    // Start web interface
    if (start_web_interface() == 0) {
        printf("Web interface started successfully\n");
    } else {
        printf("Failed to start web interface\n");
    }
    
    return SYS_PRX_RESIDENT;
}

// Module stop function
int module_stop(void *arg) {
    plugin_running = 0;
    interface_state.interface_active = 0;
    
    // Stop web interface
    stop_web_interface();
    
    // Wait for threads to finish
    if (remap_thread) {
        sys_ppu_thread_join(remap_thread, NULL);
    }
    
    if (interface_state.interface_thread_id) {
        sys_ppu_thread_join(interface_state.interface_thread_id, NULL);
    }
    
    netCtlTerm();
    netDeinitialize();
    return SYS_PRX_RESIDENT;
} 