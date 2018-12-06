#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_linalg.h>

using namespace std;

vector<string> read_directory(string const& name);
bool genArtSys(int const& ndata, double** C, double** artsys);
bool CholeskyDecomposition(int const& ndata, double** V, double** L);
bool SolveLowerSystem(int const& ndata, double** L, double* y, double* x);
bool SolveUpperSystem(int const& ndata, double** U, double* y, double* x);
bool SolveSymmetricSystem(int const& ndata, double** A, double* rho, double* lambda);

int main()
{
  // Data folder
  const string folder = "TestData/";

  // Get list od datafiles
  vector<string> filenames = read_directory(folder);

  // Print datafile
  cout << "\nData files:" << endl;
  for (auto const& f : filenames)
    cout << "- " << f << endl;
  cout << "\n";

  // Global counter
  double chi2tot = 0;
  int ntot       = 0;
  int icount     = 0;

  // Shift file
  ofstream shiftfile;
  shiftfile.open("shifts.txt");
  shiftfile << scientific;

  // Gnuplot file
  ofstream gpfile;
  gpfile.open("shifts.gp");
  gpfile << "set term postscript noenhanced color font 'Times-Roman,20'" << endl;
  gpfile << "set out 'shifts.eps'" << endl;
  gpfile << endl;
  gpfile << "set xlabel 'p_T [GeV]'" << endl;
  gpfile << endl;

  // Run over ino
  for(auto const& nf : filenames)
    {
      string dummy;
      // Read input file
      ifstream ifile (folder + nf);
      getline(ifile, dummy);
      int ndata;
      ifile >> ndata;
      double *y   = new double[ndata];
      double *x   = new double[ndata];
      double *m   = new double[ndata];
      double *t   = new double[ndata];
      double *ptl = new double[ndata];
      double *ptu = new double[ndata];
      double **U  = new double*[ndata];
      double **C  = new double*[ndata];
      double **V  = new double*[ndata];
      double **L  = new double*[ndata];
      double **artsys = new double*[ndata];
      for(int i = 0; i < ndata; i++)
	{
	  U[i] = new double[ndata];
	  C[i] = new double[ndata];
	  V[i] = new double[ndata];
	  L[i] = new double[ndata];
	  artsys[i] = new double[ndata];
	}

      // Read central values and predictions and construct deviations.
      getline(ifile, dummy);
      getline(ifile, dummy);
      for(int i = 0; i < ndata; i++)
	{
	  int dum;
	  double stdv;
	  ifile >> dum >> ptl[i] >> ptu[i] >> m[i] >> stdv >> t[i];
	  y[i] = m[i] - t[i];
	  U[i][i] = stdv * stdv;
	}

      // Read covariance matrix
      getline(ifile, dummy);
      getline(ifile, dummy);
      for(int i = 0; i < ndata; i++)
	for(int j = 0; j < ndata; j++)
	  {
	    int dum;
	    ifile >> dum >> dum >> V[i][j];
	    C[i][j] = V[i][j];
	    if (j == i)
	      C[i][j] -= U[i][i];
	    else
	      U[i][j] = 0;
	  }
      ifile.close();

      CholeskyDecomposition(ndata, V, L);

      SolveLowerSystem(ndata, L, y, x);

      // Compute chi2 per datapoint 
      double chi2 = 0;
      for(int i = 0; i < ndata; i++)
	chi2 += x[i] * x[i] / ndata;

      ntot += ndata;
      chi2tot += chi2 * ndata;

      cout << scientific;
      cout << nf << ": chi2 per data point = " << chi2 << endl;

      // Now generate articificial systematics and recompute chi2
      genArtSys(ndata, C, artsys);

      // Construct matrix A and vector rho
      double *rho    = new double[ndata];
      double *lambda = new double[ndata];
      double **A     = new double*[ndata];
      for(int alpha = 0; alpha < ndata; alpha++)
	{
	  A[alpha]  = new double[ndata];
	  rho[alpha] = 0;
	  for(int i = 0; i < ndata; i++)
	    rho[alpha] += y[i] * artsys[i][alpha] / U[i][i];

	  for(int beta = 0; beta < ndata; beta++)
	    {
	      A[alpha][beta] = 0;
	      for(int i = 0; i < ndata; i++)
		A[alpha][beta] += artsys[i][alpha] * artsys[i][beta] / U[i][i];

	      if(alpha == beta)
		A[alpha][beta] += 1;
	    }
	}

      // Solve A * lambda = rho to obtain the nuisance parameters
      SolveSymmetricSystem(ndata, A, rho, lambda);

      // Write gnuplot file
      int subset = 0;
      gpfile << "##########################################" << endl;
      gpfile << endl;
      gpfile << "set title '" << nf.substr(0, nf.size()-4) << " " << subset++ << "'" << endl;
      gpfile << "set ylabel 'Cross section'" << endl;
      gpfile << "plot [0:]\\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):4:5 index " << icount << " with yerrorbars pointtype 7 pointsize 1.0 lc rgb 'black' t 'Data', \\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):6   index " << icount << " w l linewidth 5.0 lc rgb 'red'  t 'Theory w/o shifts', \\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):7   index " << icount << " w l linewidth 5.0 lc rgb 'blue' t 'Theory w/ shifts'" << endl;
      gpfile << endl;
      gpfile << "set ylabel 'Theory / Data'" << endl;
      gpfile << "plot [0:]\\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):($4/$4):($5/$4) index " << icount << " with yerrorbars pointtype 7 pointsize 1.0 lc rgb 'black' notitle, \\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):($6/$4)         index " << icount << " w l linewidth 5.0 lc rgb 'red'  notitle, \\" << endl;
      gpfile << "     'shifts.txt' u (($3+$2)/2):($7/$4)         index " << icount << " w l linewidth 5.0 lc rgb 'blue' notitle" << endl;
      gpfile << endl;
      icount++;

      // Compute chi2 per datapoint using the shifts
      double chi2n = 0;
      double *shifts = new double[ndata];
      //shiftfile << nf << "\t\t" << ndata << endl;
      shiftfile << "# " << nf.substr(0, nf.size()-4) << endl;
      for(int i = 0; i < ndata; i++)
	{
	  shifts[i] = 0;
	  for(int alpha = 0; alpha < ndata; alpha++)
	    shifts[i] += lambda[alpha] * artsys[i][alpha];

	  chi2n += pow( ( y[i] - shifts[i] ), 2) / U[i][i];
	  if (i > 0 && ptl[i] < ptl[i-1])
	    {
	      shiftfile << endl;
	      shiftfile << endl;
	      gpfile << "set title '" << nf.substr(0, nf.size()-4) << " " << subset++ << "'" << endl;
	      gpfile << "set ylabel 'Cross section'" << endl;
	      gpfile << "plot [0:]\\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):4:5 index " << icount << " with yerrorbars pointtype 7 pointsize 1.0 lc rgb 'black' t 'Data', \\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):6   index " << icount << " w l linewidth 5.0 lc rgb 'red'  t 'Theory w/o shifts', \\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):7   index " << icount << " w l linewidth 5.0 lc rgb 'blue' t 'Theory w/ shifts'" << endl;
	      gpfile << endl;
	      gpfile << "set ylabel 'Theory / Data'" << endl;
	      gpfile << "plot [0:]\\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):($4/$4):($5/$4) index " << icount << " with yerrorbars pointtype 7 pointsize 1.0 lc rgb 'black' notitle, \\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):($6/$4)         index " << icount << " w l linewidth 5.0 lc rgb 'red'  notitle, \\" << endl;
	      gpfile << "     'shifts.txt' u (($3+$2)/2):($7/$4)         index " << icount << " w l linewidth 5.0 lc rgb 'blue' notitle" << endl;
	      gpfile << endl;
	      icount++;
	    }
	  shiftfile << i << "\t\t"
		    << ptl[i] << "\t\t" << ptu[i] << "\t\t"
		    << m[i] << "\t\t" << sqrt(U[i][i]) << "\t\t"
		    << t[i] << "\t\t" << t[i] + shifts[i]
		    << endl;
	}
      shiftfile << endl;
      shiftfile << endl;

      // Compute penalty
      double penalty = 0;
      for(int alpha = 0; alpha < ndata; alpha++)
	penalty += lambda[alpha] * lambda[alpha];

      chi2n += penalty;
      chi2n /= ndata;

      if(abs(chi2n - chi2) > 1e-8)
	cout << "Problem withe computation of the chi2 in terms of nuisance parameters." << endl;

      // Delete pointers
      delete[] y;
      delete[] x;
      delete[] rho;
      delete[] lambda;
      delete[] shifts;
      delete[] m;
      delete[] t;
      delete[] ptl;
      delete[] ptu;
      for(int i = 0; i < ndata; i++)
	{
	  delete[] U[i];
	  delete[] C[i];
	  delete[] V[i];
	  delete[] L[i];
	  delete[] artsys[i];
	  delete[] A[i];
	}
      delete[] U;
      delete[] C;
      delete[] V;
      delete[] L;
      delete[] artsys;
      delete[] A;
   }
  cout << "\nGLOBAL: chi2 per data point = " << chi2tot / ntot << "\n" << endl;

  gpfile.close();
  shiftfile.close();

  system("gnuplot shifts.gp");
  system("open shifts.eps");

  return 0;
}

