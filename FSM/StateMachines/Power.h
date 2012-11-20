/*
 * Power.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef POWER_H_
#define POWER_H_

#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "../FSM_Exceptions.h"
#include "../FSM.h"
#include "../State.h"

using namespace std;



class Powering_On : public State {
	private:
		int count;

	public:
		Powering_On() : State("Powering_On")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Self_Test : public State {
	private:
		int count;

	public:
		Self_Test() : State("Self_Test")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Powering_Off : public State {
	private:
		int count;

	public:
		Powering_Off() : State("Powering_Off")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Power_Seeking : public State {
	private:
		int count;

	public:
		Power_Seeking() : State("Power_Seeking")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Power_Docking : public State {
	private:
		int count;

	public:
		Power_Docking() : State("Power_Docking")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Charging : public State {
	private:
		int count;

	public:
		Charging() : State("Charging")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Power_Undocking : public State {
	private:
		int count;

	public:
		Power_Undocking() : State("Power_Undocking")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

FSM * init_power_state_fsm() {


	FSM* power_fsm = new FSM();

	State* Dormant = new Dormant();
	State* Self_Test = new Self_Test();
	State* Powering_Off = new Powering_Off();
	State* Power_Seeking = new Power_Seeking();
	State* Power_Docking = new Power_Docking();
	State* Charging = new Charging();
	State* Power_Undocking = new Power_Undocking();

	power_fsm->addState(Dormant);
	power_fsm->addState(Self_Test);
	power_fsm->addState(Powering_Off);
	power_fsm->addState(Power_Seeking);
	power_fsm->addState(Power_Docking);
	power_fsm->addState(Charging);
	power_fsm->addState(Power_Undocking);

	power_fsm->setCurrentState(Dormant);
	return power_fsm;
}

#endif /* POWER_H_ */
