#include<iostream>
#include<fstream>
using namespace std;

class SudokuFrame{

    int sudoku[9][9];

public:SudokuFrame(){
        menu();
    }

// This function generates a menu for the user at the starting of the program execution. This lets the user select the input method for entering the values for the Sudoku Puzzle into the SudokuFrame object.

private:void menu(){

        cout<<"\n======================\n";
        cout<<"   Sudoku Validator\n";
        cout<<"======================\n\n";

        cout<<"Input the puzzle into this program.\n\n";
        cout<<"Either:-\n";
        cout<<"\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
        cout<<"\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
        cout<<"\t   The file must not have a name > 30 characters.\n";
        cout<<"\t   The file must be in the same directory as this C++ file.\n";
        cout<<"\t   The file must have all 81 values seperated with spaces.\n";
        cout<<"\t   Blank cells must be filled in as 0 (eg; 1 2 9 8 1 9 ...).\n";
        cout<<"\t   --> ";

        int option;
        cin>>option;

        if(option==1) readFrameValues();
        else if(option==2) readFrameValuesFile();
        else{
            while(true){
                cout<<"\nInvalid option. Try again.\n";
                cout<<"\t   --> ";
                cin>>option;

                if(option==1) readFrameValues();
                else if(option==2) readFrameValuesFile();
                else continue;

                break;
            }
        }

    }

 // Reads the values for the Sudoku Frame cell-by-cell.

private:void readFrameValues(){
        cout<<"\nEnter the specified value when prompted.\n";
        cout<<"Enter 0 if cell is empty.\n\n";

        int rowIter, colIter;

        for(rowIter=0; rowIter<9; rowIter++){ //Iterating over cells to read vals.
            for(colIter=0; colIter<9; colIter++){
                int enteredValue;

                cout<<"Enter value for cell["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
                cin>>enteredValue;

                if(!(enteredValue>=1 && enteredValue<=9)){ //Checking for bounds in input.
                    while(true){ //We loop until valid input is read from user.
                        cout<<"Oops! You seem to have entered a wrong value! Try again.\n";
                        cout<<"Enter value for cell ["<<rowIter+1<<"]["<<colIter+1<<"] --> ";
                        cin>>enteredValue;

                        if(enteredValue>=1 && enteredValue<=9) break;
                    }
                }

                sudoku[rowIter][colIter]=enteredValue;
            }
            cout<<"-------\n"; //Display a break after every row for convenience.
        }
    }

// reads values from a specified file.

private:void readFrameValuesFile(){

        int rowIter, colIter;
        char filename[30];
        ifstream file;

        cout<<"\nEnter the name of the file which contains the puzzle --> ";
        cin>>filename;

        file.open(filename,ios::in);

        for(rowIter=0; rowIter<9; rowIter++){
            for(colIter=0; colIter<9; colIter++){

                int readValue;
                file>>readValue;

                sudoku[rowIter][colIter]=readValue;

                if(file.eof()) break;

            }
        }

        //If there aren't 81 values in the file, then it is invalid.
        if((colIter*rowIter)!=81){
            cout<<"Oops! The file doesn't have the required amount of values.\n";
            cout<<"Try again!\n";
            exit(EXIT_FAILURE);
        }

        file.close();

    }

// Returns the value of a cell of a specified col and row.

public:int getCellValue(int row, int col){
        return sudoku[row][col];
    }

};

class SudokuValidator{

    SudokuFrame frame;

//  Calls the function which validates the values in the Sudoku frame.

public:SudokuValidator(){
        validateFrame();
    }

// Calls functions which validates the rows, columns and 3x3 grids.

private:void validateFrame(){
        if(valuesAreValid()){
            if(rowsAreValid()){
                if(columnsAreValid()){
                    if(ThreeByThreeSquaresAreValid()){
                        cout<<"\nYour puzzle is valid!\n\n";
                    }
                    else cout<<"Your puzzle in invalid!\n";
                }
                else cout<<"Your puzzle is invalid!\n";
            }
            else cout<<"Your puzzle is invalid!\n";
        }
        else cout<<"Your puzzle is invalid!\n";
    }

// Checks if all values in the frame are between the ranges of 1-9.

private:bool valuesAreValid(){
        int rowIter, colIter;

        for(rowIter=0; rowIter<9; rowIter++){
            for(colIter=0; colIter<9; colIter++){
                int cellValue=frame.getCellValue(rowIter,colIter);
                if(!(cellValue>=0 && cellValue<=9)) return false;
            }
        }

        return true;
    }
// Checks if the rows are valid in the frame.

private:bool rowsAreValid(){

        int rowIter, colIter, valIter;

        for(rowIter=0; rowIter<9; rowIter++){ //Iterating over rows

            for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9

                if(rowContains(rowIter,valIter)==false)
                    return false;

            } //Value iteration loop ends here

        } //Row iteration loop ends here

        return true;
    }

// Checks if the columns in the frame are valid.

private:bool columnsAreValid(){

        int rowIter, colIter, valIter;

        for(colIter=0; colIter<9; colIter++){ //Iterating over cols

            for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9

                if(columnContains(colIter,valIter)==false)
                    return false;

            } //Value iteration loops ends

        } //Col iteration loop ends here

        return true;
    }

// Checks if the 3x3 grids in the frame are valid.

private:bool ThreeByThreeSquaresAreValid(){

        int squareIter, valIter;

        for(squareIter=0; squareIter<9; squareIter++){ //Iter over squares

            for(valIter=1; valIter<=9; valIter++){ //Iter over 1-9

                if(squareContains(squareIter,valIter)==false)
                    return false;

            } //Value iteration loop ends here

        } //Square iteration loop ends here

        return true;
    }

// Checks whether a given value is present in a specified row.

private:bool rowContains(int row, int value){
        int colIter;
        for(colIter=0; colIter<9; colIter++){
            if(frame.getCellValue(row,colIter)==value)
                return true;
        }
        return false;
    }

// Check whether a given value is present in the specified column.

private:bool columnContains(int col, int value){
        int rowIter=0;
        for(rowIter=0; rowIter<9; rowIter++){
            if(frame.getCellValue(rowIter,col)==value)
                return true;
        }
        return false;
    }

// Check whether a given value is present in the specified 3x3 grid.

private:bool squareContains(int squareNumber, int value){
        int rowStart=(squareNumber/3)*3;
        int rowEnd=rowStart+2;

        int colStart=(squareNumber%3)*3;
        int colEnd=colStart+2;

        int rowIter, colIter;
        for(rowIter=rowStart; rowIter<=rowEnd; rowIter++){
            for(colIter=colStart; colIter<=colEnd; colIter++){
                if(frame.getCellValue(rowIter,colIter)==value)
                    return true;
            }
        }

        return false;
    }

};


int main(){
    SudokuValidator s;
    return 0;
}