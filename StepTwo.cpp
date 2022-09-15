#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "rapidxml.hpp"
#include <sstream>      // std::stringstream


using namespace std;
using namespace rapidxml;

xml_document<> doc;
xml_node<> * root_node = NULL;

vector<string> myTownFields = {"id", "code", "name", "population", "average_age", "district_code", "department_code", "region_code", "region_name"};
vector<string> myTownFieldsTypes = {"int", "int", "string", "int", "float", "int", "string", "int", "string"};


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool checkValueTypeIsValid(string field, string value) {
  vector<string>::iterator itr = find(myTownFields.begin(), myTownFields.end(), field);
  int index = distance(myTownFields.begin(), itr);

  string valueType = myTownFieldsTypes[index];

  if (valueType == "int" || valueType == "float") {
    return is_number(value);
  } else {
    return !is_number(value);
  }
}

string convertToSql(string fileName){
// Read the exemple.xml file
    stringstream ss;
    vector<string> myTownFields = {"id", "code", "name", "population", "average_age", "district_code", "department_code", "region_code", "region_name"};
    ifstream theFile (fileName);
    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    // Parse the buffer
    doc.parse<0>(&buffer[0]);

    // Find out the root node
    root_node = doc.first_node("query");
    xml_node<>* fields_node = root_node->first_node("fields");
    
    ss << "SELECT ";
   
    // Iterate over the fields nodes
    for (xml_node<> * field_node = fields_node->first_node("field"); field_node; field_node = field_node->next_sibling())
    {
      if (find(myTownFields.begin(), myTownFields.end(), field_node->value()) != myTownFields.end())
        ss << field_node->value() << ", ";
      else {
        cout << "Field doesn't exist " << endl;
        throw exception();
      }    
    }

    ss << endl<< "FROM towns" <<endl;

    // Iterate over the filters nodes
    xml_node<>* filters_node = root_node->first_node("filters");

    if (filters_node) {
      ss << "WHERE ";

      xml_node<> * field_node = filters_node->first_node("field");
      xml_node<> * value_node = filters_node->first_node("value");
      xml_node<> * predicate_node = filters_node->first_node("predicate");

      // Setting the predicate
      string predicate = predicate_node->value();
      if (predicate == "eq") predicate = "=";
      else if (predicate == "gt") predicate = ">";
      else if (predicate == "lt") predicate = "<";
      else if (predicate == "contains") predicate = "contains";
      else predicate = "=";

      if (find(myTownFields.begin(), myTownFields.end(), field_node->value()) != myTownFields.end() && checkValueTypeIsValid(field_node->value(), value_node->value())) {
        ss << field_node->value() << predicate << value_node->value() << endl;
      }
    }
    return ss.str();
}

int main(void)
{

    // Calling the function
    string s = convertToSql("exemple_2.xml");
    cout << s;
    
    return 0;
}
