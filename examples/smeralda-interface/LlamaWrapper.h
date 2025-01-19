#ifndef LLAMA_WRAPPER_H
#define LLAMA_WRAPPER_H

#include <string>

class LlamaWrapper {
  public:
    LlamaWrapper(const char * name, const char * path);

    ~LlamaWrapper();

    static const char * sendRequest(const char * input);

  private:
    std::string            modelName;
    std::string            modelPath;
    bool                   isLoaded;
    struct llama_context * ctx;

    void loadModel();

    void unloadModel();
};

#endif
