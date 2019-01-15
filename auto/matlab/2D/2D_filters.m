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
AngleC(1,1) = getCorrectionAngle(acc(:,1));
AngleEst(1,1) = AngleC(1,1);
% initial state
x(:,1) = [	cos(AngleEst(1,1);
			sin(AngleEst(1,1)];


%zeta filter
if filter_number == 1
	%initialization
	% process noise
	w = (Ts*sigma_gyro)^2;
	% initial state
	x(:,1) = x(:,1)*1E-10;


	for i=2:n

		% prediction
		
		% compute control complex number b_g 
		b_g(1,1) = 1;
		b_g(2,1) = Ts*gyro(1,i);
		
		% process
		x(:,i) = complexMultiplication(x(:,i-1),b_g);
					
		length_x = (x(1,i)^2 + x(2,i)^2)*w + 1;
		x(:,i) = x(:,i)/length_x;

		% correction

		% get correction complex number
		x_c = [acc(3,1);acc(2,1)]/sqrt(acc(3,1)^2 + acc(2,1)^2);
		sigma_angle = getCorrectionAngleDeviation(acc(:,i),sigma_acc);
		v = sigma_angle^2;
		x_c = x_c/v;

		%update
		x(:,i) = x(:,i) + x_c;


		%output
		% get estimated angle
		AngleEst(:,i) = complex2Angle(x(:,i));

	end
end

% AEKF
if filter_number == 2

	%initialization

	% initial state
	P = eye(2)*1E10;

	% correction noise (constant)
	R = eye(2)*sigma_acc^2;


	H = eye(2)*9.81;

	for i=2:n

		%prediction


		A = [1 -Ts*gyro(1,i);
			 Ts*gyro(1,i) 1];
		x(:,i) = A*x(:,i-1);
		
		
		E = [x(2,i) 0;       		
		    0	x(1,i)];
		
		Q = E*eye(2)*(Ts*sigma_gyro)^2*E';
			 
		P = A*P*A' + Q;

		%correction
		z_est = H*x;

		e = z - z_est;
			
		S=H*P*H' + R;
		K=P*H'*S^-1;

		x(:,i) = x(:,i) + K*e;
		% complex number normalization
		x(:,i) = x(:,i)/sqrt(x(1,i)^2 + x(2,i)^2);
		
		% covariance matrix update
		P = (eye(2) - K*H)*P;
		
		%output
		% get estimated angle
		AngleEst(:,i) = complex2Angle(x(:,i));
		
		
	end

%MEKF

if filter_number == 3

	%initialization

	P = eye(1)*1E10;
	x(:,1) = [0];

	% this is constant through iterations
	Q = (Ts*sigma_gyro)^2;
	
	H = 1;

	for i=2:n

		%prediction						
		a(:,i) = Ts*gyro(1,i);
		P = Q;
		
		
		%correction
		% mapping into angle residual
		z_est = H*a(:,i);
		
		
		% get correction angle
		AngleC(:,i) = getCorrectionAngle(acc(:,i));
		
		z = [AngleC(1,i) - AngleEst(1,i-1)];
		% get residual vector
		e = z - z_est;	
		
		sigma_angle = getCorrectionAngleDeviation(acc(:,i),sigma_acc);
		R = [sigma_angle(1,1)^2];
			

		S=H*P*H' + R;
		K=P*H'*S^-1;

		x(:,i) = x(:,i) + K*e;
		P = (eye(1) - K*H)*P;	
		
		%get complex number
		x(:,i) = complexMultiplication(x(:,i-1),[1;a(:,i)]);
		
		%output
		% get estimated angle
		AngleEst(:,i) = complex2Angle(x(:,i));
		
	end
	
end