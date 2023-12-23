

void solve_simultaneous(float coefficients1[3], float coefficients2[3]);
void solve_quadratic(float coefficients[3]);
void solve_cubic(float coefficients[4]);
void solve_quartic(float coefficients[5], float diff[4]);
float newton_raphson(float coefficients[5], float diff[4], float x0, int i);