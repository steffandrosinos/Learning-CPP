#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Person Class
class Person {
    private:
        //Variables
        string name;
        int age;
    public:
        //Constructors
        Person();
        Person(string name, int age);

        //Input name and age
        friend istream &operator>>(istream &input, Person &p) {
            input >> p.name >> p.age;
            return input;
        }
        //Output name and age
        friend ostream &operator<<(ostream &output, const Person &p) {
            output << p.name << " " << p.age;
            return output;
        }
        //if p1 < p2 then return true
        bool operator<(const Person &p) {
            if(this->age < p.age) {
                return true;
            } else {
                return false;
            }
        }
        //if p1 > p2 then return true
        bool operator>(const Person &p) {
            if(this->age > p.age) {
                return true;
            } else {
                return false;
            }
        }
        //if p1 == p2 then return true
        bool operator==(const Person &p) {
            if(this->age == p.age) {
                return true;
            } else {
                return false;
            }
        }
};
// Default Person Constructor
Person::Person() {
    name = "";
    age = 0;
}
// Usual Person Constructor
Person::Person(string name, int age) : name(name), age(age) {}

void main_part1(){
    /*
     * Here I will ask the user to input 2 people.
     * I will then print the name and age of these people by using the << and >> operators
     * I will compare the ages of these people by comparing them with the < > and == operators
     * Hopefully this is enough to prove that these functions work
     */
    Person p1, p2; //Creating 2 Person classes
    cout << "Input Person 1 Details: ";
    cin >> p1; //Ask for p1 info
    cout << "Input Person 2 Details: ";
    cin >> p2; //Ask for p2 info
    cout << "Person 1: " << p1 << endl; //Print p1 name and age
    cout << "Person 2: " << p2 << endl; //Print p2 name and age
    if(p1<p2) { // Check if p1 is younger than p2
        cout << "Person 1 is younger" << endl;
    }
    if(p1>p2) { // Check if p1 is older than p2
        cout << "Person 1 is older" << endl;
    }
    if(p1==p2) { // Check if p1 and p2 are the same age
        cout << "Person 1 and Person 2 are the same age" << endl;
    }
}

void main_part2(){
    string menu = "1. Add Person\n" //Menu items
                  "2. List Everyone\n"
                  "3. Remove Person\n"
                  "4. Find Oldest\n"
                  "Q. Quit\n";
    Person people[9]; //Data structure for storing people

    char input; //User input
    int arr_index=0; //manual index, points to next (emtpy) array element. This also is the amount of people
    while(input != 'Q' && input != 'q') { //loop until 'q' or 'Q' is entered
        cout << menu; //output menu;
        cout << "Enter Option: ";
        cin >> input; //get user input as char

        switch(input){
            case '1': //Add Person
                if(arr_index < 9) { //Max check
                    cout << "Enter Details: "; //User input
                    cin >> people[arr_index]; //add to people array
                    arr_index++; //add to array index
                } else {
                    cout << "Error, max amount of people reached" << endl; //Error message as there are already 9 people
                }
                break;
            case '2': //List Everyone
                //loop for arr_index -1 .i.e if index is at 3, then there are 2 people in the array
                for(int i=0; i<arr_index; i++)
                    cout << "[" << (i+1) << "] " << people[i] << endl; //output array pointer, then person name and age
                break;
            case '3': //Remove Person
                cout << "Enter Index: ";
                int delete_index;
                cin >> delete_index; //Get user int input
                if(delete_index >= 1 && delete_index < (arr_index+1)) { //Delete index can't be less than 1 AND can't be more than the amount of people in the list
                    /*
                     * Considering that order doesn't matter,
                     * when deleting an index we can just take
                     * the last element and move it up to take
                     * the place of the person thats being delted.
                     * Then set last index to empty.
                     */
                    Person empty; //Empty person
                    if(delete_index == 9) { //If last element is being deleted
                        people[(delete_index-1)] = empty; //Set it as empty
                    } else {
                        people[(delete_index-1)] = people[(arr_index-1)]; //moving last element
                        people[(arr_index-1)] = empty; //setting last element as empty
                    }
                    //if we remove and index we need to negate the array index
                    if(arr_index != 0) { //if the array is not empty
                        arr_index--; //Negate the array index
                    }
                }
                break;
            case '4': //Find Oldest
                int oldest = 0;  //Record index for oldest
                for(int i=1; i<arr_index; i++) { //Loop through all elements
                    if(people[i] > people[oldest])
                        oldest = i;
                }
                cout << "Oldest: " << people[oldest] << endl; //Print the oldest person
                break;
        }
    }
}

//Function that returns true if p1 is younger than p2
bool compare(Person p1, Person p2) {
    return p1 < p2;
}

void main_part3(){
    string menu = "1. Add Person\n"
                  "2. List Everyone\n"
                  "3. Remove Person\n"
                  "4. Find Oldest\n"
                  "5. Sort Data\n"
                  "Q. Quit\n"; //Menu items
    vector<Person> people; //vector for storing people
    char input; //User input
    while(input != 'Q' && input != 'q') { //loop until 'q' or 'Q' is entered
        cout << menu; //output menu;
        cout << "Enter Option: ";
        cin >> input; //get user input as char

        switch(input){
            case '1': { //Add Person
                cout << "Enter Details: "; //User input
                Person new_person; //New person input
                cin >> new_person; //get user input
                people.insert(people.end(), new_person); //Insert user into vector
                break;
            }
            case '2': { //List Everyone
                int index=1; //visual index for user
                //Loop through all Person in people
                for(auto person=people.begin(); person<people.end(); person++) {
                    cout << "[" << index << "] " << *person << endl; //Output [index] name age
                    index++; //Add to visual index for next Person
                }
                break;
            }
            case '3': //Remove Person
                cout << "Enter Index: ";
                int delete_index;
                cin >> delete_index; //Get user int input
                people.erase(people.begin()+(delete_index-1)); //Delete index being + (delete_index-1)
                break;
            case '4': { //Find Oldest
                //Using max_element from "algorithm" to find the oldest person
                //compare is a function defined above part3
                auto oldest = max_element(people.begin(), people.end(), compare);
                cout << "Oldest: " << *oldest << endl; //Print the oldest person
                break;
            }
            case '5': //Sort Data
                //Using sort from "algorithm" to sort the Person vector based on the compare function
                sort(people.begin(), people.end(), compare);
                break;
        }
    }
}

int main() {
    // UNCOMMENT THE RELEVANT LINE TO TEST/RUN EACH PART
    //main_part1();
    //main_part2();
    main_part3();
}
