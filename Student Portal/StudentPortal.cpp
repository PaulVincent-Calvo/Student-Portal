#include <iostream>
using namespace std;

class student
{
    public:
        string name, subjectcode, subject, schedule;
        int srcode;
        student* next;
        // constructor that initializes every next pointer to nullptr whenever an object is created from the class
        student() : next(nullptr) {}
};

// declared globally because they'll be used in two functions: print_subjectcodes_and_subjects() & add_to_SIS()
string subjectcodes[3] = {"CS131" , "LITR101", "MATH401"};
string subjects[3] = {"Data Structures and Algorithms", "ASEAN Literature", "Integral Calculus"};

void sis_header()
{
    cout << "======================================================="<< endl << "               Student Information Sheet" << endl << "=======================================================" << endl;
}

void menu_header()
{
    system ("cls");
    cout << "============================================" << endl << "              BatStateU Portal" << endl << "============================================" << endl; 
}

void print_subjectcodes_and_subjects()
{
    cout << endl << "Available Subjects" << endl;
    for (int s = 0; s < 3; s++)
    {
        cout << "Subject Code: " << subjectcodes[s] << "\t" << "Subject: " << subjects[s] << endl;
    }
    cout << endl;
}

void add_to_SIS(student*& head)
{
    system ("cls");
    sis_header();
    string srcode_placeholder, subjectcode_placeholder;
    student* new_student = new student();

    while (true)
    {
        try
        {    
            cout << "Enter SR Code: ";
            cin >> srcode_placeholder;
            new_student->srcode = stoi(srcode_placeholder);
            break;
        }
        catch (const exception&)
        {
            cout << "Please input an integer!" << endl;
        }
    }

    cout << endl << "Enter Student Name: ";
    cin >> new_student->name;

    while (true)
    {
        print_subjectcodes_and_subjects();
        try
        {    
            cout << "Enter Subject Code: ";
            cin >> subjectcode_placeholder;

            if (subjectcode_placeholder == subjectcodes[0])
            {
                new_student->subjectcode = subjectcodes[0];
                new_student->subject = subjects[0];
                break;
            }
            else if (subjectcode_placeholder == subjectcodes[1])
            {
                new_student->subjectcode = subjectcodes[1];
                new_student->subject = subjects[1];
                break;
            }
            else if (subjectcode_placeholder == subjectcodes[2])
            {
                new_student->subjectcode = subjectcodes[2];
                new_student->subject = subjects[2];
                break;
            }
            else
            {
                cout << "Please input a valid option!" << endl << endl;
            }
        }
        catch (const exception&)
        {
            cout << "Please input a valid option!";
        }
    }    

    cout << endl << "Enter Schedule: ";
    cin >> new_student->schedule;

    if (head == nullptr) 
    {
        // if the ll is empty, make the new student the head
        head = new_student;  
    } 
    else 
    {
        student* current = head;
        while (current->next != nullptr) { 
            // find the last node in the linked list
            current = current->next; 
        }
        // add the new student to the end of the linked list
        current->next = new_student;  
    }
}

void display_all_SIS(const student* head)
{
    if (head == nullptr) 
    {
        menu_header();
        cout << "No student information on the system yet." << endl;
        return;
    }

    system("cls");
    const student* current = head;
    while (current != nullptr) 
    {
        sis_header();        
        cout << "Student Code: " << current->srcode << endl;
        cout << "Name: " << current->name << endl;
        cout << "Subject Code: " << current->subjectcode << endl;
        cout << "Subject: " << current->subject << endl;
        cout << "Schedule: " << current->schedule << endl << endl;
        current = current->next;
    }
}

const student* search_student(const student* head, int srcode)
{
    const student* current = head;
    while (current != nullptr) {
        if (current->srcode == srcode) 
        {
            // return the student if the srcode matches
            return current;  
        }
        current = current->next;
    }
    // return nullptr if the student is not found
    return nullptr;  
}

int main()
{
    // pointer to head of ll
    student* head = nullptr; 
    string choice_placeholder, search_srcode_placeholder, return_to_main;
    int choice, search_srcode;
    const student* find_student = nullptr;
    
    do
    {
        menu_header();
        cout << "What would you like to do?" << endl;
        cout << "[1] Add to Student Information Sheets" << endl << "[2] Display all students' information" << endl << "[3] Search for a students' information" << endl << "[4] Exit" << endl; 
        
        while (true)
        {
            try
            {    
                cout << "Please input your choice: ";    
                cin >> choice_placeholder;
                choice = stoi(choice_placeholder);
                if (choice >= 1 && choice <= 4) {
                    break;
                }
            }
            catch (const exception&)
            {
                cout << "Please input an integer based on the choices given!" << endl;
            }
        }

        switch(choice)
        {
            case 1:
                add_to_SIS(head);
                break;

            case 2:
                display_all_SIS(head);
                break;

            case 3:
                while (true)
                {
                    try
                    {    
                        cout << "Please input the SR Code of the student you are searching for: ";    
                        cin >> search_srcode_placeholder;
                        search_srcode = stoi(search_srcode_placeholder);
                        break;
                    }
                    catch (const exception&)
                    {
                        cout << "Invalid input. Plese input an integer!" << endl;
                    }
                }
                find_student = search_student(head, search_srcode);

                if (find_student != nullptr)
                {
                    system("cls");
                    cout << "Student found!" << endl;
                    sis_header();
                    cout << "SR Code: " << find_student->srcode << endl;
                    cout << "Student Name: " << find_student->name << endl;
                    cout << "Subject Code: " << find_student->subjectcode << endl;
                    cout << "Subject: " << find_student->subject << endl;
                    cout << "Schedule: " << find_student->schedule << endl; 
                }
                else
                {
                    menu_header();
                    cout << "Student not found in the system!" << endl;
                }
                break;

            case 4:
                menu_header();
                cout << "Thank you for using the BatStateU Portal. The program will now be terminated.";
                return 0;

            default:
                cout << "Invalid choice! Please select a number from 1 to 4." << endl;
                break;
        }

        cout << "Return to main menu? y/n: ";
        cin >> return_to_main;
    }while(return_to_main == "y" || return_to_main == "Y");

    return 0;
}