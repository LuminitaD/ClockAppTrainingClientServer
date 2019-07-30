#include "myApp_generated.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
#include <dbus/dbus-glib.h>
#include <stdlib.h> /* exit, EXIT_FAILURE */

void getAlarmStatus(char **out_status_message);
void setAlarmStatus(int arg_status);
void setAlarmTime(int hour, int min);
void setTime(int hour, int min);
void init();
void deInit();
bool signal_function(bool (*Callback)(void));