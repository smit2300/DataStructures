#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/list.h"
#include "../include/clog.h"

ListNode * create_node(int value) {
    ListNode * new_node = malloc(sizeof(*new_node));
    new_node->value = value;
    sprintf(new_node->label, "%d", value);
    new_node->next = NULL;
    return new_node;
}

ListNode * append(ListNode * head, int value) {

    ListNode * new_node = create_node(value);

    if (head == NULL) {
        return new_node;
    }

    ListNode * temp_node = head;
    while (temp_node->next != NULL) {
        temp_node = temp_node->next;
    }
    temp_node->next = new_node;

    return head;
}

void pop(ListNode * head) {
    ListNode * temp_node = head;
    while(temp_node->next->next != NULL){
      temp_node = temp_node->next;
    }
    temp_node->next = NULL;
}

void destroy_list(ListNode * head) {
    ListNode * victim_node = head;
    while (head->next != NULL) {
        victim_node = head;
        head = head->next;
        free(victim_node);
    }
    free(head);
}

void print_list(ListNode * head) {
    ListNode * print_node = head;
    while (print_node->next != NULL) {
        printf("%d-->", print_node->value);
        print_node = print_node->next;
    }
    printf("%d", print_node->value);
}

int randint(int lower, int upper) {
    return ((rand() % (upper - lower + 1)) + lower);
}
