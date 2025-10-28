#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <limits>

#define infinity 999999999

using namespace std;

struct store {
    long long int cost[20];
    int array[20];
} travel[15];

struct initialdata {
    long long int cost[20];
} ini[15];

static string to_lower_str(const string &s) {
    string r = s;
    transform(r.begin(), r.end(), r.begin(), [](unsigned char c) { return std::tolower(c); });
    return r;
}

static string trim(const string &s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

class datamodule {
public:
    string city[15];

    datamodule() : city{"Delhi","Mumbai","Chennai","Kolkata","Kerala","Hyderabad","Pune","Goa",
                        "Bangalore","Amritsar","Jaipur","Patna","Puducherry","Srinagar","Bhopal"} {}

    void costdeclaration() {
        int N = 15;
        long long int arr[15][15] = {
            {0,3500,2000,infinity,1000,infinity,infinity,infinity,infinity,7000,4000,1500,infinity,6500,infinity},
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
            {infinity,5000,1500,1000,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,infinity,0}
        };

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                travel[i].cost[j] = arr[i][j];
                travel[i].array[j] = j;
                ini[i].cost[j] = arr[i][j];
            }
        }
    }
};

class bellmanfordalgorithm : public datamodule {
public:
    int N;
    bellmanfordalgorithm() { N = 15; }

    void algorithmic_implementation() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    if (travel[i].cost[k] < infinity && travel[k].cost[j] < infinity) {
                        if (travel[i].cost[j] > travel[i].cost[k] + travel[k].cost[j]) {
                            travel[i].cost[j] = travel[i].cost[k] + travel[k].cost[j];
                            travel[i].array[j] = travel[i].array[k];
                        }
                    }
                }
            }
        }
    }
};

class filehandlingmodule {
public:
    string username1, password1;

    bool log_in(string username, string password) {
        ifstream fileread("login.txt");
        while (fileread >> username1 >> password1) {
            if (username == username1 && password == password1) {
                cout << "\nAccount Login Successful...\n";
                return true;
            }
        }
        cout << "\nAccount Login Failed...\n";
        return false;
    }

    void createaccount(string username, string password) {
        ofstream filewrite("login.txt", ios::app);
        filewrite << username << " " << password << "\n";
        filewrite.close();
        cout << "\nAccount Created Successfully...\n";
    }

    void ticket(string username, const vector<string>& firstname, const vector<string>& lastname,
                const vector<string>& sex, const vector<int>& age, int no) {
        ofstream filewrite("ticket.txt", ios::app);
        for (int i = 0; i < no; i++)
            filewrite << username << " " << firstname[i] << " " << lastname[i]
                      << " " << sex[i] << " " << age[i] << "\n";
        filewrite.close();
    }
};

class inputmodule {
public:
    string source, destination;
    string username, password;

    string read_nonempty_line(const string &prompt) {
        string s;
        while (true) {
            cout << prompt;
            if (!getline(cin, s)) return "";
            s = trim(s);
            if (!s.empty()) return s;
        }
    }

    void user_input(string userchoice[]) {
        #ifdef _WIN32
        system("CLS");
        #else
        system("clear");
        #endif
        cout << "\n********** Travel Management System **********\n";
        source = read_nonempty_line("Enter Your City: ");
        destination = read_nonempty_line("Enter Your Destination: ");
        userchoice[0] = source;
        userchoice[1] = destination;
    }

    string login() {
        while (true) {
            cout << "\n********** Travel Management System **********\n";
            cout << "1. Login\n";
            cout << "2. Create New Account\n";
            cout << "Enter Your Choice: ";

            string line;
            if (!getline(cin, line)) return "";
            line = trim(line);
            if (line.empty()) continue;

            int ch = 0;
            try { ch = stoi(line); } catch (...) { cout << "Invalid choice.\n"; continue; }

            filehandlingmodule fobj;
            if (ch == 1) {
                cout << "Enter Username: ";
                getline(cin, username);
                username = trim(username);
                cout << "Enter Password: ";
                getline(cin, password);
                password = trim(password);
                if (fobj.log_in(username, password)) return username;
            } else if (ch == 2) {
                cout << "Enter Username: ";
                getline(cin, username);
                username = trim(username);
                cout << "Enter Password: ";
                getline(cin, password);
                password = trim(password);
                fobj.createaccount(username, password);
                cout << "Please login with your new account.\n";
            } else {
                cout << "Invalid choice. Please enter 1 or 2.\n";
            }
        }
    }

    int noofpassenger() {
        while (true) {
            cout << "Enter number of passengers: ";
            string line;
            if (!getline(cin, line)) return 0;
            line = trim(line);
            try {
                int n = stoi(line);
                if (n > 0 && n < 100) return n;
            } catch (...) {}
            cout << "Invalid number. Please enter between 1-99.\n";
        }
    }
};

