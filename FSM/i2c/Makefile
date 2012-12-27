OBJS = ../log.o ../test/test_log.o \
		I2C_Exceptions.o i2c.o test/test_i2c.o  \
		ADXL345.o test/test_ADXL345.o \
		DS1307.o test/test_DS1307.o \
		L3G4200D.o test/test_L3G4200D.o \
		J2004A.o test/test_J2004A.o

DEBUG = -g

CFLAGS = -Wall -O2 -c
CXX = g++
LFLAGS = -Wall

LIBS = -L/usr/lib/ 

LIBS        = -L/usr/lib/ -lpthread
BOOST_LIBS  = -lboost_log -lboost_log_setup -lboost_date_time -lboost_filesystem -lboost_system -lboost_thread
OPENCV_LIBS = -lopencv_video -lopencv_highgui -lopencv_core -lopencv_imgproc
TEST_LIBS   = -lboost_unit_test_framework 

all: $(OBJS) test_log test_i2c test_DS1307 test_ADXL345 test_L3G4200D test_J2004A
	

test_log: ../log.o ../test/test_log.o 
	$(CXX) -o test_log $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o ../test/test_log.o
		
test_i2c: ../log.o I2C_Exceptions.o i2c.o test/test_i2c.o 
	$(CXX) -o test_i2c $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o test/test_i2c.o 
	
test_DS1307: ../log.o I2C_Exceptions.o i2c.o DS1307.o test/test_DS1307.o 
	$(CXX) -o test_DS1307 $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o DS1307.o test/test_DS1307.o 
		
test_ADXL345: ../log.o I2C_Exceptions.o i2c.o ADXL345.o test/test_ADXL345.o 
	$(CXX) -o test_ADXL345 $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o ADXL345.o test/test_ADXL345.o 
		
test_L3G4200D: ../log.o I2C_Exceptions.o i2c.o L3G4200D.o test/test_L3G4200D.o 
	$(CXX) -o test_L3G4200D $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o L3G4200D.o test/test_L3G4200D.o 

test_J2004A: ../log.o I2C_Exceptions.o i2c.o J2004A.o test/test_J2004A.o 
	$(CXX) -o test_J2004A $(LIBS) $(BOOST_LIBS) $(TEST_LIBS) ../log.o I2C_Exceptions.o i2c.o J2004A.o test/test_J2004A.o 

.cpp.o: $<
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) ../test/test_log test/test_i2c test/test_DS1307 test/test_ADXL345 test/test_L3G4200D
