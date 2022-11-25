// PlopsaRidePrediction_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <Windows.h>

#include "Ride.h"

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

int main()
{
    SetConsoleTitleA("Plopsa Ride Prediction v1.1.0"); // adds title to program window ALWAYS UPDATE VERSION AFTER MODIFICATION!
    // introduction at start
    cout << "Welkom bij de Plopsa Ride Prediction app versie 1.1.0.\n"; // ALWAYS UPDATE VERSION AFTER MODIFICATION!
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
        cout << "Zorg er steeds voor dat de minimumtemperatuur kleiner is dan de maximumtemperatuur en dat de windkracht een positief getal is.\n";
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

    Ride rth("Ride to Happiness", 6, 4, data);
    Ride rest("other rides", 5, 7, data);

    // end program
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
