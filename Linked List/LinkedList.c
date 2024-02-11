#include <stdio.h>
#include <stdlib.h>

#define LIST_APPEND(head, add) list_append((struct list_node **)head, (struct list_node *)add)
#define LIST_REMOVE(head, remove) list_remove((struct list_node **)head, (struct list_node *)remove)
#define LIST_NEXT(item) (struct string_item *)item->node.next

struct list_node {
    struct list_node *next;
};

struct string_item {
    struct list_node node;
    const char *string;
};

struct string_item *string_item_new(const char *string) {
    struct string_item *item = malloc(sizeof(struct string_item));
    if (!item) {
        return NULL;
    }
    item->string = string;
    item->node.next = NULL;
    return item;
}

void list_append(struct list_node **head, struct list_node *node) {
    while (*head) {
        head = &(*head)->next;
    }
    *head = node;
}

void list_remove(struct list_node **head, struct list_node *node) {
    while (*head && *head != node) {
        head = &(*head)->next;
    }
    if (*head) {
        *head = node->next;
    }
}

struct list_node *list_reverse(struct list_node *head) {
    struct list_node *prev = NULL, *next = NULL;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

int main() {
    struct string_item *my_linked_list = NULL;
    LIST_APPEND(&my_linked_list, string_item_new("Hello World"));
    LIST_APPEND(&my_linked_list, string_item_new("Test001"));
    LIST_APPEND(&my_linked_list, string_item_new("Test002"));
    LIST_APPEND(&my_linked_list, string_item_new("Last Item of the Linked List"));

    struct string_item *string_item = my_linked_list;
    while (string_item) {
        printf("%s\n", string_item->string);
        string_item = LIST_NEXT(string_item);
    }

    // Reverse the list
    my_linked_list = (struct string_item *)list_reverse((struct list_node *)my_linked_list);

    printf("\nReversed list:\n");
    string_item = my_linked_list;
    while (string_item) {
        printf("%s\n", string_item->string);
        string_item = LIST_NEXT(string_item);
    }

    return 0;
}