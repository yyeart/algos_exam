void heapify(int *arr, int root, int bottom){
    int max_child;
    while ((root * 2 + 1) <= bottom) {
        if (root * 2 + 1 == bottom) max_child = root * 2 + 1;
        else if (arr[root * 2 + 1] > arr[root * 2 + 2]) max_child = root * 2 + 1;
        else max_child = root * 2 + 2;

        if (arr[root] < arr[max_child]){
            int temp = arr[root];
            arr[root] = arr[max_child];
            arr[max_child] = temp;
            root = max_child;
        } else break;
    }
}

void heapsort(int* arr, int n){
    for(int i = (n / 2) - 1; i >= 0; --i) heapify(arr, i, n - 1);
    for(int i = n - 1; i >= 1; --i){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, 0, i - 1);
    }
}