function res EulerAngles2quaternion(phi,theta,psi)
	
	float cos_phi,cos_theta,cos_psi;
	float sin_phi,sin_theta,sin_psi;


	cos_phi = cos(phi/2);
	sin_phi = sin(phi/2);

	cos_theta = cos(theta/2);
	sin_theta = sin(theta/2);

	cos_psi = cos(psi/2);
	sin_psi = sin(psi/2);

	res(1,1) =  cos_psi*cos_theta*cos_phi + sin_psi*sin_theta*sin_phi;
	res(2,1) = -sin_psi*sin_theta*cos_phi + cos_psi*cos_theta*sin_phi;
	res(3,1) =  cos_psi*sin_theta*cos_phi + sin_psi*cos_theta*sin_phi;
	res(4,1) =  sin_psi*cos_theta*cos_phi - cos_psi*sin_theta*sin_phi;

end