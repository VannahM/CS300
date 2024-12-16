//Savannah Mattoon
//December 12, 2024
//cs 300

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>  

using namespace std;

//course structure to store the course information
struct Course {
    string courseID;
    string courseTitle;
    vector<string> preReqs;
};


string toUpperCase(const string& str) {
    //create a copy of the input string
    string upperCase = str;  

    //for length of upperCase
    for (size_t i = 0; i < upperCase.size(); ++i) {
        //convert each character to uppercase
        upperCase[i] = toupper(upperCase[i]);  
    }
    return upperCase; //return upperCase string
}


string trimWhiteSpace(const string& str) {
    size_t start = 0;
    size_t end = str.size() - 1;

    //trim leading whitespace
    while (start < str.size() && isspace(str[start])) {
        start++;
    }

    //trim trailing whitespace
    while (end > start && isspace(str[end])) {
        end--;
    }

    //initialize result
    string trimmedString = "";
    //loop to store str in result
    for (size_t i = start; i <= end; ++i) {
        trimmedString += str[i];
    }

    return trimmedString; // return trimmed string
}



vector<Course> loadCourses(const string& filename) {
    vector<Course> courses; //vector to store course data
    ifstream file(filename); //open the file for reading

    // If file is not found, output error message
    if (!file) {
        cout << "Could not open file: " << filename << endl;
        return courses;
    }

    string line; //holds line from file

    while (getline(file, line)) {
        //call function to remove whitespace
        line = trimWhiteSpace(line);

        //if line is empty skip it
        if (line.empty()) {
            continue;
        }

        //initialize begin and end
        size_t begin = 0;
        size_t end = 0;

        //find the first comma 
        while (end < line.size() && line[end] != ',') {
            end++; //increment end to find the comma
        }

        //initialize courseID
        string courseID = "";
        //copy from begin to end 
        for (size_t i = begin; i < end; ++i) {
            courseID += line[i]; //store in courseID
        }

        //re-initialize begin and end
        begin = end + 1;
        end = begin;

        //find the next comma
        while (end < line.size() && line[end] != ',') {
            end++;  //increment to find next comma
        }

        //initialize courseTitle
        string courseTitle = "";
        //copy from begin to end
        for (size_t i = begin; i < end; ++i) {
            courseTitle += line[i]; //store in courseTitle
        }

        //create a new course object
        Course newCourse;
        newCourse.courseID = courseID;
        newCourse.courseTitle = courseTitle;

        //re-initialize begin and end
        begin = end + 1;
        end = begin;

        while (end < line.size()) {
            //while end is less than line size and is not a comma
            while (end < line.size() && line[end] != ',') {
                end++;  //increment to find comma
            }

            //initialize preReq
            string preReq = "";
            //copy from begin to end
            for (size_t i = begin; i < end; ++i) {
                preReq += line[i]; //store in preReq
            }

            //if the preReq is not empty
            if (!preReq.empty()) {
                newCourse.preReqs.push_back(preReq); //add to preReq list
            }

            //re-initialize begin and end
            begin = end + 1;
            end = begin;
        }

        //add course to the courses vector
        courses.push_back(newCourse);
    }

    file.close();  //close the file after reading
    return courses; //return courses
}


bool compareByCourseID(const Course& a, const Course& b) {
    return a.courseID < b.courseID;  //compare course IDs
}



void printCourses(const vector<Course>& courses) {
    //check for courses
    if (courses.empty()) {
        cout << "No courses available" << endl;
        return;
    }

    //store courses in sortedCourses
    vector<Course> sortCourses = courses;
    //sort courses
    sort(sortCourses.begin(), sortCourses.end(), compareByCourseID);

    //print the sorted courses 
    for (size_t i = 0; i < sortCourses.size(); ++i) {
        const Course& course = sortCourses[i];  
        //output course ID and title
        cout << course.courseID << ", " << course.courseTitle << endl; 
    }
}



void searchCourse(const vector<Course>& courses, const string& courseID) {
    //change string to uppercase
    string upperCourseID = toUpperCase(courseID);

    //loop through the courses 
    for (size_t i = 0; i < courses.size(); ++i) {
        //if courseID matches 
        if (courses[i].courseID == upperCourseID) {  
            //print course info
            cout << courses[i].courseID << ", " << courses[i].courseTitle << endl;
            cout << "Prerequisites: ";

            //if course has no preReqs
            if (courses[i].preReqs.empty()) {
                cout << "none" << endl;  //output none
            }
            else {
                //if preReqs exist
                for (size_t j = 0; j < courses[i].preReqs.size(); ++j) {
                    //list all preReqs
                    cout << courses[i].preReqs[j] << " ";
                }
                cout << endl;
            }
            return;
        }
    }
    //output if course not found
    cout << "Course ID " << courseID << " not found" << endl;
}


int main() {
    
    vector<Course> courses; //vector to hold courses
    string filename; //string to hold fine name
    bool file = false; //file set to false

    int choice; //holds user choice

    cout << "\nWelcome to the course planner\n" << endl;

    while (true) {
       //output menu options
        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit\n" << endl;
        cout << "What would you like to do?  ";
        
        string input;
        getline(cin, input); 

       //try converting the input to an integer
        try {
            //convert string to integer
            choice = stoi(input);  
        }
        catch (const invalid_argument&) {
            //if the input is not a valid integer output error
            cout << "\nInvalid choice. Please try again\n\n";
            continue; 
        }
        catch (const out_of_range&) {
            //if the input is too large output error
            cout << "\nInvalid choice. Please try again\n\n";
            continue;
        }

        switch (choice) {
        case 1:
            //ask user for the file name to load
            cout << "Enter the file name: ";
            getline(cin, filename);

            //load courses from the file
            courses = loadCourses(filename);
            if (!courses.empty()) {
                file = true;
                cout << "Data structure loaded successfully\n" << endl;
            }
            else {
                cout << "Failed to load courses from the file\n" << endl;
            }
            break;
        case 2:
            if (file) {

                //print all courses sorted
                cout << "Here is a sample schedule\n" << endl;
                printCourses(courses);
                cout << endl;
            }
            else {
                cout << "Please load a file first\n" << endl;
            }
            break;
        case 3:
            if (file) {
                //ask for a course ID to search
                string courseID;
                cout << "What course do you want to know about? ";
                getline(cin, courseID);
                cout << endl;

                //convert the user input to uppercase
                searchCourse(courses, courseID);
                cout << endl;
            }
            else {
                cout << "Please load a file first\n" << endl;
            }
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again\n" << endl;
        }
    }

    return 0;
}
