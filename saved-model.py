import tensorflow as tf

class Adder(tf.Module):
    @tf.function
    def add(self, x):
        return x + x

if __name__ == '__main__':
    model = Adder()
    tf.saved_model.save(model, './adder-saved-model', signatures=model.add.get_concrete_function(tf.TensorSpec([], tf.float32)))
