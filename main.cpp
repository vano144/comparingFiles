#include <iostream>
#include <stdio.h>
#include <map>
#include <regex>
#include <fstream>
using namespace std;

regex puncmark(",|\\.|!|\\?|\\\"|…|:|-|\\(|\\)|—|\\[|\\]");//edit for punctuation

void statistic(string wordFIle, map<string,int>* store) { //counting frequences
    if (regex_search(wordFIle,puncmark)) {
        wordFIle=regex_replace(wordFIle,puncmark,"");
    }
    if (wordFIle=="") return;
    if (store->count(wordFIle)==1) {
        //addition of old element
        (*store)[wordFIle]++;
    }
    else {                                            //addition of new element
        store->insert ( pair<string,int>(wordFIle,1) );
    }
}

int countWords(map <string,int>* storeFile1,char filename[20]) {
    string wordFIle;
    ifstream in;
    int amount=0;
    in.open(filename);
    if (!in.is_open()) {
        cout<<"trouble with"<<filename<<endl;
        return -1;
    }
    while (in>>wordFIle) {
        statistic(wordFIle, storeFile1);
        amount++;
    }
    in.close();
    return amount;
}

int calculateDifference(map <string,int> storeFile1, map <string,int> storeFile2, int size1, int size2) {
    int difference=0;
    for (auto it=storeFile1.begin();it!=storeFile1.end();it++)
    {
        if (storeFile2.count((*it).first)) {
            difference+=( abs((*it).second-storeFile2[(*it).first]));
            storeFile2.erase((*it).first);
        }
        else {
            difference+=((*it).second);
        }
    }
    for (auto it=storeFile2.begin();it!=storeFile2.end();it++)
    {
        difference+=((*it).second);
    }
    return difference;
}

double compareFiles(map <string,int> storeFile1, map <string,int> storeFile2, int size1, int size2) {
    int difference=0;
    if (size1>=size2) {
        difference=calculateDifference(storeFile1, storeFile2, size1, size2);
        return (double)difference/(size1+size2)*100.0;
    }
    else
    {
        difference=calculateDifference(storeFile2, storeFile1, size2, size1);
        return (double)difference/(size2+size1)*100.0;
    }
    return -1;
}

int main()
{
    map <string,int> storeFile1;
    map <string,int> storeFile2;
    char filename1[20]="/f2.txt";
    char filename2[20]="/f3.txt";
    int size1=countWords(&storeFile1, filename1);
    int size2=countWords(&storeFile2, filename2);
    //cout<<size1<<endl;
    //cout<<size2<<endl;
    auto result=compareFiles(storeFile1,storeFile2,size1,size2);
    if (result==-1) {
        cout<<"problem with comparing"<<endl;
        return 1;
    }
     printf("%f%%",result);
    cout<<endl;
    return 0;
}