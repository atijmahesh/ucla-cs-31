//  array.cpp
//  Atij Mahesh
//  905954423

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main() {
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    assert(lookup(h, 7, "john") == 5);
    assert(lookup(h, 7, "gordon") == 2);
    assert(lookup(h, 2, "gordon") == -1);
    assert(positionOfMax(h, 7) == 3);
    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");
    string e[4] = { "gordon", "tony", "", "john" };
    assert(subsequence(h, 7, e, 4) == 2);
    assert(subsequence(h,4,e,4) == -1);
    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
    assert(countRuns(d, 0) == 0);
    assert(countRuns(d, 1) == 1);
    assert(countRuns(d, -1) == -1);
    string f[3] = { "liz", "gordon", "tony" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(lookupAny(h, 7, f, 0) == -1);
    assert(flip(f, 0) == 0 && f[0] == "liz");
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
    assert(split(h, 7, "liz") == 3);
    string a[2] = {"", ""};
    assert(lookup(a, 2, "john") == -1);
    assert(lookup(a, 2, "") == 0);
    assert(lookup(a, -1, "") == -1);
    assert(lookup(a, 0, "john") == -1);
    assert(positionOfMax(a, 2) == 0);
    assert(positionOfMax(a, 0) == -1);
    assert(positionOfMax(a, -2) == -1);
    assert(differ(a, 0, f, 0) == 0);
    assert(differ(a, 0, f, -1) == -1);
    assert(differ(a, -1, f, 0) == -1);
    assert(appendToAll(a, -1, "bob") == -1 && a[0] == "");
    assert(rotateLeft(a, 2, 4) == -1 && a[0] == "");
    assert(rotateLeft(a, -1, 2) == -1 && a[0] == "");
    assert(rotateLeft(a, 2, -1) == -1 && a[0] == "");
    assert(subsequence(a,2,f,3) == -1);
    assert(subsequence(a,1,f,3) == -1);
    assert(subsequence(a,-1,f,3) == -1);
    assert(subsequence(a,1,f,-3) == -1);
    assert(countRuns(a, 2) == 1);
    assert(countRuns(a, 0) == 0);
    assert(countRuns(a, -1) == -1);
    assert(lookupAny(a, -2, f, 3) == -1);
    assert(lookupAny(a, 2, f, -3) == -1);
    assert(lookupAny(h, 0, f, 3) == -1);
    assert(lookupAny(a, 2, f, 0) == -1);
    assert(flip(a, -1) == -1 && a[0] == "");
    
    string b[5] = {"d", "c", "b", "e", "a"};
    assert(split(b, 5, "b") == 1);
    assert(split(b, -1, "b") == -1);
    assert(split(b, 0, "b") == 0);
    cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value) {
    if(n<0) return -1;  //bad user input
    for(int i = 0; i<n; i++)
        a[i] = a[i] + value;
    return n;
}

int lookup(const string a[], int n, string target) {
    if(n<0) return -1; //bad user input
    for(int i = 0; i<n; i++) {
        if(a[i] == target) return i;
    }
    return -1;
}

int positionOfMax(const string a[], int n) {
    if(n<=0) return -1; //bad user input
    string max = a[0];
    int maxPos = 0;
    for(int i = 1; i<n; i++) {
        if(a[i] > max) {
            max = a[i];
            maxPos = i;
        }
    }
    return maxPos;
}
int rotateLeft(string a[], int n, int pos) {
    if(n<0 || pos<0 || pos>=n) return -1; //bad user input
    string valAtPos = a[pos];
    for(int i = pos; i<n-1; i++) {
        a[i] = a[i+1];
    }
    a[n-1] = valAtPos;
    return pos;
}

int countRuns(const string a[], int n) {
    if(n<0) return -1; //bad user input
    if(n == 0) return 0;
    int runCount = 1;
    for(int i = 1; i<n; i++) {
        if(a[i] == a[i-1]) continue;
        else runCount++;
    }
    return runCount;
}

int flip(string a[], int n) {
    if(n<0) return -1; //bad user input
    for(int i = 0; i<n/2; i++) {
        string temp = a[i];
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) return -1; //bad user input
    int smallestArrSize = n1;
    if(n2<n1) smallestArrSize = n2;
    int i = 0;
    for(i = 0; i<smallestArrSize; i++) {
        if(a1[i] != a2[i]) break;
    }
    if(i<smallestArrSize) return i;
    return smallestArrSize;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0 || n2>n1) return -1; //bad user input
    if(n2 == 0) return 0;
    const string firstElem = a2[0];
    const string lastElem = a2[n2-1];
    
    int i = 0;
    for(i = 0; i<n1; i++) {
        if(a1[i] == firstElem) break;
    }
    
    //when the first or last element of a2 aren't in a1
    if(lookup(a1, n1, firstElem) == -1 || lookup(a1, n1, lastElem) == -1 )
        return -1;
    
    int j = 0;
    int k = i;
    while(k<n1 && j<n2) {
        if(a1[k] != a2[j]) {
            if(n1-k-1>=n2) {
                int z = k;
                for(z = k; z<n1; z++) {
                    if(a1[z] == firstElem) break;
                }
                if(z == n1) return -1;
                k = z;
                i = z;
                j=0;
            }
            else return -1;
        }
        j++;
        k++;
    }
    return i;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
    if(n1 < 0 || n2 < 0) return -1; //bad user input
    for(int i = 0; i<n1; i++) {
        for(int j = 0; j<n2; j++) {
            if(a1[i] == a2[j])
                return i; //immeadiate return
        }
    }
    return -1;
}


int split(string a[], int n, string splitter) {
    if(n<0) return -1; //bad user input
    int lastSplitIndex = 0;
    for(int i = 0; i<n; i++) {
        if(a[i] < splitter) {
            //swap and incremenet
            string temp = a[i];
            a[i] = a[lastSplitIndex];
            a[lastSplitIndex] = temp;
            lastSplitIndex++;
        }
    }
    if(lastSplitIndex > 0) return lastSplitIndex;
    return n;
}
