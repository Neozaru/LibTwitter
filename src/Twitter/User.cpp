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

			for ( int i = 0; i < tweets_roots.size(); ++i ) {
			   
				Tweet* tw = Tweet::from_JSON( tweets_roots[i], _session );
				if ( tw != NULL ) {
					tw->set_sender( this );
					_timeline.push_back(tw);
				}

			}


		}


	}

	return _timeline;

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

User::~User() {
	
}