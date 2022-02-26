import os
import tensorflow as tf
import numpy as np
from tensorflow.python.ops import gen_audio_ops as audio_ops

def load_wav_file(wav_filename, desired_samples):
    wav_file = tf.io.read_file(wav_filename)
    decoded_wav = audio_ops.decode_wav(wav_file, desired_channels=1, desired_samples=desired_samples)
    return decoded_wav.audio, decoded_wav.sample_rate


def calculate_mfcc(audio_signal, audio_sample_rate, window_size, window_stride, num_mfcc):
    spectrogram = audio_ops.audio_spectrogram(input=audio_signal, window_size=window_size, stride=window_stride,
                                              magnitude_squared=True)

    mfcc_features = audio_ops.mfcc(spectrogram, audio_sample_rate, dct_coefficient_count=num_mfcc)    
    return mfcc_features


def test():
    directory = './audios'
    for filename in os.scandir(directory):
        if filename.is_file():
            print(f"\n----audio file: {filename.path}")
            audio, sample_rate =load_wav_file(filename.path,16000)
            mfccs = calculate_mfcc(audio, sample_rate, 640,640,10)
            mfccs = tf.reshape(mfccs, [1,250])
            with tf.Session() as sess:
                print(*mfccs.eval()[0]) 
            
           
if __name__ == '__main__':
    test()