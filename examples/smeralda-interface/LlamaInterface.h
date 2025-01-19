#ifndef LLAMA_INTERFACE_H
#define LLAMA_INTERFACE_H

#include "LlamaWrapper.h"

extern "C" {

LlamaWrapper * createModel(const char * name, const char * path);
void           deleteModel(LlamaWrapper * wrapper);
const char *   sendRequest(LlamaWrapper * wrapper, char * input);
}

#endif
