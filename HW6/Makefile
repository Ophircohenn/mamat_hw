CXX     = g++
CXXFLAGS = -Wall -g -std=c++11
OBJS   = field.o port.o ip.o string.o
EXEC   = firewall.exe

$(EXEC): main.o libfirewall.so libinput.so
	$(CXX) $(CXXFLAGS) main.o -o $(EXEC) -lfirewall -linput -L.

libfirewall.so: ip.o port.o field.o string.o
	$(CXX) $(CXXFLAGS) -shared $(OBJS) -o libfirewall.so -L.	

main.o: main.cpp libfirewall.so input.h 
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

port.o: ip.h port.cpp string.h field.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

ip.o: ip.h ip.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

clean:
	rm -fr $(EXEC) *.o libfirewall.so 