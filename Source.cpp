#include <iostream>
#include <string>
#include "MPQ.h"
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
	MPQ<int> MPQF; // MPQ First
	ifstream reader ("input.txt");
	string line="";
	getline(reader,line);
	int buildingNumber = atoi(line.c_str());
	int xCordL=0;
	int height=0;
	int xCordR=0;
	int counter = 1;
	while(getline(reader,line))
	{
		istringstream ss(line);
		ss >> xCordL;
		ss >> height ;
		ss >> xCordR ;
		MPQF.insert(xCordL,counter, LEFT,height);
		MPQF.insert(xCordR,counter, RIGHT,height);
		counter++;
	}
	MPQF.heapSort(MPQF.arrayElementGetter()); // To sort heap! ascending order.
	MPQ<int> MPQC;//MPQ Comparison
	vector<ComparableAndLabel<int>> vec = MPQF.arrayElementGetter();
	int maxHeight=0;
	for(int i = 1; i <= MPQF.currentSizeGetter();i++)
	{// height is value and height is value in this case.
		if(vec[i].LOR == LEFT) 
		{// In left we start to build new height then insert element!
			MPQC.insert(vec[i].height,vec[i].label,vec[i].LOR,vec[i].value); // We insert anyway. 
			if(maxHeight < MPQC.arrayElementGetter()[MPQC.currentSizeGetter()].value) // if current height is more then maxheight then change maxheight. Give print the console
			{
				cout << MPQC.arrayElementGetter()[1].height << "  " <<   MPQC.arrayElementGetter()[1].value<<endl;
				maxHeight = MPQC.arrayElementGetter()[1].value;
			}
		}
		else
		{// otherwise we just remove pair of that label and if maxheight is change then give cout and change maxheight to current one
			int index = vec[i].value;
			MPQC.Remove(vec[i].height,vec[i].label,vec[i].LOR,vec[i].value);
			if(maxHeight < MPQC.arrayElementGetter()[MPQC.currentSizeGetter()].value ) // if currentHeight is bigger then maxHeight!
			{ // height is value
				cout << MPQC.arrayElementGetter()[1].height << "  " <<   MPQC.arrayElementGetter()[1].value<<endl;
				maxHeight = MPQC.arrayElementGetter()[1].value; // value is height 
			}
			else if(maxHeight >= MPQC.arrayElementGetter()[MPQC.currentSizeGetter()].value) 
			{//otherwise current height is 0 then it will give cout about index will 
				if(MPQC.arrayElementGetter()[1].value != 0) 
				{ // Currentval < maxHeight! also height is not 0 Then we dont maxHeight.
					cout <<index << "  " <<   MPQC.arrayElementGetter()[MPQC.currentSizeGetter()].value<<endl;
				}
				else
				{ // if it is 0 then you have to update maxHeight as 0. No element left in MPQC.arrayElement!
					cout <<index << "  " << "0"<<endl;
					maxHeight=0;
				}
			}
		}
	}
	cin.get();
	cin.ignore();
	return 0;
}