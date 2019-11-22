#include<Minesweeper.h>
#include<random>
#include<cmath>

    Minesweeper::Minesweeper(){
        
        //Defaults
        height = 9;
        width = 9;
        mines = 10;
        foundMines = 0;
        totalMines = mines;
        flags = 0;
        firstClick = true;
        gameState = 0;
        
        //Setup Board
        initializeBoard();
    
        //Add X mines in random positions on board
        generateMines();

        //Count number of mines near each space and update each space with the number
        countNearbyMines();         
        
    }
    

    Minesweeper::Minesweeper(int h, int w, int m){
        
        //Variable Init
        height = h;
        width = w;
        mines = m;
        totalMines = m;
        foundMines = 0;
        flags = 0;
        firstClick = true;
        gameState = 0;

        //Board Setup
        initializeBoard();
        
        //Add X mines in random positions on board
        generateMines();

        //Debug Board Test Mines
        /*
        board[1][1].setMine(true);
        board[0][0].setMine(true);
        board[1][7].setMine(true);
        board[7][1].setMine(true);
        board[7][7].setMine(true);
        */
        //Count number of mines near each space and update each space with the number
        countNearbyMines();
        
    }
    

    Minesweeper::Minesweeper(const Minesweeper& other){
        this->height = other.height;
        this->width = other.width;
        this->board = other.board;
        this->firstClick = other.firstClick;
        this->foundMines = other.foundMines;
        this->gameState = other.gameState;
        this->flags = other.flags;
        this->mines = other.mines;
    }

    //Setters
    void Minesweeper::setHeight(int height){
        this->height = height;
    }
    
    void Minesweeper::setWidth(int width){
        this->width = width;
    }

    void Minesweeper::setMines(int mines){
        this->mines = mines;
    }

    void Minesweeper::setBoard(std::vector<std::vector<Space>> board){
        this->board = board;
    }

    //Getters
    int Minesweeper::getHeight() const{
        return this->height;
    }
    
    int Minesweeper::getWidth() const{
        return this->width;
    }

    int Minesweeper::getMines() const{
        return this->mines;
    }

    std::vector<std::vector<Space>> Minesweeper::getBoard() const{
        return this->board;
    }

    void Minesweeper::reset(){
        Minesweeper newGame(height,width,totalMines);
        height = newGame.height;
        width = newGame.width;
        board = newGame.board;
        firstClick = newGame.firstClick;
        gameState = newGame.gameState;
        mines = newGame.mines;
        flags = newGame.flags;
        foundMines = newGame.foundMines;

    }
    void Minesweeper::initializeBoard(){
        Space setup;
        for(int i = 0; i < height; i++){
            std::vector<Space> temp;
            for(int j = 0; j < width; j++){
                temp.push_back(setup);
            }
            board.push_back(temp);
        }
    }

    //Add X mines in random positions on board
    void Minesweeper::generateMines(){
        std::random_device rd;
        std::mt19937 g(rd());
        std::vector<int> spaces;
        for(int i = 0; i <= board.size()-1; i++){
            for(int j = 0; j <= board.size()-1; j++){
                int num;
                if(i < 10)
                    num = i * 10 + j;
                else{
                    num = i * 100  + j ;
                    //std::cout << "i:j:"<< i << ":"<< j << std::endl;      

                }
               spaces.push_back(num);
            }
        }
        std::shuffle(spaces.begin(), spaces.end(), g);
        for(int i = 0; i < mines; i++){
                int j, l;
                //std::cout << "soaces"<< spaces[i] << std::endl;
                if(spaces[i] > 1000){
                    l = ((spaces[i] % 100));
                    j = spaces[i]/100;
                }
                else if(spaces[i] < 1000){
                    l = ((spaces[i]% 10));
                    j = spaces[i]/10;
                }
               
                //std::cout << "j:l:"<< j << ":"<< l << std::endl; 
                board[j][l].setMine(true);    
        }

    }
    
    void Minesweeper::countNearbyMines(){
        for(int i = 0; i < height; i++){
                for(int j = 0; j < width; j++){
                    if(!board[i][j].getMine()){
                        int mine = board[i][j].minesNearby(board,i,j);
                        board[i][j].setNearbyMines(mine);
                    }
                }
            }
    }

    //Local Utiliy Function to update space states
    void updateSpace(Space* current){
        if(current->getNearbyMines() == 0 && !current->getMine())
            current->setState(EMPTY);
        else if(current->getNearbyMines() == 1 && !current->getMine())
            current->setState(1);
        else if(current->getNearbyMines() == 2 && !current->getMine())
            current->setState(2);
        else if(current->getNearbyMines() == 3 && !current->getMine())
            current->setState(3);
        else if(current->getNearbyMines() == 4 && !current->getMine())
            current->setState(4);
        else if(current->getNearbyMines() == 5 && !current->getMine())
            current->setState(5);
        else if(current->getNearbyMines() == 6 && !current->getMine())
            current->setState(6);
        else if(current->getNearbyMines() == 7 && !current->getMine())
            current->setState(7);
        else if(current->getNearbyMines() == 8 && !current->getMine())
            current->setState(8);
    }

