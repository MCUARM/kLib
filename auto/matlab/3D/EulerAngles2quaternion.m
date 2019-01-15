function res EulerAngles2quaternion(Euler)
	
	float cos_phi,cos_theta,cos_psi;
	float sin_phi,sin_theta,sin_psi;

	cos_phi = cos(Euler(1,1)/2);
	sin_phi = sin(Euler(1,1)/2);

	cos_theta = cos(Euler(2,1)/2);
	sin_theta = sin(Euler(2,1)/2);

	cos_psi = cos(Euler(3,1)/2);
	sin_psi = sin(Euler(3,1)/2);

	res(1,1) =  cos_psi*cos_theta*cos_phi + sin_psi*sin_theta*sin_phi;
	res(2,1) = -sin_psi*sin_theta*cos_phi + cos_psi*cos_theta*sin_phi;
	res(3,1) =  cos_psi*sin_theta*cos_phi + sin_psi*cos_theta*sin_phi;
	res(4,1) =  sin_psi*cos_theta*cos_phi - cos_psi*sin_theta*sin_phi;

end