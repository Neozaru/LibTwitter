#ifndef H_USER_STREAM_H
	#define H_USER_STREAM_H

#include <Twitter/Core/TwitterRequest.h>
#include <Twitter/Core/TwitterSession.h>

#include "Session.h"

namespace Twitter {

	class User_Stream : public TwitterRequest {
	public:
		User_Stream( Session* session, bool followings = true, bool replies = true );
		User_Stream( Session* session, const std::string& keywords, bool followings = true, bool replies = true );

		~User_Stream();
		
	protected:

		virtual void on_tweets_received( const std::list<Tweet*>& tweets );
		virtual void on_connection_closed( unsigned long response_code );

	private:

		virtual void on_data_received( const std::string& data );


	};
}

#endif