#include<Space.h>
#include<iostream>
Space::Space(){
    spaceState = HIDDEN;
    nearbyMines = 0;
    mine = false;
}
Space::Space(const Space& other){
    this->spaceState = other.spaceState;
    this->nearbyMines = other.nearbyMines;
    this->mine = other.mine;
}
Space::Space(int spaceState, int nearbyMines, bool mine){
    this->spaceState = spaceState;
    this-> nearbyMines = nearbyMines;
    this-> mine = mine;
}

//Setters
void Space::setNearbyMines(int nearbyMines){this->nearbyMines = nearbyMines;}
void Space::setState(int spaceState){this->spaceState = spaceState;}
void Space::setMine(bool mine){this->mine = mine;}

//Getters
int Space::getState() const{return this->spaceState;}
int Space::getNearbyMines() const{return this->nearbyMines;}
bool Space::getMine() const{return this->mine;}

//Functions
int Space::minesNearby(std::vector<std::vector<Space>> board, int i, int j){
    		//Count nearby mines 
    		int mines = 0;
            //Board Middle and Right Edge
            if(i >= 1 && j >= 1 && i < board.size()-1 && j < board[0].size()-1){
				for(int k = -1; k <= 1; k++){
	        		for(int l = -1; l <= 1; l++){
                        if(board[i + k][j + l].getMine()){
                            mines++;
                        }
					}
				}
			}
			
            //Edge Cases First
			//Top Edge
			
            else if(i == 0 && j > 0 && j < board[0].size()-1){
				
					for(int k = 0; k <= 1; k++){
	        			for(int l = -1; l <= 1; l++){
							if(board[i + k][j + l].getMine()){
			        			mines++;
							}
						}
					}
				
				
			}
            
			//Bottom Edge
			else if(i == board.size()-1 && j > 0 && j < board[0].size()-1){
				
					for(int k =-1; k <= 0; k++){
	        			for(int l = -1; l <= 1; l++){
							if(board[i + k][j + l].getMine()){
			        			mines++;
							}
						}
					}	
			}
            
			//Left Edge
			else if(j == 0 && i > 0 && i < board.size()-1){
				
					for(int k = -1; k <= 1; k++){
	        			for(int l = 0; l <= 1; l++){
							if(board[i + k][j + l].getMine()){
			        			mines++;
							}
						}
					}
				
				
			}
            
			//Right Edge
			else if(j == board[i].size()-1 && i > 0 && i < board.size()-1){
					for(int k = -1; k <= 1; k++){
	        			for(int l = -1; l <= 0; l++){
							if(board[i + k][j + l].getMine()){
								
			        			mines++;
							}
						}
					}
				
				
			}
            
			//Corner Cases
			//Upper Left
			else if(i == 0 && j== 0){
				for(int k = 0; k <= 1; k++){
	        			for(int l = 0; l <= 1; l++){
							if(board[i + k][j + l].getMine() ){
			        			mines++;
							}
						}
					}
			}
			//Lower Right
			else if(i == board.size()-1 && j== board.size()-1){
				
				//std::cout << "Counting a lower right"<< std::endl;
				for(int k = -1; k <= 0; k++){
	        			for(int l = -1; l <= 0; l++){
							if(board[i + k][j + l].getMine()){
			        			mines++;
							}
						}
					}
			}
			//Lower Left
			else if(i == board.size()-1 && j== 0){
				for(int k = -1; k <= 0; k++){
	        			for(int l = 0; l <= 1; l++){
							if(board[i + k][j + l].getMine() ){
			        			mines++;
							}
						}
					}
			}
			//Upper Right
			else if(i == 0 && j== board.size()-1){
				//std::cout << "Counting a upper right"<< std::endl;
				for(int k = 0; k <= 1; k++){
	        			for(int l = -1; l <= 0; l++){
							if(board[i + k][j + l].getMine()){
			        			mines++;
							}
						}
					}
			}
            
    return mines;
}