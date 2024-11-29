import network
import time
import ubinascii
import machine
from umqttsimple import MQTTClient

# Definição dos pinos
trigger_pin = 5
echo_pin = 18
led_verde = machine.Pin(2, machine.Pin.OUT)
led_vermelho = machine.Pin(4, machine.Pin.OUT)
led_amarelo = machine.Pin(16, machine.Pin.OUT)

led_verde.off()
led_vermelho.off()
led_amarelo.off()

# Configuração da rede
rede = network.WLAN(network.STA_IF)
rede.active(True)
rede.connect('Lab', '123456789')
while not rede.isconnected():
    print('.', end="")
    time.sleep(1)
print("Conectado:", rede.ifconfig())

# Configurações do MQTT
mqtt_server = b'4166df98726c4a0cb6bcbd279ddc281a.s1.eu.hivemq.cloud'
port = 8883
user = b'cotuca'
pwd = b'cotuca'
client_id = ubinascii.hexlify(machine.unique_id())
topic_pub = b'tf_dist'
topic_sub = b'trab_final'

# Função para medir a distância com o HC-SR04
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

# Callback para processar mensagens recebidas
def callback(topic, msg):
    try:
        print(f"Nova mensagem no tópico {topic.decode('utf-8')}: {msg.decode('utf-8')}")
        data = eval(msg.decode('utf-8'))
        ra_msg = data.get('ra')
        led = data.get('led')
        
        if ra_msg == "23333":  
            if led == 0:
                led_verde.on()
                led_vermelho.off()
                led_amarelo.off()
            elif led == 1:
                led_vermelho.on()
                led_verde.off()
                led_amarelo.off()
            elif led == 2:
                led_amarelo.on()
                led_vermelho.off()
                led_verde.off()
            print(f"LED {led} ligado.")
    except Exception as e:
        print(f"Erro ao processar a mensagem: {e}")

# Configuração do cliente MQTT
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
    client.subscribe(topic_sub)
except OSError as e:
    print(e)
    time.sleep(5)
    machine.reset()

# Loop principal para publicar a distância e processar mensagens
while True:
    distancia = distanciaHCSR04()
    mensagem = f'{{"ra": "23333", "dist": {distancia:.2f}}}'
    
    client.publish(topic_pub, mensagem)
    print(f"Publicado: {mensagem}")

    client.check_msg() 
    time.sleep(z)
