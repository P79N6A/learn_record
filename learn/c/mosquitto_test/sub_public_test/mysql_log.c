#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mosquitto.h>

#define mqtt_host "localhost"
#define mqtt_port 1883

#define mqtt_sub  "mqtt_lcd_sub"
#define mqtt_pub  "mqtt_lcd_pub"

static struct mosquitto *mosq;
static char run = 1;

void handle_signal(int s)
{
	mosquitto_disconnect(mosq);
	mosquitto_loop_stop(mosq, true);
	run = 0;
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	printf("Mqtt Topic %d : %s msg : %s\n", getpid(), message->topic, (char*)message->payload);
	fflush(stdout);
}

int main(int argc, char *argv[])
{
	char clientid[24];
	int rc = 0;
	int i;
	pid_t pid=0;

	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	memset(clientid, 0, 24);
	snprintf(clientid, 23, "mqtt_lcd_M_%d", getpid());

	/* fork childs */
	for(i = 0;i < 10; i++) {
		pid = fork();
		if(pid <= (pid_t) 0) {
			/* child process or error*/
			sleep(1); /* make childs faster */
			memset(clientid, 0, 24);
			snprintf(clientid, 23, "mqtt_lcd_c_%d", getpid());
			break;
		}
	}

	if (pid < (pid_t) 0) {
		printf("Fork error!!\n\r");
		return 1;
	}

	mosquitto_lib_init();
	mosq = mosquitto_new(clientid, true, NULL);

	if(mosq) {
		mosquitto_message_callback_set(mosq, message_callback);
		rc = mosquitto_connect(mosq, mqtt_host, mqtt_port, 60);
		if (rc != MOSQ_ERR_SUCCESS) {
			printf("%d Mqtt connect fail %d !!!\r\n", __LINE__, getpid());
			run = 0;
		}

		if(pid== (pid_t) 0) {
		/* I am a child */
			printf("Mqqt child process %d\n\r", getpid());
			mosquitto_subscribe(mosq, NULL, mqtt_pub, 0);
			rc = mosquitto_loop_start(mosq);
			for (i = 0; i < 5; ++i) {
				mosquitto_publish(mosq, NULL, mqtt_sub, strlen(clientid) + 1,  clientid, 0, false);
				sleep(1);
			}
		} else {
			/*ma de*/
			printf("Mqqt main process %d\n\r", getpid());
			while (run) {

				mosquitto_subscribe(mosq, NULL, mqtt_sub, 0);
				rc = mosquitto_loop_start(mosq);

				for (i = 0; i < 2; ++i) {
					char msg[] = "lcd i am your mother";
					mosquitto_publish(mosq, NULL, mqtt_pub, sizeof(msg),  msg, 0, false);
				}
				sleep(3);
			}
		}
		printf("Mqtt quit %d \n\r", getpid());
		mosquitto_destroy(mosq);
	} else {
		printf("%d Mqtt init fail !!!\r\n", __LINE__);
	}
	mosquitto_lib_cleanup();
	return 0;
}

