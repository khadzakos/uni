#include <iostream>
#include <random>
#include <vector>
#include <fstream>

class Sort {
public:
    Sort() {
        std::random_device rd;
        gen.seed(rd());
    }
    ~Sort() = default;

    template<typename T>
    void quickSort(std::vector<T> &v) {
        int n = v.size();
        quickSort(v, 0, n);
    }

protected:
    template<typename T>
    int partition(std::vector<T> &v, int l, int r) {
        dis.param(std::uniform_int_distribution<int>::param_type(l, r - 1));
        int pivot = dis(gen);
        std::swap(v[pivot], v[r - 1]);
        T x = v[r - 1];
        int i = l - 1;
        for (int j = l; j < r - 1; ++j) {
            if (v[j] <= x) {
                i++;
                std::swap(v[i], v[j]);
            }
        }
        std::swap(v[i + 1], v[r - 1]);
        return i + 1;
    }
private:
    template<typename T>
    void quickSort(std::vector<T> &v, int l, int r) {
        if (l < r) {
            int p = partition(v, l, r);
            quickSort(v, l, p);
            quickSort(v, p + 1, r);
        }
    }

private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;
};

class IntroSort: public Sort {
public:
    IntroSort() = default;
    ~IntroSort() = default;

    template<typename T>
    void introSort(std::vector<T> &v) {
        int n = v.size();
        int maxDepth = 2 * static_cast<int>(std::log2(n));
        quickSort(v, 0, n, maxDepth);
    }

private:
    template<typename T>
    void insertionSort(std::vector<T> &v, int l, int r) {
        for (int i = l + 1; i < r; ++i) {
            int j = i;
            while (j > l && v[j] < v[j - 1]) {
                std::swap(v[j], v[j - 1]);
                --j;
            }
        }
    }

    template<typename T>
    void heapify(std::vector<T> &v, int n, T i) {
        T largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n && v[l] > v[largest]) {
            largest = l;
        }
        if (r < n && v[r] > v[largest]) {
            largest = r;
        }
        if (largest != i) {
            std::swap(v[i], v[largest]);
            heapify(v, n, largest);
        }
    }

    template<typename T>
    void buildMaxHeap(std::vector<T> &v, int n) {
        int index = n / 2 - 1;
        for (int i = index; i >= 0; --i) {
            heapify(v, n, i);
        }
    }

    template<typename T>
    void heapSort(std::vector<T> &v, int n) {
        buildMaxHeap(v, n);
        for (int i = n - 1; i > 0; i--) {
            std::swap(v[0], v[i]);
            heapify(v, i, 0);
        }
    }

    template<typename T>
    void quickSort(std::vector<T> &v, int l, int r, int maxDepth) {
        if (r - l <= 16) {
            insertionSort(v, l, r);
            return;
        }
        if (maxDepth == 0) {
            heapSort(v, r);
            return;
        }
        int p = partition(v, l, r);
        quickSort(v, l, p, maxDepth - 1);
        quickSort(v, p + 1, r, maxDepth - 1);
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

    long long measureIntroSortTime(std::vector<int>& v) {
        long long totalTime = 0;
        for (int i = 0; i < 10; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            IntroSort is;
            is.introSort(v);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            long long ms = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
            totalTime += ms;
        }
        return totalTime / 10;
    }

    long long measureSortTime(std::vector<int>& v) {
        long long totalTime = 0;
        for (int i = 0; i < 10; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            Sort s;
            s.quickSort(v);
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
    std::ofstream csvFileSort("data/sort_results.csv");
    std::ofstream csvFileIntroSort("data/introsort_results.csv");
    csvFileSort << "size,random,reversed,almost_sorted" << std::endl;
    csvFileIntroSort << "size,random,reversed,almost_sorted"<< std::endl;

    std::vector<int> sizes;
    for (int i = 500; i <= 15000; i += 100) {
        sizes.emplace_back(i);
    }

    for (int i = 0; i < sizes.size(); ++i) {
        std::vector<int> randomArr = ag.generateArray(sizes[i], 1);
        std::vector<int> reversedArr = ag.generateArray(sizes[i], 2);
        std::vector<int> almostSortedArr = ag.generateArray(sizes[i], 3);

        long long mergeTimeRandom = st.measureSortTime(randomArr);
        long long mergeTimeReversed = st.measureSortTime(reversedArr);
        long long mergeTimeAlmostSorted = st.measureSortTime(almostSortedArr);

        csvFileSort << sizes[i] << "," << mergeTimeRandom << "," << mergeTimeReversed << "," << mergeTimeAlmostSorted << std::endl;
        std::cout << sizes[i] << ' ' << mergeTimeRandom << ' ' << mergeTimeReversed << ' ' << mergeTimeAlmostSorted << std::endl;
    }

    for (int i = 0; i < sizes.size(); ++i) {
        std::vector<int> randomArr = ag.generateArray(sizes[i], 1);
        std::vector<int> reversedArr = ag.generateArray(sizes[i], 2);
        std::vector<int> almostSortedArr = ag.generateArray(sizes[i], 3);

        long long introSortTimeRandom = st.measureIntroSortTime(randomArr);
        long long introSortTimeReversed = st.measureIntroSortTime(reversedArr);
        long long introSortTimeAlmostSorted = st.measureIntroSortTime(almostSortedArr);

        csvFileIntroSort << sizes[i] << "," << introSortTimeRandom << "," << introSortTimeReversed << "," << introSortTimeAlmostSorted << std::endl;
        std::cout << sizes[i] << ' ' << introSortTimeRandom << ' ' << introSortTimeReversed << ' ' << introSortTimeAlmostSorted << std::endl;
    }

    csvFileSort.close();
    csvFileIntroSort.close();
    return 0;
}
