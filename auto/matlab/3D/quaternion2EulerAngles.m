function res quaternion2EulerAngles(q)
	% converts quaternion to Euler angles using the homogeneous expression

	% get phi
	nom = 2*(q(1,1)*q(2,1) + q(3,1)*q(4,1));
	denom = q(1,1)*q(1,1) - q(2,1)*q(2,1) - q(3,1)*q(3,1) + q(4,1)*q(4,1);
	res(1,1) = atan2(nom,denom);

	% get theta
	nom = 2*(q(1,1)*q(3,1) - q(4,1)*q(2,1));
	denom = q(1,1)^2 + q(2,1)^2 + q(3,1)^2 + q(4,1)^2;
	res(2,1) = asin(nom/denom);

	% get psi
	nom = 2*(q(1,1)*q(4,1) + q(2,1)*q(3,1));
	denom = q(1,1)*q(1,1) + q(2,1)*q(2,1) - q(3,1)*q(3,1) - q(4,1)*q(4,1);
	res(3,1) = atan2(nom,denom);

end