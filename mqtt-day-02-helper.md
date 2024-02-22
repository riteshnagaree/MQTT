$SYS TOPIC
-- reserved for broker stats
mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883

mosquitto_sub -t \# -h test.mosquitto.org -p 1883

mosquitto_sub -t \# -h test.mosquitto.org -p 1883 > test_data.json

------------------------------------------------------------------

For $SYS with more details
refer Broker status section
https://mosquitto.org/man/mosquitto-8.html


Quality of Service:
QOS - 0

By Default the QOS is 0 (implicit with pub/sub)

Pub:

mosquitto_pub -t desd/room/temperature --qos 0 -h localhost -p 1883 -l -d

Sub:

mosquitto_sub -t desd/room/temperature --qos 0 -h localhost -p 1883 -d

Sample Output:

BHIoT$ mosquitto_sub -t desd/room/temperature --qos 0 -h localhost -p 1883 -d
Client null sending CONNECT
Client null received CONNACK (0)
Client null sending SUBSCRIBE (Mid: 1, Topic: desd/room/temperature, QoS: 0, Options: 0x00)
Client null received SUBACK
Subscribed (mid: 1): 0
------------------------------
BHIoT$ mosquitto_pub -t desd/room/temperature --qos 0 -h localhost -p 1883 -l -d
Client null sending CONNECT
Client null received CONNACK (0)


PUB (QOS-0)

hello
Client null sending PUBLISH (d0, q0, r0, m1, 'desd/room/temperature', ... (5 bytes))

SUB (QOS-0)

Client null sending CONNECT
Client null received CONNACK (0)
Client null sending SUBSCRIBE (Mid: 1, Topic: desd/room/temperature, QoS: 0, Options: 0x00)
Client null received SUBACK
Subscribed (mid: 1): 0
Client null received PUBLISH (d0, q0, r0, m0, 'desd/room/temperature', ... (5 bytes))
hello

QOS-1

BHIoT$ mosquitto_sub -t desd/room/temperature --qos 1 -h localhost -p 1883 -d
Client null sending CONNECT
Client null received CONNACK (0)
Client null sending SUBSCRIBE (Mid: 1, Topic: desd/room/temperature, QoS: 1, Options: 0x00)
Client null received SUBACK
Subscribed (mid: 1): 1

BHIoT$ mosquitto_pub -t desd/room/temperature --qos 1 -h localhost -p 1883 -l -d
Client null sending CONNECT
Client null received CONNACK (0)



QOS-1 (SUB)

Client null received PUBLISH (d0, q1, r0, m1, 'desd/room/temperature', ... (5 bytes))
Client null sending PUBACK (m1, rc0)
hello

QOS-1 (PUB)

Client null sending PUBLISH (d0, q1, r0, m1, 'desd/room/temperature', ... (5 bytes))
Client null received PUBACK (Mid: 1, RC:0)
Client null sending PINGREQ
Client null received PINGRESP


QOS-2 (Pub)
mosquitto_pub -t desd/room/temperature --qos 2 -h localhost -p 1883 -l -d


Client null sending PUBLISH (d0, q2, r0, m1, 'desd/room/temperature', ... (9 bytes))
Client null received PUBREC (Mid: 1)
Client null sending PUBREL (m1)
Client null received PUBCOMP (Mid: 1, RC:0)

QOS-2 (SUB)
mosquitto_sub -t desd/room/temperature --qos 2 -h localhost -p 1883 -d

Client null received PUBLISH (d0, q2, r0, m1, 'desd/room/temperature', ... (9 bytes))
Client null sending PUBREC (m1, rc0)
Client null received PUBREL (Mid: 1)
Client null sending PUBCOMP (m1)
temp : 20



