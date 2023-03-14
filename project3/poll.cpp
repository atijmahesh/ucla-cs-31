//  poll.cpp
//  Atij Mahesh
//  905954423

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

bool isValidUppercaseStateCode(string);
bool isValidPollString(string);
int countSeats(string, char, int&);
int recurCountSeats(string, char, int&);


int main() {
    int seats;
    string pollData;
    string party;
    
    cout << "Please enter Poll Data:" << endl;
    getline(cin, pollData);
    cout << "Which party (first letter) do you inqure about?" << endl;
    getline(cin, party);
    
    //case to catch weird user party input
    if(party.length() != 1) {
        cout << "Sorry! That party input isn't valid." << endl;
        return 1;
    }
    
    char partyChar = party.at(0);
    int output = countSeats(pollData, partyChar, seats);
    if(output == 1)
        cout << "Sorry! That isn't valid poll data." << endl;
    else if (output == 2)
        cout << "Sorry! That party has not been formed (yet)." << endl;
    else if(output == 0)
        cout << "The predicted number of seats for party " << party << " is " << seats << "." << endl;
}

bool isValidUppercaseStateCode(string stateCode) {
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isValidPollString(string pollData) {
    //find comma and calculate forecast length
    string delimiter = ",";
    int nearestCommaPosition = (int)pollData.find(delimiter);
    int stateForecastLength = 0;
    if(nearestCommaPosition == -1) stateForecastLength = pollData.length();
    else stateForecastLength = nearestCommaPosition;
    
    if(pollData.length() == 0) return true; //end of parsing
    
    //weird cases of strange comma positioning
    if(pollData.at(0) == ',' || pollData.at(pollData.length()-1) == ',' )
        return false;
    
    //weird case of empty string input which is valid
    if(stateForecastLength == 0) return isValidPollString(pollData.substr(1));
    
    if(stateForecastLength < 2) return false; //one char forecast
    
    //make string uppercase
    transform(pollData.begin(), pollData.end(), pollData.begin(), ::toupper);
    
    if(isValidUppercaseStateCode(pollData.substr(0, 2))) {
        for(int i = 2; i<stateForecastLength-1; i+=2) {
            //check if first number is a digit
            if(isdigit(pollData.at(i))) {
                //if the second is a letter, its valid so far
                if(isalpha(pollData.at(i+1))) {
                    continue;
                }
                //if the second is a number, check if the next is a letter
                if(isdigit(pollData.at(i+1)) && i<pollData.length()-2) {
                    if(isalpha(pollData.at(i+2))) {
                        i++;
                        continue;
                    }
                }
            }
            return false;
        }
        if(nearestCommaPosition == -1) return true; //end of parsing
        return isValidPollString(pollData.substr(nearestCommaPosition+1));
    }
    return false;
}


int countSeats(string pollData, char party, int& seatCount) {
    if(!isValidPollString(pollData)) return 1; //return 1 case
    if(!isalpha(party)) return 2; //return 2 case
    seatCount = 0;
    return recurCountSeats(pollData, party, seatCount);
}

int recurCountSeats(string pollData, char party, int& seatCount) {
    if(pollData.length() == 0) return 0; //end of parsing

    string partyString(1, toupper(party)); //make char an uppercase string
    transform(pollData.begin(), pollData.end(), pollData.begin(), ::toupper); //make string uppercase
    string delimiter = ",";
    int nearestCommaPosition = (int)pollData.find(delimiter);
    if(pollData.length() == 2) return 0;
    
    
    if(nearestCommaPosition == 2) //case of just state code
        return recurCountSeats(pollData.substr(nearestCommaPosition+1), party, seatCount);
    
    int firstInstanceOfParty = (int)pollData.find(partyString);
    if(firstInstanceOfParty < 2 && firstInstanceOfParty != -1) { //case where statecode shares same letter
        firstInstanceOfParty = (int)(pollData.substr(2).find(partyString));
    }
    
    if(firstInstanceOfParty == -1) return 0; //end of parsing
    
    
    if(firstInstanceOfParty > nearestCommaPosition && nearestCommaPosition != -1) //no party in forecast
        return recurCountSeats(pollData.substr(nearestCommaPosition+1), party, seatCount);
    else {
        if(isdigit(pollData.at(firstInstanceOfParty-2)))
            seatCount += stoi(pollData.substr(firstInstanceOfParty-2, firstInstanceOfParty));
        else
            seatCount += stoi(pollData.substr(firstInstanceOfParty-1, firstInstanceOfParty));
        if(nearestCommaPosition-firstInstanceOfParty >= 2 || (nearestCommaPosition == -1 && pollData.length() - firstInstanceOfParty >= 2)) {
            return recurCountSeats(pollData.substr(0,2) +
                              pollData.substr(firstInstanceOfParty+1), party, seatCount);
        }
        if(nearestCommaPosition != -1)
            return recurCountSeats(pollData.substr(nearestCommaPosition+1), party, seatCount);
    }
    return 0;
}
