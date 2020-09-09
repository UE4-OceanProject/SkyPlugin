//This is a c++/UE4 port of the excellent ephemerides(in Java) by Tomás Alonso Albi:
//http://conga.oan.es/~alonso/doku.php?id=blog:sun_moon_position

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeDateStruct.h"
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

/** Julian century conversion constant = 100 * days per year. */
const double JULIAN_DAYS_PER_CENTURY = 36525.0;

/** Seconds in one day. */
const double SECONDS_PER_DAY = 86400.0;

/** Our default epoch. The Julian Day which represents noon on 2000-01-01. */
const double J2000 = 2451545.0;

/**
 * Class to hold the results of ephemerides.
 * @author T. Alonso Albi - OAN (Spain)
 */
USTRUCT(BlueprintType)
struct FEphemeris
{
	GENERATED_BODY()

public:
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
//An actor based calendar system for tracking date + time, and Sun/Moon rotation/phase.
UCLASS(BlueprintType)
class ASkyManager : public AActor
{
	GENERATED_BODY()

public:
	ASkyManager(const class FObjectInitializer& ObjectInitializer);

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	ATimeManager* TimeManager;

	/** The set of twilights to calculate (types of rise/set events). */
	enum TWILIGHT {
		/**
		 * Event ID for calculation of rising and setting times for astronomical
		 * twilight. In this case, the calculated time will be the time when the
		 * center of the object is at -18 degrees of geometrical elevation below the
		 * astronomical horizon. At this time astronomical observations are possible
		 * because the sky is dark enough.
		 */
		TWILIGHT_ASTRONOMICAL,
		/**
		 * Event ID for calculation of rising and setting times for nautical
		 * twilight. In this case, the calculated time will be the time when the
		 * center of the object is at -12 degrees of geometric elevation below the
		 * astronomical horizon.
		 */
		 TWILIGHT_NAUTICAL,
		 /**
		  * Event ID for calculation of rising and setting times for civil twilight.
		  * In this case, the calculated time will be the time when the center of the
		  * object is at -6 degrees of geometric elevation below the astronomical
		  * horizon.
		  */
		  TWILIGHT_CIVIL,
		  /**
		   * The standard value of 34' for the refraction at the local horizon.
		   */
		   HORIZON_34arcmin
	};

	/** The set of events to calculate (rise/set/transit events). */
	enum EVENT {
		/** Rise. */
		RISE,
		/** Set. */
		SET,
		/** Transit. */
		TRANSIT
	};


	/** The set of phases to compute the moon phases. */
	class MOONPHASE {
		/** New Moon phase. */
		float NEW_MOON = 0,
			/** Crescent quarter phase. */
			CRESCENT_QUARTER = 0.25,
			/** Full Moon phase. */
			FULL_MOON = 0.5,
			/** Descent quarter phase. */
			DESCENT_QUARTER = 0.75;

		/** Phase name. */
		FString phaseName;
		/** Phase value. */
		double phase;

	private:
		MOONPHASE(FString name, double ph) {
			phaseName = name;
			phase = ph;
		}
	};

	/** Input values. */
private:
	double jd_UT = 0, t = 0, obsLon = 0, obsLat = 0, TTminusUT = 0;
	TWILIGHT twilight = HORIZON_34arcmin;




	/** Ephemeris for the Sun and Moon bodies. */
public:
	FEphemeris* sun;// { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	FEphemeris* moon;// { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	/** Moon's age in days as an independent variable. */
	double moonAge;

	//XXX Added new fields for moon
/** Moon illumination percentage (0-1), Position angle of axis, Bright Limb angle, Paralactic angle*/

	double moonIll, moonP, moonBL, moonPar;
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		float moonIll_out;
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		float moonP_out;
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		float moonBL_out;
	UPROPERTY(BlueprintReadOnly, Category = "TimeManager")
		float moonPar_out;

	//XXX Added constant as is used at multiple places
	/** Lunar cycle length in days*/
	double LUNAR_CYCLE_DAYS = 29.530588853;


