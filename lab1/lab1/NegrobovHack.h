#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "utils.h"
#include "NegrobovCrypto.h"


std::vector<int> get_frequency(std::vector<unsigned char>& text);

double compliance_index(std::vector<unsigned char>& text);

int find_key_len(int least, int great, std::vector<unsigned char>& text, bool show, int n);

std::vector<int> get_popular_chars(const std::vector<int>& frequency, int n);

std::string get_key(int length, std::vector<unsigned char>& text, std::vector<int> popular_chars);

std::vector<int> get_popular_chars(std::vector<unsigned char>& text, int n);

bool hack_key();