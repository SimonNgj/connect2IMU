int Calculate(int* fileX, int* fileY, int* fileZ)
{
	int k = 0, Result = 10;
	int Gesture[] = {0, 0, 0, 0, 0, 0};
	// Calculate likelihood of gestures
	// Calculate likelihood of gestures array[1]
	if(fileX[3] == -1 && fileY[3] == 0)
		{
			Gesture[1]+= 5;
		}
		else if(fileX[3] == 0 && fileY[3] == -1 && fileZ[3] == 0)
		{
			Gesture[0]+= 5;
		}
		else if(fileX[3] == 0 && fileY[3] == 1 && fileZ[3] == 1)
		{
			Gesture[3]+= 8;
			Gesture[5]+= 3;
		}
		else if(fileX[3] == 0 && fileY[3] == -1 && fileZ[3] == 1)
		{
			Gesture[4]+= 3;
		}
		else if(fileX[3] == 1 && fileY[3] == 0)
		{
			Gesture[2]+= 5;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[4]
		if(fileX[4] == -1 && fileY[4] == 0 && fileZ[4] == 0)    //1
		{
			Gesture[1]+= 6;
		}
		else if(fileX[4] == 0 && fileY[4] == 0 && fileZ[4] == -1)
		{
			Gesture[0]+= 5;
		}
		else if(fileX[4] == 0 && fileY[4] == 1 && fileZ[4] == 0)
		{
			Gesture[5]+= 6;
		}
		else if(fileX[4] == 0 && fileY[4] == -1 && fileZ[4] == 0)
		{
			Gesture[0]+= 6;
			Gesture[4]+= 5;
		}
		else if(fileX[4] == -1 && fileY[4] == 0 && fileZ[4] == 1)
		{
			Gesture[1]+= 5;
		}
		else if(fileX[4] == 0 && fileY[4] == 1 && fileZ[4] == 1)
		{
			Gesture[3]+= 8;
			Gesture[5]+= 5;
		}
		else if(fileX[4] == 0 && fileY[4] == -1 && fileZ[4] == 1)
		{
			Gesture[3]+= 8;
			Gesture[4]+= 5;
		}
		else if(fileX[4] == 1 && fileY[4] == 0 && fileZ[4] == 1)   //2
		{
			Gesture[2]+= 5;
		}
		else if(fileX[4] == 1 && fileY[4] == 0 && fileZ[4] == 0)   //2
		{
			Gesture[2]+= 6;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[5]
		if(fileX[5] == 0 && fileY[5] == 0 && fileZ[5] == -1)
		{
			Gesture[0]+= 5;
		}
		else if(fileX[5] == 0 && fileY[5] == -1 && fileZ[5] == 0)
		{
			Gesture[0]+= 5;
			Gesture[4]+= 6;
		}
		else if(fileX[5] == -1 && fileY[5] == 0 && fileZ[5] == 1)
		{
			Gesture[1]+= 5;
		}
		else if(fileX[5] == -1 && fileY[5] == 0 && fileZ[5] == 0)
		{
			Gesture[1]+= 6;
		}
		else if(fileX[5] == 0 && fileY[5] == -1 && fileZ[5] == 1)
		{
			Gesture[3]+= 8;
			Gesture[4]+= 5;
		}
		else if(fileX[5] == 0 && fileY[5] == 1 && fileZ[5] == 1)
		{
			Gesture[5]+= 7;
		}
		else if(fileX[5] == 1 && fileY[5] == 0 && fileZ[5] == 1)
		{
			Gesture[2]+= 5;
		}
		else if(fileX[5] == 1 && fileY[5] == 0 && fileZ[5] == 0)
		{
			Gesture[2]+= 6;
		}
		else if(fileX[5] == 0 && fileY[5] == 1 && fileZ[5] == 0)
		{
			Gesture[5]+= 6;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[6]
		if(fileX[6] == 0 && fileY[6] == 0 && fileZ[6] == -1)
		{
			Gesture[0]+= 10;
		}
		else if(fileX[6] == -1 && fileY[6] == 0 && fileZ[6] == 0)
		{
			Gesture[1]+= 10;
		}
		else if(fileX[6] == 1 && fileY[6] == 0 && fileZ[6] == 0)
		{
			Gesture[2]+= 10;
		}
		else if(fileX[6] == 0 && fileY[6] == 0 && fileZ[6] == 1)
		{
			Gesture[3]+= 7;
			Gesture[4]+= 1;
		}
		else if(fileX[6] == 0 && fileY[6] == -1 && fileZ[6] == 0)
		{
			Gesture[0]+= 4;
			Gesture[4]+= 10;
		}
		else if(fileX[6] == 0 && fileY[6] == -1 && fileZ[6] == 1)
		{
			Gesture[3]+= 8;
		}
		else if(fileX[6] == 0 && fileY[6] == 1 && fileZ[6] == 0)
		{
			Gesture[5]+= 10;
		}
		else if(fileX[6] == 0 && fileY[6] == 1 && fileZ[6] == 1)
		{
			Gesture[5]+= 7;
		}
		else if(fileX[6] == -1 && fileY[6] == 0 && fileZ[6] == 1)
		{
			Gesture[1]+= 5;
		}
		else if(fileX[6] == 1 && fileY[6] == 0 && fileZ[6] == 1)
		{
			Gesture[2]+= 5;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[7]
		if(fileX[7] == 0 && fileY[7] == 0 && fileZ[7] == -1)
		{
			Gesture[0]+= 10;
		}
		else if(fileX[7] == -1 && fileY[7] == 0 && fileZ[7] == 0)
		{
			Gesture[1]+= 10;
		}
		else if(fileX[7] == 1 && fileY[7] == 0 && fileZ[7] == 0)
		{
			Gesture[2]+= 10;
		}
		else if(fileX[7] == 0 && fileY[7] == 0 && fileZ[7] == 1)
		{
			Gesture[3]+= 7;
			Gesture[4]+= 1;
		}
		else if(fileX[7] == 0 && fileY[7] == -1 && fileZ[7] == 0)
		{
			Gesture[0]+= 5;
			Gesture[4]+= 10;
		}
		else if(fileX[7] == 0 && fileY[7] == 1 && fileZ[7] == 0)
		{
			Gesture[5]+= 10;
		}
		else if(fileX[7] == 0 && fileY[7] == -1 && fileZ[7] == 1)
		{
			Gesture[3]+= 8;
		}
		else if(fileX[7] == 0 && fileY[7] == 1 && fileZ[7] == 1)
		{
			Gesture[5]+= 5;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[8]
		if(fileX[8] == 0 && fileY[8] == 0 && fileZ[8] == -1)
		{
			Gesture[0]+= 10;
		}
		else if(fileX[8] == -1 && fileY[8] == 0 && fileZ[8] == 0)
		{
			Gesture[1]+= 10;
		}
		else if(fileX[8] == 1 && fileY[8] == 0 && fileZ[8] == 0)
		{
			Gesture[2]+= 10;
		}
		else if(fileX[8] == 0 && fileY[8] == 0 && fileZ[8] == 1)
		{
			Gesture[1]+= 5;
			Gesture[2]+= 5;
			Gesture[3]+= 10;
		}
		else if(fileX[8] == 0 && fileY[8] == -1 && fileZ[8] == 0)
		{
			Gesture[0]+= 4;
			Gesture[4]+= 10;
		}
		else if(fileX[8] == 0 && fileY[8] == 1 && fileZ[8] == 0)
		{
			Gesture[5]+= 10;
		}
		else if(fileX[8] == 0 && fileY[8] == -1 && fileZ[8] == 1)
		{
			Gesture[3]+= 8;
		}
		else if(fileX[8] == 0 && fileY[8] == 1 && fileZ[8] == 1)
		{
			Gesture[3]+= 8;
			Gesture[5]+= 3;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[9]
		if(fileX[9] == 0 && fileY[9] == 0 && fileZ[9] == -1)
		{
			Gesture[0]+= 10;
		}
		else if(fileX[9] == -1 && fileY[9] == 0 && fileZ[9] == 0)
		{
			Gesture[1]+= 10;
		}
		else if(fileX[9] == 1 && fileY[9] == 0 && fileZ[9] == 0)
		{
			Gesture[2]+= 10;
		}
		else if(fileX[9] == 0 && fileY[9] == 0 && fileZ[9] == 1)
		{
			Gesture[3]+= 10;
		}
		else if(fileX[9] == 0 && fileY[9] == -1 && fileZ[9] == 0)
		{
			Gesture[4]+= 10;
		}
		else if(fileX[9] == 0 && fileY[9] == 1 && fileZ[9] == 0)
		{
			Gesture[5]+= 10;
		}
		else if(fileX[9] == 0 && fileY[9] == 1 && fileZ[9] == 1)
		{
			Gesture[3]+= 8;
		}
		// Calculate likelihood of gestures
		// Calculate likelihood of gestures array[10]
		if(fileX[10] == 0 && fileY[10] == 0 && fileZ[10] == -1)
		{
			Gesture[0]+= 10;
		}
		else if(fileX[10] == -1 && fileY[10] == 0 && fileZ[10] == 0)
		{
			Gesture[1]+= 10;
		}
		else if(fileX[10] == 1 && fileY[10] == 0 && fileZ[10] == 0)
		{
			Gesture[2]+= 10;
		}
		else if(fileX[10] == 0 && fileY[10] == 0 && fileZ[10] == 1)
		{
			Gesture[3]+= 10;
		}
		else if(fileX[10] == 0 && fileY[10] == -1 && fileZ[10] == 0)
		{
			Gesture[4]+= 10;
		}
		else if(fileX[10] == 0 && fileY[10] == 1 && fileZ[10] == 0)
		{
			Gesture[5]+= 10;
		}
	int max = 25;
	for(k=0; k<6; k++)
	{
		if(Gesture[k]>max)
		{
			max = Gesture[k];
			Result = k;
		}
	}
	return Result;
}
//-----------------------------------o0o------------------------------------------
