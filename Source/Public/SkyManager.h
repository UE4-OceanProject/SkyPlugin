#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeManager.h"
#include "SkyManager.generated.h"

/** Radians to degrees. */
const double RAD_TO_DEG = 180.0 / PI;

/** Degrees to radians. */
const double DEG_TO_RAD = 1.0 / RAD_TO_DEG;

/** Astronomical Unit in km. As defined by JPL. */
const double AU = 149597870.691;

/** Earth equatorial radius in km. IERS 2003 Conventions. */
const double EARTH_RADIUS = 6378.1366;

/** Two times Pi. */
const double TWO_PI = 2.0 * PI;

/** Pi divided by two. */
const double PI_OVER_TWO = PI / 2.0;



/**
 * Class to hold the results of ephemerides.
 * @author T. Alonso Albi - OAN (Spain)
 */
USTRUCT(BlueprintType)
struct FEphemeris
{
	GENERATED_BODY()

		/** Values for azimuth, elevation, rise, set, and transit for the Sun. Angles in radians, rise ...
 * as Julian days in UT. Distance in AU. */
		UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float azimuth;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  elevation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  rise;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  set;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  transit;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  transitElevation;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  distance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  rightAscension;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  declination;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  illuminationPhase;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  eclipticLongitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  eclipticLatitude;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		float  angularRadius;
	//Constructor
	FEphemeris()
	{
		azimuth = 0;
		elevation = 0;
		rise = 0;
		set = 0;
		transit = 0;
		transitElevation = 0;
		rightAscension = 0;
		declination = 0;
		distance = 0;
		illuminationPhase = 100;
		eclipticLongitude = 0;
		eclipticLatitude = 0;
		angularRadius = 0;
	}

	FEphemeris(double azi, double alt, double rise2, double set2,
		double transit2, double transit_alt, double ra, double dec,
		double dist, double eclLon, double eclLat, double angR) {
		azimuth = azi;
		elevation = alt;
		rise = rise2;
		set = set2;
		transit = transit2;
		transitElevation = transit_alt;
		rightAscension = ra;
		declination = dec;
		distance = dist;
		illuminationPhase = 100;
		eclipticLongitude = eclLon;
		eclipticLatitude = eclLat;
		angularRadius = angR;
	}


};


/**
* A very simple yet accurate Sun/Moon calculator without using JPARSEC library.
* @author T. Alonso Albi - OAN (Spain), email t.alonso@oan.es
* @version November 26, 2018 (two new methods getCulminationTime and getAzimuthTime)
* @version November 6, 2018 (better accuracy for Moon, angular radius in ephemeris, cosmetic improvements)
* @version July 24, 2018 (new class to hold results, illumination phase, moon phases, equinoxes and solstices)
* @version May 25, 2017 (fixed nutation correction and moon age, better accuracy in Moon)
*/
//An actor based system for tracking the Sun/Moon rotation/phase.
UCLASS(NotBlueprintable)
class ASkyManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	ATimeManager* TimeManager;

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

	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		int32 DayOfYear = 0;

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

	/**
	* @Name: CalculateSunAngle
	* @Description: Calculates the sun angle rotator from the current time.
	*
	* @return: FRotator - The sun rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		FRotator CalculateSunAngle();


	/**
	* @Name: CalculateMoonAngle
	* @Description: Calculates the moon angle rotator from the current time.
	*
	* @return: FRotator - The moon rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		FRotator CalculateMoonAngle();


	/**
	* @Name: CalculateMoonPhase
	* @Description: Calculates the moon phase for the current time and date.
	*
	* @return: FRotator - The moon rotation value for the current time.
	*/
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		float CalculateMoonPhase();

	private:

		bool bIsCalendarInitialized = false;

		// Obliquity of the Ecliptic (as of 2000/01/01 - approximation, but fairly accurate)
		double EcObliquity = 23.4397;
};

