#include <iostream>
#include <list>
#include <set>
#include <vector>

// Given a string and a list of characters, find how many times any of those
// characters appeared in the input string. Make the comparison case
// insensitive.
//
// Example: Input: "This is a test", characters = {'t','h'}
// Output: 4. Explanation: there are three 't' characters (case insensitive) and
// one 'h' character.
int CountCharacters(std::string& input, std::vector<char> characters);
