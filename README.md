# Weather Data Retrieval Using OpenWeatherMap API
This C++ program fetches weather data from the OpenWeatherMap API based on user input for a city name. It then displays the current temperature, humidity, and weather description for the specified city.

# Dependencies
This program utilizes the following dependencies:

• cURL: A library for transferring data with URLs.

• nlohmann/json: A JSON library for modern C++.

# Functionality
1. User Input: The program prompts the user to enter the name of a city.
2. API Request: It constructs a URL to query the OpenWeatherMap API for weather data of the specified city.
3. HTTP Request: Utilizing cURL, the program performs an HTTP request to fetch the weather data from the API.
4. Data Parsing: The JSON response received from the API is parsed to extract the temperature, humidity, and weather description.
5. Output: The extracted weather information is displayed to the user, including the temperature in Celsius, humidity percentage, and a description of the weather conditions.
6. Continuation: After displaying the weather information, the program prompts the user whether to continue querying for weather data of other cities or to exit the program.
   
# Usage
To run the program:
1. Compile the source code (weather.cpp) with a C++ compiler, ensuring that the required dependencies are linked.
2. Execute the compiled binary.
3. Follow the prompts to enter city names and view weather information.

# Notes
• Ensure that you have an active internet connection to fetch weather data from the OpenWeatherMap API.
• API key: This program utilizes a predefined API key (69b829bd23008ef0443d455a64ca474f). You may need to replace it with your own API key if you intend to use the program extensively.
• Error Handling: The program provides error messages if it fails to fetch weather data or encounters invalid JSON responses.
• Dependencies: Make sure to install and link the required dependencies (cURL and nlohmann/json) before compiling the program.

# License
This program is provided under the MIT License. Feel free to modify and distribute it according to the terms of the license.
