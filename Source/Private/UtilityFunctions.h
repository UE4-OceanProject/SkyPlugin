// For copyright see LICENSE in EnvironmentProject root dir, or:
//https://github.com/UE4-OceanProject/OceanProject/blob/Master-Environment-Project/LICENSE

/* --- Utility Functions --- */

// Float versions

// Performs FMath::Sin(input) using degrees
float SinD(float input)
{
	return FMath::Sin((PI / 180.0f) * input);
}

// Performs FMath::Asin(input) using degrees
float ASinD(float input)
{
	return (180.0f / PI) * FMath::Asin(input);
}

// Performs FMath::Cos(input) using degrees
float CosD(float input)
{
	return FMath::Cos((PI / 180.0f) * input);
}

// Performs FMath::Acos(input) using degrees
float ACosD(float input)
{
	return (180.0f / PI) * FMath::Acos(input);
}

// Performs FMath::Tan(input) using degrees
float TanD(float input)
{
	return FMath::Tan((PI / 180.0f) * input);
}

// Performs FMath::Atan(input) using degrees
float ATanD(float input)
{
	return (180.0f / PI) * FMath::Atan(input);
}

// Performs FMath::Atan2(A, B) using degrees
float ATan2D(float A, float B)
{
	return (180.0f / PI) * FMath::Atan2(A, B);
}

// Double versions

// Performs FMath::Sin(input) using degrees
double SinD(double input)
{
	return sin((PI / 180.0) * input);
}

// Performs FMath::Asin(input) using degrees
double ASinD(double input)
{
	return (180.0 / PI) * asin(input);
}


// Performs FMath::Cos(input) using degrees
double CosD(double input)
{
	return cos((PI / 180.0) * input);
}

// Performs FMath::Acos(input) using degrees
double ACosD(double input)
{
	return (180.0 / PI) * acos(input);
}

// Performs FMath::Tan(input) using degrees
double TanD(double input)
{
	return tan((PI / 180.0) * input);
}

// Performs FMath::Atan(input) using degrees
double ATanD(double input)
{
	return (180.0 / PI) * atan(input);
}

// Performs FMath::Atan2(A, B) using degrees
double ATan2D(double A, double B)
{
	return (180.0 / PI) * atan2(A, B);
}