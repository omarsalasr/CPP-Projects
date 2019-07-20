/*gradeutil.cpp*/

//
// <<Omar Salas-Rodriguez>>
// U. of Illinois, Chicago
// CS 341, Spring 2019
// Project #03: GradeUtil
// 

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#include "gradeutil.h"

using namespace std;


//
// API:
//

// 
// ParseCourse:
//
// Parses a CSV (comma-separated values) line into a Course
// object, which is then returned.  The given line must have
// the following format:
//
//   Dept,Number,Section,Title,A,B,C,D,F,I,NR,S,U,W,Instructor
//
// Example:
//   BIOE,101,01,Intro to Bioengineering,22,8,2,1,0,1,0,0,0,5,Eddington
//
// Note the lack of spaces, except perhaps in the title.
// If the given line does not have this format, the behavior 
// of the function is undefined (it may crash, it may throw
// an exception, it may return).
//
Course ParseCourse(string csvline)
{
  // intialize values
  string  Dept = "";
  string Title = "";
  string Instructor = "";
  string Number = "";
  string Section = "";
  string NumA = "";
  string NumB = "";
  string NumC = "";
  string NumD = "";
  string NumF = "";
  string NumI = "";
  string NumS = "";
  string NumU = "";
  string NumW = "";
  string NumNR = "";
  
  // open a stringstream for data extraction
  stringstream ss(csvline);
    
  // get all the elements from the csvline  
  getline(ss, Dept, ',');
  getline(ss, Number, ',');
  getline(ss, Section, ',');
  getline(ss, Title, ',');
  getline(ss, NumA, ',');
  getline(ss, NumB, ',');
  getline(ss, NumC, ',');
  getline(ss, NumD, ',');
  getline(ss, NumF, ',');
  getline(ss, NumI, ',');
  getline(ss, NumNR, ',');
  getline(ss, NumS, ',');
  getline(ss, NumU, ',');
  getline(ss, NumW, ',');
  getline(ss, Instructor);
  
  // return a course with the data from the csvline
  return Course(Dept, Title, stoi(Number), stoi(Section), Instructor,
         stoi(NumA), stoi(NumB), stoi(NumC), stoi(NumD), stoi(NumF), stoi(NumI), stoi(NumS), stoi(NumU), stoi(NumW), stoi(NumNR));
}


//
// GetDFWRate:
//
// Returns the DFW rate as a percentage for a given course, 
// department, or college.  For a course whose grading type 
// is defined as Course::Letter, the DFW rate is defined as
// 
//   # of D grades + F grades + Withdrawals
//   -------------------------------------- * 100.0
//   # of A, B, C, D, F grades + Withdrawls
//
// The numerator is returned via the reference parameter DFW;
// the denominator is returned via the reference parameter N.
// If the course grading type is not Course::Letter, the DFW
// rate is 0.0, and parameters DFW and N are set to 0.  
//
// When computed for a dept or college, all courses of type 
// Course::Letter are considered in computing an overall DFW 
// rate for the dept or college.  The reference parameters 
// DFW and N are also computed across the dept or college.
//
double GetDFWRate(const Course& c, int& DFW, int& N)
{
  DFW = 0;
  N   = 0;
  
  // Check if the course is a letter course
  if(c.getGradingType() == Course::Letter){
      DFW = c.NumD + c.NumF + c.NumW;
      N = c.NumA + c.NumB + c.NumC + DFW;
      return (DFW * 100.0) / N;
  }
  
  return 0.0;
}

double GetDFWRate(const Dept& dept, int& DFW, int& N)
{
  DFW = 0;
  N   = 0;
  int tempDFW = 0;
  int tempN = 0;
    
  // Iterate through each course in the department
  for(Course c : dept.Courses){
      GetDFWRate(c, tempDFW, tempN); // Call overloaded method
      DFW += tempDFW;
      N += tempN;
  }
  if(N <= 0){ // Prevent a division by 0 Error
      DFW = 0;
      return 0.0;
  }
  
  return (DFW * 100.0) / N;
}

double GetDFWRate(const College& college, int& DFW, int& N)
{
  DFW = 0;
  N   = 0;
  int tempDFW = 0;
  int tempN = 0;
    
  // Iterate through each course in the department
  for(Dept d: college.Depts){
      GetDFWRate(d, tempDFW, tempN); // Call overloaded method
      DFW += tempDFW;
      N += tempN;
  }
  if(N <= 0){ // Prevent a division by 0 Error
      DFW = 0;
      return 0.0;
  }
  
  return (DFW * 100.0) / N;
}  


//
// GetGradeDistribution
//
// Returns an object containing the grade distribution for a given
// course, dept or college.  For a course whose grading type is
// defined as Course::Letter, the grade distribution is defined by
// the following values:
//
//   N: the # of A, B, C, D, F grades
//   NumA, NumB, NumC, NumD, NumF: # of A, B, C, D, F grades
//   PercentA, PercentB, PercentC, PercentD, PercentF: % of A, B, 
//     C, D, F grades.  Example: PercentA = NumA / N * 100.0
//
// If the course grading type is not Course::Letter, all values
// are 0.  When computed for a dept or college, all courses of
// type Course::Letter are considered in computing an overall 
// grade distribution for the dept or college.
//
GradeStats GetGradeDistribution(const Course& c)
{
  int N = 0;
  // Check if the course is a letter course
  if(c.getGradingType() == Course::Letter){
      N = c.NumA + c.NumB + c.NumC + c.NumD + c.NumF;
      return GradeStats(N, c.NumA, c.NumB, c.NumC, c.NumD, c.NumF,
             (c.NumA * 100.0)/N, (c.NumB * 100.0)/N, (c.NumC * 100.0)/N, (c.NumD * 100.0)/N, (c.NumF * 100.0)/N);
  }
  
  return GradeStats(0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0);  
}

