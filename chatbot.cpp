#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

    string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int main() {
    string userInput;
    cout << "Welcome to the chatbot. Type 'exit' to end the conversation." <<endl;

    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        userInput = toLowerCase(userInput);

        if (userInput == "exit") {
            cout << "Chatbot: byy. Have a great day" <<endl;
            break;
        }
        else if (userInput == "hello" || userInput == "hi") {
            cout << "Chatbot: Hello sir" <<endl;
        }
        else if (userInput == "how are you") {
            cout << "Chatbot: I'm good! How about you?" <<endl;
        }
        else if (userInput == "what is your name") {
            cout << "Chatbot: I'm a simple chatbot. I don't have a name, but you can call me Chatbot" <<endl;
        }
        else if (userInput == "how to prepare for exams") {
            cout << "Chatbot: Focus on understanding concepts. Practice past papers and take time to review your notes. Good luck" << endl;
        }
        else if (userInput == "what is the weather") {
            cout << "Chatbot: you can check a weather website for current information." <<endl;
        }
        else if (userInput == "what time is it") {
            cout << "Chatbot: Sorry, I can't check the time. you can look at your device for the current time" <<endl;
        }
        else {
            cout << "Chatbot: I'm sorry, I don't understand that. Can you ask something else?" <<endl;
        }
    }

    return 0;
}
