function res = quaternionMultiplication(q1,q2)

    res(1,1) = q1(1,1)*q2(1,1) - q1(2,1)*q2(2,1) - q1(3,1)*q2(3,1) - q1(4,1)*q2(4,1);
    res(2,1) = q1(1,1)*q2(2,1) + q1(2,1)*q2(1,1) + q1(3,1)*q2(4,1) - q1(4,1)*q2(3,1);
    res(3,1) = q1(1,1)*q2(3,1) - q1(2,1)*q2(4,1) + q1(3,1)*q2(1,1) + q1(4,1)*q2(2,1);
    res(4,1) = q1(1,1)*q2(4,1) + q1(2,1)*q2(3,1) - q1(3,1)*q2(2,1) + q1(4,1)*q2(1,1);
	
end