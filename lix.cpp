#include <iostream>
#include <list>
#include <map>
#include <limits>

using namespace std;

int main(){
    const int NUM_DISKS = 2;

    const int CACHE_LIMIT = 4;

    //a constant used in formula
    const double C = 0.5;

    string disk[NUM_DISKS] = {"ABC", "DEFGHIJKL"};

    string broadcast = "ABCDEFABCGHIABCJKL";

    int frequency[NUM_DISKS] = {3, 1};

    string diskName[NUM_DISKS] = {"Disk A", "Disk B"};

    list<char> cached[NUM_DISKS];

    int totalInCache = 0;

    //LIX value for the last item of each disk's cach list
    double lix[NUM_DISKS] = {0, 0};

    //each data item will know what its most recent pi(estimated access probability) is.
    map<char, double> pi;
    map<char, int> lastAccessTime;
    //initiate pi for all letters to be 0
    for (int i = 0; i<NUM_DISKS; i++) {
        for( int j=0; j<disk[i].length(); j++) {
            char letter = disk[i][j];
            pi[letter] = 0;
            lastAccessTime[letter] = 0;
        }
    }
    cout<<"************************LIX PROGRAM*********************************"<<endl;
    //go through broadcast once, showcase how lix works.
    for(int i = 0; i<broadcast.length(); i++) {
        char letter = broadcast[i];
        for(int j = 0; j<NUM_DISKS; j++) {
            //figure out which disk the broadcast item belongs to
            if(disk[j].find(broadcast[i])!=string::npos){
                //add to the top of the cached list for the appropriate disk
                cached[j].push_front(broadcast[i]);
                totalInCache++;
                cout<<broadcast[i]<<" has been put to the beginning of list for "<<diskName[j]<<endl;
                //calculate pi for the item              
                pi[letter] = C / (i+1 - lastAccessTime[letter]) + (1 - C) * pi[letter];
                lastAccessTime[letter] = i+1;
            }
        }

        if (totalInCache>CACHE_LIMIT){
            cout<<"Need to eliminate one item from cache."<<endl;
            cout<<"Calculating LIX values of last items on the all the lists."<<endl;
            for(int i=0; i<NUM_DISKS; i++) {
                if (cached[i].empty()) {
                    lix[i] = numeric_limits<double>::max();
                    cout<<"max is "<<lix[i]<<endl;
                }
                else {
                    char lastItem = cached[i].back();
                    lix[i] = pi[lastItem] / frequency[i];
                }
            }
            cout<<"Find which last item has the smallest LIX value."<<endl;
            //smallest last item LIX value
            double smallestLix = 0;  

            //which disk has the smallest last item LIX
            int smallestIndex = lix[0];
            for(int index = 0; index < NUM_DISKS -1; index++) {
                
                if (smallestLix > lix[index+1]){ 
                    cout<<"smallestLix is "<<smallestLix<<" lix[index+1] is "<<lix[index+1]<<endl;
                    smallestLix = lix[index+1];
                    smallestIndex = index+1;
                }
                
                //eliminate the item in cache with the smallest LIX    
                char toEliminate = cached[smallestIndex].back();
                cout<<diskName[smallestIndex]<<"'s last item "<<toEliminate<<" has the smallest LIX value."<<endl;
                cached[smallestIndex].pop_back();
                cout<<toEliminate<<" has been removed from cache."<<endl;
            
                totalInCache--;
            }
        }
        //print out what's in the cache table
        cout<<"Cache Table"<<endl;
        cout<<"DISK A \t \t \tDISK B \t "<<endl;
        for (int i=0; i<NUM_DISKS; i++) {
          
            for (list<char>::iterator it = cached[i].begin(); it!=cached[i].end(); it++){
                cout<<*it<<", ";
            }
            cout<<"\t\t";
        }
        cout<<endl;
    }//end of broadcast
    cout<<endl;

    return 0;
}