//Opens all nearby empty spaces when a empty space is clicked.
    void Minesweeper::openSpace(int  x, int y){

        if((x >= 0 && x < board.size()) && (y >= 0 && y < board.size())){
            if((board[x][y].getState() == HIDDEN  || board[x][y].getState() == FLAG || board[x][y].getState() == QMARK) && !board[x][y].getMine() ){
                if(board[x][y].getState() == FLAG){
                    std::cout << mines << flags << std::endl;
                    mines++;
                    flags--;
                }
                if(board[x][y].getNearbyMines() == 0){       
                    updateSpace(&board[x][y]);
                    openSpace( x, y-1);
                    openSpace( x, y+1);
                    openSpace( x-1, y-1);
                    openSpace( x+1, y-1);
                    openSpace( x+1, y+1);
                    openSpace( x-1, y+1);
                    openSpace( x-1, y);
                    openSpace( x+1, y);                  
                }
                else if (board[x][y].getNearbyMines() > 0){
                    updateSpace(&board[x][y]);
                    return;
                } 
                
            }
                
        }     
    }
    
	void Minesweeper::handle(int x, int y, MouseButton button){
        //Left: used to check spaces /Right: used to flag bombs/qmark?
        if(button == left && board[x][y].getState() == HIDDEN && !board[x][y].getMine()){
            firstClick = false;
            openSpace(x,y);
        }
        else if(button == left && board[x][y].getState() == HIDDEN && board[x][y].getMine() && !firstClick){
            firstClick = false;
            //Hit bomb-end game:Terminal State
            for(int i = 0; i < board.size(); i++){
                for(int j = 0; j < board[i].size(); j++){
                    if(board[i][j].getMine())
                        board[i][j].setState(MINE);
                    else 
                        updateSpace(&board[i][j]); 
                }    
            }
            board[x][y].setState(EXPLODED);

            //Set end game state
            gameState = 1;
            
        }
        else if(button == left && board[x][y].getState() == HIDDEN && board[x][y].getMine() && firstClick){
            
            //First was a mine reset current mine and update nearby count
            if(x-1 >= 1 && board[x-1][y].getState() == HIDDEN){
                board[x][y].setMine(false);
                board[x-1][y].setMine(true);
                
            }
            else if(x+1 < board.size()-1 && board[x+1][y].getState() == HIDDEN){
                board[x][y].setMine(false);
                board[x+1][y].setMine(true);
                
            }
            else if(y-1 >= 1 && board[x][y-1].getState() == HIDDEN){
                board[x][y].setMine(false);
                board[x][y-1].setMine(true);
                
            }
            else if(y+1 < board.size()-1 && board[x][y+1].getState() == HIDDEN){
                board[x][y].setMine(false);
                board[x][y+1].setMine(true);
                
            }
            else{
                generateMines();
            }
            
            countNearbyMines();
            openSpace(x,y);
            firstClick = false;
            
        }
        else if(button == right && board[x][y].getState() == HIDDEN && flags < totalMines){
            
            board[x][y].setState(FLAG);
            mines--;
            flags++;
            if(board[x][y].getMine())
                foundMines++;
        }
        else if(button == right && board[x][y].getState() == FLAG){
            board[x][y].setState(QMARK);
            mines++;
            flags--;
            if(board[x][y].getMine())
                foundMines--;
        }
        else if(button == right && board[x][y].getState() == QMARK){
            //change space x/y to FLAG if HIDDEN//Change to HIDDEN if already FLAG
            board[x][y].setState(HIDDEN);
        }
        //Set end game state
           //gameState = 2; if all empty spaces not hidden or only hidden spaces left contain mines.....
        if(foundMines == totalMines){
            bool allOpen = true;
            for(int i = 0; i < board.size()-1; i++){
                for(int j = 0; j < board.size()-1; j++){
                    if(board[i][j].getState() == HIDDEN && !board[i][j].getMine()){
                        allOpen = false;
                    }
                }   
            }
            if(allOpen)
                gameState = 2;
        }
    }
    
    
	ucm::json Minesweeper::getBoard(){
        ucm::json result;
        for(int i = 0; i < height; i++){
            std::vector<int> temp;
            for(int j = 0; j < width; j++){
                temp.push_back(board[i][j].getState());
            }
           result["board"].push_back(temp);
        }
        result["gameState"] = gameState;
        result["mines"] = mines;
          
        return result;
    }


	Minesweeper::~Minesweeper() {
        
    }