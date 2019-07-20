# CPP-Gridworld-Simulations (Data Structures)
Gridworld that simulates the birth, death, and several movements of people in a district within the grid.

The simulation has several functions that have very fast runtimes so that the simulation executes with efficiency

Execution: ./gw

Input:

  birth \<row> \<col> - give birth to a person with a unique ID in the given district
  
  death \<id> - sends the person with the given ID to the graveyard leaving the ID open for the next birth
  
  move \<id> \<target-row> \<target-col> - move the person with the given ID to the new location specified
  
  members \<row> \<col> - prints the members in the given district (row,col) in order of seniority
  
  whereis \<id> - prints the district location in which the person with the given ID lives in
  
  population - total world population
  
  population \<row> \<col> - total district population
  
  num_rows - prints the number of rows in the grid
  
  num_cols - prints the number of columns in the grid
  
  quit - quits the program
