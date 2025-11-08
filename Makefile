CXX      := g++
CXXFLAGS := -std=c++20 -g -Wall -Wextra

SRCDIR   := src
SOURCES  := $(wildcard $(SRCDIR)/*.cc)
OBJECTS  := $(patsubst $(SRCDIR)/%.cc,$(SRCDIR)/%.o,$(SOURCES))

TARGET   := cc3k

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
