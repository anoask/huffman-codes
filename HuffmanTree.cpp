#include <stack>
#include "HuffmanTree.hpp"

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}

void HuffmanTree::buildTree(const std::string& inputStr) {
    std::map<char, size_t> frequencyMap;
    for (char c : inputStr) {
        frequencyMap[c]++;
    }

    HeapQueue<HuffmanNode*, HuffmanNode::Compare> heap;

    for (auto pair : frequencyMap) {
        heap.insert(new HuffmanNode(pair.first, pair.second));
    }

    while (heap.size() > 1) {
        HuffmanNode* left = heap.min();
        heap.removeMin();
        HuffmanNode* right = heap.min();
        heap.removeMin();

        size_t combinedFrequency = left->getFrequency() + right->getFrequency();
        HuffmanNode* parentNode = new HuffmanNode('\0', combinedFrequency, nullptr, left, right);
        left->parent = parentNode;
        right->parent = parentNode;

        heap.insert(parentNode);
    }

    root = heap.min();
}

void HuffmanTree::buildCodeTable(HuffmanNode* node, const std::string& code) {
    if (!node) return;

    if (node->isLeaf()) {
        codeTable[node->getCharacter()] = code;
    } else {
        buildCodeTable(node->left, code + "0");
        buildCodeTable(node->right, code + "1");
    }
}

std::string HuffmanTree::compress(const std::string inputStr) {
    buildTree(inputStr);
    buildCodeTable(root, "");

    std::string compressed;
    for (char c : inputStr) {
        compressed += codeTable[c];
    }
    return compressed;
}

std::string HuffmanTree::serializeTree() const {
    return serializeTreeHelper(root);
}

std::string HuffmanTree::serializeTreeHelper(HuffmanNode* node) const {
    if (!node) return "";

    if (node->isLeaf()) {
        return "L" + std::string(1, node->getCharacter());
    }

    std::string leftSerialized = serializeTreeHelper(node->left);
    std::string rightSerialized = serializeTreeHelper(node->right);

    return leftSerialized + rightSerialized + "B";
}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree) {
    // step 1: Deserialize
    std::stack<HuffmanNode*> nodeStack;
    for (size_t i = 0; i < serializedTree.size(); ++i) {
        if (serializedTree[i] == 'L') {
            i++;  // move to the character
            nodeStack.push(new HuffmanNode(serializedTree[i], 0));
        } else if (serializedTree[i] == 'B') {
            HuffmanNode* rightChild = nodeStack.top();
            nodeStack.pop();
            HuffmanNode* leftChild = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(new HuffmanNode('\0', 0, nullptr, leftChild, rightChild));
        }
    }

    HuffmanNode* localRoot = nodeStack.top();

    // step 2: Decode
    std::string decompressed;
    HuffmanNode* currentNode = localRoot;

    for (char bit : inputCode) {
        if (bit == '0') {
            currentNode = currentNode->left;
        } else {  // bit is 1
            currentNode = currentNode->right;
        }

        if (currentNode->isLeaf()) {
            decompressed += currentNode->getCharacter();
            currentNode = localRoot;  // reset back to root for next character
        }
    }

    // Cleanup
    deleteTree(localRoot);
    return decompressed;
}



void HuffmanTree::deleteTree(HuffmanNode* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
