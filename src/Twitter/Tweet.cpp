#include "Tweet.h"

#include "User.h"
#include <Twitter/Core/TwitterSession.h>
#include <Twitter/Core/TwitterRequest.h>


#include "Information_Manager.h"

using namespace Twitter;

Tweet::Tweet( const Json::Value& root_node, TwitterSession* session ) 
: Parsable_Object(root_node), _session(session), _sender(NULL), _original_author(NULL) {

	_id = _json_root_node["id_str"].asString();
	_text = _json_root_node["text"].asString();

	_retweet_count = _json_root_node["retweet_count"].asInt();

}

Tweet::~Tweet() {


}


int Tweet::get_retweet_count() {
	return _retweet_count;
}

const std::string& Tweet::get_text() {
	return _text;
}

const std::string& Tweet::get_id() {
	return _id;
}

bool Tweet::retweet() {

	if ( _session != NULL ) {

		TwitterRequest* req = _session->retweet_request( this->get_id(), true );
		req->send();

		if ( req->get_response_code() == 200 ) {
			return true;
		}

	}

	return false;

}

bool Tweet::set_sender( User* sender ) {

	if ( _json_root_node["user"].isNull() || _json_root_node["user"]["id_str"] == sender->get_id() ) {
		_sender = sender;
		return true;
	}
	else {
		std::cout << "Failed to set user. Content : " << _json_root_node["user"] << std::endl;
	}

	return false;

}


void Tweet::to_stream( std::ostream& stream ) const {
	stream << "Tweet id : " << _id << std::endl;
	if ( _sender != NULL ) {
		stream << "From : " << _sender->get_screen_name() << std::endl;
	}
	stream << "Content : " << _text << std::endl;
	//stream << "User description : " << _description << std::endl;
}