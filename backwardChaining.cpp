#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

int main() {
    struct carParts
    {
        bool broken = false;
        std::string name;
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
    
    std::string answer;
    std::cout << "Does the car start on it's own?: Y or N" << std::endl;
    std::cin >> answer;
    if (answer == "Y")
    {
        variableList[0] = true;
        std::cout << "Does the car stall?: Y or N" << std::endl;
        std::cin >> answer;
        if (answer == "Y")
        {
            std::cout << "Does the car stall on the key release";
        }
    } 
    else
    {
        variableList[0] = false;
        std::cout << "Does the car start with a jump?: Y or N" << std::endl;
        std::cin >> answer;
        if (answer == "Y")
        {
            battery.broken = true;
            std::cout << "Problem with " << battery.name << std::endl;
        }
    }
    return 0;
}
