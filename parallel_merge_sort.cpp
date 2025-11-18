#include <bits/stdc++.h>
#include <thread> 

vector<int> temp(1e7+1); 

void rec(vector<int>& arr, int l, int r, int depth){
    if (l==r) return ;
    int mid = (l+r)/2; 

    if (depth<=3){ 
      /*
        depth<=3 ensures that we don't spin up lot of threads (O(NLOGN))
      */
        std::thread t1(rec, std::ref(arr), l,mid,depth+1);
        std::thread t2(rec, std::ref(arr), mid+1,r, depth+1);
        t1.join();
        t2.join();
    }else{
        rec(arr,l,mid,depth+1);
        rec(arr,mid+1,r,depth+1);
    }   
    //perform merge in this thread 
    std::merge(arr.begin()+l, arr.begin()+mid+1, 
    arr.begin()+mid+1, arr.begin()+r+1, 
    temp.begin()+l);
    std::copy(temp.begin()+l, temp.begin()+r+1, arr.begin()+l);
}   

void benchmark(int N, int runs = 3) {
    std::cout << "Benchmarking N = " << N << " (" << runs << " runs)\n";
    std::cout<<"With Multithread - \n";
    for (int i = 1; i <= runs; i++) {
        vector<int> arr(N);
        temp.assign(N, 0);

        // fill with random data
        std::mt19937 rng(12345);
        std::uniform_int_distribution<int> dist(1, 1e9);
        for (int j = 0; j < N; j++)
            arr[j] = dist(rng);

        auto start = chrono::high_resolution_clock::now();

        rec(arr, 0, N - 1, 0);

        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end - start).count();

        // correctness check
        if (!is_sorted(arr.begin(), arr.end())) {
            std::cout << "!!!!! Array is NOT sorted! Something is wrong.\n";
            return;
        }

        std::cout << "Run " << i << ": " << ms << " ms\n";
    }

    std::cout<<"Without Multithread - \n";
    for (int i = 1; i <= runs; i++) {
        vector<int> arr(N);
        temp.assign(N, 0);

        // fill with random data
        std::mt19937 rng(12345);
        std::uniform_int_distribution<int> dist(1, 1e9);
        for (int j = 0; j < N; j++)
            arr[j] = dist(rng);

        auto start = chrono::high_resolution_clock::now();

        rec(arr, 0, N - 1, 4);

        auto end = chrono::high_resolution_clock::now();
        double ms = chrono::duration<double, milli>(end - start).count();

        // correctness check
        if (!is_sorted(arr.begin(), arr.end())) {
            std::cout << "!!!!! Array is NOT sorted! Something is wrong.\n";
            return;
        }

        std::cout << "Run " << i << ": " << ms << " ms\n";
    }

    std::cout<<"--------------------- \n";
}

int main() {
  
    int N = 10;  // change as needed
    benchmark(10);
    benchmark(100);
    benchmark(1000);
    benchmark(10000);
    benchmark(100000);
    benchmark(1000000);
    benchmark(10000000);

    return 0;
}
