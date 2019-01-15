function res = complexMultiplication(c1,c2)

    res(1,1) = c1(1,1)*c2(1,1) - c1(2,1)*c2(2,1);
	res(2,1) = c1(1,1)*c2(2,1) + c1(2,1)*c2(1,1);
	
end