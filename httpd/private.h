#ifndef HTTPD_PRIVATE_H
#define HTTPD_PRIVATE_H

#include <sys/param.h>
#include <sys/types.h>
#include <osapi.h>

#include "../config.h"
#include "missing-decls.h"

#define HTTPD_CRITICAL(s, ...) { \
    uint32_t t = system_get_time(); \
    \
    if (HTTPD_LOG_LEVEL <= LEVEL_CRITICAL) \
        os_printf("%u.%03u: critical: %s:%d: " s, \
                  t/1000000, (t%1000000)/1000, \
                  __FILE__, __LINE__, ##__VA_ARGS__); \
    \
    while (1) os_delay_us(1000); \
}

#define HTTPD_ERROR(s, ...) { \
    uint32_t t = system_get_time(); \
    \
    if (HTTPD_LOG_LEVEL <= LEVEL_ERROR) \
        os_printf("%u.%03u: error: %s:%d: " s, \
                  t/1000000, (t%1000000)/1000, \
                  __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define HTTPD_WARNING(s, ...) { \
    uint32_t t = system_get_time(); \
    \
    if (HTTPD_LOG_LEVEL <= LEVEL_WARNING) \
        os_printf("%u.%03u: warning: %s:%d: " s, \
                  t/1000000, (t%1000000)/1000, \
                  __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define HTTPD_INFO(s, ...) { \
    uint32_t t = system_get_time(); \
    \
    if (HTTPD_LOG_LEVEL <= LEVEL_INFO) \
        os_printf("%u.%03u: info: %s:%d: " s, \
                  t/1000000, (t%1000000)/1000, \
                  __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define HTTPD_DEBUG(s, ...) { \
    uint32_t t = system_get_time(); \
    \
    if (HTTPD_LOG_LEVEL <= LEVEL_DEBUG) \
        os_printf("%u.%03u: debug: %s:%d: " s, \
                  t/1000000, (t%1000000)/1000, \
                  __FILE__, __LINE__, ##__VA_ARGS__); \
}

typedef struct {
    uint8_t inuse;

    struct espconn *conn;

    #define HTTPD_STATE_HEADERS 0
    #define HTTPD_STATE_POSTDATA 1
    #define HTTPD_STATE_RESPONSE 2
    uint8_t state;

    #define HTTPD_METHOD_GET 0
    #define HTTPD_METHOD_POST 1
    uint8_t method;

    #define HTTPD_URL_LEN 256
    uint8_t url[HTTPD_URL_LEN];
    uint8_t host[64];

    uint8_t buf[2048];
    uint16_t bufused;

    uint32_t postused;
    uint32_t postlen;
} HttpdClient;

extern HttpdClient httpd_clients[HTTPD_MAX_CONN];

enum httpd_task_signal { HTTPD_DISCONN };

typedef struct {
    uint8_t baseurl[HTTPD_URL_LEN/2];
    int (*handler)(HttpdClient *);
} HttpdUrl;

extern const HttpdUrl httpd_urls[];
extern const size_t httpd_urlcount;

#define HTTPD_OUTBUF_MAXLEN 1024
uint8_t httpd_outbuf[HTTPD_OUTBUF_MAXLEN];
uint16_t httpd_outbuflen;

#define HTTPD_IGNORE_POSTDATA { \
    if (client->state == HTTPD_STATE_POSTDATA) { \
        size_t len = MIN(client->bufused, client->postlen - client->postused); \
        \
        client->postused += len; \
        \
        os_memmove(client->buf, client->buf + len, client->bufused - len); \
        client->bufused -= len; \
        \
        if (client->postused == client->postlen) { \
            client->state = HTTPD_STATE_RESPONSE; \
            if (client->bufused > 0) \
                HTTPD_WARNING("urls: extra bytes after post\n") \
        } \
        else \
            return 0; \
    } \
}

#define HTTPD_OUTBUF_APPEND(src) { \
    size_t srclen; \
    \
    if ((srclen = os_strlen(src)) >= sizeof(httpd_outbuf)-httpd_outbuflen) { \
        HTTPD_ERROR("urls: outbuf overflow\n") \
        return 0; \
    } \
    \
    /* Copy srclen+1 for the terminating null byte */ \
    os_strncpy((char *)httpd_outbuf+httpd_outbuflen, src, srclen+1); \
    httpd_outbuflen += srclen; \
}

int httpd_process(HttpdClient *client);

int httpd_url_404(HttpdClient *client);

int httpd_url_fota(HttpdClient *client);

#endif
