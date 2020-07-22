#pragma once

template<class integral=int, class floating=double>
struct ising_params {
	integral nrows;
	integral ncols;

	floating J;
	floating h;
	floating T_0;
	floating T_f;
	floating T;
};