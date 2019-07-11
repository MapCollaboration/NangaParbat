#LIBPATH =  -L/sw/lib -L/usr/local/lib
LIB = -lmathlib -lpacklib -lkernlib -lLHAPDF -lAPFEL
#LIB = -lLHAPDF -lAPFEL
LIBPATH =  -L/usr/local/lib
COMP = gfortran
FFLAGS = -O3
RUNFLAGS = -ffixed-line-length-none -cpp -fbacktrace -fcheck=all
DEBUGFLAGS = -g -Wall -Wextra -Wsurprising -Walign-commons -ffpe-trap=zero,invalid,overflow,underflow
SOURCE = comvar.f90 LeptonCutsDY.f90 integrands.f gridmaker.f fit.f norm.f90 kernel.f bin.f90 reading.f chisquare.f fragmentation.f utilities.f wilsonCoeff.f minuit/*.f cernlib/*.F


fit:
	$(COMP) $(SOURCE) $(FFLAGS) $(LIBPATH) $(LIB) -o fit.exe
	rm -rf fit.dSYM

grid:
	$(COMP) comvar.f90  LeptonCutsDY.f90 integrands.f kernel.f bin.f90 reading.f fragmentation.f utilities.f wilsonCoeff.f gridmaker.f maingrid.f $(FFLAGS) $(LIBPATH) $(LIB) -o makegrids.exe

denom:
	$(COMP) comvar.f90 bin.f90 reading.f denommaker.f $(FFLAGS) $(LIBPATH) $(LIB) -o makedenom.exe

clean:
	-rm fit.exe
	-rm *mod
	-rm *.out
	-rm fort.*
