# esp8266-toolbox
Motley of servers and clients for the ESP8266 with signed OTA updates

# Completed
- HTTP server framework
  - Multiple simultaneous clients
  - GET and POST methods
- SHA256 implementation
- Push-based OTA updates
  - Triggered by HTTP POST on /fota/push

# Forthcoming
- Signed OTA updates
- Pull-based OTA updates
  - Scheduled checks every six hours
- Misc. sensor drivers
- MQTT client framework
- SMTP client framework

# OTA updates
An unencoded binary is uploaded by HTTP POST to /fota/push.  The binary gets
written to the unused partition in flash while its hash is calculated.  When done
it is read from flash and its hash is recalculated to verify the write integrity,
if successful an HTTP 202 Accepted response is returned and the system is
rebooted into the new application.

The Makefile target fota shows how this can be done with curl.

# Quick start
- Install the toolchain and SDK: https://github.com/pfalcon/esp-open-sdk
- Modify the variables at the top of the Makefile if necessary
- Run `make` to build the application binary
- Breadboard a circuit (refer to /hw for a development schematic)
- Power the circuit and connect via a USB-UART bridge
- Put the ESP8266 in flash mode by holding GPIO0 low during boot
- Run `make flash` to flash the bins (as root or user with appropriate perms)
- The default WiFi SSID is `esp-<system id in hex>`
- The default WiFi password is in /config.h
- The default IP address is 192.168.4.1
- The applications uart0.py and uart0/uart0 are provided for debugging output
  - uart0/uart0 is for USB-UART bridges that don't inherently support
    non-standard baudrates

# Coding style
- 80 character line limits (for multiple horizontally-split editor views)
- Prefer to put function-scope variables at the top of the function; to help
  facilitate calculation of stack space used by the function

# License
This software is freely available for non-commerical use, commerical use requires
an expressed agreement from the author. The preceding clause must be included in
all derivative software developed with commerical rights retained by the author
of this software.

The author takes no responsibility for the consequences of the use of this
software.

Use of the software in any form indicates acknowledgement of the licensing terms.

Copyright (c) 2017 J. O. Makar <jomakar@gmail.com>
