/*
 * "Copyright 2019 Sergei Petrenko"
 */
#include <stdio.h>
#include "Resource.h"
int main() {
    size_t  size = 7;
    Resource *resources = (Resource*)malloc(    // NOLINT
            sizeof(struct Resource)*size); // NOLINT
    add_some_resources(resources);
    print_grouped_resources(&*resources, size);
    printf("%d %s", get_measure_statistics(resources, size, "l",
                                           "Liquid") , "l of Liquid\n");
    printf("%d %s", get_measure_statistics(resources, size,
                                           "kg", "Metal"), "kg of metal]\n");
    free(resources);
    return 0;
}