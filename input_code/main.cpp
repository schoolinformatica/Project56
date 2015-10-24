#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class CSVRow {
public:
    std::string const &operator[](std::size_t index) const {
        return m_data[index];
    }

    std::size_t size() const {
        return m_data.size();
    }

    void readNextRow(std::istream &str) {
        std::string line;
        std::getline(str, line);

        std::stringstream lineStream(line);
        std::string cell;

        m_data.clear();
        while (std::getline(lineStream, cell, ',')) {
            m_data.push_back(cell);
        }
    }

private:
    std::vector<string> m_data;
};

istream & operator >>(std::istream & str, CSVRow& data){
    data.readNextRow(str);
    return str;
}

int main() {

    ifstream file("C:/positions.csv");

    CSVRow row;
    while (file >> row){

    }

    cout << "--" << endl;
}