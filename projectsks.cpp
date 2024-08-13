#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstring> // For strlen()
#include <conio.h> // For getch()

using namespace std;

class User {
private:
    string username;
    string password;
    string name;
    int age;
    string gender;
    string from; 
    string to;  
	string date; 
    string modeOfTransportation;
    string transportationDetails; 
    string timings;

public:
    // Constructors
    User() {}
    User(const string& uname, const string& pwd, const string& n, int a, const string& g)
        : username(uname), password(pwd), name(n), age(a), gender(g) {}

    // Getdata
    
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getFrom() const { return from; } 
    string getTo() const { return to; }   
	string getdate() const{ return date; }  
    string getModeOfTransportation() const { return modeOfTransportation; }
    string getTransportationDetails() const { return transportationDetails; }
    string getTimings() const { return timings; }

    //  Trip details
    
    void setTripDetails(const string& f, const string& t, const string& d1,const string& mode, const string& details, const string& time) {
        from = f;  
        to = t;  
		date = d1; 
        modeOfTransportation = mode;
        transportationDetails = details;
        timings = time;
    }

    // Checking that this user cane be comapnion for the given user
    
    bool canBeCompanion(const User& other) const {
        return (from == other.getFrom() && to == other.getTo());
    }
};

class TravelCompanion {
private:
    vector<User> users;
    string filename;

public:
    // Constructor
    
    TravelCompanion(const string& fname) : filename(fname) {}

    // Register a new user
    
    void registerUser() {
        string username, password, name, gender;
        int age;

        cout<<"-------BASIC DETAILS-------\n";
        
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password : ";
        password = maskedInput();
        cout << endl;
        cout<<"Please enter your details.\n";
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter gender: \n";
        cin >> gender;

        User newUser(username, password, name, age, gender);
        users.push_back(newUser);

        // Put user data into file
        
        ofstream outfile(filename.c_str(), ios::app);
        if (outfile.is_open()) {
            outfile << username << " " << password << " " << name << " " << age << " " << gender << endl;
            outfile.close();
            cout << "User registered successfully!\n";
        } else {
            cout << "Error: Unable to open file for writing.\n";
        }
    }

    // Get user data from file
    
    void loadUsersFromFile() {
        ifstream infile(filename.c_str());
        if (infile.is_open()) {
            while (!infile.eof()) {
                User user;
                string uname, pwd, name, gender;
                int age;
                infile >> uname >> pwd >> name >> age >> gender;
                if (!uname.empty()) {
                    user = User(uname, pwd, name, age, gender);
                    users.push_back(user);
                }
            }
            infile.close();
        } else {
            cout << "Error: Unable to open file for reading.\n";
        }
    }

    // Login user
    
    const User& loginUser(const string& username) {
        cout << "Enter password : ";
        string password = maskedInput();
        cout << endl;

        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].getUsername() == username && users[i].getPassword() == password) {
                return users[i]; // Return reference to the user object
            }
        }
        // If login fails, throw a custom exception
        throw "Invalid username or password!";
    }

    // Update trip details after login
    
    void updateTripDetails(User& user) {
        string from, to, mode, details, time,date;
        cout<<"------MY TRIP-------\n";
        cout<<"Enter details about your Trip\n";
        cout<<"Date: ";
        cin>>date;
        cout << "From: ";
        cin >> from;   // Change current location to from
        cout << "To : ";
        cin >> to;     // Change destination to to

        // Select mode of transportation
        cout << "Select mode of transportation:\n";
        cout << "1. Train\n";
        cout << "2. Bus\n";
        cout << "3. Flight\n";
        cout << "4. Cab\n";
        cout << "5. Other\n";
        cout << "Enter your choice: ";
        int modeChoice;
        cin >> modeChoice;
        switch (modeChoice) {
            case 1:
                mode = "Train";
                cout << "Enter train number: ";
                cin.ignore();
                getline(cin, details);
                break;
            case 2:
                mode = "Bus";
                // Additional questions for Bus
                
                cout << "Enter bus number: ";
                cin.ignore();
                getline(cin, details);
                break;
            case 3:
                mode = "Flight";
                // Additional questions for Flight
                
                cout << "Enter flight number: ";
                cin.ignore();
                getline(cin, details);
                break;
            case 4:
                mode = "Cab";
                // Additional questions for Cab
                
                cout << "Enter cab company: ";
                cin.ignore();
                getline(cin, details);
                break;
            case 5:
                mode = "Other";
                cout << "Enter mode of transportation: ";
                cin.ignore();
                getline(cin, details);
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }

        cout << "Enter Timings: ";
        cin >> time;

        user.setTripDetails(from, to, date,mode, details, time);
    }

    // Get all possible companions for a specific user
    
    vector<User> getPossibleCompanions(const User& user) const {
        vector<User> possibleCompanions;
        for (size_t i = 0; i < users.size(); ++i) {
            if (users[i].canBeCompanion(user) && users[i].getUsername() != user.getUsername()) {
                possibleCompanions.push_back(users[i]);
            }
        }
        return possibleCompanions;
    }

    // Display all details of a possible companion
    
    void displayCompanionDetails(const User& companion) const {
        cout << "Companion Details: ";
        cout << "Name: " << companion.getName() << ", ";
        cout << "Age: " << companion.getAge() << ", ";
        cout << "Gender: " << companion.getGender() << ", ";
        cout << "From: " << companion.getFrom() << ", ";   // Change current location to From
        cout << "To: " << companion.getTo() << ", ";       // Change destination to To
        cout << "Date: "<<companion.getdate()<< ", ";
		cout << "Mode of Transportation: " << companion.getModeOfTransportation() << ", ";
        cout << "Transportation Details: " << companion.getTransportationDetails() << ", ";
        cout << "Timings: " << companion.getTimings() << endl;
    }

private:
    
    string maskedInput() {
        string password;
        char ch;
        while ((ch = getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // Backspace
                if (!password.empty()) {
                    cout << "\b \b"; // Erase the character by moving cursor back, printing space, and moving cursor back again
                    password = password.substr(0, password.size() - 1); // Remove the last character from the password
                }
            } else {
                cout << '*'; 
                password.push_back(ch); 
            }
        }
        cout << endl; 
        return password;
    }
};

int main() {
    TravelCompanion travelCompanion("users.txt");
    travelCompanion.loadUsersFromFile();

    int choice;
    string username;

    cout<<"---------SAFAR KA SATHI-----------\n";
    
    while (true) {
    	cout<<"-----------MENU--------------\n";
        cout << "1. Registeration\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                travelCompanion.registerUser();
                break;
            case 2:
                cout << "Enter username: ";
                cin >> username;
                try {
                    User& currentUser = const_cast<User&>(travelCompanion.loginUser(username));
                    cout << "Login successful!\n";
                    travelCompanion.updateTripDetails(currentUser);
                    
					// Get possible companions for the current user
                    
					vector<User> possibleCompanions = travelCompanion.getPossibleCompanions(currentUser);
                    if (possibleCompanions.empty()) {
                        cout << "No companions found.\n";
                    } else {
                        cout << "Possible Companions:\n";
                        for (size_t i = 0; i < possibleCompanions.size(); ++i) {
                            travelCompanion.displayCompanionDetails(possibleCompanions[i]);
                        }
                    }
                    // Do other operations after login
                    
                } catch (const char* e) {
                    cout << e << endl; // Print the error message
                }
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

