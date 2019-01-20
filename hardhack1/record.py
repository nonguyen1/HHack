import sounddevice as sd
import numpy as np

sd.default.channels = 1
fs = 48000
duration = 10.5  # seconds
myrecording = sd.rec(int(duration * fs), samplerate=fs,blocking=True)
print(myrecording)
