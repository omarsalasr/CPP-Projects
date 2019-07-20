#include <iostream>
//template class so that we can simulate a vector class
//Makes the class an integer or a char for reusability
template <typename T>//interchangable types
class dArr {
  private:
    T* arr;//array of type T
    int size;//array size
    int inUse;//array usage numer

  public:
    dArr(){//constructor that initializes the array
      size = 2;
      inUse = 0;
      arr = new T[size];//allocates memory for a new array
    }

    bool isEmpty(){//function that checks if the array is empty
      return inUse == 0 ? true: false;
    }

    void push(T data){//push an item to the stack
      //grow the array if it's full
      if(inUse == size)
        incArr();
      arr[inUse] = data;//push to the end of the array
      inUse += 1;
    }

    void incArr(){//helper function that increases the array when it's full
      T* temp = new T[size+2];//allocates memory for a temp array
      int i;
      for(i = 0; i < size; i++)//copies the data over
        temp[i] = arr[i];
      delete arr;//delets old array
      arr = temp;//sets new array equal to instance field
      size+=2;
    }

    T top(){//get the top of the stack
      return isEmpty() ? 0: arr[inUse -1];
    }

    void pop(){//pops the item at the top of the stack
      if(!isEmpty())
        inUse--;
    }

    void reset(){//clears the stack
      delete arr;//deallocates memory
      size = 2;
      inUse = 0;
      arr = new T[size];//allocates a new array
    }

};