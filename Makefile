CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		src/main.o src/custom_malloc.o

LIBS =

TARGET =	main

$(TARGET):	$(OBJS)
	gcc -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
