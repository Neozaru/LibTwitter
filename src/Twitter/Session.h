#ifndef H_TWITTER_SESSION_H_
	#define H_TWITTER_SESSION_H_

#include <Twitter/Core/TwitterSession.h>
#include <Twitter/Core/TwitterRequest.h>

#include <string>


#include "JSON_Parser.h"
#include "User.h"


namespace Twitter {

	class Session : public TwitterSession {
	public:
		Session();

		bool connect( const std::string& username, const std::string& password );

		~Session() ;

		User* get_myself();

		Tweet* get_tweet( const std::string& tweet_id );


	private:
		//TwitterSession* _tc_session;

	};

}

#endif