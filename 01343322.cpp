/*
	First name	Jialong
	Last name		Yu
	Student ID	01343322
	Username		jy3717
*/

//IMPORTANT: before submitting your source code, please make sure to comment your main function (needed for automated testing)


#include <iostream>
#include <string>
#include <map>
#include <vector>


// do not use using namespace std

// do not alter the struct declaration
struct hufftreenode {
	char character;
	int frequency;
	hufftreenode* left;
	hufftreenode* right;
};

// do not alter the typedef
typedef hufftreenode* hufftreeptr;


// you can define and use any additional *structures* if you might need to

// YOUR CODE HERE FOR ADDIIONAL STRUCTS DECLARATION, IF ANY



/////////////////////////////////////////
// Functions declarations (prototypes) //
/////////////////////////////////////////

// do not alter these functions declarations

//utility function
bool valid_hufftree(const hufftreeptr hufftree);
 // returns true if the input hufftree is a valid Huffman tree
 // i.e. all the terminal nodes (leaves) have characters,
 // all the non-leaf nodes have two sub-trees each,
 // and the occurrence frequency of a non-leaf node equals
 // the sum of the occurrence frequencies of its two sub-trees.
void create_table(const hufftreeptr& t,std::map<char, std::string>& hufftable,std::string code);

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable);
// encodes an input message (a string of characters) into an encoded message (string of bits) using the Huffman coding
// builds the Huffman tree and its associated encoding table (i.e. the association between the characters in the tree leaves and their encodings (string of bits))

std::string huffdecode(const std::string& encodedmessage, const hufftreeptr& hufftree);



// decodes an encoded message (a string of bits) into the original message (a string of characters) using the Huffman tree built during the encoding



// you can define and use any additional *functions* if you might need to

// YOUR CODE HERE FOR ADDIIONAL FUNCTIONS DECLARATION (NOT THE IMPLEMENTATION), IF ANY




///////////////////
// main function //
///////////////////

//IMPORTANT (Reminder): before submitting your source code, please make sure to comment your main function (needed for automated testing)
int main() {

	// YOUR CODE HERE FOR TESTING YOUR PROGRAM

	// an example of basic encoding/decoding

	std::string message, encodedmessage, decodedmessage;
	hufftreeptr hufftree;
	std::map<char, int> freqtable;
	std::map<char, std::string> hufftable;


	//message = randomCharGenerator(length);
//	std::cout<<message<<std::endl;

message= "go go gophers";



	encodedmessage = huffencode(message, freqtable, hufftree, hufftable);


	// freqtable should be as in Table 1.
	// hufftree might be as in Figure 2 (remember, the Huffman coding tree IS NOT UNIQUE. If we swap two siblings in a Huffman tree, it is still a Huffman tree of the same message.)
	// hufftable should correspond to hufftree, and might be as in Table 2 <' ',"100">, <'g',"00">, <'o',"01">, <'p',"1110">, <'h',"1101">, <'e',"101">, <'r',"1111">, <'s',"1100">.
	// encodedmessage might then be the 37-bits string "0001100000110000011110110110111111100" (i.e. "00.01.100.00.01.100.00.01.1110.1101.101.1111.1100")
	//(hufftree->left)->frequency = 'T';


//  printtree(hufftree);
		 //start= clock();

	if(valid_hufftree(hufftree))  {
		std::cout << "valid Huffman tree." << std::endl;
	}
	else {
		std::cout << "not valid Huffman tree." << std::endl;
	}

	// 2) decoding (uncompression)
//	start= clock();

 decodedmessage = huffdecode(encodedmessage, hufftree);




	//end = clock();
// std::cout<<"decode time = "<<(end-start)/1000<<std::endl;

	// should be "go go gophers"

	if(decodedmessage == message) {
		std::cout << "decoding OK." << std::endl;
	}
	else {
		std::cout << "decoding not OK." << std::endl;
	}
//	std::cout<<decodedmessage<<std::endl;


	return 0;
}

