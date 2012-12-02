/**
    Purpose: Implement a simple single level Finite State Machine (FSM)

    @author Roger Unwin
    @version 0.1 10-17-2012
**/

#include <iostream>
#include <ostream>
#include <string>
#include <map>

// http://boost-log.sourceforge.net/libs/log/doc/html/index.html




#include "FSM_Exceptions.h"
#include "FSM.h"
#include "State.h"

#include "StateMachines/Problem.h"
using namespace std;

#include "log.h"


class Online : public State {
	private:
		int count;

	public:
		Online() : State("Online")  {
			count = 0;
		};

		void onEnter()  {
			LOG << "Online::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Online::DoWork - " << this->getName() << " COUNT = " << count++;
		}


};

class Offline : public State{
	private:
		int count;

	public:
		Offline() : State("Offline") {
			count = 0;
		};

		void onEnter()  {
			LOG << "Offline::onEnter - " << this->getName();
		}

		void onExit()  {
			count = 0;
		}

		void DoWork() {
			LOG << "Offline::DoWork - " << this->getName() << " COUNT = " << count++;
		}
};



/*
 * Hierarchical Finite State Machine Experiment
 * Need to come up with a test for this...
 */
class HFSM : public State, public FSM {
	private:

	public:
		HFSM() : State(), FSM() {

		};

		HFSM(std::string n) : State(n), FSM(){

		};

		void onEnter ()  {
			std::cout << this->getName() << " HFSM::onEnter " << std::endl;
		}
};

void foo() {

	FSM *fsm = init_problem_fsm();

	State* online = new Online();
	State* offline = new Offline();
	sleep(2);
	online->add_transition("logout", offline);
	sleep(2);
	offline->add_transition("login", online);
	sleep(2);

	FSM* f = new FSM();


	LOG << "FSM_test " << "CURRENT STATE: " << f->getCurrentState();
	sleep(2);
	f->addState(online);
	sleep(2);
	f->addState(offline);
	sleep(2);

	LOG << "FSM_test " << "CURRENT STATE: " << f->getCurrentState();
	sleep(2);
	f->setCurrentState(online);
	sleep(2);
	f->executeCommand("logout");
	sleep(2);
	f->executeCommand("login");
	sleep(2);
	f->executeCommand("logout");
	sleep(2);
	f->executeCommand("login");
	sleep(2);

	LOG << "FSM_test " << "CURRENT STATE: " << f->getCurrentState();
	sleep(2);
	f->transitionToState(offline->getName());
	sleep(2);

	LOG << "FSM_test " << "CURRENT STATE: " << f->getCurrentState();
	sleep(2);

	LOG << "delete fsm";
	delete fsm;
	LOG << "delete f";
	delete f;
	LOG << "FSM_test " << "EXITING";
	sleep(2);
}

int main()
{
	init_logging();

	LOG << "A normal severity message, will not pass to the file";
	NOTIFICATION << "A notification severity message, will not pass to the file";
	WARN << "A warning severity message, will pass to the file";
	ERROR << "An error severity message, will pass to the file";
	CRITICAL << "A critical severity message, will pass to the file";

	try {
		foo();
	} catch( int &E ) {
		ERROR << "0 GOT EXCEPTION = " << E;
	} catch( NotImplemented &e) {
		ERROR << "1 GOT EXCEPTION = " << e.what();
	} catch( exception& e ) {
		ERROR << "2 GOT EXCEPTION = " << e.what();
	}

	return 0;
}
