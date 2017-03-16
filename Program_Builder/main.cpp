/*
Program attempts to create and compile a different program outputting 'Hello World'
Start Date: 3/15/17


*/

#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::string outputFile =
    "//Created by Trenton Potter's Creator Program\n\n#include <iostream>\n\nint main()\n{\nstd::cout << \"Hello World\\n\";\nreturn 0;\n}";

    std::cout << "\n\nCreating program\n";
    std::ofstream outFile;
    outFile.open("AutoGeneratedFile.cpp");
    outFile << outputFile;
    outFile.close();
    std::cout << "Ending program creation.\n\n";

    std::cout << "Begin Compiling\n";
    system("g++ AutoGeneratedFile.cpp -o HelloWorld");
    std::cout << "End Compiling\n";

    std::cout << "Program call\n\n";
    system("./HelloWorld");
    std::cout << "\nEnd Call\n";

}
