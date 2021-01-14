#include "searchers.h"

int linear_search(const commodity comms[], int comms_count, comm_id_t ids[], int ids_count, int quantities[]) {
    int i,j,prvky;

    if (!comms || comms_count <= 0 || !ids || ids_count <= 0 || !quantities){
        return EXIT_FAILURE;
    }

    for (i = 0; i < ids_count; i++){
        prvky = 0;
        for (j = 0; j < comms_count; j++){
            if (strcmp(ids[i], comms[j].id) == 0){
                prvky = 1;
                quantities[i] = comms[j].quantity;
                break;
            }
        }
        if (!prvky){
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;

}

int btree_search(const commodity comms[], int comms_count, comm_id_t ids[], int ids_count, int quantities[]) {
    commodity *comms_copy, *found;
    int i;

    if (!comms || comms_count <= 0 || !ids || ids_count <= 0 || !quantities){
        return EXIT_FAILURE;
    }
    comms_copy = (commodity *)malloc(sizeof(commodity) * comms_count);
    if (!comms_copy){
        return EXIT_FAILURE;
    }

    memcpy(comms_copy,comms, sizeof(commodity) * comms_count);
    qsort(comms_copy,comms_count,sizeof(commodity),comm_compare);

    for (i = 0;i <ids_count;i++){
        found = bsearch(&ids[i],comms_copy,comms_count,sizeof(commodity),ids_compare);
        if (!found){
            return EXIT_FAILURE;
        }
        quantities[i] = found->quantity;
    }

    free(comms_copy);
    return EXIT_SUCCESS;
}

int comm_compare(const void *a, const void *b) {
    if (a && b){
        return strcmp(((commodity *)a)->id,((commodity *)b)->id);
    } else {
        return 0;
    }


}

int ids_compare(const void *a, const void *b) {
    if (!a || !b){
        return 0;
    }
    return strcmp((const char *)a, ((commodity *)b)->id);
}

