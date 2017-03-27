#include "boost-pba/portable_binary_iarchive.hpp"
#include "boost-pba/portable_binary_oarchive.hpp"

#include <iostream>
#include <fstream>

struct Record
{
    Record() {}
    Record(int age, const std::string &name) : age(age), name(name) {}

    int age;
    std::string name;

    // Boost serialization:
    //friend class boost::serialization::access;
    template<class Archive>  void serialize(Archive & ar, const unsigned int version)
    {
        ar & age;
        ar & name;
    }
};

int main(int argc, char **argv) 
{
    std::string filename = "record.dat";

    Record recordA(1, "kermit");
    { // Dump the record:
        std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);
        if(ofs)
        {
            portable_binary_oarchive oa(ofs);
            oa << recordA;
        }
    }

    Record recordB;
    { // Load the record
        std::ifstream ifs(filename, std::ios_base::in | std::ios_base::binary);
        if(ifs)
        {
            portable_binary_iarchive ia(ifs);
            ia >> recordB;
        }
    }

    assert(recordA.age == recordB.age);
    assert(recordA.name == recordB.name);
}
