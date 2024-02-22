#sample https://github.com/aschiffler/python-mqtt
#https://github.com/eclipse/paho.mqtt.python
# The callback for when the client receives a CONNACK response from the server.
"""
Developed for PG-DESD, ACTS Student (2023 Batch)
@maintainer : bhupendra.jmd@gmail.com
MQTT subscriber client
"""
import paho.mqtt.client as mqtt
import uuid
import time
import json
def on_connect(client, userdata, flags, rc):
    try:
        print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
        #subscribe(topic, qos=0)
        client.subscribe("cdac/docker/testing")
        client.subscribe("cdac/docker/t2")
    except Exception as e:
        print("Exception in Subscriber block",e)
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    try:
        print(msg.topic+" "+str(msg.payload))
        print("data received",msg.payload.decode())
        data_received = int(msg.payload.decode())
        print(type(data_received))
        if isinstance(data_received,int):
            localtime = time.asctime( time.localtime(time.time()) )
            if data_received > 10 and data_received <= 20:
                #data_format = f"{data_received} {localtime}"
                data_format = {
                    "temperature": data_received,
                    "timestamp" : localtime
                }
                print ("data is between 10 and 20")
                f = open("demofile2.json", "a")
                f.write(json.dumps(data_format))
                f.write("\n")
                f.close()
        else:
            print("Sending data to cloud")
    except Exception as e:
        print("Exception in on message block",e)
try:
    mqtt_client_id=uuid.uuid4().hex
    """
    Client(client_id="", clean_session=True, userdata=None, protocol=MQTTv311, transport="tcp")
    """
    client = mqtt.Client(client_id=mqtt_client_id)
    #set username and password based authentication with broker
    #client.username_pw_set(username="",password="")
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("localhost", 1883, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
    client.loop_forever()
except Exception as e:
    print("Excption in main",e)
