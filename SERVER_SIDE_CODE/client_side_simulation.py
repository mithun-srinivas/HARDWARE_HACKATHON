from websocket import create_connection
import random
import time
import json
ws = create_connection("ws://10.60.2.245:8000/ws/10949")
print("Connected to websocket server")
while True:
    data = {}
    data["ecg"] = random.randint(1,991)
    data["temp"] = round(random.uniform(95,98),2)
    data["spo2"] = random.randint(87,95)
    data["bpm"] = random.randint(70,84)
    data["bp"] = random.randint(80,120)
    ws.send(json.dumps(data))
    print(json.dumps(data))
    print("Data is sent")
    time.sleep(1)
ws.close()