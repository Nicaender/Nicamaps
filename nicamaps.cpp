#include "nicamaps.h"
#include <admin.h>
#include <user.h>

NicaMaps::NicaMaps()
{

}

void NicaMaps::mode() const
{
    cout << "Who are you?" << endl;
    cout << "(1) Admin" << endl;
    cout << "(2) User" << endl;
    cout << "(3) Exit" << endl;
}

void NicaMaps::benutzerMenu() const
{
    // Initialization Attributes
    bool exit = false;
    string option;
    int state = 0;      // 0 = Reset, 1 = Admin, 2 = User, 3 = Exit
    Admin admin;
    User user;

    // Ask whether the user is an admin


    while(exit == false)
    {
        exit = false;
        if(state == 0)      // Wahlmodus
        {
            mode();
            cin >> state;
            if(!cin)
            {
                cout << "Geben Sie bitte einen gueltigen Datentyp!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
            }
            continue;
        }
        else if(state == 1)     // Admin
        {
            string password;
            cout << "Passwort? " << endl;
            cin >> password;
            if(password != "nicanica")
            {
                cout << "Falsches Passwort! zurueck zum Wahlmodus." << endl;
                state = 0;
                continue;
            }
            else
            {
                string name, startort, zielort;
                long double latitude, longitude;
                while(exit == false)
                {
                    cout << string(5, '\n');
                    admin.benutzerMenu();
                    cin >> option;

                    switch(option[0])
                    {
                    case 'a':
                    {
                        cout << "Ort? ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        getline(cin, name);
                        cout << "Latitude? ";
                        cin >> latitude;
                        if(!cin)
                        {
                            cout << "Geben Sie bitte einen gueltigen Datentyp!" << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            break;
                        }
                        cout << "Longitude? ";
                        cin >> longitude;
                        if(!cin)
                        {
                            cout << "Geben Sie bitte einen gueltigen Datentyp!" << endl;
                            cin.clear();
                            cin.ignore(1000, '\n');
                            break;
                        }
                        Ort* newOrt = new Ort(name, latitude, longitude);
                        admin += newOrt;
                        name.clear();
                        latitude = 0;
                        longitude = 0;
                        break;
                    }
                    case 'b':
                        cout << "Ort? ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        getline(cin, name);
                        admin.delOrt(name);
                        name.clear();
                        break;
                    case 'c':
                        admin.showAllOrt();
                        break;
                    case 'd':
                        cout << "Startort? ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        getline(cin, startort);
                        if(!admin.checkOrtExist(startort))
                            break;
                        cout << "Zielort? ";
                        cin.clear();
                        getline(cin, zielort);
                        if(!admin.checkOrtExist(zielort))
                            break;
                        if(admin.createArc(startort, zielort))
                            cout << "Verbindung von " << startort << " nach " << zielort << " wurde hergestellt" << endl;
                        else
                            cout << "Verbindung von " << startort << " nach " << zielort << " konnte hergestellt, weil es schon existiert ist" << endl;
                        break;
                    case 'e':
                        cout << "Startort? ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        getline(cin, startort);
                        if(!admin.checkOrtExist(startort))
                            break;
                        cout << "zielOrt? ";
                        cin.clear();
                        getline(cin, zielort);
                        if(!admin.checkOrtExist(zielort))
                            break;
                        if(admin.delArc(startort, zielort))
                            cout << "Verbindung von " << startort << " nach " << zielort << " wurde geloescht" << endl;
                        else
                            cout << "Verbindung von " << startort << " nach " << zielort << " konnte nicht geloescht werden" << endl;
                        break;
                    case 'x':
                        exit = true;
                        break;
                    case 'y':
                        cout << "Ort? ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                        getline(cin, name);
                        if(admin.checkOrtExist(name))
                            cout << "Ort existiert." << endl;
                        else
                            cout << "Ort existiert nicht." << endl;
                        name.clear();
                        break;
                    case 'z':       // Back to Wahlmodus
                        state = 0;
                        exit = true;
                        break;
                    default:
                        cout << "Geben Sie bitte eine gueltige Wahl!" << endl;
                        break;
                    }
                }
            }
        }
        else if(state == 2)      // User logon
        {
            string startOrt, zielOrt, ort;
            Ort* startOrtPointer = nullptr;
            Ort* zielOrtPointer = nullptr;
            while(exit == false)
            {
                cout << string(5, '\n');
                user.benutzerMenu();
                cin >> option;

                switch(option[0])
                {
                case 'a':
                    cout << "Start Ort? ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getline(cin, startOrt);
                    if(!admin.checkOrtExist(startOrt))
                    {
                        cout << "Ort existiert nicht." << endl;
                        break;
                    }
                    startOrtPointer = admin.getOrt(startOrt);
                    cout << "\nZiel Ort? ";
                    cin.clear();
                    getline(cin, zielOrt);
                    if(!admin.checkOrtExist(zielOrt))
                    {
                        cout << "Ort existiert nicht." << endl;
                        break;
                    }
                    zielOrtPointer = admin.getOrt(zielOrt);
                    user.giveOrt(startOrtPointer, zielOrtPointer);
                    startOrt.clear();
                    zielOrt.clear();
                    break;
                case 'b':
                    user.navigation();
                    admin.setAllVisit(false);
                    admin.resetAllDistance();
                    break;
                case 'x':
                    exit = true;
                    break;
                case 'y':
                    cout << "Ort? ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getline(cin, ort);
                    if(admin.checkOrtExist(ort)) cout << "Ort existiert." << endl;
                    ort.clear();
                    break;
                case 'z':       // Back to Wahlmodus
                    state = 0;
                    exit = true;
                    break;
                default:
                    cout << "Geben Sie bitte eine gueltige Wahl!" << endl;
                    break;
                }
            }
        }
        else if(state == 3)     // Get out from the program
        {
            exit = true;
        }
        else
        {
            cout << "Geben Sie bitte eine gueltige Wahl!" << endl;
            state = 0;
        }

        if(exit == true && state == 0)      // Back to Wahlmodus
        {
            exit = false;
            continue;
        }
    }
}
