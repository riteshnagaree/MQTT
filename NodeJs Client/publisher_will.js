/* ------------------------------------
Description : A publisher example to check will message
*/

const mqtt = require('mqtt')
const TOPIC = 'cdac/diot'
const WILL_TOPIC = 'dead/device'
let number = 0
//connection to broker; Set will for the CLient
const client = mqtt.connect('mqtt://localhost:1883',{
    will:{
        topic:WILL_TOPIC,
        payload:'{"device":123,"status":"deactivated"}',
        qos:2,
        retain:true
    }


});
//REgistering the Callback to notify the Broker connection 
client.on('connect',()=>{
    console.log("i'm connected to the Broker")
    setInterval(()=>{
        //Publishing  to Broker on Topic
        client.publish(TOPIC,`{"temperature":${number++}}`,{
            qos:2,        
            retain:1
        })
    },1000)
})

