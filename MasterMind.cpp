#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

void set_random_seed();
int randn(int n);
int max(int x, int y);
struct mm_code_maker{

	void init(int i_length, int i_num){
    	length = i_length;
    	num = i_num;
	}

	void generate_sequence(){
    	for(int i = 0; i < length; i++){
        	sequence.push_back(randn(num));
    	}
	}

	void give_feedback(const std::vector<int>& attempt, int& black_hits, int& white_hits){
  	black_hits=0;
  	for(int i=0;i<attempt.size();i++){
  	for(int j=0; j<attempt.size();j++){
    	if(sequence[i]==attempt[j]&& i==j){
      	black_hits++;
    	}
  	}
	}
	int total_hits=0;
  	for(int i=0;i<num;i++){
    	int a=0,b=0;
    	for(int j=0;j<attempt.size();j++){
      	if(attempt[j]==i){
        	a++;
      	}
      	if(sequence[j]==i){
        	b++;
      	}
    	}
    	if(a>=b){
      	total_hits=total_hits+b;
    	}
    	else{
      	total_hits=total_hits+a;
    	}
  	}
  	white_hits= total_hits - black_hits;
	}

	std::vector<int> sequence;

	int length;
	int num;
};

struct mm_solver{

	void init(int i_length, int i_num){
    	length = i_length;
    	num = i_num;
	}

	void create_possibilites (){
  	std::vector<int> comb;
  	int possibilities_size = pow(num,length);
		std::cout<< possibilities_size<<std::endl;
  	for(int i=0;i<length;i++){
    	comb.push_back(0);
  	}
  	for(int i=1;i<=possibilities_size;i++){
    	for(int j=0;j<length;j++){
      	if(j==(length-1)){
        	comb[j]=(i-1)%num;
      	}
      	else{
        	int denominator=pow(num,length-1-j);
        	comb[j]=((i-1)/denominator)%num;
      	}
    	}
  	combinations.push_back(comb);

  	}
	}
	/// this member function creates an attempt to find the right code
	/// this version generates a random a ttempt, then checks whether
	/// it has already been tried before and was not the right solution
	/// (if that's the case it generates another attempt etc)
	/// this is clearly still far from being a good implementation!
	void create_attempt(std::vector<int>& attempt){
    		int random = randn(combinations.size());
    		attempt=combinations[random];
  	}


	/// this version just learns whether an attempt is correct or not
	/// if it is not, it adds it adds it to the list of unsuccessful attempts
	/// this is clearly still far from being a good implementation
	/// the information from black hits and white hits is not really used
	void learn(std::vector<int>& attempt, int black_hits, int white_hits){
    		std::vector<std::vector<int> > remain_combinations;
    	int b_hits,w_hits;

    	for(int i=0;i< combinations.size();i++){

        	give_feedback2(attempt,b_hits,w_hits,combinations[i]);
        	if(b_hits==black_hits&&w_hits==white_hits&& combinations[i]!=attempt){
          	remain_combinations.push_back(combinations[i]);
        	}

    	}
	combinations=remain_combinations;
	}

	void give_feedback2(const std::vector<int>& attempt, int& black_hits, int& white_hits,const std::vector<int> comb){
  	black_hits=0;
  	for(int i=0;i<attempt.size();i++){
  	for(int j=0; j<attempt.size();j++){
    	if(comb[i]==attempt[j]&& i==j){
      	black_hits++;
    	}
  	}
	}
	int total_hits=0;
  	for(int i=0;i<num;i++){
    	int a=0,b=0;
    	for(int j=0;j<attempt.size();j++){
      	if(attempt[j]==i){
        	a++;
      	}
      	if(comb[j]==i){
        	b++;
      	}
    	}
    	if(a>=b){
      	total_hits=total_hits+b;
    	}
    	else{
      	total_hits=total_hits+a;
    	}
  	}
  	white_hits= total_hits - black_hits;
	}


	std::vector<std::vector<int> > combinations;
	int length;
	int num;

};

/// the main is the same as in the previous example

int main(){

	set_random_seed();

	int length, num;
	std::cout << "enter length of sequence and number of possible values:" << std::endl;
	std::cin >> length >> num;

	mm_solver solver;
	solver.init(length, num);

	mm_code_maker maker;
	maker.init(length, num);
	maker.generate_sequence();
	//generate all the combinations
	solver.create_possibilites();

	int black_hits=0, white_hits=0;
	int attempts_limit = 5000;
	int attempts = 0;
	while((black_hits < length) && (attempts < attempts_limit)){
    	std::vector<int> attempt;
    	solver.create_attempt(attempt);
    	maker.give_feedback(attempt, black_hits, white_hits);
    	std::cout << "attempt: " << std::endl;
    	for(int i = 0; i < attempt.size(); i++){
        	std::cout << attempt[i] << " ";
    	}
    	std::cout << std::endl;
    	std::cout << "black pegs: " << black_hits << " " << " white pegs: " << white_hits << std::endl;

    	solver.learn(attempt, black_hits, white_hits);
    	attempts++;
	}

	if(black_hits == length){
    	std::cout << "the solver has found the sequence in " << attempts << " attempts" << std::endl;
	}
	else{
    	std::cout << "after " << attempts << " attempts still no solution" << std::endl;
	}
	std::cout << "the sequence generated by the code maker was:" << std::endl;
	for(int i = 0; i < maker.sequence.size(); i++){
    	std::cout << maker.sequence[i] << " ";
	}

	std::cout << std::endl;
	return 0;
}

void set_random_seed(){
	std::srand(std::time(0));
}

int randn(int n){
	return std::rand() % n;
}
int max(int x, int y) {
	if (x >= y) {
    	return x;
	}
	else {
    	return y;
	}

}





