// #ifndef PARAMETERS_H
// #define PARAMETERS_H

// #define DEBUG_ 1
// #define ON 1
// #define OFF 0
// #define PARAM_PATH "/saperlipopette"
// #define MUTEX_NAME "/saperlipopette-sem"
// #define FOREVER for (;;)
// #define MAX_LEN 256

// /**
// * The structure that holds parameters for the syrup fountain.
// * It is stored in the associated shared memory.
// */
// typedef struct parameters_t {
//     pid_t pid_gui;
//     int ending_flag;
//     char key[MAX_LEN]; /*!< The key to activate the simulation */
//     char tap[MAX_LEN]; /*!< The open/close tap */
//     char drink[MAX_LEN]; /*!< The drink (water, etc.) */
// } parameters;

// void initialize_parameters(parameters *params);
// void analyze_parameters_to_read_key(parameters *params);
// void close_and_destroy_parameters(parameters *params, const char *path);
// #endif
