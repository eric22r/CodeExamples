//Declare Libararies
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <cstdio>
#include <ctime>
#include <chrono>
#include <thread>
//Declare namespaces
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


/// TYPEDEFS
typedef bool(*onInputCallback)(string);
//Differentiates the different types of words with responses
typedef enum ParserContext {
	NONE = 0,
	KEYWORD,
	GENERIC,
	GREETING,
	EMPTY,
	THING,
	PLACE,
	PERSON
} ParserContext;

/// UTILITIES
//List of words to ignore in responses
vector<string> stopwords = {
"i", "a", "about", "an", "are", "as", "at", "be", "by", "com", "for", "from", "how", "in", "is", "it", "of", "on", "or", "that", "the", "this", "to", "was", "what", "when", "where", "who", "will", "with", "the", "www" };
//Tokenizes strings
vector<string> tokenize(string _string, char separator = ' ')
{
	vector<string> tokens;
	string temp;
	stringstream data(_string);
	while (getline(data, temp, separator))
	{
		tokens.push_back(temp);
	}
	return tokens;
}

//allows you to type in lower case and converts it to caps
string strtoupper(string data)
{
	transform(data.begin(), data.end(), data.begin(), ::toupper);
	return data;
}

string strtolower(string data)
{
	transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}
//Checks for list of words to ignore to focus on likely keywords
bool isStopWord(string word)
{
    return count(stopwords.begin(), stopwords.end(), strtolower(word)) > 0;
}

//Eliza Central Class

class Eliza
{
public:
	Eliza();
	~Eliza();
	string readLine();
	void say(string stuff);
	void start();
	void end();
	void registerInputCallback(onInputCallback);
    string requestAdditionalInput(string prompt);
	void setPrompt(string prompt);
    void setTypingDelay(int typingDelayMs);

	string lastInput;

private:
	string m_Name = "ELIZA";
	bool m_Running = true;
	string m_Prompt = "";
	onInputCallback m_Callback = nullptr;
    int m_typingDelay = 0;

};

Eliza::Eliza() {}
Eliza::~Eliza() {}

string Eliza::readLine()
{
	//Exit on end of file
	if (cin.eof())
		m_Running = false;

	cout << m_Prompt << "> ";
	string input;
	getline(cin, input);

	return input;
}
//Eliza Output with delay
void Eliza::say(string stuff)
{
    if (m_typingDelay > 0)
    {
        for(auto i = stuff.begin(); i != stuff.end(); i++)
        {
            cout << *i << flush;
            sleep_for(milliseconds(m_typingDelay));
        }
        cout << endl;
    }
    else
    {
        cout << m_Name << "> " << stuff << endl;
    }
}

void Eliza::registerInputCallback(onInputCallback c)
{
	m_Callback = c;
}

string Eliza::requestAdditionalInput(string prompt)
{
    cout << m_Name << "> " << prompt << endl;
    cout << "\t>";

    string input;
    getline(cin, input);
    return strtoupper(input);
}

void Eliza::setPrompt(string prompt)
{
	m_Prompt = prompt;
}
//Begin Running
void Eliza::start()
{
	while (m_Running)
	{
		if (m_Callback != nullptr)
		{
			string data = strtoupper(readLine());

			bool continueRunning = m_Callback(data);
			if (!continueRunning)
			{
				m_Running = false;
			}
		}
	}
}
//Turns off
void Eliza::end()
{
	m_Running = false;
}
//Adds a delay for typing for effect
void Eliza::setTypingDelay(int typingDelayMs)
{
    m_typingDelay = typingDelayMs;
}

