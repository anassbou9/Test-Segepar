#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include <algorithm>
#include <sstream>      // std::stringstream

using namespace std;
using namespace rapidxml;

xml_document<> doc;
xml_node<> * root_node = NULL;

string XML2SQL(vector<char> & buffer)  {

    return 0;
}

string convertToSql(string fileName){

    vector<string> myTownFields = {"id", "code", "name", "population", "average_age", "district_code", "department_code", "region_code", "region_name"};

    stringstream ss;
    // Read the xml file
    ifstream theFile (fileName);
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node("query")->first_node("fields");

    ss << "SELECT ";
   
    // Iterate over the fields nodes
    for (xml_node<> * field_node = root_node->first_node("field"); field_node; field_node = field_node->next_sibling())
    {
      if (find(myTownFields.begin(), myTownFields.end(), field_node->value()) != myTownFields.end())
        ss << field_node->value() << ", ";
      else {
        cout << "Field doesn't exist " << endl;
        throw exception();    
        }
    }

    ss << endl<< "FROM towns" <<endl;
    return ss.str();

}

int main()
{
   
    // Calling the function
    string s = convertToSql("exemple.xml");
    cout << s;
    
   
    return 0;
}