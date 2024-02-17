import requests
import json
import SERVER

HOST = SERVER.host_name
PORT = SERVER.port_number
PATH = SERVER.db_path

REQUEST_BODY ={
    "index":0,
    "value":11212
}

response = requests.put(HOST+PORT+PATH,json = REQUEST_BODY)

print(response.json())