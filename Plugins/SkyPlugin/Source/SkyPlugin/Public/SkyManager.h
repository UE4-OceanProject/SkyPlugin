/*=================================================
* For parts referencing UE4 code, the following copyright applies:
* Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
*
* Feel free to use this software in any commercial/free game.
* Selling this as a plugin/item, in whole or part, is not allowed.
* See LICENSE for full licensing details.
* =================================================*/

#pragma once

#include "GameFramework/Actor.h"
#include "SkyManager.generated.h"


//An actor based Sun/Moon rotation/phase calculator.
//Transient will prevent this from being saved since we autospawn this anyways
//Removed the Transient property, plugin will spawn this if its missing, and wont if its already there
UCLASS(NotBlueprintable)
class ASkyManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// The current Local Solar Time (in minutes)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float SolarTime = 0.0f;

	// The current Local Clock Time value (in minutes)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float LocalClockTime = 0.0f;

	// The current Time Correction factor
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float TimeCorrection = 0.0f;

	// The value of the local Standard Time Meridian (15deg intervals)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		int32 LSTM = 0;

	// THe current Equation of Time value
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float EoT = 0.0f;

	// The current Altitude Angle of the sun
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float SolarAltAngle = 0.0f;

	// The current Declination angle of the sun
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float SolarDeclination = 0.0f;

	// The Azimuth angle of the sun
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float SolarAzimuth = 0.0f;

	// The current Hour Angle of the sun
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Sun Debug")
		float SolarHRA = 0.0f;

	// The current Sidereal Time value
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float SiderealTime = 0.0f;

	// The current Altitude Angle of the moon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarAltAngle = 0.0f;

	// The current Hour Angle of the moon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarHRA = 0.0f;

	// The current Declination angle of the moon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarDeclination = 0.0f;

	// The current Azimuth angle of the moon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarAzimuth = 0.0f;

	// The current Right Ascension angle for the moon
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarRightAsc = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float LunarElapsedDays = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float EcLongitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float EcLatitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float EcDistance = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float PartL = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
		float PartM = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Lunar Debug")
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

    };

