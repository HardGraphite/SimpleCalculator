CXX = g++
CFLAG = -g -Wall
AR = ar

INCDIR := ../inc
OBJDIR := ../out
BINDIR := ../bin

SRC = $(filter-out ./main.cc, $(wildcard ./*.cc))
OBJ = $(patsubst %.cc, $(OBJDIR)/%.o, $(notdir $(SRC)))

TARGET = calc

all: $(OBJ) main.cc
	$(AR) -crv $(BINDIR)/lib$(TARGET).a
	$(CXX) $(CFLAG) -I$(INCDIR) -o $(BINDIR)/$(TARGET) $^

PHONY: c
c: $(OBJ)

$(OBJDIR)/%.o: %.cc
	$(CXX) $(CFLAG) -I$(INCDIR) -c -o $@ $<

PHONY: clean
clean:
	rm $(OBJDIR)/*.o
