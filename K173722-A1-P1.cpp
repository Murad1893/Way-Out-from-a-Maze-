/*
Made by: K173722
Q1
Maze problem

Overview:
This program finds a path towards the end point from a known location of startpoint. Once traversing it hits a point it marks it as '!' visited to avoid going back to that location.
If it hits a dead end it starts locating 'x' onto the visited location so that the pointer will not come here again.
It will mark 'x' until it finds an available path '-' in front of it and if it does then it start to traverse again until the next dead end or end point found
Then once end point found it will locate all the visited location and mention its coordinates in file
In this whole program precedence of checking is right,down,left,upward

*/

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <string.h>

using namespace std;

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
	
	t getelement(int i,int j)const{
		return ptr[i][j];
	}
	
	int getrow(){return row;}
	int getcol(){return col;}
	int getstartrow(){return start_row;}
	int getstartcol(){return start_col;}
	int getendrow(){return end_row;}
	int getendcol(){return end_col;}
    
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
	
	//other fucntionalities
	
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
	
	int countwalls(int a,int b){ //this checks how many walls are there around point (a,b)
		t c;
		int count=0;
		c=getelement(a+1,b);
		if(c=='*'){
		   count+=1;
		}
		c=getelement(a-1,b);
		if(c=='*'){
			count+=1;
		}
		c=getelement(a,b+1);
		if(c=='*'){
			count+=1;
		}
		c=getelement(a,b-1);
		if(c=='*'){
		    count+=1;
		}
		return count;
	}
	
	bool deadendchecker(int a){ //if the number of walls around a '-' is 3 meaning no available path and hence dead end
		if(a==3){
			return true;
		}
		else return false;
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
	
	bool multiplestartend(){
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
	
	bool endpoint(int a,int b){ //checks whether there is an endpoint on any of the four sides (a,b). If end point is found then end point coords are saved into the object else both are default '-1'
	t c;
    c=getelement(a,b+1);
	if(c=='e'){ 
	    end_row=a;
	    end_col=b+1; 
		return true;
	}
	else{
		c=getelement(a+1,b);
		if(c=='e'){
		   end_row=a+1;
	       end_col=b;
			return true;
	    }
	    else{
			c=getelement(a,b-1);
			if(c=='e'){
			    end_row=a;
	            end_col=b-1; 
				return true;
			}
			else{
				c=getelement(a-1,b);
				if(c=='e'){
				    end_row=a-1;
	                end_col=b;
					return true;
				}	
				else{
					return false;	
					}
				}
			}
			
		}
    }
    
    bool path(int a,int b){ //checks whether there is a path available on any of the four sides of (a,b) 's' is also treated as a valid path
    t c;
    c=getelement(a,b+1);
	if(c=='-'  || c=='s'){
		return true;
	}
	else{
		c=getelement(a+1,b);
		if(c=='-'  || c=='s'){
			
			return true;
	    }
	    else{
			c=getelement(a,b-1);
			if(c=='-'  || c=='s' ){
				
				return true;
			}
			else{
				c=getelement(a-1,b);
				if(c=='-'  || c=='s' ){
					
					return true;
				}	
				else{
					return false;	
					}
				}
			}
			
		}
	}
	
	bool checkvisited(int a,int b){ //checks whether there is any visited location around the point
	t c;
    c=getelement(a,b+1);
	if(c=='!'){
		return true;
	}
	else{
		c=getelement(a+1,b);
		if(c=='!' || c=='e'){ //as it cannot reach illegally end hence 'e' is also considered to be visited point until traversed from the original path
			
			return true;
	    }
	    else{
			c=getelement(a,b-1);
			if(c=='!' || c=='e'){
				
				return true;
			}
			else{
				c=getelement(a-1,b);
				if(c=='!' || c=='e'){
					
					return true;
				}	
				else{
					return false;	
					}
				}
			}
			
		}
	}
	
	void restartpoint(int a,int b){ //checks whether the pointer has the start point anywhere around it hence it starts all over again from start point
    t c;
	c=getelement(a,b+1);
	if(c=='s'){
		pathfinder(a,b+1); //path finding is now started again from point 's'
	}
	else{
		c=getelement(a+1,b);
		if(c=='s'){
			pathfinder(a+1,b);
	    }
	    else{
			c=getelement(a,b-1);
			if(c=='s'){
				pathfinder(a,b-1);
			}
			else{
				c=getelement(a-1,b);
				if(c=='s'){
					pathfinder(a-1,b);
				}	
				else{
					return;	
					}
				}
			}
			
		}
	}
	
	

	void pathdeletor(int a,int b){ //this is for marking 'x' meaning deleting that path
		t c;
		c=getelement(a,b);
		if(path(a,b)){ //if a path is found then start traversing the path
			pathfinder(a,b);
			restartpoint(a,b);	//if the considered path is a 's' then call this fucntion else if it hits 's' then it will not start for other path as pathfinder is for '-' not 's'!
		}
		else{
		c=getelement(a,b+1); 
		if(c=='!'){
			setelement(a,b,'x');
			pathdeletor(a,b+1);	 //recursion calling to mark 'x'
	    }
	    else{
		c=getelement(a+1,b);
		if(c=='!'){
			setelement(a,b,'x');
			pathdeletor(a+1,b);	 
	    }
	    else{
		c=getelement(a,b-1);
		if(c=='!'){
			setelement(a,b,'x');
			pathdeletor(a,b-1);	 
	    }
		else{
		c=getelement(a-1,b);
		if(c=='!'){
			setelement(a,b,'x');
			pathdeletor(a-1,b);	 
	    }
	    else return;
	    }
	    }
	    }
		}
		
	}
	
	void pathfinder(int a,int b){ 
	    t c,d;
	    //coords saved in file is ignoring the added boundary hence the coords are (x-1,y-1)
		if(endpoint(a,b)){ //if the end point is found
			int i,j;
			i=getstartrow(); //now we start filing from the start point
			j=getstartcol();
		
		
			fstream obj;
			obj.open("outputA1P1.txt",ios::app);
			
			while(!endpoint(i,j)){ // until we reach a point where end is around run this loop
			c=getelement(i,j+1);
		
			if(c=='!' && checkvisited(i,j+1)){ //this is mainly to avoid error like ! ! s ! x meaning that we have to check that the next and its next is not a blocked location then add '+' so that filing can be done linearly and will not disrupt
			obj<<i-1<<" "<<j<<endl;
			setelement(i,j+1,'+');
			j++;
			}
			else{
			c=getelement(i+1,j);
	
			if(c=='!' && checkvisited(i+1,j)){
			obj<<i<<" "<<j-1<<endl;
			setelement(i+1,j,'+');
			i++;
			}
			else{
			c=getelement(i,j-1);
		
			if(c=='!' && checkvisited(i,j-1)){
			obj<<i-1<<" "<<j-2<<endl;
			setelement(i,j-1,'+');
			j--;
			}
			else{
			c=getelement(i-1,j);
		
			if(c=='!' && checkvisited(i-1,j)){
			obj<<i-2<<" "<<j-1<<endl;
			setelement(i-1,j,'+');	 
			i--;
			}
			}
			}
			}
		    }
		    obj<<end_row-1<<" "<<end_col-1; //once end point is found write it into the file. 
		    
	    	return;
		}
		else{
		c=getelement(a,b+1);
		if(c=='-'){
			if(deadendchecker(countwalls(a,b+1)) || getelement(a,b+2)=='!'){ //if the path is dead end or if the next element is a visited location then it is also a dead end as you can not go to that location
			setelement(a,b+1,'x');
			pathdeletor(a,b);
			}
			else{
			setelement(a,b+1,'!');
			pathfinder(a,b+1);
			}  
	    }
	    else{
		c=getelement(a+1,b);
		if(c=='-'){
			if(deadendchecker(countwalls(a+1,b)) || getelement(a+2,b)=='!'){
			setelement(a+1,b,'x');
			pathdeletor(a,b);
			}
			else{
			setelement(a+1,b,'!');
			pathfinder(a+1,b);
			}	
		}
	    else{
		c=getelement(a,b-1);
		if(c=='-'){	
			if(deadendchecker(countwalls(a,b-1)) || getelement(a,b-2)=='!'){
			setelement(a,b-1,'x');
			pathdeletor(a,b);
			}
			else{
			setelement(a,b-1,'!');
			pathfinder(a,b-1);
			}
		}
		else{
		c=getelement(a-1,b);
		if(c=='-'){
			if(deadendchecker(countwalls(a-1,b)) || getelement(a-2,b)=='!'){
			setelement(a-1,b,'x');
			pathdeletor(a,b);
			}
			else{
			setelement(a-1,b,'!');
			pathfinder(a-1,b);
			}
		}
	    }
	    }
	    }
		}   
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

int main(){	
	//in this program end point coordinates are not located until it is found and there is no threat that recursion will occur for no end point as first it is checked whether 'e' is present in array or not
	char a;
	int row,col;
	
	fstream infile;
	///*********hardcoded testcase. You can manually input your testcase file name here***************
	infile.open("input1.txt",ios::in); 
	
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
				d.setelement(i,j,'*'); // boundary of walls made
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
		obj.open("outputA1P1.txt",ios::out|ios::trunc);
    	obj<<"No solution";
    	obj.close();
		exit(0);
	}
	
	if(!d.multiplestartend()){ //checking that there are no multiple start or end points
		cout<<"There can be no multiple start or end point.";
		fstream obj;
		obj.open("outputA1P1.txt",ios::out|ios::trunc);
    	obj<<"No solution";
    	obj.close();
		exit(0); //if not then illegal exit
	}
	
	if(!d.boundarychecker()){ //this is checking whether the start or end is at the boundary or not
		cout<<"Start or end point is not on boundary.";
		fstream obj;
		obj.open("outputA1P1.txt",ios::out|ios::trunc);
    	obj<<"No solution";
    	obj.close();
		exit(0); //if not then illegal exit
	}
	
    fstream obj;
    obj.open("outputA1P1.txt",ios::out|ios::trunc);
    d.startpoint_locator(); //locate start point first
    obj<<d.getstartrow()-1<<" "<<d.getstartcol()-1<<endl; //write the coords into the file
    d.pathfinder(d.getstartrow(),d.getstartcol());
    
    if(d.getendcol()==-1 || d.getstartrow()==-1){ //if there is no path available then output is no solution
    	
		fstream obj;
		obj.open("outputA1P1.txt",ios::out|ios::trunc);
    	obj<<"No solution";
	}
	
}
