#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

struct page {
    int id;
    unsigned int counter;
};

void output_pages(struct page *array, int size, int current_page) {
    for (int i = 0; i < size; i++) {
        printf("i=%d\tid=%d\tcounter = %u\n", i, array[i].id, array[i].counter);
    }
    printf("Current page is %d\n", current_page);
    printf("\n");
}
/*
 * Check existing of page in table
 */
int is_in_table(struct page *array, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (array[i].id == id) {
            return i;
        }
    }
    return -1;
}
/*
 * Shift counter. If its current page - add 1 in start, otherwise 0
 */
void shift_counter(struct page *array, int size, int id) {
        unsigned int r = 1;
        for (int i = 0; i < size; i++) {
            if (array[i].id != id) {
                array[i].counter >>= 1;
            }
            else {
                array[i].counter = (array[i].counter >> 1) | (r << 31);
            }
        }
}
/*
 * Change page, if we need add new page
 * Find page with minimum counter or not used page and change it on current
 */
void change_page(struct page *array, int size, int id) {
    unsigned int min = UINT32_MAX;
    int ptr_on_min;
    for (int i = 0; i < size; i++) {
        if (array[i].id == -1) {
            ptr_on_min = i;
            break;
        }
        if (array[i].counter < min) {
            min = array[i].counter;
            ptr_on_min = i;
        }
    }
    array[ptr_on_min].id = id;
    array[ptr_on_min].counter = 1 << 31;
}

int main() {
    FILE *test_input = fopen("Lab 09 input.txt", "r");
    int pages_amount;
    printf("Enter pages amount:\n");
    scanf("%d", &pages_amount);
    struct page current_pages[pages_amount];
    for (int i = 0; i < pages_amount; i++) {
        current_pages[i].id = -1;
        current_pages[i].counter = 0 << 31;
    }
    int current_page;
    int hit = 0, miss = 0;
    while(fscanf(test_input, "%d ", &current_page) != EOF) {
        output_pages(current_pages, pages_amount, current_page);
        if (is_in_table(current_pages, pages_amount, current_page) > -1) {
            hit++;
        }
        else {
            miss++;
            change_page(current_pages, pages_amount, current_page);
        }
        shift_counter(current_pages, pages_amount, current_page);
    }

    printf("hits = %d, misses = %d, ratio = %f\n", hit, miss, (double) hit / (double) miss);
}
