'''
Cart main driver
'''
import time
import sys
sys.path.insert(0, "./Grid_Env")

from voiceReco.google_voice import Google_Audio
from Grid_Env.methods import Agent
from Grid_Env.gridworld import GridWorld



POSITIONS = {0: (1, 0), 1: (3, 2), 2: (2, 4), 3: (3, 0), 4: (0, 3)}


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
    bot = Robot()

    # Start the bot
    while True:
        pos = (2,2) # TODO: Get position here.
        commands = bot.go_to_position((2,2))

        # TODO: Execute commands here.
        print(commands)

    print("End")
