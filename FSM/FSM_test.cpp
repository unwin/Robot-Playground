/**
    Purpose: Implement a simple single level Finite State Machine (FSM)

    @author Roger Unwin
    @version 0.1 10-17-2012
**/

#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "FSM.h"

using namespace std;

class Online : public State {
	private:
	public:
		Online() : State() {

		};
		Online(std::string n) : State(n) {

		};

		void onEnter ()  {
			std::cout << this->getName() << " Online::onEnter" << std::endl;
		}
};

class Offline : public State {
	private:

	public:
		Offline() : State() {

		};
		Offline(std::string n) : State(n) {

		};
		void onEnter ()  {
			std::cout << this->getName() << " Offline::onEnter" << std::endl;
		}
};

int main()
{

	State* online = new Online ("<<Online State>>");
	State* offline = new Offline ("<<Offline State>>");

	online->add_transition("logout", offline);
	offline->add_transition("login", online);

	FSM* f = new FSM();
	std::cout << f->getCurrentState()<< std::endl;

	f->addState(online);
	f->addState(offline);
	std::cout << f->getCurrentState()<< std::endl;
	f->setCurrentState(online);

	f->executeCommand("logout");
	f->executeCommand("login");

	std::cout << f->getCurrentState()<< std::endl;
	f->traansitionToState("<<Offline State>>");
	std::cout << f->getCurrentState()<< std::endl;
	return 0;
}
