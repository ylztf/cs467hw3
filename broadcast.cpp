#include <map> 
#include <vector>
#include <iostream>
#include <string.h>
#include <math.h>

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

void printChunk(vector<int>& a_disk, int start_index, int how_many){
    cout<<"[";
    
    for(int it=start_index; it<(start_index + how_many); it++) {
        cout<<a_disk[it]<<", ";
    }

    cout<<"]";
}

int main(){
    const int NUM_DISKS = 3;

    //structure to present raw data
    map<int, string> items;
    
    const string ACCESS_PROB[NUM_DISKS] = {"1/4","1/32","1/120"};
   
    const double ACCESS_PROB_VALUE[NUM_DISKS] = {0.25, 0.03125, 0.008333333333};

    string diskName[3] = {"Disk A", "Disk B", "Disk C"};
    //static input for raw data.  Be ideal if this is read from std input or a file.
    items[0] = ACCESS_PROB[0];
    items[1] = ACCESS_PROB[2];   
    items[2] = ACCESS_PROB[2]; 
    items[3] = ACCESS_PROB[2];
    items[4] = ACCESS_PROB[1];   
    items[5] = ACCESS_PROB[2];

    items[6] = ACCESS_PROB[2];
    items[7] = ACCESS_PROB[1];   
    items[8] = ACCESS_PROB[2]; 
    items[9] = ACCESS_PROB[2];
    items[10] = ACCESS_PROB[2];   
    items[11] = ACCESS_PROB[2]; 

 
    items[12] = ACCESS_PROB[2]; 
    items[13] = ACCESS_PROB[2];
    items[14] = ACCESS_PROB[1];   
    items[15] = ACCESS_PROB[2];

    items[16] = ACCESS_PROB[2];
    items[17] = ACCESS_PROB[1];   
    items[18] = ACCESS_PROB[2]; 
    items[19] = ACCESS_PROB[2];
    items[20] = ACCESS_PROB[2];   
    items[21] = ACCESS_PROB[2]; 

    items[22] = ACCESS_PROB[1]; 
    items[23] = ACCESS_PROB[2];
    items[24] = ACCESS_PROB[2];   
    items[25] = ACCESS_PROB[1]; 

    items[26] = ACCESS_PROB[2]; 
    items[27] = ACCESS_PROB[1];
    items[28] = ACCESS_PROB[2];   
    items[29] = ACCESS_PROB[2]; 
    items[30] = ACCESS_PROB[2]; 
    items[31] = ACCESS_PROB[2];
    items[32] = ACCESS_PROB[2];   
    items[33] = ACCESS_PROB[1]; 
    items[34] = ACCESS_PROB[2]; 
    items[35] = ACCESS_PROB[2];
    items[36] = ACCESS_PROB[0];   
    items[37] = ACCESS_PROB[2]; 
    items[38] = ACCESS_PROB[2]; 
    items[39] = ACCESS_PROB[2];
   
    //data structure for items to be stored in each disk    
    typedef vector<int> disk;
   
    //total items stored in respective disks
    disk disks[NUM_DISKS];
   
    int countTotal=0;  //total number of data items

    int count[NUM_DISKS]= {0, 0, 0}; //number of items in each disk

    //broadcast frequencies for the different groups
    int freq[NUM_DISKS] = {0,0,0};

    //calculated max length of a chunk for output
    int max_chunks = 0;

    //divide each disk into appropriate number of chunks
    int num_chunks[NUM_DISKS] = {0, 0, 0};

    //how many items are in a chunk for a particular disk
    int itemsPerChunk[NUM_DISKS] = {0, 0, 0};

    // the kth chunk in a disk
    int k = 0;

    //print out all items and their access probabilites
    cout<<"We have the following data items and their respective access probablilities."<<endl;
    cout<<"data item     "<<"     access probability"<<endl;
    for (map<int, string>::iterator it=items.begin(); it!=items.end(); ++it){
        cout<<(*it).first<<"                  "<<(*it).second<<endl;
        countTotal++;
    }
    cout<<"There are "<<countTotal<<" data items in total."<<endl;

    //go through all items and put them into different vectors according to their access probability
    cout<<"We divide data items into different groups according to their access probabilities and assign them to different disks \n"<<endl;

    //this is not very smart as I use string compare.
    for ( map<int, string>::iterator it=items.begin(); it!=items.end(); ++it){
        int whichDisk=0;
      
        if((*it).second.compare(ACCESS_PROB[0]) == 0){
                ;
        }
        else if((*it).second.compare(ACCESS_PROB[1])==0) { 
            whichDisk++;
        }
        else if((*it).second.compare(ACCESS_PROB[2])==0){
            whichDisk=whichDisk+2;;
        }
        disks[whichDisk].push_back((*it).first);
    }
    //print out the contents of the disks.
    for (int index = 0; index<NUM_DISKS; index++){
        cout<<diskName[index]<<" is for items with access probability of "<<ACCESS_PROB[index]<<endl;
        cout<<diskName[index]<<"  has the following items:"<<endl;
        for(int it=0; it<disks[index].size(); it++) {
            cout<<disks[index][it]<<endl;
            count[index]++;
        }
        cout<<"There are "<<count[index]<<" items in "<<diskName[index]<<" \n"<<endl;
    }

    cout<<"Calculating frequencies..."<<endl;
    //frequency calculation is not dynamic enough, hard coding array subscripts instead of using loops.  May leave this to Chris.  I need to move on
    freq[0] = ceil( sqrt(ACCESS_PROB_VALUE[0]/ACCESS_PROB_VALUE[2]) );
    freq[1] = ceil( sqrt(ACCESS_PROB_VALUE[1]/ACCESS_PROB_VALUE[2]) );
    freq[2] = ceil( sqrt(ACCESS_PROB_VALUE[2]/ACCESS_PROB_VALUE[2]) );

    cout<<"frequency_A / frequency_B = sqrt(access_probablility_A) / sqrt(access_probability_B)"<<endl;
    cout<<"frequency_A / frequency_B = sqrt("<<ACCESS_PROB[0]<<")/sqrt("<<ACCESS_PROB[1]<<")="<<sqrt(ACCESS_PROB_VALUE[0]/ACCESS_PROB_VALUE[1])
        <<", which is rounded up to "<<ceil( sqrt(ACCESS_PROB_VALUE[0]/ACCESS_PROB_VALUE[1]) )<<"\n"<<endl;

    cout<<"frequency_A / frequency_C = sqrt(access_probablility_A) / sqrt(access_probability_C)"<<endl;
    cout<<"frequency_A / frequency_C = sqrt("<<ACCESS_PROB[0]<<")/sqrt("<<ACCESS_PROB[2]<<")="<<sqrt(ACCESS_PROB_VALUE[0]/ACCESS_PROB_VALUE[2])
        <<", which is rounded up to "<<ceil( sqrt(ACCESS_PROB_VALUE[0]/ACCESS_PROB_VALUE[2]) )<<"\n"<<endl;

    cout<<"frequency of items in disk A is "<<freq[0]<<endl;
    cout<<"frequency of items in disk B is "<<freq[1]<<endl;  
    cout<<"frequency of items in disk B is "<<freq[2]<<"\n"<<endl;                                                
    cout<<"max_chunks is the least common multiple of the frequencies: "<<endl;
    max_chunks = lcm(lcm(freq[0], freq[1]), freq[2]);
    cout<<"LCM("<<freq[0]<<", "<<freq[1]<<", "<<freq[2]<<") = "<<max_chunks<<endl;

    num_chunks[0] = max_chunks/freq[0];
    num_chunks[1] = max_chunks/freq[1];
    num_chunks[2] = max_chunks/freq[2];
    cout<<"number_chunks(A) = max_chunks / rel_freq(A) = "<<max_chunks<<" / "<<freq[0]<<" = "<<num_chunks[0]<<endl;
    cout<<"number_chunks(B) = max_chunks / rel_freq(A) = "<<max_chunks<<" / "<<freq[1]<<" = "<<num_chunks[1]<<endl;
    cout<<"number_chunks(C) = max_chunks / rel_freq(A) = "<<max_chunks<<" / "<<freq[2]<<" = "<<num_chunks[2]<<"\n"<<endl;

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
