#ifndef MODEL_RECTILINEAR_PROPAGATION_H
#define MODEL_RECTILINEAR_PROPAGATION_H

// Radius of the Earth [m]
const double R_e = 6378000;

// Get length of the arc on the Earth's surface between the nadir direction of the radar and the target
// SRC: (2.11, 2.9) from citation
//    d : the length of the arc on the Earth's surface between the nadir direction of the radar and target [m]
//    psi_d : declination angle [rad]
//    psi_g : sliding angle [rad]
double calculate_d(double psi_d, double psi_g);


#endif // MODEL_RECTILINEAR_PROPAGATION_H
