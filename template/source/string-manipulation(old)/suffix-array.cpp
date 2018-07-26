int array[N], rank[N], height[N];
int counter[N], new_array[N], new_rank[N][2];
int log2[N], value[N][20];

void build(char *text, int n) {
    memset(counter, 0, sizeof(counter));
    for (int i = 0; i < n; ++i) {
        counter[(int)text[i]]++;
    }
    for (int i = 0; i < 256; ++i) {
        counter[i + 1] += counter[i];
    }
    for (int i = 0; i < n; ++i) {
        rank[i] = counter[(int)text[i]] - 1;
    }
    for (int length = 1; length < n; length <<= 1) {
        for (int i = 0; i < n; ++i) {
            new_rank[i][0] = rank[i];
            new_rank[i][1] = i + length < n ? rank[i + length] + 1 : 0;
        }
        memset(counter, 0, sizeof(counter));
        for (int i = 0; i < n; ++i) {
            counter[new_rank[i][1]]++;
        }
        for (int i = 0; i < n; ++i) {
            counter[i + 1] += counter[i];
        }
        for (int i = n - 1; i >= 0; --i) {
            new_array[--counter[new_rank[i][1]]] = i;
        }
        memset(counter, 0, sizeof(counter));
        for (int i = 0; i < n; ++i) {
            counter[new_rank[i][0]]++;
        }
        for (int i = 0; i < n; ++i) {
            counter[i + 1] += counter[i];
        }
        for (int i = n - 1; i >= 0; --i) {
            array[--counter[new_rank[new_array[i]][0]]] = new_array[i];
        }
        rank[array[0]] = 0;
        for (int i = 0; i + 1 < n; ++i) {
            rank[array[i + 1]] = rank[array[i]] + 
                (new_rank[array[i]][0] != new_rank[array[i + 1]][0] 
              || new_rank[array[i]][1] != new_rank[array[i + 1]][1]);
        }
    }
    for (int i = 0, length = 0; i < n; ++i) {
        if (rank[i]) {
            int j = array[rank[i] - 1];
            while (i + length < n && j + length < n 
                    && text[i + length] == text[j + length]) {
                length++;
            }
            height[rank[i]] = length;
            if (length) {
                length--;
            }
        }
    }
    for (int i = 2; i <= n; ++i) {
        log2[i] = log2[i >> 1] + 1;
    }
    for (int i = 1; i < n; ++i) {
        value[i][0] = height[i];
    }
    for (int step = 1; (1 << step) <= n; ++step) {
        for (int i = 1; i + (1 << step) <= n; ++i) {
            value[i][step] = std::min(value[i][step - 1],
                                      value[i + (1 << step - 1)][step - 1]);
        }
    }
}

int lcp(int left, int right) {
    if (left > right) {
        std::swap(left, right);
    }
    int step = log2[right - left];
    return std::min(value[left + 1][step], value[right - (1 << step) + 1][step]);
}