CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 

OBJS =		FSM_test.o

LIBS =          -L/usr/lib/ -lpthread -lboost_log -lboost_log_setup -lboost_date_time -lboost_filesystem -lboost_system -lboost_thread

TARGET =	FSM_test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

