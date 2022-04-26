CC			= g++
CFLAGS	= -O2 -g -MMD
LDFLAGS	= -lSDL2 -lGLU -lGL -lm
SRC = opengl.cpp basics.cpp Character.cpp Menu.cpp Level.cpp

opengl : $(SRC:%.cpp=%.o)
	$(CC) $^ -o $@ $(LDFLAGS) $(CFLAGS)

opengl.o : opengl.cpp
	$(CC) -c $< $(LDFLAGS) $(CFLAGS)

%.o : %.cpp %.h
	$(CC) -c $< $(LDFLAGS) $(CFLAGS)

clean :
	rm *.o
	rm *.d

-include $(SRC:%.cpp=%.d)