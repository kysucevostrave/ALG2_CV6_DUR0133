#include <string>
#include <fstream>
#include <vector>
#include <utility> 
#include <stdexcept>
#include <sstream> 
#include <iostream>

class MyClass {     
public:             
    double open = 0;
    double close = 0;
    double high = 0;
    double low = 0;
public: MyClass() {};
};


int main() {

    std::vector<MyClass*> vec;

    std::ifstream myFile("BTC.csv");

    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    std::string line;
    double val;
    

    while (std::getline(myFile, line))
    {
        
        std::stringstream ss(line);
        
        std::vector<double> v1;
        
        while (ss >> val) {
            v1.push_back(val);
            if (ss.peek() == ',') ss.ignore();
        }
        MyClass *tmp = new MyClass();
        if (v1.size() > 0)
        {
            tmp->open = v1.at(0);
            tmp->high = v1.at(1);
            tmp->low = v1.at(2);
            tmp->close = v1.at(3);
        }

        vec.push_back(tmp);
        
    }
    myFile.close();
   

    int weeks_count = vec.size() / 7;

    for (size_t i = 0; i < weeks_count; i++)
    {
        std::cout << "Open " << vec.at(i * 7)->open << std::endl;


        double max = 0;
        double min = 100000000000000; //toto nastavte v prvom ifku na prvu hodnotu,nech tam neni taketo jeble cislo lebo vam na to pride

        for (size_t j = 0; j < 7; j++)
        {
            if (vec.at(i*7 + j)->low < min)
            {
                min = vec.at(i * 7 + j)->low;
            }
            if (vec.at(i * 7 + j)->high > max)
            {
                max = vec.at(i * 7 + j)->high;
            }
        }

        std::cout << "Min hodnota tyzdna  " << min << std::endl;
        std::cout << "Max hodnota tyzdna  " << max << std::endl;
        
        std::cout << "Close " << vec.at(i * 7 +6)->close << std::endl << std::endl ;

    }

    return 0;
}
