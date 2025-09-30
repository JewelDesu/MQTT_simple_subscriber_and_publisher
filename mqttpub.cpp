#include <stdio.h>
#include <mosquitto.h>

int main(){
	
	int return_value;
	struct mosquitto* mosq;

	mosquitto_lib_init();
	
	//client name, clean session, auth
	mosq = mosquitto_new("test", true, NULL);

	//client, host name / broker IP, part number, keep alive time
	return_value = mosquitto_connect(mosq, "localhost", 1883, 60);

	if(return_value != 0)
	{
		printf("Could not connect to broker. Error: %d\n", return_value);
		mosquitto_destroy(mosq);
		return -1;
	}

	printf("Connected to the broker \n");

	//client, pointer to message ID, topic, payload in bytes, payload, service quality, retrain
	mosquitto_publish(mosq, NULL, "test", 19, "Test Test Beep Boop", 0, false);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}
