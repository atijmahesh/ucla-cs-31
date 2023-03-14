//  tax.cpp
//  Atij Mahesh
//  905954423

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    //Inputs
    cout << "Name: ";
    string personsName;
    getline(cin, personsName);
    
    cout << "Taxable Income: ";
    double income;
    cin >> income;
    cin.ignore(10000, '\n');
    
    cout << "Occupation: ";
    string occupation;
    getline(cin, occupation);
    
    cout << "Number of children: ";
    int children;
    cin >> children;
    cin.ignore(10000, '\n');
    
    cout << "---" << endl;
    
    //catch error cases
    if(personsName == "") {
        cout << "You must enter a name" << endl;
        return 1;
    }
    else if(income < 0) {
        cout << "The taxable income must not be negative" << endl;
        return 1;
    }
    else if(occupation == "") {
        cout << "You must enter an occupation" << endl;
        return 1;
    }
    else if(children < 0) {
        cout << "The number of children must not be negative" << endl;
        return 1;
    }
    
    //constant variables
    double FIRST_TAX_BRACKET_MULTIPLIER = 0.04;
    int FIRST_TAX_BRACKET_LIMIT = 55000;
    double SECOND_TAX_BRACKET_MULTIPLIER = 0.07;
    double SPECIAL_SECOND_TAX_BRACKET_MULTIPLIER = 0.05; //for nurses and teachers
    int SECOND_TAX_BRACKET_LIMIT = 125000;
    int TAX_BRACKET_DIFFERENCE = 70000;
    double THIRD_TAX_BRACKET_MULTIPLIER = 0.093;
    int CHILD_TAX_REDUCTION = 200;
    double taxSum = 0.0;
    
    //tax calculation
    if(income > SECOND_TAX_BRACKET_LIMIT) {
        taxSum += (FIRST_TAX_BRACKET_LIMIT*FIRST_TAX_BRACKET_MULTIPLIER
                + THIRD_TAX_BRACKET_MULTIPLIER*(income - SECOND_TAX_BRACKET_LIMIT));
        if(occupation == "teacher" || occupation == "nurse")
            taxSum += SPECIAL_SECOND_TAX_BRACKET_MULTIPLIER*TAX_BRACKET_DIFFERENCE;
        else
            taxSum += SECOND_TAX_BRACKET_MULTIPLIER*TAX_BRACKET_DIFFERENCE;
        
    }
    else if(income > FIRST_TAX_BRACKET_LIMIT) {
        taxSum += FIRST_TAX_BRACKET_LIMIT*FIRST_TAX_BRACKET_MULTIPLIER;
        if(occupation == "teacher" || occupation == "nurse")
            taxSum += (income-FIRST_TAX_BRACKET_LIMIT)*SPECIAL_SECOND_TAX_BRACKET_MULTIPLIER;
        else
            taxSum += (income-FIRST_TAX_BRACKET_LIMIT)*SECOND_TAX_BRACKET_MULTIPLIER;
    }
    else {
        taxSum += income*FIRST_TAX_BRACKET_MULTIPLIER;
    }
    
    //child tax reduction
    if(income < SECOND_TAX_BRACKET_LIMIT) {
        taxSum -= CHILD_TAX_REDUCTION*children;
        if(taxSum < 0)
            taxSum = 0;
    }
    
    //output
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << personsName << " would pay $" << taxSum << endl;
}
