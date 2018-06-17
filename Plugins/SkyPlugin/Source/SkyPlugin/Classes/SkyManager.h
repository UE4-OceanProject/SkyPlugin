/*=================================================
* FileName: SkyManager.h
*
* Created by: DotCam
* Project name: OceanProject
* Unreal Engine version: 4.18.3
* Created on: 2015/07/12
*
* Last Edited on: 2018/05/31
* Last Edited by: Dotcam
*
* -------------------------------------------------
* For parts referencing UE4 code, the following copyright applies:
* Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
*
* Feel free to use this software in any commercial/free game.
* Selling this as a plugin/item, in whole or part, is not allowed.
* See "OceanProject\License.md" for full licensing details.
* =================================================*/

#pragma once

#include "GameFramework/Actor.h"
#include "TimeManager.h"
#include "TimePlugin.h"
#include "SkyManager.generated.h"


//An actor based calendar system for tracking date + time, and Sun/Moon rotation/phase.
UCLASS(BlueprintType)
class ASkyManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	ATimeManager* TimeManagerActor = FTimePlugin::Get().TimeManagerActor;

	// The current Local Solar Time (in minutes)
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarTime = 0.0f;

	// The current Local Clock Time value (in minutes)
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float LocalClockTime = 0.0f;

	// The current Time Correction factor
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float TimeCorrection = 0.0f;

	// The value of the local Standard Time Meridian (15deg intervals)
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		int32 LSTM = 0;

	// THe current Equation of Time value
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float EoT = 0.0f;

	// The current Altitude Angle of the sun
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarAltAngle = 0.0f;

	// The current Declination angle of the sun
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarDeclination = 0.0f;

	// The Azimuth angle of the sun
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarAzimuth = 0.0f;

	// The current Hour Angle of the sun
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarHRA = 0.0f;

	// The current Sidereal Time value
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float SiderealTime = 0.0f;

	// The current Altitude Angle of the moon
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarAltAngle = 0.0f;

	// The current Hour Angle of the moon
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarHRA = 0.0f;

	// The current Declination angle of the moon
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarDeclination = 0.0f;

	// The current Azimuth angle of the moon
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarAzimuth = 0.0f;

	// The current Right Ascension angle for the moon
	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarRightAsc = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarElapsedDays = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcLongitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcLatitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcDistance = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartL = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartM = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartF = 0.0f;

	// -------------------
	// PUBLIC FUNCTIONS
	// -------------------


	/**
	* @Name: CalculateSunAngle
	* @Description: Calculates the sun angle rotator from the current time.
	*
	* @return: FRotator - The sun rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "SkyManager")
		FRotator CalculateSunAngle();


	/**
	* @Name: CalculateMoonAngle
	* @Description: Calculates the moon angle rotator from the current time.
	*
	* @return: FRotator - The moon rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "SkyManager")
		FRotator CalculateMoonAngle();


	/**
	* @Name: CalculateMoonPhase
	* @Description: Calculates the moon phase for the current time and date.
	*
	* @return: FRotator - The moon rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "SkyManager")
		float CalculateMoonPhase();


private:

	// The Julian Day number for Jan 1, 2000 @ 12:00 UTC
	double JD2000 = 2451545.0;

	// The Julian Day number for Jan 1, 1900 @ 12:00 UTC
	double JD1900 = 2415020.0;

	double ElapsedJD1900 = 0.0;

	// Obliquity of the Ecliptic (as of 2000/01/01 - approximation, but fairly accurate)
	double EcObliquity = 23.4397;

	/* --- Utility Functions --- */

	// Float versions

	// Performs FMath::Sin(input) using degrees
	float SinD(float input);

	// Performs FMath::Asin(input) using degrees
	float ASinD(float input);

	// Performs FMath::Cos(input) using degrees
	float CosD(float input);

	// Performs FMath::Acos(input) using degrees
	float ACosD(float input);

	// Performs FMath::Tan(input) using degrees
	float TanD(float input);

	// Performs FMath::Atan(input) using degrees
	float ATanD(float input);

	// Performs FMath::Atan2(A, B) using degrees
	float ATan2D(float A, float B);

	// Double versions

	// Performs FMath::Sin(input) using degrees
	double SinD(double input);

	// Performs FMath::Asin(input) using degrees
	double ASinD(double input);

	// Performs FMath::Cos(input) using degrees
	double CosD(double input);

	// Performs FMath::Acos(input) using degrees
	double ACosD(double input);

	// Performs FMath::Tan(input) using degrees
	double TanD(double input);

	// Performs FMath::Atan(input) using degrees
	double ATanD(double input);

	// Performs FMath::Atan2(A, B) using degrees
	double ATan2D(double A, double B);



	// TODO - Requires extra functions & rewriting to accommodate, FUTURE/NOT URGENT
	// Designates that the calendar should use custom Date & Time struct rather than
	// using the built in DateTime values. This is useful for worlds that have longer days,
	// months, and years.
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DateTime")
	//bool UsingCustomCaledar;


    };

