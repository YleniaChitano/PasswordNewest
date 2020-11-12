#include <iostream>
#include <vector>
#include <conio.h> // Needed for _getch
#include <fstream> // Needed for the password file I/O
#include <string>

void menu();
void create();
std::vector <int> move(std::vector <int>& cursorPos, bool& loop, std::fstream& password);
void printTable(std::vector <int>& cursorPos);
void end(bool& loop, std::fstream& password);


int main()
{
    char account;
    std::string sequence;
    std::cout << "Welcome to Battleship!\n\n";
account:
    std::cout << "Press 1 if you want to create a new account or 2 to log in to your previous account.\n";
    std::cin >> account;
    

    if (account == '1')
    {
        create();
        std::fstream password;
        
        password.open("Password.txt", std::fstream::in | std::fstream::out | std::fstream::app);
        std::getline(password, sequence);

        password.close();

        //std::cout << sequence << std::endl;
        menu();
    }

    /*else if (account == '2')
    {
        insert();
    }*/

    else {
        std::cout << "Invalid input\n";
        goto account;
    }
}

void create()
{
    std::fstream password("Password.txt", std::ios::in | std::ios::out | std::ios::trunc); // Trunc deletes the previous file content

    std::cout << "Please insert a password sequence by using WASD keys. Press ENTER when the sequence is complete.\n" << std::endl;


    std::vector <int> cursorPos{ 0,0 };

    bool loop = true;

    while (loop == true) {

        printTable(cursorPos);
        move(cursorPos, loop, password);

    }



}

void printTable(std::vector <int>& cursorPos)
{


    char cursor = '_'; // A symbol to show the cursor's position

    std::vector <std::vector <char>> table{ {'A','B','C','D'},{'E','F','G','H'}, {'I','J','K','L'}, {'M','N','O','P'} }; // A vector to store the content of the table

    for (unsigned int i = 0; i < table.size(); i++) {

        for (unsigned int j = 0; j < table[i].size(); j++) {


            if (i == cursorPos.at(0) && j == cursorPos.at(1)) {

                table[i][j] = cursor;
            }


            std::cout << table[i][j] << " ";


        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void menu()
{
	char choice;
choice:
	std::cout << "Please Select an option ( 1-3) : \n\n";
	std::cout << "1: Change the password\n";
	std::cout << "2: Play battleship\n";
	std::cout << "3: Quit\n";
	std::cin >> choice;

	if (choice == '1')
	{
		create();
		menu();
	}

	else if (choice == '3')
	{
		exit(0);
	}

	else
	{
		std::cout << "Invalid input.\n";
		goto choice;
	}
}

std::vector <int> move(std::vector <int>& cursorPos, bool &loop, std::fstream &password) {
    std::vector <std::vector <char>> table{ {'A','B','C','D'},{'E','F','G','H'}, {'I','J','K','L'}, {'M','N','O','P'} };
    char move;
    move = _getch();
    if (move == 'a' && cursorPos.at(1) != 0) {

        cursorPos.at(1) = (cursorPos.at(1) - 1);
        password << table[cursorPos.at(0)][cursorPos.at(1)];


    }

    if (move == 'd' && cursorPos.at(1) != 3) {
        cursorPos.at(1) = (cursorPos.at(1) + 1);
        password << table[cursorPos.at(0)][cursorPos.at(1)];
    }

    if (move == 'w' && cursorPos.at(0) != 0) {
        cursorPos.at(0) = (cursorPos.at(0) - 1);
        password << table[cursorPos.at(0)][cursorPos.at(1)];
    }

    if (move == 's' && cursorPos.at(0) != 3) {
        cursorPos.at(0) = (cursorPos.at(0) + 1);
        password << table[cursorPos.at(0)][cursorPos.at(1)];
    }

    if (move == '\r') {
        end(loop, password);
    }


    return cursorPos;
}

void end(bool &loop, std::fstream& password) {
    password.close();
    std::cout << "Password registered.\n";
    loop = false;
}
