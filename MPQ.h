#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum LeftOrRight {LEFT,RIGHT};

template <class Comparable> 
struct ComparableAndLabel
{// Which will use in vector.
	int label; //id
	Comparable value; // coordinate
	LeftOrRight LOR;
	int height; 
};

template <class Comparable>
class MPQ // MAX HEAP ! 
{
public:
	MPQ();
	~MPQ();
	void insert( const Comparable & x, int label ,LeftOrRight lor, int height);
	void Remove(const Comparable & x, int label ,LeftOrRight lor, int height);
	//Comparable GetMax( );
	bool IsEmpty( );
	void heapSort(vector<ComparableAndLabel<Comparable>> &a) ;
	int currentSizeGetter();
	vector<ComparableAndLabel<Comparable>> & arrayElementGetter();

private:
	int currentSize; // Number of elements in heapComparableAndLabel
	vector<ComparableAndLabel<Comparable>> arrayElement;       // The heap arrayElement
	void percDown( vector<ComparableAndLabel<Comparable>> &a, int i, int n );
};

template <class Comparable>
MPQ<Comparable>::MPQ() // first push input 0 
{
	ComparableAndLabel<Comparable> cl;
	cl.label = 0;
	cl.value = 0;
	arrayElement.push_back(cl);
	currentSize = 0; // Because first arrayElement is dumb.
}

template <class Comparable>
vector<ComparableAndLabel<Comparable>> & MPQ<Comparable>::arrayElementGetter() 
{// to reach private value
	return arrayElement;
}

template <class Comparable>
MPQ<Comparable>::~MPQ() 
{ // basic destructor.
	arrayElement.clear();
}

template <class Comparable>
int MPQ<Comparable>::currentSizeGetter()
{ // taking currentSize which is private
	return currentSize;
}

template <class Comparable>
// In MPQC vector height will be the x cordinates and x will be height
void MPQ<Comparable>::insert( const Comparable & x , int label ,LeftOrRight lor, int height)
{
	ComparableAndLabel<Comparable> cl; // takin all element as for struct vector
	cl.value = x;
	cl.label = label;
	cl.height = height;
	cl.LOR = lor;
	if(currentSize == arrayElement.size()-1)
	{// resize when it is in last element
		arrayElement.resize(arrayElement.size()*2); 
	}
	// Percolate up
	// Note that instead of swapping we move the hole up
	int hole = ++currentSize;
	for( ; hole > 1 && x > arrayElement[ hole / 2 ].value; hole /= 2 )
	{ // its max heap then we need to carry up max one's.
		arrayElement[ hole ] = arrayElement[ hole / 2 ];
	}
	arrayElement[ hole ]= cl;
}

template <class Comparable>
void MPQ<Comparable>::Remove(const Comparable & x, int label ,LeftOrRight lor, int height) 
{
	int i;
	//For find the best case is O(N)
	if(IsEmpty())
		return ;
	for(i = 1;i<=currentSize;i++)
	{
		if(arrayElement[i].label == label && arrayElement[i].value == x && arrayElement[i].LOR !=lor)
			break;
	}
	arrayElement[i] = arrayElement[currentSize]; // change place with deleted one and last element of vector
	arrayElement[currentSize].value = 0;
	arrayElement[currentSize].height = 0; 
	arrayElement[currentSize].label = 0; 
	arrayElement[currentSize].LOR = LEFT; 
	currentSize--; // then decrease 1 currentSize Bcs we delete element
	ComparableAndLabel<Comparable> cl;
	cl = arrayElement[i];
	//We need to keep as max heap ! 
	if(arrayElement[i].value > arrayElement[i/2].value )  
	{ // upside is bigger then percolate up!!
		for( ; i > 1 && x > arrayElement[ i / 2 ].value; i /= 2 )
		{
			arrayElement[ i ] = arrayElement[ i / 2 ];
		}
		arrayElement[i] = cl;
	}
	else if(arrayElement[i].value < arrayElement[i/2].value) 
	{//Otherwise then percolate down! 
		percDown(arrayElement,i,currentSize);
	}
}

template <class Comparable>
bool MPQ<Comparable>::IsEmpty()
{// checking is it empty or not
	return (currentSize == 0);
}

template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void MPQ<Comparable>::percDown(vector<ComparableAndLabel<Comparable>> &a, int i, int n )
{ // It works with HeapSort! It is kind of organize as max heap after the swapping.
	int child;
	ComparableAndLabel<Comparable> tmp;
	//tmp = arrayElement[ i ].value; // tmp is the item that will 
	for(tmp=a[i] ; (i*2) <= n; i  = child )
	{
		child = i*2;
		if( child != n && a[ child  ].value < a[ child+1 ].value )
			child++;
		if( a[child ].value > tmp.value )
		{
			a[i] = a[ child ];
		}
		else
			break;
	} 
	a[ i ] = tmp;
}

template <class Comparable>
void MPQ<Comparable>::heapSort(vector<ComparableAndLabel<Comparable>> &a)
{ // this is basic sort algorithm.
	// sort
	for(int j = currentSize; j >0; j--)
	{ // first swap then prectDown. 
		swap(a[1], a[j]);  // swap max to the last pos.
		percDown(a,1,j-1); // re-form the heap
	}

}
