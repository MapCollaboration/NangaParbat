//
// Author: Valerio Bertone: valerio.bertone@cern.ch
//

#include "NangaParbat/utilities.h"

#include <iostream>
#include <cmath>
#include <gsl/gsl_linalg.h>

namespace NangaParbat
{
  //_________________________________________________________________________________
  std::vector<double> GenerateGrid(int const& n, double const& min, double const& max, int const& ext)
  {
    std::vector<double> grid(n+ext+1);
    const double step = ( max - min ) / n;
    for (int i = 0; i <= n + ext; i++)
      grid[i] = min + i * step;
    return grid;
  }

  //_________________________________________________________________________________
  apfel::matrix<double> CholeskyDecomposition(apfel::matrix<double> const V)
  {
    // Convert two dimentional array to one dimentional for gsl routines
    const int ndata = V.size(0);
    double* mat = new double[ndata*ndata];
    for(int i = 0; i < ndata; i++)
      for(int j = 0; j < ndata; j++)
	mat[i * ndata + j] = V(i, j);

    gsl_matrix_view covmat = gsl_matrix_view_array(mat,ndata,ndata);

    gsl_linalg_cholesky_decomp1(&covmat.matrix);

    apfel::matrix<double> L{ndata, ndata};
    for(int i = 0; i < ndata; i++)
      for(int j = 0; j < ndata; j++)
	if(j > i)
	  L(i, j) = 0;
	else
	  L(i, j) = gsl_matrix_get(&covmat.matrix,i,j);

    // Check that L * L^T = V
    for(int i = 0; i < ndata; i++)
      for(int j = 0; j < ndata; j++)
	{
	  double T = 0;
	  for(int k = 0; k < ndata; k++)
	    T += L(i, k) * L(j, k);
	  if(abs(T - V(i, j)) > 1e-8)
	    throw std::runtime_error("[CholeskyDecomposition]: Problem with the Cholesky decomposition.");
	}
    delete[] mat;
    return L;
  }

  //_________________________________________________________________________________
  std::vector<double> SolveLowerSystem(apfel::matrix<double> L, std::vector<double> y)
  {
    // Solve the system L * y = x by forward substitution
    const int ndata = y.size();
    std::vector<double> x(ndata);
    for(int i = 0; i < ndata; i++)
      {
	x[i] = y[i];
	for(int j = 0; j < i; j++)
	  x[i] -= L(i, j) * x[j];

	x[i] /= L(i, i);
      }

    // Check that the solution worked
    for(int i = 0; i < ndata; i++)
      {
	double z = 0;
	for(int j = 0; j < ndata; j++)
	  z += L(i, j) * x[j];
	if(abs(z - y[i]) > 1e-8)
	  throw std::runtime_error("[SolveLowerSystem]: Problem with the forward substitution.");
      }
    return x;
  }

  //_________________________________________________________________________________
  std::vector<double> SolveUpperSystem(apfel::matrix<double> U, std::vector<double> y)
  {
    // Solve the system U * y = x by backward substitution
    const int ndata = y.size();
    std::vector<double> x(ndata);
    for(int i = ndata - 1; i >= 0; i--)
      {
	x[i] = y[i];
	for(int j = i + 1; j < ndata; j++)
	  x[i] -= U(i, j) * x[j];

	x[i] /= U(i, i);
      }

    // Check that the solution worked
    for(int i = 0; i < ndata; i++)
      {
	double z = 0;
	for(int j = 0; j < ndata; j++)
	  z += U(i, j) * x[j];
	if(abs(z-y[i]) > 1e-8)
	  throw std::runtime_error("[SolveUpperSystem]: Problem with the backward substitution.");
      }
    return x;
  }

  //_________________________________________________________________________________
  std::vector<double> SolveSymmetricSystem(apfel::matrix<double> A, std::vector<double> rho)
  {
    // Get Cholesky decomposition of A
    const apfel::matrix<double> La = CholeskyDecomposition(A);

    // Solve system La * sigma = rho
    const std::vector<double> sigma = SolveLowerSystem(La, rho);

    // Transpose La
    const int ndata = rho.size();
    apfel::matrix<double> LaT{ndata, ndata};
    for(int alpha = 0; alpha < ndata; alpha++)
      for(int beta = 0; beta < ndata; beta++)
	LaT(alpha, beta) = La(beta, alpha);

    // Solve system LaT * lambda = sigma
    const std::vector<double> lambda = SolveUpperSystem(LaT, sigma);

    // Check that A * lambda = rho
    for(int i = 0; i < ndata; i++)
      {
	double z = 0;
	for(int j = 0; j < ndata; j++)
	  z += A(i, j) * lambda[j];
	if(abs(z - rho[i]) > 1e-8)
	  throw std::runtime_error("[SolveSymmetricSystem]: Problem with the symmetric system.");
      }
    return lambda;
  }
}
