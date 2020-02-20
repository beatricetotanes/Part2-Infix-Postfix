#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*--------------------------------STRUCTURE-----------------------------------*/

struct NODE{
    char info;
    struct NODE *next;
};

/*--------------------------------FUNCTION PROTOTYPES-----------------------------------*/
void push(struct NODE **stack, struct NODE **queue);
int pop(struct NODE **stack);
int dequeue(struct NODE **queue);
void pushString(struct NODE **stack, struct NODE **answer);
void initialize(struct NODE **queu, struct NODE **stack);
int stackDigit(char digit2);
void greater(struct NODE **stack, struct NODE **tempInfo);
void ifQ(struct NODE **queu, char digit);
int precedence(char digit1, char digit2);
//void veryStartOfStack(struct NODE **queu, struct NODE **stack, char digit, int value);
void notGreater(struct NODE **stack, struct NODE **temp, struct NODE **queu);
int is_operator(char digit);

/*--------------------------------MAIN FUNCTION-----------------------------------*/

int main() {
    struct NODE *queu = NULL; //Main basis for queu; Queu is adding at the last
    struct NODE *stack = NULL; //Main basis for stack; Stack is adding at the beginning
    char entry[50];
    unsigned long length;
    int count = 0;
    int value;
    char digit;
    struct NODE *tempQueue;
    struct NODE *stackStorageTmp;
    
    initialize(&queu, &stack);
    
    
    printf("Enter input: ");
    scanf("%s", entry);
    
    length = strlen(entry);
    
    while (count<= (length-1)) {
        digit = entry[count];
        value = is_operator(digit);
        
        if (value==0){
            ifQ(&queu, digit);
        }else {
            struct NODE *tempInfo;
            tempInfo = (struct NODE*)malloc(sizeof(struct NODE));
            tempInfo->info = digit;
            tempInfo->next = NULL;
            if (stack == NULL) stack = tempInfo;
            else {
                struct NODE *temp = stack;
                while (temp!=NULL) {
                    if (precedence(tempInfo->info, temp->info) == 1) greater(&stack, &tempInfo);
                    else if (precedence(tempInfo->info, temp->info) == 0) notGreater(&stack, &temp, &queu);
                    temp = temp->next;
                }
                if (stack == NULL) stack = tempInfo;
            }
        }
        count++;
    }
    
    tempQueue = queu;
    while (tempQueue->next!=NULL) {
        tempQueue = tempQueue->next;
    }
    while (stack!=NULL) {
        stackStorageTmp = (struct NODE*)malloc(sizeof(struct NODE));
        stackStorageTmp->info = stack->info;
        tempQueue->next = stackStorageTmp;
        if (tempQueue->next!=NULL) {
            tempQueue = tempQueue->next;
        }
        if (stack!=NULL) {
            stack = stack->next;
        }
    }
    
    //Diplay final queu-------------------------------
    struct NODE *tmp;
    tmp = queu;
    printf("Result for Queu: ");
    while (tmp!=NULL) {
        printf("%c", tmp->info);
        tmp = tmp->next;
    }
    
    
    
    /*OPTIONAL TO PRINT STACK
    struct NODE *tmpS;
    tmpS = stack;
    printf("\nResult for Stack: ");
    while (tmpS!=NULL) {
        printf("%c", tmpS->info);
        tmpS = tmpS->next;
    }*/
    
    //LAB03 Ma'am Maui:
    char digit1;
    char digit2;
    char operator;
    int opValueForEval = 0;
    struct NODE *stackForEvaluate;
    int num1;
    int num2;
    struct NODE *newNodeEval;
    char dequeueChar;
    int answer;
    int opValue = 0;
    stackForEvaluate = NULL;
    stack = NULL;
    
    while (queu!=NULL) {
        newNodeEval = (struct NODE*)malloc(sizeof(struct NODE));
        newNodeEval->next = NULL;
        do {
            push(&stackForEvaluate, &queu);
            dequeueChar= dequeue(&queu);
            opValue = is_operator(dequeueChar);
            
        } while (opValue==0);
        
        
        operator = pop(&stackForEvaluate);
        printf("\nOperator: %c", operator);
        digit1 = pop(&stackForEvaluate);
        printf("DIGIT 1: %c", digit1);
        num1 = digit1 - '0';
    
        printf("\nNum1: %d", num1);
        digit2 = pop(&stackForEvaluate);
        num2 = digit2 - '0';
        printf("\nNum2: %d", num2);
        
        if (operator=='*') {
            opValueForEval = 4;
        }else if (operator=='/'){
            opValueForEval = 3;
        }else if (operator=='+'){
            opValueForEval = 2;
        }else if (operator=='-'){
            opValueForEval = 1;
        }

        switch (opValueForEval) {
            case 1:
                answer = num2 - num1;
                break;
            case 2:
                answer = num1 + num2;
                break;
            case 3:
                answer = num1 / num2;
                break;
            case 4:
                answer = num1 * num2;
                break;
        }
        
        char intToChar;
        
        intToChar = answer + '0';
        newNodeEval->info = intToChar;

        pushString(&stackForEvaluate, &newNodeEval);
        printf("\nAnswer: %d", answer);
        struct NODE *tempQ;
        tempQ = queu;
        printf("\nResult for Queu: ");
        while (tempQ!=NULL) {
            printf("%c", tempQ->info);
            tempQ = tempQ->next;
        }
        
        struct NODE *tempS;
        tempS = stackForEvaluate;
        printf("\nResult for Stack:");
        while (tempS!=NULL) {
            printf("%c", tempS->info);
            tempS = tempS->next;
        }
        
        
        
        
    }
    
    struct NODE *tempS;
    int finalValue;
    tempS = stackForEvaluate;
    finalValue = tempS->info - '0';
    printf("\nFINAL Value of Stack: %d ", finalValue);

    
    return 0;
    
}
/*--------------------------------START OF FUNCTIONS------------------------------------*/


