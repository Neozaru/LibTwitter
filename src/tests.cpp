#include "Twitter/User.h"
#include "Twitter/Tweet.h"

#include "Twitter/JSON_Parser.h"
#include "Twitter/Session.h"
#include "Twitter/User_Stream.h"


#include <iostream>
#include <fstream>

#include <cstdlib>

#include <ctime>
#include <list>

int main( int argc, char** argv ) {


	std::string username;
	std::string password;

	if ( argc > 2 ) {
		username = argv[1];
		password = argv[2];
	}
	else {
		std::cout << "Usage : " << argv[0] << " <username> <password" << std::endl;
		return -1;
	}

	Twitter::Session* session = new Twitter::Session();



	/* *** */
	/* Set consummer keys and secrets. */
	/* It corresponds to your own app key/secret */
	/* *** */

	session->get_oauth().set_consumer_key( "4wdGht7GCUYqMbLLsY8Yg" );
	session->get_oauth().set_consumer_secret( "DmPp6hteK6bgR4JiKLbOqSFPNT0r35QFAlbRGjR3E" );

	/*************************************/



	if ( session->connect(username,password) ) {
		std::cout << "Connected !" << std::endl;

		Twitter::User* me = session->get_myself();

		if ( me != NULL ) {

			std::cout << *me << std::endl;

			me->get_description();

			std::cout << *me << std::endl;

			const std::list<Twitter::Tweet*>& tws = me->get_tweets();
			std::list<Twitter::Tweet*>::const_iterator iterTw;

			for ( iterTw = tws.begin(); iterTw != tws.end(); iterTw++ ) {

				Twitter::Tweet* tw = *iterTw;
				std::cout << *tw <<  std::endl;

			}

		}



		Twitter::Tweet* tweet = session->get_tweet( "210462857140252672" );

		/*
		if ( tweet != NULL ) {
			
			std::cout << "TW = " << *tweet << std::endl;
			tweet->retweet();

		}
		*/

		Twitter::User_Stream* us = new Twitter::User_Stream( session );
		us->send();
	

	}
	else {
		std::cout << "Connection failed" << std::endl;
	}



	return 0;
}