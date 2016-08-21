GPP=g++
OPTS=-Wall -pedantic -std=c++11
LIBS=-lstdc++
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

APPFILE=calculator

TESTRUNNER=runtest.sh

all: $(APPFILE)

$(APPFILE): $(OBJECTS)
	$(GPP) $(LIBS) -o $@ $^

.cpp.o:
	$(GPP) -c $(OPTS) $<

clean:
	rm -f $(APPFILE) $(OBJECTS)

install:
	cp $(APPFILE) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(APPFILE)

tests:
	./$(TESTRUNNER)

tests-verbose:
	./$(TESTRUNNER)	-v