bool valid_hufftree(const hufftreeptr hufftree){

 	 hufftreeptr current = hufftree;
	 while(current != NULL){

			if(current->left == NULL && current->right == NULL){  // check all the terminal nodes (leaves) have characters,

				 if(current->character == '\0'){

					return false;

				 }

			}

			if((current->left != NULL && current->right == NULL)||(current->left == NULL && current->right != NULL)){

			 return false;	// check all the non-leaf nodes have two sub-trees each,

			}

			if(current->left != NULL && current->right != NULL){

				 if(current->frequency != (current->left->frequency + current->right->frequency)){

					return false; // check the occurrence frequency of a non-leaf node equals
				  // the sum of the occurrence frequencies of its two sub-trees.
				 }
			}

			return valid_hufftree(current->left) & valid_hufftree(current->right); // if one of them are false then return false

	 }

	 return true; // returns true if the input hufftree is a valid Huffman tree

}

std::string huffencode(const std::string& message, std::map<char, int>& freqtable, hufftreeptr& hufftree, std::map<char, std::string>& hufftable){

	std::map<char,int>::iterator iter_freqtable;
	std::map<char,std::string>::iterator iter_hufftable;
	int character_count[256]={0};

	for(int i=0; message[i] != '\0'; i++){

			character_count[message[i]]++;

	}

	for(int i = 0; i<256; i++){
		if(character_count[i]!=0){

			freqtable[char(i)] = character_count[i];

		}
	}

	std::vector<hufftreeptr> forest; // create forest
	std::string code ="\0";

	for(iter_freqtable= freqtable.begin();iter_freqtable!=freqtable.end();iter_freqtable++){ // push all the trees into the forest

			hufftreeptr tmp = new hufftreenode;
			tmp->character = iter_freqtable->first;
			tmp->frequency = iter_freqtable->second;
			tmp->left = NULL;
			tmp->right = NULL;
			forest.push_back(tmp);
		}

    int min_node_position =0;
    int min_frequncy = forest[0]->frequency;

		while(forest.size()>1){

					hufftreeptr minimum_node = new hufftreenode;
					minimum_node->character = '\0';

					for(int i = 0;i<forest.size();i++){
		          if (min_frequncy >=((forest[i]->frequency))){ // find the node with the smalles frequency
		            min_node_position=i;
		            min_frequncy = forest[i]->frequency;
		          }
	        }

	        minimum_node->left = forest[min_node_position]; //link the sub node to the new node
	        forest.erase(forest.begin()+min_node_position); // erase that vector

	        min_node_position=0;
	        min_frequncy = forest[0]->frequency;

	        for(int i = 0;i<forest.size();i++){
		          if (min_frequncy >=((forest[i]->frequency))){
		            min_node_position=i;
		            min_frequncy = forest[i]->frequency;
		          }
	        }

	        minimum_node->right = forest[min_node_position];
	        forest.erase(forest.begin()+min_node_position);

	        minimum_node-> frequency = ((minimum_node->left)->frequency)+((minimum_node->right)->frequency);
	        forest.push_back(minimum_node);
			}

		hufftree=forest[0];
		create_table(hufftree,hufftable,code);

		code="\0";
		for(int i = 0;i<message.size();i++){

				iter_hufftable=hufftable.find(message[i]);
				code+=iter_hufftable->second;

		}

		 //assign the pointer to the root of the hufftree

		return code;
	}

std::string huffdecode(const std::string& encodedmessage,const hufftreeptr& hufftree){

	hufftreeptr current = hufftree;
	std::string decode="\0"; //initiate decoded message

	for(int i=0;i<encodedmessage.size();i++){

			if(encodedmessage[i]=='1'){

				current=current->right;

				if((current->character)!='\0'){ //if reached the leaf node return to the start
					decode+=current->character;
					current=hufftree;
				}

			}
			else{
				current=current->left;

				if((current->character)!='\0'){
					decode+=current->character;	// add the character to the decoded message
					current=hufftree;		// send the pointer back to the root
				}
			}

    }

	return decode;
}


void create_table(const hufftreeptr& t,std::map<char, std::string>& hufftable,std::string code){
	// this function is used to create huffman table
	hufftreeptr tmp = t;

	  if(tmp->left == NULL && tmp->right == NULL){
	    hufftable[tmp->character] = code;  // store the character and its codeword at leaf node
	  }

	  if(tmp->left != NULL){
	    create_table(tmp->left, hufftable, code + '0'); // recursion into left node if not at leaf node with code+"0"
	  }

	  if(tmp->right != NULL){
	    create_table(tmp->right, hufftable, code + '1');// recursion into right node if not at leaf node with code+"1"
	  }

}

/////////////////////////////////////////////
// Functions definitions (implementations) //
/////////////////////////////////////////////

// YOUR CODE HERE FOR THE FUNCTIONS IMPLEMENTATIONS
