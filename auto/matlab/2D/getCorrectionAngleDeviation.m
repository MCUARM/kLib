function res getCorrectionAngleDeviation(acc(:,i),sigma_acc)

	% get correction angle deviation
	res = (abs(acc(2,1)) + abs(acc(3,1)))/(acc(3,1)^2 + acc(2,1)^2)*sigma_acc;

end