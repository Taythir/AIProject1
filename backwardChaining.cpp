#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

void backwardChaining() {
    
    carParts fuelFilter, stuckChoke, powerBooster, powerAssist, brakeFluid, lugNuts, torqueNut, strutSpring, bentPart, toeCamber, suspension, tireInflation, pump, battery, starter, dirtyTerminals, ignitionCircuit, coil, brakeLines;
    
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
    starter.name = "Starter";
    dirtyTerminals.name = "Dirty Battery Terminals";
    ignitionCircuit.name = "Ignition Circuit";
    coil.name = "Cracked Coil";
    stuckChoke.name = "Stuck Choke";
    brakeLines.name = "Brake Lines";
    
    carParts conclusionList[30] = {fuelFilter, powerBooster, powerAssist,  brakeFluid, lugNuts, torqueNut, strutSpring, bentPart, toeCamber, suspension, tireInflation, pump, battery, starter, dirtyTerminals, ignitionCircuit, coil, stuckChoke, brakeLines};
    
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
            cout << "Does the car stall on the key release: Y or N" << endl;
            cin >> answer;
            if (answer == "Y")
            {
                ignitionCircuit.broken = true;
                cout << "Problem with " << ignitionCircuit.name;
            }
            else
            {
                cout << "Does the car stall in the rain?: Y or N" << endl;
                cin >> answer;
                if (answer == "Y")
                {
                    coil.broken = true;
                    cout << "Problem with " << coil.name;
                }
                else
                {
                    cout << "Does the car stall when it's warm?: Y or N" << endl;
                    cin >> answer;
                    if (answer == "Y")
                    {
                        fuelFilter.broken = true;
                        cout << "Problem with " << fuelFilter.name;
                    }
                    else
                    {
                        stuckChoke.broken = true;
                        cout << "Problem with " << stuckChoke.name;
                    }
                }
            }
        }
        else 
        {
            cout << "Do the brakes stop the car?: Y or N" << endl;
            cin >> answer;
            if (answer == "Y")
            {
                cout << "Is the steering wheel loose?: Y or N?" << endl;
                cin >> answer;
                if (answer == "Y")
                {
                    cout << "Are the lug nuts loose?: Y or N" << endl;
                    cin >> answer;
                    if (answer == "Y")
                    {
                        lugNuts.broken = true;
                        cout << "Problem with " << lugNuts.name;
                    }
                    else
                    {
                        cout << "Is axle nut loose?: Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y")
                        {
                            torqueNut.broken = true;
                            cout << "Problem with " << torqueNut.name;
                        }
                        else
                        {
                            strutSpring.broken = true;
                            cout << "Problem with " << strutSpring.name;
                        }
                    }
                }
                else
                {
                    cout << "Does the steering wheel pull?: Y or N" << endl;
                    cin >> answer;
                    if (answer == "Y")
                    {
                        cout << "Has the car been damaged by impact?: Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y")
                        {
                            bentPart.broken = true;
                            cout << "Problem with " << bentPart.name;
                        }
                        else
                        {
                            cout << "Is there uneven tire wear?: Y or N" << endl;
                            cin >> answer;
                            if (answer == "Y")
                            {
                                toeCamber.broken = true;
                                cout << "Problem with " << toeCamber.name;
                            }
                            else
                            {
                                suspension.broken = true;
                                cout << "Problem with " << suspension.name;
                            }
                        }
                    }
                    else
                    {
                        cout << "Is it hard to steer?: Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y")
                        {
                            tireInflation.broken = true;
                            cout << "Problem with " << tireInflation.name;
                        }
                        else
                        {
                            cout << "Is it steering noisy?: Y or N" << endl;
                            cin >> answer;
                            if (answer == "Y")
                            {
                                pump.broken = true;
                                cout << "Problem with " << pump.name;
                            }
                            else
                            {
                                cout << "No Problem found" << endl;
                            }
                        }
                    }
                }
            }
            else 
            {
                cout << "Do the brakes work when the pedal is to the floor?: Y or N" << endl;
                cin >> answer;
                if (answer == "Y")
                {
                    cout << "Is brake fluid level okay?: Y or N" << endl;
                    cin >> answer;
                    if (answer == "Y")
                    {
                        cout << "Is brake warning light on?: Y or N" << endl;
                        cin >> answer;
                        if (answer == "Y")
                        {
                            powerBooster.broken = true;
                            cout << "Problem with " << powerBooster.name;
                        }
                        else
                        {
                            powerAssist.broken = true;
                            cout <<"Problem with " << powerAssist.name;
                        }
                    }
                    else
                    {
                        brakeFluid.broken = true;
                        cout << "Problem with " << brakeFluid.name;
                    }
                }
                else
                {
                    brakeLines.broken = true;
                    cout << "Problem with " << brakeLines.name;
                }
            }
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
        else
        {
            cout << "Are terminals clean?: Y or N" << endl;
            cin >> answer;
            if (answer == "Y")
            {
                starter.broken = true;
                cout << "Problem with " << starter.name << endl;
            }
            else
            {
                dirtyTerminals.broken = true;
                cout << "Problem with " << dirtyTerminals.name << endl;
            }
        }
    }

}
