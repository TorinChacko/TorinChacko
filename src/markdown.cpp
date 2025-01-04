#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <regex>
#include <cstdlib>
#include <chess.hpp> // Assuming a C++ chess library
#include <yaml-cpp/yaml.h> // YAML parsing library for C++

YAML::Node settings;

std::string create_link(const std::string& text, const std::string& link) {
    return "[" + text + "](" + link + ")";
}

std::string create_issue_link(const std::string& source, const std::set<std::string>& dest_list) {
    std::string issue_link = settings["issues"]["link"].as<std::string>();
    // URL encoding and parameter formatting would need to be implemented

    std::vector<std::string> ret;
    for (const auto& dest : dest_list) {
        ret.push_back(create_link(dest, "formatted_issue_link"));
    }
    
    std::string result;
    for (size_t i = 0; i < ret.size(); ++i) {
        if (i > 0) result += ", ";
        result += ret[i];
    }
    return result;
}

std::string generate_top_moves() {
    std::ifstream file("data/top_moves.txt");
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    // Parsing the content as a dictionary would require implementation

    std::string markdown = "\n| Total moves |  User  |\n| :---------: | :----- |\n";

    int max_entries = settings["misc"]["max_top_moves"].as<int>();
    // Sorting and formatting the dictionary entries would need to be implemented

    return markdown + "\n";
}

std::string generate_last_moves() {
    std::string markdown = "\n| Move | Author |\n| :--: | :----- |\n";

    int counter = 0;
    std::ifstream file("data/last_moves.txt");
    std::string line;
    std::regex move_regex("([A-H][1-8])([A-H][1-8])", std::regex_constants::icase);

    while (std::getline(file, line) && counter < settings["misc"]["max_last_moves"].as<int>()) {
        if (line.find(':') == std::string::npos) continue;

        std::smatch match;
        if (std::regex_search(line, match, move_regex)) {
            std::string source = match[1].str();
            std::string dest = match[2].str();
            std::transform(source.begin(), source.end(), source.begin(), ::toupper);
            std::transform(dest.begin(), dest.end(), dest.begin(), ::toupper);
            // Format the markdown line
        } else {
            // Format the markdown line for non-move entries
        }
        counter++;
    }

    return markdown + "\n";
}

std::string generate_moves_list(chess::Board& board) {
    std::unordered_map<std::string, std::set<std::string>> moves_dict;

    // Populate moves_dict using the chess library

    std::string markdown;

    if (board.is_game_over()) {
        // Format game over message
        return markdown;
    }

    if (board.is_check()) {
        markdown += "**CHECK!** Choose your move wisely!\n";
    }

    markdown += "|  FROM  | TO (Just click a link!) |\n| :----: | :---------------------- |\n";

    // Format the moves table

    return markdown;
}

std::string board_to_markdown(chess::Board& board) {
    std::unordered_map<char, std::string> images = {
        {'r', "img/black/rook.svg"},
        {'n', "img/black/knight.svg"},
        // ... other piece mappings ...
        {'.', "img/blank.png"}
    };

    std::string markdown;

    // Format the board header

    // Format the board rows

    // Format the board footer

    return markdown;
}

int main() {
    settings = YAML::LoadFile("data/settings.yaml");

    // Main logic to use the functions goes here

    return 0;
}
