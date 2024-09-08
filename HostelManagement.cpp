#include <bits/stdc++.h>
#include <fstream> // File Handling
#include <windows.h> // Sleep (Windows-specific)
#include <sstream> 

using namespace std;

class Hostel {
private:
    string Name;
    int Rent, Bed;

public:
    Hostel(string name, int rent, int bed) {
        this->Name = name;
        this->Rent = rent;
        this->Bed = bed;
    }

    string getName() {
        return Name;
    }

    int getBed() {
        return Bed;
    }

    int getRent() {
        return Rent;
    }

    void reserve() {
        ifstream in("Hostel.txt");
        ofstream out("Hostel_Temp.txt");
        string line;

        while (getline(in, line)) {
            // Find the hostel block dynamically (based on Name)
            int pos = line.find(Name);
            if (pos != string::npos) {
                int bed = Bed - 1;
                Bed = bed; // Update the in-memory Bed count

                stringstream ss;
                ss << bed;
                string strBed = ss.str();

                int bedPos = line.find_last_of(':');
                line.replace(bedPos + 1, string::npos, strBed); 
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("Hostel.txt");
        rename("Hostel_Temp.txt", "Hostel.txt");
        cout << "\tBed Reserved Successfully!!!!" << endl;
    }
};

class Student {
private:
    string Name, Address, RegNo;

public:
    Student() : Name(""), RegNo(""), Address("") {}

    void setName(string name) {
        Name = name;
    }

    void setRegNo(string regno) {
        RegNo = regno;
    }

    void setAddress(string address) {
        Address = address;
    }

    string getName() {
        return Name;
    }

    string getRegNo() {
        return RegNo;
    }

    string getAddress() {
        return Address;
    }
};

int main() {
    Hostel h("Block-15", 180000, 543);
    ofstream out("Hostel.txt");
    out << "\t" << h.getName() << ":" << h.getRent() << ":" << h.getBed() << endl << endl;
    cout << "Hostel Data is saved" << endl;
    out.close();

    bool exit = false;
    Student s;
    
    while (!exit) {
        system("cls"); // Clear the console
        int val;

        cout << "\t Welcome to the Hostel Accommodation System" << endl;
        cout << "\t******************************************" << endl;
        cout << "\t1. Reserve a Bed" << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter a choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            string name, rollno, address;
            cout << "\tEnter name of Student: ";
            cin.ignore(); // To avoid skipping input due to previous `cin`
            getline(cin, name);
            s.setName(name);

            cout << "\tEnter Roll No: ";
            getline(cin, rollno);
            s.setRegNo(rollno);

            cout << "\tEnter Address: ";
            getline(cin, address);
            s.setAddress(address);

            if (h.getBed() > 0) {
                h.reserve();
            } else if (h.getBed() == 0) {
                cout << "\tSorry, Bed Not Available" << endl;
            }

            ofstream outFile("Student.txt", ios::app); // Append student details to the file
            outFile << "\t" << s.getName() << ":" << s.getRegNo() << ":" << s.getAddress() << endl << endl;
            outFile.close();
            Sleep(5000); // Pause for 5 seconds
        }

        else if (val == 2) {
            system("cls");
            exit = true;
            cout << "Exiting..." << endl;
            Sleep(3000); // Pause for 3 seconds before exiting
        }
    }

    return 0;
}
