#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<ctime>
#include<cstdlib>
#define infinity 999999999

using namespace std;

struct store
{
	long long int cost[20];
	long long int time[20];
	int array[20];
	int parent[20];
	int parent_time[20];
}travel[15];

struct initialdata{
	long long int cost[20];
	long long int time[20];
}ini[15];

struct Route{
	vector<int> path;
	long long int cost;
	long long int time;
};

class datamodule{
	public:
	string city[15];
	
	datamodule():city{"Delhi","Mumbai","Chennai","Kolkata","Kerala","Hyderabad","Pune","Goa","Bangalore","Amritsar","Jaipur","Patna","Puducherry","Srinagar","Bhopal"}{}
	
	void costdeclaration(){
		int N,i,j;
		N=15;

		long long int arr[15][15]={{0,3500,2000,infinity,1000,infinity,infinity,infinity,infinity,7000,4000,1500,infinity,6500,infinity},
								   {3500,0,infinity,1520,infinity,infinity,infinity,2500,infinity,infinity,infinity,infinity,infinity,infinity,5000},
							       {2000,infinity,0,1500,infinity,3000,infinity,infinity,infinity,infinity,2000,1000,infinity,infinity,1500},
							       {infinity,1520,1500,0,infinity,1200,4500,infinity,6000,infinity,infinity,infinity,infinity,infinity,1000},
							       {1000,infinity,infinity,infinity,0,1500,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,3000,1200,1500,0,1950,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,infinity,4500,infinity,1950,0,infinity,infinity,2050,infinity,infinity,infinity,infinity,infinity},
							       {infinity,2500,infinity,infinity,infinity,infinity,infinity,0,5000,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,infinity,6000,infinity,infinity,infinity,5000,0,7000,infinity,infinity,infinity,infinity,infinity},
							       {7000,infinity,infinity,infinity,infinity,infinity,2050,infinity,7000,0,infinity,infinity,infinity,infinity,infinity},
							       {4000,infinity,2000,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity,infinity,infinity},
							       {1500,infinity,1000,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity,infinity},
							       {infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity},
							       {6500,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity},
							       {infinity,5000,1500,1000,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0}};

		long long int timearr[15][15]={{0,2,3,infinity,2,infinity,infinity,infinity,infinity,4,3,2,infinity,5,infinity},
								   {2,0,infinity,2,infinity,infinity,infinity,1,infinity,infinity,infinity,infinity,infinity,infinity,3},
							       {3,infinity,0,2,infinity,2,infinity,infinity,infinity,infinity,3,2,infinity,infinity,2},
							       {infinity,2,2,0,infinity,2,3,infinity,4,infinity,infinity,infinity,infinity,infinity,2},
							       {2,infinity,infinity,infinity,0,2,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,2,2,2,0,1,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,infinity,3,infinity,1,0,infinity,infinity,2,infinity,infinity,infinity,infinity,infinity},
							       {infinity,1,infinity,infinity,infinity,infinity,infinity,0,3,infinity,infinity,infinity,infinity,infinity,infinity},
							       {infinity,infinity,infinity,4,infinity,infinity,infinity,3,0,4,infinity,infinity,infinity,infinity,infinity},
							       {4,infinity,infinity,infinity,infinity,infinity,2,infinity,4,0,infinity,infinity,infinity,infinity,infinity},
							       {3,infinity,3,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity,infinity,infinity},
							       {2,infinity,2,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity,infinity},
							       {infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity,infinity},
							       {5,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0,infinity},
							       {infinity,3,2,2,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0}};

		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				travel[i].cost[j]=arr[i][j];
				travel[i].time[j]=timearr[i][j];
				travel[i].array[j]=j;
				travel[i].parent[j]=-1;
				travel[i].parent_time[j]=-1;
				ini[i].cost[j]=arr[i][j];
				ini[i].time[j]=timearr[i][j];
			}
		}
	}
	
	void displayCities(){
		cout<<"\n";
		cout<<"========================================================\n";
		cout<<"              AVAILABLE CITIES FOR TRAVEL               \n";
		cout<<"========================================================\n";
		for(int i=0;i<15;i++){
			cout<<"  "<<(i+1)<<". "<<city[i]<<endl;
		}
		cout<<"========================================================\n";
	}
};

