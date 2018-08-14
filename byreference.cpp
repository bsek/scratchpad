#include <iostream>
#include <cstring>

using namespace std;

template<class T>
void swapRef(T &obj1, T &obj2) {
    T temp = obj1;
    obj1 = obj2;
    obj2 = temp;
}

template<class T>
void swapVal(T obj1, T obj2) // copy constructor x 2
{
    cout << "3: " << obj1 << "   " << obj2 << endl;
    cout << "5: " << &obj1 << " " << &obj2 << endl;
    T temp = obj1; // copy constructor
    obj1 = obj2;   //
    obj2 = temp;
    cout << "4: " << &obj1 << "   " << &obj2 << " " << temp << endl;
}

static int run = 0;

class Bogo {
public:
    // default constructor
    Bogo(int i = 0, const char *s = "") {
        cout << "Default constructor" << endl;
        myInt = i;
        int len = strlen(s);
        myString = new char[len + 1];
        strcpy(myString, s);
    }

    // copy constructor overloading
    Bogo(const Bogo &b) {
        cout << "Copy constructor:" << this << " with " << &b << endl;
        int len = strlen(b.myString);
        myString = new char[len + 1];
        strcpy(myString, b.myString);
        myInt = run++;
    }

    // move constructor overloading
    Bogo(Bogo &&b) : myInt(std::move(b.myInt)), myString(std::move(b.myString)) {
        cout << "Move constructor:" << this << " with " << &b << endl;

    }

    // move assignment operator overloading
    Bogo &operator=(Bogo &&b) {
        cout << "Move assignment" << this << " with " << &b << endl;

        myString = std::move(b.myString);
        myInt = std::move(b.myInt);

        return *this;
    }

    // copy assignment operator overloading
    Bogo &operator=(const Bogo &b) {
        cout << "Copy assignment" << this << " with " << &b << endl;
        int len = strlen(b.myString);
        myString = new char[len + 1];
        strcpy(myString, b.myString);
        myInt = b.myInt;
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Bogo &b);

private:
    int myInt;
    char *myString;
};

ostream &operator<<(ostream &os, const Bogo &b) {
    os << b.myInt << "," << b.myString;
    return os;
}

Bogo createATemporaryBogo(Bogo b) {
    return b;
}

int main() {
    Bogo bogoA = Bogo(100, "AAA"); // default
    Bogo bogoB = Bogo(200, "BBB"); // default
    cout << "Value:" << endl;
    cout << "1: " << bogoA << "   " << bogoB << endl;
    swapVal<Bogo>(bogoA, bogoB);
    cout << "2: " << bogoA << "   " << bogoB << endl;

    cout << endl;

    Bogo bogoC = Bogo(createATemporaryBogo(Bogo()));
    Bogo bogoD;
    bogoD = std::move(bogoB);
    cout << "3: " << bogoC << "   " << bogoD << "   " << bogoB << endl;

    cout << "Finish" << endl;
    /*
    bogoA = Bogo(100, "AAA");
    bogoB = Bogo(200, "BBB");
    cout << "Reference:" << endl;
    cout << "1: " << bogoA << "   " << bogoB << endl;
    swapRef<Bogo>(bogoA, bogoB);
    cout << "2: " << bogoA << "   " << bogoB << endl;
  */
    return 0;
}

/*

Copy constructor
Copy constructor
Copy constructor
Copy constructor
Copy assignment
Copy constructor
Copy constructor
Copy assignment
Copy constructor
2: 100,AAA   200,BBB


Copy constructor
Copy constructor
Copy constructor
Copy assignment
Copy constructor
Copy assignment
Copy constructor
2: 100,AAA   200,BBB
 */