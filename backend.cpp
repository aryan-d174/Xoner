#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp> // Ensure this file is downloaded and in the project folder

using json = nlohmann::json;
using namespace std;

// API Endpoint for fetching NCS songs and artists
const string API_URL = "https://ncs-api-url.com/v1/songs";  // Replace with actual NCS API

// Function to handle cURL response
size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}
// Function to make an API request and fetch data
string fetchDataFromAPI() {
    CURL* curl = curl_easy_init();
    string response_data;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, API_URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // Ignore SSL verification if needed

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }

    return response_data;
}

// Function to cache API response to a local file
void cacheData(const string& data) {
    ofstream file("ncs_cache.json");
    if (file.is_open()) {
        file << data;
        file.close();
    }
}

// Function to read cached data if available
string readCache() {
    ifstream file("ncs_cache.json");
    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return data.empty() ? "" : data;
}

// Function to get NCS songs (either from cache or API)
json getNCSData() {
    string cachedData = readCache();

    if (!cachedData.empty()) {
        cout << "Using Cached Data\n";
        return json::parse(cachedData);
    } else {
        cout << "Fetching New Data from API\n";
        string apiData = fetchDataFromAPI();
        cacheData(apiData);
        return json::parse(apiData);
    }
}

// Main function to run the backend
int main() {
    json ncsData = getNCSData();

    if (!ncsData.is_null()) {
        cout << "🎵 Available NCS Songs & Artists:\n";
        for (const auto& song : ncsData["songs"]) {
            cout << "🎶 " << song["title"] << " - " << song["artist"] << "\n";
        }
    } else {
        cout << "⚠️ No data available. Check API connectivity.\n";
    }

    return 0;
}
