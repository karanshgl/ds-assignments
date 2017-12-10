#include <iostream>
#include "heap.hpp"

using namespace std;

class Less{
public:
	bool operator()(int a, int b){ return a<b; }
};

int main(){
	Heap<int, Less> H;
	char y;
	do{
		cout << "Enter the command " << endl;
		cout << "1. Add to Heap" << endl;
		cout << "2. Get Min" << endl;
		cout << "3. Remove Min" << endl;
		int c;
		int toAdd;
		cin >> c;

		switch(c){
			case 1: cout << "Enter the Number"<<endl;
					cin >> toAdd;
					H.insert(toAdd);
					break;

			case 2: cout << "Min = " << H.min() << endl;
					break;

			case 3: H.removeMin();
					break;
		}

		cout << "Do you wish to continue ? " << endl;
		cin>>y;

	}while(y=='y' || y=='Y');
	
}