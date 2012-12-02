/*
 * Command.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef COMMAND_H_
#define COMMAND_H_


#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "../FSM_Exceptions.h"
#include "../FSM.h"
#include "../State.h"
#include "../log.h"

using namespace std;



class Autonomous : public State {
	private:
		int count;

	public:
		Autonomous() : State("Autonomous")  {
			count = 0;
		};

		void onEnter()  {
			LOG << "Autonomous::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Autonomous::DoWork - " << this->getName() << " COUNT = " << count++;
		}
};

class Guided : public State {
	private:
		int count;

	public:
		Guided() : State("Guided")  {
			count = 0;
		};

		void onEnter()  {
			LOG << "Guided::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Guided::DoWork - " << this->getName() << " COUNT = " << count++;
		}
};

FSM * init_command_state_fsm() {


	FSM* command_fsm = new FSM();

	State* Autonomous = new Autonomous();
	State* Guided = new Guided();

	command_fsm->addState(Autonomous);
	command_fsm->addState(Guided);;

	command_fsm->setCurrentState(Guided);
	return command_fsm;
}


#endif /* COMMAND_H_ */
