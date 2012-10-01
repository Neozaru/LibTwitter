#ifndef H_PARSABLE_OBJECT_H
	#define H_PARSABLE_OBJECT_H

	#include <jsoncpp/json.h>

	#include <iostream>
	#include <fstream>

class Parsable_Object {
protected:

	/*
	Parsable_Object( const std::string& json_string ) {
		_json_reader.parse( json_string, _json_root_node );
	}

	Parsable_Object( std::ifstream json_stream ) {
		_json_reader.parse( json_stream, _json_root_node );
	}
	*/


	Parsable_Object ( const Json::Value& root_node ) {
		_json_root_node = root_node;

		if ( !_json_root_node.empty() ) {
			_valid = true;
		}
	}

public:

	Parsable_Object ( bool valid = false ) : _valid(valid) {}

	~Parsable_Object() {}

	const Json::Value& get_json_root_node() {
		return _json_root_node;
	}

	bool is_valid() {
		return _valid;
	}

protected:

	//Json::Reader _json_reader;
	Json::Value _json_root_node;

	bool _valid;
	
};


#endif
