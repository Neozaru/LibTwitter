#ifndef _H_DIRECT_MESSAGE_H_
	#define _H_DIRECT_MESSAGE_H_


#include <string>

#include "Parsable_Object.h"

namespace Twitter {
	
	class User;
	class Session;

	/**
	* \class DirectMessage
	* \brief Represents a Private Message, sent by an User to another following User.
	*/
	class Direct_Message : public Parsable_Object  {

	private:
		Direct_Message( const Json::Value& root_node, Session* session );

	public:
		Direct_Message( std::string title, std::string content, User* sender, User* receiver );
		~Direct_Message();

	private:

		Session* _session; // TODO check if unused

		const std::string _title;
		const std::string _content;
		User*	_sender;
		User*	_receiver;

	};

}


#endif