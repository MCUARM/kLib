function res getCorrectionAnglesDeviations(acc,mag,sigma_acc,sigma_mag)

	% get correction angles errors
	
	sigma_phi_c = (abs(acc(2,1)) + abs(acc(3,1)))/(acc(3,1)^2 + acc(2,1)^2)*sigma_acc;

	temp2 = acc(2,1)^2 + acc(3,1)^2;
	temp1 = sqrt(temp2);
	temp2 += acc(1,1)^2;

	a = temp1/temp2;
	temp1 = 1/(temp1*temp2);
	b = abs(acc(1,1)*acc(2,1))*temp1;
	c = abs(acc(1,1)*acc(3,1))*temp1;

	sigma_theta_c = (a+b+c)*sigma_acc;

	temp1 = 1/(mag(1,1)^2 + mag(2,1)^2);

	a = abs(mag(1,1))*temp1;
	b = abs(mag(2,1))*temp1;

	sigma_psi_c = (a+b)*sigma_mag;

	res(1,1) = sigma_phi_c;
	res(2,1) = sigma_theta_c;
	res(3,1) = sigma_psi_c;

end