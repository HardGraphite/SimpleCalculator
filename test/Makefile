CXX = g++
CFLAG = -g -Wall

INCDIR := ../inc
OBJDIR := ../out

OBJS := $(filter-out $(OBJDIR)/main.o, $(wildcard $(OBJDIR)/*.o))

%: %.cc ../src/*.cc
	make -C ../src c
	$(CXX) $(CFLAG) -I$(INCDIR) -o $@ $< $(OBJS)
