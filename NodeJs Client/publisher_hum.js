/* ------------------------------------
Description : A publisher example to check will message
*/

const mqtt = require('mqtt')
const TOPIC = 'cdac/diot/hum/value'
// const WILL_TOPIC = 'hum/pune'
let number = 0
//connection to broker
const client = mqtt.connect('mqtt://localhost:1883');
//REgistering the Callback to notify the Broker connection 
client.on('connect',()=>{
    console.log("i'm connected to the Broker")
    setInterval(()=>{
        //Publishing  to Broker on Topic
        client.publish(TOPIC,`{Humidity:60%}`,{
            qos:2,        
            retain:0
        })
    },7000)
})

