/*
 * Vision.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef VISION_H_
#define VISION_H_

#include <iostream>
#include <ostream>
#include <string>
#include <map>

#include "../FSM_Exceptions.h"
#include "../FSM.h"
#include "../State.h"
using namespace std;

class Unknown : public State {
	private:
		int count;

	public:
		Unknown() : State("Unknown")  {
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
		Operational() : State("Operational")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Impaired : public State {
	private:
		int count;

	public:
		Impaired() : State("Impaired")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Nonfunctional : public State {
	private:
		int count;

	public:
		Nonfunctional() : State("Nonfunctional")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};

class Imaging : public State {

	private:
		int count;

	public:
		Imaging() : State("Imaging")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		}

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		}
};


FSM * init_vision_fsm() {


	FSM* vision_fsm = new FSM();

	State* Unknown = new Unknown();
	State* Operational = new Operational();
	State* Impaired = new Impaired();
	State* Nonfunctional = new Nonfunctional();
	State* Imaging = new Imaging();

	vision_fsm->addState(Operational);
	vision_fsm->addState(Impaired);
	vision_fsm->addState(Nonfunctional);
	vision_fsm->addState(Imaging);

	vision_fsm->setCurrentState(Unknown);
	return vision_fsm;
}

#endif /* VISION_H_ */
