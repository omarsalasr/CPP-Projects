# CPP-Airport-Flight-Simulator
Program that simulates airports and all of it's incoming and outgoing flights

The program utilizes a linked list setup in form of c++ classes which act as an adjacency list to each airport. The list is made up of the outgoing edges from airport A to airport B.

Terminal Compilation: make

Input:

  q - quit the program
  
  ? - display a list of commands the user can enter for the program
  
  \# - ignore this line of input
  
  t <int1> <int2> - display a message stating whether a person can travel from airport <int1> to airport <int2> in one or more flights 
  
  r <int> - remove all values from the traffic network and resize the array to contain the number of aiports as indicated by the given integer value. The value of the integer must be greater than zero.
  
  i <int1> <int2> - insert the edge to indicate a plane flies from airport <int1> to airport <int2>
  
  d <int1> <int2> - delete the edge that indicates a plane flying from airport <int1> to airport <int2>
  
  l - list all the items contained in the travel network. First display all of the airports (if any) that can be reached from the aiport #1 in one flight (that have an edge in the network), followed by all the airports (if any) that can be reachede from airport #2 in one flight, etc.
  
  f <filename> - open the file indicates by the <filename> (assume it is in the current directory) and read commands from this file. When the end of the file is reached, continue reading commands from previous input source.
  
