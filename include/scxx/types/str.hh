/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Scxx Headerfile , Containing all the Scxx Types with it.
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/

// This files contains the alph data type of scxx


// #include "alph.hh"

#include <cstdarg>
#include <new>
class str {
    private:
        alph VALUE;
    public:
        str (const char*  __VALUE) : VALUE(__VALUE) {};
        char* value(const char* __VALUE = "\0"){
            char* rval = VALUE.value(__VALUE);
            return rval;
        }
        unsigned long long length = VALUE.length;
        

        
        void append (const char* __VALUE){
            VALUE.append(__VALUE);
        }



        char at(unsigned long long index){
            return VALUE.at(index);
        }



        unsigned long long size(){
            return VALUE.length - 1;
        }



        const unsigned long long UNIDEF = -1;
        unsigned long long find(const char* __VALUE, unsigned long long pos , unsigned long long skips){
            return VALUE.find(__VALUE, pos, skips);
        }


        bool &substr_out_of_bounds = VALUE.substr_out_of_bounds;
        char* substr (unsigned long long start=0, unsigned long long len=0){
            return VALUE.substr(start, len);
        }



        void concat (const char* what){
            VALUE.append(what);
        }



        char* replace (const char* what, const char* with, unsigned long long pos=0){
            char* rval = new char[2];
            unsigned long long finded = VALUE.find(what, pos);
            if (finded == UNIDEF){}
            else {
                alph a (VALUE.substr(finded + alph(what).length));
                alph b (VALUE.substr(0, finded));
                alph c (b.value());
                c.append(with);
                c.append(a.value());
                delete[] rval;
                rval = new char[c.length];
                for (unsigned long long i = 0;i < c.length;i++)
                    rval[i] = c.at(i);
                rval[c.length] = '\0';
            }
            return rval;
        }



        char* replaceAll (const char* what, const char* with){
            char* rval = new char[2];
            unsigned long long pos = 0;
            str a = VALUE.value();
            for (unsigned long long i = 0; VALUE.find(what, pos) != UNIDEF; i++){
                // delete [] rval;
                rval = a.replace(what, with, pos);
                a.value(rval);
                pos = VALUE.find(what, pos) + 1;
            }
            return rval;
        }
};