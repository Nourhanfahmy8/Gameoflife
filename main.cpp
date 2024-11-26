// File: A2_T1.2_S21_20230560_sheetPb3.cpp
// Author: Nourhan Mohammed Ahmed Fahmy
// Section: S21
// ID: 20230560
// Date: __ Nov 2024
// Detailed explanation of the file and how program works:
// Problem No. 6 :

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

class Universe{
private:
    vector <vector<string>> gridnumbered;
    vector <vector<string>> grid;
    vector <int> initialtoalive;
    vector <vector<string>> new_grid;

public:

    // initialize the grid to be all dead cells
    Universe(){
        grid.resize(20, vector<string>(20, "D"));
        gridnumbered.resize(20, vector<string>(20));

        int counter = 0;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                gridnumbered[i][j] = to_string(counter++);
            }
        }

    }


    // display for the user the cell numbers
    void displaygridnumbers()const{
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                cout << setw(5) << setfill(' ') << gridnumbered[i][j];
            }
            cout<< endl;
        }
    }

    // a starting layout
    void initialize(){
        cout << "\nPlease enter the cell numbers you want to initialize to alive (or -1 to exit)\n";
        int celln;

        int counter = 0;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                gridnumbered[i][j] = to_string(counter++);
            }
        }


        /*
        while(true) {

            if(celln == -1) break;
            else if (cin.fail() || celln < 0 || celln > 200) {
                // Clear n input
                cin.clear();
                // Ignore n input
                cin.ignore(1000, '\n');
                cout << "\nInvalid input!! Please enter a suitable cell number\n";
                continue;
            }
            else{
                // storing the input cell number
                initialtoalive.push_back(celln);
            }
        }
        */

        while(celln != -1){
            cin >> celln;
            if (cin.fail() || celln < 0 || celln > 200) {
                // Clear n input
                cin.clear();
                // Ignore n input
                cin.ignore(1000, '\n');
                cout << "\nInvalid input!! Please enter a suitable cell number\n";
                continue;
            }
            initialtoalive.push_back(celln);
        }

        sort(initialtoalive.begin(),initialtoalive.end());

        /*
        for (int cell : initialtoalive) {
            int row = cell / 20;
            int col = cell % 20;
            grid[row][col] = "L";
        }*/


        for(int k = 0;k<initialtoalive.size();k++) {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {
                    if (gridnumbered[i][j] == to_string(initialtoalive[k]))
                        grid[i][j] = "L";
                }
            }
        }

        /*
        cout << "\n displaying the grid after initializing the alive cells places\n";
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                cout << setw(5) << setfill(' ')<< grid[i][j] ;
            }
            cout<< endl;
        }*/

        // display the grid after initialization
        display();
    }


    void reset(){
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                grid[i][j] = "D";
            }
        }
        initialtoalive.clear();
    }


    void count_neighbors(){
    }


    void next_generation(){
        // Any live cell with fewer than two live neighbors dies, as if caused by underpopulation
        // Any live cell with two or three live neighbors lives on to the next generation
        // Any live cell with more than three live neighbors dies, as if by overpopulation
        // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction

        // row = 0, col = 0,row = 199,col= 199

        // first make a new vector to change the live cells in so that we don't interfere with the original vector while checking the cells in it
        new_grid = grid;

        int countlive;
        for(int i=0;i<20;i++){
            for(int j=0;j<20;j++){
                countlive = 0;
                if(i == 0){


                    // if the row and columns are both 0 --> this is the top left corner --> will only check for 3 cells
                    if(j==0){
                        // checking for the cell (0,0)
                        if(grid[i][j+1] == "L") countlive++; // cell (0,0)
                        if(grid[i+1][j]== "L")countlive++;  // cell (1,0)
                        if(grid[i+1][j+1] == "L")countlive++; // cell (1,1)


                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                        // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                        // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                        // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";

                    }



                    // if the row is = 0 and the column = 199 --> the top right corner
                    else if(j == 19){
                        // checking for the cell (0,19)
                        if(grid[i][j-1] == "L") countlive++; // cell (0,18)
                        if(grid[i+1][j-1]== "L")countlive++;  // cell (1,18)
                        if(grid[i+1][j] == "L")countlive++; // cell (1,19)

                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";

                    }


                    // row = 0 and the column is not = 0, so this is the row at the top of the grid
                    else{
                        // checking for the cell (0,_)
                        if(grid[i][j+1] == "L") countlive++; // cell (0,_+1)
                        if(grid[i][j-1]== "L")countlive++;  // cell (0,_-1)
                        if(grid[i+1][j] == "L")countlive++; // cell (1,_)
                        if(grid[i+1][j-1] == "L")countlive++; // cell (1,_-1) (diagonal from the right)
                        if(grid[i+1][j+1] == "L")countlive++; // cell (1,_+1) (diagonal from the left)


                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";

                    }

                }


                // the column = 0, the top right corner has been checked
                // so will check for the remaining rows
                else if(j == 0){

                    // the bottom left corner of the grid (19,0)
                    if(i == 19){
                        if(grid[i-1][j] == "L") countlive++; // cell (18,0)
                        if(grid[i-1][j+1]== "L")countlive++;  // cell (18,1) the right top diagonal
                        if(grid[i][j+1] == "L")countlive++; // cell (19,1)

                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";
                    }

                    else{

                        // checking for the cell (_,0)
                        if (grid[i - 1][j] == "L") countlive++; // cell (_-1,_)
                        if (grid[i + 1][j] == "L")countlive++;  // cell (_+1,_)
                        if (grid[i][j + 1] == "L")countlive++; // cell (_,_+1)
                        if (grid[i - 1][j + 1] == "L")countlive++; // cell (_-1,_+1) (diagonal from the top right)
                        if (grid[i + 1][j + 1] == "L")countlive++; // cell (_+1,_+1) (diagonal from the bottom right)


                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";

                    }

                }

                else if(i == 19){
                    if(j==19){
                        // checking for the cell (19,19)
                        if(grid[i][j-1] == "L") countlive++; // cell (19,18)
                        if(grid[i+1][j]== "L")countlive++;  // cell (18,19)
                        if(grid[i-1][j-1] == "L")countlive++; // cell (18,18) the top left diagonal


                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";

                    }

                    // the bottom row
                    else{

                        // checking for the cell (19,_)
                        if (grid[i - 1][j] == "L") countlive++; // cell (18,_)
                        if (grid[i][j-1] == "L")countlive++;  // cell (19,_-1)
                        if (grid[i][j + 1] == "L")countlive++; // cell (19,_+1)
                        if (grid[i - 1][j - 1] == "L")countlive++; // cell (_-1,_-1) (diagonal from the top left)
                        if (grid[i - 1][j + 1] == "L")countlive++; // cell (_-1,_+1) (diagonal from the top right)

                        // if the number of alive cells around it have <2 alive, then the cell dies from underpopulation
                        if(countlive <2) new_grid[i][j] = "D";

                            // if the number of alive cells equal 2 or 3 then the cell lives onto next generation
                        else if(countlive == 2 || countlive == 3) new_grid[i][j] = "L";

                            // if the cell itself is dead, and have > 3 alive cells around it, then it reproduces and becomes a live cell
                        else if((grid[i][j] == "D") && (countlive > 3)) new_grid[i][j] = "L";

                            // if the number of alive cells around it is greater than 3, it dies from overpopulation
                        else if(countlive > 3) new_grid[i][j] = "D";


                    }

                }
                else if(j == 19){

                    // checking for the cell (_,19)
                    if (grid[i][j-1] == "L") countlive++; // cell (_,_-1)
                    if (grid[i+1][j] == "L")countlive++;  // cell (_+1,_)
                    if (grid[i-1][j] == "L")countlive++; // cell (_-1,_)
                    if (grid[i - 1][j - 1] == "L")countlive++; // cell (_-1,_-1) (diagonal from the top left)
                    if (grid[i + 1][j - 1] == "L")countlive++; // cell (_-1,_+1) (diagonal from the bottom left)


                }
            }
        }

    }

    void display()const{
        cout << "\nDisplaying the grid after initializing the alive cells places\n\n";
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                cout << setw(5) << setfill(' ') << grid[i][j] ;
            }
            cout<< endl;
        }
    }
    void run();

};

int main() {
    Universe u;
    cout << "\n-- Welcome to the Game of life application --\n";
    int choice;
    cout << "^^ What would you like to do? ^^\n1) Start the game\n2)Exit\n";
    while (true){
        cin >> choice;
        if (cin.fail() || choice <=0 || choice >2) {
            // Clear n input
            cin.clear();
            // Ignore n input
            cin.ignore(1000, '\n');
            cout << "\nInvalid input!! Please enter a suitable option\n";
            continue;
        }
        if(choice == 1){
            cout << "The initial grid is\n";
            u.displaygridnumbers();
            u.initialize();
            //u.display();
            continue;
        }
        else if(choice == 2){
            cout << "\nThank you for using the program\n";
            break;
        }

    }
    return 0;
}
