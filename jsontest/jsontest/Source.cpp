#include<iostream>
#include<string>
using namespace std;

void main()
{
	rapidjson::Document d;
	d.Parse(json.c_str());

	for (auto& m : it->value)
	{
		std::string mac = m.GetString();
		if (!utils::is_mac(mac))
		{
			(*check_result)[mac] = reply::invalid_mac;
			invalid_mac_count++;
			continue;
		}
		boost::algorithm::to_lower(mac);
		mac_list.push_back(mac);
	}
}