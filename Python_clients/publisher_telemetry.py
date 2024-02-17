#publisher with single publisher

import paho.mqtt.client as mqtt
import json

publisher = mqtt.Client(client_id= "cdacsensor01",protocol=mqtt.MQTTv31)

#topic for publication
TOPIC = 'cdac/diot'



def on_connection(Client,userdata,flags,rc):
    if rc== mqtt.MQTT_ERR_SUCCESS:
     print('connection with broker code' + str(rc))
     value = {"temp":24.0}
     publisher.publish(TOPIC,payload = json.dumps(value),qos=1 , retain=True)
     print("Data published....")
    else:
       print("Error occured")

#assign our method to client callback
publisher.on_connect = on_connection

#connect to the broker HOSTNAME,PORT,KeepAlive
publisher.connect("localhost",1883)


#adding the loop forever
publisher.loop_forever()
