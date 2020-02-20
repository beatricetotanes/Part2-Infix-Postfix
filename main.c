#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*--------------------------------STRUCTURE-----------------------------------*/

struct NODE{
    char info;
    char arr[100];
    struct NODE *next;
};

struct NODE1{
    char arr[100];
    struct NODE *next;
};

/*--------------------------------FUNCTION PROTOTYPES-----------------------------------*/
void evaluate(struct NODE **queu, struct NODE **stack);
void initialize(struct NODE **queu, struct NODE **stack);
int stackDigit(char digit2);
void greater(struct NODE **stack, char digit);
void ifQ(struct NODE **queu, char digit);
void veryStartOfStack(struct NODE **queu, struct NODE **stack, char digit, int value);
void notGreater(char digit, struct NODE **stack, struct NODE **queu);
int is_operator(char digit);

/*--------------------------------MAIN FUNCTION-----------------------------------*/

int main() {
    struct NODE *queu; //Main basis for queu; Queu is adding at the last
    struct NODE *stack = NULL; //Main basis for stack; Stack is adding at the beginning
    struct NODE *stackForEvaluate;
    char entry[50];
    unsigned long length;
    int count = 0;
    int value;
    char digit;
    int stackValue;
    
    initialize(&queu, &stack);
    
    
    printf("Enter input: ");
    scanf("%s", entry);
    
    length = strlen(entry);
    
    while (count<=length) {
        digit = entry[count];
        if (count==length) {
            value = 1;
        } else {
            value = is_operator(digit);
        }
        
        if (value==0) {
            ifQ(&queu, digit);
        }else{
            if (stack!=NULL) {
                stackValue = is_operator(stack->info);
                if (value<=stackValue) {
                    do {
                        notGreater(digit, &stack, &queu);
                        if ((stack==NULL)&&(count==length-1)) {
                            break;
                        }
                        if (stack==NULL) {
                            greater(&stack, digit);
                            stackValue = 0;
                        }else{
                            stackValue = is_operator(stack->info);
                        }
                    } while (value<=stackValue);
                } else {
                    greater(&stack, digit);
                }
            }else{
                veryStartOfStack(&queu, &stack, digit, value);
            }
        }
        count++;
    }
    
    //Diplay final queu-------------------------------
    struct NODE *tmp;
    tmp = queu;
    printf("Result for Queu: ");
    while (tmp!=NULL) {
        printf("%c", tmp->info);
        tmp = tmp->next;
    }
    
    
    /*
     OPTIONAL TO PRINT STACK
     struct NODE *tmpS;
     tmpS = stack;
     printf("\nResult for Stack: ");
     while (tmpS!=NULL) {
     printf("%c", tmpS->info);
     tmpS = tmpS->next;
     }
     
     //Start of evaluating queue
     
     while (queu!=NULL) {
     evaluate(&queu, &stack);
     }*/
    
    //LAB03 Ma'am Maui:
    evaluate(&queu, &stackForEvaluate);
    
    return 0;
}

/*--------------------------------END OF MAIN FUNCTION-----------------------------------*/

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
void notGreater(char digit, struct NODE **stack, struct NODE **queu){
    struct NODE *tempQueu;
    struct NODE *tempInfo;
    
    tempInfo = (struct NODE*)malloc(sizeof(struct NODE));
    tempQueu = *queu; //Traveller from node to node to access the last node of queu
    tempInfo->info = (*stack)->info; //Stores the information of stack and is no way connected to the linked list stack
    tempInfo->next = NULL;
    while (tempQueu->next!= NULL) { //Loop to find the last node of queu
        tempQueu = tempQueu->next;
    }
    tempQueu->next = tempInfo; //Assigning/moving the first node of stack to queu
    *stack = (*stack)->next; //The first node of stack will move on to the next node in stack.
    
}

