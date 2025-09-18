#include <iostream>
#include <fstream>
#include "contacts.pb.h"
using namespace std;

void PrintContacts(contacts2::Contacts& contacts)
{
    for (int i = 0; i < contacts.contacts_size(); i++)
    {
        cout << "----------" << i << "th contacts" << "----------" << endl;
        const contacts2::PeopleInfo& people = contacts.contacts(i);
        cout << "name:   " << people.name() << endl;
        cout << "age:    " << people.age() << endl;
        for (int j = 0; j < people.phone_size(); j++)
        {
            const contacts2::PeopleInfo_Phone& phone = people.phone(j);
            cout << "phone" << j << ": " << phone.number();
            cout << "    (" << phone.PhoneType_Name(phone.type()) << ")" << endl;
        }
    }
}


int main()
{
    // read local book file
    contacts2::Contacts contacts;

    fstream input("contacts.bin", ios::in | ios::binary);
    if (!contacts.ParseFromIstream(&input))
    {
        cerr << "parse error!" << endl;
        input.close();
        return -1;
    }

    // print contacts list
    PrintContacts(contacts);
    input.close();

    return 0;
}