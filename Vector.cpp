#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;
class Vector
{
private:
    int size;
    int *arr = nullptr;
    int capacity;

public:
    Vector(int size):size(size)
    {
        if(size<=0)
        size=1;
        capacity=size*2;
        arr = new int[capacity]{};
    }

    ~Vector()
    {
      delete[] arr;
		  arr = nullptr;
    }

    int get(int idx) {
		assert(0 <= idx && idx < size);
		return arr[idx];
	}

	void set(int idx, int val) {
		assert(0 <= idx && idx < size);
		arr[idx] = val;
	}
  void print()
  {
      for (int i = 0; i < size; i++)
      {
          cout<<arr[i]<<" ";
      }
      cout<<"\n";
  }
  int find(int num)
  {
      for (int i = 0; i < size; i++)
      {
          if(arr[i]==num)
          {
            return i;
          }
      }
      return-1;
  }
  void push_back(int val)
  {
    if (size==capacity)
    {
      expand_capacity(val);
    }
    else
    arr[size++]=val;
  }
  void expand_capacity(int val)
  {
    capacity *= 2;
    int* temp= new int[capacity];
    for (int i = 0; i < size; i++)
    {
      temp[i]=arr[i];
    }
    temp[size++]=val;
    swap(arr,temp);
    delete[] temp;
  }
  void insert(int pos,int val)
  {
    if (size==capacity)
      expand_capacity(val);
    
    for (int i = size ; i >= pos; --i)    
    {
      arr[i]=arr[i-1];
    }
    arr[pos]=val;
    size++;
  }
  void right_rotate()
  {
    int temp=arr[size-1];
    for (int i = size-1; i >=0 ; --i)
    {
      arr[i]=arr[i-1];
    }
    arr[0]=temp;
  }
  void left_rotate()
  {
    int temp=arr[0];
    for (int i = 0; i < size ; ++i)
    {
      arr[i]=arr[i+1];
    }
    arr[size-1]=temp;
  }
  void right_rotate(int step)
  {
    int temp[step];
    for (int i = 0; i < step; i++)
    {
      temp[i]=arr[size-step+i];
    }
    for (int i = size-1; i >=step ; --i)
    {
      arr[i]=arr[i-step];
    }
    for (int i = 0; i < step; i++)
    {
      arr[i]=temp[i];
    }
  }
  int pop(int id)
  {
    int val=arr[id];
    for (int i = id; i < size-1 ; ++i)
    {
      arr[i]=arr[i+1];
    }
    size--;
    return val;
  }
  int find_transposition(int val)
  {
    int pos=find(val);
    if(pos>0)
    {
      int temp=arr[pos];
      arr[pos]=arr[pos-1];
      arr[pos-1]=temp; 
    }
    return pos-1;
  }
};


int main()
{ 
    Vector v1(10);
    for (int i = 0; i < 10; i++)
    {
        v1.set(i,i);
    }
    cout<<v1.find(5);
    cout<<v1.find(12)<<endl;
    v1.print();

    v1.push_back(50);
    v1.print();

    v1.insert(2,22);
    v1.print();

    v1.right_rotate(3);
    v1.print();

    v1.left_rotate();
    v1.print();

    cout<<v1.pop(4)<<endl;
    v1.print();

    cout<<v1.find_transposition(6)<<endl;
    v1.print();
  return 0;
}