/*
 * Master.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef MASTER_H_
#define MASTER_H_

#include "../FSM_Exceptions.h"
#include "../State.h"

#include <iostream>
#include <ostream>
#include <string>
#include <map>

/*
 * MASTER STATE
 * ------------
 * DORMANT
 * OPERATIONAL
 * ACTIVE
 * DISABLED
 */

class Dormant : public State {
	private:
		int count;

	public:
		Dormant() : State("Dormant")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Operational : public State {
	private:
		int count;

	public:
		Operational() : State("Operational") {
			count = 0;
		};

		void onEnter ()  {
			std::cout << this->getName() << " Offline::onEnter " << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Active : public State {
	private:
		int count;

	public:
		Active() : State("Active") {
			count = 0;
		};

		void onEnter ()  {
			std::cout << this->getName() << " Offline::onEnter " << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Disabled : public State {
	private:
		int count;

	public:
		Disabled() : State("Disabled") {
			count = 0;
		};

		void onEnter ()  {
			std::cout << this->getName() << " Offline::onEnter " << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};


FSM * init_master_state_fsm() {


	FSM* master_fsm = new FSM();

	State* Dormant = new Dormant();
	State* Operational = new Operational();
	State* Active = new Active();
	State* Disabled = new Disabled();

	master_fsm->addState(Dormant);
	master_fsm->addState(Operational);
	master_fsm->addState(Active);
	master_fsm->addState(Disabled);

	master_fsm->setCurrentState(Disabled);
	return master_fsm;
}

#endif /* MASTER_H_ */
