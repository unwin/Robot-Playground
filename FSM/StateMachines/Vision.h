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
#include "opencv2/opencv.hpp"

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
		cv::VideoCapture *cap;
		cv::Mat edges;
		cv::Mat *frame;

	public:
		Imaging() : State("Imaging")  {
			count = 0;
			cap = NULL;
			frame = NULL;
		};

		~Imaging() : State("Imaging")  {
			if (cap->isOpened())
				cap->release();
				cap = NULL;
			if (frame != NULL)
				frame = NULL;
		};

		void onEnter()  {
			LOG << "Imaging::onEnter - " << this->getName();

			cap = new cv::VideoCapture(0);
			if (!cap->isOpened())
				cap = NULL;
			cv::namedWindow("Imaging",1);
		}

		void DoWork() {
			LOG << "Imaging::DoWork - " << this->getName() << " COUNT = " << count++;
			frame = new cv::Mat();
			cap->read(*frame);
			cv::imshow("Imaging", *frame);
			cv::cvtColor(*frame, edges, CV_BGR2GRAY);
			GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
			Canny(edges, edges, 0, 30, 3);
			cv::imshow("Imaging", edges);

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
