#include<iostream>
#include<vector>
#include<algorithm>


const int LEN = 1000000;

int main()
{
    std::vector<int> v;
    v.reserve(LEN);

    int x = 0;
    while(std::cin >> x) {
	v.push_back(x);
    }
    std::sort(v.begin(), v.end());
    for(auto it = v.begin(); it != v.end(); ++it) {
	std::cout << (*it) << '\n';
    }
    std::cout << std::endl;
    return 0;
}
