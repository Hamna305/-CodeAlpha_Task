#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

struct Course {
    float marks;
    float average;
    float totalMarks;
    int creditHours;
    string gradeLetter;
    float gradePoint;
    float gradePoints;
};

// Function to convert marks difference into letter grade and GPA
pair<string, float> calculateGrade(float diff) {
    if (diff >= 15)       return {"A", 4.0};
    else if (diff >= 10)  return {"B+", 3.5};
    else if (diff >= 5)   return {"B", 3.0};
    else if (diff >= -4)  return {"C+", 2.5};
    else if (diff >= -9)  return {"C", 2.0};
    else if (diff >= -14) return {"D", 1.0};
    else                  return {"F", 0.0};
}

int main() {
    int numCourses;
    float totalGradePoints = 0;
    int totalCredits = 0;

    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);

    // Input for each course
    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Enter marks obtained: ";
        cin >> courses[i].marks;
        cout << "Enter class average: ";
        cin >> courses[i].average;
        cout << "Enter total marks: ";
        cin >> courses[i].totalMarks;
        cout << "Enter credit hours: ";
        cin >> courses[i].creditHours;

   
     float diff = courses[i].marks - courses[i].average;
pair<string, float> result = calculateGrade(diff);
courses[i].gradeLetter = result.first;
courses[i].gradePoint = result.second;
courses[i].gradePoints = result.second * courses[i].creditHours;



        totalGradePoints += courses[i].gradePoints;
        totalCredits += courses[i].creditHours;
    }

    float cgpa = totalGradePoints / totalCredits;

    // Display results
    cout << "\n--- Course Summary ---\n";
    cout << fixed << setprecision(2);
    for (int i = 0; i < numCourses; ++i) {
        cout << "Course " << i + 1
             << ": Marks = " << courses[i].marks
             << ", Average = " << courses[i].average
             << ", Grade = " << courses[i].gradeLetter
             << ", GPA = " << courses[i].gradePoint
             << ", Credit Hours = " << courses[i].creditHours
             << ", Grade Points = " << courses[i].gradePoints << endl;
    }

    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << "\nFinal CGPA: " << cgpa << endl;

    return 0;
}

