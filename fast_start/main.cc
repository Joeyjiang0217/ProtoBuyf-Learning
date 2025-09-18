#include <iostream>
#include <string>
#include "contacts.pb.h"

int main()
{
    std::string people_str;
    {

        contacts::PeopleInfo people;
        people.set_name("zhangsan");
        people.set_age(20);
        if (!people.SerializeToString(&people_str))
        {
            std::cerr << "serialize contacts failed" << std::endl;
            return -1;
        }

        std::cout << "serialize success, result: " << people_str << std::endl;
    }

    {
        contacts::PeopleInfo people;
        if (!people.ParseFromString(people_str))
        {
            std::cerr << "deserialzation failed!" << std::endl;
            return -1;
        }
        std::cout << "deserialize success" << std::endl
                  << "name: " << people.name() << std::endl
                  << "age: " << people.age() << std::endl;
    }
    

    return 0;

}