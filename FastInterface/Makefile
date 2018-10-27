
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
all : CreateTable

CreateTable: CreateTable.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

clean:
	rm -rf *.lo *.o *.la CreateTable *~

