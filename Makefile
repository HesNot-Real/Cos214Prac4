
CXX      := g++
SUBDIRS  := 
INC_FLAGS := $(addprefix -Isrc/, $(SUBDIRS))
CXXFLAGS  := -Wall -Wextra -std=c++11 -I. -Isrc $(INC_FLAGS)
TARGET   := taskforge
TARGETTEST   := $(addprefix $(TARGET), test)


SRCS := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
HEADERS := $(wildcard src/**/*.h) $(wildcard src/*.h)
PDFS := 

ZIP_NAME=prac.zip


	

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TARGETTEST)
	$(CXX) $(CXXFLAGS) $(SRCS) -g -o $@
$(TARGETTEST):
	$(CXX) $(CXXFLAGS) $(SRCS) -g -o $@
	
runtest:
	gdb ./$(TARGETTEST)


zip:
	zip -j $(ZIP_NAME) $(SRCS) $(HEADERS) $(PDFS) Makefile 



val:
	valgrind --leak-check=full $(TARGET)

clean:
	rm -f $(TARGET) $(TARGETTEST) $(ZIP_NAME)
