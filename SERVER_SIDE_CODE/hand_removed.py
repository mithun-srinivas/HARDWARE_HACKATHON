from websocket import create_connection
import random
import time
import json
ws = create_connection("ws://192.168.225.138:8000/ws/10950")
print("Connected to websocket server")
while True:
    data = {}
    data["ecg"] = random.randint(500,991)
    data["temp"] = round(random.uniform(77,78),2)
    data["spo2"] = round(random.uniform(55,57),2)
    data["bpm"] = random.randint(65,66)
    data["bp"] = random.randint(65,66)
    ws.send(json.dumps(data))
    print(json.dumps(data))
    print("Data is sent")
    time.sleep(0.08)
ws.close()