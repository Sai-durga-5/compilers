
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int * array; // This is where elements are stores
    int number_of_elements; // Total elements in the array currently
    int max_elements; // Maximum number of elements in the array
} vector;

void initialize(vector ** vec){
    // TODO: IMPLEMENT THIS FUNCTION
    *vec = (vector *)malloc(sizeof(vector));
    (*vec)->number_of_elements = 0;
    (*vec)->max_elements = 2; 
    (*vec)->array = (int *)malloc(sizeof(int) * (*vec)->max_elements);
}

void push_back(vector * vec, int element){
    // TODO: IMPLEMENT THIS FUNCTION
    if (vec->number_of_elements >= vec->max_elements) {
        vec->max_elements *= 2;
        vec->array = (int *)realloc(vec->array, sizeof(int) * vec->max_elements);
    }
    vec->array[vec->number_of_elements++] = element;
}

int back(vector * vec){
    // TODO: IMPLEMENT THIS FUNCTION
    if (vec->number_of_elements == 0) return -1;
    return vec->array[vec->number_of_elements - 1];
}

int get_index(vector * vec, int index){
    // TODO: IMPLEMENT THIS FUNCTION
    if (index < 0 || index >= vec->number_of_elements) return -1;
    return vec->array[index];
}

void destroy(vector ** vec){
    // TODO: IMPLEMENT THIS FUNCTION
    free((*vec)->array);
    free(*vec);
    *vec = NULL;
    exit(0);
}

int main(){

    // Write the operation Loop
    vector *vec = NULL;
    int op_code, arg;

    while (1) {
        if (scanf("%d", &op_code) != 1) break;

        switch (op_code) {
            case 1: 
                initialize(&vec);
                break;
            case 2: 
                scanf("%d", &arg);
                push_back(vec, arg);
                break;
            case 3: 
                printf("%d\n", back(vec));
                break;
            case 4: 
                scanf("%d", &arg);
                printf("%d\n", get_index(vec, arg));
                break;
            case 5: 
                destroy(&vec);
                
            default:
                
                break;
        }
    }
    return 0;
}
