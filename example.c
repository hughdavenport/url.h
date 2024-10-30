#define URL_IMPLEMENTATION
#include "url.h"

int main(int argc, char **argv) {
    URL url = {0};
    if (!parse_url(argv[1], argv[1] + strlen(argv[1]), &url)) {
        return 1;
    }

    int sock = connect_url(&url);
    if (sock == -1) {
        return 1;
    }

    dprintf(sock, "GET /");
    if (url.path) dprintf(sock, "%s", url.path);
    if (url.query) dprintf(sock, "?%s", url.query);
    dprintf(sock, " HTTP/1.0\r\n");

    // FIXME: This should have port, but only if present
    dprintf(sock, "Host: %s\r\n", url.host);
    dprintf(sock, "User-Agent: %s\r\n", "url.h");
    dprintf(sock, "Accept: */*\r\n");
    dprintf(sock, "\r\n");

#define BUF_SIZE 8192
    char buf[BUF_SIZE];
    int len = read(sock, buf, BUF_SIZE);
    for (int idx = 0; idx < len; idx++) {
        printf("%c", buf[idx]);
    }
}
