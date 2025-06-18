#ifndef GUARD_Database_h
#define GUARD_Database_h


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


template <class T>
class Database
{
    public:
        Database()  {   }
        Database(std::string f, std::string c = "", int r = 1) {   filename = f; column = c;row = r;  }
        ~Database() {   }

        T Read() const;
        void WriteNewLine(const std::string&) const;
        void AddNewLine(const std::string&) const;

    private:
        std::string filename;
        std::string column;
        int row;

        std::vector<std::string> SplitCSVLine(const std::string&) const;
        T StringToValue(const std::string&) const;
};


template <class T> T Database<T>::StringToValue(const std::string& value) const   
{
    T result;
    std::istringstream iss(value);
    iss >> result;
    
    if (iss.fail()) 
    {
        throw std::domain_error("Failed to convert string to type: " + value);
    }
    return result;
}


// Full specialization for Database<std::string>
template <>
inline std::string Database<std::string>::StringToValue(const std::string& value) const
{
    return value;  
}


template <class T> std::vector<std::string> Database<T>::SplitCSVLine(const std::string& line) const
{
    std::vector<std::string> ret;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) 
    {
        // Remove leading and trailing whitespace
        cell.erase(0, cell.find_first_not_of(" \t"));
        cell.erase(cell.find_last_not_of(" \t") + 1);

        ret.push_back(cell);
    }
    return ret;
}


template <class T> T Database<T>::Read() const
{
    T data;
    std::ifstream file(filename);
    if (file.is_open()) 
    {
        std::string line;

        // read the title line
        if (std::getline(file, line)) 
        {
            // parse all column names
            std::vector<std::string> headers = SplitCSVLine(line); 
            
            // find the index corresponding to the column name
            int column_index = -1;
            for (std::vector<std::string>::size_type i = 0; i < headers.size(); ++i) 
            {
                if (headers[i] == column) 
                {
                    column_index = i;
                    break;
                }
            }
            
            if (column_index != -1) 
            {
                // read the specified row
                for(int i = 1; i < row; ++i) 
                {
                    if (!std::getline(file, line)) 
                    {
                        file.close();
                        throw std::domain_error("Not enough rows in file: " + filename);
                    }
                }

                // read the data line
                if (std::getline(file, line)) 
                {
                    // parse all data
                    std::vector<std::string> row_data = SplitCSVLine(line);

                    // ensure the column index valid
                    if (column_index < row_data.size()) 
                    {
                        data = this->StringToValue(row_data[column_index]);
                    } 
                    else 
                    {
                        file.close();
                        throw std::domain_error("Column index out of range in file: " + filename);
                    }
                }
                else 
                {
                    file.close();
                    throw std::domain_error("Not enough rows in file: " + filename);
                }
                file.close();
            } 
            else 
            {
                file.close();
                throw std::domain_error("Could not find column: " + column);
            }
        }
        else
        {
            file.close();
            throw std::domain_error("File is empty: " + filename);
        }
    } 
    else 
    {
        throw std::domain_error("Could not open file: " + filename);
    }
    return data;
}


template <class T> void Database<T>::WriteNewLine(const std::string& data) const
{
    std::ifstream inFile(filename);
    std::vector<std::string> lines;
    if (inFile.is_open()) 
    {    
        std::string line;
        
        // read and store all lines
        while (std::getline(inFile, line)) 
        {
            lines.push_back(line);
        }
        inFile.close();
    }
    else
    {
        throw std::domain_error("Could not open file: " + filename);
    }

    // keep the title line
    std::vector<std::string> new_lines = {lines.front(), data};


    // clear the whole file and write the new content
    std::ofstream outFile(filename);
    if(outFile.is_open()) 
    {
        outFile.clear(); 
        for (const auto& line : new_lines) 
        {
            outFile << line << std::endl;
        }
        outFile.close();
    } 
    else
    {
        throw std::domain_error("Could not open file: " + filename);
    }
}


template <class T> void Database<T>::AddNewLine(const std::string& data) const
{
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) 
    {
        throw std::domain_error("Could not open file: " + filename);
    }

    outFile << '\n';
    outFile << data;
    outFile.close();
}

#endif