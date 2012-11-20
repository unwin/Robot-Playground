/*
 * Communication.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "../FSM_Exceptions.h"
#include "../FSM.h"
#include "../State.h"

using namespace std;



class Connected : public State {
	private:
		int count;

	public:
		Connected() : State("Connected")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Disconnected : public State {
	private:
		int count;

	public:
		Disconnected() : State("Disconnected")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

FSM * init_communication_state_fsm() {


	FSM* communication_fsm = new FSM();

	State* Connected = new Connected();
	State* Disconnected = new Disconnected();

	communication_fsm->addState(Connected);
	communication_fsm->addState(Disconnected);;

	communication_fsm->setCurrentState(Disconnected);
	return communication_fsm;
}

#endif /* COMMUNICATION_H_ */