//Centralized Class for how Eliza will respond
class ResponseDatabase
{
public:
	ResponseDatabase(string filename);
	void addResponseForKeyword(string keyword, string response);
	string getRandomResponseForKeyword(string keyword);
	string getGenericResponse();
	string getGreeting();
	string getEmpty();
	string getThing();
	string getPlace();
	string getPerson();

private:
	ifstream m_FileStream;
	unordered_map<string, vector<string>> m_KeywordMap;
	std::vector<string> m_genericResponses;
	std::vector<string> m_greetings;
	std::vector<string> m_emptyResponses;
	std::vector<string> m_thingResponses;
	std::vector<string> m_placeResponses;
	std::vector<string> m_personResponses;
};
ResponseDatabase::ResponseDatabase(string filename)
{
	m_FileStream.open(filename);

	std::string line;
	std::string currentKeyword = "";
	bool nextLineIsKeyword = false;

	ParserContext context = ParserContext::NONE;

	while (getline(m_FileStream, line))
	{
		if (line.find("@KWD@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::KEYWORD;
			nextLineIsKeyword = true;
			continue;
		}

		if (nextLineIsKeyword)
		{
			currentKeyword = line;
			nextLineIsKeyword = false;
			continue;
		}

		if (line.find("@GREETING@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::GREETING;
			continue;
		}

		if (line.find("@GENERIC@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::GENERIC;
			continue;
		}

		if (line.find("@EMPTY@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::EMPTY;
			continue;
		}

		if (line.find("@THING@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::THING;
			continue;
		}

		if (line.find("@PLACE@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::PLACE;
			continue;
		}

		if (line.find("@PERSON@") != string::npos)//Look for tag and make sure it is found
		{
			context = ParserContext::PERSON;
			continue;
		}

		switch (context)
		{
		case ParserContext::NONE:
			cout << "Error in Parser" << endl;
			break;

		case ParserContext::KEYWORD:
			addResponseForKeyword(currentKeyword, line);
			break;

		case ParserContext::GREETING:
			m_greetings.push_back(line);
			break;

		case ParserContext::GENERIC:
			m_genericResponses.push_back(line);
			break;

		case ParserContext::EMPTY:
			m_emptyResponses.push_back(line);
			break;

		case ParserContext::THING:
			m_thingResponses.push_back(line);
			break;

		case ParserContext::PLACE:
			m_placeResponses.push_back(line);
			break;

		case ParserContext::PERSON:
			m_personResponses.push_back(line);
			break;
		}
	}
}
//Adds Response
void ResponseDatabase::addResponseForKeyword(string keyword, string response)
{
	if (m_KeywordMap.count(keyword) == 0)
	{
		std::vector<string> responseVector;
		responseVector.push_back(response);
		m_KeywordMap[keyword] = responseVector;
	}
	else
	{
		m_KeywordMap[keyword].push_back(response);
	}
}
//Pulls random response from grouping below keyword
string ResponseDatabase::getRandomResponseForKeyword(string keyword)
{
	if (m_KeywordMap.count(keyword) > 0)
	{
		std::vector<string> possibleResponses = m_KeywordMap[keyword];

		int n = possibleResponses.size();
		int choice = rand() % n;

		return possibleResponses.at(choice);
	}

	return "";
}
//Response getters
string ResponseDatabase::getGenericResponse()
{
	if (m_genericResponses.size() == 0)
		return "No generic responses loaded. Do you have any in the .dat file?";
	return m_genericResponses.at(rand() % m_genericResponses.size());
}
//Response getters
string ResponseDatabase::getGreeting()
{
	if (m_greetings.size() == 0)
		return "No greetings loaded. Do you have any in the .dat file?";
	return m_greetings.at(rand() % m_greetings.size());
}

//Response getters
string ResponseDatabase::getEmpty()
{
	if (m_emptyResponses.size() == 0)
		return "No empty responses loaded. Do you have any in the .dat file?";
	return m_emptyResponses.at(rand() % m_emptyResponses.size());
}
//Response getters
string ResponseDatabase::getThing()
{
	if (m_thingResponses.size() == 0)
		return "No responses loaded for things. Do you have any in the .dat file?";
	return m_thingResponses.at(rand() % m_thingResponses.size());
}
//Response getters
string ResponseDatabase::getPlace()
{
	if (m_placeResponses.size() == 0)
		return "No responses loaded for places. Do you have any in the .dat file?";
	return m_placeResponses.at(rand() % m_placeResponses.size());
}
//Response getters
string ResponseDatabase::getPerson()
{
	if (m_personResponses.size() == 0)
		return "No responses loaded for places. Do you have any in the .dat file?";
	return m_personResponses.at(rand() % m_personResponses.size());
}
//Class to store history

class HistoryFile
{
    public:
        HistoryFile();
        void open(string filename);
        void dump();
        void writeEntry(string name, string content);
		string hasNegativeSentiment();//For remembering

    private:
        fstream m_FileHandle;
        vector<string> historyLines;
        void parse();
};

HistoryFile::HistoryFile(){}

void HistoryFile::writeEntry(string name, string content)
{
    m_FileHandle << name + "^" + content << endl;
    m_FileHandle.flush();
}

void HistoryFile::open(string filename)
{
    //Open the file to read it, parse it then open it for more writing
    m_FileHandle.open(filename, fstream::in);
    parse();
    m_FileHandle.close();
    m_FileHandle.open(filename, fstream::out | fstream::app);//NEEDS APP OR WILL OVERWRITE
}
//File parser
void HistoryFile::parse()
{
    string line;
    while(getline(m_FileHandle, line))
    {
        vector<string> parts = tokenize(line, '^');
        string name = parts.at(0);
        string content = parts.at(1);

        //If this is user input (aka not Eliza)
        if (name.compare("ELIZA") != 0)
        {
            historyLines.push_back(content);
        }
    }
}

void HistoryFile::dump()
{
    for(auto i = historyLines.begin(); i != historyLines.end(); i++)
    {
        cout << *i << endl;
    }
}
//Import list of negative focus words for Eliza to remember
string HistoryFile::hasNegativeSentiment()
{
	ifstream m_NegativeWordFile("negative_words.txt");
	string word;
	while(getline(m_NegativeWordFile, word))
    {
        for(auto i = historyLines.begin(); i != historyLines.end(); i++)
        {
            string historyLine = *i;
            if(historyLine.find(word) != string::npos)
            {
                return word;
            }
        }
    }

    return "";
}

//Begin main declarations and functions
Eliza eliza;
HistoryFile history;
ResponseDatabase responses("Eliza.dat");
string username = "";
string password = "";

bool onInput(string inputData)
{
	//Set username on first input if username is empty - checks for password and if new user writes password to a txt file
	if (username.empty())
	{
		username = inputData;
		eliza.setPrompt(username);

        ifstream passwordFile(username + "password.txt");
        if(passwordFile.is_open())
        {
            string inputPassword = eliza.requestAdditionalInput("WELCOME BACK, " + username + ". PLEASE ENTER YOUR PASSWORD.");
            getline(passwordFile, password);

            if(inputPassword.compare(password) == 0)
            {
                eliza.say("YOUR PASSWORD IS CORRECT. WELCOME BACK, " + username);
            }
            else
            {
                eliza.say("YOUR PASSWORD IS INCORRECT. GOODBYE.");
                return false;
            }
        }
        else
        {
            string response = eliza.requestAdditionalInput("WOULD YOU LIKE TO SECURE YOUR HISTORY WITH A PASSWORD?");
            if(response.compare("YES") == 0)
            {
                string password = eliza.requestAdditionalInput("PLEASE ENTER YOUR PASSWORD.");
                ofstream passwordFileWrite(username + "password.txt");
                passwordFileWrite << password;
                eliza.say("YOUR PASSWORD HAS BEEN SET.");
            }
        }

        history.open(username + "log.txt");
		//Checks if there was negative sentiment in the last conversation and will reference it if it is true
        string negativeSentiment = history.hasNegativeSentiment();
        if(negativeSentiment.empty())
            eliza.say(responses.getGreeting());
        else
            eliza.say("I HOPE YOU ARENT STILL DEALING WITH THE " + negativeSentiment + " PROBLEM");

		return true;
	}

	if (inputData == "")
	{
		eliza.say(responses.getEmpty());
		return true;
	}
	//Checks words for keywords
	string response;
	vector<string> tokens = tokenize(inputData);
	for (auto i = tokens.begin(); i != tokens.end(); i++)
	{
		string possibleResponse = responses.getRandomResponseForKeyword(*i);
		if (!possibleResponse.empty())
		{
			response = possibleResponse;
			break;
		}

	}

	if (response.empty())
	{
		response = responses.getGenericResponse();
	}

	cout << response << endl;
    history.writeEntry(username, inputData);
    history.writeEntry("ELIZA", response);
	return true;
}
//Main loop used to reference functions
int main(int argc, char **argv)
{
	srand(time(nullptr));
	eliza.registerInputCallback(onInput);
    eliza.setTypingDelay(60);
	eliza.setPrompt("?");
	eliza.say("What's your name?");
	eliza.start();
}
