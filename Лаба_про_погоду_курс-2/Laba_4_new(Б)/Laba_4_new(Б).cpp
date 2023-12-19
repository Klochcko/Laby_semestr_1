#include <iostream>
#include <vector>
#include <algorithm>

struct Request {
    int start, end, profit;
};

int findLatestNonConflict(const std::vector<Request>& requests, int i) {
    for (int j = i - 1; j >= 0; j--) {
        if (requests[j].end <= requests[i].start) {
            return j;
        }
    }
    return -1;
}

int maxProfit(const std::vector<Request>& requests) {
    int n = requests.size();
    std::vector<int> dp(n);

    // Base case
    dp[0] = requests[0].profit;

    for (int i = 1; i < n; i++) {
        int includeProfit = requests[i].profit;
        int latestNonConflict = findLatestNonConflict(requests, i);

        if (latestNonConflict != -1) {
            includeProfit += dp[latestNonConflict];
        }

        dp[i] = std::max(includeProfit, dp[i - 1]);
    }

    return dp[n - 1];
}

int main() {
    int n;
    std::cout << "Enter the number of requests: ";
    std::cin >> n;

    std::vector<Request> requests(n);

    std::cout << "Enter start, end, and profit for each request:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> requests[i].start >> requests[i].end >> requests[i].profit;
    }

    std::sort(requests.begin(), requests.end(), [](const Request& a, const Request& b) {
        return a.end < b.end;
        });

    int result = maxProfit(requests);

    std::cout << "Maximum profit: " << result << std::endl;

    return 0;
}
