from websocket import create_connection
import random
import time
import json
ws = create_connection("ws://192.168.225.138:8000/ws/10950")
print("Connected to websocket server")
while True:
    data = {}
    data["ecg"] = random.randint(500,991)
    data["temp"] = round(random.uniform(95,96),2)
    data["spo2"] = round(random.uniform(87,88),2)
    data["bpm"] = random.randint(70,71)
    data["bp"] = random.randint(80,82)
    ws.send(json.dumps(data))
    print(json.dumps(data))
    print("Data is sent")
    time.sleep(0.08)
ws.close()