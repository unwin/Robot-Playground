#ifndef State_H_
#define State_H_

using namespace std;

#include <iostream>
#include <ostream>
#include <string>
#include "SimpleThread.h"
#include "log.h"
#include <boost/unordered_map.hpp>

class State : public SimpleThread {
	private:
		typedef boost::unordered_map<std::string, State *> state_map;
		string name;
		state_map commands;

	public:
		State() : SimpleThread() {
			this->name = "UNDEFINED";
		};

		State(std::string name) : SimpleThread() {
			this->name = name;
			LOG <<  "State::State() name = " << name;
		};

		virtual ~State() {
		};

		virtual void onEnter()  {
			LOG << "State::onEnter - " << getName() ;
		}

		virtual void onExit()  {
			LOG << "State::onExit - " << getName();
		}

		virtual string getName()  {
			return this->name;
		}

		virtual void add_transition(string command, State *new_state) {
			commands[command] = new_state;
		};

		virtual State *execute_command(std::string command) {
			State *s = commands.at(command);
			return s;
		};

		virtual bool hasCommand(std::string command) {
			if (commands.at(command))
				return true;
			return false;
		};

		void InternalThreadEntry() {
			LOG << "State::InternalThreadEntry";
			usleep(10);
		}
};

#endif /* State_H_ */
