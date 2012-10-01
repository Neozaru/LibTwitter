#ifndef H_TWITTER_USER_H
	#define H_TWITTER_USER_H

#include <iostream>
#include <string>

#include "Parsable_Object.h"

#include <list>


namespace Twitter {

	class Session;
	class Tweet;

	class User : public Parsable_Object {

	private:
		User( const Json::Value& root_node, Session* session );

	public:
		User( bool valid = false ) : Parsable_Object(valid) {}
		~User();


		static User* from_JSON( const Json::Value& root_node, Session* session  = NULL ) {
			return new User( root_node, session );
		}

		const std::string& get_id();
		const std::string& get_screen_name();
		const std::string& get_description();

		const time_t& get_creation_date();

		Tweet* get_status();
		const std::list<Tweet*>&  get_tweets( int count = 20, bool include_retweets = true, bool include_replies = true );

		void request_full_info( bool force = false );


		const std::string& to_string();


		void to_stream( std::ostream& stream ) const;

	private:

		const Json::Value& _get_value( const std::string& value );

		bool _auto_load;
		bool _fully_loaded;

		std::string _id;
		std::string _screen_name;

		std::string _description;

		time_t _creation_date;

		Tweet* _status;
		std::list<Tweet*> _timeline;

		Session* _session;
	
	};


}

	static std::ostream& operator<<( std::ostream& stream, Twitter::User const& user ) {
		user.to_stream(stream);
		return stream;
	}

#endif