vector<string> read_directory(string const& name)
{
  vector<string> v;
  DIR* dirp = opendir(name.c_str());
  struct dirent* dp;
  while ((dp = readdir(dirp)) != NULL)
    if (((string) dp->d_name).compare(0, 1, ".") != 0)
      v.push_back(dp->d_name);
  closedir(dirp);
  return v;
}

/*
 * Function to generate artificial systematics
 *
 * These are required for sets where only the covariance matrix
 * is provided (and not the systematics).
 *
 * Artificial systematics are generated from eigensystem of covariance
 * matrix.
 */
bool genArtSys(int const& ndata, double** C, double** artsys)
{
  // Convert two dimentional array to one dimentional for gsl routines
  double* mat = new double[ndata*ndata];
  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      mat[i * ndata + j] = C[i][j];

  // gsl routines to generate eigensystem
  gsl_matrix_view covmat = gsl_matrix_view_array(mat,ndata,ndata);
  gsl_vector* eval = gsl_vector_alloc(ndata);
  gsl_matrix* evec = gsl_matrix_alloc(ndata,ndata);

  gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(ndata);
  gsl_eigen_symmv(&covmat.matrix,eval,evec,w);
  gsl_eigen_symmv_free(w);

  // Check positive-semidefinite-ness (with a tollerance)
  const double toll = - 1e-8;
  for(int i = 0; i < ndata; i++)
    if(gsl_vector_get(eval,i) < toll)
      {
        cerr << "Error in getArtSys: Covariance matrix is not positive-semidefinite" << endl;
        cerr << i << "-th eigen value =" << gsl_vector_get(eval,i) << endl;
        return false;
      }
  
  // Generate aritificial systematics
  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      {
	artsys[i][j] = gsl_matrix_get(evec,i,j) * sqrt(gsl_vector_get(eval,j));
	if(gsl_vector_get(eval,j) < 0)
	  artsys[i][j] = 0;
      }

  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      {
	double T = 0;
	for(int alpha = 0; alpha < ndata; alpha++)
	  T += artsys[i][alpha] * artsys[j][alpha];
	if(abs(T - C[i][j]) > 1e-8)
	  cout << "Problem with the artificial replica generation." << endl;
      }

  gsl_vector_free(eval);
  gsl_matrix_free(evec);

  delete[] mat;

  return true;
}

