#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

#include "../include/list.h"
#include "../include/graph.h"
#include "../include/gviz_structs.h"
#include "../include/clog.h"

int parse_args(int argc, char ** argv, bool * verbose, bool * generate_dot,
                char ** dot_filename, int * num_nodes);

int main(int argc, char ** argv) {

    printf("Beginning program...\n\n");
    srand(time(0));

    bool verbose      = false;
    bool generate_dot = false;
    char * dot_filename = "graphviz/list_graph.dot";
    int  num_nodes    = 10;
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

    printf("Building initial adjacency list...");
    ListNode ** a_list = build_a_list(num_nodes);
    log_green("✓");

    fill_a_list(a_list, num_nodes);

    if (generate_dot) {
        printf("Generating graphviz dotfile...");
        gviz_a_list(dot_filename, a_list, num_nodes);
        log_green("✓");
    }

    if (verbose) {
        print_a_list(a_list, num_nodes);
    }

    printf("Destroying adjacency list...");
    destroy_a_list(a_list, num_nodes);
    log_green("✓");

    log_green("\nAll Done!\n");
    return EXIT_SUCCESS;
}

int parse_args(int argc, char ** argv, bool * verbose, bool * generate_dot,
                char ** dot_filename, int * num_nodes) {

    int opt;

    while ((opt = getopt(argc, argv, "vd:n:")) != -1) {
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
                log_yell("max nodes set to %d", *num_nodes);
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
