#include "log/log.h"
#include "missing-decls.h"

#include <esp_sdk_ver.h>
#include <ets_sys.h>
#include <osapi.h>

#if ESP_SDK_VERSION < 020000
    #error "ESP8266 SDK version >= 2.0.0 required"
#endif

ICACHE_FLASH_ATTR void user_init() {
    info(MAIN, "Version %s built on %s", VERSION, BUILD_DATETIME);
}
