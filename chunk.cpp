#include <map> 
#include <vector>
#include <iostream>
#include <string.h>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

//void group(map<int, double> & data){}

//put_schedule();

int gcd(int a, int b){
    for(;;) {
        if(a == 0) return b;
        b %=a;
        if(b==0)return a;
        a %=b;
    }
}

int lcm(int a, int b){
    int tmp = gcd(a,b);
    return tmp? (a/tmp*b): 0;
}

int lcm(vector<int> v)
{
	switch(v.size())
	{
		case 1:
			return v[0];
			break;
		case 2:
			return lcm(v[0], v[1]);
			break;
		default:
			int retme = lcm(v[0], v[1]);
			for(int i = 2; i < v.size(); ++i)
				retme = lcm(v[i], retme);
				
			return retme;
			break;
	}
}

void printChunk(vector<int>& a_disk, int start_index, int how_many){
    cout<<"[";
    
    for(int it=start_index; it<(start_index + how_many); it++) {
        cout<<a_disk[it]<<", ";
    }

    cout<<"]";
}

int main(int argc, char* argv[]){
	//input stream from file
	ifstream in(argv[1]);

    int NUM_DISKS = 0;

    //structure to present raw data
    map<int, double> items;
    
    //const string ACCESS_PROB[NUM_DISKS] = {"1/4","1/32","1/120"};
   
    vector<double> ACCESS_PROB_VALUE; // {0.25, 0.03125, 0.008333333333};

    vector<string> diskName; // {"Disk A", "Disk B", "Disk C"};
   
    //data structure for items to be stored in each disk    
    typedef vector<int> disk;
   
    //total items stored in respective disks
    vector<disk> disks;
   
    int countTotal=0;  //total number of data items

    vector<int> count; // {0, 0, 0}; //number of items in each disk

    //broadcast frequencies for the different groups
    vector<int> freq; // {0,0,0};

    //calculated max length of a chunk for output
    int max_chunks = 0;

    //divide each disk into appropriate number of chunks
    vector<int> num_chunks; // {0, 0, 0};

    //how many items are in a chunk for a particular disk
    vector<int> itemsPerChunk; // {0, 0, 0};
	
	//read input from file
	int page;
	double prob;
	
	do{
		in >> page >> prob;
		
		items[page] = prob;
		countTotal++;
		
		//search for the probability to see if it is shared by other pages
		bool found = false;
		int i;
		
		for(i = 0; i < ACCESS_PROB_VALUE.size(); ++i)
			if(ACCESS_PROB_VALUE[i] == prob)
			{
				found = true;
				break;
			}
		
		//if not found, add a new disk for the neww access probability
		if(!found)
		{
			NUM_DISKS++;
			ACCESS_PROB_VALUE.push_back(prob);
			
			disk tempDisk;
			disks.push_back(tempDisk);

			count.push_back(0);
			freq.push_back(0);
			num_chunks.push_back(0);
			itemsPerChunk.push_back(0);
			
			//just some magic to convert an integer to a string
			stringstream ss;
			ss << i;
			diskName.push_back("Disk_" + ss.str());
		}
	}while(!in.eof());

    // the kth chunk in a disk
    int k = 0;

    //print out all items and their access probabilites
    cout<<"We have the following data items and their respective access probablilities."<<endl;
    cout<<"data item     "<<"     access probability"<<endl;
    for (map<int, double>::iterator it=items.begin(); it!=items.end(); ++it){
        cout<<(*it).first<<"                  "<<(*it).second<<endl;
    }
    cout<<"There are "<<countTotal<<" data items in total."<<endl;

    //go through all items and put them into different vectors according to their access probability
    cout<<"We divide data items into different groups according to their access probabilities and assign them to different disks \n"<<endl;

    //this is not very smart as I use string compare.
    for ( map<int, double>::iterator it=items.begin(); it!=items.end(); ++it){
		for(int m = 0; m < ACCESS_PROB_VALUE.size(); ++m)
			if((*it).second == ACCESS_PROB_VALUE[m])
			{
				disks[m].push_back((*it).first);
				break;
			}
    }
	
	// sort the disks according to access probability
	int i, j, flag = 1;    // set flag to 1 to start first pass
	double temp;             // holding variables
	disk tempDisk;
	for(i = 1; (i <= ACCESS_PROB_VALUE.size()) && flag; i++)
	{
		flag = 0;
		for (j=0; j < (ACCESS_PROB_VALUE.size() -1); j++)
		{
			if (ACCESS_PROB_VALUE[j+1] > ACCESS_PROB_VALUE[j])      // ascending order simply changes to <
			{ 
				temp = ACCESS_PROB_VALUE[j];             // swap elements
				tempDisk = disks[j];
				
				disks[j] = disks[j+1];
				ACCESS_PROB_VALUE[j] = ACCESS_PROB_VALUE[j+1];
				
				ACCESS_PROB_VALUE[j+1] = temp;
				disks[j+1] = tempDisk;
				
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
	
    //print out the contents of the disks.
    for (int index = 0; index<NUM_DISKS; index++){
        cout<<diskName[index]<<" is for items with access probability of "<<ACCESS_PROB_VALUE[index]<<endl;
        cout<<diskName[index]<<"  has the following items:"<<endl;
        for(int it=0; it<disks[index].size(); it++) {
            cout<<disks[index][it]<<endl;
            count[index]++;
        }
        cout<<"There are "<<count[index]<<" items in "<<diskName[index]<<" \n"<<endl;
    }

    cout<<"Calculating frequencies..."<<endl;
    //find the minimum access probabilities and calculate relative frequencies from it
	int minimumIndex = 0;
	for(int i = 0; i < NUM_DISKS; ++i)
		if(ACCESS_PROB_VALUE[i] < ACCESS_PROB_VALUE[minimumIndex])
			minimumIndex = i;
	
	cout<<"frequency_A / frequency_B = sqrt(access_probablility_A) / sqrt(access_probability_B)"<<endl;
	
	for(int i = 0; i < NUM_DISKS; ++i)
	{
		freq[i] = ceil( sqrt(ACCESS_PROB_VALUE[i]/ACCESS_PROB_VALUE[minimumIndex]) );

		cout<< diskName[i] << ": " << endl;
		cout<<"relative frequency = sqrt("<<ACCESS_PROB_VALUE[i]<<")/sqrt("<<ACCESS_PROB_VALUE[minimumIndex]<<")="<<sqrt(ACCESS_PROB_VALUE[i]/ACCESS_PROB_VALUE[minimumIndex])
			<<", which is rounded up to "<<ceil( sqrt(ACCESS_PROB_VALUE[i]/ACCESS_PROB_VALUE[minimumIndex]) )<<"\n"<<endl;
	}

	for(int i = 0; i < NUM_DISKS; ++i)
		cout<<"frequency of items in " << diskName[i] << " is "<<freq[i]<<endl;
	
    cout<<"max_chunks is the least common multiple of the frequencies: "<<endl;
    max_chunks = lcm(freq);
    cout<<"LCM = "<<max_chunks<<endl;

	for(int i = 0; i < NUM_DISKS; ++i)
    {
		num_chunks[i] = max_chunks/freq[i];
		cout<<"number_chunks(" << diskName[i] << ") = max_chunks / rel_freq(" << diskName[i] << ") = "<<max_chunks<<" / "<<freq[i]<<" = "<<num_chunks[i]<<endl;
	}
		
    for(int index = 0; index<NUM_DISKS; index++){
       
        while( (count[index] % num_chunks[index])!= 0 ){
            num_chunks[index]--;
            cout<<"    number_chunks in "<<diskName[index]<<" cannot evenly divide items in "<<diskName[index] << ". Decreasing number_chunks in "<<diskName[index]<<" by 1."<<endl;
            cout<<"    number_chunks in "<<diskName[index] <<" is now "<<num_chunks[index]<<endl<<endl;
        }
        itemsPerChunk[index] = count[index]/num_chunks[index];
        cout<<diskName[index]<<" has "<<itemsPerChunk[index]<<" items in each chunk"<<endl<<endl;
    }

    
    cout<<"Broadcast schedule is "<<endl;

    for(int i=0; i<max_chunks; i++) {
        for (int j=0; j<NUM_DISKS; ++j) {
            k = i % (num_chunks[j]);
           
            printChunk(disks[j],k * itemsPerChunk[j], itemsPerChunk[j]);
            cout<<"    ";
           
        }
    }
    cout<<endl;
    return 0;
}
