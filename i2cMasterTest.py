import smbus
import time
import WirelessTool

bus = smbus.SMBus(1)
command = WirelessTool.TCPEchoServer(3005,2)
while(not command.connect(5)):
    print("Waiting connection from commander")


address = 0x04

def writeNumber(value):
    msb = value/1000
    lsb = value%1000
    bus.write_i2c_block_data(address,msb,[lsb])
    return -1

while True:
    #var = int(input("format direction,speed: "))
    #if not var:
    #    continue
    received = command.read()
    if(received != 'Z' and received != ''):
        print(received)
        var = int(received)
        writeNumber(var)





