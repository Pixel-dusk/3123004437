#ifndef FUNCTION_H 
#define FUNCTION_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

extern const int N;

// º¯ÊıÉùÃ÷
vector<string> split_utf8(const string& s);
unordered_map<string, int> get_ngrams(const string& s);
double compute_cosine(const unordered_map<string, int>& a,
    const unordered_map<string, int>& b);

#endif