class bellmanfordalgorithm:public datamodule{
	public:
	int N,i,j,k;
	bellmanfordalgorithm(){
		N=15;
	}
	
	void bellman_ford_cost(){
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<N;k++){
					if(travel[i].cost[j]>travel[i].cost[k]+travel[k].cost[j])
					{
						travel[i].cost[j]=travel[i].cost[k]+travel[k].cost[j];
						travel[i].parent[j]=k;
					}
				}
			}
		}
	}
	
	void bellman_ford_time(){
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				for(k=0;k<N;k++){
					if(travel[i].time[j]>travel[i].time[k]+ini[k].time[j])
					{
						travel[i].time[j]=travel[i].time[k]+ini[k].time[j];
						travel[i].parent_time[j]=k;
					}
				}
			}
		}
	}
	
	void dijkstra_cost(){
		for(int src=0; src<N; src++){
			vector<long long> dist(N, infinity);
			dist[src] = 0;
			priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
			pq.push({0, src});
			vector<int> prev(N, -1);
			while(!pq.empty()){
				pair<long long, int> p = pq.top(); pq.pop();
				long long cost = p.first;
				int u = p.second;
				if(cost > dist[u]) continue;
				for(int v=0; v<N; v++){
					if(ini[src].cost[v] < infinity && dist[v] > dist[u] + ini[src].cost[v]){
						dist[v] = dist[u] + ini[src].cost[v];
						prev[v] = u;
						pq.push({dist[v], v});
					}
				}
			}
			for(int j=0; j<N; j++){
				travel[src].cost[j] = dist[j];
				travel[src].parent[j] = prev[j];
			}
		}
	}
	
	void dijkstra_time(){
		for(int src=0; src<N; src++){
			vector<long long> dist(N, infinity);
			dist[src] = 0;
			priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
			pq.push({0, src});
			vector<int> prev(N, -1);
			while(!pq.empty()){
				pair<long long, int> p = pq.top(); pq.pop();
				long long time_val = p.first;
				int u = p.second;
				if(time_val > dist[u]) continue;
				for(int v=0; v<N; v++){
					if(ini[src].time[v] < infinity && dist[v] > dist[u] + ini[src].time[v]){
						dist[v] = dist[u] + ini[src].time[v];
						prev[v] = u;
						pq.push({dist[v], v});
					}
				}
			}
			for(int j=0; j<N; j++){
				travel[src].time[j] = dist[j];
				travel[src].parent_time[j] = prev[j];
			}
		}
	}
};

class filehandlingmodule{
	public:
	string username1,password1;
	
	bool log_in(string username,string password){
		ifstream fileread;
		fileread.open("login.txt");
		while(fileread>>username1>>password1){
			if((username==username1)&&(password==password1)){
				cout<<"\n    Login Successful! Welcome "<<username<<"!\n";
				return true;
			}
		}
		cout<<"\n    Invalid username or password.\n";
		return false;
	}
	
	void createaccount(string username,string password){
		ofstream filewrite;
		filewrite.open("login.txt",ios::app);
		filewrite<<username<<" "<<password<<"\n";
		filewrite.close();
		cout<<"\n    Account Created Successfully!\n";
	}
	
	void ticket(string username, vector<string> firstname, vector<string> lastname, vector<string> sex, vector<int> age, int no){
		ofstream filewrite;
		filewrite.open("ticket.txt",ios::app);
		for(int i=0;i<no;i++){
			filewrite<<username<<" "<<firstname[i]<<" "<<lastname[i]<<" "<<sex[i]<<" "<<age[i]<<"\n";
		}
		filewrite.close();
	}
	
	string generatePNR(){
		string pnr="";
		srand(time(0)+rand());
		for(int i=0;i<10;i++){
			int choice=rand()%2;
			if(choice==0){
				pnr+=(char)('A'+rand()%26);
			}
			else{
				pnr+=(char)('0'+rand()%10);
			}
		}
		return pnr;
	}
	
	void saveTicketWithPNR(string pnr,string username,string source,string destination,int no,int totalprice){
		ofstream filewrite;
		filewrite.open("pnr_tickets.txt",ios::app);
		filewrite<<pnr<<" "<<username<<" "<<source<<" "<<destination<<" "<<no<<" "<<totalprice<<"\n";
		filewrite.close();
	}
	
