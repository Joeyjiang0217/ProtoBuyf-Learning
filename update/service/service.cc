#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;
using namespace s_contacts;

/**
 * 新增联系⼈ 
 */
void AddPeopleInfo(PeopleInfo *people_info_ptr) {
    cout << "-------------New added contacts-------------" << endl;
    cout << "Enter the name: ";
    string name;
    getline(cin, name);
    people_info_ptr->set_name(name);

    // cout << "age: ";
    // int age;
    // cin >> age;
    // people_info_ptr->set_age(age);
    // cin.ignore(256, '\n'); 

    cout << "Enter the birthday: ";
    int birthday;
    cin >> birthday;
    people_info_ptr->set_birthday(birthday);
    cin.ignore(256, '\n'); 

    for(int i = 1; ; i++) {
        cout << "Enter the phone number" << i << ": ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        PeopleInfo_Phone* phone = people_info_ptr->add_phone();
        phone->set_number(number);
    }
    cout << "-----------Succeeded to add-----------" << endl;
}

int main() {

    s_contacts::Contacts contacts;    
    // read the local existing address book file
    fstream input("../contacts.bin", ios::in | ios::binary);
    if (!input) {
        cout << "contacts.bin not found. Creating a new file." << endl;
    } else if (!contacts.ParseFromIstream(&input)) {
        cerr << "Failed to parse contacts." << endl;
        input.close();
        return -1;
    }

    // add new contacts
    AddPeopleInfo(contacts.add_contacts());

    // write the new contact to a disk file
    fstream output("../contacts.bin", ios::out | ios::trunc | ios::binary);
    if (!contacts.SerializeToOstream(&output)) {
        cerr << "Failed to write contacts." << endl;
        input.close();
        output.close();
        return -1;
    }

    input.close();
    output.close();
    return 0;
}
