// A simple JSON parser

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void parse(ifstream & file, int & weight)
{
    char nextChar; // Holds the value being read
    string junk; // Holds any text not necessary in computing the weight

    file.get(nextChar); // Function used to read next character from file into variable

    char temp = file.peek(); // A char linked to a function to aways read the next character


    while (!file.eof())
    {
        if (nextChar == '{') // If object
        {
            weight++; // Increase due to object
            file.get(nextChar);
        }
        if (nextChar == '"')
        {
            getline(file, junk, '"'); // Gets name
            file.get(nextChar); // Gets ':'
            file.get(nextChar); // Gets ' '
            file.get(nextChar);

            if (nextChar == '"') // If string
            {
                while (nextChar != '"' && temp != ',')
                {
                    file.get(nextChar);
                }
                weight++; // Increasing due to mapped value with string
                file.get(nextChar); // Gets ','
                file.get(nextChar); // Gets ' '
                file.get(nextChar);
            }

            if (nextChar == 't' || nextChar == 'f' || nextChar == 'n') // If true, false, or null
            {
                weight++;
                getline(file, junk, ',');
                file.get(nextChar); // Gets ' '
                file.get(nextChar);
            }
            if (nextChar == '[') // If array
            {
                weight++;
                file.get(nextChar);
            }
            if (nextChar == '-' || isdigit(nextChar)) // If numeric
            {
                weight++;
                file.get(nextChar);

                while (isdigit(nextChar) || nextChar == '.')
                {
                    file.get(nextChar);
                }
                file.get(nextChar); // Gets ','
                file.get(nextChar); // Gets ' '
            }
        }

        file.get(nextChar);
    }
}
int main()
{
    ifstream file;

    int weight = 0; // An integer to hold the weight of the document read

    file.open("JSON_Data.txt");

    parse(file, weight);

    cout << "The weight of the JSON document is: " << weight << ".";
    return 0;
}
