#include "clientProxyLibrary.h"

static MyExampleComAppTrainningAlarmClock* source;
static GDBusConnection* connection;
static GError * error = NULL;

void getAlarmStatus(char **out_status_message)
{
	my_example_com_app_trainning_alarm_clock_call_get_alarm_status_sync (source, out_status_message, NULL, &error);
}

void setAlarmStatus(int arg_status)
{
	my_example_com_app_trainning_alarm_clock_call_set_alarm_status_sync (source, arg_status, NULL, NULL, &error);
}

void setAlarmTime(int hour, int min)
{
	my_example_com_app_trainning_alarm_clock_call_set_alarm_time_sync (source, hour, min, NULL, NULL, &error);
}

void setTime(int hour, int min)
{
	my_example_com_app_trainning_alarm_clock_call_set_time_sync (source, hour, min, NULL, NULL, &error);
}

void init()
{
	gchar *addr = g_dbus_address_get_for_bus_sync(G_BUS_TYPE_SYSTEM, NULL, &error);
	connection = g_dbus_connection_new_for_address_sync
				(
				addr,
				G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT|G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION,
				NULL,
				NULL,
				&error
				);
	source = my_example_com_app_trainning_alarm_clock_proxy_new_sync
			(
				connection,
				G_DBUS_PROXY_FLAGS_NONE,
				"com.AppTrainning.AlarmClock",
				"/com/AppTrainning/AlarmClock/manager/Object",
				NULL,
				&error
			);
}

void deInit()
{
	g_object_unref(connection);
	g_object_unref(source);
}

bool signal_function(bool (*Callback)(void))
{
    printf("signal - Inside the Library\n");
    g_signal_connect(source,"ring-alarm",G_CALLBACK(Callback),&error);
    return TRUE;
}