import tensorflow as tf
import numpy as np
from tensorflow.keras.applications import MobileNetV3Large
from tensorflow.keras.applications.resnet50 import ResNet50
from keras.models import save_model

def representative_dataset():
    for _ in range(100):
      data = np.random.rand(1, 224, 224, 3)
      yield [data.astype(np.float32)]

def mobilenetV3_QuantWeights():
  #Quantize only the weights from fp to int8
  tensorflowModel = "/tmp/mobilenetV3"
  network = "mobilenetV3_quantWeights.tflite"
  model = MobileNetV3Large()
  model.save(tensorflowModel)
  converter = tf.lite.TFLiteConverter.from_keras_model(model)
  converter.optimizations = [tf.lite.Optimize.DEFAULT]
  tflite_model = converter.convert()
  with open(network, 'wb') as f:
    f.write(tflite_model)

def mobilenetV3_FullInteger():
  #Quantize the weights and the activations based on a rep dataset
  #Use float operators when they don't have an integer implementation
  tensorflowModel = "/tmp/mobilenetV3"
  network = "mobilenetV3_fullInteger.tflite"
  model = MobileNetV3Large()
  model.save(tensorflowModel)
  converter = tf.lite.TFLiteConverter.from_keras_model(model)
  converter.optimizations = [tf.lite.Optimize.DEFAULT]
  converter.representative_dataset = representative_dataset
  tflite_model = converter.convert()
  with open(network, 'wb') as f:
    f.write(tflite_model)

def mobilenetV3_IntOnly():
  #Quantize the weights and the activations based on a rep dataset
  #Uensure compatibility with integer only devices (such as 8-bit microcontrollers) and accelerators 
  #(such as the Coral Edge TPU), you can enforce full integer quantization for all ops including the input and output
  tensorflowModel = "/tmp/mobilenetV3"
  network = "mobilenetV3_IntOnly.tflite"
  model = MobileNetV3Large()
  model.save(tensorflowModel)
  converter = tf.lite.TFLiteConverter.from_keras_model(model)
  converter.optimizations = [tf.lite.Optimize.DEFAULT]
  converter.target_spec.supported_ops = [tf.lite.OpsSet.TFLITE_BUILTINS_INT8]
  converter.inference_input_type = tf.int8
  converter.inference_output_type = tf.int8
  converter.representative_dataset = representative_dataset
  tflite_model = converter.convert()
  with open(network, 'wb') as f:
    f.write(tflite_model)


mobilenetV3_QuantWeights();
mobilenetV3_IntOnly()
mobilenetV3_FullInteger()