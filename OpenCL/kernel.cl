/*kernel void matMult(global float* matA, global float* matB, global float* Dest)
{
	int dimensions = get_global_size(0);
	int x = get_global_id(0);
	int y = get_global_id(1);
	if (x < dimensions && y < dimensions)
	{
		float resultXY = 0.0f;
		for (int counter = 0; counter != dimensions; ++counter)
		{
			resultXY += matA[x*dimensions + counter] * matB[counter*dimensions + y];
		}
		Dest[x*dimensions + y] = resultXY;
	}
}*/

kernel void matMult(global float* matA, global float* matB, global float* Dest)
{
	int dimensions = get_global_size(0);
	int i = get_global_id(0);

	if (i < dimensions)
	{
		float vectorA[1024];
		for (int k = 0; k != dimensions; ++k)
		{
			vectorA[k] = matA[i*dimensions + k];
		}
		for (int j = 0; j != dimensions; ++j)
		{
			float Cij = 0.0f;
			for (int k = 0; k != dimensions; ++k)
			{
				Cij += vectorA[k] * matB[k*dimensions + j];
			}
			Dest[i*dimensions + j] = Cij;
		}
	}
}

/*kernel void matMult(global float* matA, global float* matB, global float* Dest, local float* Bwrk)
{
	int dimensions = get_global_size(0);
	int i = get_global_id(0);
	int iloc = get_local_id(0);
	int nloc = get_local_size(0);
	if (i < dimensions)
	{
		float vectorA[2048];
		for (int k = 0; k != dimensions; ++k)
		{
			vectorA[k] = matA[i*dimensions + k];
		}
		for (int j = 0; j != dimensions; ++j)
		{
			for (int k = iloc; k < dimensions; k = k + nloc)
				Bwrk[k] = matB[k*dimensions + j];
			barrier(CLK_LOCAL_MEM_FENCE);
			float Cij = 0.0f;
			for (int k = 0; k != dimensions; ++k)
			{
				Cij += vectorA[k] * Bwrk[k];
			}
			Dest[i*dimensions + j] = Cij;
		}
	}
}*/