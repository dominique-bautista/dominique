#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>


//max
const int max_words = 100;
const int max_users = 20;
const int max_length = 100;

//entries
char words[max_words][max_length];
char definitions[max_words][max_length];
char categories[max_words][max_length] = {"Changed Words", "Acronyms"};
char changedWords[max_words][max_length];
char acronyms[max_length][max_length];
int approved[max_words];
int wordCount = 0;

//accounts
char usernames[max_users][max_length];
char passwords[max_users][max_length];
int isAdmin[max_users];
int userCount = 0;

int isLoggedIn = 0;
int currentUserIndex = -1;


//functions
void loadDatabase();

void saveDatabase();

void loadUsers();

void saveUsers();


void mainMenu();

void adminMenu();

void userMenu();

void adminLogin();

void userLogin();

void registerUser();

void initializeDefaultAdmin();

void addAndEdit();

void categorize();

void approval();

void feedback();

void manageUsers();

void backup();

void restore();


//global variables
int choice = 0, i = 0;

//default admin
void initializeDefaultAdmin() {
    strcpy(usernames[0], "admin");
    strcpy(passwords[0], "admin");
    isAdmin[0] = 1;
    userCount = 1;
}

//files
void loadDatabase() {
    ifstream load;
    load.open("database.txt");
    wordCount = 0;
    while (load >> words[wordCount]) {
        load.ignore();
        load.getline(definitions[wordCount], max_length);
        load.getline(changedWords[wordCount], max_length);
        load.getline(acronyms[wordCount], max_length);
        load >> approved[wordCount];
        wordCount++;
        cout << "Database loaded.\n";
    }
    load.close();
}

void saveDatabase() {
    ofstream save ("database.txt");
    for (i = 0; i < wordCount; i++) {
        save << words[i] << "\n" << definitions[i] << "\n" << changedWords[i] << "\n" << acronyms[i] << "\n"
             << approved[i] << "\n";
    }
    save.close();
}

void loadUsers() {
    ifstream loadUsers ("users.txt");
    userCount = 1;
    while (loadUsers >> usernames[userCount]) {
        loadUsers >> passwords[userCount];
        loadUsers >> isAdmin[userCount];
        userCount++;
        cout << "Users Loaded.\n";
    }
    loadUsers.close();
}

void saveUsers() {
    ofstream saveUsers ("users.txt");
    for (i = 0; i < userCount; i++) {
        saveUsers << usernames[i] << " " << passwords[i] << " " << isAdmin[i] << "\n";
    }
    saveUsers.close();
}

// displays

void displayMainMenu() {
    clrscr();
    cout << "Main Menu\n";
    cout << "1. Admin Login\n";
    cout << "2. User Login\n";
    cout << "3. Register\n";
    cout << "4. Exit\n";
    cout << "Enter Choice: \n";
}

void displayAdminMenu() {
    clrscr();
    cout << "Admin Menu\n";
    cout << "1. Add and Edit Words\n";
    cout << "2. Categorize Words\n";
    cout << "3. Approval Queue\n";
    cout << "4. Feedback Management\n";
    cout << "5. Manage Users\n";
    cout << "6. Backup Data\n";
    cout << "7. Restore Data\n";
    cout << "8. Logout\n";
    cout << "9. Exit Program\n";
    cout << "Enter Choice: \n";
}

void displayUserMenu() {
    clrscr();
    cout << "User Menu\n";
    cout << "1. Search for Gen Z Words\n";
    cout << "2. Logout\n";
    cout << "3. Exit Program\n";
    cout << "Enter Choice: \n";
}

//menus

void mainMenu() {
    clrscr();
    int continueLoop = 1;
    while (continueLoop == 1) {
        displayMainMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                registerUser();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice.\n";
                getch();
                break;

        }
    }
}

void adminMenu() {
    clrscr();
    int continueLoop = 1;
    while (continueLoop == 1) {
        displayAdminMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addAndEdit();
                break;
            case 2:
                categorize();
                break;
            case 3:
                approval();
                break;
            case 4:
                feedback();
                break;
            case 5:
                manageUsers();
                break;
            case 6:
                backup();
                break;
            case 7:
                restore();
                break;
            case 8:
                isLoggedIn = 0;
                return;
            case 9:
                exit(0);
            default:
                cout << "Invalid choice.\n";
                getch();
                break;
        }
    }
}

