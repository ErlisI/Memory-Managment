//
//  main.cpp
//  Lab #3
//
//  Created by Erlis Ibraimi on 12.10.22.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Process{
    int PID = NULL;
    string pStatus = "wait";
    int memSize = NULL;
};

struct Partition{
    int PartID = NULL;
    string partStatus = "wait";
    int memSize = NULL;

};

void bestFit(vector<Process>, vector<Partition>);
void firstFit(vector<Process>, vector<Partition>);
void nextFit(vector<Process>, vector<Partition>);
void worstFit(vector<Process>, vector<Partition>);
void worstFitDynamic(vector<Process>, vector<Partition>);


int main(int argc, const char * argv[]) {
    
    vector<Process> pro;
    vector<Partition> part;
    
    int numPart, numP, sizePart = 0, sizeP = 0;
    
    cout<<"Enter the number of Processes: ";
    cin>>numP;
    
    cout<<"Enter the size for each Process: "<<endl;
    
    for(int i = 0; i < numP; i++){
        cin>>sizeP;
        pro.push_back(Process());
        pro[i].PID = i + 1;
        pro[i].memSize = sizeP;
    }
    
    cout<<endl;
    
    cout<<"Enter the number of Partitions: ";
    cin>>numPart;
    
    cout<<"Enter the size for each Process: "<<endl;
    
    for(int i = 0; i < numPart; i++){
        cin>>sizePart;
        part.push_back(Partition());
        part[i].PartID = i + 1;
        part[i].memSize = sizePart;
    }
    
    cout<<endl;
    
    bestFit(pro, part);
    firstFit(pro, part);
    nextFit(pro, part);
    worstFit(pro, part);
    worstFitDynamic(pro, part);
    
    
    return 0;
}

//200 100 300 300 200        100 300 200 450

void bestFit(vector<Process> pro, vector<Partition> part){
    
    int totalWaste = 0, currWaste[part.size()];
    
    cout<<"--------------------------------Best Fit--------------------------------"<<endl;
    cout<<"  PID             Partition ID             Waste             Status     "<<endl;
    
    
    for(int i = 0; i < pro.size(); i++){
        
        int temp = -1;
        
        //to get the temporary index of the partiontion with less waste for the process
        for(int k = 0; k < part.size(); k++)
            if((part[k].memSize >= pro[i].memSize) && (part[k].partStatus != "run")){
                if(temp == -1)
                    temp = k;
                else if(part[temp].memSize > part[k].memSize)
                    temp = k;
            }
        
        if(temp != -1){
            for(int j = temp; j < part.size(); j++){
                
                if((part[temp].memSize >= pro[i].memSize) && (part[temp].partStatus != "run")){
                    
                    //changing the status of the current process and partition
                    part[temp].partStatus = "run";
                    pro[i].pStatus = "run";
                    
                    //calculating current waste of the process and total waste
                    currWaste[j] = part[temp].memSize - pro[i].memSize;
                    totalWaste += currWaste[j];
                    
                    //output
                    cout<<"   "<<pro[i].PID<<setw(20)<<part[temp].PartID<<setw(23)<<currWaste[j]<<setw(19)<<part[temp].partStatus<<endl;
                    break;
                    
                    //if we don't have any partition for the process we display a display a default output
                }else if (j == part.size() - 1)
                    cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
            }
        }else
            cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
    }
        
    cout<<"Total Waste is: "<<totalWaste<<endl;
    
    cout<<"------------------------------------------------------------------------"<<endl;
    
    cout<<endl;
    
}
 

void firstFit(vector<Process> pro, vector<Partition> part){
    
    int totalWaste = 0, currWaste[part.size()];

    cout<<"--------------------------------First Fit--------------------------------"<<endl;
    cout<<"  PID             Partition ID             Waste             Status      "<<endl;
    
    //traversing through the processes and partitions to calculate and display
    for(int i = 0; i < pro.size(); i++)
        for(int j = 0; j < part.size(); j++){
            
            if((part[j].memSize >= pro[i].memSize) && (part[j].partStatus != "run")){
                
                //changing the status of the current process and partition
                part[j].partStatus = "run";
                pro[i].pStatus = "run";
                
                //calculating current waste of the process and total waste
                currWaste[j] = part[j].memSize - pro[i].memSize;
                totalWaste += currWaste[j];
                
                //output
                cout<<"   "<<pro[i].PID<<setw(20)<<part[j].PartID<<setw(23)<<currWaste[j]<<setw(19)<<part[j].partStatus<<endl;
                break;
                
                //if we don't have any partition for the process we display a display a default output
            }else if (j == part.size() - 1)
                cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
        }
    
    cout<<"Total Waste is: "<<totalWaste<<endl;
    
    cout<<"------------------------------------------------------------------------"<<endl;
    
    cout<<endl;
    
}


