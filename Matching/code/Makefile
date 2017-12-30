
CXX = clang++

CXXFLAGS += -O3 -fPIC -std=c++11

# LHAPDF
LHAPDFINCS = $(shell lhapdf-config --cppflags)
LHAPDFLIBS = $(shell lhapdf-config --ldflags)

# APFEL++
APFELPPINCS = $(shell apfelxx-config --cppflags)
APFELPPLIBS = $(shell apfelxx-config --ldflags)

# APFEL
APFELINCS = $(shell apfel-config --cppflags)
APFELLIBS = $(shell apfel-config --ldflags)

# HOPPET
HOPPETINCS = $(shell hoppet-config --cxxflags)
HOPPETLIBS = $(shell hoppet-config --libs) -lgfortran

# QCDNUM
QCDNUMINCS = $(shell qcdnum-config --cppflags)
QCDNUMLIBS = $(shell qcdnum-config --ldflags)

# Now set up the compiler and link flags and libs
CXXFLAGS += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(HOPPETINCS) $(QCDNUMINCS)
LDFLAGS  += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(HOPPETLIBS) $(QCDNUMLIBS)

CLIBS += $(LHAPDFLIBS) $(APFELLIBS) $(APFELPPLIBS)

install : all
all : SIDIS

SIDIS: SIDIS.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

.SUFFIXES : .cxx .o .f .c

.cxx.o:	 
	$(CXX) $(CXXFLAGS) -c $< 

.f.o:	 
	$(F77)  -c $< 

clean:
	rm -rf *.lo *.o *.la SIDIS *~

