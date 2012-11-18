#include <pthread.h>
#include "FSM_Exceptions.h"

using namespace std;

class SimpleThread {
	// stolen from http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
public:
	SimpleThread() {
		run = false;
		worker_thread = NULL;
		this->run_interval = 1000000;
	}

	SimpleThread(int run_interval) {
			run = false;
			worker_thread = NULL;
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
	   std::cout << " StopWorker - thread stopped. " << std::endl;
   }


protected:
   void ThreadEntry() {
	   run = true;
	   while (this->run) {
		   try {
			   DoWork();
		   } catch( NotImplemented &E ) {
			   std::cout << "GOT EXCEPTION = " << E.what() << std::endl;
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

