#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>

class HuffmanTree : public HuffmanTreeBase {
public:
    HuffmanTree();
    ~HuffmanTree();

    virtual std::string compress(const std::string inputStr) override;
    virtual std::string serializeTree() const override;
    virtual std::string decompress(const std::string inputCode, const std::string serializedTree) override;

private:
    HuffmanNode* root;
    std::map<char, std::string> codeTable;

    std::string serializeTreeHelper(HuffmanNode* node) const;
    void buildTree(const std::string& inputStr);
    void buildCodeTable(HuffmanNode* node, const std::string& code);
    //char decode(HuffmanNode* node, const std::string& inputCode, size_t& pos);
    void deleteTree(HuffmanNode* node);
};

#endif
