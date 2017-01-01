#ifndef ASS1_VALUE_H
#define ASS1_VALUE_H
/**
 * Value class- this class represents a vector.
 */
class Value {
public:
    /**
     * getiValue.
     * @param i the i-th parameter in the vector.
     * @return the value of the i-th parameter of the vector.
     */
    virtual int getiValue(int i)=0;
    /**
     * printValue.
     * print the parameters in the vector in the following format: (a,b,c,...,)
     */
    virtual void printValue()=0;
    bool operator==(const Value &other)const;
    bool operator!=(const Value &other)const;
};

#endif //ASS1_VALUE_H