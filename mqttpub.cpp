#include <stdio.h>
#include <mosquitto.h>
#include <fstream>
#include <string>
#include <unistd.h>
#include <iostream>

int main(){
	
	int return_value;
	struct mosquitto* mosq;
	std::string temp, broker_IP;
	

	mosquitto_lib_init();
	
	//client name, clean session, auth
	mosq = mosquitto_new("test", true, NULL);
	
	printf("Enter brokers IP address\n");
        std::cin >> broker_IP;
	//client, host name / broker IP, part number, keep alive time
	return_value = mosquitto_connect(mosq, broker_IP.c_str(), 1883, 60);

	if(return_value != 0)
	{
		printf("Could not connect to broker. Error: %d\n", return_value);
		mosquitto_destroy(mosq);
		return -1;
	}

	printf("Connected to the broker \n");

	while(1)
	{
		std::ifstream temp_file ("/tmp/m4/temp");
		while (std::getline (temp_file,temp))
		{
			mosquitto_publish(mosq, NULL, "test", temp.size(), temp.c_str(), 0, false);
		}	
		sleep(30);
	}
	//client, pointer to message ID, topic, payload in bytes, payload, service quality, retrain
	//mosquitto_publish(mosq, NULL, "test", 19, "Test Test Beep Boop", 0, false);

	mosquitto_disconnect(mosq);
	mosquitto_destroy(mosq);

	mosquitto_lib_cleanup();
	return 0;
}
