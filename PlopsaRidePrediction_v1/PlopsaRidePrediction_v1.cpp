// PlopsaRidePrediction_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>

using namespace std;

vector<int> getNewInput() { // this function asks for new weather conditions if incorrect data were entered
    vector<int> newData = { 0, 0, 0 };
    cout << "Wat is de voorspelde mimimumtemperatuur (in graden C)?\n";
    int TminNew;
    cin >> TminNew;

    cout << "Wat is de voorspelde maximumtemperatuur (in graden C)?\n";
    int TmaxNew;
    cin >> TmaxNew;

    cout << "Wat is de voorspelde windkracht (in Beafort)?\n";
    int windkrachtNew;
    cin >> windkrachtNew;

    newData = { TminNew, TmaxNew, windkrachtNew };

    return newData;
}

double probability(vector<int> inputdata, bool morning) { // this function calculates the actual probability
    int Tmin = inputdata[0];
    double Tmax = inputdata[1];
    int wind = inputdata[2];
    double temperatureFactor;
    double windFactor;
    double probabilityOpen;

    //find influence of temperature
    if (Tmin > 6) {
        temperatureFactor = 0.99;
    } else {
        // update v1.0.1: no longer use Tmax, instead use T at 1 hour before Tmax would be reached
        if (Tmax < 7 && morning == false) {
            double temperature;
            temperature = (Tmax - Tmin) / 7 * 6 + Tmin;
            Tmax = temperature;
            //cout << temperature << "\n";
        }

        if (Tmax < 5) {

            temperatureFactor = -1 * pow((5 - Tmax), 0.33) * 0.25 + 0.6; // pow cannot handle negative numbers
        } else {
            temperatureFactor = pow((Tmax - 5), 0.33) * 0.25 + 0.6;
        }
        
        if (Tmax < 5) {
            temperatureFactor = temperatureFactor / (5 - Tmax);
        }

        if (temperatureFactor > 0.99) {
            temperatureFactor = 0.99;
        }

        if (temperatureFactor < 0.01) {
            temperatureFactor = 0.01;
        }
    }
    //cout << "Invloed temperatuur: " << temperatureFactor << "\n";

    // find windfactor    
    if (wind > 7) {
        windFactor = 0.01;
    }
    else
    {
        double windMatrix[2][8]; //define and fill windmatrix
        for (int i = 0;i < 8;i++) {
            windMatrix[0][i] = i;
        }

        for (int i = 0; i < 3; i++) {
            windMatrix[1][i] = 0.99;
        }

        windMatrix[1][3] = 0.95;
        windMatrix[1][4] = 0.90;
        windMatrix[1][5] = 0.60;
        windMatrix[1][6] = 0.30;
        windMatrix[1][7] = 0.10;

        windFactor = windMatrix[1][wind];
    }

    //cout << "Invloed wind: " << windFactor << "\n";

    probabilityOpen = temperatureFactor * windFactor;
    probabilityOpen = round(probabilityOpen * 100);
    if (probabilityOpen < 1) {
        probabilityOpen = 1;
    }

    return probabilityOpen;
}

double probabilityMorning(vector<int> inputdata) { // function that calculates the probability around opening time
    double Tmin = inputdata[0];
    double Tmax = inputdata[1];
    double temperature;
    temperature = (Tmax - Tmin) / 7 * 2.5 + Tmin; // update formula to calculate T at opening time
    int temperatureRound = round(temperature);
    vector<int>input = { temperatureRound, temperatureRound,inputdata[2] };
    bool isMorning = true;
    double morningProbability = probability(input, isMorning);

    if (temperature < 6) {
        morningProbability = round(morningProbability * 0.9); // real life experience shows a smaller chance for opening if T < 6°C
    }

    if (morningProbability < 1) {
        morningProbability = 1;
    }
    return morningProbability;
}

int main()
{
    SetConsoleTitleA("Plopsa Ride Prediction v1.0.4"); // adds title to program window ALWAYS UPDATE VERSION AFTER MODIFICATION!
    // introduction at start
    cout << "Welkom bij de Plopsa Ride Prediction app versie 1.0.4.\n"; // ALWAYS UPDATE VERSION AFTER MODIFICATION!
    cout << "Dit programma probeert te voorspellen hoe groot de kans is dat de grote attracties \n";
    cout << "zoals 'The Ride to Happiness' en 'Anubis The Ride' geopend zullen zijn tijdens uw bezoek.\n";
    cout << "\n";
    cout << "Om van start te gaan hebben we een aantal gegevens nodig:\n";
    cout << "- de voorspelde minimumtemperatuur\n";
    cout << "- de voorspelde maximumtemperatuur\n";
    cout << "- de voorspelde windkracht\n";
    cout << "\n";
    cout << "Let op: op dit moment werken enkel gehele getallen!\n";
    cout << "\n";
    cout << "Druk 'Enter' om te beginnen met het invullen van de gegevens.\n";
    cin.get(); // pauses program till enter

    // collect input
    cout << "Wat is de voorspelde mimimumtemperatuur (in graden C)?\n";
    int Tmin;
    cin >> Tmin;

    cout << "Wat is de voorspelde maximumtemperatuur (in graden C)?\n";
    int Tmax;
    cin >> Tmax;

    cout << "Wat is de voorspelde windkracht (in Beaufort)?\n";
    int windkracht;
    cin >> windkracht;

    // verify input data, ask for new if invalid
    /*cout << "Dit zijn de door jou ingevoerde gegevens:\n";
    cout << "- minimumtemperatuur: " << Tmin << " graden C\n";
    cout << "- maximumtemperatuur: " << Tmax << " graden C\n";
    cout << "- de windkracht: " << windkracht << " Bft\n";
    cout << "\n";*/

    if (Tmin > Tmax || windkracht < 0) {
        cout << "De gegevens die je zonet hebt ingevoerd zijn ongeldig. Gelieve deze opnieuw in te geven.\n";
        bool dataCorrect;
        dataCorrect = false;
        vector<int> newInput;

        while (dataCorrect == false) {
            newInput = getNewInput();
            Tmin = newInput[0];
            Tmax = newInput[1];
            windkracht = newInput[2];

            //verify again
            if (Tmin > Tmax || windkracht < 0) {
                cout << "De nieuwe gegevens zijn nog steeds ongeldig. Probeer Opnieuw.\n";
            }
            else {
                dataCorrect = true;
            }
        }
    }
    
    //calculate data
    vector<int> data = { Tmin, Tmax, windkracht };

    double waarschijnlijkheid;
    bool ochtend = false;
    waarschijnlijkheid = probability(data, ochtend);
    double waarschijnlijkheidOchtend = probabilityMorning(data);
    cout << "Je hebt " << waarschijnlijkheid << " procent kans dat de attracties gedurende de dag zullen openenen.\n";
    cout << "De kans dat de attracties openen bij parkopening bedraagt " << waarschijnlijkheidOchtend << " procent.\n";
    cout << "De kans dat 'The Ride to Happiness' opent bedraagt 0 procent.\n";
    cout << "\n";
    cout << "Druk op een willekeurige toets om af te sluiten...\n";
    system("pause");
    


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
