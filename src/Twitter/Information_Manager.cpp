#include "Information_Manager.h"

using namespace Twitter;

void Information_Manager::add_user( User* user ) {


	if ( user != NULL ) {

		const std::string& id = user->get_id();
		if ( _users[id] == NULL ) {
			_users[id] = user;
		}



	}

	return;

}

void Information_Manager::add_tweet( Tweet* tweet ) {

}