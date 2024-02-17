import requests
import json
import SERVER

HOST = SERVER.host_name
PORT = SERVER.port_number
PATH =SERVER.path_name

REQUEST_BODY ={
    "user":"cdac",
    "password":"diot"
}

header ={
    "Content-type" : "/application/json"
}

response = requests.post(HOST+PORT+PATH,json=REQUEST_BODY)

print(response.json())