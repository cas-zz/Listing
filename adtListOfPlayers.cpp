#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;
#define MAX 15
typedef struct {
    string name;
    int fga, fgm;
} REC;
typedef struct {
    REC bp[MAX];
    int last;
} LIST;
class MyList {
private:
    LIST L;
    bool isFull();
    int locatePos(const string& name);
    double computeFGP(int a, int m);
public:
    MyList();
    void insertSort(const REC& player);
    void display();
    void save();
    void retrieve();
};
int menu();
MyList::MyList() {
    L.last = -1;
    retrieve();
}
bool MyList::isFull() {
    return (L.last == MAX - 1);
}

int MyList::locatePos(const string& name) {
    int i;
    for (i = 0; i <= L.last; i++) {
        if (stricmp(name.c_str(), L.bp[i].name.c_str()) < 0) {
            return i;
        }
    }
    return i;
}
void MyList::insertSort(const REC& player) {
    if (isFull()) {
        cout << "List is full." << endl;
        system("pause");
    } else {
        int p = locatePos(player.name);
        for (int i = L.last; i >= p; i--) {
            L.bp[i + 1] = L.bp[i];
        }
        L.bp[p] = player;
        L.last++;
    }
}
void MyList::display() {
    system("cls");
    cout << left << setw(24) << "Name" << setw(19) << "FGA" << setw(19) << "FGM" << setw(19) << "FGP(%)" << setw(14) << "REMARKS" << endl;
    for (int i = 0; i <= L.last; i++) {
        double fgp = computeFGP(L.bp[i].fga, L.bp[i].fgm);
        string remarks = (fgp > 50) ? "HIGH" : "LOW";
        cout << i + 1 << ".) " << setw(20) << left << L.bp[i].name << setw(20) << L.bp[i].fga << setw(20) << L.bp[i].fgm << setw(20) << fixed << setprecision(2) << fgp << setw(20) << remarks << endl;
    }
    system("pause");
}
double MyList::computeFGP(int a, int m) {
    return (a > 0) ? (static_cast<double>(m) / a * 100.0) : 0.0;
}
void MyList::save() {
    ofstream fileptr("data2.txt");
    if (fileptr.is_open()) {
        for (int i = 0; i <= L.last; i++) {
            fileptr << L.bp[i].name << endl << L.bp[i].fga << " " << L.bp[i].fgm << endl;
        }
        fileptr.close();
        cout << "The records have been saved successfully!" << endl;
    } else {
        cout << "Unable to open the file for saving." << endl;
    }
}
void MyList::retrieve() {
    ifstream fileptr("data2.txt");
    if (fileptr.is_open()) {
        REC player;
        string line;
        int strline = 0;
        while (getline(fileptr, line)) {
            istringstream data(line);
            if (strline % 2 == 0) {
                data >> player.name;
            } else {
                data >> player.fga >> player.fgm;
                insertSort(player);
            }
            strline++;
        }
        cout << "File is read successfully." << endl;
    } else {
        cout << "There is no existing record." << endl;
    }
    fileptr.close();
    system("pause");
}
int main() {
    MyList pl;
    REC pd;
    while (true) {
        switch (menu()) {
            case 1:
                system("cls");
                cout << "Insert Mode\n";
                cout << "Input Name: ";
                getline(cin >> ws, pd.name);
                cout << "Input FGA: ";
                cin >> pd.fga;
                cout << "Input FGM: ";
                cin >> pd.fgm;
                pl.insertSort(pd);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                pl.display();
                break;
            case 5:
                pl.save();
                exit(0);
            default:
                cout << "1 to 4 only." << endl;
                system("pause");
        }
    }
    return 0;
}

int menu() {
    int op;
    system("cls");
    cout << "MENU\n";
    cout << "1. Add a Record\n";
    cout << "2. Update a Record\n";
    cout << "3. Delete a Record\n";
    cout << "4. Display All Records\n";
    cout << "5. Exit\n";
    cout << endl << "Select (1-5): ";
    cin >> op;
    return op;
}
