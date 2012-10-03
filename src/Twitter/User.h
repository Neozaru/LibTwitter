#ifndef H_TWITTER_USER_H
	#define H_TWITTER_USER_H

#include <iostream>
#include <string>

#include "Parsable_Object.h"

#include <list>


namespace Twitter {

	class Session;
	class Tweet;

	/**
	* \class User
	* \brief Represents a Twitter User, including his information
	*
	*/
	class User : public Parsable_Object {

	private:
		User( const Json::Value& root_node, Session* session );

	public:
		User( bool valid = false ) : Parsable_Object(valid) {}
		~User();


		static User* from_JSON( const Json::Value& root_node, Session* session  = NULL ) {
			return new User( root_node, session );
		}

		/**
		* \fn get_id
		*
		*/
		const std::string& get_id();
		
		/**
		* \fn get_screen_name
		* \brief Gets screen name (pseudo) of the user
		*
		* \return A string containing screen name of this User.
		*/
		const std::string& get_screen_name();

		/**
		* \fn get_description
		* \brief Gets user description
		*
		* \return A string containing user description
		*
		*/
		const std::string& get_description();

		/**
		* \fn get_creation_date
		* \brief Gets user registration data
		*
		* \return A time_t object containing user creation date
		*/
		const time_t& get_creation_date();

		/**
		* \fn get_status
		* \brief Returns last user status/tweet
		*
		* \return The Tweet object representing current user status
		*
		*/
		Tweet* get_status();

		/**
		* \fn get_tweets
		* \brief Returns a list of Tweet posted by this user
		*
		* \param count Max number of Tweets to return
		* \param include_entities true
		* \param include_replies If true, function returned Tweets will include replies
		*
		* \return A list of Tweets posted by this User.
		*/
		const std::list<Tweet*>&  get_tweets( int count = 20, bool include_retweets = true, bool include_replies = true );

		void request_full_info( bool force = false );


		const std::string& to_string();


		void to_stream( std::ostream& stream ) const;


		bool follow();
		bool unfollow();

	private:

		const Json::Value& _get_value( const std::string& value );

		bool _set_following( bool follow );

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