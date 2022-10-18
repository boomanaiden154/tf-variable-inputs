#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/model_builder.h"
#include "tensorflow/lite/op_resolver.h"
#include "tensorflow/lite/logger.h"

#include <iostream>

int main() {
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile("adder-tflite.tflite");

  tflite::ops::builtin::BuiltinOpResolver resolver;
  std::unique_ptr<tflite::Interpreter> interpreter;
  tflite::InterpreterBuilder(*model, resolver)(&interpreter);

  interpreter->AllocateTensors();

  float* input = interpreter->typed_input_tensor<float>(0);
  input[0] = 1.0;
  input[1] = 1.0;

  interpreter->Invoke();

  float* output = interpreter->typed_output_tensor<float>(0);

  std::cout << output[0] << "\n";
}
