#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

int array_count=0; //global variable made to track the number of paths found

template <typename t>
class _stack{
	private:
	t* arr; //stack using dynamic array 
	int top; //this points to top or recently added element of stack
	int size; //this is size of stack 
		
	public:
	_stack(){
		top=-1; //because 0 is considered a vaid index inside the array so -1
		arr=NULL; 
		size=0;
	}
	_stack(int a){
		size=a; //this much size of array made as we should know the size of stack or pre allocate it as it is not linked list
		top=-1;
		arr=new t[a];
	}
	
	void setsize(int a){
		size=a;
		top=-1;
		arr=new t[a];
	}
	
	void push(t a){
		if(top>size){
			cout<<"\nStack full\n";
		}
		top++; //top increased
		arr[top]=a; //element placed on top of stack
	}
	
	//assignment operator
	_stack<t>& operator=(_stack<int>& obj){
		if(this!=&obj){
			delete[] this->arr;
			this->arr=NULL;
			this->size=obj.size;
			this->top=obj.top;
			this->arr=new int [size];
			memcpy(this->arr,obj.arr,sizeof(t)*obj.size);
		}
		else return *this;
	}
	
	t pop(){ 
		if(top!=-1){
		t a;
		a=arr[top];
		top--; //removes object and returns it
		return a;
	    }
	    else{
		cout<<"\nStack is empty so no pop\n"; //error handling if popped from already empty stack
	    return 0; //as this was uninitialized value
		}
	}
	
	int getsize(){ //this returns size of stack and not the size of array
		if(!isempty())
		return top+1; //because top starts from -1
		else{
	    return 0;
		}
	}
	
	t gettopelement(){ //this is basically a peeking function that returns the element from stack but does not remove it from stack
		if(!isempty()){
			return arr[top];
		}
		else{
		cout<<"\nStack is empty\n";
	    return 0;
		}
	}
	
	bool isempty(){ //checks whether stack is empty or not
		if(top!=-1){
			return false;
		}
		else return true;
	}
	
	void printstack(){ //this is printing of stack to know the status of stack
		for(int i=0;i<top+1;i++){
			cout<<arr[i]<<" ";
		}
	}
	
	t getelement(int i){ //returns an element from the stack array. This is peeking from a certain position on the stack with no effect on the top
		return arr[i];
	}
	
};

template <typename t>
class dynamicsafe2darray{
	
	private:
	t **ptr;
	int row;
	int col;
	int start_row;
	int start_col;
	int end_row;
	int end_col;
		
	public:
	//constructors
	
	//default constructor	
	dynamicsafe2darray(){
	ptr=NULL;
	row=0;
	col=0;
	start_row=0;
	start_col=0;
	end_row=-1;
	end_col=-1;
	}
	
	//parameterized constructor
	dynamicsafe2darray(int a,int b){
	ptr=new t*[a];
	for(int i=0;i<a;i++){
	ptr[i]=new t[b];
    }
	row=a;
	col=b;
	start_row=0;
	start_col=0;
	end_row=-1;
	end_col=-1;
	for(int i=0;i<a;i++){ //allocating null to all the pointer locations
	memset(ptr[i],0,sizeof(t)*col);
    }
	}
	
	//copy constructor
	dynamicsafe2darray(const dynamicsafe2darray& obj){
	this->ptr=new t*[obj.row];
	for(int i=0;i<obj.row;i++){
		this->ptr[i]=new t[obj.col];
		memcpy(this->ptr[i],obj.ptr[i],sizeof(t)*obj.col);
	}
	this->row=obj.row;
	this->col=obj.col;
	}
	
	//setget fuctionalities
	void setelement(int i,int j,t element){
		ptr[i][j]=element;
	}
	
	t getelement(int i,int j){
		return ptr[i][j];
	}
	
	int getrow(){return row;}
	int getcol(){return col;}
	int getstartrow(){return start_row;}
	int getstartcol(){return start_col;}
	int getendrow(){return end_row;}
	int getendcol(){return end_col;}
    
    void getstartpoint(){
    	cout<<"("<<start_row-1<<","<<start_col-1<<")";
	}
	
	void getendpoint(){
    	cout<<"("<<end_row-1<<","<<end_col-1<<")";
	}
    