/*
 * Function to compute the Cholesky decomposition.
 */
bool CholeskyDecomposition(int const& ndata, double** V, double** L)
{
  // Convert two dimentional array to one dimentional for gsl routines
  double* mat = new double[ndata*ndata];
  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      mat[i * ndata + j] = V[i][j];

  gsl_matrix_view covmat = gsl_matrix_view_array(mat,ndata,ndata);

  gsl_linalg_cholesky_decomp1(&covmat.matrix);

  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      if(j > i)
	L[i][j] = 0;
      else
	L[i][j] = gsl_matrix_get(&covmat.matrix,i,j);

  // Check that L * L^T = V
  for(int i = 0; i < ndata; i++)
    for(int j = 0; j < ndata; j++)
      {
	double T = 0;
	for(int k = 0; k < ndata; k++)
	  T += L[i][k] * L[j][k];
	if(abs(T - V[i][j]) > 1e-8)
	  cout << "Problem with the Cholesky decomposition (1)." << endl;
      }

  delete[] mat;

  return true;
}

bool SolveLowerSystem(int const& ndata, double** L, double* y, double* x)
{
  // Solve the system L * y = x by forward substitution
  for(int i = 0; i < ndata; i++)
    {
      x[i] = y[i];
      for(int j = 0; j < i; j++)
	x[i] -= L[i][j] * x[j];

      x[i] /= L[i][i];
    }

  // Check that the solution worked
  for(int i = 0; i < ndata; i++)
    {
      double z = 0;
      for(int j = 0; j < ndata; j++)
	z += L[i][j] * x[j];
      if(abs(z-y[i]) > 1e-8)
	cout << "Problem with the forward substitution." << endl;
    }

  return true;
}

