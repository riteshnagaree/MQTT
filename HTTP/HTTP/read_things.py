import requests
import json
import thingspeak

HOST = thingspeak.host_name
channel = thingspeak.channel_number
read = thingspeak.api_key
read_key = thingspeak.api_read_key

response = requests.get(HOST+channel+read+read_key)
                

print(response.json())
print(response.status_code)