GradeStats GetGradeDistribution(const Dept& dept)
{
  int N = 0;
  int numA = 0;
  int numB = 0;
  int numC = 0;
  int numD = 0;
  int numF = 0;
    
  GradeStats g;
    
  // Go through each course in the department
  for(Course c: dept.Courses){
      g = GetGradeDistribution(c); // Get each grade distribution for a course
      N += g.N;
      numA += g.NumA;
      numB += g.NumB;
      numC += g.NumC;
      numD += g.NumD;
      numF += g.NumF;
  }
  if(N == 0){
      return GradeStats(0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0);  
  }
  return GradeStats(N, numA, numB, numC, numD, numF,
             (numA * 100.0)/N, (numB * 100.0)/N, (numC * 100.0)/N, (numD * 100.0)/N, (numF * 100.0)/N);
}

GradeStats GetGradeDistribution(const College& college)
{
  
  int N = 0;
  int numA = 0;
  int numB = 0;
  int numC = 0;
  int numD = 0;
  int numF = 0;
    
  GradeStats g;
    
  // Go through each course in the department
  for(Dept d: college.Depts){
      g = GetGradeDistribution(d); // Get each grade distribution for a course
      N += g.N;
      numA += g.NumA;
      numB += g.NumB;
      numC += g.NumC;
      numD += g.NumD;
      numF += g.NumF;
  }
  if(N == 0){
      return GradeStats(0, 0, 0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0);  
  }
  
  return GradeStats(N, numA, numB, numC, numD, numF,
             (numA * 100.0)/N, (numB * 100.0)/N, (numC * 100.0)/N, (numD * 100.0)/N, (numF * 100.0)/N);
}

//
// FindCourses(dept, courseNumber)
//
// Searches the courses in the department for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, and returned in
// ascending order by section number.
//
vector<Course> FindCourses(const Dept& dept, int courseNumber)
{
    
  vector<Course>  courses;
     
  if(courseNumber < 0)
      return courses;
    
  // Push back all the courses with the same Course Number
  for(Course c: dept.Courses)
      if(c.Number == courseNumber && c.getGradingType() == Course::Letter)
          courses.push_back(c);
    
  // Sort the courses in ascending order by section number
  sort(courses.begin(), courses.end(),
       [](Course c1, Course c2){
          if(c1.Section < c2.Section)
              return true;
          else
              return false;
       }

  );
    
  return courses;
}


//
// FindCourses(dept, instructorPrefix)
//
// Searches the courses in the department for those whose 
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".
//
// If none are found, then the returned vector is empty.  If 
// one or more courses are found, copies of the course objects
// are returned in a vector, with the courses appearing in 
// ascending order by course number.  If two courses have the 
// same course number, they are given in ascending order by 
// section number.  Note that courses are NOT sorted by instructor
// name.
//
vector<Course> FindCourses(const Dept& dept, string instructorPrefix)
{
  vector<Course>  courses;
  
  for(Course c: dept.Courses)
      if(c.Instructor.find(instructorPrefix) == 0)
          courses.push_back(c);
      
  
    
  sort(courses.begin(), courses.end(),
       [](Course c1, Course c2){
            if(c1.Number < c2.Number)
              return true;
           else if(c1.Number > c2.Number)
              return false;
           else{
               if(c1.Section < c2.Section)
                   return true;
               else
                   return false;
           }
       }

  );

  return courses;
}


//
// FindCourses(college, courseNumber)
//
// Searches for all courses in the college for those that match
// the given course number.  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by department, then course number,
// and then section number.
//
vector<Course> FindCourses(const College& college, int courseNumber)
{
    

  vector<Course>  courses;
    
  // Push back all the courses with the same Course Number
  for(Dept d: college.Depts)
      for(Course c: d.Courses)
          if(c.Number == courseNumber)
              courses.push_back(c);
    
  // Sort the courses in ascending order by department
  sort(courses.begin(), courses.end(),
       [](Course c1, Course c2){
          if(c1.Dept < c2.Dept)
              return true;
          else if(c1.Dept > c2.Dept)
              return false;
          else{ // Secondary sort by section number
              if(c1.Number < c2.Number)
                  return true;
              else if(c1.Number > c2.Number)
                  return false;
              else{
                  if(c1.Section < c2.Section)
                      return true;
                  else
                      return false;
              }
          }
       }

  );
  
  return courses;
}


//
// FindCourses(college, instructorPrefix)
//
// Searches all the courses in the college for those whose 
// instructor name starts with the given instructor prefix.
// For example, the prefix "Re" would match instructors "Reed"
// and "Reynolds".  If none are found, then the returned
// vector is empty.  If one or more courses are found, copies of
// the course objects are returned in a vector, with the courses
// appearing in ascending order by instructor, then course number,
// and then section number.
//
vector<Course> FindCourses(const College& college, string instructorPrefix)
{
  vector<Course>  courses;
  
  for(Dept d: college.Depts)
      for(Course c: d.Courses)
          if(c.Instructor.find(instructorPrefix) == 0)
              courses.push_back(c);
      
  
    
  sort(courses.begin(), courses.end(),
       [](Course c1, Course c2){
            if(c1.Instructor < c2.Instructor)
              return true;
           else if(c1.Instructor > c2.Instructor)
              return false;
           else{
               if(c1.Number < c2.Number)
                   return true;
               else if(c1.Number > c2.Number)
                   return false;
               else{
                   if(c1.Section < c2.Section)
                       return true;
                   else
                       return false;
               }
           }
       }

  );

  return courses;
}
