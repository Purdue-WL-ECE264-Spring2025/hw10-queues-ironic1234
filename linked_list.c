#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { 
    struct list_node * node = (struct list_node *) malloc(sizeof(struct list_node));
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_at_head(struct linked_list *list, size_t value) {
    struct list_node * node = new_node(value);
    node->next = list->head;
    list->head = node;
}

void insert_at_tail(struct linked_list *list, size_t value) {
    struct list_node * node = new_node(value);
    struct list_node * current_node = list->head;
    if (current_node != NULL) {
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = node;
    } else {
        list->head = node;
    }
}

size_t remove_from_head(struct linked_list *list) { 
    struct list_node * temp = list->head;
    size_t value = temp->value;
    list->head = temp->next;
    free(temp);
    return value;
}

size_t remove_from_tail(struct linked_list *list) {
    struct list_node * current = list->head;
    struct list_node * previous = NULL;
    if (current->next == NULL) {
        size_t value = current->value;
        free(current);
        list->head = NULL; 
        return value;
    }
    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    size_t value = current->value;
    previous->next = NULL;
    free(current);
    return value;
}

void free_list(struct linked_list list) {
    struct list_node * current = list.head;
    while (current != NULL) {
        struct list_node * next = current->next;
        free(current);
        current = next;
    }
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
