


#ifndef SIMPLE_THREAD_H_
#define SIMPLE_THREAD_H_

#include "FSM_Exceptions.h"
#include <pthread.h>

#include "log.h"

using namespace std;

#define nullptr 0
class SimpleThread {
	// stolen from http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
public:
	SimpleThread() {
		run = false;
		worker_thread = nullptr;
		this->run_interval = 1000000;
	};

	void SetRunInterval(int interval) {
		this->run_interval = interval;
	};

	SimpleThread(int run_interval) {
		run = false;
		worker_thread = nullptr;
		this->run_interval = run_interval;
	}

	virtual ~SimpleThread() {

	};

	bool StartWorker() {
		return (pthread_create(&worker_thread, NULL, ThreadEntryFunc, this) == 0);
	}

   void StopWorker() {
	   run = false;
	   (void) pthread_join(worker_thread, NULL);

	   LOG << "SimpleThread::StopWorker - thread stopped.";
   }


protected:
   void ThreadEntry() {
	   run = true;
	   while (this->run) {
		   try {
			   DoWork();
		   } catch( NotImplemented &E ) {
			   ERROR << "GOT EXCEPTION = " << E.what();
		   }
		   usleep(this->run_interval);
	   }
   }

   virtual void DoWork() {
	   throw NotImplemented("DoWork - Not Implemented");
   }

private:
   pthread_t worker_thread;
   bool run;
   int run_interval;

   static void * ThreadEntryFunc(void * This) {
	   ((SimpleThread *)This)->ThreadEntry();
	   return NULL;
   }
};

#endif /* SIMPLE_THREAD_H_ */
