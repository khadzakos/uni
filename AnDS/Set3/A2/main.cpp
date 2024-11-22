#include <iostream>
#include <random>
#include <vector>
#include <fstream>


class MergeSort {
public:
    MergeSort() = default;

    void mergeSort(std::vector<int> &v, int l, int r) {
        if (r - l == 1) {
            return;
        }
        int m = (l + r) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m, r);
        merge(v, l, r);
    }

protected:
    void merge(std::vector<int> &v, int l, int r) {
        int m = (l + r) / 2;
        std::vector<int> res(r - l);
        int i = l, j = m, k = 0;
        while (i < m && j < r) {
            if (v[i] < v[j]) {
                res[k++] = v[i++];
            } else {
                res[k++] = v[j++];
            }
        }
        while (i < m) {
            res[k++] = v[i++];
        }
        while (j < r) {
            res[k++] = v[j++];
        }
        for (i = l; i < r; ++i) {
            v[i] = res[i - l];
        }
    }
};

class MergeInsertionSort: protected MergeSort {
public:
    MergeInsertionSort() = default;

    void mergeSort(std::vector<int> &v, int l, int r, int x) {
        if (r - l < x) {
            insertionSort(v, l, r);
            return;
        }
        int m = (l + r) / 2;
        mergeSort(v, l, m, x);
        mergeSort(v, m, r, x);
        merge(v, l, r);
    }

private:
    void insertionSort(std::vector<int> &v, int l, int r) {
        for (int i = l + 1; i < r; ++i) {
            int j = i;
            while (j > l && v[j] < v[j - 1]) {
                std::swap(v[j], v[j - 1]);
                --j;
            }
        }
    }
};

class ArrayGenerator {
public:
    ArrayGenerator() {
        std::random_device rd;
        gen.seed(rd());
        dis.param(std::uniform_int_distribution<int>::param_type(0, 6000));
    }

    std::vector<int> generateArray(int n, int type) {
        std::vector<int> res(N);
        switch (type) {
            case 1:
                generateRandomArray(res);
                break;
            case 2:
                generateReversedArray(res);
                break;
            case 3:
                generateAlmostSortedArray(res);
                break;
            default:
                break;
        };

        return getSubarray(res, n);

    }
private:
    std::vector<int> getSubarray(std::vector<int>& arr, int n) {
        std::vector<int> res(n);
        int start = dis(gen) % (N - n);
        for (int i = 0; i < n; ++i) {
            res[i] = arr[start + i];
        }

        return res;
    }

    void generateRandomArray(std::vector<int>& res) {
        for (int i = 0; i < N; ++i) {
            res[i] = dis(gen);
        }
    }

    void generateAlmostSortedArray(std::vector<int>& res) {
        for (int i = 0; i < N; ++i) {
            res[i] = i;
        }

        for (int i = 0; i < N / 10; ++i) {
            int x = dis(gen) % N;
            int y = dis(gen) % N;
            std::swap(res[x], res[y]);
        }
    }

    void generateReversedArray(std::vector<int>& res) {
        generateRandomArray(res);
        std::sort(res.begin(), res.end());
        std::reverse(res.begin(), res.end());
    }
private:
    const int N = 10000;

    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
};

class SortTester {
public:
    SortTester() = default;

    long long measureMergeInsertionSortTime(std::vector<int>& v, int x) {
        long long totalTime = 0;
        for (int i = 0; i < 10; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            MergeInsertionSort().mergeSort(v, 0, v.size(), x);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            totalTime += ms;
        }
        return totalTime / 10;
    }

    long long measureMergeSortTime(std::vector<int>& v) {
        long long totalTime = 0;
        for (int i = 0; i < 10; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            MergeSort().mergeSort(v, 0, v.size());
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            totalTime += ms;
        }
        return totalTime / 10;
    }
};

