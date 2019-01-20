'''
Main driver for application
'''

from voiceReco.google_voice import Google_Audio

class Position(object):
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    def get_pos(self):
        return (self.x, self.y)


class Robot(object):
    def __init__(self):
        self.ga = Google_Audio()
        self.position = Position(0, 0)

    def get_item_position(self, audio):
        ''' Get the steps required to get to said position '''
        pass

    def go_to_position(self):
        ''' Call bot commands to get the item position '''
        pass


if __name__ == "__main__":
    # Build general robot
    bot = Robot()



    print("End")
