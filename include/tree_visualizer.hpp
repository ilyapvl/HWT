#ifndef TREE_VISUALIZER_HPP
#define TREE_VISUALIZER_HPP

#include "tree.tpp"
#include <fstream>
#include <string>

template<typename Tree>
class TreeVisualizer
{
public:
    static void generateDotFile(const Tree& tree, const std::string& filename)
    {
        std::ofstream file(filename);
        file << "digraph AVLTree {\n";
        file << "  node [shape=rectangle, style=filled, fillcolor=lightblue];\n";
        
        if (!tree.empty())
        {
            generateNodeDot(file, tree.getRoot());
        }
        
        file << "}\n";
        file.close();
    }
    
    static void visualize(const Tree& tree, const std::string& baseFilename)
    {
        std::string dotFilename = baseFilename + ".dot";
        
        generateDotFile(tree, dotFilename);
    }

private:
    static void generateNodeDot(std::ofstream& file, typename Tree::iterator node)
    {
        if (!node) return;
        
        file << "  " << node->key_ << " [label=\"" << node->key_ << "\\nh=" << node->height_ << "\"];\n";
        
        if (node->left_)
        {
            file << "  " << node->key_ << " -> " << node->left_->key_ << " [label=\"L\"];\n";
            generateNodeDot(file, node->left_);
        }

        else
        {
            file << "  null" << node->key_ << "l [shape=point];\n";
            file << "  " << node->key_ << " -> null" << node->key_ << "l [label=\"L\"];\n";
        }
        


        if (node->right_)
        {
            file << "  " << node->key_ << " -> " << node->right_->key_ << " [label=\"R\"];\n";
            generateNodeDot(file, node->right_);
        }

        else
        {
            file << "  null" << node->key_ << "r [shape=point];\n";
            file << "  " << node->key_ << " -> null" << node->key_ << "r [label=\"R\"];\n";
        }
    }
};

#endif // TREE_VISUALIZER_HPP
