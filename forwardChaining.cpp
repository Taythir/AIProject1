#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <map>

using namespace std;

carParts forwardChaining(int num){

    // check to see if there arent any problems to solve, or if program run error exists

    if ( num == 4 ){
        cout << "The car has no problems." << endl;
        return;

    } else if ( num == -1 ){
        cout << "There was an error, try running the program again." << endl;
        
        return;
    }

    string VarList[4] = { "Problem with car", "Have certified mechanic replace the circuit", "Replace coil", "Replace fuel filter" };

    //a little confused on my size of this clauseVarList
    string clauseVarList[70];

    // building clauseVarList
    clauseVarList[1] = "Problem with car";

    for ( int i = 2 ; i < 60 ; i += 4) {
        clauseVarList[i]   = "";
        clauseVarList[i+1] = "";
        clauseVarList[i+2] = "";
        clauseVarList[i+3] = "Problem with car";
    }

    // rulebase funcs
    typedef pair < string, int > pair_FIX;
    typedef pair < int, pair_FIX > pair_prob;

    //*********************************************************//
    //The idea here was to utilize the map function to speed up 
    //the program, because it allows us to quickly access the value
    //through a key. This also helps keep duplications out of the program.
    //*********************************************************//


    // creating the rule base through a map
    map <int , pair_prob> ruleBase ;
    ruleBase.insert(pair< int,pair_prob > ( 10, pair_prob (3, pair_FIX( "Have certified mechanic replace the circuit" , 1 ))));
    ruleBase.insert(pair< int,pair_prob > ( 20, pair_prob (2, pair_FIX( "Have certified mechanic replace the circuit" , 1 ))));
    ruleBase.insert(pair< int,pair_prob > ( 30, pair_prob (2, pair_FIX( "Replace coil" , 2 ))));
    ruleBase.insert(pair< int,pair_prob > ( 50, pair_prob (8, pair_FIX( "Have certified mechanic replace the circuit" , 1 ))));
    ruleBase.insert(pair< int,pair_prob > ( 60, pair_prob (8, pair_FIX( "Replace coil" , 3 ))));
    ruleBase.insert(pair< int,pair_prob > ( 70, pair_prob (8, pair_FIX( "Replace fuel filter" , 4 ))));
    ruleBase.insert(pair< int,pair_prob > ( 80, pair_prob (1, pair_FIX( "Have certified mechanic replace the circuit" , 1 ))));
    ruleBase.insert(pair< int,pair_prob > ( 90, pair_prob (1, pair_FIX( "Replace coil" , 5 ))));
    ruleBase.insert(pair< int,pair_prob > (100, pair_prob (1, pair_FIX( "Replace fuel filter" , 6 ))));
    ruleBase.insert(pair< int,pair_prob > (110, pair_prob (9, pair_FIX( "Have certified mechanic replace the circuit" , 5 ))));
    ruleBase.insert(pair< int,pair_prob > (120, pair_prob (7, pair_FIX( "Have certified mechanic replace the circuit" , 5 ))));
    ruleBase.insert(pair< int,pair_prob > (130, pair_prob (5, pair_FIX( "Have certified mechanic replace the circuit" , 5 ))));
    ruleBase.insert(pair< int,pair_prob > (140, pair_prob (5, pair_FIX( "Have certified mechanic replace the circuit" , 6 ))));
    ruleBase.insert(pair< int,pair_prob > (150, pair_prob (6, pair_FIX( "Have certified mechanic replace the circuit" , 5 ))));
    ruleBase.insert(pair< int,pair_prob > (160, pair_prob (6, pair_FIX( "Have certified mechanic replace the circuit" , 7 ))));
    ruleBase.insert(pair< int,pair_prob > (170, pair_prob (6, pair_FIX( "Have certified mechanic replace the circuit" , 8 ))));

    // creating a map with the list of problems names
    map <int, string> problemNames;
    
    problemNames.insert(pair< int,string > (1 , "Fuel Filter"));
    problemNames.insert(pair< int,string > (2 , "Power Booster"));
    problemNames.insert(pair< int,string > (3 , "Power Assist"));
    problemNames.insert(pair< int,string > (5 , "Brake Fluid"));
    problemNames.insert(pair< int,string > (6 , "Lug Nuts"));
    problemNames.insert(pair< int,string > (7 , "Torque Nut"));
    problemNames.insert(pair< int,string > (8 , "Strut and Spring"));
    problemNames.insert(pair< int,string > (9 , "Bent Part"));
    
    // creating a map of fixes that will be recommended to user after problem is known
    map <int, string> FIXNames;
    FIXNames.insert(pair< int,string >(1 , "Have certified mechanic replace the part"));
    FIXNames.insert(pair< int,string >(2 , "Replace coil"));
    FIXNames.insert(pair< int,string >(3 , "Replace fuel filter"));
    FIXNames.insert(pair< int,string >(4 , "Replace brake fluid"));
    FIXNames.insert(pair< int,string >(5 , "Replace lug nuts"));
    FIXNames.insert(pair< int,string >(6 , "Replace torque nut"));
    FIXNames.insert(pair< int,string >(7 , "Replace strut and spring"));
    FIXNames.insert(pair< int,string >(8 , "Have a mechanic replace bent part"));

    // creating the fact base through a map
    map <string , int> factBase;

    // creating conclusion variable quueue
    queue <string> conclusionVarQueue;

    // add the problem found to the fact base
    factBase.insert(pair< string, int > ("Problem with car" , num ) );

    conclusionVarQueue.push( "Problem with car" );

    int ruleNum = 0;
    string newVar;
    
    while ( !conclusionVarQueue.empty() ){
        // iterate through clause Var list
        for (int i = 1 ; i < 62 ; i++) {
            if (clauseVarList[i] == conclusionVarQueue.front()){
                // compute rule number from Var list number
                //use equation below we learned in class for finding rule num
                ruleNum = (( i / 4 ) + 1) * 10;
                
                // check problem against rule base rule number we have calculated
                if (factBase["Problem with car"] == ruleBase[ruleNum].first){
                    
                    factBase.insert( ruleBase[ruleNum].second );

                    newVar = ruleBase[ruleNum].second.first;

                    conclusionVarQueue.push( newVar );
                }
            }
        }
        // pop var from queuee
        conclusionVarQueue.pop();
    }

    // return results to user
    cout << "Recommended fix for " << problemNames[factBase["problem with car"]] << " is:" << endl;
    int FIXs = factBase.size() - 1;

    if ( FIXs > 0 ){
        cout << "\t" << FIXNames[factBase["Have certified mechanic replace the circuit"]] << endl;
    }
    
    if ( FIXs > 1 ){
        cout << "\t" << FIXNames[factBase["Replace coil"]] << endl;
    }
    
    if ( FIXs > 2 ){
        cout << "\t" << FIXNames[factBase["Replace fuel filter"]] << endl;
    }
    return;
}
