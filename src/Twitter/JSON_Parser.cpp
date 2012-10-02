#include "JSON_Parser.h"

#include "Tweet.h"
#include "User.h"

using namespace Twitter;

JSON_Parser::JSON_Parser() {

	Json::Value val;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( "", val );
	if ( !parsingSuccessful ) {
		std::cout << "trololol" << std::endl;
	}
	else {
		std::cout << "dfsfdf" << std::endl;
	}
}

int JSON_Parser::test() {

	std::ifstream infile;

	infile.open ("tests/tweet.json", std::ifstream::in);

	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( infile, root );


	if ( !parsingSuccessful ) {
	    // report to the user the failure and their locations in the document.
	    std::cout  << "Failed to parse configuration\n"
	               << reader.getFormatedErrorMessages();
	    return -1;
	}

	std::cout << root["created_at"] << std::endl;

	std::cout << "Parsed !" << std::endl;

	return 0;

}

JSON_Parser::~JSON_Parser() {

}
