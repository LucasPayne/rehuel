#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP


/**
   \file integrator.hpp

   \brief This file contains a class that implement a generic time
   integration loop with a "plug-n-play" way to add different integrators.
*/

#include <armadillo>

#include <vector>

#include "functor.hpp"
#include "irk.hpp"
#include "newton.hpp"

/**
   \brief Integrator class for non-sparse Jacobian matrix.
*/
class integrator
{
public:
	struct options
	{
		// Default options:
		options() : rel_tol( 1e-5 ), abs_tol( 1e-4), max_dt( 1e10 ),
		            constant_jac_approx( true ),
		            adaptive_time_step( true ) {}

		/// Relative tolerance to satisfy when adaptive time stepping
		double rel_tol;
		/// Absolute tolerance to satisfy when adaptive time stepping
		double abs_tol;
		/// Maximum time step size
		double max_dt;
		/// If true, use a constant Jacobi matrix approximation
		bool constant_jac_approx;
		/// If true, use adaptive time step size.
		bool adaptive_time_step;
	};

	integrator( int method ) : sc( irk::get_coefficients(method) ) {}
	~integrator() {}


	int odeint( functor &func, const arma::vec &y0,
	            double t0, double t1, double dt );


private:
	options int_opts;
	irk::solver_coeffs sc;

	double estimate_error( const arma::vec &y_new,
	                       const arma::vec &y_alt,
	                       const arma::mat &J,
	                       double gamma, double dt );

	double get_new_dt( double dt1, double dt0, double err, double err_old );



	arma::vec construct_F( double t, const arma::vec &y,
	                       const arma::vec &K, double dt, functor &func );


	arma::mat construct_J( double t, const arma::vec &y,
	                       const arma::vec &K, double dt, functor &func );

};





#endif // INTEGRATOR_HPP
