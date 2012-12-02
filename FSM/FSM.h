/**
    Purpose: Implement a simple single level Finite State Machine (FSM)

    @author Roger Unwin
    @version 0.1 10-17-2012
**/


#ifndef FSM_H_
#define FSM_H_

#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include "SimpleThread.h"
#include <boost/unordered_map.hpp>
#include "State.h"
#include "log.h"

class FSM {
	private:
		typedef boost::unordered_map<std::string, State *> state_map;
		state_map states;

		State *current_state;

		void change_state(State * new_state) {
			current_state->StopWorker();
			current_state->onExit();
			current_state = new_state;
			current_state->onEnter();
			current_state->StartWorker();
		}

	public:
		FSM() {
			current_state = NULL; // switch to nullptr;
		}

		~FSM() {
			for (state_map::iterator it = states.begin(); it != states.end(); ++it) {
				LOG << "FSM::~FSM deleting " << it->first;
				State *s = it->second;
				if (s == current_state) {
					s->StopWorker();
					s->onExit();
				}
				delete s;
			}
		}

		void addState(State *s) {
			string sn = s->getName();
			LOG << "FSM::addState ADDING STATE NAME '" << sn << "'.";
			states[sn] = s;
		}

		void setCurrentState(State * s) {
			if (current_state != NULL) {
				current_state->StopWorker();
				current_state->onExit();
			}
			current_state = s;
			current_state->onEnter();
			current_state->StartWorker();
		}

		std::string getCurrentState() {
			if (current_state)
				return current_state->getName();
			else
				return "==UNITIALIZED==";
		}



		void transitionToState(string new_state_name) {
			LOG << "FSM::transitionToState(" << new_state_name << ")";

			State *new_state = states.at(new_state_name);
			LOG << "FSM::transitionToState NEW STATE = " << new_state->getName();

			if (new_state != NULL)
				change_state(new_state);
			else
				ERROR << "FSM::transitionToState NEW STATE NAME '" << new_state_name << "' NOT FOUND.";
			LOG << "FSM::transitionToState  EXITING ";
		}

		void executeCommand(string command) {
			LOG << "FSM::executeCommand CURRENT_STATE NOW " << current_state->getName();
			if (current_state->hasCommand(command)) {
				State *new_state = current_state->execute_command(command);
				change_state(new_state);
			} else {
				throw CommandNotFound("FSM::executeCommand(" + command + ") : Command Not Found");
			}
		}
};
#endif /* FSM_H_ */