void userMenu() {
    clrscr();
    int continueLoop = 1;
    while (continueLoop == 1) {
        displayUserMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "searchWords();" << "\n";
                break;
            case 2:
                isLoggedIn = 0;
                return;
            case 3:
                exit(0);
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
    getch();
}

//login functions
void adminLogin() {
    clrscr();
    char username[max_length], password[max_length];
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0 && isAdmin[i]) {
            isLoggedIn = 1;
            currentUserIndex = i;
            adminMenu();
            return;
        }
    }
    cout << "Invalid login credentials or not an admin.\n";
    getch();
    mainMenu();
}

void userLogin() {
    clrscr();
    char username[max_length], password[max_length];
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for (i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], username) == 0 && strcmp(passwords[i], password) == 0) {
            isLoggedIn = 1;
            currentUserIndex = i;
            userMenu();
            return;
        }
    }
    cout << "Invalid login credentials.\n";
    getch();
    mainMenu();
}

void registerUser() {
    clrscr();
    char newUsername[max_length], newPassword[max_length];
    a:
    cout << "Enter new username: ";
    cin >> newUsername;
    cout << "Enter new password: ";
    cin >> newPassword;

    for (i = 0; i < userCount; i++) {
        if (strcmp(usernames[i], newUsername) == 0) {
            cout << "Username already exists.\n";
            goto a;
        }
    }

    strcpy(usernames[userCount], newUsername);
    strcpy(passwords[userCount], newPassword);
    isAdmin[userCount] = 0;
    userCount++;
    saveUsers();
    cout << "Registration successful.\n";
    getch();
}

//admin functions
void addAndEdit() {
    clrscr();
    cout << "1. Add Word\n";
    cout << "2. Edit Word\n";
    cout << "Enter Choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            if (wordCount >= max_words) {
                cout << "Database is full.\n";
                return;
            }

            char newWord[max_length], newDefinition[max_length], newChangedWords[max_length], newAcronyms[max_length];
            cout << "Enter word: ";
            cin >> newWord;
            cout << "Enter definition: ";
            cin.ignore();
            cin.getline(newDefinition, max_length);
            cout << "Enter the changed word: ";
            cin.getline(newChangedWords, max_length);
            cout << "Enter the acronym: ";
            cin.getline(newChangedWords, max_length);

            for (i = 0; i < wordCount; i++) {
                if (strcmp(words[i], newWord) == 0) {
                    cout << "Word already exists.\n";
                    return;
                }
                getch();
            }

            strcpy(words[wordCount], newWord);
            strcpy(definitions[wordCount], newDefinition);
            strcpy(changedWords[wordCount], newChangedWords);
            strcpy(acronyms[wordCount], newAcronyms);
            approved[wordCount] = 0;
            wordCount++;
            saveDatabase();
            cout << "Word added to approval queue.\n";
            getch();
            break;
        case 2:
            char wordToEdit[max_length];

            if (wordCount == 0) {
                cout << "No words available to edit.\n";
                getch();
                return;
            }

            cout << "Available words:\n";
            for (i = 0; i < wordCount; i++) {
                cout << i + 1 << ". " << words[i] << " - "
                     << definitions[i] << " - "
                     << changedWords[i] << " - "
                     << acronyms[i] << " - "
                     << "\n";
            }

            cout << "Enter word to edit: ";
            cin >> wordToEdit;

            for (i = 0; i < wordCount; i++) {
                if (strcmp(words[i], wordToEdit) == 0) {
                    cout << "Enter new definition: ";
                    cin.ignore();
                    cin.getline(definitions[i], max_length);
                    cout << "Enter the new changed word: ";
                    cin.getline(changedWords[i], max_length);
                    cout << "Enter the new acronym: ";
                    cin.getline(acronyms[i], max_length);
                    saveDatabase();
                    cout << "Entry updated.\n";
                    getch();
                    return;
                }
            }
            cout << "Word not found.\n";
            getch();
            break;
        default:
            cout << "Invalid Input!\n";
            adminMenu();
            getch();
    }
}