int main() {
    ArrayGenerator ag;
    SortTester st;
    std::ofstream csvFileMerge("merge_sort_results.csv");
    std::ofstream csvFileMergeInsertion("merge_insertion_sort.csv");
    csvFileMerge << "size,random,reversed,almost_sorted" << std::endl;
    csvFileMergeInsertion << "size,random5,reversed5,almost_sorted5,random10,reversed10,almost_sorted10,random15,reversed15,almost_sorted15,random30,reversed30,almost_sorted30,random100,reversed100,almost_sorted100" << std::endl;

    std::vector<int> sizes;
    for (int i = 500; i <= 10000; i += 100) {
        sizes.emplace_back(i);
    }

    for (int i = 0; i < sizes.size(); ++i) {
        std::vector<int> randomArr = ag.generateArray(sizes[i], 1);
        std::vector<int> reversedArr = ag.generateArray(sizes[i], 2);
        std::vector<int> almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeTimeRandom = st.measureMergeSortTime(randomArr);
        long long mergeTimeReversed = st.measureMergeSortTime(reversedArr);
        long long mergeTimeAlmostSorted = st.measureMergeSortTime(almostSortedArr);

        csvFileMerge << sizes[i] << "," << mergeTimeRandom << "," << mergeTimeReversed << "," << mergeTimeAlmostSorted << std::endl;
        std::cout << sizes[i] << ' ' << mergeTimeRandom << ' ' << mergeTimeReversed << ' ' << mergeTimeAlmostSorted << std::endl;
    }

    for (int i = 0; i < sizes.size(); ++i) {
        std::vector<int> randomArr = ag.generateArray(sizes[i], 1);
        std::vector<int> reversedArr = ag.generateArray(sizes[i], 2);
        std::vector<int> almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeInsertionTimeRandom5 = st.measureMergeInsertionSortTime(randomArr, 5);
        long long mergeInsertionTimeReversed5 = st.measureMergeInsertionSortTime(reversedArr, 5);
        long long mergeInsertionTimeAlmostSorted5 = st.measureMergeInsertionSortTime(almostSortedArr, 5);

        randomArr = ag.generateArray(sizes[i], 1);
        reversedArr = ag.generateArray(sizes[i], 2);
        almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeInsertionTimeRandom10 = st.measureMergeInsertionSortTime(randomArr, 10);
        long long mergeInsertionTimeReversed10 = st.measureMergeInsertionSortTime(reversedArr, 10);
        long long mergeInsertionTimeAlmostSorted10 = st.measureMergeInsertionSortTime(almostSortedArr, 10);

        randomArr = ag.generateArray(sizes[i], 1);
        reversedArr = ag.generateArray(sizes[i], 2);
        almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeInsertionTimeRandom15 = st.measureMergeInsertionSortTime(randomArr, 15);
        long long mergeInsertionTimeReversed15 = st.measureMergeInsertionSortTime(reversedArr, 15);
        long long mergeInsertionTimeAlmostSorted15 = st.measureMergeInsertionSortTime(almostSortedArr, 15);

        randomArr = ag.generateArray(sizes[i], 1);
        reversedArr = ag.generateArray(sizes[i], 2);
        almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeInsertionTimeRandom30 = st.measureMergeInsertionSortTime(randomArr, 30);
        long long mergeInsertionTimeReversed30 = st.measureMergeInsertionSortTime(reversedArr, 30);
        long long mergeInsertionTimeAlmostSorted30 = st.measureMergeInsertionSortTime(almostSortedArr, 30);

        randomArr = ag.generateArray(sizes[i], 1);
        reversedArr = ag.generateArray(sizes[i], 2);
        almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeInsertionTimeRandom100 = st.measureMergeInsertionSortTime(randomArr, 100);
        long long mergeInsertionTimeReversed100 = st.measureMergeInsertionSortTime(reversedArr, 100);
        long long mergeInsertionTimeAlmostSorted100 = st.measureMergeInsertionSortTime(almostSortedArr, 100);

        csvFileMergeInsertion << sizes[i] << "," << mergeInsertionTimeRandom5 << "," << mergeInsertionTimeReversed5 << "," << mergeInsertionTimeAlmostSorted5 << ","
                              << mergeInsertionTimeRandom10 << "," << mergeInsertionTimeReversed10 << "," << mergeInsertionTimeAlmostSorted10 << ","
                              << mergeInsertionTimeRandom15 << "," << mergeInsertionTimeReversed15 << "," << mergeInsertionTimeAlmostSorted15 << ","
                              << mergeInsertionTimeRandom30 << "," << mergeInsertionTimeReversed30 << "," << mergeInsertionTimeAlmostSorted30 << ","
                              << mergeInsertionTimeRandom100 << "," << mergeInsertionTimeReversed100 << "," << mergeInsertionTimeAlmostSorted100 << std::endl;
        std::cout << sizes[i] << ' ' << mergeInsertionTimeRandom5 << ' ' << mergeInsertionTimeReversed5 << ' ' << mergeInsertionTimeAlmostSorted5 << ' '
                              << mergeInsertionTimeRandom10 << ' ' << mergeInsertionTimeReversed10 << ' ' << mergeInsertionTimeAlmostSorted10 << ' '
                              << mergeInsertionTimeRandom15 << ' ' << mergeInsertionTimeReversed15 << ' ' << mergeInsertionTimeAlmostSorted15 << ' '
                              << mergeInsertionTimeRandom30 << ' ' << mergeInsertionTimeReversed30 << ' ' << mergeInsertionTimeAlmostSorted30 << ' '
                                << mergeInsertionTimeRandom100 << ' ' << mergeInsertionTimeReversed100 << ' ' << mergeInsertionTimeAlmostSorted100 << std::endl;

    }

    csvFileMerge.close();
    csvFileMergeInsertion.close();
    return 0;
}
