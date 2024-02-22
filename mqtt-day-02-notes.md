https://mosquitto.org/

Note:

1. While doing the practicals keep a habit of using -h and -p 
2. host (Broker address) represented with -h and port number (-p) 1883 is not mandetory
   to provide if you are using your hostmachine for pub sub and broker operations.
3. while using broker of other system specify the IP address of the host machines.
4. refer man pages and help section to get correct understanding of flags
--------------------------------------------------------------------------------------

#To publish a message

mosquitto_pub -t cdac/pune/panchwati/floor1/desd/103/temp -h localhost -p 1883 -l

#To subscribe a messge

mosquitto_sub -t cdac/pune/panchwati/floor1/desd/103/temp -h localhost -p 1883

#to check flag details
mosquitto_pub --help

-l : read messages from stdin, sending a separate message for each line.

-----------------------------------------------------------------------------
In order to receive all the messages over a public broker

mosquitto_sub -t \# -h test.mosquitto.org -p 1883 (Avoid CDAC Network - Wireless Port is Blocked only wired connection have open connectivity)

Paho Project:
https://projects.eclipse.org/projects/iot.paho/developer

https://github.com/eclipse/paho.mqtt.python

mosquitto_pub -t cdac/desd -h localhost -p 1883 -m "Hello"

mosquitto_sub -t cdac/desd -h localhost -p 1883

#Publish Single Message

BHIoT$ mosquitto_pub -t cdac/desd -h localhost -p 1883 -m "Hello"

#Example of gracefull disconnect 
    - client sends Disconnect packet before closing the connection

BHIoT$ mosquitto_pub -t cdac/desd -h localhost -p 1883 -m "Hello" -d
Client mosq-pyrW8W1Li1PGTin2ZI sending CONNECT
Client mosq-pyrW8W1Li1PGTin2ZI received CONNACK (0)
Client mosq-pyrW8W1Li1PGTin2ZI sending PUBLISH (d0, q0, r0, m1, 'cdac/desd', ... (5 bytes))
Client mosq-pyrW8W1Li1PGTin2ZI sending DISCONNECT

BHIoT$ mosquitto_pub -t cdac/desd -h localhost -p 1883 -m "Hello I am from DESD" -d
Client mosq-lRVosENkJnMQ7SamFA sending CONNECT
Client mosq-lRVosENkJnMQ7SamFA received CONNACK (0)
Client mosq-lRVosENkJnMQ7SamFA sending PUBLISH (d0, q0, r0, m1, 'cdac/desd', ... (20 bytes))
Client mosq-lRVosENkJnMQ7SamFA sending DISCONNECT

#Case when client is sending the continuous data and being terminated by signal or
due to network Error

-- Case of Ungraceful disconnect as client doesn't send the Disconnect Packet

BHIoT$ mosquitto_pub -t cdac/desd -h localhost -p 1883 -l
Hello^C
[Use Ctrl +C to disconnect]

BHIoT$ mosquitto_pub -t cdac/desd -h localhost -p 1883 -l -d
Client mosq-g4wG7jgn4ahZW9QSLC sending CONNECT
Client mosq-g4wG7jgn4ahZW9QSLC received CONNACK (0)
Hello
Client mosq-g4wG7jgn4ahZW9QSLC sending PUBLISH (d0, q0, r0, m1, 'cdac/desd', ... (5 bytes))
^C
-----------------------------------------------------------------------------------

Wild cards: (valid at subscriber end)

Why do we need wild cards: 

Provide feature to subscriber topics simultaneously
----------------------------------------------------------
Supported Wild Cards

+ -> Single level Wild Cards
# -> Multi level Wild cards
------------------------------------------------------------

Open Terminal 1 (sub)

mosquitto_sub -t d/+/event -h localhost -p 1883

Open Terminal 2 (Pub)

mosquitto_pub -t d/7896/event -h localhost -p 1883 -l

Open Terminal 3 (Pub)

mosquitto_pub -t d/7897/event -h localhost -p 1883 -l 

Open Terminal 4 (sub)

mosquitto_sub -t +/+/event -h localhost -p 1883

Open Terminal 5 (sub)

mosquitto_sub -t +/+/+ -h localhost -p 1883


Observation:
Data Received from all terminals at t1.t4 and t5

