import WirelessTool, socket

TCPServer = WirelessTool.TCPClient('127.0.0.1',3005,0.1)
#while(not TCPServer.connect(10)):
#    print("[INFO]\tWaiting User Connection")

TCPServer.write(b'70016')
