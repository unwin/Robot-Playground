OBJS = test_i2c test_fsm test_gps test_vision test_main

DEBUG = -g

CFLAGS = -Wall -O2 -c #$(DEBUG) 

LFLAGS = -Wall #$(DEBUG)

LIBS        = -L/usr/lib/ -lpthread
BOOST_LIBS  = -lboost_log -lboost_log_setup -lboost_date_time -lboost_filesystem -lboost_system -lboost_thread
OPENCV_LIBS = -lopencv_video -lopencv_highgui -lopencv_core -lopencv_imgproc
TEST_LIBS   = -lboost_unit_test_framework 

all: $(OBJS)

test_i2c: ../i2c/i2c.o ../i2c/ADXL345.o ../i2c/DS1307.o test_i2c.cpp
	$(CXX) $(CFLAGS) test_i2c.cpp -o test_i2c $(LIBS) $(BOOST_LIBS) $(TEST_LIBS)
	
test_fsm: test_fsm.hpp
	$(CXX) $(CFLAGS) test_fsm.hpp -o test_fsm

test_gps: test_gps.hpp ../serial/GPS.o
	$(CXX) $(CFLAGS) test_gps.hpp -o test_gps

test_vision: test_vision.hpp
	$(CXX) $(CFLAGS) test_vision.hpp -o test_vision	
	
test_main: i2c.o test_main.hpp
	$(CXX) $(CFLAGS) test_main.hpp -o test_main

clean:
	rm -f $(OBJS) $(TARGET)
