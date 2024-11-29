""" 
Autores: 
        Marcelo Henrique Morello Manzo - 23340
        Rafael Moreira Calvancate de Souza - 23333
        Vitor Henrique Girio Paes - 23340
"""

import network
import time
import ubinascii
import ssl
import machine
from umqttsimple import MQTTClient

# Definição dos pinos 
trigger_pin = 5  
echo_pin = 18   
led1 = machine.Pin(2, machine.Pin.OUT)
led2 = machine.Pin(4, machine.Pin.OUT)
led3 = machine.Pin(16, machine.Pin.OUT)

rede = network.WLAN(network.STA_IF)
rede.active(True)
rede.connect('Lab', '123456789')
while not rede.isconnected():
    print('.', end="")
    time.sleep(1)
print("Conectado:", rede.ifconfig())
print("Iniciando a rede")

# Configurações do MQTT
mqtt_server = b'4166df98726c4a0cb6bcbd279ddc281a.s1.eu.hivemq.cloud'
port = 8883
user = b'cotuca'
pwd = b'cotuca'
client_id = ubinascii.hexlify(machine.unique_id())
topic_pub = b'aula_s'
topic_sub = b'aula_s'


# medir a distância usando o sen
def distanciaHCSR04():
    trigger = machine.Pin(trigger_pin, machine.Pin.OUT)
    echo = machine.Pin(echo_pin, machine.Pin.IN)

    trigger.value(0)
    time.sleep_us(2)
    trigger.value(1)
    time.sleep_us(10)
    trigger.value(0)
    
    duration = machine.time_pulse_us(echo, 1)
    distance = duration * 0.034 / 2
    return distance


def callback(topic, msg):
    try:
        data = eval(msg.decode('utf-8'))
        id_msg = data.get('id')  
        distancia = float(data.get('distancia', 0))  

        if id_msg != "10":
            print(f"Nova mensagem no tópico {topic.decode('utf-8')}: {msg.decode('utf-8')}")

        if id_msg is not None:
            if id_msg != "10": 
                if distancia < 20:
                    led1.on()
                    led2.off()
                    led3.off()
                elif distancia > 20 and distancia < 100:
                    led1.on()
                    led2.on()
                    led3.off()
                elif distancia >= 100:
                    led1.on()
                    led2.on()
                    led3.on()
        else:
            print("ID não encontrado na mensagem.")
    except Exception as e:
        print(f"Erro ao processar a mensagem: {e}")

try:
    client = MQTTClient(
        client_id,
        mqtt_server,
        port=port,
        user=user,
        password=pwd,
        ssl=True,
        ssl_params={'server_hostname': mqtt_server}
    )
    client.set_callback(callback)
    client.connect()
    print('Conectado ao broker MQTT...')
except OSError as e:
    print(e)
    time.sleep(5)
    machine.reset()

client.subscribe(topic_sub)

# leitura do sensor e envio pro MQTT
while True:
    distancia = distanciaHCSR04()
    
    msg = f'{{"id":"10", "distancia": {distancia:.2f}}}'
    client.publish(topic_pub, msg)
    print(f"\nPublicado: {msg}")
    
    client.check_msg()
    time.sleep(1)  