void nextFit(vector<Process> pro, vector<Partition> part){
    
    int totalWaste = 0, currWaste[part.size()], j = 0;

    cout<<"--------------------------------Next Fit--------------------------------"<<endl;
    cout<<"  PID             Partition ID             Waste             Status     "<<endl;
    
    //traversing through the processes and partitions to calculate and display
    for(int i = 0; i < pro.size(); i++)
        while(j < part.size()){
            
            if((part[j].memSize >= pro[i].memSize) && (part[j].partStatus != "run")){
                
                //changing the status of the current process and partition
                part[j].partStatus = "run";
                pro[i].pStatus = "run";
                
                //calculating current waste of the process and total waste
                currWaste[j] = part[j].memSize - pro[i].memSize;
                totalWaste += currWaste[j];
                
                //output
                cout<<"   "<<pro[i].PID<<setw(20)<<part[j].PartID<<setw(23)<<currWaste[j]<<setw(19)<<part[j].partStatus<<endl;
                break;
                
                //if we don't have any partition for the process we display a display a default output
            }else if (j == part.size() - 1){
                cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
                break;
            }
            
            j = (j + 1) % part.size(); //using module to circle around the partitions
        }
    
    cout<<"Total Waste is: "<<totalWaste<<endl;
    
    cout<<"------------------------------------------------------------------------"<<endl;
    
    cout<<endl;
    
}


void worstFit(vector<Process> pro, vector<Partition> part){
    
    int totalWaste = 0, currWaste[part.size()];

    cout<<"--------------------------------Worst Fit--------------------------------"<<endl;
    cout<<"  PID             Partition ID             Waste             Status      "<<endl;
    
    for(int i = 0; i < pro.size(); i++){
        
        int temp = -1;
        
        //to get the temporary index of the partiontion with less waste for the process
        for(int k = 0; k < part.size(); k++)
            if((part[k].memSize >= pro[i].memSize) && (part[k].partStatus != "run")){
                if(temp == -1)
                    temp = k;
                else if(part[temp].memSize < part[k].memSize)
                    temp = k;
            }
        
        //if we cant find a partition for the current process we output it as empty
        if(temp != -1){
            for(int j = temp; j < part.size(); j++){
                
                if((part[temp].memSize >= pro[i].memSize) && (part[temp].partStatus != "run")){
                    
                    //changing the status of the current process and partition
                    part[temp].partStatus = "run";
                    pro[i].pStatus = "run";
                    
                    //calculating current waste of the process and total waste
                    currWaste[j] = part[temp].memSize - pro[i].memSize;
                    totalWaste += currWaste[j];
                    
                    //output
                    cout<<"   "<<pro[i].PID<<setw(20)<<part[temp].PartID<<setw(23)<<currWaste[j]<<setw(19)<<part[temp].partStatus<<endl;
                    break;
                    
                //if we don't have any partition for the process we display a display a default output
                }else if (j == part.size() - 1)
                    cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
            }
        
        }else
            cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
    }
    
    cout<<"Total Waste is: "<<totalWaste<<endl;
    
    cout<<"------------------------------------------------------------------------"<<endl;
    
    cout<<endl;
    
}

void worstFitDynamic(vector<Process> pro, vector<Partition> part){
    
    int totalWaste = 0, currWaste[part.size()];

    cout<<"------------------------------Worst Fit Dynamic--------------------------------"<<endl;
    cout<<"  PID             Partition ID             Waste             Status      "<<endl;
    
    for(int i = 0; i < pro.size(); i++){
        
        int temp = -1;
        
        //to get the temporary index of the partiontion with less waste for the process
        for(int k = 0; k < part.size(); k++)
            if((part[k].memSize >= pro[i].memSize) && (part[k].partStatus != "run")){
                if(temp == -1)
                    temp = k;
                else if(part[temp].memSize < part[k].memSize)
                    temp = k;
            }
        
        //if we cant find a partition for the current process we output it as empty
        if(temp != -1){
            for(int j = temp; j < part.size(); j++){
                
                if((part[temp].memSize >= pro[i].memSize) && (part[temp].partStatus != "run")){
                    
                    //changing the status of the current process and partition
                    part[temp].partStatus = "run";
                    pro[i].pStatus = "run";
                    
                    //calculating current waste of the process and total waste
                    currWaste[j] = part[temp].memSize - pro[i].memSize;
                    
                    //making it dynamic by creating a new partition from the waste of the current one assigned for the algorithm
                    if(currWaste[j] > 0){
                        part.push_back(Partition());
                        part[part.size() - 1].PartID = part[temp].PartID + 1;
                        part[part.size() - 1].memSize = currWaste[j];
                        currWaste[j] = 0;
                    }
                    
                    totalWaste += currWaste[j];
                    
                    //output
                    cout<<"   "<<pro[i].PID<<setw(20)<<part[temp].PartID<<setw(23)<<currWaste[j]<<setw(19)<<part[temp].partStatus<<endl;
                    break;
                    
                //if we don't have any partition for the process we display a display a default output
                }else if (j == part.size() - 1)
                    cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
            }
        
        }else
            cout<<"   "<<pro[i].PID<<setw(20)<<"-"<<setw(23)<<"-"<<setw(19)<<pro[i].pStatus<<endl;
    }
    
    cout<<"Total Waste is: "<<totalWaste<<endl;
    
    cout<<"------------------------------------------------------------------------"<<endl;
    
    cout<<endl;
    
}
