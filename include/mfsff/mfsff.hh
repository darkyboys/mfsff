/*
 * Copryright (c) ghgltggamer 2025
 * MFSFF - Magma File System For Files
 * Written by ghgltggamer
 * Licensed under the MIT License
 * Checkout the README.md for more information
*/


#ifndef MFSFF
#define MFSFF 1

// headers
#include "../scxx/scxx.hh"
#include "../casci/casci.hh"
#include "../cascrypt/cascrypt.hh"
#include <vector>
#include <iostream>

const char FILE_START = '(';
const char FILE_END = '+';
const char FILE_NEND = ')';


namespace mfsff {

    class file {
        public: 
            bool is_mounted = false;
            alph raw = "";
            std::vector<std::string> file_name = {};
            std::vector<std::string> file_content = {};
    };


    int mount(mfsff::file* file_in){
        int code = 0;
        if (file_in->is_mounted) code = 2;
        else {
            unsigned long long len = file_in->raw.length;
            bool is_file_started = false,
                 can_read_content = false;
            alph cfile_name = "", cfile_content = "";

            for (unsigned long long i = 0;i < len;i++){
                // std::cout << (file_in->raw.at(i)) <<"\n";
                if (file_in->raw.at(i) == FILE_START){
                    is_file_started = true;
                    continue;
                }

                if (file_in->raw.at(i) == FILE_NEND){
                    if (is_file_started){
                        can_read_content = true;
                        continue;
                    }
                    else {
                        code = -1;
                        break;
                    }
                }

                if (file_in->raw.at(i) == FILE_END){
                    if (is_file_started and can_read_content){
                        is_file_started = false;
                        can_read_content = false;


                        std::string file_name_str = cascrypt::decode(cfile_name.value());
                        CASCI casci_file_name_out (file_name_str);
                        std::string val = casci_file_name_out.decrypt("1");
                        file_in->file_name.push_back(val.substr(0, val.find("\n")));


                        std::string file_content_str = cascrypt::decode(cfile_content.value());
                        CASCI casci_file_content_out (file_content_str);
                        file_in->file_content.push_back(casci_file_content_out.decrypt("1"));
                        // std::cout << "Files were assigned!\n"
                        //           <<"file-name: "<<file_in->file_name[0] <<"\n"
                        //           <<"file-content: "<< file_in->file_content[0] <<"\n";
                        continue;
                    }
                    else {
                        code = -1;
                        break;
                    }
                }


                if (is_file_started and can_read_content){
                    char character[2] = {'0', '\0'};
                    character[0] = file_in->raw.at(i);
                    // std::cout << "Chars: "<< character <<"\n";
                    cfile_content.append(character);
                }

                else if (is_file_started and not can_read_content){
                    char character[2] = {'0', '\0'};
                    character[0] = file_in->raw.at(i);
                    // std::cout << "Chars: "<< character <<"\n";

                    cfile_name.append(character);
                }
            }
            file_in->is_mounted = true;
            code = 1;
        }
        return code;
    }



    alph writen = "";
    int write (mfsff::file* file){
        int code = 0;
        if (not file->is_mounted){
            code = -1; 
        }
        else {
            if (file->file_content.size() != file->file_name.size()){
                code = -2; // unparallel error
            }
            else {    
                for (unsigned long long i = 0;i < file->file_name.size();i++){
                    // std::cout << "written: "<<writen.value()<<'\n';
                    writen.append(
                        std::string(FILE_START + cascrypt::encode(
                            CASCI(file->file_name[i]).encrypt("1")
                        ) + FILE_NEND).c_str()
                    );  
                    writen.append(
                        std::string(cascrypt::encode(
                            CASCI(file->file_content[i]).encrypt("1")
                        ) + FILE_END).c_str()
                    );  
                }
                code = 1;
            }
        }
        return code;
    }


    int umount (mfsff::file* file){
        int code = 0;
        if (file->is_mounted) {
            file->file_content.clear();
            file->file_name.clear();
            file->raw.value("");
            file->is_mounted = false;
            code = 1;
        }
        return code;
    }
}


#endif