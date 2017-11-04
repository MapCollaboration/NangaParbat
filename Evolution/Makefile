
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

# Now set up the compiler and link flags and libs
CXXFLAGS += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS)
LDFLAGS  += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS)

CLIBS += $(LHAPDFLIBS) $(APFELLIBS) $(APFELPPLIBS)

install : all
all : TestMatchingFunctions Benchmark CrossSection J0ZerosGenerator NWA TestCode

TestMatchingFunctions: TestMatchingFunctions.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

Benchmark: Benchmark.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

CrossSection: CrossSection.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

J0ZerosGenerator: J0ZerosGenerator.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

NWA: NWA.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

TestCode: TestCode.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

.SUFFIXES : .cxx .o .f .c

.cxx.o:	 
	$(CXX) $(CXXFLAGS) -c $< 

.f.o:	 
	$(F77)  -c $< 

clean:
	rm -rf *.lo *.o *.la TestMatchingFunctions Benchmark CrossSection J0ZerosGenerator NWA TestCode *~

