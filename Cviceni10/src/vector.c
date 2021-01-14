#include "vector.h"

vector *vector_create(unsigned long item_size) {
    vector *v;

    if (item_size == 0){
        return NULL;
    }

    v = (vector *)malloc(sizeof(vector));
    if(!v){
        return NULL;
    }

    v->item_size = item_size;
    v->capacity = 0;
    v->count = 0;
    v->data = NULL;

    if(!vector_realloc(v,VECTOR_INIT_SIZE)){
        free(v);
        return NULL;
    }

    return v;
}

void vector_destroy(vector **v, vector_item_destroyer destroyer) {
    unsigned long i;
    if (!v || !*v){
        return;
    }
    if (destroyer) { /* Aha! Takže, to co zaobaluji jsou vlastně pointery!! */
        for (i = 0;i < (*v)->count; ++i){
            destroyer((void **)((*v)->data)+ i);
            *((void **)((*v)->data) + i ) = NULL;
        }
    }

    free((*v)->data);
    (*v)->data = NULL;

    (*v)->capacity = 0;
    (*v)->count = 0;
    free(*v);
    *v = NULL;
}

int vector_realloc(vector *v, unsigned long size) {
    void *data_temp;

   if (!v || v->capacity >= size){
       return 0;
   }
   v->capacity = size;

   data_temp = (void *)realloc(v->data, v->item_size * v->capacity);
   if (!data_temp){
       return 0;
   }
   v->data = data_temp;
   return v->capacity;
}

void *vector_at(vector *v, unsigned long at) {
   if (!v || at > v->count - 1){
       return NULL;
   }
    return (void *)((char *)v->data + (at * v->item_size));

}

int vector_pushback(vector *v, void *item) {
   if (!v || !item){
       return INVALID_INDEX;
   }
   if (v->count == v->capacity){
      if(!vector_realloc(v,v->capacity * VECTOR_SIZE_MULT)){
          return INVALID_INDEX;
      }
   }

   memcpy((void *)((char *)v->data + (v->count * v->item_size)), item, v->item_size);
   v->count++;

    return v->count -1;
}

int vector_isempty(vector *v) {
    return !v || vector_count(v) == 0;
}

int vector_count(vector *v) {
    return v ? v->count : 0;
}