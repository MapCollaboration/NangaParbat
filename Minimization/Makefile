
CXX = clang++

CXXFLAGS += -O3 -fPIC -Wunused -std=c++11

# LHAPDF
LHAPDFINCS = $(shell lhapdf-config --cppflags)
LHAPDFLIBS = $(shell lhapdf-config --ldflags)

# APFEL++
APFELPPINCS = $(shell apfelxx-config --cppflags)
APFELPPLIBS = $(shell apfelxx-config --ldflags)

# APFEL
APFELINCS = $(shell apfel-config --cppflags)
APFELLIBS = $(shell apfel-config --ldflags)

# ROOT
ROOTINCS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs) -lMinuit2

# Now set up the compiler and link flags and libs
CXXFLAGS += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(ROOTINCS)
LDFLAGS  += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(ROOTINCS)

CLIBS += $(LHAPDFLIBS) $(APFELLIBS) $(APFELPPLIBS) $(ROOTLIBS)

install : all
all : Minimization

Minimization: Minimization.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

.SUFFIXES : .cxx .o .f .c

.cxx.o:	 
	$(CXX) $(CXXFLAGS) -c $< 

.f.o:	 
	$(F77)  -c $< 

clean:
	rm -rf *.lo *.o *.la Minimization *~
