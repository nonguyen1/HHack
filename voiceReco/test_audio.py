from sklearn import neighbors
import matplotlib.pyplot as plt
import numpy as np
import random
import pyaudio
import os
import sys
import wave
import librosa as lr
import librosa.display
import speech_recognition as sr

#NUM_NEIGHBORS = 1
#L_DISTANCE = 1
#CHUNK = 512
#
#duration = 3
#filename = "./records/icecream0.wav"
#DATA_DIR = "./records"
#
#def dB(a,base=1.0):
#    return 10.0*np.log10(a/base)
#
src_x, src_sr = lr.load("./records/icecream0.wav")
#sr_x, sr_sr = lr.load("./records/icecream1.wav")
#s_x, s_sr = lr.load("./records/soda1.wav")
#x, sr = lr.load("./records/soda2.wav")
#x1, s1 = lr.load("./records/icecream3.wav")
#x2, s2 = lr.load("./records/soda3.wav")
##lr.display.waveplot(src_x, src_sr, color = 'blue', alpha = 0.6, label = 'Source')
##plt.show()
#
#
## title = "TEST"
## ft = lr.stft(audio)
## db = lr.amplitude_to_db(abs(ft))
## plt.figure(figsize=(14, 4))
## plt.title(title, size = 20)
## lr.display.specshow(db, sr=sr, x_axis='time', y_axis='hz')
## plt.ylabel('Hz', size = 16)
## plt.xlabel('Time (seconds)', size = 16)
##
##
## #plt.plot(ft, db)
## plt.show()
#
#def plot_ft(x,sr,title):# source
#    ft = lr.stft(x)
#    db = lr.amplitude_to_db(abs(ft))
#    plt.figure(figsize=(14, 4))
#    plt.title(title, size = 20)
#    lr.display.specshow(db, sr=sr, x_axis='time', y_axis='hz')
#    plt.ylabel('Hz', size = 16)
#    plt.xlabel('Time (seconds)', size = 16)
#    clb = plt.colorbar()
#    clb.set_label('Decibels')
#    return db
#
#print(type(src_x), type(src_sr))
#print(src_x.shape)
##src_db = plot_ft(src_x,src_sr,'Fourier transformed power spectrum')
##src_db = plot_ft(sr_x,sr_sr,'Fourier transformed power spectrum')
##src_db = plot_ft(s_x,s_sr,'Fourier transformed power spectrum')
##src_db = plot_ft(x,sr,'Fourier transformed power spectrum')
#dsp1 = np.fft.fftshift(np.abs(np.fft.fft(src_x)) ** 2)
#dsp2 = np.fft.fftshift(np.abs(np.fft.fft(sr_x)) ** 2)
#dsp3 = np.fft.fftshift(np.abs(np.fft.fft(s_x)) ** 2)
#dsp4 = np.fft.fftshift(np.abs(np.fft.fft(x)) ** 2)
#dsp5 = np.fft.fftshift(np.abs(np.fft.fft(x1)) ** 2)
#dsp6 = np.fft.fftshift(np.abs(np.fft.fft(x2)) ** 2)
#plt.plot(dsp1)
#plt.plot(dsp2)
#plt.plot(dsp3)
#plt.plot(dsp4)
#plt.show()
#
#print(np.linalg.norm(dsp1 - dsp2))
#print(np.linalg.norm(dsp2 - dsp3))
#print(np.linalg.norm(dsp2 - dsp4))
#print(np.linalg.norm(dsp3 - dsp4))
#print(np.linalg.norm(dsp3 - dsp4))
#
#print(np.linalg.norm(dsp5 - dsp6))
#print(np.linalg.norm(dsp3 - dsp6))



#######################
r = sr.Recognizer()
soda = sr.AudioFile("./records/icecream0.wav")
soda = sr.AudioFile("./records/pyaudio-output1.wav")
with soda as source:
    audio = r.record(source)

print(r.recognize_google(audio))
