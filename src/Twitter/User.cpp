#include "User.h"

#include "Tweet.h"
#include "Session.h"
//#include "Parsable_Object.h"

#include <Twitter/Core/TwitterSession.h>

using namespace Twitter;

User::User(	 const Json::Value& root_node, Session* session ) 
	: Parsable_Object(root_node), _auto_load(true), _fully_loaded(false), _status(NULL), _session(session) {

	_id = _json_root_node["id_str"].asString();
	_screen_name = _json_root_node["screen_name"].asString();


	if ( false ) { // TODO
		_fully_loaded = true;
	}

}

const std::string& User::get_id() {
	return _id;
}

const std::string& User::get_screen_name() {
	return _screen_name;
}

const std::string& User::get_description() {

	if ( _description.empty() ) {

		Json::Value description_node = _get_value("description");
		
		if ( !description_node.empty() ) {
			_description = description_node.asString();
		}
	
	}

	return _description;

}

const time_t& User::get_creation_date() {

//
	return _creation_date;

}

Tweet* User::get_status() {

	if ( _status == NULL ) {

		Json::Value status_node = _get_value("status");

		if ( !status_node.empty() ) {
			_status = Tweet::from_JSON( status_node, _session );
		}
		else {
			_status = new Tweet(false);
		}

	}

	return _status;

}

const std::list<Tweet*>& User::get_tweets( int count, bool include_retweets, bool include_replies ) {

	if ( _session ) {

		// TODO change order of args
		TwitterRequest* req = _session->user_timeline_by_id_request( _id, count );
		req->send();

		if ( req-> get_response_code() == 200 ) {

			const std::string& data = req-> get_response_data();

			Json::Reader reader;
			Json::Value tweets_roots;

			reader.parse(data,tweets_roots);

			_timeline = Tweet::list_from_JSON( tweets_roots, _session );
			// TODO : Set myslef as owner of Timeline Tweets

		}


	}

	return _timeline;

}

bool User::follow() {

	this->_set_following(true);

}

bool User::unfollow() {

	this->_set_following(false);

}

bool User::_set_following( bool follow ) {

	if ( _session != NULL ) {

		TwitterRequest* req;

		if ( follow ) {
			req = _session->create_friendship_by_id_request( _id, true );
		}
		else {
			req = _session->destroy_friendship_by_id_request( _id ); 
		}

		req->send();

		if ( req->get_response_code() == 200 ) {
			return true;
		}

	}

	return false;

}

void User::request_full_info( bool force ) {

	if ( !_fully_loaded || force ) {

		// Request JSON
		const std::string& data = ""; // STUB

		Json::Reader reader;
		Json::Value root_node;
		reader.parse( data, root_node );

		if ( root_node["id_str"] == _json_root_node["id_str"] ) {
			_json_root_node = root_node;
		}

	}

}


const Json::Value& User::_get_value( const std::string& value ) {

	if ( _json_root_node[value].empty() && _auto_load ) {

		this->request_full_info();

	}

	return _json_root_node[value];

}


void User::to_stream( std::ostream& stream ) const {
	stream << "User id : " << _id << std::endl;
	stream << "User screen_name : " << _screen_name << std::endl;
	stream << "User description : " << _description << std::endl;
}

Json::Value send_and_get_json( TwitterRequest* req ) {

	Json::Value json;
	req->send();

	if ( req->get_response_code() == 200 ) {

		json = JSON_Parser::parse_string_to_JSON( req->get_response_data() );

	}

	return json;

}

const std::list<User*>&	User::get_followers() {

	std::list<User*> followers;

	TwitterRequest* req = _session->followers_ids_request( _id, true );
	Json::Value json = send_and_get_json( req );


	followers = ( !json.isNull() ? User::list_from_JSON( json ) : followers );

	return followers;

}


const std::list<User*>& User::get_following() {

	std::list<User*> following;

	TwitterRequest* req = _session->friends_ids_request( _id, true );
	Json::Value json = send_and_get_json( req );

	following = ( !json.isNull() ? User::list_from_JSON( json ) : following );


	return following;


}

User::~User() {
	
}