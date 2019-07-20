/*main.cpp*/

//
// Omar Salas-Rodriguez
// U. of Illinois, Chicago
// CS 341, Spring 2019
// Project #03: GradeUtil
//


#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include "gradeutil.h"

using namespace std;
/*
 *  Descripion: Read in all the data from a csv file
 *              which contains all the course and dept information
 * 
 *  Input: string of the file name to read in
 * 
 *  Output: College object populated with depts and courses
 * 
 */
College input(string filename){
	ifstream  file(filename);
	string    collegeName, semester, year;
  string    line, dept, title, instructor, number, section;
  string    numA, numB, numC, numD, numF, numI, numS, numU, numW, numNR;
	
	// Check if the file was opened correctly
	if(!file.good()){
		cout << "Error: Cannot open file!" << endl;
		return College();
	}
	
	// Get college, semester, and year information
	getline(file, line);
	stringstream ss(line);
	getline(ss, collegeName, ',');
	getline(ss, semester, ',');
	getline(ss, year);
	
	// Store all the courses in a dept inside college variable
	College college(collegeName);
	
	// Skip information line
	getline(file, line);
	
	/*
	* Retrieve the data for the file
	* Create each Course and add to appropriate Dept
	* Then add the Dept to the college if it doesn't exist
	*/ 
	while(getline(file,line)){

		// Delegate the parsing to the ParseCourse function
		Course c = ParseCourse(line);
		
		// Find if the department of the course exists in the college
		auto iter = std::find_if(college.Depts.begin(), college.Depts.end(),
												 [=](const Dept& d){
													  if(d.Name == c.Dept)
															return true;
													  return false;
														}
												 );
		// Condition to create the department or not
		if(iter == college.Depts.end()){
			Dept d(c.Dept);
			college.Depts.push_back(d);
		}
		
		// Push the course into the list of Courses in a department
		for(Dept& d: college.Depts)
			if(d.Name == c.Dept)
				d.Courses.push_back(c);
					
	}
	
	// Sort the deparments in ascending order by name
	sort(college.Depts.begin(), college.Depts.end(),
       [](Dept d1, Dept d2){
          if(d1.Name < d2.Name)
              return true;
          else
              return false;
         
       }

  );
	
	// Sort the courses in each department in ascending order
	for(Dept& d: college.Depts){
		sort(d.Courses.begin(), d.Courses.end(),
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
	}
	
	// Initial ouput
	cout << "** College of " << collegeName << ", " << semester << " " << year << " **" << endl;

	return college;
	
}

/*
 *  Descripion: Helper function that counts the total amount of courses
 * 
 *  Input: College that contains departments and courses
 * 
 *  Output: Total number of courses in that college
 * 
 */
int getTotalCourses(College& c){
	int numCourses = 0;
	for(Dept& depts: c.Depts)
		numCourses += depts.Courses.size();
	return numCourses;
}

/*
 *  Descripion: Helper function that counts the total amount of students
 * 
 *  Input: College that contains departments and courses
 * 
 *  Output: Total number of students in that college
 * 
 */
int getTotalStudents(College& c){
	int numStudents = 0;
	for(Dept& depts: c.Depts)
		for(Course& courses: depts.Courses)
			numStudents += courses.getNumStudents();
	return numStudents;
}

/*
 *  Descripion: Helper function to print information on GradeStats and DFWRate
 * 
 *  Input: GradeStats and DFWRate
 * 
 *  Output: None
 * 
 */
void printGrades(GradeStats& grades, double& DFWRate){
	cout << " grade distribution (A-F): " << grades.PercentA << "%, "<< grades.PercentB << "%, "<< grades.PercentC << "%, "<< grades.PercentD << "%, "<< grades.PercentF << "%" << endl;
	cout << " DFW rate: " << DFWRate << "%" << endl;
}

/*
 *  Descripion: Helper function that translates enum values from Course class to strings
 * 
 *  Input: Integer value of the enum
 * 
 *  Output: String equivalence of the enum
 * 
 */
string toStringGradingType(int type){
	switch (type){
		case 0: return "letter";
						break;
		case 1: return "satisfactory";
						break;
		case 2: return "unknown";
						break;
	}
	return "";
}

int main(){
	int numStudents, numCourses, DFW, N, courseNumber;
	string target, threshold, instructorPrefix, filename;
	double DFWRate;
	string inputCommand = "";
	vector<Course> courses;
	bool found = false;
	bool courseFound = false;
	
	// Set output floating point precision
	cout << std::fixed;
	cout << std::setprecision(2);
	
	cin >> filename;
	
	// Populate the college with the file information
	auto college = input(filename);
	if(college.Depts.empty())
		return 0;
	numCourses = getTotalCourses(college);
	numStudents = getTotalStudents(college);
	GradeStats grades = GetGradeDistribution(college);
	DFWRate = GetDFWRate(college, DFW, N);
	
	// Initial ouput
	cout << "# of courses taught: " << numCourses << endl;
	cout << "# of students taught: " << numStudents << endl;
	cout << "grade distribution (A-F): " << grades.PercentA << "%, "<< grades.PercentB << "%, "<< grades.PercentC << "%, "<< grades.PercentD << "%, "<< grades.PercentF << "%" << endl;
	cout << "DFW rate: " << DFWRate << "%" << endl;
	
	// Start the user interaction with the program
	cout << "\nEnter a command> ";
	cin >> inputCommand;
	
	while(inputCommand != "#"){
		found = false;
		courseFound = false;
		
		// Summary command
		if(inputCommand == "summary"){
			
			cout << "dept name, or all? ";
			cin >> target;
			
			// Check if the input is valid
			if(target == "#")
				return 0;
			else if(target == "all"){
				
				// Iterate through all the departments and output appropriate information
				for(Dept& dep: college.Depts){
					found = true;
					numCourses = dep.Courses.size();
					numStudents = 0;
					grades = GetGradeDistribution(dep);
					DFWRate = GetDFWRate(dep, DFW, N);
					for(Course& c: dep.Courses)
						numStudents += c.getNumStudents();
					cout << dep.Name << ":" << endl;
					cout << " # courses taught: " << numCourses << endl;
					cout << " # students taught: " << numStudents << endl;
					printGrades(grades, DFWRate);
				}
				
			}else{ // Single department
				
				// Find the desired department and output the appropriate information
				for(Dept& dep: college.Depts){
					if(dep.Name == target){
						found = true;
						numCourses = dep.Courses.size();
						numStudents = 0;
						grades = GetGradeDistribution(dep);
						DFWRate = GetDFWRate(dep, DFW, N);
						for(Course& c: dep.Courses)
							numStudents += c.getNumStudents();
						cout << dep.Name << ":" << endl;
						cout << " # courses taught: " << numCourses << endl;
						cout << " # students taught: " << numStudents << endl;
						printGrades(grades, DFWRate);
					}
				}
				
			}	
			
			// Check if the user gave a correct department
				if(!found)
					cout << "**dept not found" << endl;
		}

		// Search command
		else if(inputCommand == "search"){
			
			cout << "dept name, or all? ";
			cin >> target;
			
			if(target == "#")
				return 0;
			else if(target == "all"){
				found = true;
				// Iterate through all the departments, find courses desired
				cout << "course # or instructor prefix? ";
				cin >> instructorPrefix;
				stringstream ss(instructorPrefix);
				ss >> courseNumber;// try to convert input to a course #
				if(ss.fail()){ // Instructor Prefix search
					courses = FindCourses(college, instructorPrefix);
					for(Course& c: courses){
						courseFound = true;
						numStudents = c.getNumStudents();
						grades = GetGradeDistribution(c);
						DFWRate = GetDFWRate(c, DFW, N);
						cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
						cout << " # students: " << numStudents << endl;
						cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
						printGrades(grades, DFWRate);
					}
				}else{ // Course Number search
					courses = FindCourses(college, courseNumber);
					for(Course& c: courses){
						courseFound = true;
						numStudents = c.getNumStudents();
						grades = GetGradeDistribution(c);
						DFWRate = GetDFWRate(c, DFW, N);
						cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
						cout << " # students: " << numStudents << endl;
						cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
						printGrades(grades, DFWRate);
					}
				}
				
			}else{
				
				cout << "course # or instructor prefix? ";
				cin >> instructorPrefix;
				
				// Find the desired department and search within it
				for(Dept& dep: college.Depts){
					if(dep.Name == target){
						found = true;
						// Iterate through all the departments, find courses desired
						
						stringstream ss(instructorPrefix);
						ss >> courseNumber;// try to convert input to a course #
						if(ss.fail()){ // Instructor Prefix search
							courses = FindCourses(dep, instructorPrefix);
							for(Course& c: courses){
								courseFound = true;
								numStudents = c.getNumStudents();
								grades = GetGradeDistribution(c);
								DFWRate = GetDFWRate(c, DFW, N);
								cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
								cout << " # students: " << numStudents << endl;
								cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
								printGrades(grades, DFWRate);
							}
						}else{ // Course Number search
							courses = FindCourses(dep, courseNumber);
							for(Course& c: courses){
								courseFound = true;
								numStudents = c.getNumStudents();
								grades = GetGradeDistribution(c);
								DFWRate = GetDFWRate(c, DFW, N);
								cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
								cout << " # students: " << numStudents << endl;
								cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
								printGrades(grades, DFWRate);
							}
						}
					}
				}
			
					
			}
			
			// Check if the user gave a correct department
				if(!found)
					cout << "**dept not found" << endl;
				else if(!courseFound) // Check if a course was found
					cout << "**none found" << endl;
			
		}
		// Unknown command
		else if(inputCommand == "unknown"){
			
			
			cout << "dept name, or all? ";
			cin >> target;
			
			if(target == "#")
				return 0;
			else if(target == "all"){
				found = true;
				// Iterate through all the departments and output unknown courses
				for(Dept& dep: college.Depts){
					for(Course& c: dep.Courses){
						if(c.getGradingType() == Course::Unknown){
							courseFound = true;
							numCourses = dep.Courses.size();
							grades = GetGradeDistribution(c);
							DFWRate = GetDFWRate(c, DFW, N);
							numStudents = c.getNumStudents();
							cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
							cout << " # students: " << numStudents << endl;
							cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
							printGrades(grades, DFWRate);
						}
					}
				}
				
			}else{ // Single department
				
				// Iterate through a single department and output unknown courses
				for(Dept& dep: college.Depts){
					if(dep.Name == target){
						found = true;
						for(Course& c: dep.Courses){
							if(c.getGradingType() == Course::Unknown){
								courseFound = true;
								numCourses = dep.Courses.size();
								grades = GetGradeDistribution(c);
								DFWRate = GetDFWRate(c, DFW, N);
								numStudents = c.getNumStudents();
								cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
								cout << " # students: " << numStudents << endl;
								cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
								printGrades(grades, DFWRate);
							}
						}
					}
				}
				
			}
			
			// Check if the user gave a correct department
			if(!found)
				cout << "**dept not found" << endl;
			else if(!courseFound) // Check if a course was found
				cout << "**none found" << endl;
			
		}
		// DFW command
		else if(inputCommand == "dfw"){
			courses.clear();
			cout << "dept name, or all? ";
			cin >> target;
			
			if(target == "#")
				return 0;
			else if(target == "all"){
				found = true;
				cout << "dfw threshold? ";
				cin >> threshold;
				
				// Iterate through all the departments and find threshold courses
				for(Dept& dep: college.Depts){
					for(Course& c: dep.Courses){
						DFWRate = GetDFWRate(c, DFW, N);
						if(DFWRate > stod(threshold)){
							courseFound = true;
							courses.push_back(c);
						}
					}
				}
				
				// Sort the courses in descending order by DFWRate
				double DFWRate1, DFWRate2;
				sort(courses.begin(), courses.end(),
						[&](Course course1, Course course2){
								DFWRate1 = GetDFWRate(course1, DFW, N);
								DFWRate2 = GetDFWRate(course2, DFW, N);	
								if(DFWRate1 > DFWRate2)
									return true;
								else if(DFWRate1 < DFWRate2)
									return false;
								else{
									if(course1.Dept < course2.Dept)
										return true;
									else if(course1.Dept > course2.Dept)
										return false;
									else{
										if(course1.Number < course2.Number)
											return true;
										else if(course1.Number > course2.Number)
											return false;
										else{
											if(course1.Section < course2.Section)
												return true;
											else
												return false;
										}
									}
								}
						});
				
				for(Course& c: courses){
					DFWRate = GetDFWRate(c, DFW, N);
					numCourses = c.getNumStudents();
					grades = GetGradeDistribution(c);
					numStudents = c.getNumStudents();
					cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
					cout << " # students: " << numStudents << endl;
					cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
					printGrades(grades, DFWRate);
				}
				
				
			}else{ // Single department
				
				cout << "dfw threshold? ";
				cin >> threshold;
				
				// Iterate through a single department and find threshold courses
				for(Dept& dep: college.Depts){
					if(dep.Name == target){
						found = true;
						
						
						
						for(Course& c: dep.Courses){
							DFWRate = GetDFWRate(c, DFW, N);
							if(DFWRate > stod(threshold)){
								courseFound = true;
								courses.push_back(c);
							}
						}
					}
				}
				
				
				
				if(courseFound){
				// Sort the courses in descending order by DFWRate
					double DFWRate1, DFWRate2;
					sort(courses.begin(), courses.end(),
							[&](Course course1, Course course2){
									DFWRate1 = GetDFWRate(course1, DFW, N);
									DFWRate2 = GetDFWRate(course2, DFW, N);	
									if(DFWRate1 > DFWRate2)
										return true;
									else if(DFWRate1 < DFWRate2)
										return false;
									else{
										if(course1.Dept < course2.Dept)
											return true;
										else if(course1.Dept > course2.Dept)
											return false;
										else{
											if(course1.Number < course2.Number)
												return true;
											else if(course1.Number > course2.Number)
												return false;
											else{
												if(course1.Section < course2.Section)
													return true;
												else
													return false;
											}
										}
									}
							});

					for(Course& c: courses){
						DFWRate = GetDFWRate(c, DFW, N);
						numCourses = c.getNumStudents();
						grades = GetGradeDistribution(c);
						DFWRate = GetDFWRate(c, DFW, N);
						numStudents = c.getNumStudents();
						cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
						cout << " # students: " << numStudents << endl;
						cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
						printGrades(grades, DFWRate);
					}
					
				}
				
			}
			
			// Check if the user gave a correct department
				if(!found)
					cout << "**dept not found" << endl;
				else if(!courseFound) // Check if a course was found
					cout << "**none found" << endl;
			
		}
		// LetterA command
		else if(inputCommand == "letterA"){
			courses.clear();
			cout << "dept name, or all? ";
			cin >> target;
			
			if(target == "#")
				return 0;
			else if(target == "all"){
				found = true;
				cout << "letter A threshold? ";
				cin >> threshold;
				
				// Iterate through all the departments and find threshold courses
				for(Dept& dep: college.Depts){
					for(Course& c: dep.Courses){
						grades = GetGradeDistribution(c);
						if(grades.PercentA > stod(threshold)){
							courseFound = true;
							courses.push_back(c);
						}
					}
				}
				
				// Sort the courses in descending order by PercentA
				GradeStats percA1, percA2;
				sort(courses.begin(), courses.end(),
						[&](Course course1, Course course2){
								percA1 = GetGradeDistribution(course1);
								percA2 = GetGradeDistribution(course2);	
								if(percA1.PercentA > percA2.PercentA)
									return true;
								else if(percA1.PercentA < percA2.PercentA)
									return false;
								else{
									if(course1.Dept < course2.Dept)
										return true;
									else if(course1.Dept > course2.Dept)
										return false;
									else{
										if(course1.Number < course2.Number)
											return true;
										else if(course1.Number > course2.Number)
											return false;
										else{
											if(course1.Section < course2.Section)
												return true;
											else
												return false;
										}
									}
								}
						});
				
				for(Course& c: courses){
					DFWRate = GetDFWRate(c, DFW, N);
					numCourses = c.getNumStudents();
					grades = GetGradeDistribution(c);
					numStudents = c.getNumStudents();
					cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
					cout << " # students: " << numStudents << endl;
					cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
					printGrades(grades, DFWRate);
				}
				
				
			}else{ // Single department
				
				cout << "letter A threshold? ";
				cin >> threshold;
				
				// Iterate through a single department and find threshold courses
				for(Dept& dep: college.Depts){
					if(dep.Name == target){
						found = true;
						
						
						
						for(Course& c: dep.Courses){
							grades = GetGradeDistribution(c);
							if(grades.PercentA > stod(threshold)){
								courseFound = true;
								courses.push_back(c);
							}
						}
					}
				}
				
				
				
				if(courseFound){
					// Sort the courses in descending order by PercentA
					GradeStats percA1, percA2;
					sort(courses.begin(), courses.end(),
							[&](Course course1, Course course2){
									percA1 = GetGradeDistribution(course1);
									percA2 = GetGradeDistribution(course2);	
									if(percA1.PercentA > percA2.PercentA)
										return true;
									else if(percA1.PercentA < percA2.PercentA)
										return false;
									else{
										if(course1.Dept < course2.Dept)
											return true;
										else if(course1.Dept > course2.Dept)
											return false;
										else{
											if(course1.Number < course2.Number)
												return true;
											else if(course1.Number > course2.Number)
												return false;
											else{
												if(course1.Section < course2.Section)
													return true;
												else
													return false;
											}
										}
									}
							});

					for(Course& c: courses){
						DFWRate = GetDFWRate(c, DFW, N);
						numCourses = c.getNumStudents();
						grades = GetGradeDistribution(c);
						DFWRate = GetDFWRate(c, DFW, N);
						numStudents = c.getNumStudents();
						cout << c.Dept << " " << c.Number << " (section " << c.Section << "): " << c.Instructor << endl;
						cout << " # students: " << numStudents << endl;
						cout << " course type: " << toStringGradingType(c.getGradingType()) << endl;
						printGrades(grades, DFWRate);
					}
					
				}
			}
			
			// Check if the user gave a correct department
				if(!found)
					cout << "**dept not found" << endl;
				else if(!courseFound) // Check if a course was found
					cout << "**none found" << endl;
			
		}
		else{ // Not one of the 5 commands available
			cout << "**unknown command" << endl;
		}
		
		cout << "Enter a command> ";
		cin >> inputCommand;
	}
	
	return 0;
}