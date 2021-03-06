#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../include/clog.h"
#include "../include/tree.h"
#include "../include/gviz_structs.h"

int parse_args(int argc, char ** argv, bool * verbose, bool * generate_dot,
                char ** dot_filename, int * num_nodes);

int main(int argc, char ** argv) {

    printf("Beginning ordered binary tree program...");

    int num_nodes = 10;
    bool verbose = false;
    bool generate_dot = false;
    char * dot_filename = "graphviz/ord_tree.dot";
    if (argc > 1) {
        int arg_result = parse_args(
            argc, argv,
            &verbose,
            &generate_dot,
            &dot_filename,
            &num_nodes
        );
        if (arg_result == -1) {
            return EXIT_SUCCESS;
        }
    }

    TreeNode * root = NULL;

    printf("Building binary tree...");
    for (int build_ix=0; build_ix<num_nodes; build_ix++) {
        root = insert_treenode(root, build_ix);
    }
    log_green("✓");

    if (generate_dot) {
        printf("Generating binary tree graphviz dot file...");
        gviz_tree(dot_filename, root);
        log_green("✓");
    }

    destroy_tree(root);

    return EXIT_SUCCESS;
}

int parse_args(int argc, char ** argv, bool * verbose, bool * generate_dot,
                char ** dot_filename, int * num_nodes) {

    int opt;

    log_yell("==Command Line Arguments==\n");

    while ((opt = getopt(argc, argv, "vd:n:p:")) != -1) {
        switch (opt) {
            case 'v':
                *verbose = true;
                log_yell("verbose output on");
                break;
            case 'd':
                *generate_dot = true;
                *dot_filename = optarg;
                log_yell("graph .dot will be generated");
                break;
            case 'n':
                *num_nodes = atoi(optarg);
                log_yell("number of nodes set to %d", *num_nodes);
                break;
            case ':':
                printf("option needs a value\n");
                return -1;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
        }
    }

    for (; optind<argc; optind++) {
        printf("extra argument: %s\n", argv[optind]);
    }

    printf("\n");
    return 1;
}