    //start and end point locator
    void startpoint_locator(){ //locating coords of 's' in array
    	
	    for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				if(ptr[i][j]=='s'){
					start_row=i;
					start_col=j;
				}
			}
  }
		
    }
    
    void endpoint_locator(){ //locating coords of 'e' in array
    	
	    for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				if(ptr[i][j]=='e'){
					end_row=i;
					end_col=j;
				}
			}
		}
    }
    
    bool multiplestartend(){ //this checks that whether invalid condition of multiple starts or ends is not present
		int count=0;
		for(int i=0;i<row;i++){ 
			for(int j=0;j<col;j++){
				
					if(ptr[i][j]=='s'){
						count++;
					}
					else if(ptr[i][j]=='e'){
						count++;
					}
				
			}
		}
		if(count==2){
			return true;
		}
		else return false;
	}
	
	bool isend(int x,int y){ //checks whether the specified point is end point or not
		if(x==getendrow() && y==getendcol()){
			return true;
		}
		else return false;
	}
	
	bool startpresent(){ //this checks whether start point is present or not 
    	for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				if(ptr[i][j]=='s'){
					return true;
				}
			}
		}
		return false;
	}
	
	bool endpresent(){ //this checks whether end point is present or not 
    	for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				if(ptr[i][j]=='e'){
					return true;
				}
			}
		}
		return false;
	}
	
	bool boundarychecker(){ //this is for checking whether s or e are at boundary	
		//if s or e is present at boundary then count is incremented. Count being 2 means both end and start are present and will not be valid for anyother conditions
		int count=0;
		for(int i=0;i<row;i++){ 
			for(int j=0;j<col;j++){
				if(i==1 || j==1 || i==row-2 || j==col-2){ 
					if(ptr[i][j]=='s'){
						count++;
					}
					else if(ptr[i][j]=='e'){
						count++;
					}
				}
			}
		}
		if(count==2){
			return true;
		}
		else return false;
	}
  
	//operator overloading
	
	t operator()(int a,int b){ //returns dereferenced value 
		return *(*(ptr+a)+b);
	}
	
	friend ostream& operator<<(ostream& out,dynamicsafe2darray& d){
		for(int i=0;i<d.row;i++){
			for(int j=0;j<d.col;j++){
				cout<<d.ptr[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	
	bool notvalid(int x,int y){ //this checks whether the point is a valid point within the boundary or not
		if(x < 1 || y < 1 || y >= col+2||  x>= row+2){
			return true;
		}
		else return false;
	}
	
	void print(){ //print the maze
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
				cout<<ptr[i][j]<<" ";
			}
			cout<<endl;
		}
	}
    
	//xarr and yarr are basically pointers to array of stack objects that holds the address of the stack containing a path  
	void pathfinder(int x,int y,_stack<int>& sx,_stack<int>& sy,_stack<int> *xarr,_stack<int> *yarr){ //this is the path calculation phase implemented using depth first search
	   	    
		if (notvalid(x,y) || ptr[x][y]=='0') { //checks that if the point is not valid or is a possible dead end or blockage then return
		return;        
		}
	
		sx.push(x-1); //pushes the x_coord onto the stack
		sy.push(y-1); //pushes the y_coord onto the stack

		if (isend(x,y)){ //if the end point occurs then
		xarr[array_count]=sx; //assignment operator made to use here! the stack is copied to the stack located at array_count of xarr.
		yarr[array_count]=sy; //same as xarr
		array_count++;
		} 
		
        else{ //if not endpoint then
		ptr[x][y]='0';  //initially sets the visited location to a blockage so that we donot revisit that location
		pathfinder(x,y+1,sx,sy,xarr,yarr); //recursion run for finding all four possible paths
		pathfinder(x,y-1,sx,sy,xarr,yarr);
		pathfinder(x+1,y,sx,sy,xarr,yarr);
		pathfinder(x-1,y,sx,sy,xarr,yarr);
		ptr[x][y]='1'; //after returning from the call it is again set to a possible path
        }
	
		sx.pop(); //if dead end occurs and the path is not valid the to pop them from both the stacks
		sy.pop();	
	} 
	
	 	
	//destructor
	~dynamicsafe2darray(){
		for(int i=0;i<row;i++){
			if(ptr[i]!=0)
			delete[] ptr[i];
			ptr[i]=NULL;
		}
		delete[] ptr;
	}
	
};

void sortstack(_stack<int> *arrx,_stack<int> *arry){ //this fucntionality is made to sort the stack array in ascending order as per the cost
	
	//selection sort is used here
	_stack<int> tempx; //temporary stack objects made inorder to swap stack objects within the array of stack objects
	_stack<int> tempy;
	int min;
	
	for(int i=0;i<array_count;i++){
		min=i;
		for(int j=i+1;j<array_count;j++){
			if(arrx[j].getsize()<arrx[min].getsize()){ //if the condition for x satisfies then the condition for y also satifies hence only one condition is checked here
				min=j;
			}
		}
		tempx=arrx[min]; //for x_coord
		arrx[min]=arrx[i];
		arrx[i]=tempx;
		
		tempy=arry[min]; //similarly for y_coord
		arry[min]=arry[i];
		arry[i]=tempy;
	}
	
}

int main(){
	
	char a;
	int row,col;
	string path;
	_stack<int> s_x(1000); //a large size taken to avoid overflow condition
	_stack<int> s_y(1000); //a large size taken to avoid overflow condition
	_stack<int> s_xarray[1000]; //a large size taken to avoid overflow condition
	_stack<int> s_yarray[1000]; //a large size taken to avoid overflow condition
	int sorted_size;
	
	fstream infile,obj1;
	///*********hardcoded testcase. You can manually input your testcase file name here***************
	infile.open("A2P1-in-01.txt",ios::in); 
	
	if(!infile){
	cout<<"\nfile not found\n";
	exit(0);
	}
	
	infile>>row;
	infile>>col;
	
	row+=2; //this is done to make a boundary of walls around the array so that there is no out of bound
	col+=2;
	
	dynamicsafe2darray<char> d(row,col);
	
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(i==0 || i==row-1 || j==0 || j==col-1){
				d.setelement(i,j,'0'); // boundary of walls made
			}
		}
    }
	
	for(int i=1;i<row-1;i++){ //now the points are (i+1,j+1) hence starts from i and j till row-1 and col-1 because at row and col there is '*'
		for(int j=1;j<col-1;j++){
			infile>>a;
			d.setelement(i,j,a); //
		}
    }
    
    if(!d.startpresent() || !d.endpresent()){ //checking if the input is valid or not
    	
    	cout<<"No start or end point present";
    	fstream obj;
		obj.open("A2P1-out.txt",ios::out|ios::trunc);
    	obj<<"No start or end point present";
    	obj.close();
		exit(0);
	}
	
	if(!d.multiplestartend()){ //checking that there are no multiple start or end points
		cout<<"There can be no multiple start or end point.";
		fstream obj;
		obj.open("A2P1-out.txt",ios::out|ios::trunc);
    	obj<<"There can be no multiple start or end point.";
    	obj.close();
		exit(0); //if not then illegal exit
	}
	
	if(!d.boundarychecker()){ //this is checking whether the start or end is at the boundary or not
		cout<<"Start or end point is not on boundary.";
		fstream obj;
		obj.open("A2P1-out.txt",ios::out|ios::trunc);
    	obj<<"Start or end point is not on boundary.";
    	obj.close();
		exit(0); //if not then illegal exit
	}
	
	cout<<d;
	
	d.startpoint_locator();
	d.endpoint_locator();
	d.setelement(d.getstartrow(),d.getstartcol(),'1'); //as 's' is not recognized a valid point within the path finder hence we set it to '1' and then run the path finder
	d.pathfinder(d.getstartrow(),d.getstartcol(),s_x,s_y,s_xarray,s_yarray);
	
	obj1.open("A2P1-out.txt",ios::out|ios::trunc);
	
	if(s_xarray[0].getsize()==0){ //if no end point found then all the pushes were popped leaving the top to -1 for both stacks and hence no solution
		cout<<"No solution. Cannot reach end";
		obj1<<"No solution. Cannot reach end";
		obj1.close();
		exit(0);
	}
	
    sortstack(s_xarray,s_yarray); //the array of stacks are sorted according to cost in ascending order

    //printing the array of stacks
	for(int i=0;i<array_count;i++){
		int counter=s_xarray[i].getsize();
		obj1<<"Path#"<<i+1<<"={";
		cout<<"Path#"<<i+1<<"={";
		for(int j=0;j<counter;j++){
		if(j==counter-1){ 
		cout<<"("<<s_yarray[i].getelement(j)<<","<<s_xarray[i].getelement(j)<<")";
		obj1<<"("<<s_yarray[i].getelement(j)<<","<<s_xarray[i].getelement(j)<<")";
		}
		else{
		cout<<"("<<s_yarray[i].getelement(j)<<","<<s_xarray[i].getelement(j)<<"), ";
		obj1<<"("<<s_yarray[i].getelement(j)<<","<<s_xarray[i].getelement(j)<<"), ";
	    }
	    }
	    obj1<<"}";
	    cout<<"}";
	    cout<<" Cost: "<<s_xarray[i].getsize();
	    obj1<<" Cost: "<<s_xarray[i].getsize();
	    cout<<endl;
	    obj1<<endl;
	}
	
}
