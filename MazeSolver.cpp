/*
	First name	Jialong
	Last name		YU
	Student ID	01343322
	Username		jy3717
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include<ctime>

// do not use using namespace std

// do not alter the struct declaration
struct node {
	char id;
	node* north;
	node* south;
	node* east;
	node* west;
};

// do not alter the typedef
typedef node* nodeptr;

/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////

// do not alter these functions declarations

void build_basic_maze(nodeptr& start, nodeptr& finish);
// builds the basic maze displayed in page 1

nodeptr traverse_maze(const nodeptr& start, const std::string& path);
// traverses the maze using a predefined path

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path);
// allows the user to solve the maze interactively

nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path);
// simulates a random walk in the maze

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a queue to store the unvisited neighbours of the current node

void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path);
// an improvement of the random walk: solves the maze using a stack to store the unvisited neighbours of the current node


// you can define and add use additional functions if you might need to

///////////////////
// main function //
///////////////////

// //IMPORTANT (Reminder): before submitting your source code, please make sure to comment your main function (needed for automated testing)
int main() {

    nodeptr start = NULL;
    nodeptr finish = NULL;
    build_basic_maze(start, finish);


    std::cout<<"start = "<< start->id << std::endl;
    std::cout<<"finish = "<< finish->id << std::endl;
    std::string path= "";

		/* -------------------------------traver_maze--------------------------------*/
		   // std::string pathinput;
		   // std::cin>> pathinput;
		   // std::cout<<std::endl;
		   // nodeptr stop = traverse_maze(start, pathinput);
			 //
		   // std::cout<<"we stopped at: " << stop->id <<std::endl;


		/* --------------------------solve interactively-----------------------------*/

		     //solve_interactively(start, finish, path);

		/* ---------------------random_walk--------------------------*/
			 //
		  nodeptr stop = random_walk(start, finish, path);


		/* ---------------------solve_queue and solve_stack--------------------------*/


		   //solve_queue(start, finish, path);
	    //solve_stack(start, finish, path);
			//
	       std::cout<<"the path used is: "<< path << std::endl;

		    return 0;

}




/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE
void build_basic_maze(nodeptr& start, nodeptr& finish){
    nodeptr tmpA = new node; // To create nodes
    tmpA->id = 'A';

    nodeptr tmpB = new node;
    tmpB->id = 'B';

    nodeptr tmpC = new node;
    tmpC->id = 'C';

    nodeptr tmpD = new node;
    tmpD->id = 'D';

    nodeptr tmpE = new node;
    tmpE->id = 'E';

    nodeptr tmpF = new node;
    tmpF->id = 'F';

    nodeptr tmpG = new node;
    tmpG->id = 'G';

    nodeptr tmpH = new node;
    tmpH->id = 'H';

    nodeptr tmpI = new node;
    tmpI->id = 'I';

    nodeptr tmpJ = new node;
    tmpJ->id = 'J';

    nodeptr tmpK = new node;
    tmpK->id = 'K';

    nodeptr tmpL = new node;
    tmpL->id = 'L';

    start = tmpA;       finish = tmpL;

    tmpA->north = tmpA;    tmpA->east = tmpB;    tmpA->south = tmpE;   tmpA->west = tmpA; // assign the nodes around

    //tmpE->north = tmpA;    tmpE->east = tmpF;    tmpE->south = tmpI;   tmpE->west = tmpE; // test the loop
		tmpE->north = tmpA;    tmpE->east = tmpE;    tmpE->south = tmpI;   tmpE->west = tmpE;
    tmpI->north = tmpE;     tmpI->east = tmpJ;    tmpI->south = tmpI;   tmpI->west = tmpI;
    tmpJ->north = tmpJ;     tmpJ->east = tmpJ;    tmpJ->south = tmpJ;   tmpJ->west = tmpI;

    tmpB->north = tmpB;     tmpB->east = tmpB;    tmpB->south = tmpF;   tmpB->west = tmpA;
		//tmpF->north = tmpB;     tmpF->east = tmpG;    tmpF->south = tmpF;   tmpF->west = tmpE; // test the loop
    tmpF->north = tmpB;     tmpF->east = tmpG;    tmpF->south = tmpF;   tmpF->west = tmpF;
    tmpG->north = tmpC;     tmpG->east = tmpH;    tmpG->south = tmpK;   tmpG->west = tmpF;

    tmpC->north = tmpC;     tmpC->east = tmpD;    tmpC->south = tmpG;   tmpC->west = tmpC;
    tmpD->north = tmpD;     tmpD->east = tmpD;    tmpD->south = tmpD;   tmpD->west = tmpC;

    tmpH->north = tmpH;     tmpH->east = tmpH;    tmpH->south = tmpL;   tmpH->west = tmpG;
    tmpK->north = tmpG;     tmpK->east = tmpK;    tmpK->south = tmpK;   tmpK->west = tmpK;

    tmpL->north = tmpH;     tmpL->east = tmpL;    tmpL->south = tmpL;   tmpL->west = tmpL;
}

nodeptr traverse_maze(const nodeptr& start, const std::string& path){
	nodeptr tmp = start;
	for (int i=0;i<path.size();i++){
		if(path[i]=='N'){tmp = tmp->north;}
		if(path[i]=='E'){tmp = tmp->east;}
		if(path[i]=='S'){tmp = tmp->south;}
		if(path[i]=='W'){tmp = tmp->west;}
	}
	return tmp;
}

