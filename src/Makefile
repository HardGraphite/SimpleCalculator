CXX = g++
CFLAG = -g -Wall
AR = ar

INCDIR := ../inc
OBJDIR := ../out
BINDIR := ../bin

SRC = $(filter-out ./main.cc, $(wildcard ./*.cc))
OBJ = $(patsubst %.cc, $(OBJDIR)/%.o, $(notdir $(SRC)))
OBJPIC = $(patsubst %.cc, $(OBJDIR)/%_pic.o, $(notdir $(SRC)))

TARGET = calc
TARGET_SL = lib$(TARGET).a
TARGET_DL = lib$(TARGET).so


all: $(BINDIR)/$(TARGET) $(BINDIR)/$(TARGET_SL) dl

PHONY: dl
dl: $(BINDIR)/$(TARGET_DL)

$(BINDIR)/$(TARGET): $(OBJ) ./main.cc
	$(CXX) $(CFLAG) -I$(INCDIR) -lreadline -o $@ $^

$(BINDIR)/$(TARGET_SL): $(OBJ)
	$(AR) -crv $@

$(BINDIR)/$(TARGET_DL): $(OBJPIC)
	$(CXX) $(CFLAG) -shared -o $@ $^

$(OBJDIR)/%.o: %.cc
	$(CXX) $(CFLAG) -I$(INCDIR) -c -o $@ $<

$(OBJDIR)/%_pic.o: %.cc
	$(CXX) $(CFLAG) -fPIC -I$(INCDIR) -c -o $@ $<

PHONY: clean
clean:
	rm $(OBJDIR)/*.o
