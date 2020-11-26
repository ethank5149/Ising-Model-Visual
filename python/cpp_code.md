```c++
#include <iostream>
#include <vector>
using namespace std;
    
    
template <typename T>
vector<T> linspace(T a, T b, size_t N) {
    T h = (b - a) / static_cast<T>(N-1);
    vector<T> xs(N);
    typename vector<T>::iterator x;
    T val;
    for (x = xs.begin(), val = a; x != xs.end(); ++x, val += h)
        *x = val;
    return xs;
}
    
class IsingModel{
        int _rows, 
            _cols, 
            _number_of_temperatures, 
            _number_of_magnetic_field_magnitudes, 
            _sample_size, 
            _number_of_relaxation_steps;
    
        double _initial_magnetic_field_magnitude, 
               _final_magnetic_field_magnitude, 
               _ferromagnetic_coupling_constant, 
               _k_boltzmann, 
               _initial_temperature, 
               _final_temperature, 
               _scale;
    
        public:
    
        int rows, 
            cols, 
            number_of_temperatures, 
            number_of_magnetic_field_magnitudes, 
            sample_size, 
            number_of_relaxation_steps;
    
        double initial_magnetic_field_magnitude, 
               final_magnetic_field_magnitude, 
               ferromagnetic_coupling_constant, 
               k_boltzmann, 
               initial_temperature, 
               final_temperature, 
               scale;
    
        vector<double> magnetic_field_magnitude_range, 
                       temperature_range, 
                       energy_sample, 
                       magnetization_sample, 
                       magnetic_field_magnitudes, 
                       temperatures, 
                       energies, 
                       magnetizations, 
                       specific_heat_capacities, 
                       magnetic_susceptibilities;
        vector<vector<int>>  at;

//     IsingModel(   int _rows, 
//                   int _cols, 
//                   int _number_of_relaxation_steps, 
//                   int _sample_size,
//                double _initial_temperature, 
//                double _final_temperature, 
//                   int _number_of_temperatures, 
//                double _initial_magnetic_field_magnitude, 
//                double _final_magnetic_field_magnitude, 
//                   int _number_of_magnetic_field_magnitudes,
//                double _ferromagnetic_coupling_constant, 
//                double _k_boltzmann);
    
    IsingModel(   int /*rows*/, 
                  int /*cols*/, 
                  int /*number_of_relaxation_steps*/, 
                  int /*sample_size*/,
               double /*initial_temperature*/, 
               double /*final_temperature*/, 
                  int /*number_of_temperatures*/, 
               double /*initial_magnetic_field_magnitude*/, 
               double /*final_magnetic_field_magnitude*/, 
                  int /*number_of_magnetic_field_magnitudes*/,
               double /*ferromagnetic_coupling_constant*/, 
               double /*k_boltzmann*/);
    
    double matrix_at(int /*i*/, int /*j*/);
}
    
IsingModel::IsingModel(   int input_rows=10, 
                          int input_cols=10, 
                          int input_number_of_relaxation_steps=2500, 
                          int input_sample_size=2500,
                       double input_initial_temperature=0.1,
                       double input_final_temperature=3.0,
                          int input_number_of_temperatures=100, 
                       double input_initial_magnetic_field_magnitude=0.0, 
                       double input_final_magnetic_field_magnitude=1.0, 
                          int input_number_of_magnetic_field_magnitudes=1,
                       double input_ferromagnetic_coupling_constant=1.0, 
                       double input_k_boltzmann=1.0){    
    
    rows                                = input_rows;
    cols                                = input_cols;
    ferromagnetic_coupling_constant     = input_ferromagnetic_coupling_constant;
    k_boltzmann                         = input_k_boltzmann;
    initial_temperature                 = input_initial_temperature;
    final_temperature                   = input_final_temperature;
    number_of_temperatures              = input_number_of_temperatures;
    initial_magnetic_field_magnitude    = input_initial_magnetic_field_magnitude;
    final_magnetic_field_magnitude      = input_final_magnetic_field_magnitude; 
    number_of_magnetic_field_magnitudes = input_number_of_magnetic_field_magnitudes;
    number_of_relaxation_steps          = input_number_of_relaxation_steps;
    sample_size                         = input_sample_size;
        
    const double scale = 1.0 / (rows * cols);
//     at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

    vector<double>              temperature_range = linspace(initial_temperature             , final_temperature             , number_of_temperatures             );
    vector<double> magnetic_field_magnitude_range = linspace(initial_magnetic_field_magnitude, final_magnetic_field_magnitude, number_of_magnetic_field_magnitudes);
    
    vector<double>             energy_sample(                                                 sample_size, 0.0);
    vector<double>      magnetization_sample(                                                 sample_size, 0.0);
    vector<double> magnetic_field_magnitudes(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
    vector<double>              temperatures(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
    vector<double>                  energies(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
    vector<double>            magnetizations(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
    vector<double>  specific_heat_capacities(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
    vector<double> magnetic_susceptibilities(number_of_magnetic_field_magnitudes * number_of_temperatures, 0.0);
}
    
double IsingModel::metric_at(int i, int j){
    return this->at[             (i + 1) % this->rows,                                 j] +
           this->at[(i - 1 + this->rows) % this->rows,                                 j] +
           this->at[                                i,              (j + 1) % this->cols] +
           this->at[                                i, (j - 1 + this->cols) % this->cols];
}
    
    def get_E(self):
        return self.scale * np.mean(self.energy_sample)
        
    def get_M(self):
        return self.scale * np.mean(self.magnetization_sample)
        
    def get_C(self, temperature):
        return self.scale * np.var(self.energy_sample) * temperature ** (-2.0)
    
    def get_X(self, temperature):
        return self.scale * np.var(self.magnetization_sample) * temperature ** (-1.0)

    def metric(self):
        _ = np.zeros_like(self.at)
        for i in range(self.rows):
            for j in range(self.cols):
                _[i, j] = self.metric_at(i, j)
        return _

    def update(self, magnetic_field_magnitude, temperature):
        for i in range(self.rows):
            for j in range(self.cols):
                dE = 2.0 * (self.J * self.metric_at(i, j) - magnetic_field_magnitude) * self.at[i, j]
                prob = 1.0 if dE < 0.0 else np.exp(-dE / (self.k_B * temperature))
                if np.random.random() < prob:
                    self.at[i, j] = -self.at[i, j]            

    def relax(self, magnetic_field_magnitude, temperature):
        for _ in range(self.n_R):
            self.update(magnetic_field_magnitude, temperature)

    def measure_at(self, magnetic_field_magnitude, temperature):
        for _ in range(self.n_S):
            self.update(magnetic_field_magnitude, temperature)
            dE = 2.0 * (self.J * self.metric() - magnetic_field_magnitude) * self.at
            self.energy_sample[_] = -0.5 * np.sum(dE)
            self.magnetization_sample[_] = np.sum(self.at)
        return magnetic_field_magnitude, temperature, self.get_E(), self.get_M(), self.get_C(temperature), self.get_X(temperature)

    def reset(self):
        self.at = np.random.choice(np.array([1, -1]), size=(self.rows, self.cols))

    def simulate(self):
        for i_h in range(self.n_h):
            magnetic_field_magnitude = self.magnetic_field_magnitude_range[i_h]
            for i_t in range(self.n_T):
                temperature = self.temperature_range[i_t]
                line = i_h * self.n_T + i_t
                print('Running:', 100.0 * line / (self.n_T * self.n_h), '%')
                self.reset()
                self.relax(magnetic_field_magnitude, temperature)
                self.magnetic_field_magnitudes[line], self.T[line], self.E[line], self.M[line], self.C[line], self.X[line] = self.measure_at(magnetic_field_magnitude, temperature)
        return self.H, self.T, self.E, self.M, self.C, self.X
```