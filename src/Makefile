.PHONY : clean

UNAME := $(shell uname)
ifeq ($(UNAME), Windows_NT)
	TARGET = mscdatagroups.dll
else
	CXX = clang++ 
	CPPFLAGS = -I../../libmot/src -O2 -std=c++11 -stdlib=libc++ #-Weverything
	TARGET = libmscdatagroups.so
endif

LDFLAGS= -shared -std=c++11 -stdlib=libc++ -L../../libmot -lmot

SOURCES = $(shell echo *.cpp)
HEADERS = $(shell echo *.h)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

clean:
	rm $(OBJECTS) $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CFLAGS) $(OBJECTS) -o ../$@ $(LDFLAGS)
