'''
'
 Desenvolvedores:
 Rafael Moreira Cavalcante de Souza - 23333
 Marcelo Henrrique Morello Manzo - 23326
 Vitor Henrique Gírio Paes - 23340

'''


import network
from machine import Pin
import socket


led1 = Pin(15, Pin.OUT)
led2 = Pin(2, Pin.OUT)
led3 = Pin(4, Pin.OUT)

# Configura o ESP32 como Access Point
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid='ESP32_AP', password='12345678')


html = """<!DOCTYPE html>
<html>

<head>
    <title>ESP32 LED Control</title>
</head>

<body>
    <div class="container">
        <h1>Controlar LEDs</h1>
        <div class="buttons">
            <div class="eachLed">
                <a href="/?led1=on"><button class="onButton">ON LED 1</button></a>
                <a href="/?led1=off"><button class="offButton">OFF LED 1</button></a>
            </div>
            <div class="eachLed">
                <a href="/?led2=on"><button class="onButton">ON LED 2</button></a>
                <a href="/?led2=off"><button class="offButton">OFF LED 2</button></a>
            </div>
            <div class="eachLed">
                <a href="/?led3=on"><button class="onButton">ON LED 3</button></a>
                <a href="/?led3=off"><button class="offButton">OFF LED 3</button></a>
            </div>
        </div>
    </div>
    

    <style>
        * {
            font-family: Arial, sans-serif;
        }

        body {
            display: flex;
            align-items: center;
            justify-content: center;
            height: 100vh;
            width: 100vw;
            background-color: #f0f0f0;
            margin: 0;
            padding: 0;
        }

        .container {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-items: center;
            gap: 10px;

            font-size: 30px;
            width: 80%;
            padding: 20px;

        }

        .buttons {
            display: flex;
            gap: 10px;
            border: #004080 1px solid;
            padding: 10px;
            border-radius: 5px;
            background-color: white;

            width: 100%;
            
        }

        .eachLed {
            display: flex;
            flex-direction: column;
            gap: 10px;
            width: 100%;
            height: 100%;
        }

        button {
            padding: 10px;
            border: none;
            border-radius: 5px;
            color: white;
            font-size: 30px;
            cursor: pointer;
            width: 100%;
            height: 20rem;
        }

        .onButton {
            background-color: #00cc00;
        }

        .offButton {
            background-color: #ff0000;
        }

        .onButton:hover {
            background-color: #00ff00;
        }

        .offButton:hover {
            background-color: #ff3333;
        }

        a {
            text-decoration: none;
        }


    </style>
</body>

</html>
"""

# gerencia as requisições
def web_page():
    return html

# servidor web
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)

print('Servidor Web rodando no endereço:', addr)

while True:
    cl, addr = s.accept()
    print('Cliente conectado:', addr)
    request = cl.recv(1024)
    request = str(request)
    print('Requisição:', request)

    #  qual LED deve ser controlado
    if '/?led1=on' in request:
        led1.on()
    if '/?led1=off' in request:
        led1.off()
    if '/?led2=on' in request:
        led2.on()
    if '/?led2=off' in request:
        led2.off()
    if '/?led3=on' in request:
        led3.on()
    if '/?led3=off' in request:
        led3.off()

    #  resposta HTML
    response = web_page()
    cl.send('HTTP/1.1 200 OK\n')
    cl.send('Content-Type: text/html\n')
    cl.send('Connection: close\n\n')
    cl.sendall(response)
    cl.close()
