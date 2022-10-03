#include <stdio.h>
#include <stdlib.h>
#include "tensorflow/c/c_api.h"

#include <iostream>

void NoOpDeallocator(void* data, size_t a, void* b) {}

int main()
{
  TF_Graph* Graph = TF_NewGraph();
  TF_Status* Status = TF_NewStatus();

  TF_SessionOptions* SessionOpts = TF_NewSessionOptions();
  TF_Buffer* RunOpts = NULL;

  const char* saved_model_dir = "adder-saved-model/";
  const char* tags = "serve";
  int ntags = 1;

  TF_Session* Session = TF_LoadSessionFromSavedModel(SessionOpts, RunOpts, saved_model_dir, &tags, ntags, Graph, NULL, Status);

  if(TF_GetCode(Status) == TF_OK) {
    std::cout << "loaded model okay\n";
  } else {
    std::cout << TF_Message(Status) << "\n";
  }

  int NumInputs = 1;
  TF_Output* Input = (TF_Output*)malloc(sizeof(TF_Output) * NumInputs);

  TF_Output t0 = {TF_GraphOperationByName(Graph, "serving_default_x"), 0};
  if(t0.oper == NULL) {
    std::cout << "failed to get input\n";
  } else {
    std::cout << "got input ok\n";
  }

  Input[0] = t0;

  int NumOutputs = 1;
  TF_Output* Output = (TF_Output*)malloc(sizeof(TF_Output) * NumOutputs);

  TF_Output t2 = {TF_GraphOperationByName(Graph, "PartitionedCall"), 0};
  if(t2.oper == NULL) {
    std::cout << "failed to get output\n";
  } else {
    std::cout << "got output ok\n";
  }

  Output[0] = t2;

  TF_Tensor** InputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*)*NumInputs);
  TF_Tensor** OutputValues = (TF_Tensor**)malloc(sizeof(TF_Tensor*)*NumOutputs);

  int ndims = 1;
  int64_t dims[] = {1,1};
  float data[] = {2};
  int ndata = sizeof(float);

  TF_Tensor* float_tensor = TF_NewTensor(TF_FLOAT, dims, ndims, data, ndata, &NoOpDeallocator, 0);
  if(float_tensor != NULL) {
    std::cout << "tensor is ok\n";
  } else {
    std::cout << "failed to make tensor\n";
  }

  InputValues[0] = float_tensor;

  TF_SessionRun(Session, NULL, Input, InputValues, NumInputs, Output, OutputValues, NumOutputs, NULL, 0, NULL, Status);

  if(TF_GetCode(Status) == TF_OK) {
    std::cout << "model ran ok\n";
  } else {
    std::cout << TF_Message(Status) << "\n";
  }

  TF_DeleteGraph(Graph);
  TF_DeleteSession(Session, Status);
  TF_DeleteSessionOptions(SessionOpts);
  TF_DeleteStatus(Status);

  float* buff = (float*)TF_TensorData(OutputValues[0]);
  std::cout << buff[0] << "\n";
  return 0;
}
