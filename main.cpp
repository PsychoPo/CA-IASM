#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

void print(ostream& out, long arr[], long size)
{
    for (long i = 0; i < size; i++)
    {
        out << "Arr[" << i + 1 << "]: " << arr[i] << endl;
    }
    return;
}

int increment(long inc[], long size)
{
    int p1, p2, p3, s;

    p1 = p2 = p3 = 1;
    s = -1;
    do
    {
        if (++s % 2)
        {
            inc[s] = 8 * p1 - 6 * p2 + 1;
        }
        else
        {
            inc[s] = 9 * p1 - 9 * p3 + 1;
            p2 *= 2;
            p3 *= 2;
        }
        p1 *= 2;
    } while (3 * inc[s] < size);

    return s > 0 ? --s : 0;
}

void shellSort(long arr[], long size)
{
    long inc, i, j, seq[40];
    int s;

    s = increment(seq, size);
    while (s >= 0)
    {
        inc = seq[s--];

        for (i = inc; i < size; i++)
        {
            long temp = arr[i];
            for (j = i - inc; (j >= 0) && (arr[j] > temp); j -= inc)
                arr[j + inc] = arr[j];
            arr[j + inc] = temp;
        }
    }
}

void downHeap(long arr[], long k, long n)
{
    long new_elem;
    long child;
    new_elem = arr[k];

    while (k <= n / 2)
    {
        child = 2 * k;
        if (child < n && arr[child] < arr[child + 1])
            child++;
        if (new_elem >= arr[child])
            break;
        arr[k] = arr[child];
        k = child;
    }
    arr[k] = new_elem;
}
void heapSort(long arr[], long size)
{
    long i;
    long temp;

    for (i = size / 2 - 1; i >= 0; i--)
        downHeap(arr, i, size - 1);

    for (i = size - 1; i > 0; i--)
    {
        temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        downHeap(arr, 0, i - 1);
    }
}

void quickSortR(long* a, long N)
{

    long i = 0, j = N - 1;
    long temp, p;

    p = a[N >> 1];

    do
    {
        while (a[i] < p)
        {
            i++;
        }

        while (a[j] > p)
        {
            j--;
        }

        if (i <= j)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);

    if (j > 0)
        quickSortR(a, j + 1);
    if (N - 1 > i)
        quickSortR(a + i, N - i);
}

void createRandArrS(ostream& out, long arr[], long size, long r, long r1, long s)
{
    for (long i = 0; i <= size; i += s)
    {
        arr = new long[i];
        for (long j = 0; j < i; j++)
        {
            arr[j] = rand() % (r1 - r + 1) + r;
        }
        clock_t t0 = clock();
        shellSort(arr, i);
        clock_t t1 = clock();
        print(out, arr, i);
        out << endl;
        delete[] arr;
        out << "Elements[" << i << "] Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl;
    }
    return;
}

void createRandArrH(ostream& out, long arr[], long size, long r, long r1, long s)
{
    for (long i = 0; i <= size; i += s)
    {
        arr = new long[i];
        for (long j = 0; j < i; j++)
        {
            arr[j] = rand() % (r1 - r + 1) + r;
        }
        clock_t t0 = clock();
        heapSort(arr, i);
        clock_t t1 = clock();
        print(out, arr, i);
        out << endl;
        delete[] arr;
        out << "Elements[" << i << "] Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl;
    }
    return;
}

void createRandArrQ(ostream& out, long arr[], long size, long r, long r1, long s)
{
    for (long i = 0; i <= size; i += s)
    {
        arr = new long[i];
        if (arr != nullptr)
            out << "\nTest_ArrayNotNullptr is OK!";
        for (long j = 0; j < i; j++)
        {
            arr[j] = rand() % (r1 - r + 1) + r;
            if (arr[j] <= r1 && arr[j] >= r)
                out << "\nTest_ValueInRange is OK!";
        }
        clock_t t0 = clock();
        quickSortR(arr, i);
        clock_t t1 = clock();
        if (t0 != 0 && t1 != 0)
            out << "\nTest_ClockNotNull is OK!\n";
        print(out, arr, i);
        out << endl;
        delete[] arr;
        out << "Elements[" << i << "] Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl;
    }
    return;
}

int main()
{
    long* A = nullptr;
    int key = 0;
    long n = 0, r = 0, r1 = 0, s = 0;
    cout << "\nWelcome! You are using IASM.\nChoose from the list by entering numbers.\n";
    while (key != 10)
    {
        cout << "\n1 - Create an array with random values and choose method of sorting.";
        cout << "\n10 - EXIT.\nEnter: ";
        cin >> key;
        cout << endl;
        switch (key)
        {
        case 1:
        {
            ofstream fout;
            string f;
            int answer = 0;
            if (A != nullptr)
            {
                delete[] A;
                n = 0;
                r = 0;
                r1 = 0;
                s = 0;
            }
            cout << "Enter number of the Array: " << endl;
            cin >> n;
            cout << "Specify the range of values of the array elements.\nEnter the smallest number: ";
            cin >> r;
            cout << "Enter the biggest number: ";
            cin >> r1;
            cout << endl;
            cout << "Enter the step of the creation an array: ";
            cin >> s;
            cout << endl;
            cout << "Enter 1 - if you want to sort by ShellSort\nEnter 2 - if you want to sort by HeapSort\nEnter 3 - if you want to sort by QuickSort\nAnswer: ";
            cin >> answer;
            cout << endl;
            cout << "Enter the name of the file, which you need to print: " << endl;
            cin >> f; // 1.txt
            fout.open(f, ios::trunc);
            if (!fout)
            {
                cout << "\n No file";
                return 1;
            }
            if (answer == 1)
                createRandArrS(fout, A, n, r, r1, s);
            else if (answer == 2)
                createRandArrH(fout, A, n, r, r1, s);
            else if (answer == 3)
                createRandArrQ(fout, A, n, r, r1, s);
            else
            {
                cout << "Error\n";
                break;
            };
            fout.close();
            cout << "\nDone!\n";
        }
        break;
        }
    }
    delete[] A;
    return 0;
}