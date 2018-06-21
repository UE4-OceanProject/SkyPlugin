/* --- Utility Functions --- */

// Float versions

float ASkyManager::SinD(float input)
{
	return FMath::Sin((PI / 180.0f) * input);
}

float ASkyManager::ASinD(float input)
{
	return (180.0f / PI) * FMath::Asin(input);
}

float ASkyManager::CosD(float input)
{
	return FMath::Cos((PI / 180.0f) * input);
}

float ASkyManager::ACosD(float input)
{
	return (180.0f / PI) * FMath::Acos(input);
}

float ASkyManager::TanD(float input)
{
	return FMath::Tan((PI / 180.0f) * input);
}

float ASkyManager::ATanD(float input)
{
	return (180.0f / PI) * FMath::Atan(input);
}

float ASkyManager::ATan2D(float A, float B)
{
	return (180.f / PI) * FMath::Atan2(A, B);
}


// Double versions

double ASkyManager::SinD(double input)
{
	return sin((PI / 180.0) * input);
}

double ASkyManager::ASinD(double input)
{
	return (180.0 / PI) * asin(input);
}

double ASkyManager::CosD(double input)
{
	return cos((PI / 180.0) * input);
}

double ASkyManager::ACosD(double input)
{
	return (180.0 / PI) * acos(input);
}

double ASkyManager::TanD(double input)
{
	return tan((PI / 180.0) * input);
}

double ASkyManager::ATanD(double input)
{
	return (180.0 / PI) * atan(input);
}

double ASkyManager::ATan2D(double A, double B)
{
	return (180.0 / PI) * atan2(A, B);
}
