      program fit

      external chisquare

!      call gridmaker

      call gridreader

c     initial values of parameters and other configurations of Minuit
      open(unit=5,file='fit.input',form='formatted',status='old')

c     output of Minuit
      open(unit=6,file='fit.out')

c     temporary values of the parameters
      open(unit=7,file='parameters_save.out')

c     fit curves
      open(unit=8,file='curves.out')

c     generic error messages
      open(unit=9,file='errors.out')

c     covariance matrix
      open(unit=10,file='covmat.out')

c     final values of the parameters
      open(unit=11,file='parameters.out')

c     final result for chi2
      open(unit=12,file='chi2.out')

c     binning of data
      open(unit=14,file='binned.out')

!     normalization Values
      open(unit=25,file='normal.out')

c     test files
      open(unit=122,file='test.out')

c     theory predictions and selected data from experiments
      open(unit=22,file='predictions.out')
      open(unit=23,file='selected_data.out')
      open(unit=24,file='selected_data_replica.out')

      call mtlset('      ',12,255,255)
      call minuit(chisquare,0)

      close(unit=5)
      close(unit=6)
      close(unit=7)
      close(unit=8)
      close(unit=9)
      close(unit=10)
      close(unit=11)
      close(unit=12)
      close(unit=14)
      close(unit=122)
      close(unit=22)
      close(unit=23)

      stop
      end