/*5. OPERATOR IN THE STRING INPUTTED BY USER IS GREATER THAN THE OPERATOR IN STACK (BASED ON PRECEDENCE)*/
void greater(struct NODE **stack, char digit){
    struct NODE *newInfo;
    newInfo = (struct NODE*)malloc(sizeof(struct NODE));
    newInfo->info = digit;
    if ((*stack)==NULL) {
        *stack = newInfo;
    } else {
        newInfo->next = *stack; //Connects the node to the first node of stack and is starting to insert itself before the first node
        *stack = newInfo; //newInfo now becomes the first node
    }
    
}

/*6. IF STACK IS EMPTY, THE OPERATOR WILL BE ASSIGNED AS THE FIRST NODE*/
void veryStartOfStack(struct NODE **queu, struct NODE **stack, char digit, int value){
    struct NODE *newInfo;
    newInfo = (struct NODE*)malloc(sizeof(struct NODE));
    newInfo->info = digit;
    newInfo->next = NULL;
    *stack = newInfo; //Assigns newInfo to stack
}

/*7. Compute*/
void evaluate(struct NODE **queu, struct NODE **stack){
    struct NODE *newInfo;
    struct NODE *tempQueu = *queu;
    struct NODE *tmpQ;
    struct NODE *tmpS;
    char *stackChar = NULL;
    int opValue = 0;
    int value = 2;
    int count = 0;
    int num1 = 0;
    int num2 = 0;
    int ans = 0;
    int n, c;
    char character;
    struct NODE *converted;
    converted = (struct NODE*)malloc(sizeof(struct NODE));
    char convertedAns;
    char tmpNum1[100];
    char tmpNum2[100];
    
    *stack = NULL;
    
    do {
        while (tempQueu!=NULL && value!=1) {
            newInfo = (struct NODE*)malloc(sizeof(struct NODE));
            character = (tempQueu)->info;
            newInfo->info = character;
            newInfo->next = NULL;
            if (character == '*' || character == '/' || character == '+' || character == '-'){
                tmpQ = tempQueu;
                free(tmpQ);
                value = 1;
            }else {
                if (stack==NULL) {
                    tmpQ = tempQueu;
                    *stack = newInfo; //Assigns newInfo to stack
                    printf("Stack: %c", (*stack)->info);
                    free(tmpQ);
                    value = 2;
                } else {
                    tmpQ = tempQueu;
                    free(tmpQ);
                    newInfo->next = *stack;
                    *stack = newInfo;
                    value = 2;
                }
            }
            tempQueu = tempQueu->next;
        }
        
        //TESTER
        struct NODE *tmp;
        tmp = *stack;
        printf("\nResult for Stack: ");
        while (tmp!=NULL) {
            printf("%c", tmp->info);
            tmp = tmp->next;
        }
        
         while (count<2) {;
             if (count==0) {
                 num1 = (*stack)->info - '0';
                 //num1 = atoi(stackChar);
                 printf("\nNum1: %d", num1);
                 tmpS = *stack;
                 *stack = (*stack)->next;
                 free(tmpS);
             
             } else {
                 //num2 = atoi(&(*stack)->info);
                 num2 = (*stack)->info - '0';
                 printf("\nNum2: %d", num2);
                 tmpS = *stack;
                 *stack = (*stack)->next;
                 free(tmpS);
             }
             count++;
         }
         
         if (newInfo->info == '*') {
             opValue = 4;
         } else if(newInfo->info == '/'){
             opValue = 3;
         } else if(newInfo->info == '+'){
             opValue = 2;
         }else if(newInfo->info == '-'){
             opValue = 1;
         }
         
         if (opValue == 4 || opValue == 3 || opValue == 2 || opValue == 1) {
         switch (opValue) {
         case 1:
         ans = num1 - num2;
         break;
         case 2:
         ans = num1 + num2;
         break;
         case 3:
         ans = num1/num2;
         break;
         case 4:
         ans = num1*num2;
         break;
         }
         }
         
         
         //convertedAns = sprintf(storage, "%d", ans);
         converted->info = convertedAns;
         if ((*stack)==NULL) {
         (*stack) = converted;
         }else{
         converted->next = *stack;
         *stack = converted;
         }
         
        
    } while (queu!=NULL);
    
    // printf("Result: %c", (*stack)->info);
}


/*--------------------------------END OF FUNCTIONS-----------------------------------*/