	// Formulae here is a simplification of the expansion from 
	// "Planetary Programs and Tables" by Pierre Bretagnon and
	// Jean-Louis Simon, Willman-Bell, 1986. This source also 
	// have expansions for ephemerides of planets
private:
	const double sun_elements[26][4] = {
	 { 403406.0, 0.0, 4.721964, 1.621043 },
	{ 195207.0, -97597.0, 5.937458, 62830.348067 },
	{ 119433.0, -59715.0, 1.115589, 62830.821524 },
	{ 112392.0, -56188.0, 5.781616, 62829.634302 },
	{ 3891.0, -1556.0, 5.5474, 125660.5691 },
	{ 2819.0, -1126.0, 1.512, 125660.9845 },
	{ 1721.0, -861.0, 4.1897, 62832.4766 },
	{ 0.0, 941.0, 1.163, .813 },
	{ 660.0, -264.0, 5.415, 125659.31 },
	{ 350.0, -163.0, 4.315, 57533.85 },
	{ 334.0, 0.0, 4.553, -33.931 },
	{ 314.0, 309.0, 5.198, 777137.715 },
	{ 268.0, -158.0, 5.989, 78604.191 },
	{ 242.0, 0.0, 2.911, 5.412 },
	{ 234.0, -54.0, 1.423, 39302.098 },
	{ 158.0, 0.0, .061, -34.861 },
	{ 132.0, -93.0, 2.317, 115067.698 },
	{ 129.0, -20.0, 3.193, 15774.337 },
	{ 114.0, 0.0, 2.828, 5296.67 },
	{ 99.0, -47.0, .52, 58849.27 },
	{ 93.0, 0.0, 4.65, 5296.11 },
	{ 86.0, 0.0, 4.35, -3980.7 },
	{ 78.0, -33.0, 2.75, 52237.69 },
	{ 72.0, -32.0, 4.5, 55076.47 },
	{ 68.0, 0.0, 3.23, 261.08 },
	{ 64.0, -10.0, 1.22, 15773.85 }
	};

public:
	// The current Local Solar Time (in minutes)
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float SolarTime = 0.0f;

	// The current Local Clock Time value (in minutes)
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float LocalClockTime = 0.0f;

	// The current Time Correction factor
	UPROPERTY(BlueprintReadOnly, Category = "Sun Debug")
		float TimeCorrection = 0.0f;

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
		float JulianDateonTTscale = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcLongitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcLatitude = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcDistance = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float EcDistanceRadii = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartL = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartM = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float PartF = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarPhase_Fraction = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarPhase_Phase = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarPhase_Angle = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarParallax = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarAngularRadius = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Lunar Debug")
		float LunarAdjustedAngularRadious = 0.0f;


	// -------------------
	// PUBLIC FUNCTIONS
	// -------------------



	/**
* @Name: CalculateMoonPhase
* @Description: Calculates the moon phase for the current time and date.
*
* @return: FRotator - The moon rotation value for the current time.
*/
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		FRotator CalculateSunMoonAngle(float Latitude2, float Longitude2, float TimeZone, bool bIsDaylightSavingTime, int32 Year, int32 Month, int32 Day, int32 Hours, int32 Minutes, int32 Seconds);

	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		FEphemeris CalculateMoonAngle(float Latitude2, float Longitude2, float TimeZone, bool bIsDaylightSavingTime,
			int32 Year, int32 Month, int32 Day, int32 Hours, int32 Minutes, int32 Seconds,
			float& moonIll2, float& moonAngle, float& moonPhaseAngle, float& moonPhaseShadowAngle, float& moonBL2, float& moonPar2, float& SiderealTime2);
	UFUNCTION(BlueprintCallable, Category = "TimeManager")
		FEphemeris CalculateSunAngle(float Latitude2, float Longitude2, float TimeZone, bool bIsDaylightSavingTime, int32 Year, int32 Month, int32 Day, int32 Hours, int32 Minutes, int32 Seconds);



public:
	void InitSunMoonCalculator(int year, int month, int day, int h, int m, int s, double obsLon, double obsLat, float TimeZone);
	void setTwilight(TWILIGHT t);
	void calcSunAndMoon();
	static TArray<int32> getDate(double jd);
	static FString getDateAsString(double jd);
	static double normalizeRadians(double r);
	static void test();
	TArray<double> getMoonDiskOrientationAngles();


private:
	//double toJulianDay(int year, int month, int day, int h, int m, int s);
	void setUTDate(double jd);
	TArray<double> getSun();
	TArray<double> getMoon();
	FEphemeris* doCalc(TArray<double>  pos, bool geocentric);
	double obtainAccurateRiseSetTransit(double riseSetJD, EVENT index, int niter, bool sun);



private:
	//bool bIsCalendarInitialized = false;

	//FDateTime InternalTime;

	//// The UTC + DST TimeSpan difference vs current time
	//FTimespan SpanUTC;

	//// The Julian Day number for Jan 1, 2000 @ 12:00 UTC
	//double JD2000 = 2451545.0;

	//// The Julian Day number for Jan 1, 1900 @ 12:00 UTC
	//double JD1900 = 2415020.0;

	//double ElapsedJD1900 = 0.0;

	// Obliquity of the Ecliptic (as of 2000/01/01 - approximation, but fairly accurate)
	double EcObliquity = 23.4397;


};