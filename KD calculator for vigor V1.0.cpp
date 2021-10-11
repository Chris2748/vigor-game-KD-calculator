//Code to calculate and record vigor game stats faster.
//Program Developed By Christian D. Rabine.

// Internal Librarys needed.
#include <iostream> 
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <math.h>

using namespace std; // Makes for less typing.

//class function declorations
double pOne(double, int);
int pTwo(int, double);
double pThree(int, int);
double checkAnswer(string);

//main program. Asks for user inputs, calls functions to calc stats, records data to text file for future refrence. allows for multiple uses
int main()
{
													//intro
													cout << "Hello, welcome to the vigor REAL kd calculator! \nMade by PSN: Chris_Burds!" << endl << endl;

//Decloration of Variables
double survRate;
string survivalRate;

int EP, kills;
string EncP, Tkills;

string playerName;
 
string PL = "Y";

//Decloration of time based variables
time_t now = time(0);
char* dt = ctime(&now);

while ( PL == "Y" || PL == "y")
{

	//collecting stats, verifying answers.
	
													cout << "\nPlease enter player name: ";
	getline(cin, playerName);
			
													cout << "\nPlease input your survival rate: ";
	cin >> survivalRate; //passes string
	survRate = checkAnswer(survivalRate);
	
	while(survRate < 0 || survRate > 100) 
		{ 
													cout << "\nInvalid input, survival rate is a percentage between 0 and 100...\n\nRe-input your survival rate: ";
			cin >> survivalRate;
			survRate = checkAnswer(survivalRate);
		}
	
													cout << "\nPlease input your total number of Encounters played: ";
	cin >> EncP;
	EP = checkAnswer(EncP);
	
	while(EP < 0) 
		{ 
													cout << "\nInvalid input, Encounters played cannot be below zero...\n\nRe-input your total number of Encounters played: ";
			cin >> EncP;
			EP = checkAnswer(EncP);
	
		}
	
													cout << "\nPlease input your total number of kills: ";
	cin >> Tkills;
	kills = checkAnswer(Tkills);
		
	while(kills < 0) 
		{ 
													cout << "\nInvalid input, Total kills cannot be below zero...\n\nRe-input your total number of kills: ";
			cin >> Tkills;
			kills = checkAnswer(Tkills);
		}
	
													cout << "_____________________________________________________________________________________";
	
	
	double Esurv = pOne(survRate, EP);
    //cout << "\nTesting 1 " << fixed << setprecision(3) << Esurv << endl; //passed variable accuracy test 1
	
	int Tdeath = pTwo(EP, Esurv);
	//cout << "\nTesting 2 " << fixed << setprecision(3) << Tdeath << endl; //passed variable accuracy test 2
	
	double kiDe = pThree(kills, Tdeath);

													cout << "\n\nYour REAL kill/death ratio (K/D) is: " << fixed << setprecision(3) << kiDe << endl << endl;
													
											if(isinf(kiDe)) //if a calculation error is present due to bad data the user will be informed why and a sultion to fix the mistake next run of the program.
												{
													cout << "\n*Warning*\ncalculation issue detected...";
													cout << "\n\nIn Order for this Tool to work properly, you must enter realistic stats.\nYou can find this in-game within your shelter menu or by viewing \nanother player's stats that killed you after an encounter.\n\n";
												}
	
	system("pause");
	
//____________________________________________________________________________________________________________________________________________________________
	
//	below is the process of writing stats to a text file to keep record of.
	
	char filename[ ] = "VigorStatSheet.txt"; 	//assigned name to file.
	ofstream vss; 								//vvs = vigor stat sheet
	
	cout << "\nWriting recorded stats to external text file...";
	
	vss.open (filename, fstream::app); 			//opens the file to write data
	vss << "\n______________________________________________________\n";
	vss << "\nDate " << dt << endl;
	vss << "Player Name: " << playerName << endl; 
	vss << "\n                  - Player Stats -";
	vss << "\nSurvival Rate: " << survRate << "  Encounters Played: " << EP << "  Kills: " << kills << endl;
	vss << "\nActual Kill/Death Ratio: " << fixed << setprecision(3) << kiDe;
	vss.close();								//closes file

													cout << "\n\nCalulate another entry? Enter 'Y''. If no, hit any key then 'Enter'\n\nInput: ";
													
													cin >> PL; 	//reassing string character. used to restart or end loop.
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); 		//clears the string memory in prep for another loop of the program
} 
		cout << "\n--------------------------------";
		cout << "\n\nIf you enjoyed this tool, or see value in it, consider donating! Much appreciated!";
		cout << "\n\nStellar Lumens: GD3JGUN5DBRLUNQTNRMJUYL76KSJTRSJWIE6G4AFOWQWEYOAUOFUACQE \n\nShiba Inu: 0x6B291B43a5Ab549af490Df87D576Ee4cb1EAe290 \n";
		return 0;
}

//function pOne take the survival rate and the encounters played to calculate the encouters survived, returns a double.
double pOne(double survRate, int EP)
{
	double es = (double)(survRate * EP) / 100 ;

	return es;
}

//function pTwo subtracks the encounters survived from the encounters played to find out the encounters died. return an int.
int pTwo(int EP, double Esurv)
{
	int ed = EP-Esurv;

	return ed;
}
	
//function pThree divides total kills with total deaths to find the players kd. returns a double.
double pThree(int kills, int Tdeath)
{
	double KD = (double)kills/Tdeath;
	
	return KD;
}

//multipurpose function used to prevent the user from imputing non numbers and special characters into the calculation fuctions.
//See logic used in seperate document. returns douuble if input is good. 
double checkAnswer(string A) // string temp
{	
	string line;
	string::size_type sz;
	double d;
	
	line = A; 				//assign A to temporary line
	
	bool running = true;	//enable the loop to run until break
	
  	while(running)
    	{
        	stringstream ss(line);
        	if (ss >> d)
        		{
            		if (ss.eof()) //if input passed into function survives, the loop ends.
            			{ 
                			break;
            			}
        		}
        												cout << "\nInvalid input, please remove any non-numbers from your response and try again: ";
        												cin >> line;
    	}
  
    double tempTwo = stod( line, &sz); 	//used to convet checked string into double. 
  
    return tempTwo; 					//replace with new double
}


