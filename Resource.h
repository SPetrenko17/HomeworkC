/*
 * "Copyright 2019 Sergei Petrenko"
 */
#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Resource Resource;

struct Resource {
    char* name;
    char* callnumber;
    char* measure;
    char* category;
    int count;
};
void resource_init(Resource* resource, char* name, char* callnumber,
                   char* measure, char* category, int count) {
    resource->name = name;
    resource->callnumber = callnumber;
    resource->measure = measure;
    resource->category = category;
    resource->count = count;
}

int compare(const void *resource1, const void *resource2) {
    Resource *res1 = (Resource *)resource1; // NOLINT
    Resource *res2 = (Resource *)resource2; // NOLINT
    int result_comp = strcmp(res1->category, res2->category);
    if (result_comp == 0) {
        result_comp = strcmp(res2->measure, res1->measure);
        if (result_comp == 0) {
            return res1->count > res2->count;
        } else {
            return result_comp;
        }
    } else {
        return result_comp;
    }
}

void my_swap(void* v1, void* v2, int size) {
    char *buffer[size];
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

void my_quicksort(void* v, size_t size, int left, int right,
                  int (*comp)(const void*, const void*)) {
    void *vt, *v3;
    size_t i, last, mid = (left + right) / 2;
    if (left >= right)
        return;
    void* vl = (char*)(v + (left * size)); // NOLINT
    void* vr = (char*)(v + (mid * size)); // NOLINT
    my_swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {
        vt = (char*)(v + (i * size)); // NOLINT
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size)); // NOLINT
            my_swap(vt, v3, size);
        }
    }
    v3 = (char*)(v + (last * size)); // NOLINT
    my_swap(vl, v3, size);
    my_quicksort(v, size, left, last - 1, comp);
    my_quicksort(v, size, last + 1, right, comp);
}

void print_grouped_resources(Resource *resources, int size) { //NOLINT
    my_quicksort(resources, sizeof(Resource), 0, size-1, compare); // NOLINT
    for (size_t i = 0; i < size; ++i) {
        printf("%s %s %s %d %s %s", resources[i].category, resources[i].name,
               resources[i].callnumber, resources[i].count,
               resources[i].measure, "\n");
    }
}
int get_measure_statistics(Resource* resources, size_t size,
                           char* measure, char* category) {
    int result = 0;
    for (size_t i = 0; i < size; i++) {
        if ( strcmp(resources[i].measure, measure) == 0
             && strcmp(resources[i].category, category) == 0 ) {
            result+=resources[i].count;
        }
    }
    return result;
}
void add_some_resources(Resource* resources) {
    resource_init(&resources[0] , "Coal", "CE01", "kg"
            , "Energy", 600);
    resource_init(&resources[1] , "Oil", "O11S",
                  "l", "Energy", 100);
    resource_init(&resources[2] , "Silver", "Slv01",
                  "kg", "Metal", 400);
    resource_init(&resources[3] , "Аcid", "AC02E",
                  "l", "Liquid", 300);
    resource_init(&resources[4] , "Gold", "Gld01",
                  "kg", "Metal", 500);
    resource_init(&resources[5] , "Antifreeze",  "AF01W",
                  "l", "Liquid", 200);
    resource_init(&resources[6], "Bla", "Bla",
                  "Bla", "Bla", 100000);
}

#endif  // RESOURCE_H_"

