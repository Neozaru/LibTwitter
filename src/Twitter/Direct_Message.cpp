#include "Direct_Message.h"

namespace Twitter {

Direct_Message::Direct_Message( const Json::Value& root_node, Session* session ) 
: Parsable_Object(root_node), _session(session), _sender(NULL) , _receiver(NULL) {
	
	_json_root_node[""];

}

Direct_Message::Direct_Message( std::string title, std::string content, User* sender, User* receiver )
: _title(title), _content(content), _sender(sender), _receiver(receiver)  {

}



Direct_Message::~Direct_Message() {

}


}