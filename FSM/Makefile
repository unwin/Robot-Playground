CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 

OBJS =		FSM_test.o

LIBS =          -L/usr/lib/ -lpthread -lboost_log -lboost_log_setup -lboost_date_time -lboost_filesystem -lboost_system -lboost_thread \
                -lopencv_video -lopencv_highgui -lopencv_core -lopencv_imgproc
TEST_LIBS = 	$(LIBS) -lboost_unit_test_framework -lpthread

TARGET =	FSM_test




$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	clean $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

test_vision:
	rm -f 
	$(CXX) tests/test_vision.cpp -o tests/test_vision  $(TEST_LIBS)
	./tests/test_vision

test_gps:
	rm -f 
	$(CXX) tests/test_gps.cpp -o tests/test_gps  $(TEST_LIBS)
	./tests/test_gps