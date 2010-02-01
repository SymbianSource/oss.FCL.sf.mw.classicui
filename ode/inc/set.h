#ifndef SET_H_
#define SET_H_

typedef class pair pair;
typedef class iterator iterator;

#define MAX 50



class set
{
   private:
		int n; 
		pair* el;
   public:
		set(); //constructor
		int addElem(pair e);  //adds the specified pair to this set
		int delElem(pair e); //removes the specified pair from this set
		int belongs(pair e); // returns true if this set contains the e pair.
		int length(); //returns the number of pairs in this set
    	int isEmpty(); //returns true if this set contains no pairs.
		pair getElem(int i); //returns the i-th pair 
		iterator* setIterator(); //returns an iterator over the pairs in this set.
		~set(); //destructor
};

class iterator
{
	private:         
		set* s;
  		int current; //current refers the current pair
	public:
    	iterator(set* sc); //constructor
   		~iterator(); //destructor
    	pair getElem(); //returns  the current pair 
    	int hasNext(); //returns true if the iteration has more pairs.
		void next(); // moves the current to the next pair
    	void setToFirst(); // first pair is current
};

class pair
{
	private:
		int anum1;
		int anum2;
	public:
		pair();
		pair(int num1, int num2);
		~pair();
		int getNum1();
		int getNum2();
};


#endif /*SET_H_*/
