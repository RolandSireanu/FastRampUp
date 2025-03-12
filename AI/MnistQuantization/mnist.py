#!/usr/bin/env python
# coding: utf-8

# In[2]:


import h5py


# In[266]:


import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.layers import Flatten
from tensorflow.keras.layers import Dense
from tensorflow.keras.losses import SparseCategoricalCrossentropy
from sklearn.metrics import accuracy_score
from sys import getsizeof
import numpy as np
import os


# In[19]:


print(tf.__version__)


# In[200]:


def GetSize(aPath, unit="KB"):
    lNrOfBytes = os.path.getsize(aPath)
    if(unit == "KB"):
       return round(lNrOfBytes / 1024, 4);
    elif(unit == "MB"):
        return round(lNrOfBytes / (1024 * 1024), 4)
    else:
        print("Unknown measurement unit")
        return 0


# In[185]:


def print_in_out_info(aInterpreter):
    print("Input details:")
    print(aInterpreter.get_input_details())
    print("Output details:")
    print(aInterpreter.get_output_details())


# In[ ]:


class Runner(object):
    def __init__(self, aKerasModel):
        self.mKerasModel = aKerasModel
        self.mTfLiteModel = None
        self.TF_MODEL_PATH = "./mnist_tf_model.tflite"
        self.TF_MODEL_FP16_PATH = "./mnist_tf_fp16_model.tflite"
        self.TF_MODEL_INT8_PATH = "./mnist_tf_int8_model.tflite"

    @staticmethod
    def GetSize(aPath, unit="KB"):
        lNrOfBytes = os.path.getsize(aPath)
        if(unit == "KB"):
           return round(lNrOfBytes / 1024, 4);
        elif(unit == "MB"):
            return round(lNrOfBytes / (1024 * 1024), 4)
        else:
            print("Unknown measurement unit")
            return 0
    
    def Run(self, aTestImages, aTestLabels):
        _, lAcc = self.mKerasModel.evaluate(aTestImages, aTestLabels, verbose=2)
        print("Accuracy of keras model: {}%".format(round(lAcc*100,2)))
        
    def RunTfLite(self, aTestImages, aTestLabels, dt="FP32"):
        lTfLiteConverter = tf.lite.TFLiteConverter.from_keras_model(self.mKerasModel)
        lTfLiteModelPath = self.TF_MODEL_PATH;
        if(dt == "FP16"):
            lTfLiteConverter.optimizations = [tf.lite.Optimize.DEFAULT]
            lTfLiteConverter.target_spec.supported_types = [tf.float16]
            lTfLiteModelPath = self.TF_MODEL_FP16_PATH;
        elif(dt == "INT8"):
            lTfLiteConverter.optimizations = [tf.lite.Optimize.OPTIMIZE_FOR_SIZE]
            lTfLiteModelPath = self.TF_MODEL_INT8_PATH;
        else:
            print("Unknown data type provided")
       
        self.mTfLiteModel = lTfLiteConverter.convert()
        if(self.mTfLiteModel is not None):
            lFd = open(lTfLiteModelPath, mode="wb")
            lNrOfBytesWritten = lFd.write(self.mTfLiteModel)
            assert(lNrOfBytesWritten == len(self.mTfLiteModel))
        
        lTfLiteInterpreter = tf.lite.Interpreter(model_path=lTfLiteModelPath)
        lTfLiteInterpreter.resize_tensor_input(input_index=in_details[0]["index"], tensor_size=(10000,28,28))
        lTfLiteInterpreter.resize_tensor_input(input_index=out_details[0]["index"], tensor_size=(10000,10))
        lTfLiteInterpreter.allocate_tensors()

        lTestImagesFp32 = np.float32(aTestImages)
        lInDetails = lTfLiteInterpreter.get_input_details()
        lOutDetails = lTfLiteInterpreter.get_output_details()
        lTfLiteInterpreter.set_tensor(lInDetails[0]["index"], lTestImagesFp32)
        lTfLiteInterpreter.invoke()
        lYValues = lTfLiteInterpreter.tensor(lOutDetails[0]["index"])()
        lPred = np.argmax(lYValues, axis=1)
        lAccScore = accuracy_score(aTestLabels, lPred)

        print("Accuracy score for tflite model with size {} is {}%".format(round(GetSize(lTfLiteModelPath),2), round(100*lAccScore,2)))

    def RunModel(self, aTestImages, aTestLabels, dt="FP64"):
        if(dt == "FP64"):
            _, lAcc = self.mKerasModel.evaluate(aTestImages, aTestLabels, verbose=2)
            print("Accuracy of keras model: {}%".format(round(lAcc*100,2)))
        elif(dt == "FP32"):
            RunTfLite(aTestImages, aTestLabels)
        elif(dt == "FP16"):
            RunTfLite(aTestImages, aTestLabels, "FP16")
        elif(dt == "INT8"):
            RunTfLite(aTestImages, aTestLabels, "INT8")
        else:
            print("Unknown data type provided!")

        


# In[233]:


dataset = keras.datasets.fashion_mnist


# In[208]:


(x_train,y_train),  (x_test, y_test) = dataset.load_data();


# In[209]:


print(x_train.shape, x_train.dtype)


# In[210]:


print(y_train.shape, y_train.dtype)


# In[211]:


len(x_train)


# In[212]:


unique_y_train = np.unique(y_train)


# In[213]:


print(unique_y_train)


# In[214]:


plt.figure()
plt.imshow(x_train[12], cmap="gray")
plt.colorbar()
plt.grid(False)
plt.show()


# In[215]:


x_train = x_train / 256
x_test = x_test / 256


# In[279]:


model = keras.Sequential([keras.layers.Input(shape=(28,28)), 
                          keras.layers.Flatten(),
                          keras.layers.Dense(128, activation="relu"),
                          keras.layers.Dropout(rate=0.20),
                          keras.layers.Dense(128, activation="relu"),
                          keras.layers.Dense(10)])


# In[280]:


model.summary()


# In[282]:


model.compile(optimizer="adam", loss=SparseCategoricalCrossentropy(from_logits=True), metrics=["accuracy"])
model.fit(x=x_train, y=y_train, epochs=30)


# In[ ]:





# In[ ]:





# In[ ]:





# In[274]:


r = Runner(model)
r.Run(x_test, y_test)


# In[275]:


r.RunTfLite(x_test, y_test)


# In[276]:


r.RunTfLite(x_test, y_test, dt="FP16")


# In[277]:


r.RunTfLite(x_test, y_test, dt="INT8")


# In[ ]:




