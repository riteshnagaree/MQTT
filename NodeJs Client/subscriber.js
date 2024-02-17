/* ------------------------------------
Description : A publisher example to check will message
Broker: Mosquitto
*/

const mqtt = require('mqtt')
const TOPIC = 'cdac/diot/+/value'

// const BROKER_TOPIC = '$SYS/'
const WILL_TOPIC = 'dead/device'
//connection to broker
const client = mqtt.connect('mqtt://localhost:1883',{
    protocolVersion:5,
    keepalive:0,
    clientId:'cdacdiot_sensor',
    clean:false,
    username:'actuator',
    password:'qwerty123'
});

client.on('connect',()=>{
    console.log("i'm connected to the Broker")
    //Subscription to Broker on Topic
    client.subscribe(TOPIC,(err)=>{
        if(err){
            console.log("NOT connected properly");
            return;
        }
        console.log(`Subscriber to Topic: ${TOPIC}`)
    })
})

//To receive messages on subscribed TOPIC
client.on('message',(topic,payload)=>{
    console.log(`Message received at TOPIC: ${topic}`)
    console.log(payload.toString())
})
