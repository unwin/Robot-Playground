CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 

OBJS =		FSM_test.o

LIBS =

TARGET =	FSM_test

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
