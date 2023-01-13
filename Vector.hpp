#ifndef vector
#define vector

#include <iostream>
#include <string>

template <typename T>
class Vector {
private:
    T* m_elements;
    int m_nrOfElements;
    int m_capacity;
public:
    Vector();
    ~Vector();
    Vector(const Vector<T>& other);
    Vector(Vector<T>&& other);
    Vector<T>& operator=(const Vector<T>& other);
    Vector<T>& operator=(Vector<T>&& other);
    int size() const;
    int capacity() const;
    bool empty() const;
    T& operator[] (int index) const;
    T& at(int index) const;
    T& front() const;
    T& back() const;
    const T* data() const;
    void clear();
    void insert(int index, const T& element);
    void erase(int index);
    void push_back(const T& element);
    void pop_back();

};

template <typename T>
Vector<T>::Vector() { //jonstruktor
    m_nrOfElements = 0;
    m_capacity = 10;
    m_elements = new T[m_capacity];
}

template <typename T>
Vector<T>::~Vector() { //destruktor
    delete[] this->m_elements;
    this->m_nrOfElements = 0;
    this->m_capacity = 0;
    this->m_elements = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) { //kopykonstruktor
    this->m_capacity = other.m_capacity;
    this->m_nrOfElements = other.m_nrOfElements;
    this->m_elements = new T[other.m_capacity];

    for (size_t i = 0; i < m_nrOfElements; i++) {
        this->m_elements[i] = other.m_elements[i];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) { //kopy
    if (this != &other) {
        delete[] this->m_elements;
        this->m_capacity = other.m_capacity;
        this->m_nrOfElements = other.m_nrOfElements;
        this->m_elements = new T[other.m_capacity];

        for (size_t i = 0; i < this->m_nrOfElements; i++) {
            this->m_elements[i] = other.m_elements[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) { //Konstruktor som tar över ansvar
    this->m_nrOfElements = other.m_nrOfElements;
    this->m_elements = other.m_elements;
    this->m_capacity = other.m_capacity;
    other.m_nrOfElements = 0;
    other.m_capacity = 0;
    other.m_elements = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) { //Vektorn finns redan men tar över ansvar
    if (this == &other) {
        return *this;
    }

    delete[] this->m_elements;

    this->m_nrOfElements = other.m_nrOfElements;
    this->m_capacity = other.m_capacity;
    this->m_elements = other.m_elements;
    other.m_elements = nullptr;
    other.m_nrOfElements = 0;
    other.m_capacity = 0;

    return *this;
}

template <typename T>
T& Vector<T>::at(int index) const { //Returnerar vad som finns på index
    if (index >= this->m_nrOfElements || index < 0) {
        throw std::string("The vector is empty");
    }

    return this->m_elements[index];
}

template <typename T>
T& Vector<T>::operator[](int index) const { //Returnerar vad som finns på index
    if (index >= this->m_nrOfElements || index < 0) {
        throw std::string("The vector is empty");
    }
    return m_elements[index];
}

template <typename T>
T& Vector<T>::front() const { //Returnerar vad som finns på första elementet
    if (this->m_nrOfElements == 0) {
        throw std::string("The vector is empty");
    }
    return this->m_elements[0];
}

template <typename T>
T& Vector<T>::back() const { //Returnerar vad som finns på sista elementet
    if (m_nrOfElements == 0) {
        throw std::string("The vector is empty");
    }
    return this->m_elements[m_nrOfElements - 1];
}

template <typename T>
const T* Vector<T>::data() const { //Returnerar en pekare till arrayen
    return this->m_elements;
}

template <typename T> //Returnerar antalet objekt som är i arrayen
int Vector<T>::size() const {
    return this->m_nrOfElements;
}

template <typename T>
int Vector<T>::capacity() const { //Returnerar kapaciteten
    return this->m_capacity;
}

template <typename T>
bool Vector<T>::empty() const { //Kollar om vektorn är tom
    if (this->m_nrOfElements == 0) {
        return true;
    }
    return false;
}

template <typename T>
void Vector<T>::clear() { //Tömmer vektorn
    this->m_nrOfElements = 0;
}

template <typename T>
void Vector<T>::insert(int index, const T& element) { //Lägger in element på ett visst index.
    if (index > this->m_nrOfElements || index < 0) {
        return;
    }
    if (this->m_nrOfElements == 0) { //På noll är de bara att lägga in
        this->m_nrOfElements++;
        this->m_elements[index] = element;
    }
    else {
        if (this->m_nrOfElements == this->m_capacity) { //Expandera arrayen
            this->m_capacity = this->m_capacity * 2 + 10;

            T* tempvect = new T[this->m_capacity];
            for (int i = 0; i < this->m_nrOfElements; i++) {
                tempvect[i] = this->m_elements[i];
            }

            delete[] this->m_elements;
            this->m_elements = tempvect;
        }
        for (int i = this->m_nrOfElements - 1; i >= index; --i) { //Allt som ligger efter indexet ska flyttas fram innan vi kan lägga in det så vi inte överskrivet något
            this->m_elements[i + 1] = this->m_elements[i];
            if (i == 0) { //Om vi kommer till 0, break (hittade inget snyggare sätt)
                break;
            }
        }
        this->m_nrOfElements++;
        this->m_elements[index] = element;
    }
}
template <typename T>
void Vector<T>::erase(int index) { // Ta bort ett objekt på index
    if (index >= this->m_nrOfElements || index < 0) {
        return;
    }
    else {
        for (int i = index; i < this->m_nrOfElements - 1; ++i) { //Vi tar bort det genom att gå från indexet och lägga allt som är +1 ner till det under.
            this->m_elements[i] = this->m_elements[i + 1];
        }
        this->m_nrOfElements--;
    }
}
template <typename T>
void Vector<T>::push_back(const T& element) { //Placerar ett objekt längst bak i vektorn
    
    if (this->m_nrOfElements == this->m_capacity) {

       this->m_capacity = this->m_capacity*2 + 10; //expandering


        T* tempvect = new T[this->m_capacity];
        for (int i = 0; i < this->m_nrOfElements; i++) {
            tempvect[i] = this->m_elements[i];
        }
        delete[] this->m_elements;
        this->m_elements = tempvect;
    } 
   
    this->m_elements[this->m_nrOfElements] = element; //Lägger det längst bak
    this->m_nrOfElements++;
    
}

template <typename T>
void Vector<T>::pop_back() {
    if (this->m_nrOfElements > 0) {
        this->m_nrOfElements--;
    }
    else {
        return;
    }
}

#endif