void solve_interactively(const nodeptr& start, const nodeptr& finish, std::string& path){
nodeptr current=start;
std::string dir;
while(current !=finish){
	std::cout<<"You are in room "<<current->id<<" of the MAZE.!"<<std::endl;

	std::cout<<"Please enter your move,";
		if(current->north !=current){
			std::cout<<"(N)orth  ";
		}
		if(current->west !=current){
			std::cout<<"(W)est  ";
		}
		if(current->south !=current){
			std::cout<<"(S)outh  ";
		}
		if(current->east !=current){
			std::cout<<"(E)ast  ";
		}
		std::cout<<"(Q)uit!"; //Press Q to quit
		std::cout<<std::endl;

		std::cin>>dir;
		if((dir =="N")||(dir =="E")||(dir =="S")||(dir =="W")||(dir =="Q")){
			if(dir == "Q"){
				std::cout<<"Lose..."<<std::endl;
				return;
			}
			path+=dir;//store the path
			current= traverse_maze(start,path);
		}
	}

			std::cout<<"Congratulations, you reached the finish!"<<std::endl;

}

nodeptr random_walk(const nodeptr& start, const nodeptr& finish, std::string& path){

	std::srand(time(NULL));
	nodeptr current =start;
	path = "";
	int limit = 20; //set the limit when repetition occurs
	for (int i = 0;i<limit;i++){
		std::string directions = "";
		if(current->north != current){
			directions+= "N";
		}
		if(current->east != current){
			directions+= "E";
		}
		if(current->south != current){
			directions+= "S";
		}
		if(current->west != current){
			directions+= "W";
		}
		int pos = rand() %(directions.size());
		std::cout<<pos<<"  " <<directions[pos]<<std::endl;
		path = path +directions[pos];
		current = traverse_maze(start,path); // find the location of the current node
		if(current ==finish){
			std::cout<<"YES! You reached the end of the maze! You solved the maze in "<<i+1<<" steps."<<std::endl;
			return current;
		}
	}
		std::cout<<"Sorry, you could not solve the maze in "<<limit<<" steps."<<std::endl;
		return current;


}

void solve_queue(const nodeptr& start, const nodeptr& finish, std::string& path){
	nodeptr current= start;

	std::queue<nodeptr> not_visited,visited;
	path +=current->id;
	visited.push(current);

	if(current != finish && path[path.size()-1]!=finish->id){ // to see whether the finish is reached

		if(current->north != current && path.find((current->north)->id) == std::string::npos){
			not_visited.push(current->north);
		}
		if(current->east != current && path.find((current->east)->id) == std::string::npos){
			not_visited.push(current->east);
		}
		if(current->south != current && path.find((current->south)->id )== std::string::npos){
			not_visited.push(current->south);
		}

		if(current->west != current && path.find((current->west)->id) == std::string::npos){
			not_visited.push(current -> west);
		}

		while(!not_visited.empty()&& path[path.size()-1] !=finish->id){
			current = not_visited.front();// current node moves to the not_visited node
			not_visited.pop();//pop that not_visited node out of the queue
			solve_queue(current,finish,path);
			if(current->id == path[path.length()-1]&& current != finish ){ // out of the recursion and compare with the last node
				current= visited.front();
				path += current->id;

			}
		}
	}

	current = start;
	if(current->id == path[0]){ //convert the id to directions
		 int i =0;
		while (path[path.size()-1]==finish->id && i<path.size()){

			if(((current->north)->id) == path[i+1]){
				path[i]='N';
				current=current->north;
			}
			else if(((current->south)->id) == path[i+1]){
				path[i]='S';
				current=current->south;
			}
			else if(((current->east)->id) == path[i+1]){
				path[i]='E';
				current=current->east;
			}
			else if(((current->west)->id) == path[i+1]){
				path[i]='W';
				current=current->west;
			}
			i++;
		}
		path.erase(path.size()-1);
		while(!visited.empty()){
 		 visited.pop(); // clean up the dynamic memory
 	 }
	}
}
void solve_stack(const nodeptr& start, const nodeptr& finish, std::string& path){
	nodeptr current= start;
	std::stack <nodeptr> not_visited,visited;
	path +=current->id;
	visited.push(current);

	if(current != finish && path[path.size()-1]!=finish->id){

		if(current->north != current && path.find((current->north)->id) == std::string::npos){
			not_visited.push(current->north);
		}

		if(current->east != current && path.find((current->east)->id) == std::string::npos){
			not_visited.push(current->east);
		}
		if(current->south != current && path.find((current->south)->id )== std::string::npos){
			not_visited.push(current->south);
		}

		if(current->west != current && path.find((current->west)->id) == std::string::npos){
			not_visited.push(current -> west);
		}


		while(!not_visited.empty()&& path[path.size()-1] !=finish->id){
			current = not_visited.top();
			not_visited.pop();

			solve_stack(current,finish,path);

			if(current->id == path[path.length()-1]&& current !=finish ){
				current= visited.top();
				path += current->id;

			}
		}
	}
	current = start;
 if(current->id == path[0]){
		int i =0;
	 while (path[path.size()-1]==finish->id && i<path.size()){//convert the id to directions

		 if(((current->north)->id) == path[i+1]){
			 path[i]='N';
			 current=current->north;
		 }
		 else if(((current->south)->id) == path[i+1]){
			 path[i]='S';
			 current=current->south;
		 }
		 else if(((current->east)->id) == path[i+1]){
			 path[i]='E';
			 current=current->east;
		 }
		 else if(((current->west)->id) == path[i+1]){
			 path[i]='W';
			 current=current->west;
		 }
		 i++;
	 }
	 path.erase(path.size()-1);
	 while(!visited.empty()){
		 visited.pop(); // clean up the dynamic memory
	 }

 }
}
