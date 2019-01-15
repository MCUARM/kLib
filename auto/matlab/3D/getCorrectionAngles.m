function res getCorrectionAngles(acc,mag,EulerEst)

	% phi angle (using accelerometer)
	res(1,1) = atan2(acc(2,1),acc(3,1));

	
	% theta angle (using accelerometer)
	res(2,1) = asinf(-acc(1,1),sqrt(acc(1,1)^2+acc(2,1)^2+acc(3,1)^2));	
	
	% psi angle utilizing magnetometer
	mag = rotx(EulerEst(1,1))*mag;
	mag = roty(EulerEst(2,1))*mag;
	% atan2(-y,x)
	res(3,1) = atan2(-mag(2,1),mag(1,1));

end