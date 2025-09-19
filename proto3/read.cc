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
        if (people.has_data() && people.data().Is<contacts2::Address>())
        {
            contacts2::Address address;
            people.data().UnpackTo(&address);
            if (!address.home_address().empty())
            {
                cout << "home address: " << address.home_address() << endl;
            }
            if (!address.unit_address().empty())
            {
                cout << "unit address: " << address.unit_address() << endl;
            }
        }

        // if (people.has_qq())
        // {

        // }
        // else if (people.has_wechat())
        // {

        // }
        switch (people.other_contact_case())
        {
        case contacts2::PeopleInfo::OtherContactCase::kQq:
            cout << "qq: " << people.qq() << endl;
            break;
        case contacts2::PeopleInfo::OtherContactCase::kWechat:
            cout << "wechat: " << people.wechat() << endl;
            break;
        default:
            break;
        }

        if (people.remark_size())
        {
            cout << "remark: " << endl;
        }

        for (auto it = people.remark().cbegin(); it != people.remark().cend(); it++)
        {
            cout << "        " << it->first << ": " << it->second << endl;
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