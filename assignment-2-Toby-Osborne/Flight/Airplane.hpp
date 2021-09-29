#ifndef AIRPLANE_HPP
#define AIRPLANE_HPP

class Airplane {
private:
    Airplane& operator=(const Airplane &other);
    Airplane(const Airplane &other);
    int Capacity;
public:
    Airplane(int capacity);
    int getCapacity() const;
};

#endif
