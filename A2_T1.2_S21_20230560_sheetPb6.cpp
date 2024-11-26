// File: A2_T1.2_S21_20230560_sheetPb6.cpp
// Author: Nourhan Mohammed Ahmed Fahmy
// Section: S21
// ID: 20230560
// Date: 26 Nov 2024
// Detailed explanation of the file and how program works:
// Problem No. 6 : Game of life
//                 The universe of this game consists of a grid of square cells that could have one of the two states
//                 either dead or alive. And every cell interacts with its adjacent neighbours and according to some condition
//                 the cell either stays alive, becomes dead or remains dead


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include <conio.h>

using namespace std;

// The class universe of the Game of life
class Universe{

private:

    // vector for the grid numbered so that the user can easily choose which square he wants to initialize to alive
    vector <vector<string>> gridnumbered;

    // vector for the grid we use to check the conditions on it
    vector <vector<string>> grid;

    // vector to store the values of the cells that the user chose to initialize to alive
    vector <int> initialtoalive;

    // vector to store the changes done in the grid during each run
    vector <vector<string>> new_grid;

    // vector that contains the original starting grid that is used for checking the neighbours and conditions
    vector <vector<string>> original_grid;


public:

    // initialize the grids to be all dead cells
    Universe(){
        grid.resize(20, vector<string>(20, "D"));
        gridnumbered.resize(20, vector<string>(20));
        new_grid.resize(20, vector<string>(20, "D"));
        original_grid.resize(20, vector<string>(20, "D"));

        // initializing the numbered grid with index numbers from 0 to 399, since the grid size is (20 * 20)
        int counter = 0;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                gridnumbered[i][j] = to_string(counter++);
            }
        }

    }


    // display for the user the cell numbers, so he can choose which cells he wants to initialize to alive
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

        // asking the user to input the cell numbers he wants to be alive (or -1 to stop)
        cout << "\n--- Please enter the cell index numbers you want to initialize to alive (or -1 if you are done) ---\n";
        int celln;

        while(true) {

            cin >> celln;
            if(celln == -1) break;

            // validation check to make sure index input is a valid input and within the range
            if (cin.fail() || celln < 0 || celln > 399) {
                // Clear n input
                cin.clear();
                // Ignore n input
                cin.ignore(1000, '\n');
                cout << "\nInvalid input!! Please enter a suitable cell number you want to initialize to alive (or -1 if you are done)\n";
                continue;
            }

            // storing the input cell numbers into a vector
            initialtoalive.push_back(celln);
        }

        // sorting the vector so we can easily loop around it
        sort(initialtoalive.begin(),initialtoalive.end());

        // setting the grid indexes to alive with the indexes the user chose
        for(int k = 0;k<initialtoalive.size();k++) {
            for (int i = 0; i < 20; i++) {
                for (int j = 0; j < 20; j++) {

                    // looping over the numbered grid to be able to know the value of i and j
                    if (gridnumbered[i][j] == to_string(initialtoalive[k])) {
                        grid[i][j] = "L";
                        new_grid[i][j] = "L";
                        original_grid[i][j] = "L";
                    }
                }
            }
        }

    }


    // function to count the alive neighbours around each cell
    int count_neighbors(int i,int j) {


        // initializing the count to 0 for each cell
        int countlive = 0;

        // Counting the number of live cells around each cell:
        // we count 8 cells --> the cell above it, below it, next to it from the left and right,
        // diagonal from top left and right, diagonal from the bottom left and right

        // if the row and columns are both 0 --> this is the top left corner --> will only check for 3 cells
        // else if the row is = 0 and the column = 19 --> the top right corner
        // else if the row = 0 and the column is not = 0, so this is the row at the top of the grid
        // else if the column = 0, the top right corner has been checked, so
        //      we check the bottom left corner of the grid (19,0)
        //      or we check the column to the left, we check for the 5 cells around the cell
        // else we check for the cell (_,19) which is the last column
        // else we will check for the remaining rows
        //      the cell is in the middle of the grid, so can check all the 8 cells around it

        // looping over the surrounding cells
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {

                // Skip the cell itself
                if (x == 0 && y == 0) continue;

                // calculating the neighbor coordinates
                int ni = i + x, nj = j + y;

                // Checking the boundaries and whether we can check 8 or 5 or 3 cells
                if (ni >= 0 && ni < 20 && nj >= 0 && nj < 20) {

                    // counting the surrounding cells that are alive
                    if (original_grid[ni][nj] == "L") countlive++;
                }
            }
        }

        // returning the count
        return countlive;
    }


    // updating the grid to the next generation
    void next_generation(){

        // Any live cell with fewer than two live neighbors dies, as if caused by underpopulation
        // Any live cell with two or three live neighbors lives on to the next generation
        // Any live cell with more than three live neighbors dies, as if by overpopulation
        // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction


        int countlive;
        for(int i=0;i<20;i++) {
            for (int j = 0; j < 20; j++) {

                // variable to store the count live from the count_neighbours function, where we pass the index of each cell to it
                countlive = count_neighbors(i, j);

                // checking based on the conditions
                if (original_grid[i][j] == "L") {

                    // Cell is currently alive
                    if (countlive < 2 || countlive > 3) {

                        // the cell dies from underpopulation or overpopulation
                        new_grid[i][j] = "D";

                        // else the cell lives on to the next generation
                    } else {
                        new_grid[i][j] = "L";
                    }

                    // Cell is currently dead
                } else {

                    // the cell becomes alive due to reproduction
                    if (countlive == 3) {
                        new_grid[i][j] = "L";

                        // else the conditions aren't met and the cell remains dead
                    } else {
                        new_grid[i][j] = "D";
                    }
                }

            }
        }

        // copying the change of the generation to the grid
        grid = new_grid;

    }

    // getter to return the grid after it was changed
    const vector<vector<string>>& getgrid() const {
        return grid;
    }

    // getter to return the original grid after initializing the alive cells
    const vector<vector<string>>& getoriginalgrid() const {
        return original_grid;
    }

    // function to display the grid, and it depends on the grid passed to the function
    // as we can either pass the original initialized grid, or print the grid after each generation
    void display(const vector<vector<string>>& input_grid){

        for (const auto& row : input_grid) {
            for (const auto& cell : row) {
                cout << setw(5) << setfill(' ') << cell;
            }
            cout << endl;
        }

    }

    // function to run the game according to the number of times the user specified
    void run(){
        // calling the next generation
        next_generation();
        original_grid = new_grid;
    }

    // resetting the grids to dead in case the user wants to play the game several times
    void reset(){
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                grid[i][j] = "D";
                new_grid[i][j] = "D";
                original_grid[i][j] = "D";
            }
        }
        initialtoalive.clear();
    }


};

