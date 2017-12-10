#include <string>
#include "node.hpp"
#include "name_map.hpp"
#include "number_map.hpp"

int main(){
	Name_Map<string, string> M;
	Number_Map<long long int, int> m;
	M.input("names.txt");
	M.output("2016csb1080.txt");
	m.input("numbers.txt");
	m.output("2016csb1080.txt");
	int cont=0, choice;
	long long int number;
	string name;
	do{
		 cout<<"Please enter 1 to know balance of a  phone number and 2  to know meaning of a  name ";   
		 cin>>choice;

		 if(choice == 1){
		 	cout<<"Please enter number ";
		 	cin>>number;
		 	cout<<"Number = "<<number<<" Balance = INR "<<m.find(number)<<endl;
		 }                                      
		 else if(choice == 2){
		 	cout<<"Please enter name ";
		 	cin>>name;
		 	cout<<"Name = "<<name<<" Meaning = "<<M.find(name)<<endl;
		 }
		 cout<<"Do you wish to continue? (1/0)"<<endl;
		 cin>>choice;
	}while(choice);
}