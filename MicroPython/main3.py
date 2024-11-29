import network
from time import sleep
from umqttsimple import MQTTClient
import ubinascii
import ssl
import time
import machine
from machine import Pin

rede = network.WLAN(network.STA_IF)
rede.active(True)
print(rede.scan())
rede.connect('Lab','123456789')
while not (rede.isconnected()):
    print('.', end="")
    sleep(1)
print(rede.ifconfig())
print("Iniciando a rede")

def callback(topic, msg):
    print("Nova mensagem no tópico {}".format(topic.decode('utf-8')))
    msg = msg.decode('utf-8')
    print("Mensagem recebida no topico {}, Msg: {}".format(topic, msg))

mqtt_server = b'4166df98726c4a0cb6bcbd279ddc281a.s1.eu.hivemq.cloud'
port=8883    # se ssl True porta tem que ser zero ou 8883

user=b'cotuca'
pwd =b'cotuca'
client_id = ubinascii.hexlify(machine.unique_id())
topic_pub = b'aula_s'
topic_sub = b'aula_s'
try:
    client = MQTTClient( client_id,
                         mqtt_server,
                         port= port,
                         user = user,
                         password = pwd,
                         ssl=True ,
                         ssl_params={'server_hostname': mqtt_server}
                         )
    
    client.set_callback(callback)
    client.connect()
    print('Conectando...')
except OSError as e:
    print(e)
    sleep(5)
    machine.reset()
    
client.subscribe(topic_sub)
    
push_boot = machine.Pin(0, machine.Pin.IN)    
deadline = time.ticks_add(time.ticks_ms(),5000)

while True:
    client.check_msg()
    estado = push_boot.value()
    print(estado)
    msg = '{"id": r, "distancia": }' 
   # print(msg)
    
   # print(deadline)
   # print(time.ticks_diff(deadline, time.ticks_ms()))
    time.sleep(2)
    if time.ticks_diff(deadline, time.ticks_ms()) < 0:
        print(f'publicado {msg}')
        client.publish(topic_pub, msg)
        deadline = time.ticks_add(time.ticks_ms(), 5000)