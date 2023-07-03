#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
/*
Problem:
Given a text file called "words.txt", write a C++ program
that reads in the file, counts the number of occurrences of each word,
and prints the results to the console.

The output should be case-sensitive, words in uppercase and lowercase
should be treated as distinct words.
The new streams we learned about in lecture namely std::ifstream, std::getline,
and std::stringstream will be helpful here!
*/

int main()
{
    // TODO: Write your code here 
    ifstream ifs("words.txt", ios_base::in);
    string line;
    string word;
    map<string,int> words;

//  while(getline(ifs,line)){}
    while(ifs.good()){
        getline(ifs,line);
        // cout<<line<<endl;
        istringstream iss(line);// use a iss to store the line, then stream into a word string word by word.
        while(iss>>word){// return false when iss is empty
            words[word]++;// map will detect, 
        }
    }

    for(auto pair: words){
        cout<<pair.first<<": "<<pair.second<<endl;
    }
    //ostringstream oss();

    return 0;
}