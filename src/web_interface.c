#include "guitar_remap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/thread.h>
#include <ppu-types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// webMAN MOD integration
#define WEBMAN_PORT 80
#define WEBMAN_PATH "/guitar_remap"
#define MAX_CLIENTS 5
#define BUFFER_SIZE 2048

typedef struct {
    int socket;
    struct sockaddr_in address;
    int active;
} web_client_t;

web_client_t web_clients[MAX_CLIENTS];
int web_server_socket = -1;
sys_ppu_thread_t web_server_thread_id;
int web_server_running = 0;

// Generate HTML page with controller information (webMAN MOD style)
void generate_html_page(char *buffer, size_t buffer_size) {
    snprintf(buffer, buffer_size,
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "    <title>Guitar Controller Remapping - webMAN MOD</title>\n"
        "    <meta charset='utf-8'>\n"
        "    <style>\n"
        "        body { font-family: Arial, sans-serif; margin: 0; padding: 0; background: #1a1a1a; color: #ffffff; }\n"
        "        .header { background: #000000; padding: 10px 20px; border-bottom: 2px solid #007acc; }\n"
        "        .header h1 { margin: 0; color: #007acc; font-size: 24px; }\n"
        "        .container { max-width: 1200px; margin: 0 auto; padding: 20px; }\n"
        "        .status-bar { background: #333333; padding: 10px; margin: 10px 0; border-radius: 5px; }\n"
        "        .status-bar .status { display: inline-block; margin-right: 20px; }\n"
        "        .status.active { color: #28a745; }\n"
        "        .status.inactive { color: #dc3545; }\n"
        "        .controller-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(400px, 1fr)); gap: 20px; margin: 20px 0; }\n"
        "        .controller-card { background: #2a2a2a; border: 1px solid #444; border-radius: 8px; padding: 20px; }\n"
        "        .controller-card.guitar { border-left: 5px solid #28a745; }\n"
        "        .controller-card.regular { border-left: 5px solid #007acc; }\n"
        "        .controller-title { font-size: 18px; font-weight: bold; margin-bottom: 15px; color: #007acc; }\n"
        "        .button-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(80px, 1fr)); gap: 8px; margin: 15px 0; }\n"
        "        .button-display { display: inline-block; padding: 8px 12px; background: #444; color: white; border-radius: 4px; text-align: center; font-size: 12px; }\n"
        "        .button-active { background: #28a745; }\n"
        "        .button-pressed { background: #ffc107; color: #000; }\n"
        "        .history { background: #333; padding: 10px; border-radius: 4px; margin-top: 15px; }\n"
        "        .history-title { font-weight: bold; margin-bottom: 10px; color: #007acc; }\n"
        "        .nav-buttons { margin: 20px 0; }\n"
        "        .nav-btn { background: #007acc; color: white; border: none; padding: 10px 20px; border-radius: 5px; cursor: pointer; margin-right: 10px; }\n"
        "        .nav-btn:hover { background: #0056b3; }\n"
        "        .config-section { background: #2a2a2a; border: 1px solid #444; border-radius: 8px; padding: 20px; margin: 20px 0; }\n"
        "        .config-title { font-size: 18px; font-weight: bold; margin-bottom: 15px; color: #007acc; }\n"
        "        .config-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 20px; }\n"
        "        .config-list { background: #333; padding: 15px; border-radius: 4px; }\n"
        "        .config-list ul { margin: 0; padding-left: 20px; }\n"
        "        .config-list li { margin: 5px 0; }\n"
        "        .footer { text-align: center; margin-top: 30px; padding: 20px; color: #666; border-top: 1px solid #444; }\n"
        "        .auto-refresh { color: #28a745; font-weight: bold; }\n"
        "    </style>\n"
        "    <script>\n"
        "        function refreshPage() {\n"
        "            location.reload();\n"
        "        }\n"
        "        function goToWebMAN() {\n"
        "            window.location.href = '/'; // Go back to webMAN MOD main page\n"
        "        }\n"
        "        // Auto-refresh every 3 seconds\n"
        "        setInterval(refreshPage, 3000);\n"
        "    </script>\n"
        "</head>\n"
        "<body>\n"
        "    <div class='header'>\n"
        "        <h1>🎸 Guitar Controller Remapping - webMAN MOD Integration</h1>\n"
        "    </div>\n"
        "    \n"
        "    <div class='container'>\n"
        "        <div class='status-bar'>\n"
        "            <span class='status %s'><strong>Plugin Status:</strong> %s</span>\n"
        "            <span class='status'><strong>Mappings Loaded:</strong> %d</span>\n"
        "            <span class='status'><strong>Controllers Connected:</strong> %d</span>\n"
        "            <span class='auto-refresh'>🔄 Auto-refreshing every 3 seconds</span>\n"
        "        </div>\n"
        "        \n"
        "        <div class='nav-buttons'>\n"
        "            <button class='nav-btn' onclick='refreshPage()'>🔄 Refresh</button>\n"
        "            <button class='nav-btn' onclick='goToWebMAN()'>🏠 Back to webMAN MOD</button>\n"
        "        </div>\n",
        plugin_running ? "active" : "inactive",
        plugin_running ? "ACTIVE" : "INACTIVE",
        mapping_count,
        0 // We'll calculate this
    );
    
    int connected_count = 0;
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        controller_info_t *controller = &interface_state.controllers[i];
        if (controller->connected) {
            connected_count++;
        }
    }
    
    // Update connected count in the status bar
    char *status_pos = strstr(buffer, "<strong>Controllers Connected:</strong> 0");
    if (status_pos) {
        sprintf(status_pos, "<strong>Controllers Connected:</strong> %d", connected_count);
    }
    
    // Add controller cards
    size_t current_len = strlen(buffer);
    snprintf(buffer + current_len, buffer_size - current_len,
        "        \n"
        "        <h2>🎮 Connected Controllers</h2>\n"
        "        <div class='controller-grid'>\n"
    );
    
    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        controller_info_t *controller = &interface_state.controllers[i];
        if (controller->connected) {
            char controller_class[32];
            snprintf(controller_class, sizeof(controller_class), 
                    controller->is_guitar_controller ? "controller-card guitar" : "controller-card regular");
            
            char *controller_type = controller->is_guitar_controller ? "🎸 Guitar Controller" : "🎮 Regular Controller";
            
            current_len = strlen(buffer);
            snprintf(buffer + current_len, buffer_size - current_len,
                "            <div class='%s'>\n"
                "                <div class='controller-title'>Port %d: %s %s</div>\n"
                "                <p><strong>Name:</strong> %s</p>\n",
                controller_class, controller->port, controller_type, 
                controller->is_guitar_controller ? "[GUITAR]" : "",
                controller->name
            );
            
            // Show current button state
            if (controller->current_buttons) {
                current_len = strlen(buffer);
                snprintf(buffer + current_len, buffer_size - current_len,
                    "                <p><strong>Current Buttons:</strong></p>\n"
                    "                <div class='button-grid'>\n"
                    "                    <span class='button-display button-active'>%s</span>\n"
                    "                </div>\n"
                    "                <p><small>Raw: 0x%08X</small></p>\n",
                    get_button_name(controller->current_buttons), controller->current_buttons
                );
            }
            
            // Show recent button history
            current_len = strlen(buffer);
            snprintf(buffer + current_len, buffer_size - current_len,
                "                <div class='history'>\n"
                "                    <div class='history-title'>Recent Button Presses:</div>\n"
                "                    <div class='button-grid'>\n"
            );
            
            int history_count = 0;
            for (int j = 0; j < MAX_BUTTON_HISTORY && history_count < 8; j++) {
                int idx = (controller->history_index - 1 - j + MAX_BUTTON_HISTORY) % MAX_BUTTON_HISTORY;
                if (controller->button_history[idx]) {
                    current_len = strlen(buffer);
                    snprintf(buffer + current_len, buffer_size - current_len,
                        "                        <span class='button-display button-pressed'>%s</span>\n",
                        get_button_name(controller->button_history[idx])
                    );
                    history_count++;
                }
            }
            
            current_len = strlen(buffer);
            snprintf(buffer + current_len, buffer_size - current_len,
                "                    </div>\n"
                "                </div>\n"
                "            </div>\n"
            );
        }
    }
    
    if (connected_count == 0) {
        current_len = strlen(buffer);
        snprintf(buffer + current_len, buffer_size - current_len,
            "            <div class='controller-card'>\n"
            "                <div class='controller-title'>No Controllers Connected</div>\n"
            "                <p>Please connect a guitar controller to see input detection.</p>\n"
            "            </div>\n"
        );
    }
    
    current_len = strlen(buffer);
    snprintf(buffer + current_len, buffer_size - current_len,
        "        </div>\n"
        "        \n"
        "        <div class='config-section'>\n"
        "            <div class='config-title'>📋 Button Mapping Reference</div>\n"
        "            <div class='config-grid'>\n"
        "                <div class='config-list'>\n"
        "                    <h4>🎸 Guitar Controller Buttons:</h4>\n"
        "                    <ul>\n"
        "                        <li><strong>STRUM_UP/DOWN:</strong> Strum bar up/down</li>\n"
        "                        <li><strong>FRET_GREEN:</strong> Green fret button</li>\n"
        "                        <li><strong>FRET_RED:</strong> Red fret button</li>\n"
        "                        <li><strong>FRET_YELLOW:</strong> Yellow fret button</li>\n"
        "                        <li><strong>FRET_BLUE:</strong> Blue fret button</li>\n"
        "                        <li><strong>FRET_ORANGE:</strong> Orange fret button</li>\n"
        "                        <li><strong>WHAMMY:</strong> Whammy bar</li>\n"
        "                        <li><strong>STAR_POWER:</strong> Star power button</li>\n"
        "                    </ul>\n"
        "                </div>\n"
        "                <div class='config-list'>\n"
        "                    <h4>🎮 PS3 Controller Buttons:</h4>\n"
        "                    <ul>\n"
        "                        <li><strong>CROSS:</strong> X button</li>\n"
        "                        <li><strong>SQUARE:</strong> Square button</li>\n"
        "                        <li><strong>TRIANGLE:</strong> Triangle button</li>\n"
        "                        <li><strong>CIRCLE:</strong> Circle button</li>\n"
        "                        <li><strong>L1/L2:</strong> Left shoulder buttons</li>\n"
        "                        <li><strong>R1/R2:</strong> Right shoulder buttons</li>\n"
        "                        <li><strong>SELECT/START:</strong> Menu buttons</li>\n"
        "                        <li><strong>DPAD_*:</strong> Directional pad</li>\n"
        "                    </ul>\n"
        "                </div>\n"
        "            </div>\n"
        "        </div>\n"
        "        \n"
        "        <div class='footer'>\n"
        "            <p>PS3 HEN Guitar Controller Remapping Plugin v%s - Integrated with webMAN MOD</p>\n"
        "            <p>Press any button on your guitar controller to see real-time input detection</p>\n"
        "        </div>\n"
        "    </div>\n"
        "</body>\n"
        "</html>\n",
        PLUGIN_VERSION
    );
}

