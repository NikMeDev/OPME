#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

struct passwd *pw = getpwuid(getuid());

const char *homedir = pw->pw_dir;

using namespace::std;

int main(int argc,char* argv[]) {
    if(argc == 1){
        cout << "Open Password Manager with Encryption v0.3" << endl;
        cout << "Autor: NikMe" << endl;
        cout << "Usage:" << endl;
        cout << "opme add <name of service> - add password" << endl;
        cout << "opme generate <name of service> - generate new password and add it" << endl;
        cout << "opme get <name of service> - get password" << endl;
        cout << "opme rename <name of service> <new name of service> - rename service name" << endl;
        cout << "opme remove <name of service> - delete password" << endl;
        return 0;
    }
    if(string(argv[1]) == "add") {
        if(argv[2]) {
            char password[100];
            int keyNumber;
            cout << "Enter keynum:";
            cin >> keyNumber;
            cout << "Enter your password for " << argv[2] << ":";
            cin >> password;
            for(int i = 0; (i < 100 && password[i] != '\0'); i++) {
                password[i] = password[i] + keyNumber;
            }
            string path = homedir + string("/pass/") + argv[2];
            ofstream file (path);
            if(file.is_open()) {
                file << password;
                file.close();
            } else {
                cout << "Can't create file " << argv[2] << endl;
            }
        } else {
            cout << "Not enough arguments!" << endl;
            cout << "Usage:" << endl;
            cout << "opme add <name of service> - add password" << endl;
        }
        return 0;
    }
    if(string(argv[1]) == "get") {
        if(argv[2]) {
            string path = homedir + string("/pass/") + argv[2];
            ifstream file (path);
            file.open(argv[2]);
            if(file.is_open()) {
                char password[100];
                int keyNumber;
                cout << "Enter your keynum:";
                cin >> keyNumber;
                file >> password;
                for(int i = 0; (i < 100 && password[i] != '\0'); i++) {
                    password[i] = password[i] - keyNumber;
                }
                cout << "Password for " << argv[2] << ":" << password << endl;
                file.close();
            } else {
                cout << "Can't open file " << argv[2] << endl;
            }
        } else {
            cout << "Not enough arguments!" << endl;
            cout << "Usage:" << endl;
            cout << "opme get <name of service> - get password" << endl;
        }
        return 0;
    }
    if(string(argv[1]) == "remove") {
        if(argv[2]) {
            string path = homedir + string("/pass/") + argv[2];
            remove(path.c_str());
            cout << "Password for " << argv[2] << " deleted!" << endl;
        } else {
            cout << "Not enough arguments!" << endl;
            cout << "Usage:" << endl;
            cout << "opme remove <name of service> - delete password" << endl;
        }
        return 0;
    }
    if(string(argv[1]) == "rename") {
        if(argv[2] && argv[3]) {
            string path1 = homedir + string("/pass/") + argv[2];
            string path2 = homedir + string("/pass/") + argv[3];
            rename(path1.c_str(),path2.c_str());
            cout << "Rename " << argv[2] << " to " << argv[3] << " successful!" << endl;
        } else {
            cout << "Not enough arguments!" << endl;
            cout << "Usage:" << endl;
            cout << "opme rename <name of service> <new name of service> - rename service name" << endl;
        }
        return 0;
    }
    if(string(argv[1]) == "generate") {
        if(argv[2]) {
            srand(time(NULL));
        	char * pass = new char[16 + 1];
        	for (int i = 0; i < 16; ++ i) {
		        switch(rand() % 3){
		            case 0:
			            pass[i] = rand() % 10 + '0';
			            break;
		            case 1:
			            pass[i] = rand() % 26 + 'A';
			            break;
		            case 2:
			            pass[i] = rand() % 26 + 'a';
	        	}   
	        }
	        pass[16] = 0;
            int keyNumber;
            cout << "Enter keynum:";
            cin >> keyNumber;
            for(int i = 0; (i < 100 && pass[i] != '\0'); i++) {
                pass[i] = pass[i] + keyNumber;
            }
            string path = homedir + string("/pass/") + argv[2];
            ofstream file (path);
            if(file.is_open()) {
                file << pass;
                file.close();
            } else {
                cout << "Can't create file " << argv[2] << endl;
            }
        } else {
            cout << "Not enough arguments!" << endl;
            cout << "Usage:" << endl;
            cout << "opme generate <name of service> - add password" << endl;
        }
        return 0;
    }
    if(argv[1]){
        cout << "Command " << argv[1] << " is not found.\nUsage:" << endl;
        cout << "opme add <name of service> - add password" << endl;
        cout << "opme get <name of service> - get password" << endl;
        cout << "opme generate <name of service> - add password" << endl;
        cout << "opme rename <name of service> <new name of service> - rename service name" << endl;
        cout << "opme remove <name of service> - delete password" << endl;
        return 0;
    }
    cout << "Unhandlead error" << endl;
    return 0;
};