/*1. INITIALIZE FUNCTION
 To initialize and ensure that queu and stack are NULL and is empty.*/
void initialize(struct NODE **queu, struct NODE **stack){
    *queu = *stack = NULL;
}

/*2. CHECK IF OPERATOR OR NUMBER (AND PRECEDENCE)*/
int is_operator(char digit) {
    if (digit == '*' || digit == '/'){ //Multiplication & division have higher precedence than addition and subtraction
        return 2;
    }else if (digit == '+' || digit == '-'){ //Addition & subtraction has higher precedence than multiplication & division
        return 1;
    }else {
        return 0; //Returns '0' if number
    }
}
int precedence(char digit1, char digit2) {
    if (digit1 == '*' && digit2 == '+') return 1;
    if (digit1 == '*' && digit2 == '-') return 1;
    if (digit1 == '/' && digit2 == '+') return 1;
    if (digit1 == '/' && digit2 == '-') return 1;
    return 0;
}

/*3. ADD NUMBERS TO QUEU
 If one of the inputs is a number, it will be put in the queu list*/
void ifQ(struct NODE **queu, char digit){
    
    struct NODE *prev;
    struct NODE *newInfo;
    prev = *queu;
    newInfo = (struct NODE*)malloc(sizeof(struct NODE));
    newInfo->info = digit;
    newInfo->next = NULL;
    if(*queu==NULL){
        *queu = newInfo;
    }else{
        while (prev->next != NULL) {
            prev = prev->next;
        }
        prev->next = newInfo;
    }
    
}

/*4. OPERATOR IN THE STRING INPUTTED BY USER IS LESS THAN THE OPERATOR IN STACK (BASED ON PRECEDENCE)
 To put the element in stack into the linked list queu until the digit is greater than the operator in stack.*/
void notGreater(struct NODE **stack, struct NODE **temp, struct NODE **queu){
    struct NODE *tempQueu = *queu;
    struct NODE *newInfo;
    newInfo = (struct NODE*) malloc (sizeof(struct NODE));
    newInfo->info = (*temp)->info; //Stores the information of stack and is no way connected to the linked list stack
    newInfo->next = NULL;
    *stack = (*temp)->next; //The first node of stack will move on to the next node in stack.
    if (*queu == NULL) *queu = newInfo;
    else {
        while (tempQueu->next!= NULL) { //Loop to find the last node of queu
            tempQueu = tempQueu->next;
        }
        tempQueu->next = newInfo; //Assigning/moving the first node of stack to queu
    }
    
}

/*5. OPERATOR IN THE STRING INPUTTED BY USER IS GREATER THAN THE OPERATOR IN STACK (BASED ON PRECEDENCE)*/
void greater(struct NODE **stack, struct NODE **tempInfo){
    (*tempInfo)->next = *stack; //Connects the node to the first node of stack and is starting to insert itself before the first node
    *stack = *tempInfo; //newInfo now becomes the first node
}

/*6. IF STACK IS EMPTY, THE OPERATOR WILL BE ASSIGNED AS THE FIRST NODE*/
/*void veryStartOfStack(struct NODE **queu, struct NODE **stack, char digit, int value){
 struct NODE *newInfo;
 newInfo = (struct NODE*)malloc(sizeof(struct NODE));
 newInfo->info = digit;
 newInfo->next = NULL;
 *stack = newInfo; //Assigns newInfo to stack
 }*/

//ADDITIONAL FOR LAB3
void push(struct NODE **stack, struct NODE **queue){
    struct NODE *newInfo;
    char character = (*queue)->info;
    newInfo = (struct NODE*)malloc(sizeof(struct NODE));
    if (*stack==NULL) {
        newInfo->info = character;
        *stack = newInfo;
    }else{
        newInfo->info = character;
        newInfo->next = (*stack);
        *stack = newInfo;
    }
}

void pushString(struct NODE **stack, struct NODE **answer){
    struct NODE *newInfo;
    newInfo = (struct NODE*)malloc(sizeof(struct NODE));
    newInfo->info = (*answer)->info;
    if (*stack==NULL) {
        *stack = newInfo;
    }else{
        newInfo->next = (*stack);
        *stack = newInfo;
    }
}


int pop(struct NODE **stack){
    struct NODE *tmp;
    char character;
    tmp = *stack;
    character = (tmp)->info;
    if (*stack!=NULL) {
        *stack = (*stack)->next;
    }
    free(tmp);
    return character;
}


int dequeue(struct NODE **queue){
    struct NODE *tmp;
    char character;
    tmp = *queue;
    character = tmp->info;
    *queue = (*queue)->next;
    free(tmp);
    return character;
}



/*--------------------------------END OF FUNCTIONS-----------------------------------*/



