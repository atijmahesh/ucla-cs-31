#include "utilities.h"
#include <iostream>
#include <cstring>

using namespace std;

int playOneRound(const char words[][7], int nWords, int wordnum);

int main() {
    const int MAXWORDS = 9000;
    const int MAXWORDLEN = 6;
    const char WORDFILENAME[] = "/Users/atijmahesh/Desktop/CS_31/game/words.txt";
    char wordList[MAXWORDS][MAXWORDLEN+1];
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);
    
    
    //weird error cases
    if(nWords < 1) {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }
    else if(nWords > MAXWORDS) {
        cout << "Number of words exceeds Max Words!" << endl;
        return 1;
    }
    
    //start of game
    cout << "How many rounds do you want to play? ";
    int roundNum;
    cin >> roundNum;
    if(roundNum < 0) {
        cout << "The number of rounds must be positive." << endl;
        return 1;
    }
    cout << "\n";
    
    int minimum = 0;
    int maximum = 0;
    double totalTryCount = 0;
    
    //game loop
    for(int i = 1; i<= roundNum; i++) {
        int wordnum = randInt(0, nWords-1);
        char hiddenword[MAXWORDLEN+1];
        strcpy(hiddenword,wordList[wordnum]);
        int wordlength = strlen(hiddenword);
        cout << "Round " << i << "\nThe hidden word is " << wordlength << " letters long." << endl;
        
        //play one round
        int numOfTries = playOneRound(wordList, nWords, wordnum);
        if(numOfTries == -1) { //weird argument passing
            cout << "Bad argument pass to game method. Sorry." << endl;
            return 1;
        }
        if(numOfTries == 1) cout << "You got it in 1 try." << endl;
        else cout << "You got it in " << numOfTries << " tries." << endl;
        totalTryCount += numOfTries;
        
        //min and max calcs
        if(i == 1) {
            maximum = numOfTries;
            minimum = numOfTries;
        }
        else {
            if(numOfTries < minimum)
                minimum = numOfTries;
            else if(numOfTries > maximum)
                maximum = numOfTries;
        }
        //final print statement
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Average: " << totalTryCount/i << ", minimum: " << minimum << ", maximum: " << maximum << endl;
        cout << "\n";
    }
}

int playOneRound(const char words[][7], int nWords, int wordnum) {
    cerr << words[wordnum] << endl;
    //weird input case
    if(nWords < 0 || wordnum < 0 || wordnum >= nWords) return -1;
    int tryCount = 0;
    for(;;) {
        const int MAXPROBEWORDSIZE = 100;
        const int MAXWORDSIZE = 7;
        char probeWord[MAXPROBEWORDSIZE+1];
        char hiddenword[MAXWORDSIZE];
        strcpy(hiddenword,words[wordnum]);
        int hiddenWordLen = strlen(hiddenword);
        
        //get probe word info
        cout << "Probe word: ";
        cin >> probeWord;
        int probeWordLen = strlen(probeWord);
        if(probeWordLen > 6 || probeWordLen < 4) {
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        bool badWordIndicator = false;
        for(int i = 0; i<probeWordLen; i++) {
            if(!islower(probeWord[i])) {
                cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
                badWordIndicator = true;
                break;
            }
        }
        if(badWordIndicator) continue;
        
        //check if word is in word bank
        bool wordInArrayIndicator = false ;
        for(int i = 0; i<nWords; i++) {
            if(strcmp(words[i], probeWord) == 0) {
                wordInArrayIndicator = true;
                break;
            }
        }
        if(!wordInArrayIndicator) {
            cout << "I don't know that word." << endl;
            continue;
        }
        
        tryCount++; //passed all error cases
        
        //when they equal one another
        if(strcmp(hiddenword, probeWord) == 0) {
            break;
        }
        
        //initialzing and setting up variables
        int goldCount = 0;
        int silverCount = 0;
        int goldIndex[MAXWORDSIZE];
        int silverIndex[MAXWORDSIZE];
        
        int shortestWordLen = probeWordLen;
        int longestWordLen = hiddenWordLen;
        bool isProbeWordShorter = true;
        if(hiddenWordLen < probeWordLen) {
            shortestWordLen = hiddenWordLen;
            longestWordLen = probeWordLen;
            isProbeWordShorter = false;
        }
        for(int i = 0; i<MAXWORDLEN; i++) {
            goldIndex[i] = 0;
        }
        
        //searching for golds
        for(int i = 0; i<shortestWordLen; i++) {
            if(probeWord[i] == hiddenword[i]) {
                goldCount++;
                goldIndex[i] = 1;
            }
        }
        
        //silverindex portion
        for(int z = 0; z<longestWordLen; z++) {
            silverIndex[z] = 0;
        }
        
        if(isProbeWordShorter) { //case 1
            for(int i = 0; i<longestWordLen; i++) {
                if(i<shortestWordLen) {
                    if(goldIndex[i] == 1) continue;
                }
                for(int j = 0; j<shortestWordLen; j++) {
                    if(goldIndex[j] == 1 || silverIndex[j] == 1) continue;
                    if(probeWord[j] == hiddenword[i]) {
                        silverCount++;
                        silverIndex[j] = 1;
                        break;
                    }
                }
            }
        }
        else { //case 2
            for(int i = 0; i<shortestWordLen; i++) {
                if(goldIndex[i] == 1) continue;
                for(int j = 0; j<longestWordLen; j++) {
                    if(j<shortestWordLen) {
                        if(goldIndex[j] == 1) continue;;
                    }
                    if(silverIndex[j] == 1) continue;
                    if(probeWord[j] == hiddenword[i]) {
                        silverCount++;
                        silverIndex[j] = 1;
                        break;
                    }
                }
            }
        }
        cout << "Golds: " << goldCount << ", Silvers: " << silverCount << endl;
    }
    return tryCount;
}
