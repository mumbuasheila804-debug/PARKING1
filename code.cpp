#include<iostream>
#include<unordered_map>
#include<queue>
#include<chrono>
#include<string>
#include<cmath>
using namespace std;

struct ParkingSession
{
    string licensePlate;
    int spotId;
    chrono::system_clock::time_point checkInTime;
};
class ParkingLot
{
    private:
    int totalSpots;
    double hourlyRate;
    priority_queue<int,vector<int>,greater<int>> availableSpots;
    unordered_map<string, ParkingSession> activeSessions;

    public:
    ParkingLot(int capacity,double rate)
    {
        totalSpots=capacity;
        hourlyRate=rate;
        for (int i=1;i<=capacity;i++)
        {
            availableSpots.push(i);
        }
    }
    int getAvailableSpots()
    {
        return availableSpots.size();

    }
    bool isFull()
        {
            return availableSpots.empty();
        }
    
        bool checkInVehicle(string licensePlate)
        {
            if(isFull())
            {
                cout<<"\n FULL!Please wait\n";
                return false;
            }
            if (activeSessions.find(licensePlate)!=activeSessions.end())
            {
                cout<<"\n[ERROR]Vehicle already checked in!\n";
                return false;
            }
            int assignedSpot=availableSpots.top();
            availableSpots.pop();
            
            ParkingSession session;
            session.licensePlate=licensePlate;
            session.spotId=assignedSpot;
            session.checkInTime=chrono::system_clock::now();
            activeSessions[licensePlate]=session;

            cout<<"\n WELCOME TO SHEILA'S PARKING[LICENSE PLATE:"<<licensePlate<<"] SPOT#"<< session.spotId << "\n";
            return true;
            }

            bool checkOutVehicle(string licensePlate)
            {
                auto it=activeSessions.find(licensePlate);
                if(it==activeSessions.end())
                {
                    cout<<"\n[ERROR]No match!\n";
                    return false;
                }
                ParkingSession session= it->second;
                auto checkOutTime=chrono::system_clock::now();
                chrono::duration<double>duration=checkOutTime-session.checkInTime;
                double totalMinutes=duration.count()/60.0;
                double fee=0.0;
                if(totalMinutes<=30)
                {
                    fee=0.0;
                }
                else if(totalMinutes<=60)
                
            {
                fee=50.0;

                }
                else{
                    double extraMinutes=totalMinutes-60;
                    double extraHours=ceil(extraMinutes/60.0);
                    fee= 50.0+(extraHours * 50.0);
                }
            
            activeSessions.erase(it);
            availableSpots.push(session.spotId);

            cout<<"\n==========================\n"<< endl;
            cout<<"\n       YOUR RECEIPT       \n"<< endl;
            cout<<"\n CAR PLATE NUMBER:" << session.licensePlate<< endl;
            cout<<"\n EMPTY SPOT ID:#"<<session.spotId<< endl;
            cout<<"\n YOUR PARKING TIME IS:"<<totalMinutes<<"min(s)" <<endl;
            cout<<"\n YOUR FEE IS: Sh."<<fee<<endl;
            cout<<"\n AVAILABLE SPOTS:"<<getAvailableSpots()<<endl;
            return true;

        }
};
int main()
{
    ParkingLot myLot(250,50.0);
    int choice;
    string licensePlate;

    for(;;)
    {
        cout<<"\n========WELCOME TO SHEILA'S PARKING=========\n";
        cout<<"Slots available:"<<myLot.getAvailableSpots()<<"/250\n";
        cout<<"1.Check in vehicle\n";
        cout<<"2.Check out vehicle\n";
        cout<<"3.Exit\n";
        cout<<"Select your action(ie 1-3):";
        cin>>choice;
        
        switch(choice)
        {
            case 1:
            cout<<"Enter license plate:";
            cin>>licensePlate;
            myLot.checkInVehicle(licensePlate);
            break;

            case 2:
            cout<<"Enter license plate:";
            cin>>licensePlate;
            myLot.checkOutVehicle(licensePlate);
            break;
            
            case 3:
            cout<<"THANKS FOR USING OUR PARKING LOT!\n";
            return 0;
             
            default:
            cout<<"INVALID-CHOOSE 1,2,3\n";
            break;
        


        }
    }
    return 0;
}


