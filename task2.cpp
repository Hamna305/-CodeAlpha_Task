#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream file(filename);
    string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    return users;
}

void registerUser(const string& filename) {
    unordered_map<string, string> users = loadUsers(filename);
    string username, password;

    cout << "Enter new username: ";
    cin >> username;

    if (users.find(username) != users.end()) {
        cout << "Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file(filename, ios::app);
    file << username << " " << password << endl;

    cout << " Registration successful!\n";
}

void loginUser(const string& filename) {
    unordered_map<string, string> users = loadUsers(filename);
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username] == password) {
        cout << "Login successful!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    const string filename = "users.txt";
    int choice;

    cout << "1. Register\n2. Login\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
        registerUser(filename);
    else if (choice == 2)
        loginUser(filename);
    else
        cout << "Invalid choice.\n";

    return 0;
}
