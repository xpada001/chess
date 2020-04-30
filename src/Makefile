CXXFLAGS = -g -std=c++14 -Wall

GRAPHICSFLAGS = -DGRAPHICS

SOURCEFILES = $(wildcard *.cc)

OBJS = $(SOURCEFILES:%.cc=%.o)

DEPENDS =   ${OBJECTS:.o=.d}

LIBS =

TARGET =	chess

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -lX11 -o $(TARGET) $(LIBS)
	
-include $(DEPENDS)

.PHONY: clean

all:	$(TARGET)

graphics:
	make CXXFLAGS="$(CXXFLAGS) $(GRAPHICSFLAGS)"

clean:
	rm -f $(OBJS) $(TARGET) ${DEPENDS}
