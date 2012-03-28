#include <iostream>
#include <list>
#include <map>
#include <limits>

using namespace std;

int main(){
    const int NUM_DISKS = 2;

    //up to how many items total can be in cache
    //Chris, would you figure out what if there are repeat items in cache
    //doesn't matter which disks the items are from
    const int CACHE_LIMIT = 2;

    //a constant used in formula
    const double C = 0.5;

    //dtat items in each disk
    string disk[NUM_DISKS] = {"ABC", "DEFGHIJKL"};

    string broadcast = "ACDAEBBFABlGDHCIABCJEDFKBAL";

    int frequency[NUM_DISKS] = {3, 1};

    string diskName[NUM_DISKS] = {"Disk_FAST", "Disk_SLOW"};

    //lists to store what's in the cache
    list<char> cached[NUM_DISKS];

    int totalInCache = 0;

    //LIX value for the last item of each disk's cach list
    double lix[NUM_DISKS] = {0, 0};

    //each data item will know what its most 
    //recent pi(estimated access probability) is.
    map<char, double> pi;
    //each item needs to know when it was last accessed
    map<char, int> lastAccessTime;

    //initiate pi and lastAccessTime for all letters to be 0
    for (int i = 0; i<NUM_DISKS; i++) {
        //go through all items in a disk
        for( int j=0; j<disk[i].length(); j++) {
            char letter = disk[i][j];
            pi[letter] = 0;
            lastAccessTime[letter] = 0;
        }
    }
    cout<<"*********************LIX PROGRAM*****************************"<<endl;
    //go through broadcast once, showcase how lix works.
    for(int i = 0; i<broadcast.length(); i++) {
        char letter = broadcast[i];
        for(int j = 0; j<NUM_DISKS; j++) {
            //figure out which disk the broadcast item belongs to
            if(disk[j].find(letter)!=string::npos){
                //add to the top of the cached list for the appropriate disk
                cached[j].push_front(letter);
                totalInCache++;
                cout<<"'"<<letter<<"'"<<" has been put to the beginning of cache list for "
                    <<diskName[j]<<endl;
                //calculate pi for the item              
                cout<<"p value for the data item "<<letter<<" at access time "
                    <<i+1<<" is \n"<<" C /( t - t(i) ) + (1 - C) X P(i) = "
                    <<C<<" / ("<< i+1<<" - "<<lastAccessTime[letter]
                    <<" ) + (1 - "<<C<<") X "<<pi[letter]<< " = "
                    << C / (i+1 - lastAccessTime[letter]) + (1 - C) * pi[letter]<<endl;

                pi[letter] = C / (i+1 - lastAccessTime[letter]) + (1 - C) * pi[letter];
                lastAccessTime[letter] = i+1;
            }
        }

        if (totalInCache>CACHE_LIMIT) {
            cout<<"Need to eliminate one item from cache."<<endl;
            cout<<"Calculating LIX values of last items on the all the lists."<<endl;
            for(int i=0; i<NUM_DISKS; i++) {
                if (cached[i].empty()) {
                    lix[i] = numeric_limits<double>::max();
                    cout<<diskName[i]<<"'s cache list is empty."<<endl;
                }
                else {
                    char lastItem = cached[i].back();
                    lix[i] = pi[lastItem] / frequency[i];
                    cout<<"lix value of the data item "<<lastItem 
                        <<" is p(i) / freqency(i) = "
                        << pi[lastItem]<<" / "<<frequency[i] 
                        <<" = "<<pi[lastItem] / frequency[i]<<endl;
                }
            }
         
            //smallest last item LIX value
            double smallestLix = lix[0];  

            //which disk has the smallest last item LIX
            int smallestIndex = 0;
            for(int index = 0; index < NUM_DISKS -1; index++) {
                
                if (smallestLix > lix[index+1]){ 
                    smallestLix = lix[index+1];
                    smallestIndex = index+1;
                }
                // cout<<"smallest index "<<smallestIndex<<endl;
            }    
            //eliminate the item in cache with the smallest LIX    
            char toEliminate = cached[smallestIndex].back();
            cout<<diskName[smallestIndex]<<"'s last item "<<toEliminate
                <<" has the smallest LIX value."<<endl;
            cached[smallestIndex].pop_back();
            cout<<toEliminate<<" has been removed from cache."<<endl;
            
            totalInCache--;
            }
    
        //print out what's in the cache table
        cout<<"Cache Table"<<endl;
        for (int i = 0; i<NUM_DISKS; i++) {
            cout<<"**"<<diskName[i]<<"**"<<" \t";
        }
        cout<<endl;
        for (int i=0; i<NUM_DISKS; i++) {
            //print out whole cache table
            for (list<char>::iterator it = cached[i].begin(); it!=cached[i].end(); it++){
                cout<<*it<<", ";
            }
            cout<<"\t\t";
        }
        cout<<endl<<endl;
    }//end of broadcast
    cout<<endl;

    return 0;
}
