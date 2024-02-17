/* ------------------------------------
Description : A publisher example to check will message
Broker: Mosquitto
*/

const mqtt = require('mqtt')
const TOPIC = 'cdac/diot'
const WILL_TOPIC = 'dead/device'

//connection to broker
const client = mqtt.connect('mqtt://localhost:1883',{
    protocolVersion:5,
    keepalive:0,
    clientId:'cdacdiot_sensor'
});

client.on('connect',()=>{
    console.log("i'm connected to the Broker")
    //Subscription to Broker on Topic
    client.subscribe([TOPIC,WILL_TOPIC],(err)=>{
        if(err){
            console.log("Barobar connect kr re bsdk");
            return;
        }
        console.log(`Subscriber to Topic: ${TOPIC}`)               
    })
})

//To receive messages on subscribed TOPIC
client.on('message',(topic,payload)=>{
    console.log(`Message received at TOPIC: ${topic}`)
    console.log(payload.toString())

    try {
        let data = JSON.parse(payload.toString())
        if(data && data.temperature && data.temperature>30){

            console.log("TEmperature is more than 30 Celsius")
        }
    } catch (error) {
        console.log(error)
    }
})
