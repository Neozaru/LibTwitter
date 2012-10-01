#include "Session.h"

#include "Tweet.h"
#include "User.h"

using namespace Twitter;

Session::Session() {
	//_tc_session = new TwitterSession();
}

bool Session::connect( const std::string& username, const std::string& password ) {

	const std::string& url = this->generate_auth_URL();
	return this->bypass_PIN_with_password( url, username, password );

}

Session::~Session() {}

User* Session::get_myself() {

	TwitterRequest* req = this->verify_credentials_request();
	req->send();

	if ( req->get_response_code() == 200 ) {

		const std::string& data = req->get_response_data();

		return User::from_JSON( JSON_Parser::parse_string_to_JSON(data), this );

	}

	return NULL;
}

Tweet* Session::get_tweet( const std::string& tweet_id ) {

	TwitterRequest* req = this->show_status_request(tweet_id);
	req->send();

	if ( req->get_response_code() == e_HTTP_response_code::OK ) {

		const std::string& data = req->get_response_data();

		Tweet* tweet = Tweet::from_JSON( 
			JSON_Parser::parse_string_to_JSON(data),
			this );

		return tweet;

	}

	return NULL;

}