	bool searchPNR(string pnr){
		ifstream fileread;
		fileread.open("pnr_tickets.txt");
		string pnr1,username,source,destination;
		int no,price;
		bool found=false;
		
		while(fileread>>pnr1>>username>>source>>destination>>no>>price){
			if(pnr==pnr1){
				found=true;
				system("CLS");
				cout<<"\n========================================================\n";
				cout<<"                   TICKET DETAILS                       \n";
				cout<<"========================================================\n";
				cout<<"  PNR: "<<pnr<<endl;
				cout<<"  Booked By: "<<username<<endl;
				cout<<"  From: "<<source<<endl;
				cout<<"  To: "<<destination<<endl;
				cout<<"  Passengers: "<<no<<endl;
				cout<<"  Total Cost: Rs. "<<price<<endl;
				cout<<"========================================================\n";
				break;
			}
		}
		fileread.close();
		
		if(!found){
			cout<<"\n    PNR Not Found in System.\n";
		}
		return found;
	}
	
	void showBookings(string username){
		ifstream fileread("pnr_tickets.txt");
		if(!fileread){
			cout << "No bookings found.\n";
			return;
		}
		string pnr, user, source, dest;
		int no, price;
		bool found = false;
		while(fileread >> pnr >> user >> source >> dest >> no >> price){
			if(user == username){
				cout << "\n========================================================\n";
				cout << "                   TICKET DETAILS                       \n";
				cout << "========================================================\n";
				cout << "  PNR: " << pnr << endl;
				cout << "  Booked By: " << user << endl;
				cout << "  From: " << source << endl;
				cout << "  To: " << dest << endl;
				cout << "  Passengers: " << no << endl;
				cout << "  Total Cost: Rs. " << price << endl;
				cout << "========================================================\n";
				found = true;
			}
		}
		if(!found){
			cout << "No bookings found for " << username << ".\n";
		}
		fileread.close();
	}
	
	void changePassword(string username){
		string newpass;
		cout << "Enter new password: ";
		cin >> newpass;
		ifstream infile("login.txt");
		ofstream outfile("temp.txt");
		string u, p;
		bool updated = false;
		while(infile >> u >> p){
			if(u == username){
				outfile << u << " " << newpass << "\n";
				updated = true;
			}
			else{
				outfile << u << " " << p << "\n";
			}
		}
		infile.close();
		outfile.close();
		remove("login.txt");
		rename("temp.txt", "login.txt");
		if(updated){
			cout << "Password changed successfully.\n";
		}
		else{
			cout << "User not found.\n";
		}
	}
	
	void deleteAccount(string username){
		ifstream infile("login.txt");
		ofstream outfile("temp.txt");
		string u, p;
		bool deleted = false;
		while(infile >> u >> p){
			if(u != username){
				outfile << u << " " << p << "\n";
			}
			else{
				deleted = true;
			}
		}
		infile.close();
		outfile.close();
		remove("login.txt");
		rename("temp.txt", "login.txt");
		if(deleted){
			cout << "Account deleted successfully.\n";
		}
		else{
			cout << "User not found.\n";
		}
	}
};

class inputmodule{
	public:
	string source,destination;
	string username,password;
	
	void user_input(string userchoice[],datamodule &obj){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"           TRAVEL BOOKING - SELECT ROUTE                \n";
		cout<<"========================================================\n";
		
		obj.displayCities();
		
		int srcnum,dstnum;
		cout<<"\nEnter Source City Number (1-15): ";
		cin>>srcnum;
		cout<<"Enter Destination City Number (1-15): ";
		cin>>dstnum;
		
		if(srcnum<1 || srcnum>15 || dstnum<1 || dstnum>15){
			cout<<"\n    Invalid city selection!\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			userchoice[0]="";
			userchoice[1]="";
			return;
		}
		
		if(srcnum == dstnum){
			cout<<"\n    Source and destination cannot be same!\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			userchoice[0]="";
			userchoice[1]="";
			return;
		}
		
		userchoice[0]=obj.city[srcnum-1];
		userchoice[1]=obj.city[dstnum-1];
	}
	
