import json
import requests
import SERVER

HOST = SERVER.host_name
PORT = SERVER.port_number
DB = SERVER.db_path
header = SERVER.headerr

response = requests.get(HOST + PORT + DB,headers=header)


print(response.json())
# print(response.status_code)