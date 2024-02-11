#include <stddef.h>
#include <stdio.h>

#define AIV_LIST(x) &(x.list_item)

typedef struct list_node list_item;
typedef struct list_int_node int_item;

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
    unsigned int count;
};

struct list_int_node
{
    struct list_node list_item;
    int value;
};

void list_print(struct list_node **head)
{
    struct list_node *current = *head;
    for(;current != NULL; current = current->next)
    {
        printf(" %d ", ((int_item*)current)->value);
    }
    printf("\n");
}

struct list_node *list_get_tail(struct list_node *head)
{
    if(!head)
    {
        return NULL;
    }

    struct list_node *current_item = head;
    struct list_node *last_item = head;
    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;
};

struct list_node *list_append(struct list_node **head, struct list_node *item)
{
    struct list_node *tail = list_get_tail(*head);
    if(!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }
    item->prev = tail;
    item->next = NULL;
    return item;
}

struct list_node *list_pop(struct  list_node **head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct list_node *current_head = *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    (*head)->next = NULL;
    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;
    return current_head;
};

struct list_node *list_remove_element(struct list_node **head, struct list_node *item)
{
    if(!(*head))
    {
        return NULL;
    }
    
    struct list_node *current_item = (*head);
    struct list_node *prev_item;
    unsigned int counter = (*head)->count;

    if(!item->prev)
    {
        printf("\nItem Removed : %d\n", ((int_item*)item)->value);
        item->next->prev = NULL;
        (*head) = item->next;
    }
    else if(!item->next)
    {
        printf("\nItem Removed : %d\n", ((int_item*)item)->value);
        item->prev->next = NULL;
        item = NULL;
    }
    else
    {
        printf("\nItem Removed : %d\n", ((int_item*)item)->value);
        item->next->prev = item->prev;
        item->prev->next = item->next;
        item = NULL;
    }
    return current_item;
};

struct list_node *list_add_element_prev(struct list_node **head, struct list_node *item_index, struct list_node *elementToAdd)
{
    if(!(*head))
    {
        return NULL;
    }

    if(!item_index->prev)
    {
        elementToAdd->next = (*head);
        (*head)->prev = elementToAdd;
        (*head) = elementToAdd;
        (*head)->count++;
    }
    else
    {
        elementToAdd->prev = item_index->prev;
        elementToAdd->next = item_index;
                
        item_index->prev->next = elementToAdd;
        item_index->prev = elementToAdd;
        (*head)->count++;
    }
    return item_index;
}

struct list_node *list_add_element_next(struct list_node **head, struct list_node *item_index, struct list_node *elementToAdd)
{
    if(!(*head))
    {
        return NULL;
    }

    if(!item_index->next)
    {
        item_index->next = elementToAdd;
        elementToAdd->prev = item_index;
    }
    else
    {
        elementToAdd->prev = item_index;
        elementToAdd->next = item_index->next;

        item_index->next = elementToAdd;
    }
        (*head)->count++;
    return item_index;
}

int main(int argc, char **argv)
{
    struct list_node *head = NULL;

    //Adding element in list
    printf("Adding Value in List\n");
    struct list_int_node int_item1;
    struct list_int_node int_item2;
    struct list_int_node int_item3;
    int_item1.value = 100;
    int_item2.value = 101;
    int_item3.value = 102;
    list_append(&head, AIV_LIST(int_item1));
    list_append(&head, AIV_LIST(int_item2));
    list_append(&head, AIV_LIST(int_item3));
    list_print(&head);

    //Remove element
    list_remove_element(&head, AIV_LIST(int_item1));    //Removing element by address
    list_print(&head);

    //Adding element before of a value
    struct list_int_node added_item_prev;
    added_item_prev.value = 110;
    struct list_int_node added_item_next;
    added_item_next.value = 120;
    printf("\nAdding Before : %d\n", added_item_prev.value);
    list_add_element_prev(&head, AIV_LIST(int_item2), AIV_LIST(added_item_prev));
    list_print(&head);

    //Adding element after of a value
    printf("\nAdding After : %d\n", added_item_prev.value);
    list_add_element_next(&head, AIV_LIST(int_item3), AIV_LIST(added_item_next));
    list_print(&head);
    printf("\nCount : %d\n\n", head->count);
    return 0;
}