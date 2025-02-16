CXX = g++
CPPFLAGS += -I.
CXXFLAGS += -std=c++17 -O2 -MMD -MP
CXXFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

SOURCES = BigInt/src/big_int.cpp BigInt/tests/test_big_int.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: clean all
.DEFAULT_GOAL := all

all: testing

testing: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

clean: 
	@rm testing 2>/dev/null || true
	@find ./ -type f \( -name \*.d -o -name \*.o \) -delete
	@echo "Cleaned up object files and executable"

-include $(OBJECTS:.o=.d)

# check out https://codingnest.com/basic-makefiles/#fnref4
# MMD flag for compilation to output Make-compatible dependencies between files, into a .d file
# MP flag for headers
# $^ is (all dependencies)
# $< is first dependency
# $@ is target name