--------------------------------------------------------
Multi Level Wild Cards:

- denoted with #
- it should be used as last level in the subscriber topic


vaid(Allowed)
----------------------
a/b/#
#
b/#
----------------------
Not allowed:
#/a
#/a/b
a/#/b/+

Some more Examples:
ild Card Assignment:
Publisher Tpoics : 
a/b/c/d/e/f/g/h

mosquitto_pub -t a/b/c/d/e/f/g/h -h localhost -p 1883 -l

What is the below topics will be used by the subscribers?

1. +/b/c/d/e/f/g/h   - Yes  
2. a/+/c/d/e/f/g/h   - Yes
3. a/+/+/d/e/f/g/h   - Yes
4. a/+/c/d/+/f/g/h   - Yes
5. a/b/d/+/e/f/+/h   -  No
6. a/b/c/+/d/f/g/h   -  No
7. +/+/+/d/++/+/+/+  -  ++ (Is not allowed)/No
8. +/+/+/d/+/+/+/    -  No
9. +/+/+/d/+/+/+/+   -  Yes
10. +/+/+/+/+/+/+/+  -  Yes
Try with #
1. a/#      -
2. \#       - backslash for parsing
3. a/b/c/#  - 
4. #/a/b/c  - Logically Wrong
5. a/+/+/#  - Working
6. a/#/+/+  - Will not work # should be used at the end of level


mosquitto_pub -t d/7896/event -h localhost -p 1883 -l 

Not allowed
mosquitto_sub -t #/+/+ -h localhost -p 1883

BHIoT$ mosquitto_sub -t \#/+/+ -h localhost -p 1883
Error: Invalid subscription topic '#/+/+', are all '+' and '#' wildcards correct?

Use 'mosquitto_sub --help' to see usage.
BHIoT$ 

#Understanding SYS TOPIC:
https://mosquitto.org/man/mosquitto-8.html

While working with pub and sub for data communication never use a topic with
 -- $SYS

Why do we have $SYS topic

--> stats purpose at broker

The number of currently connected clients.

$SYS/broker/clients/connected

mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883

#Example:
BHIoT$ mosquitto_sub -t \$SYS/broker/clients/connected -h localhost -p 1883
2
3
2
1

#NEVER PERFORM SUCH PRATICE - Avoid using $SYS topic

mosquitto_pub -t \$SYS/broker/clients/connected -h localhost -p 1883

------------------------------------------------------------------------------
log file default directory:
/var/log/mosquitto

--> cd /var/log/mosquitto
--> sudo cat mosquitto.log

Log files are created as mosquitto.log that contains details of all the MQTT clients
-----------------------------------------------------------------------------------------

QOS - options
------------------------------------------------------------------------
QOS - 0  - Fire and Forget (Atmost Once)
QOS - 1  - Atleast Once
QOS - 2  - Exactly once
Reliablity and latency both increases when we tend to use higher QOS 
-------------------------------------------------------------------------
While Using Debug mode (-d) flag with pub and sub utility remember:
Format:
(d0, q1, r0, m1, 'a/b', ... (5 bytes))
0 - Not Set
1 - SET
d - duplicate flag(0/1)
q - QOS Flag - 0/1/2
r - retain flag (0/1)
a/b - topic name
5 bytes - total data transmistted with header size included
----------------------------------------------------------------------------------------------------
Subscriber with QOS-0
mosquitto_sub -t pune/# -q 0 -h localhost -p 1883 -d
Sample Output:

