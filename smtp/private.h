#ifndef SMTP_PRIVATE_H
#define SMTP_PRIVATE_H

#include <ip_addr.h>
#include <espconn.h>

typedef struct {
    char host[64];
    uint16_t port;
    char user[64];
    char pass[64];
} SmtpServer;

extern SmtpServer smtp_server;

typedef struct {
    #define SMTP_STATE_FAILED  -1
    #define SMTP_STATE_READY    1
    #define SMTP_STATE_RESOLVE  2
    #define SMTP_STATE_CONNECT  3
    int8_t state;

    /* Used for both DNS and TCP */
    struct espconn conn;
    esp_tcp tcp;

    os_timer_t timer;

    uint8_t inbuf[2*1024];
    uint16_t inbufused;

    uint8_t outbuf[1024];
    uint16_t outbufused;

    uint8_t from[128];
    uint8_t to[128];
    uint8_t subj[128];
    uint8_t body[512];
} SmtpState;

#endif
