// #include "include/casci/casci.hh"
// #include "include/cascrypt/cascrypt.hh"
// #include "include/mfsff/mfsff.hh"
// #include "include/mfsff/mfsff.hh"
#include "include/mfsff/mfsff.hh"
#include <mfsff/mfsff.hh>
#include <iostream>
#include <string>
#include <fstream>

int main (){

    // CASCI file_c ("Hello.txt's content is here!");
    // CASCI file_cn ("Hello.txt");
    // mfsff::file file; 
    // std::string xz = "";
    // xz += FILE_START;
    // xz += cascrypt::encode(file_cn.encrypt("1"));
    // xz += FILE_NEND;
    // xz += cascrypt::encode(file_c.encrypt("1"));
    // xz += FILE_END;

    // file.raw.value(

    //     xz.c_str()

    // );

    // int status = mfsff::mount(&file);
    // // std::cout << file.is_mounted <<"\n";
    // // std::cout << file.file_name.size() <<"\n";
    // // std::cout << file.file_content.size() <<"\n";
    // // std::cout << xz <<"\n";
    // // std::cout << status <<"\n";
    // std::cout << "\n\n\n\n-------MFSFF--------\n\n\n\n" <<xz<<std::endl;
    // if (status == 1){
    //     std::cout << file.file_content.size()<<"\n";
    //     std::cout << file.file_name.size()<<"\n";
    //     std::cout << file.file_content[0]<<"\n";
    //     std::cout << file.file_name[0]<<"\n";
    // }

    // mfsff::file fs;
    // fs.file_content.push_back("Hello world 2025!");
    // fs.file_name.push_back("Hello.txt");

    // int mount = mfsff::mount(&fs);
    // if (mount == 1){
    //     std::cout << mfsff::write(&fs) <<'\n';
    //     std::ofstream ofile ("test.mfsff");
    //     ofile<<mfsff::writen.value();
    // }
    // else {
    //     std::cout << mount <<"\n";
    // }

    std::string file =  R"((¨ÅÌÌÏlÔØÔ

)¨ÅÌÌÏX×ÏÒÌÄXpnpsY

+)";

    mfsff::file fs;
    fs.raw.value (file.c_str());
    int loded = mfsff::mount(&fs);
    if (loded == 1){
        for (unsigned long long i = 0;i < fs.file_name.size();i++){
            std::cout << "File: " << fs.file_name[i] <<'\n';
            std::cout << "Content: " << fs.file_content[i] <<'\n';
        }
    }
    mfsff::umount(&fs);
    loded = mfsff::mount(&fs);
    std::cout << loded <<'\n';
    if (loded == 1){
        for (unsigned long long i = 0;i < fs.file_name.size();i++){
            std::cout << "File: " << fs.file_name[i] <<'\n';
            std::cout << "Content: " << fs.file_content[i] <<'\n';
        }
    }
}