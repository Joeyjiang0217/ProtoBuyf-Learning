#include <iostream>
#include <fstream>
#include "contacts.pb.h"

using namespace std;

void AddPeopleInfo(contacts2::PeopleInfo* people)
{
    cout << "----------New Added Contact-----------" << endl;
    cout << "Enter name: ";
    string name;
    getline(cin, name);
    people->set_name(name);

    cout << "Enter age: ";
    int age;
    cin >> age;
    people->set_age(age);
    cin.ignore(256, '\n');

    for (int i = 0;; i++)
    {
        cout << "Enter Phone Number" << i + 1 << ": ";
        string number;
        getline(cin, number); 
        if (number.empty())
        {
            break;
        }
        
        contacts2::PeopleInfo_Phone* phone = people->add_phone();
        phone->set_number(number);

        cout << "Enter Phone Type(1. Mobile  2. Telephone): ";
        int type;
        cin >> type;
        cin.ignore(256, '\n');
        switch (type)
        {
        case 1:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_MP);
            break;
        case 2:
            phone->set_type(contacts2::PeopleInfo_Phone_PhoneType::PeopleInfo_Phone_PhoneType_TEL);
            break;
        default:
            cout << "Selected error!" << endl;
            break;
        }
    }

    cout << "----------Added     Success-----------" << endl;
}

int main()
{
    contacts2::Contacts contacts;


    // read an existing local contacts file
    fstream input("contacts.bin", ios::in | ios::binary);
    if (!input)
    {
        cout << "contacts.bin not found, pls create a new file!" << endl;
    }
    else if (!contacts.ParseFromIstream(&input))
    {
        cerr << "parse error!" << endl;
        input.close();
        return -1;
    }

    // add one contact to the address book
    AddPeopleInfo(contacts.add_contacts());

    // write the book to one local file
    fstream output("contacts.bin", ios::out | ios::trunc | ios::binary);
    if (!contacts.SerializeToOstream(&output))
    {
        cerr << "write error!" << endl;
        input.close();
        output.close();
        return -1;
    }

    cout << "write success!" << endl;
    input.close();
    output.close();
    return 0;
}