Client mosq-j8ENhjcNZ0RIUJikJ4 sending CONNECT
Client mosq-j8ENhjcNZ0RIUJikJ4 received CONNACK (0)
Client mosq-j8ENhjcNZ0RIUJikJ4 sending SUBSCRIBE (Mid: 1, Topic: pune/#, QoS: 0, Options: 0x00)
Client mosq-j8ENhjcNZ0RIUJikJ4 received SUBACK
Subscribed (mid: 1): 0
Client mosq-j8ENhjcNZ0RIUJikJ4 received PUBLISH (d0, q0, r0, m0, 'pune/aqi', ... (2 bytes))
42

=====================================================================================================

Publisher Client with QOS - 0
--> mosquitto_pub -t pune/aqi -q 0 -h localhost -p 1883 -l -d
Sample Output:
42
Client mosq-tWwQnwybN0whar7MsJ sending PUBLISH (d0, q0, r0, m1, 'pune/aqi', ... (2 bytes))
=======================================================================================================
For QOS -1
=======================================================================================================
mosquitto_sub -t pune/# -q 1 -h localhost -p 1883 -d
#Sample Output:
Client mosq-FOufBuWuWDMd2b8JQt sending CONNECT
Client mosq-FOufBuWuWDMd2b8JQt received CONNACK (0)
Client mosq-FOufBuWuWDMd2b8JQt sending SUBSCRIBE (Mid: 1, Topic: pune/#, QoS: 1, Options: 0x00)
Client mosq-FOufBuWuWDMd2b8JQt received SUBACK
Subscribed (mid: 1): 1
Client mosq-FOufBuWuWDMd2b8JQt received PUBLISH (d0, q1, r0, m1, 'pune/aqi', ... (2 bytes))
Client mosq-FOufBuWuWDMd2b8JQt sending PUBACK (m1, rc0)

==========================================================================================================

mosquitto_pub -t pune/aqi -q 1 -h localhost -p 1883 -l -d

#Sample Output

Client mosq-63rYfbfolUhCFDhdqW sending CONNECT
Client mosq-63rYfbfolUhCFDhdqW received CONNACK (0)
40   
Client mosq-63rYfbfolUhCFDhdqW sending PUBLISH (d0, q1, r0, m1, 'pune/aqi', ... (2 bytes))
Client mosq-63rYfbfolUhCFDhdqW received PUBACK (Mid: 1, RC:0)

---> RC - Return code - 0- Stands for success
--------------------------------------------------------------------------------------------------------------
FOR QOS-2
==============================================================================================
#Subscriber
--> mosquitto_sub -t pune/# -q 2 -h localhost -p 1883 -d
Sample Output:
-------------------
Client mosq-SJaObLdIHBoYYXsg2s sending CONNECT
Client mosq-SJaObLdIHBoYYXsg2s received CONNACK (0)
Client mosq-SJaObLdIHBoYYXsg2s sending SUBSCRIBE (Mid: 1, Topic: pune/#, QoS: 2, Options: 0x00)
Client mosq-SJaObLdIHBoYYXsg2s received SUBACK
Subscribed (mid: 1): 2
Client mosq-SJaObLdIHBoYYXsg2s received PUBLISH (d0, q2, r0, m1, 'pune/aqi', ... (2 bytes))
Client mosq-SJaObLdIHBoYYXsg2s sending PUBREC (m1, rc0)
Client mosq-SJaObLdIHBoYYXsg2s received PUBREL (Mid: 1)
Client mosq-SJaObLdIHBoYYXsg2s sending PUBCOMP (m1)
48

#Publisher
--> mosquitto_pub -t pune/aqi -q 2 -h localhost -p 1883 -l -d
Sample Output:
--------------------------------------------------------------------------------------------------------
Client mosq-2ITBasTWAuwxwBHKdP sending CONNECT
Client mosq-2ITBasTWAuwxwBHKdP received CONNACK (0)
48  
Client mosq-2ITBasTWAuwxwBHKdP sending PUBLISH (d0, q2, r0, m1, 'pune/aqi', ... (2 bytes))
Client mosq-2ITBasTWAuwxwBHKdP received PUBREC (Mid: 1)
Client mosq-2ITBasTWAuwxwBHKdP sending PUBREL (m1)
Client mosq-2ITBasTWAuwxwBHKdP received PUBCOMP (Mid: 1, RC:0)
----------------------------------------------------------------------------------------------------------
Assignment:
--------------
1. What If a message is published with higher QOS and subscribed with lower QOS? //Pub/Q1 and Sub is Q0
2. What If a message is published with lower QOS and Subscribed with higher QOS  //Pub is Q1 and Sub is Q2
===========================================================================================================
Remember:
A message with Higher QOS can be degraded at the subscriber end by specifying lower QOS, however A Lower QOS
message can not be upgraded even requesting the higher QOS from the subsriber. Message will be received the higher
QOS published originally say message published with QOS-1 can not be received with QOS-2 even after requesting from
the subscriber.
----------------------------------------------------------------------------------------------------------------------