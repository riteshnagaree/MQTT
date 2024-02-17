import requests
import json
import thingspeak

HOST =thingspeak.host_name

path = thingspeak.path_name

val = {
    "api_key":thingspeak.api_write_key,
    "field1":thingspeak.feild1,
    "field2":thingspeak.feild2
}


response = requests.post(HOST+path, val)


print(response.json())
print(response.status_code)