bool SolveUpperSystem(int const& ndata, double** U, double* y, double* x)
{
  // Solve the system U * y = x by backward substitution
  for(int i = ndata - 1; i >= 0; i--)
    {
      x[i] = y[i];
      for(int j = i + 1; j < ndata; j++)
	x[i] -= U[i][j] * x[j];

      x[i] /= U[i][i];
    }

  // Check that the solution worked
  for(int i = 0; i < ndata; i++)
    {
      double z = 0;
      for(int j = 0; j < ndata; j++)
	z += U[i][j] * x[j];
      if(abs(z-y[i]) > 1e-8)
	cout << "Problem with the backward substitution." << endl;
    }

  return true;
}

bool SolveSymmetricSystem(int const& ndata, double** A, double* rho, double* lambda)
{
  // Construct matrix A and vector rho
  double **La  = new double*[ndata];
  double **LaT = new double*[ndata];
  for(int alpha = 0; alpha < ndata; alpha++)
    {
      La[alpha] = new double[ndata];
      LaT[alpha] = new double[ndata];
    }

  // Get Cholesky decomposition of A
  CholeskyDecomposition(ndata, A, La);

  // Solve system La * sigma = rho
  double *sigma  = new double[ndata];
  SolveLowerSystem(ndata, La, rho, sigma);

  // Transpose La
  for(int alpha = 0; alpha < ndata; alpha++)
    for(int beta = 0; beta < ndata; beta++)
      LaT[alpha][beta] = La[beta][alpha];

  // Solve system LaT * lambda = sigma
  SolveUpperSystem(ndata, LaT, sigma, lambda);

  // Check that A * lambda = rho
  for(int i = 0; i < ndata; i++)
    {
      double z = 0;
      for(int j = 0; j < ndata; j++)
	z += A[i][j] * lambda[j];
      if(abs(z-rho[i]) > 1e-8)
	cout << "Problem with the symmetric system." << endl;
    }

  // Delete pointers
  delete[] sigma;
  for(int alpha = 0; alpha < ndata; alpha++)
    {
      delete[] La[alpha];
      delete[] LaT[alpha];
    }
  delete[] La;
  delete[] LaT;

  return true;
}
