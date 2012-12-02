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
#include "../log.h"
using namespace std;

class Unknown : public State {
	private:
		int count;

	public:
		Unknown() : State("Unknown")  {
			count = 0;
		};

		void onEnter()  {
			LOG << "Unknown::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Unknown::DoWork - " << this->getName() << " COUNT = " << count++;
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
			LOG << "Operational::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Operational::DoWork - " << this->getName() << " COUNT = " << count++;
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
			LOG << "Impaired::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Impaired::DoWork - " << this->getName() << " COUNT = " << count++;
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
			LOG << "Nonfunctional::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Nonfunctional::DoWork - " << this->getName() << " COUNT = " << count++;
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
			LOG << "Imaging::onEnter - " << this->getName();
		}

		void DoWork() {
			LOG << "Imaging::DoWork - " << this->getName() << " COUNT = " << count++;
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
