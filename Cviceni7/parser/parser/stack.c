#include "stack.h"

stack *stack_create(uns_int size, uns_int item_size){
    stack *new;

    if (!size || !item_size){
        return NULL;
    }
    new = (stack *)malloc(sizeof(stack));
    if (!new){
        return NULL;
    }

    new->size = size;
    new->item_size = item_size;
    new->sp = -1;           /** Zásobník je prázdný */

    new->items = malloc(size * item_size);
    if (!new->items){
        free(new);
        return NULL;
    }

    return new;
}

int stack_push(stack *s, void *item){
    if (!s || !item || !s->items || s->sp >= (int)s->size - 1){
        return 0;
    }

    s->sp++;
    memcpy((char *)s->items + s->sp * s->item_size,item, s->item_size);
    return 1;
}

int stack_pop(stack *s, void *item){
    if (stack_head(s,item)){
        s->sp--;
        return 1;
    } else {
        return 0;
    }
}

int stack_head(stack *s, void *item){
    if (!s || !s->items || s->sp <0 ){
        return 0;
    }
    memcpy(item,(char *)s->items + s->sp * s->item_size, s->item_size);
    return 1;
}

uns_int stack_item_count(stack *s){
    if (!s){
        return 0;
    }
    return (uns_int)(s->sp + 1);
}

void stack_free(stack **s){
    if(!s || !*s){
        return;
    }
    free((*s)->items);
    free(*s);
    *s = NULL;
}