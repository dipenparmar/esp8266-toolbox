#include <ip_addr.h> /* Must be included before espconn.h */

#include <espconn.h>
#include <stdint.h>

typedef struct {
    /* SMTP_STATE_READY is 1 to ensure smtp_init_*() succeeded */
    #define SMTP_STATE_READY 1
    #define SMTP_STATE_DNS_DONE 2
    #define SMTP_STATE_DNS_FAIL 3
    uint8_t state;

    char host[64];
    ip_addr_t ip;
    uint16_t port;

    char user[64];
    char pass[64];
    char from[64];

    /* Shared for both DNS and TCP */
    struct espconn conn;
    esp_tcp tcp;
    esp_udp udp;
} Smtp;

extern Smtp smtp;