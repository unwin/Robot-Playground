/**
    Purpose: Implement a simple single level Finite State Machine (FSM)

    @author Roger Unwin
    @version 0.1 10-17-2012
**/

#include <iostream>
#include <ostream>
#include <string>
#include <map>


using namespace std;

struct ltstr {
	 bool operator()(const string a, const string b) {
	       return a.compare( b );
	   }
};

class State
{
	private:
		std::string name;
		map<string, State *, ltstr> commands;
	public:
		State() {
			this->name = "<<UN-NAMED>>";
		};
		State(std::string name) {
			this->name = name;
		};
		virtual ~ State() {};
		virtual void onEnter ()  {  std::cout << this->getName() << " State::onEnter" << std::endl;  }
		virtual void onExit ()  {  std::cout << this->getName() << " State::onExit" << std::endl;  }
		virtual std::string getName ()  {  return this->name;  }
		virtual void add_transition(string command, State *new_state) {
			commands[command] = new_state;
		};
		virtual State * execute_command(std::string command) {
			State *s = commands[command];
			return(s);
		};
		virtual bool hasCommand(std::string command) {
			State *s = commands[command];
			std::cout << " in hasCommand seeking " << command<< std::endl;
			if (s)
				return true;
			else
				return false;
		};
};




class FSM {
	private:
		map<string, State *, ltstr> states;

		State *current_state;

	public:
		FSM() {
			this->current_state = NULL; // switch to nullptr;
		}
		void addState(State *s) {
			this->states[s->getName()] = s;
		}
		void setCurrentState(State * s) {
			this->current_state = s;
		}
		string getCurrentState() {
			if (this->current_state)
				return this->current_state->getName();
			else
				return "==UNITIALIZED==";
		}
		void traansitionToState(std::string state_name) {
			State * s = states[state_name];
			std::cout << s->getName() << " traansitionToState" << std::endl;
			current_state->onExit ();
			this->current_state = s;
			s->onEnter ();
			std::cout << " traansitionToState FROM " << current_state->getName() << " to " << state_name << std::endl;
		}

		void executeCommand(string command) {
			std::cout << " CURRENT_STATE NOW " << current_state->getName() << std::endl;
			if (current_state->hasCommand(command)) {
				std::cout << " YES IT HAS COMMAND " << command << std::endl;
				current_state->onExit ();current_state->onExit ();
				current_state = current_state->execute_command(command);
				current_state->onEnter ();
			} else {
				std::cout << " NO IT HAS NO COMMAND" << std::endl;
			}
			std::cout << " CURRENT_STATE NOW " << current_state->getName() << std::endl;
		}
};
