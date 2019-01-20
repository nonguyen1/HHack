#!/usr/bin/env python3
import pyaudio
import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft, ifft
from random import *


CHUNK = 512
FORMAT = pyaudio.paInt16 #paInt8
CHANNELS = 1
RATE = 48000 #sample rate
RECORD_SECONDS = 3
WAVE_OUTPUT_FILENAME = "audio.wav"
dtype = 'int{0}'.format(CHUNK)

def recordWord(ct):
    p = pyaudio.PyAudio()

    stream = p.open(format=FORMAT,
                    channels=CHANNELS,
                    rate=RATE,
                    input=True,
                    frames_per_buffer=CHUNK) #buffer

    print("* recording")

    frames = []
    framesmatrix = []

    for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
        data = stream.read(CHUNK)
        frames.append(data) # 2 bytes(16 bits) per channel
        framesmatrix.append(np.fromstring(data, dtype=np.int16))

    print("* done recording")

    stream.stop_stream()
    stream.close()
    p.terminate()
    print(type(p))

    wf = wave.open(WAVE_OUTPUT_FILENAME.format(str(ct)), 'wb')
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(p.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    signal = np.hstack(framesmatrix)

    sam_wid = p.get_sample_size(FORMAT)
    sam_rate = RATE


#    return signal, sam_wid, sam_rate
#    print("signal", type(signal))


    # print(signal)

    # fig, axes = plt.subplots(2,1)
    # axes[0].plot(signal)
    # y = fft(signal)
    # axes[1].plot(y)
    # plt.show()

    wf.writeframes(b''.join(frames))
    wf.close()

if __name__ == "__main__":
    recordWord(0)