class outputmodule {
public:
    void initial() {
        #ifdef _WIN32
        system("CLS");
        #else
        system("clear");
        #endif
        cout << "\n********** Travel Management System **********\n";
        cout << "1. Display List of Cities\n";
        cout << "2. Book Ticket\n";
    }

    void list_cities(int N) {
        datamodule o;
        #ifdef _WIN32
        system("CLS");
        #else
        system("clear");
        #endif
        cout << "\nAvailable Cities:\n";
        for (int i = 0; i < N; i++) cout << "- " << o.city[i] << endl;
    }

    void ticket(int total_price, int no, const string &source, const string &destination, const string &username) {
        cout << "\n********** E-TICKET **********\n";
        cout << "User: " << username << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Passengers: " << no << endl;
        cout << "Total Cost: " << total_price << endl;
        cout << "*****************************\n";
    }

    vector<int> reconstruct_path(int src, int dest) {
        vector<int> path;
        if (src < 0 || dest < 0 || src >= 15 || dest >= 15) return path;
        if (travel[src].cost[dest] >= infinity) return path;
        int cur = src;
        path.push_back(cur);
        for (int safety = 0; safety < 100; ++safety) {
            if (cur == dest) break;
            int next = travel[cur].array[dest];
            if (next == cur || next < 0 || next >= 15) break;
            path.push_back(next);
            cur = next;
        }
        if (path.back() != dest) path.push_back(dest);
        return path;
    }

    int display_price(string source_in, string destination_in, int N, string username) {
        datamodule o;
        inputmodule in;
        string s_l = to_lower_str(trim(source_in));
        string d_l = to_lower_str(trim(destination_in));

        int iidx = -1, jidx = -1;
        for (int i = 0; i < N; i++) {
            if (s_l == to_lower_str(o.city[i])) iidx = i;
            if (d_l == to_lower_str(o.city[i])) jidx = i;
        }

        if (iidx == -1 || jidx == -1) {
            cout << "Invalid city name(s). Try again.\n";
            return 0;
        }

        int i = iidx, j = jidx;
        if (travel[i].cost[j] >= infinity) {
            cout << "No available route between these cities.\n";
            return 0;
        }

        long long cheapest = travel[i].cost[j];
        long long direct = ini[i].cost[j];
        vector<int> path = reconstruct_path(i, j);

        if (direct == infinity) {
            cout << "No direct flight. Cheapest route costs: " << cheapest << endl;
        } else if (direct == cheapest) {
            cout << "Direct flight available. Price: " << direct << endl;
        } else {
            cout << "Direct flight costs: " << direct << endl;
            cout << "Cheaper via route costs: " << cheapest << endl;
            cout << "Route: " << o.city[path[0]];
            for (size_t k = 1; k < path.size(); ++k) cout << " -> " << o.city[path[k]];
            cout << endl;
        }

        cout << "Do you want to continue booking? (Y/N): ";
        string ans; getline(cin, ans);
        if (tolower(ans[0]) != 'y') return 0;

        int no = in.noofpassenger();
        vector<string> fn(no), ln(no), sex(no);
        vector<int> age(no);
        for (int t = 0; t < no; t++) {
            cout << "Passenger " << (t + 1) << ":\n";
            cout << "First Name: "; getline(cin, fn[t]);
            cout << "Last Name: "; getline(cin, ln[t]);
            cout << "Sex: "; getline(cin, sex[t]);
            cout << "Age: "; string ag; getline(cin, ag); age[t] = stoi(ag);
        }

        int total_price = no * ((direct < cheapest) ? direct : cheapest);
        cout << "Total Price: " << total_price << endl;
        cout << "Confirm Booking? (Y/N): ";
        getline(cin, ans);
        if (tolower(ans[0]) == 'y') {
            filehandlingmodule f;
            f.ticket(username, fn, ln, sex, age, no);
            ticket(total_price, no, o.city[i], o.city[j], username);
        }
        return 0;
    }
};

int get_menu_choice() {
    while (true) {
        cout << "Enter Choice: ";
        string line;
        if (!getline(cin, line)) return -1;
        line = trim(line);
        try { return stoi(line); } catch (...) { cout << "Invalid input.\n"; }
    }
}

int main() {
    int N = 15;
    datamodule obj;
    obj.costdeclaration();

    bellmanfordalgorithm ob;
    ob.algorithmic_implementation();

    inputmodule obj1;
    string username = obj1.login();

    outputmodule object;
    object.initial();

    string userchoice[2];
    while (true) {
        int choice = get_menu_choice();
        if (choice == -1) break;
        switch (choice) {
            case 1:
                object.list_cities(N);
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                object.initial();
                break;
            case 2:
                obj1.user_input(userchoice);
                object.display_price(userchoice[0], userchoice[1], N, username);
                object.initial();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
    return 0;
}
