#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

int main(int argc, char** argv){
	ifstream file;
	string line;
	regex re("(?<key>\\w+)=(?<value>\\w+)");
	map<string, string> config;

	file.open("config.ini");

	while( getline(file, line) ){
		smatch result;
		if ( regex_search( line, result, re ) )
			//zapis do mapy
			config[result["key"]] = result["value"];
	}

	file.close();
	
	for(auto &i: config)
		if(i.first[0] == 'A')
			//wyswietla wszystkie wartosc dla kluczy o pierwszym znaku 'A'
			cout << i.first << " => " << i.second << endl;
	cout << "SDorder has value: " << config.find("SDorder")->second << endl;
}
