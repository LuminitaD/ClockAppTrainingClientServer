#include "clientProxyLibrary.h"

bool theCallBack()
{
	printf("Ring signal - Inside Callback \n");
	return 1;
}


void* menu(void * data)
{
	int option;
	bool running = true;
	while(running)
	{
		printf("\n");
		printf("\n 1.Set time");
		printf("\n 2.Set alarm time");
		printf("\n 3.Set alarm status");
		printf("\n 4.Display alarm status");
		printf("\n 5.Exit");
		printf("\n \n Your option between 1 and 5 is: ");
		scanf("%d", &option);
		switch(option)
		{
			int hour;
			int min;
			case 1:
			{
				printf("\n    hour = ");
				scanf("%d", &hour);
				if ((hour < 0 ) && (hour > 23))
				{
					printf("\n Invalid hour");
					break;
				}
				printf("    min = ");
				scanf("%d", &min);
				if ((min < 0 ) && (min > 59))
				{
					printf("\n Invalid minute");
					break;
				}
				setTime(hour, min);
				break;
			}
			case 2:
			{
				printf("\n    hour = ");
				scanf("%d", &hour);
				if ((hour < 0 ) && (hour > 23))
				{
					printf("\n Invalid hour");
					break;
				}
				printf("    min = ");
				scanf("%d", &min);
				if ((min < 0 ) && (min > 59))
				{
					printf("\n Invalid minute");
					break;
				}
				setAlarmTime(hour, min);
				break;
			}
			case 3:
			{
				int status = 0;
				printf("\n    new status = ");
				scanf("%d", &status);
				setAlarmStatus(status);
				break;
			}
			case 4:
			{
				char *out_status_message = (char *) malloc(100);
				getAlarmStatus(&out_status_message);
				printf("\n %s", out_status_message);
				free (out_status_message);
				break;
			}
			case 5:
			{
				g_main_loop_quit((GMainLoop*)data);
				running = false;
				break;
			}
			default:
			{
				printf("\n Invalid option!!");
				break;
			}
		}
	}
	g_thread_exit(NULL);
	return NULL;
}

int main(int argc, char** argv)
{
	GMainLoop* mainLoop;
	init();
	mainLoop = g_main_loop_new(NULL, FALSE);
	if (mainLoop == NULL)
	{
		printf("\n Failed to create the mainLoop");
	}

	GThread* Menuthread = g_thread_new("MenuThread",&menu, mainLoop);

	signal_function(&theCallBack);

	g_main_loop_run(mainLoop);
	printf("\n Before join");
	g_thread_join(Menuthread);
	printf("\n After join");
	deInit();
}