void categorize() {
    clrscr();
    cout << "Categories [Changed Words] [Acronyms]: \n";

    for (i = 0; i < wordCount; i++) {
        int isUnique = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(categories[i], categories[j]) == 0) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique == 1) cout << categories[i] << endl;
        getch();
    }

    cout << "Enter a category to view words: ";
    char category[100];
    cin.ignore();
    cin.getline(category, max_length);

    cout << "Words in " << category << "category: \n";

    for (i = 0; i < wordCount; i++) {
        if (strcmp(categories[i], category) == 0) {
            cout << words[i] << endl;
        }
    }
    getch();
}

void approval() {
    clrscr();
    cout << "Words awaiting approval:\n";
    for (i = 0; i < wordCount; i++) {
        if (!approved[i]) {
            cout << i << ". " << words[i] << " - " << definitions[i] << " - " << changedWords[i] << " - " << acronyms[i]
                 << "\n";
        }
    }

    int index;
    cout << "Enter the index of the word to approve or reject (-1 to cancel): ";
    cin >> index;

    if (index == -1) {
        cout << "Operation canceled.\n";
        return;
    }


    cout << "Approve (1) or Reject (2): ";
    cin >> choice;

    if (choice == 1) {
        approved[index] = 1;
        cout << "Word approved.\n";
    } else if (choice == 2) {
        for (i = index; i < wordCount - 1; ++i) {
            strcpy(words[i], words[i + 1]);
            strcpy(definitions[i], definitions[i + 1]);
            strcpy(changedWords[i], changedWords[i + 1]);
            strcpy(acronyms[i], acronyms[i + 1]);
            approved[i] = approved[i + 1];
        }
        wordCount--;
        cout << "Word rejected.\n";
    } else {
        cout << "Invalid choice.\n";
    }
    getch();
    saveDatabase();
}

void feedback() { //di nagana -_-
    clrscr();
    ifstream feedbackFile ("feedback.txt");
    if (!feedbackFile) {
        cout << "No feedback available.\n";
        return;
    }

    char line[100];
    while (feedbackFile.getline(line, 100)) {
        cout << line << "\n";
    }
    feedbackFile.close();

    char response[100];
    cout << "Enter your response to user feedback: ";
    cin.ignore();
    cin.getline(response, max_length);

    ofstream responseFile ("feedback.txt", ios::app);
    responseFile << "Admin Response: " << response << "\n";
    responseFile.close();
    cout << "Response saved.\n";
    getch();
}

void manageUsers() {
    clrscr();
    cout << "User Accounts:\n";
    for (i = 0; i < userCount; ++i) {
        cout << i << ". Username: " << usernames[i] << ", Is Admin: ";
        if (isAdmin[i]) {
            cout << "Yes";
        } else {
            cout << "No";
        }
        cout << "\n";
    }
    getch();


    cout << "Promote (1), Demote (2), or Ban (3) user (or enter '4' to cancel): ";
    cin >> choice;

    if (choice == 4) {
        cout << "Operation canceled.\n";
        return;
    }

    int index;
    cout << "Enter the index of the user: ";
    cin >> index;

    if (index < 0 || index >= userCount) {
        cout << "Invalid user index.\n";
        return;
    }

    switch (choice) {
        case 1:
            isAdmin[index] = 1;
            saveUsers();
            cout << "User promoted.\n";
            break;
        case 2:
            isAdmin[index] = 0;
            saveUsers();
            cout << "User demoted.\n";
            break;
        case 3:
            for (i = index; i < userCount - 1; ++i) {
                strcpy(usernames[i], usernames[i + 1]);
                strcpy(passwords[i], passwords[i + 1]);
                isAdmin[i] = isAdmin[i + 1];
            }
            userCount--;
            saveUsers();
            cout << "User banned.\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
    }
    getch();
}

void backup() {
    clrscr();
    ifstream src("database.txt", ios::binary);
    ofstream dst("database_backup.txt", ios::binary);
    if (src && dst) {
        dst << src.rdbuf();
        cout << "Backup completed.\n";
    } else {
        cout << "Backup failed.\n";
    }
    src.close();
    dst.close();
    getch();
}

void restore() {
    clrscr();
    ifstream src("database_backup.txt", ios::binary);
    ofstream dst("database.txt", ios::binary);
    dst << src.rdbuf(); //copy contents using rdbuf
    src.close();
    dst.close();
    loadDatabase();
    cout << "Restore completed.\n";
    getch();
}

//main
void main() {
    clrscr();
    initializeDefaultAdmin();
    loadDatabase();
    loadUsers();
    mainMenu();
    getch();
}

