'''
Cart main driver
'''
import time
import sys
sys.path.insert(0, "./Grid_Env")

from voiceReco.google_voice import Google_Audio
from Grid_Env.methods import Agent
from Grid_Env.gridworld import GridWorld
from voiceReco.audio import recordWord

import pyaudio
import wave
import RPi.GPIO as GPIO
import speech_recognition as sr

GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

POSITIONS = {0: (1, 0), 1: (3, 2), 2: (2, 4), 3: (3, 0), 4: (0, 3)}
AUDIO_FILE = "audio.wav"




class Robot(object):
    def __init__(self):
        self.ga = Google_Audio()
        self.position = (0, 0)
        self.grid_world = GridWorld(draw_grid=False, in_bot=True) # Simulate environment

    def get_item_position(self, audio):
        ''' Get the desired postion of the item we want '''
        desired_item = self.ga.identify(audio)
        return POSITIONS[desired_item]

    def go_to_position(self, pos):
        ''' Call bot commands to get the item position '''
        self.grid_world.new_grid(pos)
        return self.grid_world.loop()


if __name__ == "__main__":
    # Build general robot
    cart = Robot()

    # Start the bot
    while True:
#        pos = (2,2) # TODO: Get position here.
#        commands = bot.go_to_position((2,2))
#        pos = (2,2) # TODO: Get position here.
        # Get audio data
        recording = False
        recordWord(0)
        while False:
            # Button pressed
            input_state = GPIO.input(18)
#            print(input_state)
            if input_state == False:
                recording = True
                # Start recording audio here.
                print('Button Pressed')
#                signal, width, rate = recordWord(0)
                recordWord(0)
                # Being recording audio here.
                break

            time.sleep(0.25)

#        print("WIDTH", type(width), width)
        # Begin processing signal to get cart commands.
#        print("signal", type(signal))

        audio = sr.AudioFile(AUDIO_FILE)
        pos = cart.get_item_position(audio)
        print("class", pos)
        commands = cart.go_to_position(pos)
        print(commands)

        import WirelessTool, socket
        TCPServer = WirelessTool.TCPClient('127.0.0.1', 3005, 0.1)
        for command in commands:
            if command == (-1,0):
#                out_command = b'70050'
                out_command = b'70020'
            elif command == (1, 0):
#                out_command = b'70050'
                out_command = b'70030'
            elif command == (0, 1):
#                out_command = b'82050'
                out_command = b'66020'
            elif command == (0, -1):
#                out_command = b'76050'
                out_command = b'66016'
            TCPServer.write(out_command)
            time.sleep(3)



        break;
#        for command in commands:
#
#            if command == (-1,0):
#                out_command = '70050'
#            elif command == (1, 0):
#                out_command = '66050'
#            elif command == (0, 1):
#                out_command = '82050'
#            elif command == (0, -1):
#                out_command = '76050'
#
#            python3_command = "python2 i2cMasterTest.py out_command"  # launch your python2 script using bash
#
#            process = subprocess.Popen(python3_command.split(), stdout=subprocess.PIPE)
#            output, error = process.communicate()
    print("End")
