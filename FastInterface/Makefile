
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

# YAML
YAMLINCS = -I/usr/local/include
YAMLLIBS = -L/usr/local/lib -lyaml-cpp

# Now set up the compiler and link flags and libs
CXXFLAGS += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(YAMLINCS)
LDFLAGS  += $(LHAPDFINCS) $(APFELINCS) $(APFELPPINCS) $(YAMLINCS)

CLIBS += $(LHAPDFLIBS) $(APFELLIBS) $(APFELPPLIBS) $(YAMLLIBS)

install : all
all : CreateTable

CreateTable: CreateTable.o
	$(CXX) $(LDFLAGS) -o $@ $< $(CLIBS)

clean:
	rm -rf *.lo *.o *.la CreateTable *~

