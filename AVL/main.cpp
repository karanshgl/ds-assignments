#include "mavl.hpp"
#include <iostream>

using namespace std;

int main(){
	MAVLTree m;
	int choice, cont;
	int key;
	string value;
	do{
		cout<<"Please enter 1 to insert, 2 to delete by key, 3 to get the place of a key, 4 to delete by place of key and 5 to find the value ";
		cin>>choice;
		if(choice == 1){
			cout<<"Enter Key ";
			cin>>key;
			cout<<"Enter Value ";
			cin>>value;
			m.insert(key, value);
		}
		else if(choice == 2){
			cout<<"Enter Key ";
			cin>>key;
			m.remove(key);
		}
		else if(choice == 3){
			cout<<"Enter Key ";
			cin>>key;
			cout<<m.get_place(key)<<endl;
		}
		else if(choice == 4){
			cout<<"Enter Order ";
			cin>>key;
			m.delete_by_place(key);
		}
		else if(choice == 5){
			cout << "Enter Key ";
			cin>>key;
			cout<<m.search(key)<<endl;
		}
		cout<<"Do you wish to continue (1/0)";
		cin>>cont;
	}while(cont);
}