
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <pthread.h>
#include <mosquitto.h>


#define mqtt_host "localhost"
#define mqtt_port 1883

static pthread_t pid_mqtt_sub;


void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	printf("Topic : %s msg : %s\n", message->topic, (char*)message->payload);
}

void *mqtt_subscribe(void *p)
{
	struct mosquitto *mosq;
	mosquitto_lib_init();
	mosq = mosquitto_new("mesh_subscribe", true, NULL);

	if(mosq) {
		mosquitto_message_callback_set(mosq, message_callback);
		if (MOSQ_ERR_SUCCESS != mosquitto_connect(mosq, mqtt_host,
					mqtt_port, 0)) {
			printf("mosquitto : connectiong fail!!!!!!!!!!!\n");
		}
		mosquitto_subscribe(mosq, NULL, "mesh_info", 0);

		mosquitto_loop_forever(mosq, -1, 1);

		mosquitto_destroy(mosq);
	}
	mosquitto_lib_cleanup();
}


int main(int argc, char *argv[])
{
	pthread_create(&pid_mqtt_sub, NULL, mqtt_subscribe, NULL);

	while (1) {
		printf("%s loop\n", __FUNCTION__);
		sleep(5);
	}

	pthread_cancel(pid_mqtt_sub);
	pthread_join(pid_mqtt_sub, NULL);
	return 0;
}

