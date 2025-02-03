#include <iostream>
#include <fstream>
#include <string>


void writeToFile(const std::string& filename, const int& content) {
    std::ofstream outFile(filename, std::ios::app);
    if (outFile.is_open()) {
        outFile << content;
        // No explicit close here
        outFile.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}
 
int main() {
    writeToFile("example.txt", 100);
    writeToFile("example.txt", 200);
    return 0;
}

// void readWriteConflict(const std::string& filename) {
//     std::ofstream outFile(filename);
//     std::ifstream inFile(filename);
 
//     if (outFile.is_open() && inFile.is_open()) {
//         outFile << "Writing to file." << std::endl;
//         std::string line;
//         while (getline(inFile, line)) {
//             std::cout << line << std::endl;
//         }
//     } else {
//         std::cerr << "Failed to open file." << std::endl;
//     }
// }
 
// int main() {
//     readWriteConflict("example.txt");
//     return 0;
// }