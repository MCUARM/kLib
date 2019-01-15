%2d filters

%TODO implementations
zeta filter

%constants
Ts = 0.01;
sigma_g = 0.01;

%initialization

x(:,1) = [1;0];
R = eye(2)*1E2;
P = eye(2)*1E10;
H = eye(2);

for i=2:n

	%prediction

	% TODO Taylor series extension
	A = [cos(gyro_x(i)*Ts) -sin(gyro_x(i));
		 sin(gyro_x(i) cos(gyro_x(i)*Ts)];

	x(:,i) = A*x(:,i-1);
	
	% TODO gyro error maping to complex number (use wolfram alpha)
	Q = ?
	P = A*P*A' + Q;

	%correction

	z_est = H*x(:,i);
	e = z - z_est;
		
	S=H*P*H' + R;
	K=P*H'*S^-1;

	x(:,i) = x(:,i) + K*e;
	P = (eye(2) - K*H)*P;
	
	% output
	angle_est(i) = atan2(x(2,i),x(1,i));
	
	
end


%MEKF

%initialization

P = eye(3)*1E10;
x(:,1) = [0;0;0];

% this is constant through iterations
Q = Ts*eye(3)*sigma_g^2

% phi angle (using accelerometer)
phi_c(1) = atan2f(acc_y(1),acc_z(1));

% theta angle (using accelerometer)
% the acceleration vector length is assumed to be unity
theta_c(1) = asinf(-acc_x(1));	

% psi angle utilizing magnetometer
mag = [mag_x(1);mag_y(1);mag_z(1)];
mag = rotx(phi_est(1))*mag;
mag = roty(theta_est(1))*mag;
% atan2(-y,x)
psi_c(1) = atan2(-mag(2),mag(1));

phi_est(1) = phi_c(1);
theta_est(1) = theta_c(1);
psi_est(1) = psi_c(1);

q(:,1) = EulerAngles2quaternion(phi_est(1),theta_est(1),psi_est(1));

for i=2:n

	%prediction

	omega_cross = [	0 0 0;
					0 0 -gyro_x(i);
					0 gyro_x(i) 0];

					
	%alpha_prim = (alpha(i+1) - alpha(i))/Ts
	%alpha_prim = -omega_cross*alpha
	%(alpha(i+1) - alpha(i))/Ts = -omega_cross*alpha
	%alpha(i+1) - alpha(i) = -Ts*omega_cross*alpha(i)
	%alpha(i+1) = -Ts*omega_cross*alpha(i) + alpha(i)
	%alpha(i+1) = (eye(3) - Ts*omega_cross)*alpha(i)

	A = (eye(3) - Ts*omega_cross)
	x(:,i) = A*x(:,i-1);
	

	P = A*P*A' + Q;
	
	
	%correction
	% mapping into Euler angles residuals
	H = [	1 sin(phi_est(i-1))*tan(theta_est(i-1)) cos(phi_est(i-1))*tan(theta_est(i-1));
			0 cos(phi_est(i-1)) -sin(phi_est(i-1));
			0 sin(phi_est(i-1))/cos(theta_est(i-1)) cos(phi_est(i-1))/cos(theta_est(i-1))];
			
	z_est = H*x(:,i);
	
	
	% phi angle (using accelerometer)
	phi_c(i) = atan2f(acc_y(i),acc_z(i));

	
	% theta angle (using accelerometer)
	% the acceleration vector length is assumed to be unity
	theta_c(i) = asinf(-acc_x(i));	
	
	% psi angle utilizing magnetometer
	mag = [mag_x(i);mag_y(i);mag_z(i)];
	mag = rotx(phi_est(i-1))*mag;
	mag = roty(theta_est(i-1))*mag;
	% atan2(-y,x)
	psi_c(i) = atan2(-mag(2),mag(1));
	
	z = [	phi_c(i) - phi_est(i);
			theta_c(i) - theta_est(i);
			psi_c(i) - psi_est(i)];
	
	e = z - z_est;	
	
	%TODO macierz R!!!
	% to na podstawie pracy 1
	
	S=H*P*H' + R;
	K=P*H'*S^-1;

	x(:,i) = x(:,i) + K*e;
	P = (eye(3) - K*H)*P;	
	
	%get quaternion
	q(:,i) = quaternionMultiplication(q(:,i-1),[1;x(:,i)]);
	
	%get estimated Euler angles
	Euler = quaternion2EulerAngles(q(:,i));
	phi_est(i) = Euler(1);
	theta_est(i) = Euler(2);
	psi_est(i) =  Euler(3);
	
	
end