#include "User_Stream.h"

#include "JSON_Parser.h"
#include "Tweet.h"

#include <iostream>

using namespace Twitter;

User_Stream::User_Stream( Session* session, bool followings, bool replies ) 
: TwitterRequest( session ) {

	if ( session->user_stream_request( followings ? "followings" : "user" , replies ? "all" : "-1", "-1" )->copy(this) ) {
		std::cout << "OK ! :) \n";
	}

}


User_Stream::User_Stream( Session* session, const std::string& keywords, bool followings, bool replies ) 
: TwitterRequest( session ) {

	if ( session->user_stream_request( followings ? "followings" : "user" , replies ? "all" : "-1", keywords )->copy(this) ) {
		std::cout << "OK ! :) \n";
	}

}

void User_Stream::on_data_received( const std::string& data ) {

	std::cout << "Data : [" << data << "] (" << data.size() << ")\n";


	if ( data.size() < 5 ) {
		std::cout << "Newline keepalive\n";
		return;
	}

	Json::Reader reader;
	Json::Value tweets_roots;

	reader.parse(data,tweets_roots);

	if ( !tweets_roots["friends"].empty() ) {
		std::cout << "Friand (pas bon)" << std::endl;
		return;
	}

	std::list<Tweet*> tweets;
	if ( tweets_roots.isArray() ) {
		for ( int i = 0; i < tweets_roots.size(); ++i ) {
		   
			Tweet* tw = Tweet::from_JSON( tweets_roots[i], dynamic_cast<Session*>(_session) );
			if ( tw != NULL ) {
				std::cout << "TWEEEEET : " << *tw << std::endl;
				tweets.push_back( tw );
			}

		}
	}
	else {
		Tweet* tw = Tweet::from_JSON( tweets_roots, dynamic_cast<Session*>(_session) );
		if ( tw != NULL ) {
			std::cout << "TWEEEEET : " << *tw << std::endl;
			tweets.push_back( tw );
		}
	}

	if ( tweets.size() > 0 ) {
		on_tweets_received( tweets );
	}

}

void User_Stream::on_tweets_received( const std::list<Tweet*>& tweets ) {

	std::cout << "On TW" << std::endl;

}

void User_Stream::on_connection_closed( unsigned long response_code ) {

	std::cout << "Stream : Connection closed\n";

}

User_Stream::~User_Stream() {

}
