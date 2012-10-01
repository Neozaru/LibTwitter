#ifndef H_INFORMATION_MANAGER_H
	#define H_INFORMATION_MANAGER_H


#include <map>
#include <string>


class Twitter::User;
class Twitter::Tweet;


class Information_Manager {

private:
	Information_Manager() {}
	~Information_Manager() {}

public:
	static Information_Manager* get_information_manager() {

		if ( _manager == NULL ) {
			_manager = new Information_Manager();
		}

		return _manager;
	}

	void add_user( Twitter::User* user );
	void add_tweet( Twitter::Tweet* tweet );

protected:

	static Information_Manager* _manager;

	std::map< const std::string, Twitter::User* >  _users;
	std::map< const std::string, Twitter::Tweet* > _tweets;

};


#endif