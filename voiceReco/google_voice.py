import speech_recognition as sr
import numpy as np


# XXX: Try to simplify audio samples. Don't allow items that are two words
CLASSES = ['pasta', 'milk', 'soda', 'candy']


class Google_Audio():

    def __init__(self):
        self.r = sr.Recognizer()
        self.classes = CLASSES

    def identify(self, audio):
        ''' Determine which item to search for '''
        with audio as source:
            data = self.r.record(source)
        text = self.r.recognize_google(data)
        text.lower()
        text = text.split(" ")
        classes = np.zeros((len(self.classes,)))
        for word in text:
            for i, item in enumerate(self.classes):
                if word == item:
                    classes[i] += 1
        return np.argmax(classes)

if __name__ == "__main__":
#    soda = sr.AudioFile("./records/soda0.wav")
    soda = sr.AudioFile("./records/soda2.wav")

    machine = Google_Audio()
    print(machine.identify(soda))
