/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

#include "proj5Tokens.h"
#include "proj5Arr.h"
//including the dynamic array class

void printCommands();
void processExpression (Token inputToken, TokenReader *tr);
int debugMode = false;//debug variable

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */
    int i;
    for(i = 0;i < argc; i++){
      if('-' == argv[i][0] && 'd' == argv[i][1]){
        debugMode = true;
        printf("Debug Mode Enabled\n");
      }
    }

    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 1;
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}
//function that evaluates two numbers with the given operator
int eval(int n1, char op, int n2){
  if(op == '+')
    return n1 + n2;
  else if(op == '-')
    return n1 - n2;
  else if(op == '*')
    return n1 * n2;
  else if(op == '/'){
    return n1 / n2;
  }
  return -999;//not a valid operator
}

void processExpression (Token inputToken, TokenReader *tr)
{
 /**********************************************/
 /* Declare both stack head pointers here      */
  dArr<int> *operands = new dArr<int>();//operands stack
  dArr<char> *operators = new dArr<char>();//operators stack
  char oper;//user input operator
  char topOper;//operator from the top of the stack
  int n3;//evaluation of two numbers

 /* Loop until the expression reaches its End */
 while (inputToken.equalsType(EOLN) == false)
   {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
       /* make this a debugMode statement */
       if(debugMode)
        printf ("Val: %d, ", inputToken.getValue() );

       // add code to perform this operation here
        operands->push(inputToken.getValue());
      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
       /* make this a debugMode statement */
        if(debugMode)
          printf ("OP: %c, ", inputToken.getOperator() );
        oper = inputToken.getOperator();
        n3 = 0;
       // add code to perform this operation here
        if(oper == '(')//open parenthesis
          operators->push(oper);
        if(oper == '+' || oper == '-'){//addition or subtraction
          topOper = operators->top();//gets the top of the stack operator
          while(!(operators->isEmpty()) && (topOper == '+' || topOper == '-' || topOper == '*' || topOper == '/')){
            //pop from the stacks and evaluate the operation
            char op = operators->top();
            operators->pop();
            int n2 = operands->top();
            operands->pop();
            int n1 = operands->top();
            operands->pop();
            n3 = eval(n1, op, n2);
            operands->push(n3);
          }
          operators->push(oper);
        }
        if(oper == '/' || oper == '*'){//multiplication and division
          topOper = operators->top();
          while(!(operators->isEmpty()) && (topOper == '*' || topOper == '/')){
            //pop from the stacks and evaluate the operation
            char op = operators->top();
            operators->pop();
            int n2 = operands->top();
            operands->pop();
            int n1 = operands->top();
            operands->pop();
            n3 = eval(n1, op, n2);
            operands->push(n3);
          }
          operators->push(oper);
        }
        if(oper == ')'){//closing parenthesis
          //evaluate until the other parenthesis is met
          while(!(operators->isEmpty()) && operators->top() != '('){
            //pop from the stacks and evaluate the operation
            char op = operators->top();
            operators->pop();
            int n2 = operands->top();
            operands->pop();
            int n1 = operands->top();
            operands->pop();
            n3 = eval(n1, op, n2);
            operands->push(n3);
          }
          if(operators->isEmpty()){//error in the input of parenthesis
            printf("Parenthesis are Incorrect");
          }else{//pop the operator
            operators->pop();
          }
        }
      }
    
    /* get next token from input */
    inputToken = tr->getNextToken ();
   }

 /* The expression has Freached its end */

 // add code to perform this operation here
  while(!(operators->isEmpty())){
    //pop from the stacks and evaluate the operation
    char op = operators->top();
    operators->pop();
    int n2 = operands->top();
    operands->pop();
    int n1 = operands->top();
    operands->pop();
    n3 = eval(n1, op, n2);
    operands->push(n3);
  }
  int result = operands->top();//gets the resulting integer
  operands->pop();
  if(!(operands->isEmpty())){
    printf("Incorrect Expression");
  }else{
    printf("Result: %d", result);//print the result
  }
 printf ("\n");
}