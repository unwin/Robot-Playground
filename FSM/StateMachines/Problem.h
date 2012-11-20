/*
 * Problem.h
 *
 *  Created on: Nov 6, 2012
 *      Author: unwin
 */

#ifndef PROBLEM_H_
#define PROBLEM_H_

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
		};

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		};
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
		};

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		};
};

class Stuck : public State {
	private:
		int count;

	public:
		Stuck() : State("Stuck")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		};

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		};
};

class Blocked : public State {
	private:
		int count;

	public:
		Blocked() : State("Blocked")  {
			count = 0;
		};

		void onEnter()  {
			std::cout << "**" << this->getName() << "::onEnter()" << std::endl;
		};

		void DoWork() {
			std::cout << this->getName() <<"::DoWork() COUNT = " << count++ << std::endl;
		};
};

FSM * init_problem_fsm() {

	FSM* problem_fsm = new FSM();


	State * unknown = new Unknown();
	State * operational = new Operational();
	State * stuck = new Stuck();
	State * blocked = new Blocked();

	problem_fsm->addState(unknown);
	problem_fsm->addState(operational);
	problem_fsm->addState(stuck);
	problem_fsm->addState(blocked);

	problem_fsm->setCurrentState(unknown);
	return problem_fsm;
}


#endif /* PROBLEM_H_ */
