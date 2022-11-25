#include "Ride.h"
#include <vector>

// Ride contsructor
Ride::Ride(string name, int tMin, int windMax, vector<int> weather) {
	//cout << "test " << name << tMin << windMax << weather[0] << weather[1] << weather[2] << "\n";
	SetData(name, tMin, windMax, weather);
	PredictRide();
}

// SetData function
void Ride::SetData(string name, int tMin, int windMax, vector<int> weather) {
	rideName = name;
	minTemp = tMin;
	maxWind = maxWind;
	lowTemp = weather[0];
	highTemp = weather[1];
	wind = weather[2];
}

// This function will process all the data and print the results to the screen when calculations are done
void Ride::PredictRide() {
	double probability = CalculateProbability(false);
	double probablilityMorning = CalculateProbability(true);

	if (getRideName() == "other rides") {
		cout << "De kans dat de andere atracties openen bedraagt " << probability << " procent.\n";
		cout << "De kans dat deze bij parkopening openen bedraagt " << probablilityMorning << " procent.\n";
		return;
	}

	cout << "Je hebt " << probability << " procent kans dat " << getRideName() << " zal openen.\n";
	cout << "De kans dat deze attractie opent bij parkopening bedraagt " << probablilityMorning << " procent.\n";

}

// This function actually calculates the probability
double Ride::CalculateProbability(bool isMorning) {
	int lowestTemperature = getLowTemp();
	double highestTemperature = getHighTemp();
	int windForce = getWind();
	int minimumTemperature = getMinTemp();
	double temperatureFactor;
	double windFactor;
	double probabilityOpen;

	// calculate influence of temperature
	if (lowestTemperature > minimumTemperature + 2) {
		temperatureFactor = 0.99;
	} else {
		// update v1.0.1: no longer use Tmax, instead use T at 1 hour before Tmax would be reached
		if (highestTemperature < highestTemperature + 2 && isMorning == false){
			highestTemperature = (highestTemperature - lowestTemperature) / 7 * 6 + lowestTemperature;
		}

		// add some code for probabilities in the morning
		if (isMorning == true) {
			highestTemperature = (highestTemperature - lowestTemperature) / 7 * 2.5 + lowestTemperature;// update formula to calculate T at opening time
			lowestTemperature = round(highestTemperature);
			highestTemperature = lowestTemperature;
		}

		if (highestTemperature < minimumTemperature) {
			temperatureFactor = -1 * pow((minimumTemperature - highestTemperature), 0.33) * 0.25 + 0.6; // pow cannot handle negative numbers
			temperatureFactor = temperatureFactor / (minimumTemperature - highestTemperature);
		} else {
			temperatureFactor = pow((highestTemperature - minimumTemperature), 0.33) * 0.25 + 0.6;
		}

		if (temperatureFactor > 0.99) {
			temperatureFactor = 0.99;
		}

		if (temperatureFactor < 0.01) {
			temperatureFactor = 0.01;
		}
	}

	// calculate influence of wind

	double windMatrix[2][8]; //define and fill windmatrix
	for (int i = 0;i < 8;i++) {
		windMatrix[0][i] = i;
	}

	for (int i = 0; i < 3; i++) {
		windMatrix[1][i] = 0.99;
	}

	windMatrix[1][3] = 0.90;
	windMatrix[1][4] = 0.80;
	windMatrix[1][5] = 0.50;
	windMatrix[1][6] = 0.25;
	windMatrix[1][7] = 0.05;

	if (windForce > 7) {
		windFactor = 0.01;
	}
	else
	{
		windFactor = windMatrix[1][windForce];
	}

	probabilityOpen = temperatureFactor * windFactor;
	probabilityOpen = round(probabilityOpen * 100);

	if (isMorning == true && lowestTemperature < minimumTemperature + 1) {
		probabilityOpen = round(probabilityOpen * 0.9);
	}

	if (probabilityOpen < 1) {
		probabilityOpen = 1; // set opening chance to minimum 1%
	}

	return probabilityOpen;
}
