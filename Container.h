
#ifndef CONTAINER_H
#define CONTAINER_H

#include <iostream>
#include "Errors.h"
#include <cstring>

template<typename T>
class Container {
    size_t tab_size{0};
    T *tab{};
    size_t num_of_elements{0};

public:
    explicit Container(size_t size = 0);

    ~Container();

    void add(const T);

    T remove();

    void resize(size_t new_size);


    inline size_t size() const;


    T &operator[](int index) const {
        if (num_of_elements < 1)throw ContainerError("Empty container");
        if (index < 0) {

            if (index < -num_of_elements) {
                throw ContainerError("Index out of range");
            }
            return tab[num_of_elements + index];
        }

       if (index >= num_of_elements) {
            throw ContainerError("Index out of range");
        }
        return tab[index];
    }


    friend std::ostream &operator<<(std::ostream &s, const Container &C) {
        for (int i = 0; i < C.num_of_elements; i++) {
            s << C.tab[i] << " ";
        }
        return s;
    }

    T del(size_t id);

};

template<typename T>
Container<T>::Container(size_t size) :tab_size{size} {
    try {
        tab = new T[size]{};
    }
    catch (std::bad_alloc &) {
        tab_size = 0;
        throw ContainerError("Memory allocation failure");

    }
}


template<typename T>
Container<T>::~Container() {
    delete[] tab;
}


template<typename T>
void Container<T>::add(const T to_add) {

    if (tab_size == num_of_elements) {
        try {
            resize((num_of_elements + 1) * 2);
        }
        catch (ContainerError &e) {

            std::cout << e.what() << std::endl;
            throw ContainerError("Element can't be added");
        };
    }
    tab[num_of_elements++] = to_add;


}

template<typename T>
T Container<T>::remove() {
    if (num_of_elements > 1) {
        T temp = tab[num_of_elements - 1];
        if (tab_size > 2 * num_of_elements)resize(num_of_elements * 2 + 1);
        tab[num_of_elements] = T();
        return temp;
    } else throw ContainerError("Element can't be removed");

}

template<typename T>
void Container<T>::resize(size_t new_size) {
    if (new_size != tab_size) {

        T *temp{nullptr};
        try {
            temp = new T[new_size]{};
        } catch (std::bad_alloc &) {
            throw ContainerError(" resize(): memory allocation failure");
        }

        std::memcpy(temp, tab, num_of_elements * sizeof(T));
        delete[] tab;
        tab_size = new_size;
        tab = temp;
    }

}


template<typename T>
size_t Container<T>::size() const {
    return num_of_elements;
}

template<typename T>
T Container<T>::del(size_t id) {
    if (id >= num_of_elements)throw ContainerError("Index out of range, element can't be deleted");
    T del_t = tab[id];

    tab[id] = T{};
    for (int i = id; i < num_of_elements - 1; i++) {

        tab[i] = tab[i + 1];

    }
    num_of_elements--;
    if (2 * num_of_elements < tab_size)resize(2 * num_of_elements + 1);
    return del_t;

}


#endif
