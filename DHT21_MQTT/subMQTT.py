import time
import sys
import paho.mqtt.client as mqtt
import paho.mqtt.subscribe as subscribe

def print_msg(client, userdata, message):
    print("%s : %s" % (message.topic, message.payload))

subscribe.callback(print_msg, "demo/test", hostname="192.168.2.108")
