#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next_node;
    bool is_end;
};

void print_list(struct node *head) {
    while (head->is_end == false) {
        printf("%d ", head->value);
        head = head->next_node;
    }
    printf("\n");
}

void insert_node(struct node* head, int index, int value) {
    if (index == 0) {
        if (head->is_end == true) {
            head->value = value;
            head->next_node = malloc(sizeof(struct node));
            head->next_node->is_end = true;
            head->is_end = false;
            return;
        }
        else {
            struct node* temp_node = malloc(sizeof(struct node));
            temp_node->value = value;
            temp_node->next_node = malloc(sizeof(struct node));
            *temp_node->next_node = *head;
            *head = *temp_node;
            return;
        }
    }
    struct node* current_node = head;
    for (int i = 0; i <= index; i++) {
        if (i == index - 1) {
            if (head->is_end == true) {
                head->value = value;
                head->is_end = false;
                head->next_node = malloc(sizeof(struct node));
                head = head->next_node;
                head->is_end = true;
            }
            else {
                struct node* p_temp_node = malloc(sizeof(struct node));
                p_temp_node->value = value;
                p_temp_node->is_end = false;
                struct node* next_node = malloc(sizeof(struct node));
                next_node = head->next_node;
                p_temp_node->next_node = next_node;
                head->next_node = p_temp_node;
                return;
            }
        }
        else {
            head = head->next_node;
        }
    }
}

void delete_node(struct node* head, int index) {
    if (index == 0) {
        *head = *head->next_node;
        return;
    }
    struct node* prev_node;
    prev_node = head;
    for (int i = 0; i <= index; i++) {
        if (i == index - 1) {
            if (prev_node->next_node->is_end == true) {
                prev_node->is_end = true;
                free(prev_node->next_node);
            }
            else {
                prev_node->next_node = prev_node->next_node->next_node;
            }
        }
        else {
            prev_node = prev_node->next_node;
        }
    }
}
int main() {
    struct node head_list;
    head_list.is_end = true;
    struct node* head = &head_list;
    char user_input = 'a';
    printf("Interface:\n");
    printf("D [index] - delete element with index [index]\n");
    printf("I [index] [value]- insert element before element with index [index]\n");
    printf("P - print list\n");
    printf("E - close program\n");
    printf("Input command and/or index:\n");
    while (user_input != 'E') {
        scanf("%c", &user_input);
        if (user_input == 'E') return 0;
        if (user_input == 'I'|| user_input == 'D') {
            int index;
            scanf("%d", &index);
            if (user_input == 'D') {
                delete_node(head, index);
            }
            else {
                int value;
                scanf("%d", &value);
                insert_node(head, index, value);
            }
        }
        else if (user_input == 'P') print_list(head);
    }
    return 0;
}
