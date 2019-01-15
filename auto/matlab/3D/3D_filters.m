clear all

%constants
Ts = 0.01;
sigma_gyro = 0.01;
sigma_acc = 1;
sigma_mag = 0.01;

% (1) Zeta, (2) AEKF, (3) MEKF
filter_number = 1;


% common settings
% phi angle (using accelerometer)
EulerC(1,1) = atan2(acc(2,1),acc(3,1));
% theta angle (using accelerometer)
EulerC(2,1) = asinf(-acc(1,1),sqrt(acc(1,1)^2+acc(2,1)^2+acc(3,1)^2));	

EulerC(:,1) = getCorrectionAngles(acc(:,1),mag(:,1),EulerC(:,1));
EulerEst(:,1) = EulerC(:,1);
% initial state
q(:,1) = fromEulerAngles(EulerEst(:,i));


%zeta filter
if filter_number == 1
	%initialization
	% process noise
	w = 3*sigma_gyro^2;
	% initial state
	q(:,1) = q(:,1)*1E-10;


	for i=2:n

		% prediction
		
		% compute control quaternion q_g 
		temp = Ts/2;
		q_g(1,1) = 1;
		q_g(2,1) = temp*gyro(1,i);
		q_g(3,1) = temp*gyro(2,i);
		q_g(4,1) = temp*gyro(3,i);
		

		% process
		q(:,i) = quaternionMultiplication(q(:,i-1),q_g);
		length_q = (q(1,i)^2 + q(2,i)^2 + q(3,i)^2 + q(4,i)^2)*w + 1;
		q(:,i) = q(:,i)/length_q;

		% get Euler angles need for correction step
		EulerEst(:,i) = quaternion2EulerAngles(q(:,i));

		% correction
		
		% get correction angles
		EulerC(:,i) = getCorrectionAngles(acc(:,i),mag(:,i),EulerEst(:,i));
		% compute correction quaternion
		q_c = fromEulerAngles(EulerC(:,i));

		sigma_euler = getCorrectionAnglesDeviations(acc(:,i),mag(:,i),sigma_acc,sigma_mag);
		v = sigma_euler(1,1)^2 + sigma_euler(2,1)^2 + sigma_euler(3,1)^2;

		q_c = q_c/v;

		q(:,i) = q(:,i) + q_c;

	end
end

% AEKF
if filter_number == 2

	%initialization

	% initial state
	P = eye(4)*1E10;

	% correction noise (constant)
	R = eye(3)*sigma_acc^2;


	for i=2:n

		%prediction

		delta_theta2 = (gyro(1,i)*Ts)^2 + (gyro(2,i)*Ts)^2 + (gyro(3,i)*Ts)^2;

		Omega = [	0 -gyro(1,i) -gyro(2,i) -gyro(3,i);
					gyro(1,i) 0 gyro(3,i) -gyro(2,i);
					gyro(2,i) -gyro(3,i) 0 gyro(1,i);
					gyro(3,i) gyro(2,i) -gyro(1,i) 0];

		A = eye(4)*(1-delta_theta2/8) + 1/2*Omega*Ts;
		q(:,i) = A*q(:,i-1);
		
		E = [q(2,i) q(3,i) -q(4,i);
		-q(1,i) q(4,i) -q(3,i);
		-q(4,i) -q(1,i) q(2,i);
		q(3,i) -q(2,i) -q(1,i)];
			
		Q = (Ts/2)^2*E*sigma_gyro^2*eye(4)*E';
		
		
		P = A*P*A' + Q;

		%correction (only theta and psi)

		% TODO sprawdzic macierz H tutaj jaka jest faktycznie
		z_est = [	2*(q(3,i)*q(4,i) - q(1,i)*q(3,i);
					2*(q(3,i)*q(4,i) + q(1,i)*q(2,i);
					q(1,i)^2 - q(2,i)^2 - q(3,i)^2 + q(4,i)^2];

		e = z - z_est;

		H= [-q(3,i) q(4,i) -q(1,i) q(2,i);
			q(2,i) q(1,i) q(4,i) q(3,i);
			q(1,i) -q(2,i) -q(3,i) q(4,i)];
			
		S=H*P*H' + R;
		K=P*H'*S^-1;

		q(:,i) = q(:,i) + K*e;
		% quaternion normalization
		q(:,i) = q(:,i)/sqrt(q(1,i)^2 + q(2,i)^2 + q(3,i)^2 + q(4,i)^2);
		
		
		P = (eye(4) - K*H)*P;
		
		% output
		
		%get estimated Euler angles
		EulerEst(:,i) = quaternion2EulerAngles(q(:,i));
		
		% psi angle utilizing magnetometer
		mag_rot = [	mag(1,i);
					mag(2,i);
					mag(3,i)];
		mag_rot = rotx(EulerEst(1,i))*mag_rot;
		mag_rot = roty(EulerEst(2,i))*mag_rot;
		% atan2(-y,x)
		EulerEst(3,i) = atan2(-mag_rot(2,1),mag_rot(1,1));
		
		
		
	end

%MEKF
if filter_number == 3

	%initialization

	P = eye(3)*1E10;
	x(:,1) = [0;0;0];

	% this is constant through iterations
	Q = Ts*eye(3)*sigma_gyro^2

	for i=2:n

		%prediction

		omega_cross = [	0 -gyro_z(i) gyro_y(i);
						gyro_z(i) 0 -gyro_x(i);
						-gyro_y(i) gyro_x(i) 0];

						
		A = (eye(3) - Ts*omega_cross)
		x(:,i) = A*x(:,i-1);
		

		P = A*P*A' + Q;
		
		
		%correction
		% mapping into Euler angles residuals
		H = [	1 sin(EulerEst(1,i-1))*tan(EulerEst(2,i-1)) cos(EulerEst(1,i-1))*tan(EulerEst(2,i-1));
				0 cos(EulerEst(1,i-1)) -sin(EulerEst(1,i-1));
				0 sin(EulerEst(1,i-1))/cos(EulerEst(2,i-1)) cos(EulerEst(1,i-1))/cos(EulerEst(2,i-1))];
				
		z_est = H*x(:,i);
		
		
		% get correction angles
		EulerC(:,i) = getCorrectionAngles(acc(:,i),mag(:,i),EulerEst(:,i-1));
		
		z = [	EulerC(1,i) - EulerEst(1,i-1);
				EulerC(2,i) - EulerEst(2,i-1);
				EulerC(3,i) - EulerEst(3,i-1)];
		
		e = z - z_est;	
		

		sigma_euler = getCorrectionAnglesDeviations(acc(:,i),mag(:,i),sigma_acc,sigma_mag);
		R = [	sigma_euler(1,1)^2 0 0;
				0 sigma_euler(2,1)^2 0;
				0 0 sigma_euler(3,1)^2];
			

		S=H*P*H' + R;
		K=P*H'*S^-1;

		x(:,i) = x(:,i) + K*e;
		P = (eye(3) - K*H)*P;	
		
		%get quaternion
		q(:,i) = quaternionMultiplication(q(:,i-1),[1;x(:,i)]);
		
		%get estimated Euler angles
		EulerEst(:,i) = quaternion2EulerAngles(q(:,i));
		
	end
	
end