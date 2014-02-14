#pragma once

#include <string>

using namespace std;
//---------------------------------------------------------------------
//CTokenクラス（文字列を渡すとデリミタでトークンに分ける
//---------------------------------------------------------------------
class CToken
{
private:
	string::size_type cur_;
	string str_;
	string del_;
	bool   ret_;
	void skip();
public:
	typedef std::pair<string::size_type,string::size_type> range_type;
	CToken(const string& str, const string& del, bool ret=false);
	bool empty();
	string next();
	range_type next_range();
	void set_str(const string& str);
	void set_delimiter(const string& del, bool ret=false);
	size_t count() const;
};
