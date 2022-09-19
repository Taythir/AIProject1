#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    struct carParts
    {
        bool broken = false;
        string name;
    };
    
    carParts fuelFilter, stuckChoke, powerBooster, powerAssist, brakeFluid, lugNuts, torqueNut, strutSpring, bentPart, toeCamber, suspension, tireInflation, pump, battery;
    
    fuelFilter.name = "Fuel Filter";
    powerBooster.name = "Power Booster";
    powerAssist.name = "Power Assist";
    brakeFluid.name = "Brake Fluid";
    lugNuts.name = "Lug Nuts";
    torqueNut.name = "Torque Nut";
    strutSpring.name = "Strut and Spring";
    bentPart.name = "Bent Part";
    toeCamber.name = "Toe and Camber";
    suspension.name = "Suspension";
    tireInflation.name = "Tire Inflation";
    pump.name = "Pump";
    battery.name = "Car Battery";
    
    carParts conclusionList[30] = {fuelFilter, powerBooster, powerAssist,  brakeFluid, lugNuts, torqueNut, strutSpring, bentPart, toeCamber, suspension, tireInflation, pump, battery};
    
    bool carStarts, carStalls, carNeedsJump;
    bool variableList[30] = {carStarts, carStalls, carNeedsJump};
    
    string answer;
    cout << "Does the car start on it's own?: Y or N" << std::endl;
    cin >> answer;
    if (answer == "Y")
    {
        variableList[0] = true;
        cout << "Does the car stall?: Y or N" << endl;
        cin >> answer;
        if (answer == "Y")
        {
            cout << "Does the car stall on the key release";
        }
    } 
    else
    {
        variableList[0] = false;
        cout << "Does the car start with a jump?: Y or N" << endl;
        cin >> answer;
        if (answer == "Y")
        {
            battery.broken = true;
            cout << "Problem with " << battery.name << endl;
        }
    }
    return 0;
}
