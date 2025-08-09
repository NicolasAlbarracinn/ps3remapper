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

        const char *body = "<html><body><h1>Minimal Test</h1><p>Plugin is running on port 8080.</p></body></html>";
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
    sysModuleLoad(SYSMODULE_NET);
    sysModuleLoad(SYSMODULE_NETCTL);
    netInitialize();
    netCtlInit();

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


