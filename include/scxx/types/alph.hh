/*
 * Copyright (c) ghgltggamer 2025
 * Written by ghgltggamer
 * Scxx Headerfile , Containing all the Scxx Types with it.
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/

// This files contains the alph data type of scxx

unsigned long long alph_length(const char* __VALUE){
    unsigned long long return_value = 0;
    for (unsigned long long &i = return_value;__VALUE[i] != '\0';i++);
    return return_value;
}

char* alph_copy (const char* __VALUE){
    unsigned long long len = alph_length(__VALUE);
    char* new_copy = new char[len+1];
    for (unsigned long long i = 0;i < len;i++)
        new_copy[i] = __VALUE[i];
    new_copy[len] = '\0';
    return new_copy;
}

class alph {
    private:
        char* VALUE = new char('\0');
    public:
        alph (const char* __VALUE){
            delete[] VALUE;
            VALUE = alph_copy(__VALUE);
            length = alph_length(__VALUE);
        }

        unsigned long long length = 0;

        char* value (const char* __VALUE = "\0"){
            char* return_value = new char[1];
            return_value[0] = '\0';
            if (__VALUE[0] == '\0'){
                delete[] return_value;
                return_value = VALUE;
            }
            else {
                delete[] return_value;
                delete[] VALUE;
                VALUE = alph_copy (__VALUE);
                return_value = VALUE;
                length = alph_length(__VALUE);
            }
            return return_value;    
        }

        const unsigned long long UNIDEF = -1;
        unsigned long long find(const char* __VALUE, unsigned long long pos=0, unsigned long long skips=0){
            unsigned long long return_value = -1;
            unsigned long long current_skips = 0;
            unsigned long long len = alph_length(__VALUE);
            for (unsigned long long i = pos;i < length;i++){
                bool is_find = false;
                for (unsigned long long x = 0;x < len;x++){
                    if (VALUE[i+x] == __VALUE[x]){
                        is_find = true;
                        continue;
                    }
                    else {
                        is_find = false;
                        break;
                    }
                }
                if (is_find){
                    if (skips == current_skips)
                    {
                        return_value = i;
                        break;
                    }
                    else {
                        current_skips++;
                        continue;
                    }
                }
            }
            return return_value;
        }

        bool substr_out_of_bounds = false;
        char* substr(unsigned long long start=0, unsigned long long len=-1){
            if (start >= length){
                substr_out_of_bounds = true;
                start = length-1;
            }
            if (start + len > length) {
                len = length - start;
            }
            if (len == -1){
                len = length - start;
            }

            char* return_value = new char[len+1];
            
            unsigned long long return_value_index = 0;
            for (unsigned long long i = start;i < start+len;i++)
                return_value[return_value_index++] = VALUE[i];

            return_value[len] = '\0';
            return return_value;
        }

        void append (const char* what){
            unsigned long long len = alph_length(what);
            char* old_value = alph_copy(VALUE);
            delete[] VALUE;
            VALUE = new char[length+len+1];
            for (unsigned long long i = 0;i < length;i++){
                VALUE[i] = old_value[i];
            }
            unsigned long long what_index = 0;
            for (unsigned long long i = length;i < length + len;i++){
                VALUE[i] = what[what_index++];
            }
            VALUE[len+length] = '\0';
            length += len;
        }



        char at(unsigned long long index){
            char rval;
            if (index >= length)
                rval = UNIDEF-'0';
            else rval = VALUE[index];
            return rval;
        }



        ~alph (){
            delete[] VALUE;
        }
};