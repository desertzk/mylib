// Example that shows simple usage of the INIReader class

#include <iostream>
#include "INIReader.h"
#include<list>
int main()
{
	std::list<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(5);
	li.push_back(6);
	li.push_back(1);
	li.push_back(1);
	li.push_back(9);
	li.push_back(1);

	for (std::list<int>::iterator it = li.begin(); it != li.end(); ++it)
	{
		std::cout << *it << std::endl;
	}


    INIReader reader("mc.ini");

    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'test.ini'\n";
        return 1;
    }
	/*std::cout << "Config loaded from 'test.ini': version="
		<< reader.GetInteger("protocol", "version", -1) << ", name="
		<< reader.Get("user", "name", "UNKNOWN") << ", email="
		<< reader.Get("user", "email", "UNKNOWN") << ", pi="
		<< reader.GetReal("user", "pi", -1) << ", active="
		<< reader.GetBoolean("user", "active", true) << "\n";*/

	std::cout << reader.Get("o3", "servers", "") << std::endl;

	std::cin.get();
    return 0;
}
