#ifndef ALGO_TRIE_H
#define ALGO_TRIE_H

#include <string>

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
};

class Trie {
private:
    TrieNode *root;
public:

    explicit Trie() {
        root = makeNode();
    }

    static TrieNode *makeNode() {
        auto *pNode = new TrieNode;
        pNode->isEndOfWord = false;
        for (auto &i : pNode->children)
            i = nullptr;
        return pNode;
    }

    void insert(const std::string &key) {
        TrieNode *pCrawl = root;

        for (char k : key) {
            int index = k - 'a';
            if (!pCrawl->children[index])
                pCrawl->children[index] = makeNode();

            pCrawl = pCrawl->children[index];
        }

        // mark last node as leaf
        pCrawl->isEndOfWord = true;
    }

    bool isInTrie(const std::string &key) {
        TrieNode *pCrawl = root;
        for (char k : key) {
            int index = k - 'a';
            if (!pCrawl->children[index])
                return false;
            pCrawl = pCrawl->children[index];
        }
        return (pCrawl != nullptr && pCrawl->isEndOfWord);
    }
};

#endif //ALGO_TRIE_H
