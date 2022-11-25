#pragma once

#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <vector>

using namespace std;

class Ride
{
private:
	string rideName;
	int minTemp; // minimum temp for ride to operate
	int maxWind; // maximum wind force for ride to operate
	int lowTemp; // lowest temperature of the day
	int highTemp; // highest temperature of the day
	int wind; // wind force of the day

public:
	Ride(string name, int tMin, int windMax, vector<int> weather);

	void SetData(string name, int tMin, int windMax, vector<int> weather);

	void PredictRide();

	double CalculateProbability(bool isMorning);

	// define getters:
	string getRideName() { return rideName; }
	int getMinTemp() { return minTemp; }
	int getMaxWind() { return maxWind; }
	int getLowTemp() { return lowTemp; }
	int getHighTemp() { return highTemp; }
	int getWind() { return wind; }
};

#endif

