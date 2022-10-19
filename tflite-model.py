import tensorflow as tf

class Adder(tf.Module):
    @tf.function
    def add(self, x):
        return x + x

if __name__ == '__main__':
    model = Adder()
    addConcreteFunction = model.add.get_concrete_function(tf.TensorSpec([], tf.float32))
    converter = tf.lite.TFLiteConverter.from_concrete_functions([addConcreteFunction], model)
    tflite_model = converter.convert()
    with open('./adder-tflite.tflite', 'wb') as f:
        f.write(tflite_model)
