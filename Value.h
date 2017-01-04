#ifndef ASS1_VALUE_H
#define ASS1_VALUE_H
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
/**
 * Value class- this class represents a vector.
 */
class Value {
   friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }
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
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Value)
#endif //ASS1_VALUE_H