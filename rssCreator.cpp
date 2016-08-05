#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define RSS_FEED_NAME	"Iron Horse Interactive"
#define WEBSITE_URL	"http://ironhorse.io/"
#define WEBSITE_DESCRIPTION "IHI provides global brands with fully integrated solutions that drive demand and generate revenue for their products."

static void replaceAll(string&, const string&, const string&);

int main( int argc, char * argv[])
{
	std::ofstream outputFile;
	string title, link, description, image_url;

	if(argc < 3) {
		cout << "Please enter a file name and number of items on the command line." << endl;
		return -1;
	}

	outputFile.open(argv[1]);

// general stuff
	outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << endl;
	outputFile << "<rss version=\"2.0\">" << endl;
	outputFile << "<channel>" << endl;
	outputFile << "<title>" << RSS_FEED_NAME << "</title>" << endl;
	outputFile << "<link>" << WEBSITE_URL << "</link>" << endl;
	outputFile << "<description>" << WEBSITE_DESCRIPTION << "</description>" << endl;

	for(int i = 0; i < atol(argv[2]); i++) {
		cout << "Entering details for article " << i << "..." << endl;

		cout << "Enter the article title: " << endl;
		getline(cin, title);
		cout << "Enter the article link: "  << endl;
		getline(cin, link);
		if(!contains(link, "&amp;")) {
			replaceAll(link, "&", "&amp;");
		}
		cout << "Enter the article description: " << endl;
		getline(cin, description);
		cout << "Enter the image url: " << endl;
		getline(cin, image_url);
		if(!contains(image_url, "&amp;")) {
			replaceAll(image_url, "&", "&amp;");
		}

		outputFile << "<item>" << endl;
		outputFile << "<title>" << title << "</title>" << endl;
		outputFile << "<link>" << link << "</link>" << endl;
		outputFile << "<description><![CDATA[<div class=\"rss_thumbnail\"><img src=\"";
		outputFile << image_url << "\"/></div>" << description << "]]></description>" << endl;
		outputFile << "</item>" << endl;
	}

	outputFile << "</channel>" << endl;
	outputFile << "</rss>" << endl;

	outputFile.close();
	cout << "Done!\n";

	return 0;
}

bool contains(const string& str, const string& substr) {
	return str.find(substr) == string::npos;
}

static void replaceAll(string& str, const string& from, const string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}
