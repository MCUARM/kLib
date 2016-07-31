#include "kLKF.h"


void kLKF_2x_2u::init(void)
{
	kMatrix::transpose(Ft,F);
	kMatrix::transpose(Ht,H);
	kMatrix::makeEye(I);
}
void kLKF_2x_2u::process(void)
{
	// Prediction
	kMatrix::multiply(t1,F,x);
	kMatrix::multiply(t2,B,u);
	kVector::add(x_a_priori,t1,t2);

	kMatrix::multiply(T1,F,P_a_posteriori);
	kMatrix::multiply(T2,T1,Ft);
	kMatrix::add(P_a_priori,T2,Q);


	// Correction
	kMatrix::multiply(t1,H,x_a_priori);
	kVector::subtract(y,z,t1);

	kMatrix::multiply(T1,H,P_a_priori);
	kMatrix::multiply(T2,T1,Ht);
	kMatrix::add(T1,T2,R);

	kMatrix::invert(T2,T1);
	kMatrix::multiply(T1,P_a_priori,Ht);
	kMatrix::multiply(K,T1,T2);

	kMatrix::multiply(t1,K,y);
	kVector::add(x,x_a_priori,t1);

	kMatrix::multiply(T1,K,H);
	kMatrix::subtract(T2,I,T1);
	kMatrix::multiply(P_a_posteriori,T2,P_a_priori);
}

kLKF_2x_2u::kLKF_2x_2u(void)
{

}
