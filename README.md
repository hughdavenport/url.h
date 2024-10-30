# url.h: A URL stb-style header only library

[![patreon](https://img.shields.io/badge/patreon-FF5441?style=for-the-badge&logo=Patreon)](https://www.patreon.com/hughdavenport)
[![youtube](https://img.shields.io/badge/youtube-FF0000?style=for-the-badge&logo=youtube)](https://www.youtube.com/watch?v=dqw7B6eR9P8&list=PL5r5Q39GjMDfetFdGmnhjw1svsALW1HIY)

This repo contains a [stb-style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt) header only library. You only need the [url.h](https://github.com/hughdavenport/url.h/raw/refs/heads/main/url.h) file.

This was developed during a video series where I implement bittorrent from scratch, where [SHA-1](https://github.com/hughdavenport/sha1.h), and URL parsing is a necessary component.

To use the library, `#define URL_IMPLEMENTATION` exactly once (in your main.c may be a good place). You can `#include` the file as many times as you like.

An example file is shown below.
```c
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
```

Test by saving the above to a file `example.c` and then running this
```sh
cc example.c
./a.out http://example.com
```

It should give you the raw output of (the first 8192 bytes of) an HTTP response to that server.

I don't really guarantee the security of this, yet. Please feel free to try find bugs and report them.

Please leave any comments about what you liked. Feel free to suggest any features or improvements.

You are welcome to support me financially if you would like on my [patreon](https://www.patreon.com/hughdavenport).