// Main function
int main() {

    // object of type class Universe
    Universe u;

    // welcome message
    cout << "\n--- Welcome to the Game of life application ---\n";
    int choice,times;

    // menu for the user
    while (true){
        cout << "\n^^ What would you like to do? ^^\n1) Start the game\n2) Exit\n";
        cin >> choice;

        // validation check for the input
        if (cin.fail() || choice <=0 || choice >2) {
            // Clear n input
            cin.clear();
            // Ignore n input
            cin.ignore(1000, '\n');
            cout << "\nInvalid input!! Please enter a suitable option\n";
            continue;
        }

        // the user wants to play the game
        if(choice == 1){

            // resetting the grids
            u.reset();

            // displaying the initial numbered grid
            cout << "\nThe initial grid is\n";
            u.displaygridnumbers();

            // initializing the indexes chosen by the user to alive
            u.initialize();

            // display the original grid after initialization
            cout << "\n** Displaying the grid after initializing the alive cells places **\n\n";
            u.display(u.getoriginalgrid());

            // asking the user how many times he wants to run the program
            cout << "How many times would you like to run?\n";
            cin >> times;

            for(int i=0;i<times;i++) {
                u.run();
                // after each run, will display the next generation
                cout << "\nAfter generation " << i+1 << "\n\n";
                u.display(u.getgrid());
            }
            continue;
        }

        // the user wants to exit
        else if(choice == 2){
            cout << "\nThank you for using the program\n";
            break;
        }

    }
    return 0;
}
