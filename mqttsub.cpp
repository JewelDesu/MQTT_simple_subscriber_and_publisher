#include <stdio.h>
#include <stdlib.h>
#include <mosquitto.h>
#include <iostream>
#include <string>
#include <unistd.h>

void connected(struct mosquitto* mosq, void* obj, int return_value);
void message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* message);

int main(){

	int return_value;
	int ID=1256;

	std::string name, broker_IP;

	mosquitto_lib_init();

	struct mosquitto* mosq;
	
	printf("Enter subscribers name\n");
	std::cin >> name;
	//client name, clean session, auth
	mosq = mosquitto_new(name.c_str(), true, &ID);
	
	mosquitto_connect_callback_set(mosq, connected);
	mosquitto_message_callback_set(mosq, message);
	
	printf("Enter brokers IP address\n");
        std::cin >> broker_IP;
	//client, host name / broker ip, part number, keep alive time
	return_value = mosquitto_connect(mosq, broker_IP.c_str(), 1883, 60);

	if(return_value)
	{
		printf("Could not connect to broker. Error: %d\n", return_value);
		mosquitto_destroy(mosq);
		return -1;
	}

	mosquitto_loop_start(mosq);
	
	printf("Loop has started, Press Enter to quit \n");
	
	sleep(5);
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
