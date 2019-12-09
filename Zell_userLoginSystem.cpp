#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

const string PROFILE_DATABASE_FILENAME = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/profileDatabase.txt";
const string STORAGE_FILENAME = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/temporary.txt";
const string LOCATION = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/";

bool createProfile (string, string);
bool searchForUsername (string);
bool verifyPassword (string, string);
void displayProfile (string);
bool changeProfileInfo (string, int, string);

fstream profilesFile;
fstream storageFile;

int main (){
    int menuChoice;
    string username;
    string password;
    string firstName;
    string lastName;
    string age;
    string leastFavoriteName;
    int partToChange;
    string newInfo;
    string changeAgain;
    string profileComponents[6] {"username", "password", "first name", "last name", "age", "least favorite name"};

    //Display menu with operations user can perform
    cout << endl << "Personal Profile Program\n"
    << "------------------------------\n"
    << "1. Create profile\n"
    << "2. Log in and see profile information\n"
    << "3. Change profile information\n"
    << "4. Quit this program\n"
    << "------------------------------\n"
    <<"Enter your choice (1-4): ";
    //menu selection
    cin >> menuChoice;
    cout << endl;

    while (menuChoice != 4){

        switch (menuChoice){
            //Profile creation
            case 1 ://Gather username and password
                cout << "First we need a username and password...\n\n";
                cout << "Enter a username: ";
                cin >> username;
                while(searchForUsername (username)){
                    cout << "Username is already taken." << endl
                    << "Please enter a different username: ";
                    cin >> username;
                }
                cout << "Enter a password: ";
                cin >> password;
                                    
                //Gather profile info                                    
                cout << "Now we need the information to create your profile...\n\n";
                cout << "Enter your first name: ";
                cin >> firstName;
                cout << "Enter your last name: ";
                cin >> lastName;
                cout << "Enter your age: ";
                cin >> age;
                cout << "If you had a child, what name would be the last one you would ever choose to give him or her? (no spaces, only first name): ";
                if (!(cin >> leastFavoriteName)){
                    cout << "Bad input stream!";
                    cin >> leastFavoriteName;
                }
                //cin.ignore(numeric_limits<streamsize>::max(),'\n');


                //Call create profile function
                if (createProfile (username + "\n" + password + "\n", firstName + "\n" + lastName + "\n" + age + "\n" + leastFavoriteName + "\n\n")){
                    cout << "Profile creation successful!\n";
                }
                else{
                    cout << "Profile creation failed\n";
                }
                break;

            //Log in and display profile info
            case 2 :
                //get username
                cout << "Enter your username: ";
                cin >> username;

                //if entered username cannot be found in database, let them try again till they quit
                while (! searchForUsername (username) && username != "!"){
                    cout << "Username not found, try again (or type '!' to exit): ";
                    cin >> username;
                }
                if (username == "!"){
                    break;
                }

                //Get user's password
                cout << "Enter your password: ";
                cin >> password;
                //verify the user's password
                while (! verifyPassword (username, password) && password != "!"){
                    //If incorrect, let them try again till they quit
                    cout << "Incorrect password, try again (or type '!' to exit): ";
                    cin >> password;
                }
                if (password == "!"){
                    break;
                }
                //If they have a correct username and password, display the profile
                cout << endl << "Here is your profile: ";
                displayProfile (username);
                break;

            //Change profile info
            case 3 :

                //get username
                cout << "Enter your username: ";
                cin >> username;

                //if entered username cannot be found in database, let them try again till they quit
                while (! searchForUsername (username) && username != "!"){
                    cout << "Username not found, try again (or type '!' to exit): ";
                    cin >> username;
                }
                if (username == "!"){
                    break;
                }

                //Get user's password
                cout << "Enter your password: ";
                cin >> password;
                //verify the user's password
                while (! verifyPassword (username, password) && password != "!"){
                    //If incorrect, let them try again till they quit
                    cout << "Incorrect password, try again (or type '!' to exit): ";
                    cin >> password;
                }
                if (password == "!"){
                    break;
                }

                //show user current profile
                cout << endl << "Here is your current profile information:";
                displayProfile(username);
                //initialize variable
                changeAgain = "1";
                //loop while user would like to keep changing the profile
                while (changeAgain == "1"){
                    //ask user what to change
                    cout << endl << "Which part of your profile would you like to Change?\n1. Username\n2. Password\n"
                    << "3. First Name\n4. Last Name\n5. Age\n6. Least Favorite Name\n";
                    cout << "Enter 1-6: ";
                    cin >> partToChange;
                    //prompt user for new info
                    cout << endl << "What would you like your new " << profileComponents[partToChange - 1] << " to be? ";
                    cin >> newInfo;
                    //change profile with function
                    if(! changeProfileInfo (username, partToChange, newInfo)){
                        cout << "Error changing profile info";
                        break;
                    }
                    //show user new profile and ask if they would like to change again
                    cout << endl << "Here is the changed info: ";
                    displayProfile (username);
                    cout << endl << "Enter '1' to change another part of your profile\nEnter '2' or another character to exit: ";
                    cin >> changeAgain;
                }
                break;
            default : cout << "Not a menu choice\n";
        }
        
        //menu display
        cout << endl << "Math Tutor Menu\n"
        << "------------------------------\n"
        << "1. Create profile\n"
        << "2. Log in and see profile information\n"
        << "3. Change profile information\n"
        << "4. Quit this program\n"
        << "------------------------------\n"
        <<"Enter your choice (1-4): ";	
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin >> menuChoice;
        cout << endl;
    }
    return 0;
}

