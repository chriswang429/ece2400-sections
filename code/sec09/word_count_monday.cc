#include <algorithm>
#include <cctype>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int main(void)
{
	std::string input_word;
	std::unordered_map<std::string, std::size_t> word_hist;
	std::multimap<std::size_t, std::string, std::greater<std::size_t>> freq_word;
	while(std::cin >> input_word) {
		std::transform(
			input_word.begin(),
			input_word.end(),
			input_word.begin(),
			::tolower
			);
		word_hist[input_word]++;
	}
	for(auto& word_freq: word_hist) {
		freq_word.insert(std::make_pair(word_freq.second, word_freq.first));
	}
	for(auto& hist_entry: freq_word) {
		std::cout << hist_entry.first << "," << hist_entry.second
			<< std::endl;
	}
	return 0;
}
