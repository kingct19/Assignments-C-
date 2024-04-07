
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class SparseVector
{
public:
    SparseVector(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string pair;
            while (std::getline(iss, pair, ','))
            {
                std::istringstream pairStream(pair);
                std::string indexStr, valueStr;
                std::getline(pairStream, indexStr, ':');
                std::getline(pairStream, valueStr);
                int index = std::stoi(indexStr);
                int value = std::stoi(valueStr);
                data[index] = value;
            }
        }
    }

    SparseVector multiply(const SparseVector &other) const
    {
        SparseVector result("");
        for (std::map<int, int>::const_iterator it = data.begin(); it != data.end(); ++it)
        {
            int index = it->first;
            int value = it->second;
            if (other.data.count(index))
            {
                result.data[index] = value * other.data.at(index);
            }
        }
        return result;
    }

    void print() const
    {
        for (std::map<int, int>::const_iterator it = data.begin(); it != data.end(); ++it)
        {
            std::cout << it->first << ":" << it->second << ", ";
        }
        std::cout << std::endl;
    }

private:
    std::map<int, int> data;
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <vector1.txt> <vector2.txt>\n";
        return 1;
    }

    SparseVector vec1(argv[1]);
    SparseVector vec2(argv[2]);

    std::cout << "Vector 1: ";
    vec1.print();

    std::cout << "Vector 2: ";
    vec2.print();

    SparseVector vec3 = vec1.multiply(vec2);

    std::cout << "Vector 3: ";
    vec3.print();

    return 0;
}