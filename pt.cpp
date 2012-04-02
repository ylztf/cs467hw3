#include <iostream>
#include <list>
#include <map>
#include <fstream>

using namespace std;
//To catch the essense of PT algorithm, we assume the broadcast is done on one disk 
//(so all data items are broadcast at the same speed). 
//Some items are repeated more than others.
//Access probability of a data item may not be in sync with broadcast frequency of the item
//(as is the case in the example in the slides)
int main(int argc, char* argv[]){
    //only has one thing in cache.  Much simpler to code, but may need to be changed to make the program more dynamic.
    const int CACHE_LIMIT = 1;
	
	//input stream from file
	ifstream in(argv[1]);
    
    //read broadcast from input file
    string broadcast;
	in >> broadcast;
	
	cout << "The broadcast schedule is " << broadcast << endl << endl;

    //this is needed so string.find will not return -1 when it reached the end of the broadcast.
    string doubleLoop = broadcast + broadcast;
    //access probability for different data, using A, B, C as keys
    map<char, double> accessProb;
	
	//read in the pages and probabilities from the input file
	char page;
	double prob;

	do{
		in >> page >> prob;
		accessProb[page] = prob;
	}while(!in.eof());
    
    //data item in cache
    char cached = '\0';
    
    cout<<"*******************PT PROGRAM*********************************"<<endl;
    //go through the broadcast once, showcase all cache changes
    for (int i = 0; i < broadcast.length(); i++) {
        char item = broadcast[i];
        cout<<"Data item "<<item<<" has been broadcast."<<endl;
        if(!cached) {
            cached = item;
            cout<<item<<" has been cached."<<endl;
        }
        else {
            //calculate PT value for the item just broadcast
            cout<<item<<"'s access probability is "<<accessProb[item]<<endl;    
  
            //character position in the broadcast is used to represent broadcast time
            int nextTime = doubleLoop.find(item, i+1);
            //cout<<"i is "<<i<<" nextTime is "<<nextTime<<endl;
            int time = nextTime - i;
            cout<<"It will be "<<time<<" time units before "<<item<<" is broadcast again."<<endl;

            double Pt = accessProb[item] * time;
            cout<<"PT value for "<<item<<" is "<<accessProb[item]<<" x "<<time<<" = "<<Pt<<endl;

            //calculate PT value for the cached item, as it has changed.
            cout<<"Cached item "<<cached<<"'s access probability is "<<accessProb[cached]<<endl;    
            int cached_nextTime = doubleLoop.find(cached, i+1);
            int cached_time = cached_nextTime - i;
            cout<<"It will be "<<cached_time<<" time units before "<<cached<<" is broadcast again."<<endl;

            double cached_Pt = accessProb[cached] * cached_time;
            cout<<"Current PT value for the cached item "<<cached<<" is "
                <<accessProb[cached]<<" x "<<cached_time<<" = "<<cached_Pt<<endl;

            if (Pt > cached_Pt){
                cout<<"PT value for cached item "<<cached<<" is lower than the PT value for the newly broadcast item "
                    <<item<<endl;
                cout<<"Replacing cached item with new item "<<item<<endl;
                cached = item;
            }
            else {
                cout<<"PT value for cached item "<<cached
                    <<" is higher than or equal to the PT value for the newly broadcast item "
                    <<item<<endl;
                cout<<"Cache not changed. "<<endl;
            }
        }
        cout<<endl;
    }

    return 0;
}
