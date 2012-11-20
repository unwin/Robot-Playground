/**
    Purpose: Implement a simple single level Finite State Machine (FSM)

    @author Roger Unwin
    @version 0.1 10-17-2012
**/

#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "FSM_Exceptions.h"
#include "FSM.h"
#include "State.h"

#include "StateMachines/Problem.h"
using namespace std;



class Online : public State {
	private:
		int count;

	public:
		Online() : State("Online")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
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

			std::cout << "**" << this->getName() << "::onEnter() " << std::endl;
		}

		void onExit()  {
			count = 0;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
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



int foo() {

	FSM *fsm = init_problem_fsm();

	State* online = new Online();
	State* offline = new Offline();
	sleep(2);
	online->add_transition("logout", offline);
	sleep(2);
	offline->add_transition("login", online);
	sleep(2);

	FSM* f = new FSM();

	std::cout << "CURRENT STATE: " << f->getCurrentState()<< std::endl;
	sleep(2);
	f->addState(online);
	sleep(2);
	f->addState(offline);
	sleep(2);
	std::cout << "CURRENT STATE: " << f->getCurrentState()<< std::endl;
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
	std::cout << "CURRENT STATE: " << f->getCurrentState()<< std::endl;
	sleep(2);
	f->transitionToState(offline->getName());
	sleep(2);
	std::cout << "CURRENT STATE: " << f->getCurrentState()<< std::endl;
	sleep(2);
	std::cout << "EXITING" << std::endl;
	sleep(2);
	return 0;
}




int main()
{

	try {
		foo();
	} catch( int &E ) {
		std::cout << "0 GOT EXCEPTION = " << E << std::endl;
	} catch( NotImplemented &e) {
		std::cout << "1 GOT EXCEPTION = " << e.what()  << std::endl;
	} catch( exception& e ) {
		std::cout << "2 GOT EXCEPTION = " << e.what()  << std::endl;
	}
}
