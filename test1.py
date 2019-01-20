from devi2c import I2C
device, bus = 0x04, 0
i2c = I2C(device, bus)
value = i2c.read(1)         # read 1 byte
i2c.write([0x46, 0x10])     # write bytes
i2c.close()                 # close connection
