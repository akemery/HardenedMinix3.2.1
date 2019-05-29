#include "../real.h"


real_t loggamma(real_t x)
{
	int i;
	real_t r,x2,y,f,u0,u1,u,z,b[19];

	if (x > 13.0) {
		r=1.0;
		while (x <= 22.0) {
			r /= x;
			x += 1.0;
		}
		x2 = -1.0/(x*x);
		r=log(r);
		return log(x)*(x-0.5)-x+r+0.918938533204672+
				(((0.595238095238095e-3*x2+0.793650793650794e-3)*x2+
				0.277777777777778e-2)*x2+0.833333333333333e-1)/x;
	} else {
		f=1.0;
		u0=u1=0.0;
		b[1]  = -0.0761141616704358;  b[2]  = 0.0084323249659328;
		b[3]  = -0.0010794937263286;  b[4]  = 0.0001490074800369;
		b[5]  = -0.0000215123998886;  b[6]  = 0.0000031979329861;
		b[7]  = -0.0000004851693012;  b[8]  = 0.0000000747148782;
		b[9]  = -0.0000000116382967;  b[10] = 0.0000000018294004;
		b[11] = -0.0000000002896918;  b[12] = 0.0000000000461570;
		b[13] = -0.0000000000073928;  b[14] = 0.0000000000011894;
		b[15] = -0.0000000000001921;  b[16] = 0.0000000000000311;
		b[17] = -0.0000000000000051;  b[18] = 0.0000000000000008;
		if (x < 1.0) {
			f=1.0/x;
			x += 1.0;
		} else
			while (x > 2.0) {
				x -= 1.0;
				f *= x;
			}
		f=log(f);
		y=x+x-3.0;
		z=y+y;
		for (i=18; i>=1; i--) {
			u=u0;
			u0=z*u0+b[i]-u1;
			u1=u;
		}
		return (u0*y+0.491415393029387-u1)*(x-1.0)*(x-2.0)+f;
	}
}
