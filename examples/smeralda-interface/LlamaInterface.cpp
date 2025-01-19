#include "LlamaInterface.h"

LlamaWrapper * createModel(const char * name, const char * path) {
    return new LlamaWrapper(name, path);
}

void deleteModel(LlamaWrapper * wrapper) {
    delete wrapper;
}

const char * sendRequest(LlamaWrapper * wrapper, char * input) {
    return LlamaWrapper::sendRequest(input);
}


