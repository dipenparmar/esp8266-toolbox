#ifndef CONFIG_H
#define CONFIG_H

#include <user_interface.h>

#define SSID_PREFIX "esp"
#define SSID_PASS "l0cK*It_Dwn"

#define MAX_CONN_IN 4
#define MAX_CONN MAX_CONN_IN+2

#define HTTPD_MAX_CONN MAX_CONN_IN/2

#define HTTPD_TASK_PRIO USER_TASK_PRIO_0

/*******************************************************************************/

#define LEVEL_NOTSET    0
#define LEVEL_DEBUG    10
#define LEVEL_INFO     20
#define LEVEL_WARNING  30
#define LEVEL_ERROR    40
#define LEVEL_CRITICAL 50

#define LOG_LEVEL LEVEL_DEBUG

#define HTTPD_LOG_LEVEL LEVEL_INFO

#endif
