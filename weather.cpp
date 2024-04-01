#include <bits/stdc++.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp> 

using json = nlohmann::json;

struct MemoryStruct {
    char* memory;
    size_t size;
};

// Callback function to write received data into a buffer
static size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        // out of memory
        std::cerr << "Not enough memory (realloc returned NULL)\n";
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

// Function to fetch weather data from OpenWeatherMap API
json getWeatherData(const std::string& city) {
    std::string url = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&appid=69b829bd23008ef0443d455a64ca474f";

    CURL* curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = (char*)malloc(1); // will be grown as needed by the realloc in WriteMemoryCallback
    chunk.size = 0;                   // no data at this point

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            // HTTP request successful, parse JSON response
            json response = json::parse(chunk.memory);
            free(chunk.memory);
            curl_easy_cleanup(curl);
            return response;
        }
    }
    // Cleanup on failure
    free(chunk.memory);
    curl_easy_cleanup(curl);
    return json(); // Return empty JSON object on failure
}

int main() {
    bool continueLoop = true;
    
    while (continueLoop) {
        std::string city;
        std::cout << "Enter city name: ";
        std::cin >> city;

        json weatherData = getWeatherData(city);
        if (!weatherData.empty()) {
            // Check if the JSON response contains the expected fields
            if (weatherData["main"].is_object() && weatherData["main"]["temp"].is_number() && weatherData["main"]["humidity"].is_number() && weatherData["weather"].is_array() && !weatherData["weather"].empty() && weatherData["weather"][0]["description"].is_string()) {
                // Extract temperature from JSON response
                double temperature = weatherData["main"]["temp"];
                temperature -= 273.15;
                double humidity = weatherData["main"]["humidity"];
                std::string description = weatherData["weather"][0]["description"];
                std::cout << "The temperature in " << city << " is " << temperature << " humidity is " << humidity << " and weather description is " << description << std::endl;
            } else {
                std::cout << "Failed to fetch valid weather data for " << city << std::endl;
            }
        }
        else {
            std::cout << "Failed to fetch weather data for " << city << std::endl;
        }

        // Prompt user whether to continue or not
        std::string choice;
        std::cout << "Do you want to continue? (yes/no): ";
        std::cin >> choice;
        if (choice != "yes") {
            continueLoop = false;
        }
    }

    return 0;
}


