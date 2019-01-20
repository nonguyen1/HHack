import smbus
import time

bus = smbus.SMBus(1)


address = 0x04

def writeNumber(value):
    msb = value/1000
    lsb = value%1000
    bus.write_i2c_block_data(address,msb,[lsb])
    return -1

while True:
    var = input("format direction,speed: ")
    if not var:
        continue

    writeNumber(var)





