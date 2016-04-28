
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <mosquitto.h>

#define db_host "localhost"
#define db_username "mqtt_log"
#define db_password "password"
#define db_database "mqtt_log"
#define db_port 3306

#define db_query "INSERT INTO mqtt_log (topic, payload) VALUES (?,?)"

#define mqtt_host "localhost"
#define mqtt_port 1883

struct mosquitto *mosq;

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	printf("connect_callback\n");
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	printf("message_callback\n");
}

void disconnect_callback(struct mosquitto *mosq, void *obj, int result)
{
	printf("disconnect_callback\n");
}
int main(int argc, char *argv[])
{
	mosquitto_lib_init();
	mosq = mosquitto_new("mesh_public", true, NULL);
	char msg[128];
	if(mosq) {
		mosquitto_connect_callback_set(mosq, connect_callback);
		mosquitto_disconnect_callback_set(mosq, disconnect_callback);
		mosquitto_message_callback_set(mosq, message_callback);

		if (MOSQ_ERR_SUCCESS != mosquitto_connect(mosq, mqtt_host,
					mqtt_port, 60)) {
			printf("mosquitto : connectiong fail!!!!!!!!!!!\n");
		}
		int c= 0;
		while (1)
		{
			sprintf(msg, "Hello mosquitto :%d", c++);
			mosquitto_publish(mosq, NULL, "mqtt", strlen(msg), msg, 0, false);
			printf("send, %d\n", c);
			sleep(1);
		}
	}

	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();

	return 0;
}

