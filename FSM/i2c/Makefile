OBJS = ../log.o I2C_Exceptions.o i2c.o ADXL345.o DS1307.o test/test_i2c.o ../test/test_log.o

DEBUG = -g

CFLAGS = -Wall -O2 -c -g

LFLAGS = -Wall -g

LIBS = -L/usr/lib/ 

LIBS        = -L/usr/lib/ -lpthread
BOOST_LIBS  = -lboost_log -lboost_log_setup -lboost_date_time -lboost_filesystem -lboost_system -lboost_thread
OPENCV_LIBS = -lopencv_video -lopencv_highgui -lopencv_core -lopencv_imgproc
TEST_LIBS   = -lboost_unit_test_framework 

all: $(OBJS) test_i2c test_log

test_log: ../log.o ../test/test_log.o
	$(CXX) -o ../test/test_log $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o ../test/test_log.o
	
test_i2c: ../log.o I2C_Exceptions.o i2c.o ADXL345.o DS1307.o test/test_i2c.o 
	$(CXX) -o test_i2c $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o ADXL345.o DS1307.o test/test_i2c.o 

.cpp.o: $<
	$(CXX) $(CFLAGS) -o $@ $<

test_i2c.o: test_i2c.cpp 
	$(CXX) $(CFLAGS) test_i2c.cpp -o test_i2c.o

clean:
	rm -f $(OBJS) test_i2c ../test/test_log