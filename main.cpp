//
// Test Program for the VariableArrayList Class
// Author: Max Benson
// Date: 07/23/2021
//

#include <assert.h>

#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

#include "VariableArrayList.h"

struct Insertion {
    string value;
    size_t positionToInsert;
};

void TestInsert(const Insertion arrayOfInsertions[], const string resultingValues[], size_t numberOfValues, const string& itemNotInList);
void TestGrowShrink();
void TestCopyConstructor(const VariableArrayList<string>& L);
void TestAssignment(const VariableArrayList<string>& L);
void TestSwap();
void TestReplace();
void Cleanup(VariableArrayList<string>& L);

int main() {
    Insertion empty[] = {};
    string resultForEmpty[] = {};
    Insertion append[] = {{"In",        0},
                          {"the",       1},
                          {"beginning", 2},
                          {"God",       3}};
    string resultForAppend[] = { "In", "the", "beginning", "God"};
    Insertion prepend[] = {{"In",        0},
                          {"the",       0},
                          {"beginning", 0},
                          {"God",       0}};
    string resultForPrepend[] = { "God", "beginning", "the", "In"};
    Insertion jumbled[] = {{"the", 0},
                           {"God", 1},
                           {"beginning", 1},
                           {"In", 0}};
    string resultForJumbled[] = {"In", "the", "beginning", "God"};

    TestInsert(empty, resultForEmpty, sizeof(empty)/sizeof(empty[0]), "not-in-list");
    TestInsert(append, resultForAppend, sizeof(append)/sizeof(append[0]), "not-in-list");
    TestInsert(prepend, resultForPrepend, sizeof(prepend)/sizeof(prepend[0]), "not-in-list");
    TestInsert(jumbled, resultForJumbled, sizeof(jumbled)/sizeof(jumbled[0]), "not-in-list");
    TestSwap();
    TestReplace();
    TestGrowShrink();

    cout << "All tests passed" << endl;

    return 0;
}

void TestInsert(const Insertion arrayOfInsertions[], const string resultingValues[], size_t numberOfValues, const string& itemNotInList) {
    VariableArrayList<string> L;
    string item;
    stringstream sstr1;
    stringstream sstr2;

    assert(L.CheckConsistency());
    for (size_t i = 0; i < numberOfValues; i ++) {
        assert(L.Insert(arrayOfInsertions[i].positionToInsert, arrayOfInsertions[i].value));
        assert(L.CheckConsistency());
    }
    assert(L.Size() == numberOfValues);
    for (size_t i = 0; i < numberOfValues; i ++) {
        assert(L.Find(resultingValues[i]) == i);
        assert(L.Find(resultingValues[i],i+1) == -1);
        assert(L.Get(i, item));
        assert(item == resultingValues[i]);
    }
    assert(L.Find(itemNotInList) == -1);
    assert(!L.Get(numberOfValues,item));
    assert(!L.Get(numberOfValues+1,item));

    for (size_t i = 0; i < numberOfValues; i ++) {
        assert(L.Remove(i, item));
        assert(item == resultingValues[i]);
        assert(L.CheckConsistency());
        assert(L.Insert(i, resultingValues[i]));
        assert(L.CheckConsistency());
        assert(L.Size() == numberOfValues);
    }
    assert(!L.Insert(numberOfValues+1, "bad-position"));
    assert(!L.Remove(numberOfValues, item));
    assert(!L.Remove(numberOfValues+1, item));
    assert(L.Size() == numberOfValues);

    sstr1 << "[";
    for (size_t i = 0; i < numberOfValues; i ++) {
        if (i > 0) {
            sstr1 << ", ";
        }
        sstr1 << resultingValues[i];
    }
    sstr1 << "]";

    sstr2 << L;
    assert(sstr1.str() == sstr2.str());

    assert(L.CheckConsistency());
    TestCopyConstructor(L);
    TestAssignment(L);
    Cleanup(L);
}

void TestCopyConstructor(const VariableArrayList<string>& L) {
    VariableArrayList<string> LCopy(L);
    stringstream sstr1;
    stringstream sstr2;

    assert(L.CheckConsistency());
    assert(LCopy.CheckConsistency());
    sstr1 << L;
    sstr2 << LCopy;
    assert(sstr1.str() == sstr2.str());
    assert(L.CheckConsistency());
    assert(LCopy.CheckConsistency());
}

void TestAssignment(const VariableArrayList<string>& L) {
    VariableArrayList<string> LAssign;
    stringstream sstr1;
    stringstream sstr2;

    assert(L.CheckConsistency());
    assert(LAssign.CheckConsistency());
    LAssign = L;
    sstr1 << L;
    sstr2 << LAssign;
    assert(sstr1.str() == sstr2.str());
    assert(L.CheckConsistency());
    assert(LAssign.CheckConsistency());
}

void TestSwap() {
    VariableArrayList<int> L;
    stringstream sstr;

    L.Insert(L.Size(), 1);
    L.Insert(L.Size(), 2);
    L.Insert(L.Size(), 3);
    assert(L.Swap(0,1));
    assert(L.Swap(1,2));
    assert(!L.Swap(4, 0));
    sstr << L;
    assert(sstr.str() == "[2, 3, 1]");
}

void TestReplace() {
    VariableArrayList<string> L;
    stringstream sstr;

    L.Insert(L.Size(), "A");
    L.Insert(L.Size(), "B");
    L.Insert(L.Size(), "C");
    assert(L.Replace(1, "D"));
    assert(!L.Replace(4, "D"));
    sstr << L;
    assert(sstr.str() == "[A, D, C]");
}

void Cleanup(VariableArrayList<string>& L) {
    assert(L.CheckConsistency());
    L.Clear();
    assert(L.Size() == 0);
    assert(L.CheckConsistency());
}

void TestGrowShrink() {
    VariableArrayList<string> L;
    int nextPowerOfTwo = 1;

    for (size_t i = 0; i < 2048; i ++) {
        assert(L.Capacity() == nextPowerOfTwo);
        L.Insert(i, "Hi there");
        if (i == nextPowerOfTwo) {
            nextPowerOfTwo *= 2;
        }
    }
    while (L.Size() > 0) {
        string item;

        if (L.Size() > 1 && 4*(L.Size()-1) <= L.Capacity()) {
            nextPowerOfTwo /= 2;
        }
        L.Remove(L.Size()-1, item);
        assert(L.Capacity() == nextPowerOfTwo);
    }
    for (size_t i = 0; i < 2048; i ++) {
        assert(L.Capacity() == nextPowerOfTwo);
        L.Insert(i, "Hi there");
        if (i == nextPowerOfTwo) {
            nextPowerOfTwo *= 2;
        }
    }
}
