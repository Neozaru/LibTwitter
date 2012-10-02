#ifndef H_TWITTER_TWEET_H
	#define H_TWITTER_TWEET_H

#include <list>
#include <string>

#include "Parsable_Object.h"

#include <iostream>

class TwitterSession;

namespace Twitter {

	class User;

	class Tweet : public Parsable_Object {
	private:

		Tweet( const Json::Value& root_node, TwitterSession* session );

	public:
		Tweet( bool valid = false ) : Parsable_Object(valid) { std::cout << "Inv" << std::endl; }
		~Tweet();

		int get_retweet_count();
		const std::string& get_text();
		const std::string& get_id();

		bool retweet();
		
		bool reply( const std::string& response, const std::list<std::string>& media_paths = std::list<std::string>(0) );

		bool set_sender( User* sender );


		static Tweet* from_JSON( Json::Value root_node, TwitterSession* session ) {
			return new Tweet(root_node,session);
		}

		void to_stream( std::ostream& stream ) const;

	private:

		TwitterSession* _session;

		std::string _id;
		std::string _text;

		int _retweet_count;

		User* _sender;
		User* _original_author;

		std::list<User*> _contributors;

	};



}

	static std::ostream& operator<<( std::ostream& stream, Twitter::Tweet const& tweet ) {
		tweet.to_stream(stream);
		return stream;
	}

#endif