import paho.mqtt.client as mqtt

subscriber = mqtt.Client(client_id= "cdacsensor01" ,protocol=mqtt.MQTTv5 )

TOPIC='cdac/diot'

subscriber.username_pw_set("sensor","diot")

#set my will to the broker: TOPIC : PAYLOAD: QoS : 
WILL_TOPIC = 'device/dead'

subscriber.will_set(WILL_TOPIC,"Sensor DHT22 is offline",qos=1,retain=True)


def on_connection(Client,userdata,flags,rc):
    if rc== mqtt.MQTT_ERR_SUCCESS:
     print('connection with MQTT broker now')
     subscriber.subscribe(TOPIC)

    else:
       print("Error occured")

def on_receive(Client,userdata,msg):
   print(f'Topic : {msg.topic}, Message : {str(msg.payload)}')
  
  
subscriber.on_connect = on_connection
subscriber.on_message = on_receive


subscriber.connect("localhost",1883)

subscriber.loop_forever()