	string login(){
		while(1){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"         TRAVEL BOOKING SYSTEM - LOGIN                  \n";
		cout<<"========================================================\n\n";
		cout<<"  1. Login\n";
		cout<<"  2. Create New Account\n";
		cout<<"\n========================================================\n";
		cout<<"Enter Your Choice: ";
		int ch;
		bool res=false;
		filehandlingmodule fobj;
		cin>>ch;
		
		switch(ch){
			case 1:
				system("CLS");
				cout<<"\n========================================================\n";
				cout<<"                    USER LOGIN                          \n";
				cout<<"========================================================\n";
				cout<<"Enter Username: ";
				cin>>username;
				cout<<"Enter Password: ";
				cin>>password;
				res=fobj.log_in(username,password);
				if(res){
					cout<<"\nPress any key to continue...";
					cin.ignore();
					cin.get();
				}
				else{
					cout<<"\nPress any key to try again...";
					cin.ignore();
					cin.get();
				}
				break;
			case 2:
				system("CLS");
				cout<<"\n========================================================\n";
				cout<<"                 CREATE NEW ACCOUNT                     \n";
				cout<<"========================================================\n";
				cout<<"Choose Username: ";
				cin>>username;
				cout<<"Choose Password: ";
				cin>>password;
				fobj.createaccount(username,password);
				res=true;
				cout<<"\nPress any key to continue...";
				cin.ignore();
				cin.get();
				break;
		}
		if(res==true)
			return username;
		}
	}
	
	int noofpassenger(){
		int no;
		cout<<"\nEnter Number of Passengers: ";
		cin>>no;
		return no;
	}
};

class outputmodule{
	public:
	string source,destination;
	
	void initial(){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"           TRAVEL BOOKING SYSTEM - MAIN MENU            \n";
		cout<<"========================================================\n\n";
		cout<<"  1. Book Ticket\n";
		cout<<"  2. Check Ticket\n";
		cout<<"  3. My Bookings\n";
		cout<<"  4. Settings\n";
		cout<<"  5. Exit\n";
		cout<<"\n========================================================\n";
	}
	
	void list_cities(datamodule &o){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"           TRAVEL BOOKING SYSTEM - CITIES               \n";
		cout<<"========================================================\n";
		o.displayCities();
	}
	
	void ticket(int total_price,int no,string source,string destination,string username,string pnr){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"                  BOOKING SUCCESSFUL!                   \n";
		cout<<"========================================================\n";
		cout<<"  PNR: "<<pnr<<endl;
		cout<<"  Passenger Name: "<<username<<endl;
		cout<<"  From: "<<source<<endl;
		cout<<"  To: "<<destination<<endl;
		cout<<"  Number of Passengers: "<<no<<endl;
		cout<<"  Total Cost: Rs. "<<total_price<<endl;
		cout<<"========================================================\n";
		cout<<"\n  Please save your PNR for future reference.\n";
	}
	
	void passengerdetailedticket(int no, vector<string> firstname, vector<string> lastname, vector<string> sex, vector<int> age){
		cout<<"\n========================================================\n";
		cout<<"                 PASSENGER DETAILS                      \n";
		cout<<"========================================================\n";
		for(int i=0;i<no;i++){
			cout<<"\n  Passenger "<<(i+1)<<":\n";
			cout<<"    Name: "<<firstname[i]<<" "<<lastname[i]<<endl;
			cout<<"    Age: "<<age[i]<<"  |  Sex: "<<sex[i]<<endl;
		}
		cout<<"\n========================================================\n";
		cout<<"\nPress any key to continue...";
		cin.ignore();
		cin.get();
	}
	
