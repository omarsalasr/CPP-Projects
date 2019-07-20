/*test13.cpp*/

//
// <<Omar Salas>>
// U. of Illinois, Chicago
// CS 341, Spring 2019
// Project #01: Grade Analysis
// 


// *****************************************************************
//
// Test cases: Get Grade Distribution for a satisfactory course
// 
// *****************************************************************

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "gradeutil.h"
#include "catch.hpp"

using namespace std;


TEST_CASE( "Test 13", "[Project01]" ) 
{
  Course C = ParseCourse("CS,499,01,Professional Seminar,0,0,0,0,0,2,1,88,0,0,Hummel");

  GradeStats G = GetGradeDistribution(C);
  
  REQUIRE(G.N == 0);
  REQUIRE(G.NumA == 0);
  REQUIRE(G.NumB == 0);           
  REQUIRE(G.NumC == 0);
  REQUIRE(G.NumD == 0);
  REQUIRE(G.NumF == 0);
  
  REQUIRE(abs(G.PercentA - 0.0) < 0.001);
  REQUIRE(abs(G.PercentB - 0.0) < 0.001);
  REQUIRE(abs(G.PercentC - 0.0) < 0.001);
  REQUIRE(abs(G.PercentD - 0.0) < 0.001);
  REQUIRE(abs(G.PercentF - 0.0) < 0.001);

}