// Handle web client connection
static void handle_web_client(web_client_t *client) {
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE * 2];
    
    // Generate HTML response
    generate_html_page(response, sizeof(response));
    
    // Send HTTP response
    snprintf(buffer, sizeof(buffer),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: %zu\r\n"
        "Connection: close\r\n"
        "Cache-Control: no-cache, no-store, must-revalidate\r\n"
        "Pragma: no-cache\r\n"
        "Expires: 0\r\n"
        "\r\n",
        strlen(response)
    );
    
    send(client->socket, buffer, strlen(buffer), 0);
    send(client->socket, response, strlen(response), 0);
    
    // Close connection
    close(client->socket);
    client->active = 0;
}

// Web server thread (integrated with webMAN MOD)
void web_server_main(void *arg) {
    struct sockaddr_in server_addr;
    int opt = 1;
    
    // Create socket
    web_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (web_server_socket < 0) {
        printf("Failed to create web server socket\n");
        return;
    }
    
    // Set socket options
    setsockopt(web_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    // Bind socket to webMAN MOD port (80)
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(WEBMAN_PORT);
    
    if (bind(web_server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("Failed to bind to port %d (webMAN MOD may be using it)\n", WEBMAN_PORT);
        printf("Falling back to port 8080 for standalone mode\n");
        
        // Fallback to port 8080 if webMAN MOD is using port 80
        close(web_server_socket);
        web_server_socket = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(web_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        
        server_addr.sin_port = htons(8080);
        if (bind(web_server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            close(web_server_socket);
            printf("Failed to bind to port 8080 as well\n");
            return;
        }
        
        printf("Web interface started on port 8080 (standalone mode)\n");
        printf("Access at: http://your-ps3-ip:8080%s\n", WEBMAN_PATH);
    } else {
        printf("Web interface integrated with webMAN MOD on port %d\n", WEBMAN_PORT);
        printf("Access at: http://your-ps3-ip%s\n", WEBMAN_PATH);
    }
    
    // Listen for connections
    if (listen(web_server_socket, MAX_CLIENTS) < 0) {
        close(web_server_socket);
        return;
    }
    
    while (web_server_running) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        // Accept new connection
        int client_socket = accept(web_server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            continue;
        }
        
        // Find free client slot
        int client_index = -1;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (!web_clients[i].active) {
                client_index = i;
                break;
            }
        }
        
        if (client_index >= 0) {
            web_clients[client_index].socket = client_socket;
            web_clients[client_index].address = client_addr;
            web_clients[client_index].active = 1;
            
            // Handle client
            handle_web_client(&web_clients[client_index]);
        } else {
            close(client_socket);
        }
    }
    
    close(web_server_socket);
    return;
}

// Start web interface
int start_web_interface(void) {
    web_server_running = 1;
    
    // Initialize client array
    memset(web_clients, 0, sizeof(web_clients));
    
    // Start web server thread
    if (sys_ppu_thread_create(&web_server_thread_id, web_server_main, 0,
                             THREAD_PRIO, THREAD_STACK_SIZE,
                             SYS_PPU_THREAD_CREATE_JOINABLE, "web_server") != 0) {
        return -1;
    }
    
    return 0;
}

// Stop web interface
void stop_web_interface(void) {
    web_server_running = 0;
    
    // Close all client connections
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (web_clients[i].active) {
            close(web_clients[i].socket);
            web_clients[i].active = 0;
        }
    }
    
    // Wait for web server thread to finish
    if (web_server_thread_id) {
        sys_ppu_thread_join(web_server_thread_id, NULL);
    }
} 