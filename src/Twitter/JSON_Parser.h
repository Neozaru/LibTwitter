#ifndef H_JSON_PARSER_H
	#define H_JSON_PARSER_H

	#include <jsoncpp/json.h>

	#include <iostream>
	#include <fstream>
	

class JSON_Parser {
public:
	JSON_Parser();
	~JSON_Parser();

	int test();

	static const Json::Value parse_string_to_JSON( const std::string& str ) {

		Json::Reader reader;
		Json::Value root_node;

		reader.parse(str,root_node);

		return root_node;

	}

};


#endif