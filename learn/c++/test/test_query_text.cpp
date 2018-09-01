/*************************************************************************
> File Name: test_query_text.cpp
> Author: orientlu
> Mail: lcdsdream@126.com
> Created Time: Wed 29 Aug 2018 11:25:50 PM CST
************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>

using namespace std;

class TextQuery;
class QueryResult;

class TextQuery {
public:
    using line_no = vector<string>::size_type;

    TextQuery(ifstream &infile);
    TextQuery(const TextQuery &tq):
        m_file(tq.m_file), m_lines(tq.m_lines)
    {
        cout << "call tq copy" << endl;
    }

    TextQuery& operator=(const TextQuery &tq)
    {
        cout << "call tq=" << endl;
        m_file = tq.m_file;
        m_lines = tq.m_lines;
    }

    QueryResult query(const string word);
    ~TextQuery() {}

private:
    shared_ptr<vector<string>> m_file;
    // "word" : ptr --> set(line_no,...)
    map<string, shared_ptr<set<line_no>>> m_lines;
};

class QueryResult {
public:
    QueryResult(string s,
                shared_ptr<set<TextQuery::line_no>> p,
                shared_ptr<vector<string>> f):
        m_sought(s), m_lines(p), m_file(f)
    {}

    QueryResult(const  QueryResult &qr):
        m_sought(qr.m_sought), m_lines(qr.m_lines), m_file(qr.m_file)
    {
        cout << "call trcp" << endl;
    }
    QueryResult& operator=(const QueryResult &qr)
    {
        cout << "call tr=" << endl;
        m_sought = qr.m_sought;
        m_lines = qr.m_lines;
        m_file = qr.m_file;
    }

private:
    string m_sought;
    shared_ptr<set<TextQuery::line_no>> m_lines;
    shared_ptr<vector<string>> m_file;

    public :
    friend ostream &operator<<(ostream &os, const QueryResult &qr);
};


TextQuery::TextQuery(ifstream &infile):
    m_file(new vector<string>)
{
    string text;
    while (getline(infile, text)) {
        m_file->push_back(text);
        line_no lineNo = m_file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word) {
            //auto &pLines = m_lines[word];
            shared_ptr<set<line_no>> &pLines = m_lines[word];
            if (!pLines) {
                pLines.reset(new set<line_no>);
            }
            pLines->insert(lineNo);
        }
    }
}

QueryResult
TextQuery::query(const string word)
{
    //empty set if no found
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    //auto
    map<string, shared_ptr<set<line_no>>>::iterator loc = m_lines.find(word);
    if (loc == m_lines.end()) {
        return QueryResult(word, nodata, m_file);
    } else {
        return QueryResult(word, loc->second, m_file);
    }
}
ostream &operator<<(ostream &os, const QueryResult &qr)
{
    os << "QueryResult: ";
    os << qr.m_sought << endl;
    for (auto line : *(qr.m_lines)) {
        os  << " [ " << line  << " ] : "<< *(qr.m_file->begin() + line);
        os << endl;
        //printf("[%ld] %s\n", line, (*(qr.m_file))[line].c_str());
    }
    os << endl;
    return os;
}
void run_querys(ifstream &infile)
{
    TextQuery tq(infile);
    while (true) {
        cout << "Enter word to look for, or q to quit : ";
        string s;
        if (!(cin >> s) || s == "q") break;

        cout << tq.query(s);
    }
}

int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    run_querys(input);
    return 0;
}
