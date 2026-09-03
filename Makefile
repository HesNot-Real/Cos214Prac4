
CXX      := g++
SUBDIRS  := EventGroups EventUnits
INC_FLAGS := $(addprefix -Isrc/, $(SUBDIRS))
CXXFLAGS  := -Wall -Wextra -std=c++11 -I. -Isrc $(INC_FLAGS)
TARGET   := bin/eventFlow


SRCS := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
HEADERS := $(wildcard src/**/*.h) $(wildcard src/*.h)
PDFS := COS214_PA1.pdf

ZIP_NAME=prac.zip


	

all: $(TARGET)
	make run

$(TARGET): 
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@
	
	
$(TARGETTEST): 
	$(CXX) $(CXXFLAGSTEST) $(SRCS) -o $@

zip:
	zip -j $(ZIP_NAME) $(SRCS) $(HEADERS) $(PDFS) Makefile 


run: $(TARGET)
	./$(TARGET)

val:
	valgrind --leak-check=full $(TARGET)

clean:
	rm -f $(TARGET) $(ZIP_NAME)
