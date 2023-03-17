
enum FilterType
{
    LowPass,
    HighPass,
    BandPass,
    BandStop
};

enum WindowType
{
    Rectangular,
    Triangular,
    Welch,
    Sine,
    Hann,
    Hamming,
    Blackman,
    Nuttall,
    BlackmanNuttall,
    BlackmanHarris,
    FlatTop,
    Kiser
};

#define NUM_BESSELI0_ITERATIONS 32
#define NUM_LNGAMMA_ITERATIONS (256)
#define EULER_GAMMA            (0.57721566490153286)

float kaiser_beta_As(float _As){
    _As = fabsf(_As);
    float beta;
    if (_As >50.0f){
        beta = 0.1102f*(_As - 8.7f);
    }else if (_As > 21.0f)
    {
        beta = 0.5842*powf(_As - 21, 0.4f) + 0.07886f*(_As - 21);
    }else{
        beta = 0.0f;
    }
    return beta;
}

float lngammaf(float _z)
{
    float g;
    if (_z < 0) {
        fprintf(stderr,"error: lngammaf(), undefined for z <= 0\n");
        exit(1);
    } else if (_z < 10.0f) {
#if 0
        g = -EULER_GAMMA*_z - logf(_z);
        unsigned int k;
        for (k=1; k<NUM_LNGAMMA_ITERATIONS; k++) {
            float t0 = _z / (float)k;
            float t1 = logf(1.0f + t0);

            g += t0 - t1;
        }
#else
        // Use recursive formula:
        //    gamma(z+1) = z * gamma(z)
        // therefore:
        //    log(Gamma(z)) = log(gamma(z+1)) - ln(z)
        return lngammaf(_z + 1.0f) - logf(_z);
#endif
    } else {
        // high value approximation
        g = 0.5*( logf(2*M_PI)-log(_z) );
        g += _z*( logf(_z+(1/(12.0f*_z-0.1f/_z)))-1);
    }
    return g;
}

float besseli0f(float z){
    // TODO : use better low-signal approximation
    if (z==0.0f){
        return 1.0f;
    }
   unsigned int k;
   float t,y=0.0f;
   for (k=0;k<NUM_BESSELI0_ITERATIONS;k++){
#if 0
#else
        t = k * logf(0.5f*z) - lngammaf((float)k + 1.0f);
        y += expf(2*t);
#endif

   }
   return y;
}

// Kaiser window 
//  _n      :   sample index
//  _N      :   window length (samples)
//  _beta   :   window taper parameter
double kaiser(unsigned int _n, unsigned int _N, float _beta)
{
    // validate input
    if (_n > _N) {
        fprintf(stderr,"error: kaiser(), sample index must not exceed window length\n");
        exit(1);
    } else if (_beta < 0) {
        fprintf(stderr,"error: kaiser(), beta must be greater than or equal to zero\n");
        exit(1);
    }

    float t = (float)_n - (float)(_N-1)/2;
    float r = 2.0f*t/(float)(_N);
   // float r = 2.0f*(float)_i/(float)_N;
    float a = besseli0f(_beta*sqrtf(1-r*r));
    float b = besseli0f(_beta);
    return (double)(a / b);
}
float  beta_kaiser(int _n, float _As)
{
    // validate inputs
    if (_n == 0) {
        fprintf(stderr,"error: firdes_kaiser(), filter length must be greater than zero\n");
        exit(1);
    }

    float beta = kaiser_beta_As(_As);
    return beta;
}