/*
    To practice malloc, this is a simple program that allows the user to add numbers to an array, and then print said array.
    I am aware that scanf() is the big bad in C, but I have not yet learned how to use fgets properly, and that is not the focus of this program. 
    The main point of this program is proper use of malloc, realloc, and pointer safety. I will not worry about user input validation for this reason.
    This is not AI generated. The over commenting is to help me as a beginner get comfortable dancing around a C code base. 
*/

#include <stdio.h>
#include <stdlib.h>

void printMenu(int* userChoice) {
    printf("Please choose an option: \n\n");
    printf("1: Add an element to the array\n");
    printf("2: Print the array\n");
    printf("3: Set the array to all zeroes\n");
    printf("4: Exit the program\n\n");
    printf("Choice: ");

    scanf("%d", userChoice);
}

int doubleArraySize(int** array, int* size) {
    int* array2 = realloc(*array, (*size * sizeof(int)) * 2);

    if(array2 == NULL) {
        return 1;
    } else {
        *array = array2;
        *size = *size * 2;
        return 0;
    }
}

void addElementInternal(int** array, int number, int* count, int* size) {
    if(*count == *size) {
        int result = doubleArraySize(array, size); // Double the array size if array is already at capacity

        if(result == 1) {
            printf("Realloc failed... not adding element");
            return;
        }
    }

    (*array)[*count] = number;
    *count = *count + 1;
    printf("Count: %d, Size: %d", *count, *size);
    printf("\n\n");
}

void addElement(int** array, int* count, int* size) {
    printf("What number would you like to add to the array?\n\n");
    printf("Numer: ");

    int userInput;
    scanf("%d", &userInput);

    addElementInternal(array, userInput, count, size);
}

void printArray(int* array, int count) {
    for(int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");
}

int* zeroArray(int* array, int* count, int size) {
    int* array2 = malloc(size * sizeof(int));  // I am aware use of heap memory is inefficient, but this example is to get a rep using heap memory after a function call
    
    if(array2 == NULL) {
        printf("Memory allocation failed, not zeroing array.\n");
        return array;
    }

    for(int i = 0; i < size; i++) {
        array2[i] = 0;
    }

    *count = size;

    printf("Count: %d, Size: %d", *count, size);
    printf("\n\n");

    free(array);
    return array2;
}

int main() {
    int size = 2; // size of the array. Will double it when reached
    int currentCount = 0; // Number of elements currently in array

    int* array = malloc(sizeof(int) * size); // Allocate memory for an array with enough space for size ints

    if(array == NULL) {
        printf("Initial memory allocation failed\n");
        return 1;
    }

    printf("Welcome to the program! ");

    int userChoice;

    do {
        printMenu(&userChoice);

        switch (userChoice) {
            case 1:
                addElement(&array, &currentCount, &size);
                break;
            case 2:
                printArray(array, currentCount);
                break;
            case 3:
                array = zeroArray(array, &currentCount, size);
                break;
            default:
                break;
        }
    }
    while(userChoice != 4);

    free(array);
    return 0;
}