	vector<Route> getTopThreeRoutes(int src,int dst,datamodule &o){
		vector<Route> routes;
		
		// Route 1: Cheapest by cost
		Route r1;
		r1.cost = travel[src].cost[dst];
		r1.time = 0;
		r1.path.clear();
		
		// Build path using parent
		vector<int> tempPath;
		int curr = dst;
		while(curr != src){
			tempPath.push_back(curr);
			curr = travel[src].parent[curr];
			if(curr == -1) break;
		}
		tempPath.push_back(src);
		reverse(tempPath.begin(), tempPath.end());
		r1.path = tempPath;
		
		// Calculate time for route 1
		for(size_t i=0;i<r1.path.size()-1;i++){
			int u = r1.path[i];
			int v = r1.path[i+1];
			if(ini[u].time[v] != infinity){
				r1.time += ini[u].time[v];
			}
		}
		routes.push_back(r1);
		
		// Route 2: Fastest by time
		Route r2;
		r2.cost = 0;
		r2.time = travel[src].time[dst];
		r2.path.clear();
		
		// Build path using parent_time
		tempPath.clear();
		curr = dst;
		while(curr != src){
			tempPath.push_back(curr);
			curr = travel[src].parent_time[curr];
			if(curr == -1) break;
		}
		tempPath.push_back(src);
		reverse(tempPath.begin(), tempPath.end());
		r2.path = tempPath;
		
		// Calculate cost for route 2
		for(size_t i=0;i<r2.path.size()-1;i++){
			int u = r2.path[i];
			int v = r2.path[i+1];
			if(ini[u].cost[v] != infinity){
				r2.cost += ini[u].cost[v];
			}
		}
		
		// Check if different from r1
		if(r2.path != r1.path){
			routes.push_back(r2);
		}
		
		// Route 3: Direct flight (if available)
		if(ini[src].cost[dst] != infinity){
			Route r3;
			r3.path.push_back(src);
			r3.path.push_back(dst);
			r3.cost = ini[src].cost[dst];
			r3.time = ini[src].time[dst];
			
			// Check if different from existing
			bool isDifferent = true;
			for(auto &r : routes){
				if(r.path == r3.path){
					isDifferent = false;
					break;
				}
			}
			if(isDifferent){
				routes.push_back(r3);
			}
		}
		
		// If less than 3, add more alternatives
		if(routes.size() < 3){
			vector<Route> alternatives;
			
			// Check 1-stop routes
			for(int hub=0; hub<15; hub++){
				if(hub != src && hub != dst){
					if(ini[src].cost[hub] != infinity && ini[hub].cost[dst] != infinity){
						Route r;
						r.path = {src, hub, dst};
						r.cost = ini[src].cost[hub] + ini[hub].cost[dst];
						r.time = ini[src].time[hub] + ini[hub].time[dst];
						
						// Check if different
						bool isDifferent = true;
						for(auto &existing : routes){
							if(existing.path == r.path){
								isDifferent = false;
								break;
							}
						}
						if(isDifferent){
							alternatives.push_back(r);
						}
					}
				}
			}
			
			// Sort alternatives by cost
			sort(alternatives.begin(), alternatives.end(), [](const Route &a, const Route &b){
				return a.cost < b.cost;
			});
			
			// Add up to needed
			for(size_t i=0; i<alternatives.size() && routes.size()<3; i++){
				routes.push_back(alternatives[i]);
			}
		}
		
		return routes;
	}
	
	void displayTopThreeRoutes(vector<Route> &routes,datamodule &o,int src,int dst){
		cout<<"\n========================================================\n";
		cout<<"              TOP AVAILABLE ROUTES                      \n";
		cout<<"========================================================\n\n";
		
		for(int i=0;i<routes.size();i++){
			cout<<"  OPTION "<<(i+1)<<":\n";
			cout<<"    Route: ";
			for(int j=0;j<routes[i].path.size();j++){
				cout<<o.city[routes[i].path[j]];
				if(j < routes[i].path.size()-1){
					cout<<" -> ";
				}
			}
			cout<<endl;
			cout<<"    Cost: Rs. "<<routes[i].cost<<endl;
			cout<<"    Time: "<<routes[i].time<<" hours\n\n";
		}
		cout<<"========================================================\n";
	}
	
