void counting_selection_sort(int* arr, int n){
    int *count = (int*)calloc(n, sizeof(int));
    int *result = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            if(arr[j] < arr[i] || (arr[j] == arr[i] && j < i)){
                count[i]++;
            }
        }
    }
    for(int i = 0; i < n; ++i){
        result[count[i]] = arr[i];
    }
    for(int i = 0; i < n; ++i){
        arr[i] = result[i];
    }
    free(count); free(result);
}