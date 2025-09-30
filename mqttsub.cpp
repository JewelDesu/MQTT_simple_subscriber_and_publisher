#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>

void connected(struct mosquitto* mosq, void* obj, int return_value);
void message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message);

int main(){

	int return_value;
	int ID=1256;

	mosquitto_lib_init();

	struct mosquitto* mosq;
	
	//client name, clean session, auth
	mosq = mosquitto_new("sub-test", true, &ID);
	
	mosquitto_connect_callback_set(mosq, connected);
	mosquitto_message_callback_set(mosq, message);
	
	//client, host name / broker ip, part number, keep alive time
	return_value = mosquitto_connect(mosq, "localhost", 1883, 60);

	if(return_value)
	{
		printf("Could not connect to broker. Error: %d\n", return_value);
		mosquitto_destroy(mosq);
		return -1;
	}

	mosquitto_loop_start(mosq);
	
	printf("Loop has started, Press Enter to quit \n");
	getchar();
	mosquitto_loop_stop(mosq, true);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);
	
	mosquitto_lib_cleanup();
	return 0;
}

//client, ID, return value
void connected(struct mosquitto* mosq, void* obj, int return_value){
	if(return_value)
	{
		printf("Error has occurred: %d\n", return_value);
		exit(-1);
	}
	//client, message ID, topic, service quality
	mosquitto_subscribe(mosq, NULL, "test", 0);
	printf("Subscribed to topic: test");
}

void message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message)
{
	printf("Message received from topic %s: %s\n", message->topic, (char*) message->payload);

}
