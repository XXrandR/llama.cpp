#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

#include "common.h"
#include "llama.h"

static void llama_log_callback_null(ggml_log_level level, const char * text, void * user_data) {
    (void) level;
    (void) text;
    (void) user_data;
}

vector<string> divideString(const char * sen) {
    stringstream        ss(sen);
    string              word;
    vector<std::string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    return words;
}

// to obtain the latest argument of the command
int obtainTokenSizeOfString(const char * data, const char * modelName) {
    if (data == NULL) {
        printf("NULL pointer passed to obtainTokenSizeOfString.\n");
        return 0;  // or handle this error as appropriate
    }
    vector<std::string> argv = divideString(data);

    // variables where to put any arguments we see.
    bool         no_bos           = false;
    bool         no_parse_special = false;
    bool         disable_logging  = false;
    const char * model_path       = NULL;
    const char * prompt_path      = NULL;
    const char * prompt_arg       = NULL;

    // track which arguments were explicitly given
    // used for sanity checking down the line
    bool stdin_set = false;

    // first set the model
    std::filesystem::path baseDir = std::filesystem::current_path();
    baseDir                       = "/models";
    filesystem::path mypath       = baseDir / modelName;
    model_path                    = mypath.c_str();

    ifstream file(model_path);
    if (!file.good()) {
        cout << "SOURCE NOT FOUND: " << model_path;
        return 0;
    }

    // set the prompt
    prompt_arg = argv[0].c_str();

    GGML_ASSERT(model_path);
    GGML_ASSERT(prompt_path || prompt_arg || stdin_set);

    //////
    // Figure out where will the prompt come from.
    //////
    std::string prompt;
    prompt = prompt_arg;

    // tokenizing
    if (disable_logging) {
        llama_log_set(llama_log_callback_null, NULL);
    }

    llama_backend_init();

    llama_model_params model_params = llama_model_default_params();
    model_params.vocab_only         = true;
    llama_model * model             = llama_model_load_from_file(model_path, model_params);
    if (!model) {
        fprintf(stderr, "Error: could not load model from file '%s'.\n", model_path);
        return 1;
    }

    llama_context_params ctx_params = llama_context_default_params();
    llama_context *      ctx        = llama_new_context_with_model(model, ctx_params);
    if (!ctx) {
        fprintf(stderr, "Error: could not create context.\n");
        return 1;
    }

    const bool model_wants_add_bos = llama_add_bos_token(model);
    const bool add_bos             = model_wants_add_bos && !no_bos;
    const bool parse_special       = !no_parse_special;

    // preparing
    std::vector<llama_token> tokens;
    tokens = common_tokenize(model, prompt, add_bos, parse_special);

    int token_count = 0;

    for (int i = 0; i < (int) tokens.size(); i++) {
        token_count += tokens[i];
    }

    return token_count;
}

int main(int argc, char * argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] != NULL) {
            printf("Data stream %d: %s, ", i, argv[i]);
            printf("size token: %d \n", obtainTokenSizeOfString(argv[i], argv[i+1]));
        } else {
            printf("Data stream %d: NULL pointer.\n", i);
        }
    }
    return 0;
}

extern "C" {
int JnaInterface_obtainTokenSize(const char * data,const char * modelName) {
    return obtainTokenSizeOfString(data,modelName);
}
}
