#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <math.h>
#include <list>

using namespace std;

//Implementing a Weighted Directed Graph with BFS and DFS
struct adjVertex
{
    int cost;
    int des_vertex;
};

class Graph
{
private:
    int V; // Number of vertices
    list<adjVertex> *AdjTable; // Adjacency list for each vertex

public:

    Graph(int V) //Constructor
    {
        this->V = V;
        this->AdjTable = new list<adjVertex>[V];
    }

    ~Graph()
    {
        this->V = 0;

        for (int i = 0; i < this->V; ++i)
            this->AdjTable[i].clear();

        delete[] this->AdjTable;
    }

    bool containEgde(int src_vertex, int des_vertex, int cost)
    {
        if (src_vertex < this->V && des_vertex < this->V)
        {
            for (list<adjVertex>::iterator i = this->AdjTable[src_vertex].begin(); i != this->AdjTable[src_vertex].end(); ++i)
            {
                adjVertex* curr_adjVertex = &(*i);
                if (curr_adjVertex->des_vertex == des_vertex && curr_adjVertex->cost == cost)
                    return true;
            }
        }
        return false;
    }

    void addEgde(int src_vertex, int des_vertex, int cost) //Add v to u adjacency list
    {
        if (this->containEgde(src_vertex, des_vertex, cost) == false)
        {
            adjVertex* newEdge = new adjVertex;
            newEdge->cost = cost;
            newEdge->des_vertex = des_vertex;

            this->AdjTable[src_vertex].push_back(*newEdge);

            delete newEdge;
        }
    }

    void removeEdge(int src_vertex, int des_vertex, int cost)
    {
        if (this->containEgde(src_vertex, des_vertex, cost) == true)
        {
            adjVertex* tmp = new adjVertex;
            tmp->des_vertex = des_vertex;
            tmp->cost = cost;

            this->AdjTable[src_vertex].remove(*tmp);
        }
    }

    void removeVertex(int vertex)
    {
        if (vertex < this->V)
        {
            this->AdjTable[vertex].clear();
        }
    }

    void BFS(int start)
    {
        queue<int> BFS;
        bool* visited = new bool[V];

        for (int i = 0; i < V; ++i)
        {
            visited[i] = false;
        }

        visited[start] = true;
        BFS.push(start);

        while (!BFS.empty())
        {
            start = BFS.front();
            cout << "Now visiting vertex: " << start << endl;
            BFS.pop();
            for (list<adjVertex>::iterator i = this->AdjTable[start].begin(); i != this->AdjTable[start].end(); ++i) //Check start's remaining vertices
            {
                adjVertex* curr_adjVertex = &(*i);

                if (!visited[curr_adjVertex->des_vertex])
                {
                    visited[curr_adjVertex->des_vertex] = true;
                    BFS.push(curr_adjVertex->des_vertex);
                }
            }
        }
    }

    void DFS(int start)
    {
        stack<int> DFS;
        bool *visited = new bool[this->V];

        for (int i = 0; i < this->V; ++i)
        {
            visited[i] = false;
        }
        visited[start] = 0;
        DFS.push(start);

        while (!DFS.empty())
        {
            start = DFS.top();
            DFS.pop();
            cout << "Now visiting vertex: " << start << endl;
            for (list<adjVertex>::iterator i = this->AdjTable[start].begin(); i != this->AdjTable[start].end(); ++i)
            {
                adjVertex* curr_adjVertex = &(*i);

                if (!visited[curr_adjVertex->des_vertex])
                {
                    visited[curr_adjVertex->des_vertex] = true;
                    DFS.push(curr_adjVertex->des_vertex);
                }
            }
        }
    }
};

template <class T>
T LinearSearch(T arr[], T key, int n)
{
    //Given array arr[]
    //Start from the leftmost element of arr[] and one by one compare x with each element of arr[]
    //If x matches with an element, return the index.
    //If x doesn’t match with any of elements, return -1.
    //Complexity O(n)
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] == key)
            return arr[i];
    }
    return -1;
}

template <class T>
T BinarySearch(T arr[], T key)
{
    //Given sorted array arr[]
    //Compare x with the middle element.
    //If x matches with middle element, we return the mid index.
    //Else If x is greater than the mid element, then x can only lie in right half subarray after the mid element. So we recur for right half.
    //Else (x is smaller) recur for the left half.
    int n = sizeof(arr) / sizeof(arr[0]); // number of elements in array arr[]
    int index_left = 0;
    int index_right = n - 1;

    while (index_left <= index_right)
    {
        int index_mid = index_left + (index_right - index_left) / 2;
        if (arr[index_mid] == key)
        {
            return arr[index_mid];
        }
        if (key > arr[index_mid])
        {
            index_left = index_mid + 1;
        }
        else
        {
            index_right = index_mid - 1;
        }
    }
    return -1;
}

template <class T>
T JumpSearch(T arr[], T key)
{
    //the best step size is m = sqrt(n)
    int n = sizeof(arr) / sizeof(arr[0]); //number of elements in array arr[]
    int step = sqrt(n);

    int prev = 0;
    while (arr[min(step, n) - 1] < key)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    //Perform linear search on found block
    while (prev == min(step, n))
    {
        if (arr[prev] == key)
            return arr[prev];
        ++prev;
    }
    return -1;
}

template <class T>
T InterpolationSearch(T arr[], T key)
{
    //Step1: In a loop, calculate the value of “pos” using the probe position formula. 
    //Step2: If it is a match, return the index of the item, and exit. 
    //Step3: If the item is less than arr[pos], calculate the probe position of the left sub-array. Otherwise calculate the same in the right sub-array. 
    //Step4: Repeat until a match is found or the sub-array reduces to zero.
    int n = sizeof(arr) / sizeof(arr[0]);
    int low = 0;
    int high = n - 1;
    while (low <= high && key >= arr[low] && key <= arr[high])
    {
        if (low == high)
        {
            if (arr[low] == key)
            {
                return arr[low];
            }
            return -1;
        }

        int pos = low + ((high - low) / arr[high] - arr[low]) * (key - arr[low]);

        if (arr[pos] == key)
        {
            return arr[pos];
        }

        if (key > arr[pos])
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }
    return -1;
}