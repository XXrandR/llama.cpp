
#include "LlamaWrapper.h"
#include <cstring>

LlamaWrapper::LlamaWrapper(const char * name, const char * path) :
    modelName(name),  // Initialize modelName
    modelPath(path),  // Initialize modelPath
    isLoaded(false),  // Initialize isLoaded
    ctx(nullptr) {    // Initialize ctx
}

LlamaWrapper::~LlamaWrapper() {}

const char * LlamaWrapper::sendRequest(const char * input) {
    return input;
}
