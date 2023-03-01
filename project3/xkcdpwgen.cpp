#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
#include <sstream>

// load words from a file into a vector
std::vector<std::string> load_words(const std::string& filename) {
    std::vector<std::string> valid_words; // vector to store the words
    std::ifstream word_file(filename); // open the file
    if (word_file.is_open()) {
        std::string word;
        while (std::getline(word_file, word)) {
            // remove words more than 8 characters long
            if (word.size() <= 8) {
                valid_words.push_back(word);
            }
        }
        word_file.close();
    }
    return valid_words;
}

// generate a password using the XKCD method
std::string generate_password(const std::vector<std::string>& word_list, int num_words, int num_caps, int num_numbers, int num_symbols) {
    std::vector<std::string> words(num_words); // vector to store the words
    std::default_random_engine rng(time(nullptr)); // initialize the random number generator
    std::uniform_int_distribution<int> dist(0, word_list.size() - 1); // create a distribution to generate random indices

    // select random words from the word list
    std::generate(words.begin(), words.end(), [&word_list, &dist, &rng]() {
        return word_list[dist(rng)];
    });

    // join the words together with spaces
    std::string password = "";
    for (const auto& word : words) {
        password += word + " ";
    }

    // capitalize some of the words
    if (num_caps > 0) {
        std::uniform_int_distribution<int> cap_dist(0, num_words - 1); // create a distribution to generate random indices
        std::vector<int> cap_indices(num_caps); // vector to store the indices of the words to capitalize
        std::generate(cap_indices.begin(), cap_indices.end(), [&cap_dist, &rng]() { // generate the indices
            return cap_dist(rng);
        });
        std::sort(cap_indices.begin(), cap_indices.end()); // sort the indices
        for (const auto& index : cap_indices) { // capitalize the words
            words[index][0] = toupper(words[index][0]);
        }
        password = "";
        for (const auto& word : words) { // join the words together with spaces again so it can be split later
            password += word + " ";
        }
    }

    // insert some numbers into the password
    if (num_numbers > 0) {
        std::uniform_int_distribution<int> num_dist(0, num_words); // create a distribution to generate random indices
        std::vector<int> insert_positions(num_numbers); // vector to store the indices of the words to insert numbers into
        std::generate(insert_positions.begin(), insert_positions.end(), [&num_dist, &rng]() { // generate the indices
            return num_dist(rng); 
        });
        std::sort(insert_positions.begin(), insert_positions.end()); // sort the indices
        int num_inserted = 0;
        for (const auto& pos : insert_positions) { // insert the numbers
            int insert_pos = 0;
            for (int i = 0; i < pos; ++i) { // calculate the position to insert the number
                insert_pos += words[i].size() + 1; // add the length of the word and a space
            }
            password.insert(insert_pos + num_inserted, std::to_string(rng() % 10)); // insert the number
            ++num_inserted;
        }
    }

    // insert some symbols into the password
    if (num_symbols > 0) {
        std::uniform_int_distribution<int> symbol_dist(0, num_words); // create a distribution to generate random indices
        std::vector<int> insert_positions(num_symbols);
        std::generate(insert_positions.begin(), insert_positions.end(), [&symbol_dist, &rng]() { // generate the indices
            return symbol_dist(rng);
        });
        std::sort(insert_positions.begin(), insert_positions.end()); // sort the indices
        int num_inserted = 0;
        for (const auto& pos : insert_positions) { // insert the symbols
            int insert_pos = 0;
            for (int i = 0; i < pos; ++i) {
                insert_pos += words[i].size() + 1; // calculate the position to insert the symbol
            }
            password.insert(insert_pos + num_inserted, 1, "~!@#$%^&*.:;"[symbol_dist(rng)]); // insert the symbol
            ++num_inserted;
        }
    }

    password.erase(std::remove(password.begin(), password.end(), ' '), password.end()); // remove spaces from the password
    return password;
}

int main(int argc, char* argv[]) {
    int num_words = 4, num_caps = 0, num_numbers = 0, num_symbols = 0;
    // parse command line arguments, can be in any order and are optional
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-w") {
            std::istringstream iss(argv[i + 1]);
            iss >> num_words;
        } else if (arg == "-c") {
            std::istringstream iss(argv[i + 1]);
            iss >> num_caps;
        } else if (arg == "-n") {
            std::istringstream iss(argv[i + 1]);
            iss >> num_numbers;
        } else if (arg == "-s") {
            std::istringstream iss(argv[i + 1]);
            iss >> num_symbols;
        }
    }

    std::vector<std::string> word_list = load_words("words.txt"); // load the word list

    if (num_caps > num_words) { // if we want to capitalize more words than the number of words in the password
        std::cerr << "Error: Cannot capitalize more words than the number of words in the password" << std::endl;
        return 1;
    }

    std::string password = generate_password(word_list, num_words, num_caps, num_numbers, num_symbols); // generate the password
    std::cout << password << std::endl;
    return 0;
}