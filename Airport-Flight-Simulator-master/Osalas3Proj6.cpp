#include "Proj6.h"

class TravelNetwork
{
 private:
    int arrSize;//size of the array of airports
    Airport* airportList;//airport array
    MyFileList* fileNames;//list of file names
  
 public:
  
 TravelNetwork()
 {
   arrSize = 10;
   airportList = new Airport[arrSize];//allocates memory for the airport array
   fileNames = new MyFileList();//allocates memory for the file name list
 }
  
  
 // The main loop for reading in input
 void processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) 
      exit(1);
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();
    
    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
 void showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
  //  printf("Name:%s",fileName);
 }
 
  void doTravel(){
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
   
   
   printf ("Performing the Travel Command from %d to %d\n", 
            val1, val2);
    //call the helper function
    depthFirstSearchHelper(val1,val2);
   
  }

  private:
    //recursive depth first search function
    bool dfs(int a, int b){
      int i,c;
      for(i = 0; i < airportList[a-1].getList()->getSize(); i++){//goes through the linked list
        c = airportList[a-1].getList()->getNthValue(i);//gets the destination airport
        if(c == b)
          return true;
        if(!airportList[c-1].wasVisited()){//check if it was visited
          airportList[a-1].changeVisited(true);
          if(dfs(c,b))//recursive call to the new airport
            return true;
        }
      }
      return false;
    }
  //helper function for depth first search
  void depthFirstSearchHelper (int x, int y){
    int i;
    for(i = 0; i < arrSize; i++){//reset visited
      airportList[i].resetVisit();
    }
    //condition to check if there exists a path
    if(dfs(x, y) == true)
      printf("You can get from airport %d to airport %d in one or more flights.\n", x, y);
    else
      printf("You can NOT get from airport %d to airport %d in one or more flights.\n",x,y);
  }

  public:
 
  void doResize(){
   int val1 = 0;
   // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
    if(val1 < 1){
      printf("Input must be greater than 0\n");
      return;
    }
    printf ("Performing the Resize Command with %d\n", val1 );

    delete airportList;//deallocate memory
    airportList = new Airport[val1];//allocate a new airport array with new size
    arrSize = val1;
  }
 
  void doInsert(){
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
    if(val1 < 1 || val1 > arrSize || val2 < 1 || val2 > arrSize){//check if the inputs are valid
      printf("Not a valid airport.\n");
      return;
    }
    printf ("Performing Insert from airport %d to airport %d\n", val1, val2 );
    airportList[val1-1].getList()->insertFront(val2);//insert into the correct airport
  }
 
  void doDelete(){
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");
    if ( next == NULL ){
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0){
      printf ("Integer value expected\n");
      return;
    }

    if(val1 < 1 || val1 > arrSize || val2 < 1 || val2 > arrSize){//check if the input is valid
      printf("Not a valid airport.\n");
      return;
    }
    printf("Performing deletion from airport %d to airport %d.\n", val1, val2);
    airportList[val1-1].getList()->remove(val2);//deletes the edge if it exists
  }
 
  void doList(){//prints the airports and its edges
    printf("Performing the list comand.\n");
    int i, j, edges;
    for(i = 0; i < arrSize; i++){
      printf("Airport %d: ", i+1);
      airportList[i].getList()->printList();
      printf("\n");
    }
  }
 
  void doFile(){
    // get a filename from the input
    char* fname = strtok (NULL, " \n\t");
    if ( fname == NULL )
    {
      printf ("Filename expected\n");
      return;
    }

    if(fileNames->contains(fname)){//checks if the filename is already used
      printf("File name already used.\n");
      return;
    }
    printf ("Performing the File command with file: %s\n", fname);
    fileNames->insertFront(fname);//insert into the list
    FILE* inFile = fopen(fname, "r");//open the file
    processCommandLoop (inFile);//recursive call to command loop
    fclose(inFile);//closes the file
    fileNames->remove(fname);//removes from the list
  }
};

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the airport adjcency list
  TravelNetwork airportData;
   
  // call the method that reads and parses the input
  airportData.processCommandLoop (inFile);
   
  printf ("Goodbye\n");
  return 1;
 }