	int display_price(string source,string destination,int N,string username,datamodule &o){
		inputmodule in;
		int i,j;
		
		// Find city indices
		int srcIdx = -1, dstIdx = -1;
		for(i=0;i<N;i++){
			if(source == o.city[i]) srcIdx = i;
			if(destination == o.city[i]) dstIdx = i;
		}
		
		if(srcIdx == -1 || dstIdx == -1){
			cout<<"\n    Invalid city names!\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			return 0;
		}
		
		if(srcIdx == dstIdx){
			cout<<"\n    Source and destination cannot be same!\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			return 0;
		}
		
		// Get top 3 routes
		vector<Route> routes = getTopThreeRoutes(srcIdx, dstIdx, o);
		
		if(routes.empty() || routes[0].cost >= infinity){
			cout<<"\n    No routes available between these cities.\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			return 0;
		}
		
		// Display routes
		displayTopThreeRoutes(routes, o, srcIdx, dstIdx);
		
		int choiceofroute;
		cout<<"\nSelect Route (1-"<<routes.size()<<"): ";
		cin>>choiceofroute;
		
		if(choiceofroute<1 || choiceofroute>routes.size()){
			cout<<"\n    Invalid route selection!\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
			return 0;
		}
		
		Route selectedRoute = routes[choiceofroute-1];
		
		char c;
		cout<<"\nDo you want to continue? (Y/N): ";
		cin>>c;
		
		if(c=='Y' || c=='y'){
			int no=in.noofpassenger();
			vector<string> firstname(no), lastname(no), sex(no);
			vector<int> age(no);
			
			for(int i=0;i<no;i++){
				cout<<"\n  Passenger "<<(i+1)<<" Details:\n";
				cout<<"  First Name: ";
				cin>>firstname[i];
				cout<<"  Last Name: ";
				cin>>lastname[i];
				cout<<"  Sex (M/F/O): ";
				cin>>sex[i];
				cout<<"  Age: ";
				cin>>age[i];
			}
			
			int total_price = no * selectedRoute.cost;
			
			cout<<"\n========================================================\n";
			cout<<"  Total Price: Rs. "<<total_price<<endl;
			cout<<"========================================================\n";
			
			char y;
			cout<<"\nConfirm Booking? (Y/N): ";
			cin>>y;
			
			if(y=='Y' || y=='y'){
				filehandlingmodule f;
				string pnr=f.generatePNR();
				
				f.ticket(username,firstname,lastname,sex,age,no);
				f.saveTicketWithPNR(pnr,username,source,destination,no,total_price);
				
				ticket(total_price,no,source,destination,username,pnr);
				passengerdetailedticket(no,firstname,lastname,sex,age);
			}
			else{
				cout<<"\n    Booking Cancelled.\n";
				cout<<"Press any key to continue...";
				cin.ignore();
				cin.get();
			}
		}
		else{
			cout<<"\n    Booking Cancelled.\n";
			cout<<"Press any key to continue...";
			cin.ignore();
			cin.get();
		}
		return 0;
	}
	
	void checkPNR(){
		filehandlingmodule f;
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"                CHECK TICKET BY PNR                     \n";
		cout<<"========================================================\n";
		cout<<"Enter PNR Number: ";
		string pnr;
		cin>>pnr;
		
		f.searchPNR(pnr);
		
		cout<<"\nPress any key to continue...";
		cin.ignore();
		cin.get();
	}
	
	void myBookings(string username){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"                   MY BOOKINGS                          \n";
		cout<<"========================================================\n";
		filehandlingmodule f;
		f.showBookings(username);
		cout<<"\nPress any key to continue...";
		cin.ignore();
		cin.get();
	}
	
	void settings(string &username){
		system("CLS");
		cout<<"\n========================================================\n";
		cout<<"                     SETTINGS                           \n";
		cout<<"========================================================\n";
		cout<<"1. Change Password\n";
		cout<<"2. Delete Account\n";
		cout<<"Enter choice: ";
		int ch;
		cin>>ch;
		filehandlingmodule f;
		if(ch == 1){
			f.changePassword(username);
		}
		else if(ch == 2){
			f.deleteAccount(username);
			username = "";
		}
		else{
			cout<<"Invalid choice.\n";
		}
		cout<<"\nPress any key to continue...";
		cin.ignore();
		cin.get();
	}
};

int main(){
	int N;
	N=15;
	
	datamodule obj;
	obj.costdeclaration();
	
	bellmanfordalgorithm ob;
	ob.bellman_ford_cost();
	ob.bellman_ford_time();
	
	string userchoice[2];
	inputmodule obj1;
	
	string username;
	username=obj1.login();
	
	outputmodule object;
	object.initial();
		
	while(1){
		int choice;
		cout<<"Enter Your Choice: ";
		cin>>choice;
		
		switch(choice){
			case 1:
				obj1.user_input(userchoice,obj);
				if(userchoice[0]!="" && userchoice[1]!=""){
					object.display_price(userchoice[0],userchoice[1],N,username,obj);
				}
				object.initial();
				break;
			case 2:
				object.checkPNR();
				object.initial();
				break;
			case 3:
				object.myBookings(username);
				object.initial();
				break;
			case 4:
				object.settings(username);
				if(username == ""){
					username = obj1.login();
				}
				object.initial();
				break;
			case 5:
				system("CLS");
				cout<<"\n========================================================\n";
				cout<<"     Thank You for Using Travel Booking System!        \n";
				cout<<"========================================================\n\n";
				return 0;
		}
	}
return 0;
}
