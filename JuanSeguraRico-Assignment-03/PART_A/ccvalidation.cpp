//
// Created by Juan Segura Rico on 6/29/23.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

bool isValid(const string& cc) {
    if (cc.length() > 16 || cc.length() < 13) {
        return false;
    }
    int evens = 0, odds = 0;
    for (int i = 1, j = cc.length() - 1; j >= 0; j--, i++) {
        int icc = cc[j] - '0';							// convert string digit to int
        odds += (i % 2 != 0) ? icc : 0;					// if odd, add to odds variable
        evens += ((i % 2 == 0 && icc < 5)
                  ? icc * 2									// if even and 2 * icc is a single digit, add 2 * icc to evens variable
                  : (i % 2 == 0 && icc >= 5					// else if even and more than 2 digits
                     ? (((icc * 2 % 10) + (icc / 5 % 10)))	// add last digit to first digit
                     : 0));									// else not even, add 0
    }
    return (odds + evens) % 10 == 0;
}

int main()
{

    vector<string> cardNumbers = {
            "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
            "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
            "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
            "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
            "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
            "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
            "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
            "5556551555555557", "6011316011016011"
    };

    int i;
    vector<string>::iterator itr;

    for (i = 1, itr = cardNumbers.begin(); itr != cardNumbers.end(); ++itr, i++) {
        cout << setw(2) << i << " "
             << setw(17) << *itr
             << ((isValid(*itr)) ? " is valid" : " is not valid") << endl;
    }

    return 0;
}