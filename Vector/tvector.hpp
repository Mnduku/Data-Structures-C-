template<class T>
TVector<T>::TVector(){
   size = 0;
   capacity = SPARECAPACITY + 200;
   array = new T[capacity];                     //default cosnt
}

template<class T>
TVector< T >::TVector(T val, int num){
   size = num;
   capacity = num + SPARECAPACITY;
   array = new T[size];
   for(int i = 0; i < num; i++){                 //2 param const
      array[i] = val;
   }
}

template<class T>
TVector<T>::~TVector(){
   if(array == nullptr) return;                     //delete
   else delete [] array;
   return;
}

template<class T>
TVector<T>::TVector(const TVector<T>& v){
   array = new T(v.capacity);
   for(int i = 0; i < v.size; i ++){                   //copy const
      array[i] = v[i];
   }
   capacity = v.capacity;
   size = v.size;
   return;
}

template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v){
   if(this != &v){
      delete [] array;
      array = new T(v.capacity);
      for(int i = 0; i < v.size; i ++){           //copy assgt
         array[i] = v[i];
      }
      capacity = v.capacity;
      size = v.size;
   }
   return *this;
}

template<typename T>
TVector<T>::TVector(TVector<T> && v){                 //move const
   capacity = v.capacity;
   array = v.array;
   size = v.size;
   v.array = nullptr;
   return;
}
template<typename T>
TVector<T>& TVector<T>::operator=(TVector<T> && v){    //move assgt
   std::swap(capacity, v.capacity);
   std::swap(array, v.array);
   std::swap(size, v.size);
   return *this;
}

template<typename T>
bool TVector<T>::IsEmpty() const{
   return(size <= 0);
}

template<typename T>
int TVector<T>::GetSize() const{
   return size;
}

template<typename T>
T& TVector<T>::GetFirst() const{
    return array[0];
}

template<typename T>
T& TVector<T>::GetLast() const{
    return array[size-1];
}

template< class T >
void TVector<T>::Print(std::ostream& os, char delim) const             // print vector contents
{
    unsigned int i = 0;
    while(i < GetSize())
    {
        os << array[i];
        os << delim;
        i++;
    }
    return;
}



///////////////////MIGHT NEED TWEAKING 

template<typename T>
void TVector<T>::SetCapacity(unsigned int c){
   if(size > c) size = c;

   T* temp = new T[c];
   for(int i = 0; i < size; i++){                     //creates new array with desired capacity ( deep copy)
      temp[i] = array[i];
   }
   array = temp;
   delete [] temp;
}


template<typename T>
void TVector<T>::InsertBack(const T& d){
    if(size == capacity){
      SetCapacity(size + 10);
   //   std::cout<< "SETCAPACITY HAS BEEN CALLED";      //inserts to last spot, if full setcapacity is called
    }
    array[size] = d;
    size++;
}


template<typename T>
void TVector<T>::RemoveBack(){
   if(IsEmpty()) return;  size--;          //NOTE
}

template<typename T>
TVectorIterator<T> TVector<T>::Insert(TVectorIterator<T> pos, const T& d){

//    std::cout << "tHIS FUNCTION IS called and inserts" << d << std::endl;
    if(size == capacity){
       SetCapacity(capacity + 2);
    }

  //  std::cout << "size check " << size << std::endl ;
    int i = size;

    for(i = size; i != pos.index; i--){
       array[i] = array[i-1];
  //     std::cout << "index check " << i << std::endl ;
    }

    array[i] = d;

    size++;                                           //Copies the entire array into a new one with a

    pos.index = i; //or i                             //offset of one so that there is space for the new item
    pos.ptr = array;
    pos.vsize = size;

    return pos;

}

template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos){
   for(int i = pos.index ; i < size - 1 ; i++) {
        array[i] = array[i+1];
   }
   size = size - 1;
   pos.ptr = array + pos.index;
   pos.vsize = size;
   return pos;

}

template<typename T>
TVectorIterator<T> TVector<T>::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2){
    if(IsEmpty()) return pos1;
    if(pos1.index == pos2.index || pos1.index - pos2.index == -1 ||   //error checking for remove
    pos1.index - pos2.index == 1) return pos1;

    int removecount;
    if(pos1.index > pos2.index){
       removecount = pos1.index - pos2.index;
    }
    if(pos1.index < pos2.index){                                    //use the index to see how many items are removed
       removecount = pos2.index - pos1.index;
    }

    int i = 0;

    for(int i = 0; i <= pos1.index; i++){
        array [i] = array [i];
    }

    i++;                                                           //copies array to itself stopping at pos 1,
                                                                   //and contintuing at the end of pos2

 //   std::cout << "rc test : " << removecount << std::endl;
    for(int j = pos2.index; j < (size); j++){
        array [i+1] = array [j];
//        std::cout << " j " << j << ": " << array [j] << std::endl;
        i++;
    }

    size = size - removecount;
    TVectorIterator<T> neww;
    neww.index = i - 1;
    neww.vsize = size;
    neww.ptr = array + size;
    return neww;
}


////////////////////////ITERATOR FUNCTIONS

template<typename T>
TVectorIterator<T> TVector<T>::GetIterator() const{
    TVectorIterator<T> newit;
    newit.ptr = array;                                               //gets an iterator for a vector at the beginning
    newit.index = 0;
    newit.vsize = size;
    return newit;
}

template<typename T>
TVectorIterator<T> TVector<T>::GetIteratorEnd() const{
    TVectorIterator<T> newit;
    newit.index = size;
    newit.ptr = array + size - 1;                                   //returns an iterator to end of vector
    newit.vsize = size;
    return newit;
}

/////////////////////////ITERATOR FUNCTIONS
template<typename T>
TVectorIterator<T>::TVectorIterator(){
   index = 0;
   ptr = nullptr;
   vsize = 0;
}

template<typename T>
bool TVectorIterator<T>::HasNext() const{
   return index < vsize - 1;
}

template<typename T>
bool TVectorIterator<T>::HasPrevious() const{
   return index > 0;
}

template<typename T>
TVectorIterator<T> TVectorIterator<T>::Next(){
   if(index < vsize){
      index = index + 1;
      *ptr++;                                             //increments iterators index and pointer
   }
//   std::cout << index << std::endl;
   return *this;
}
template<typename T>
TVectorIterator<T> TVectorIterator<T>::Previous(){
   if(index > 0){
      index--;                                            //decrements iterators index and pointer
      *ptr--;
   }
   return *this;
}
template<typename T>
T& TVectorIterator<T>::GetData() const{
    if(index < 0 || index > vsize){
       return TVector<T>::dummy;
    }
    return *ptr;
}



template<typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){
    TVectorIterator<T> v1 = t1.GetIteratorEnd();
    TVectorIterator<T> v2 = t2.GetIteratorEnd();
    TVector<T> t3;
    TVectorIterator<T> v3 = t3.GetIterator();
    int i = 0;
    int j = 0;

    while(v2.HasPrevious()){
       t3.Insert(v3, v2.GetData());
       v2.Previous();
       v3.Next();                                   //creates an iterator for each vector and iterates through them
                                                    //backwards adding each element to a combined array
       i++;
    }

    while(v1.HasPrevious()){
       t3.Insert(v3, v1.GetData());
       v1.Previous();
       v3.Next();
       j++;
    }
    return t3;
}








