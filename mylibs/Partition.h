#ifndef DRAFT_PARTITION_H
#define DRAFT_PARTITION_H

#include <vector>

using namespace std;

class Partition {
private:
    static long long partitionRec(vector<long long> remainingItems, long long bag1, long long bag2) {
        if (remainingItems.empty())
            return abs(bag2 - bag1);
        long long item = remainingItems.back();
        remainingItems.pop_back();
        return min(partitionRec(remainingItems, bag1 + item, bag2), partitionRec(remainingItems, bag1, bag2 + item));
    }

public:
    static long long partitionRecursive(const long long &n, const long long &k, const vector<long long> &items) {
        vector<long long> remainingItems;
        remainingItems.reserve(items.size());
        for (auto item: items)
            remainingItems.push_back(item);
        long long bag1 = 0, bag2 = 0;
        return partitionRec(remainingItems, bag1, bag2);
    }

    static long long partitionDP(const long long &n, const long long &k, const vector<long long> &items) {
        /**
        * We will build a table of n+1 lines and k+1 columns, and a cell i, j is true if the sum of the items 1 to i is equal to j
        *    0 1 2 3 4 5 ...
        *    _ _ _ _ _ _
        * 0 |1 0 0 0 0 0| With 0 elements, no sum but 0 possible
        * 1 |1 ? ? ? ? ?|
        * 2 |1 ? ? ? ? ?|
        * 3 |1 ? ? ? ? ?|
        * 4 |1 ? ? ? ? ?|
        * 5 |1 ? ? ? ? ?|
        *    - - - - - -
        *    0 sum is always possible so 1st column to true
        */

        bool table[n + 1][k + 1];
        for (long long i = 0; i <= n; i++) {
            table[i][0] = true; // the 0 sum is always possible
        }
        for (long long i = 1; i <= k; i++) {
            table[0][i] = false; // first line is false except 0 0
        }
        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= k; j++) {
                table[i][j] = table[i -
                                    1][j]; // if the sum is already possible without this item, i.e. we exclude this item

                // the -1 is because the first line is reserved to 0 items. To avoid this, use a null element in items?
                long long apple = items[i - 1];
                if (apple <= j) { // do not go in negatives
                    table[i][j] |= table[i - 1][j - apple];
                }
            }
        }
        // now we have the table full, let's see at k/2 if there is a true, or under it to have the closest
        long long diff = 1e10;
        // to do so, go to the last line and iterate starting by the middle
        for (long long i = k / 2; i >= 0; i--) {
            if (table[n][i]) {
                diff = k - 2 * i; // optimisation to calculate here instead of doing it later
                break;
            }
        }
        return diff;
    }

    /**
     * Solve equal partition problem
     * @param n size of the vector
     * @param k sum of all elements
     * @param items
     * @return the difference between the partitions
     */
    static long long partitionDPFaster(const long long &n, const long long &k, const vector<long long> &items) {
        /**
        * We will build a table of n+1 lines and (k/2)+1 columns, and a cell i, j is true if the sum of the items 1 to i is equal to j
        *    0 1 2 3 4 5 ...
        *    _ _ _ _ _ _
        * 0 |1 0 0 0 0 0| With 0 elements, no sum but 0 possible
        * 1 |1 ? ? ? ? ?|
        * 2 |1 ? ? ? ? ?|
        * 3 |1 ? ? ? ? ?|
        * 4 |1 ? ? ? ? ?|
        * 5 |1 ? ? ? ? ?|
        *    - - - - - -
        *    0 sum is always possible so 1st column to true
        */

        bool table[n + 1][(k / 2) + 1];
        for (long long i = 0; i <= n; i++) {
            table[i][0] = true; // the 0 sum is always possible
        }
        for (long long i = 1; i <= k / 2; i++) {
            table[0][i] = false; // first line is false except 0 0
        }
        for (long long i = 1; i <= n; i++) {
            for (long long j = 1; j <= k / 2; j++) {
                table[i][j] = table[i -
                                    1][j]; // if the sum is already possible without this item, i.e. we exclude this item

                // the -1 is because the first line is reserved to 0 items. To avoid this, use a null element in items?
                long long apple = items[i - 1];
                if (apple <= j) { // do not go in negatives
                    table[i][j] |= table[i - 1][j - apple];
                }
            }
        }
        // now we have the table full, let's see at k/2 if there is a true, or under it to have the closest
        long long diff = 1e10;
        // to do so, go to the last line and iterate starting by the middle
        for (long long i = k / 2; i >= 0; i--) {
            if (table[n][i]) {
                diff = k - 2 * i; // optimisation to calculate here instead of doing it later
                break;
            }
        }
        return diff;
    }
};


#endif //DRAFT_PARTITION_H
