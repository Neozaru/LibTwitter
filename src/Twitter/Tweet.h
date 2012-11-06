#ifndef H_TWITTER_TWEET_H
	#define H_TWITTER_TWEET_H

#include <list>
#include <string>

#include "Parsable_Object.h"

#include <iostream>

//class TwitterSession;

namespace Twitter {

	class User;
	class Session;

	/**
	* \class Tweet
	* \brief Represents a Twitter Tweet
	*
	*/
	class Tweet : public Parsable_Object {
	private:

		Tweet( const Json::Value& root_node, Session* session );

	public:

		/**
		* \fn Tweet
		* \brief Instanciates an invalid Tweet
		*
		*/
		Tweet( bool valid = false ) : Parsable_Object(valid) { std::cout << "Inv" << std::endl; }
		
		/**
		*
		*/
		~Tweet();

		/**
		* \fn get_retweet_count
		* \brief Gets count of retweets of this Tweet.
		*
		* \return Count of retweets of this Tweet.
		*/
		int get_retweet_count();

		/**
		* \fn get_text
		* \brief Gets text content of this Tweet.
		*
		* \return A string containing all text of the Tweet.
		*
		*/
		const std::string& get_text();

		/**
		* \fn get_id
		* \brief Gets id of this Tweet
		*
		* \return String containing id number of this Tweet
		*
		*/
		const std::string& get_id();

		/**
		* \fn retweet
		* \brief Retweets this Tweet
		* A retweet is a copy of a Tweet, containing name of original author.
		*
		* \return true, if Tweet was successfully retweeted, false otherwise
		*
		*/
		bool retweet();
		
		/**
		* \fn reply
		* \param response Text string containing Tweet reponse
		* \param media_paths List containing file path of media/images to send with reply
		*
		* \return true if response was Tweeted successfully, false otherwise
		*
		*
		*/
		bool reply( const std::string& response, const std::list<std::string>& media_paths = std::list<std::string>(0) );


		/**
		* \fn favorite
		* \brief Sets this Tweet as favorite
		*
		* \return true if Tweet was successfully favorited, false otherwise
		*/
		bool favorite();
		

		/**
		* \fn favorite
		* \brief Unset this Tweet as favorite
		*
		* \return true if Tweet was successfully unfavorited, false otherwise
		*/
		bool unfavorite();


		/**/
		bool set_sender( User* sender );


		static Tweet* from_JSON( Json::Value root_node, Session* session ) {
			return new Tweet( root_node, session );
		}

		static std::list<Tweet*> list_from_JSON( Json::Value root_node, Session* session ) {

			std::list<Tweet*> tweets;

			for ( int i = 0; i < root_node.size(); ++i ) {
			   
				Tweet* tw = new Tweet( root_node[i], session );
				if ( tw != NULL ) {
					//tw->set_sender( session->get_myself() );
					tweets.push_back(tw);
				}

			}

			return tweets;
		}

		void to_stream( std::ostream& stream ) const;

	private:

		Session* _session;

		std::string _id;
		std::string _text;

		int _retweet_count;

		User* _sender;
		User* _original_author;

		std::list<User*> _contributors;

		bool _set_favorite( bool favorite );


	};



}

	static std::ostream& operator<<( std::ostream& stream, Twitter::Tweet const& tweet ) {
		tweet.to_stream(stream);
		return stream;
	}

#endif