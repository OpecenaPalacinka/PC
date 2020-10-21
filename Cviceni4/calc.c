#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef float (*calc_func)(float a, float b);

#define forever while(1)

#define MAX_INPUT_LENGTH 16

float sum (float a, float b){
    return a + b;
}
float sub(float a, float b){
    return a - b;
}
float mul(float a, float b){
    return a * b;
}
float divide(float a, float b){
    return a / b;
}

int main(){
    char input[MAX_INPUT_LENGTH];
    float a, b;
    char op;
    calc_func handler;

    forever {
        printf("> ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        if (strncmp(input, "quit\n", MAX_INPUT_LENGTH) == 0){
            break;
        }
        sscanf(input, "%f%c%f", &a, &op, &b);
        switch (op)
        {
        case '+':
            handler = sum;
            break;
        case '-':
            handler = sub;
            break;
        case '*':
            handler = mul;
            break;
        case '/':
            handler = divide;
            break;        
        default:
            handler = NULL;
            break;
        }

        if(!handler){
            printf("Nepodporovaný operátor.\n");
        } else
        {
            printf("%f %c %f = %f", a, op, b, handler(a,b));
        }
        
    }
    
    printf("baaj!");
    return EXIT_SUCCESS;
}