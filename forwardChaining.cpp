#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

carParts forwardChaining(int problem_num){

    // first check backward chaining output for incompatible results (no problem or error)

    if ( problem_num == 4 ){
        std::cout << "The car has no problems." << endl;
        return;

    } else if ( problem_num == -1 ){
        std::cout << "There was an error, try running the program again." << endl;
        
        return;
    }

    string variableList[4] = { "Problem with car", "FIX_1", "FIX_2", "FIX_3" };

    string clauseVariableList[62];

    // building clauseVariableList
    clauseVariableList[1] = "Problem with car";

    for ( int i = 2 ; i < 60 ; i += 4) {
        clauseVariableList[i]   = "";
        clauseVariableList[i+1] = "";
        clauseVariableList[i+2] = "";
        clauseVariableList[i+3] = "Problem with car";
    }

    // structures for rulebase
    typedef pair < string, int > pair_FIX;
    typedef pair < int, pair_FIX > pair_prob;
    //typedef pair < int, pair_prob > pair_rule;

    // create rule base
    map < int , pair_prob > ruleBase ;
    ruleBase.insert( pair <int , pair_prob > (  10, pair_prob ( 3 , pair_FIX( "FIX_1" , 1 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  20, pair_prob ( 2 , pair_FIX( "FIX_1" , 1 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  30, pair_prob ( 2 , pair_FIX( "FIX_2" , 2 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  40, pair_prob ( 2 , pair_FIX( "FIX_3" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  50, pair_prob ( 8 , pair_FIX( "FIX_1" , 1 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  60, pair_prob ( 8 , pair_FIX( "FIX_2" , 3 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  70, pair_prob ( 8 , pair_FIX( "FIX_3" , 4 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  80, pair_prob ( 1 , pair_FIX( "FIX_1" , 1 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > (  90, pair_prob ( 1 , pair_FIX( "FIX_2" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 100, pair_prob ( 1 , pair_FIX( "FIX_3" , 6 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 110, pair_prob ( 9 , pair_FIX( "FIX_1" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 120, pair_prob ( 7 , pair_FIX( "FIX_1" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 130, pair_prob ( 5 , pair_FIX( "FIX_1" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 140, pair_prob ( 5 , pair_FIX( "FIX_1" , 6 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 150, pair_prob ( 6 , pair_FIX( "FIX_1" , 5 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 160, pair_prob ( 6 , pair_FIX( "FIX_1" , 7 ) ) ) ) ;
    ruleBase.insert( pair <int , pair_prob > ( 170, pair_prob ( 6 , pair_FIX( "FIX_1" , 8 ) ) ) ) ;

    // create map of FIXs
    map <int, string> FIXNames;
    FIXNames.insert(pair< int, string  > ( 1 , "fix1" ) );
    FIXNames.insert(pair< int, string  > ( 2 , "fix2" ) );
    FIXNames.insert(pair< int, string  > ( 3 , "fix3" ) );
    FIXNames.insert(pair< int, string  > ( 4 , "fix4" ) );
    FIXNames.insert(pair< int, string  > ( 5 , "fix5" ) );
    FIXNames.insert(pair< int, string  > ( 6 , "fix6" ) );
    FIXNames.insert(pair< int, string  > ( 7 , "fix7" ) );
    FIXNames.insert(pair< int, string  > ( 8 , "fix8" ) );

    // create map of problem names
    map <int, string> problemNames;
    
    problemNames.insert(pair< int, string  > ( 1 , "problem1" ) );
    problemNames.insert(pair< int, string  > ( 2 , "problem2" ) );
    problemNames.insert(pair< int, string  > ( 3 , "problem3" ) );
    problemNames.insert(pair< int, string  > ( 5 , "problem4" ) );
    problemNames.insert(pair< int, string  > ( 6 , "problem5" ) );
    problemNames.insert(pair< int, string  > ( 7 , "problem6" ) );
    problemNames.insert(pair< int, string  > ( 8 , "problem7" ) );
    problemNames.insert(pair< int, string  > ( 9 , "problem8" ) );

    // create the fact base as a map
    map < string , int > factBase;

    // create conclusion variable queue
    queue <string> conclusionVariableQueue;

    // add the problem to the fact base
    factBase.insert(pair< string, int > ("Problem with car" , problem_num ) );

    conclusionVariableQueue.push( "Problem with car" );

    int ruleNum = 0;
    string newVariable;
    
    while ( !conclusionVariableQueue.empty() ){
        // iterate through clause variable list
        for ( int i = 1 ; i < 62 ; i++ ) {
            if ( clauseVariableList[i] == conclusionVariableQueue.front() ){
                // compute rule number from variable list number
                ruleNum = ( ( i / 4 ) + 1 ) * 10;
                
                // check problem against rule
                //if ( problem_num == ruleBase[ruleNum].first ){
                if ( factBase["Problem with car"] == ruleBase[ruleNum].first ){
                    
                    factBase.insert( ruleBase[ruleNum].second );

                    newVariable = ruleBase[ruleNum].second.first;

                    conclusionVariableQueue.push( newVariable );
                }
            }
        }
        // remove top variable from queue
        conclusionVariableQueue.pop();
    }

    // return results to user
    std::cout << "Recommended FIX for " << problemNames[ factBase["Problem with car"] ] << " is:" << endl;
    int FIXs = factBase.size() - 1;

    if ( FIXs > 0 ){
        std::cout << "\t" << FIXNames[ factBase["FIX_1"]] << endl;
    }
    
    if ( FIXs > 1 ){
        std::cout << "\t" << FIXNames[ factBase["FIX_2"]] << endl;
    }
    
    if ( FIXs > 2 ){
        std::cout << "\t" << FIXNames[ factBase["FIX_3"]] << endl;
    }
    return;
















}
