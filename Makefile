CXX	:= c++
CXXFLAGS := -Wall -std=c++20

# Contain path for any includes (headers)
# Depending on your platform: Include a path to boost, on linux should be
# /usr/local/include, on mac could be /opt/homebrew/include
INCLUDES := -I./include -I/msys64/mingw64/include

# Contains libraries we need to (-L is directory search path, -l is lib)
LDFLAGS = -L/usr/local/lib
LDLIBS = -lncurses

SRCDIR := ./src
BREAKOUT_OBJECTS := controller_console.o model_simulator_breakout.o observer.o view_console.o main.o model_ball.o model_border.o model_brick.o

breakout: $(BREAKOUT_OBJECTS)
	$(CXX) $^ -o $@ $(LDLIBS)

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $^ -o $@

clean:
	test ! -f breakout || rm breakout
	rm *.o
