'''
General test of NN Classifier for speech recognition.
'''


from sklearn import neighbors, svm, ensemble
import scipy.ndimage.measurements as m
import matplotlib.pyplot as plt
import numpy as np
import random
import pyaudio
import os
import sys
import wave
import librosa as lr
import librosa.display

NUM_NEIGHBORS = 1
L_DISTANCE = 1
CHUNK = 512
WINDOW = 100

duration = 3
filename = "./records/icecream0.wav"
DATA_DIR = "./records"

# clf = neighbors.KNeighborsClassifier(NUM_NEIGHBORS, p=L_DISTANCE)
# clf.fit(x_train, y_train)

class Voice_Rec_NN(object):
    def __init__(self, x_train, y_train):
        self.clf = neighbors.KNeighborsClassifier(NUM_NEIGHBORS, p=L_DISTANCE)
#        self.clf = svm.SVC()
#        self.clf = ensemble.RandomForestClassifier(100)
        self.clf.fit(x_train, y_train)

    def predict(self, x):
        return self.clf.predict(x)

def load_data(recordings_dir):
    my_data = []
    my_labels = []
    for filename in os.listdir(recordings_dir):
        if filename.split(".")[-1] != "wav":
            continue
        if filename[0] == 'i':
            label = 0
        elif filename[0] == 'p':
            label = 1
        elif filename[0] == 's':
            label = 2
        else:
            label = 3
        my_labels.append(label)

        src_x, src_sr = lr.load(os.path.join(recordings_dir,filename))
        ft = lr.stft(src_x)
        db = lr.amplitude_to_db(abs(ft))
        ft = np.mean(ft, axis=0)

#        ft = lr.feature.melspectrogram(src_x, src_sr)
#        db = lr.power_to_db(ft)
#        plt.plot(ft)
#        plt.show()


#        com = np.array(m.center_of_mass(ft)).astype(int)
#        print(com)
#        print(ft.shape)
#        print(com[0])
#        ft_1 = ft[com[0]-20:com[0]+20]
#        ft_1 = ft_1[:, com[1]-20:com[1]+20]
#        print(ft_1.shape)

#        my_data.append(np.append(ft,db))
#        time = np.arange(len(ft))
#        print("ft.shape", ft.shape)
#        print("time.shape", time.shape)
#        ft = np.append(ft, time)
        my_data.append(np.append(ft,db))

#        with wave.open(os.path.join(recordings_dir, filename), 'rb') as wf:
#            fs = wf.getframerate()
#            bytes_per_sample = wf.getsampwidth()
#            bits_per_sample  = bytes_per_sample * 8
#            dtype = 'int{0}'.format(bits_per_sample)
#            channels = wf.getnchannels()
#
#            # read data
#            audio = np.fromstring(wf.readframes(int(duration*fs*bytes_per_sample/channels)), dtype=dtype)
#            audio.shape = (int(audio.shape[0]/channels), channels)
#            audio = np.fft.fft(audio)
#            freqs = np.fft.fftfreq(audio[:,ch].shape[0], 1.0/fs) / 1000.0
#            my_data.append(audio)
    return np.array(my_data), np.array(my_labels)



if __name__ == "__main__":
    data, labels = load_data(DATA_DIR)
    print("P1", data.shape, labels.shape)
    print("P2", len(data), len(labels))

    # Preprocess data here

    pdata = list(zip(data, labels))
    random.shuffle(pdata)
    data, labels = zip(*pdata)

#    plt.plot(data[0])
#    plt.show()

    print("P3", len(data), len(labels))

    x_train = np.array(data[:-1])
    y_train = np.array(labels[:-1])

    x_train = np.array([np.squeeze(x) for x in x_train])

    x_test = np.array(data[-1:])
    y_test = np.array(labels[-1:])
    x_test = np.array([np.squeeze(x) for x in x_test])

    mine = Voice_Rec_NN(x_train, y_train)
    print("P4", x_test.shape)
    print(mine.predict(x_test))
    print(y_test)
