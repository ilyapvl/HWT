#include <iostream>
#include "tree.hpp"
#include "tree_visualizer.hpp"



void processInput(std::istream& input, bool visualize = false)
{
    Trees::Tree<int> tree;
    std::string command;
    bool first_output = true;
    int step = 0;

    while (input >> command)
    {
        if (command == "k")
        {
            int key;
            input >> key;
            tree.insert(key);
            
            if (visualize)
            {
                TreeVisualizer<Trees::Tree<int>>::visualize(tree, "step_" + std::to_string(step++));
            }
        }

        else if (command == "q")
        {
            int left, right;
            input >> left >> right;
            
            int count = tree.count_in_range(left, right);
            if (!first_output) std::cout << " ";
            std::cout << count;
            first_output = false;
        }
    }
    
    std::cout << std::endl;
}

int main(const int argc, const char** argv)
{
    bool visualize = false;
    std::string filename;

    if (argc > 1)
    {
        filename = argv[1];
        if (argc > 2 && std::string(argv[2]) == "-v")
        {
            visualize = true;
        }
    }

    if (!filename.empty())
    {
        std::ifstream file(filename);
        processInput(file, visualize);
    }
    else
    {
        processInput(std::cin, visualize);
    }
    
    return 0;
}