//create profile function
bool createProfile(string usernamePassword, string profileInfo){
    //open file
    profilesFile.open(PROFILE_DATABASE_FILENAME, ios::app);
    //if opening file fails
    if(! profilesFile){
        cout << "Failed to open file for profile creation!" << endl;
        return false;
    }
    //write user's information to a file
    profilesFile << usernamePassword <<  profileInfo;
    //close file
    profilesFile.close();
    return true;
}

//search for username function
bool searchForUsername(string enteredUsername){
    //placeholder to read file into
    string placeHolder;
    //open profile database
    profilesFile.open(PROFILE_DATABASE_FILENAME);
    //error check file opening
    if(! profilesFile){
        cout << "Failed to open file for username search!" << endl;
        return false;
    }
    //search for username
    while (profilesFile >> placeHolder){

        if (placeHolder == enteredUsername){
            profilesFile.close();
            //cout << "username was found in database\n";
            return true;
        }
    }
    //cout << "username was not found in database\n";
    profilesFile.close();
    return false;
}

//display the profile function
void displayProfile (string enteredUsername){
    //profile variables
    string placeHolder;
    string password;
    string firstName;
    string lastName;
    string age;
    string leastFavoriteName;
    //open profile database
    profilesFile.open(PROFILE_DATABASE_FILENAME);
    //error check file opening
    if(! profilesFile){
        cout << "Failed to open file for profile display!" << endl;
    }
    //search for username
    while (profilesFile >> placeHolder){
        if (placeHolder == enteredUsername){
            //when it is found, get profile info
            profilesFile >> password >> firstName >> lastName >> age >> leastFavoriteName;
            cout << endl << "Username: " << placeHolder << endl
            << "Password: " << password << endl << "First Name: " << firstName << endl << "Last Name: " << lastName << endl
            << "Age: " << age << endl << "Least Favorite Name: " << leastFavoriteName << endl;
        }
    }
    profilesFile.close();
}

//verify user's password
bool verifyPassword (string enteredUsername, string enteredPassword){
    string placeHolder;
    string password;
    profilesFile.open(PROFILE_DATABASE_FILENAME);
    if(! profilesFile){
        cout << "Failed to open file for password verification!" << endl;
    }
    while (profilesFile >> placeHolder){
        if (placeHolder == enteredUsername){
            profilesFile >> password;
            profilesFile.close();
            if (password == enteredPassword){
                return true;
            }
            else{
                return false;
            }
        }
    }
}

//Change Profile Info
bool changeProfileInfo (string enteredUsername, int whichPart, string infoToChange){
    //placeholder to write to storage file
    string temporary;
    //array of characters for filenames and locations
    char profileLocation[] = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/profileDatabase.txt";
    char storageLocation[] = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/temporary.txt";
    char temporaryLocation[] = "/Users/lukezell/Documents/Computer Programming/Intro to Computer Programming Class/cosc-a211-term-project-lukezell/temp.txt";
    //open profile database
    profilesFile.open(PROFILE_DATABASE_FILENAME);
    //check for failure to open profile database
    if(! profilesFile){
        cout << "Failed to open profile file for changing profile info!" << endl;
    }
    //open storage file
    storageFile.open(STORAGE_FILENAME);
    //check for failure to open storage file
    if(! storageFile){
        cout << "Failed to open storage file for changing profile info!" << endl;
    }

    //copy profile database to storage file until username is found
    while (getline (profilesFile, temporary) && temporary != enteredUsername){
        storageFile << temporary << endl;
    }

    //when username is found, change info to new info
    switch (whichPart){
        case 1: //change username
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        case 2: //write username
            storageFile << temporary << endl;
            //skip line
            getline (profilesFile, temporary);
            //change password
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        case 3: //write username
            storageFile << temporary << endl;
            //fill in old info
            getline (profilesFile, temporary);
            storageFile << temporary << endl;
            //skip line
            getline (profilesFile, temporary);
            //change first name
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        case 4: //write username
            storageFile << temporary << endl;
            //fill in old info
            for (int i = 0; i < 2; i++){
                getline (profilesFile, temporary);
                storageFile << temporary << endl;
            }
            //skip line
            getline (profilesFile, temporary);
            //change last name
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        case 5: //write username
            storageFile << temporary << endl;
            //fill in old info
            for (int i = 0; i < 3; i++){
                getline (profilesFile, temporary);
                storageFile << temporary << endl;
            }
            //skip line
            getline (profilesFile, temporary);
            //change age
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        case 6: //write username
            storageFile << temporary << endl;
            //fill in old info
            for (int i = 0; i < 4; i++){
                getline (profilesFile, temporary);
                storageFile << temporary << endl;
            }
            //skip line
            getline (profilesFile, temporary);
            //change least favorite name
            storageFile << infoToChange << endl;
            //fill in the rest of the info
            while (getline (profilesFile, temporary)){
                storageFile << temporary << endl;
            }
            break;
        default: cout << "not a valid input";
    }

    profilesFile.close();
    storageFile.close();

    if(rename(storageLocation, temporaryLocation) == 1){
        cout << "Error renaming storage file to 'temp.txt'\n";
        return false;
    }
    if(rename(profileLocation, storageLocation) == 1){
        cout << "Error renaming profile database\n to 'temporary.txt'\n";
        return false;
    }
    if(rename(temporaryLocation, profileLocation) == 1){
        cout << "Error renaming 'temp.txt'\n to 'profileDatabase.txt'";
        return false;
    }
    return true;
}