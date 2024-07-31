// CMakeProject1.cpp : Defines the entry point for the application.
//

#include "CMakeProject1.h"

using namespace std;
vector<string> replaced;
vector<string> lines;
bool run = true;
struct rfppfunction;
struct rfppvar;
int currentline = 0;
string mostrecentline = "";
vector<int> endneeded;
vector<rfppvar> variablelist;
vector<rfppfunction> functionlist;
struct rfppvar {
	string name;
	string description;
	string value;
	int type;
	string rfppclass;
};
struct rfppfunction {
	string name;
	string description;
	string owner;
	vector<rfppvar> parameters;
	int startline;
	int endline;
};
string getlistvalues(string line, vector<rfppvar>& variablelis);
string runfunc(int func, string ogline);
int runline(string line, vector<rfppvar>& variablelis, int i, string& returnvalue);
string removespaces(string text, bool protectstrings=false) {
	string retvalue;
	bool ignore = false;
	for (auto character : text) {
		if (character == '"' && protectstrings) {
			ignore = !ignore;
		}
		if (character != ' ' || ignore) {
			retvalue = retvalue + character;
		}
	}
	return retvalue;
}
string removewhitespace(string line) {
	string retvalue = "";
	int i = 0;
	for (auto character : line) {
		if (character != 0 && character != 1 && character != 4 && character != 9 && character != 32) {
			break;
		}
		i++;
	}
	return line.substr(i);
}
string before(string og, string subject) {
	auto find = og.find(subject);
	if (find != string::npos) {
		return og.substr(0, find);
	}
	return "";
}
string after(string og, string subject) {
	auto find = og.find(subject);
	if (find != string::npos) {
		return og.substr(find + subject.length(), og.length() - 1);
	}
	return "";
}
bool isvalidvariablecharacter(char character) {
	switch (character) {
	case 'a':
		return true;
		break;
	case 'b':
		return true;
		break;
	case 'c':
		return true;
		break;
	case 'd':
		return true;
		break;
	case 'e':
		return true;
		break;
	case 'f':
		return true;
		break;
	case 'g':
		return true;
		break;
	case 'h':
		return true;
		break;
	case 'i':
		return true;
		break;
	case 'j':
		return true;
		break;
	case 'k':
		return true;
		break;
	case 'l':
		return true;
		break;
	case 'm':
		return true;
		break;
	case 'n':
		return true;
		break;
	case 'o':
		return true;
		break;
	case 'p':
		return true;
		break;
	case 'q':
		return true;
		break;
	case 'r':
		return true;
		break;
	case 's':
		return true;
		break;
	case 't':
		return true;
		break;
	case 'u':
		return true;
		break;
	case 'v':
		return true;
		break;
	case 'w':
		return true;
		break;
	case 'x':
		return true;
		break;
	case 'y':
		return true;
		break;
	case 'z':
		return true;
		break;
	case 'A':
		return true;
		break;
	case 'B':
		return true;
		break;
	case 'C':
		return true;
		break;
	case 'D':
		return true;
		break;
	case 'E':
		return true;
		break;
	case 'F':
		return true;
		break;
	case 'G':
		return true;
		break;
	case 'H':
		return true;
		break;
	case 'I':
		return true;
		break;
	case 'J':
		return true;
		break;
	case 'K':
		return true;
		break;
	case 'L':
		return true;
		break;
	case 'M':
		return true;
		break;
	case 'N':
		return true;
		break;
	case 'O':
		return true;
		break;
	case 'P':
		return true;
		break;
	case 'Q':
		return true;
		break;
	case 'R':
		return true;
		break;
	case 'S':
		return true;
		break;
	case 'T':
		return true;
		break;
	case 'U':
		return true;
		break;
	case 'V':
		return true;
		break;
	case 'W':
		return true;
		break;
	case 'X':
		return true;
		break;
	case 'Y':
		return true;
		break;
	case 'Z':
		return true;
		break;
	}
	return false;
}
bool nameisinfunctionlist(string name) {
	for (auto function : functionlist) {
		if (function.name == name) {
			return true;
		}
	}
	return false;
}
bool isfunction(string value, vector<rfppvar>& variablelis) {
	if (value.find('(') != string::npos && value.find(')') != string::npos && nameisinfunctionlist(before(value, "("))) {
		return true;
	}
	return false;
}
int getfunc(string name) {
	int i = 0;
	for (auto func : functionlist) {
		if (name == func.name) {
			return i;
		}
		i++;
	}
	return -1;
}
bool isnumber(string value) {
	for (char character : value) {
		if (character != '1' && character != '2' && character != '3' && character != '4' && character != '5' && character != '6' && character != '7' && character != '8' && character != '9' && character != '0' && character != '-' && character != '.') {
			return false;
		}
	}
	return true;
}
bool isnumber(char character) {
	if (character != '1' && character != '2' && character != '3' && character != '4' && character != '5' && character != '6' && character != '7' && character != '8' && character != '9' && character != '0' && character != '-' && character != '.') {
		return false;
	}

	return true;
}
vector<string> seperateby(string line, char sep, bool listprevent=false) {
	string wordbuild = "";
	vector<string> retvalue;
	bool ignore = false;
	for (auto character : line) {
		if (character == sep && !ignore ) {
			retvalue.push_back(wordbuild);
			wordbuild = "";
		}
		else if (character == '{' && listprevent) {
			wordbuild += character;
			ignore = true;
		}
		else if (character == '}' && listprevent) {
			wordbuild += character;
			ignore = false;
		}
		else {
			wordbuild += character;
		}
	}
	if (wordbuild != "") {
		retvalue.push_back(wordbuild);
	}
	return retvalue;
}
int findvariable(string text) {
	bool isword = false;
	string varname = "";
	int i = 0;
	for (auto character : text) {
		if (!isword || isvalidvariablecharacter(character)) {
			isword = true;

		}

		if (isword && (isvalidvariablecharacter(character) || isnumber(character))) {
			varname += character;

		}
		else {
			return i - 1;
		}
		i++;
	}
	return -1;
}
int findvarstart(string text) {
	int i = 0;
	for (auto character : text) {
		if (isvalidvariablecharacter(character)) {
			return i;
		}
		i++;
	}
	return -1;
}

bool isnumeric(string value) {
	for (char character : value) {
		if (character != '1' && character != '2' && character != '3' && character != '4' && character != '5' && character != '6' && character != '7' && character != '8' && character != '9' && character != '0' && character != '.' && character != '-') {
			return false;
		}
	}
	return true;
}
bool isnumeric(char character) {
	if (character != '1' && character != '2' && character != '3' && character != '4' && character != '5' && character != '6' && character != '7' && character != '8' && character != '9' && character != '0' && character != '.' && character != '-') {
			return false;
	}
	
	return true;
}
int startofnum(string operation, char sign) {
	int i = 0;
	int start;
	bool previsnumber = false;
	for (auto character : operation) {
		if (character == sign && i != 0) {
			return start;
		}
		else if (isnumeric(character)) {
			if (!previsnumber) {
				start = i;
			}
			previsnumber = true;
		}
		else { previsnumber = false; }

		i++;

	}
	return -1;
}
int getopposing(char main, string line, string::size_type start) {
	if (start == string::npos) {
		return -1;
	}
	int val = 0;
	int i = start;
	char oppo;
	switch (main) {
	case '{':
		oppo = '}';
		break;
	case '(':
		oppo = ')';
		break;
	}
	for (auto character : line.substr(start)) {
		if (character == main) {
			val += 1;
		}
		else if (character == oppo) {
			val -= 1;
		}
		if (val == 0) {
			return i;
		}
		i++;
	}
	return -1;

}
int endofnum(string operation, char sign) {
	int i = 0;
	bool add = false;
	for (auto character : operation) {
		if (character == sign && !add) {
			add = true;
		}
		else if (add) {
			if (!isnumeric(character)) {
				return i - 1;
			}
			else if (character == operation[operation.length() - 1] && i == operation.length() - 1) {
				return i;
			}
		}
		i++;
	}
	return -1;
}
int countamount(string line, char character) {
	int pos = 0;
	pos = line.find(character, pos);
	int i = 0;
	while (pos != string::npos) {
		i++;
		pos += 1;
		pos = line.find(character, pos);

	}
	return i;
}
int getopposingend(int start) {
	int val = 1;
	string oppo = "end";
	string line;
	for (int i = start + 1; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if (line.starts_with("for every ") || line.starts_with("for ") || line.starts_with("if ") || line.starts_with("while ") || line.starts_with("define ")) {
			val += 1;
		}
		else if (line == oppo) {
			val -= 1;
		}
		if (val == 0) {
			return i;
		}
	}
	return -1;
}
int getopposingendf(int start) {
	int val = 0;
	string oppo = "end";
	string line;
	for (int i = start; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if (line.starts_with("for every ") || line.starts_with("for ") || line.starts_with("if ") || line.starts_with("while ") || line.starts_with("define ")) {
			val += 1;
		}
		else if (line == oppo) {
			val -= 1;
		}
		if (val == 0) {
			return i;
		}
	}
	return -1;
}
int getamountofelseifs(int lineofif) {
	int val = 0;
	int end = getopposingend(lineofif);
	bool ignore = false;
	string oppo = "end else if ";
	string line;
	for (int i = lineofif + 1; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if (line.starts_with("if ")) {
			ignore = true;
		}
		else if (line.starts_with("end") && line.find("else") == string::npos && ignore) {
			ignore = false;
		}
		else if (line.starts_with("end") && line.find("else") == string::npos) {
			return val;
		}
		else if (line.starts_with("end else if ") && !ignore) {
			val += 1;
		}
	}
	return val;
}
int getopposingelseif(int start) {
	int val = 0;
	int skip = 0;
	string oppo = "end else if ";
	string line;
	for (int i = start; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if (line.starts_with("if ")) {
			val += 1;
			skip += getamountofelseifs(i);
		}
		else if (line.starts_with(oppo) && !skip) {
			val -= 1;
		}
		else if (line.starts_with(oppo) && skip) {
			skip -= 1;
		}
		if (val == 0) {
			return i;
		}
	}
	return -1;
}
int getopposingelse(int start) {
	int val = 1;

	string oppo = "end else";
	string line;
	for (int i = start + 1; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if ( line.starts_with("if ") && getopposingelse(i) != -1) {
			val += 1;
		}
		else if (line == "end" && getopposingend(start) == i) {
			return -1;
		}
		else if (line.starts_with("end else") && !line.ends_with(")")) {
			val -= 1;
		}
		if (val == 0) {
			return i;
		}
	}
	return -1;
}
int runcodetoend(int start, vector<rfppvar>& variablelis) {
	int val = 0;
	string oppo = "end";
	string line;
	int oldi = start;
	string bollocks;
	for (int i = start; i < lines.size(); i++) {
		line = removewhitespace(lines[i]);
		if (line.starts_with("for every ") || line.starts_with("for ") || line.starts_with("if ") || line.starts_with("while ")) {
			val += 1;
		}
		else if (line.starts_with(oppo)) {
			val -= 1;
		}
		if (val == 0) {
			return i;
		}
		if (i != start) {
			oldi = i;
			i = runline(line, variablelis, i, bollocks);
		}
		if (oldi != i) {
			val -= 1;
		}
		
	}
	return -1;
}
int endofword(string operation) {
	int i = 0;
	bool start = false;
	for (auto character : operation) {
		if (!start && isvalidvariablecharacter(character)) {
			start = true;
		} else 
		if (start && !isvalidvariablecharacter(character)) {
			return i - 1;
		}
		
		else if (character == operation[operation.length() - 1] && i == operation.length() - 1) {
			return i;
		}
		i++;
	}
	return -1;
}
int endofqword(string operation) {
	int i = 0;
	bool start = false;
	bool ignore = false;
	for (auto character : operation) {
		
		if (!start && (isvalidvariablecharacter(character) || character == '"')) {
			start = true;
			if (character == '"') {
				ignore = !ignore;
			}
		}
		else
			if (start && character == '"') {
				ignore = !ignore;
			}
			if (start && ((!isvalidvariablecharacter(character) && character != '"') && !ignore)) {
				return i - 1;
			}

			else if (character == operation[operation.length() - 1] && i == operation.length() - 1) {
				return i;
			}
		i++;
	}
	return -1;
}
/*bool isoperation(string value) {
	for (char character : value) {
		if (character != '1' && character != '2' && character != '3' && character != '4' && character != '5' && character != '6' && character != '7' && character != '8' && character != '9' && character != '*' && character != '/' && character != '+' && character != '-' && character != '(' && character != ')' && character != ' ' && character != '^' && character != '.' && character != '0') {
			return false;
		}
	}
	return true;
}*/
int getvar(string name, vector<rfppvar>& variablelis) {
	int i = 0;
	for (rfppvar variable : variablelis) {
		if (variable.name == name) {
			return i;
		}
		i++;
	}
	return -1;
}
bool isoperation(string value, vector<rfppvar>& variablelis) {
	if ((value.find('/') != string::npos || value.find('*') != string::npos || value.find('+') != string::npos || value.find('-') != string::npos || value.find('(') != string::npos || value.find(')') != string::npos) && value.find("\"") == string::npos && !isfunction(value, variablelis)) {
		return true;
	}
	return false;
}
int getamountofinstring(string value) {
	int pos = 0;
	pos = value.find("\"", pos);
	int i = 0;
	while (pos != string::npos) {
		i++;
		pos += 1;
		pos = value.find("\"", pos);
	
	}
	return i;
}
bool isbooloperation(string value) {
	int i = getamountofinstring(value);
	if ((value.find("&&") != string::npos || value.find("||") != string::npos || value.find("==") != string::npos || value.find("!=") != string::npos || value.find("true") != string::npos || value.find("false") != string::npos) && ((value.starts_with("\"") && value.ends_with("\"") && i > 2) || !(value.starts_with("\"") && value.ends_with("\"")))) {
		return true;
	}
	return false;
}
string getoperationresult(string operation, vector<rfppvar>& variablelis) {
	operation = removespaces(operation);
	string::size_type startval;
	int endval;
	bool done = false;
	while (!done) {
		startval = operation.find("(");
		endval = getopposing('(', operation, startval);
		if (startval != string::npos) {
			string val = operation.substr(startval + 1, endval - startval - 1);
			auto tom = getoperationresult(val, variablelis);
			operation.replace(startval, endval - startval + 1, tom);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		int location = findvarstart(operation);
		if (location != -1) {
			auto endofwordd = endofword(operation);
			string varname = operation.substr(location, endofwordd - location + 1);
			operation.replace(location, endofwordd + 1, variablelis[getvar(varname, variablelis)].value);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("^");
		if (startval != string::npos) {
			int start = startofnum(operation, '^');
			string number = operation.substr(start, startval - start);
			double inumber = stod(number);
			int endofnuum = endofnum(operation, '^');
			operation.replace(start, endofnuum, to_string(pow(inumber, stod(operation.substr(startval + 1, startval - endofnuum)))));
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("*");
		if (startval != string::npos) {
			int start = startofnum(operation, '*');
			string number = operation.substr(start, startval - start);
			double inumber = stod(number);
			int endofnuum = endofnum(operation, '*');
			operation.replace(start, endofnuum, to_string(inumber*stod(operation.substr(startval + 1, startval - endofnuum))));
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("/");
		if (startval != string::npos) {
			int start = startofnum(operation, '/');
			string number = operation.substr(start, startval - start);
			double inumber = stod(number);
			int endofnuum = endofnum(operation, '/');
			operation.replace(start, endofnuum, to_string(inumber/stod(operation.substr(startval + 1, startval - endofnuum))));
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("+");
		if (startval != string::npos) {
			int start = startofnum(operation, '+');
			string number = operation.substr(start, startval - start);
			double inumber = stod(number);
			int endofnuum = endofnum(operation, '+');
			operation.replace(start, endofnuum, to_string(inumber+stod(operation.substr(startval + 1, startval - endofnuum))));
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("-");
		if (startval != string::npos && startval != 0) {
			int start = startofnum(operation, '-');
			string number = operation.substr(start, startval - start);
			double inumber = stod(number);
			int endofnuum = endofnum(operation, '-');
			auto asdf = operation.substr(startval + 1, startval - endofnuum);	
			string numberasdf = to_string(inumber - stod(operation.substr(startval + 1, startval - endofnuum)));
			operation.replace(start, endofnuum, numberasdf);
		}
		else {
			done = true;
		}
	}
	startval = operation.find('.');
	if (startval != string::npos && operation.substr(startval, 3) == ".00") {
		operation = operation.substr(0, startval);

	}
	return operation;
}
void reporterror(int errorcode) {
	cerr << "Something went wrong! Error code " << errorcode << " at \"" << mostrecentline << "\" on line number " << currentline;
	
}
string getvaluefromlist(rfppvar& list, int index, vector<rfppvar>& variablelis) {
	string values = getlistvalues(list.value, variablelis);
	values = values.substr(1, values.length() - 2);
	return seperateby(values, ',', true)[index];
}
vector<string> unpacklist(rfppvar& list) {
	return seperateby(list.value.substr(1, list.value.length()-2), ',',true);
}
vector<string> unpacklist(string listdata) {
	return seperateby(listdata.substr(1, listdata.length() - 2), ',', true);
}
int getlengthoflist(rfppvar& list) {
	return countamount(list.value, ',') + 1;
}
void packlist(rfppvar& list, vector<string> unpacked) {
	string retvalue = "{";
	for (auto item : unpacked) {
		retvalue += item + ",";
	}
	retvalue.pop_back();
	retvalue += "}";
	list.value = retvalue;
}
void setvalueinlist(rfppvar& list, int index, string value) {
	int amount = getlengthoflist(list);
	if (amount > index + 1) {
		reporterror(5);
	}
	else {
		auto lists = unpacklist(list);
		lists[index] = value;
		packlist(list, lists);
	}
}
bool isaccessinglist(string line, vector<rfppvar>& variablelis) {
	int varnum = getvar(seperateby(line, '[')[0], variablelis);
	if (line.find('[') && (varnum  != -1)) {
		rfppvar& variable = variablelis[varnum];
		if (variable.rfppclass == "rfpp-list") {
			return true;
		}
	}
	return false;
}

int gettype(string value, vector<rfppvar>& variablelis) {
	int type = 0;
	if (value.starts_with("\"") && value.ends_with("\"") && getamountofinstring(value) == 2) { //check if its a string
		type = 3; //string
	}
	
	else if (isoperation(value, variablelis) || isnumber(value)) {
		type = 1;
	}
	else if (value.starts_with("{") && value.ends_with("}")) {
		type = 4;
	}
	else if (isbooloperation(value)) {
		type = 2;
	}
	
	else if (getvar(value, variablelis) != -1) {
		type = 5;
	}
	else if (isaccessinglist(value, variablelis)) {
		type = 6;
	}
	else if (isfunction(value, variablelis)) {
		type = 7;
	}
	else {
		reporterror(4);
	}
	return type;
}
int startofword(string line) {
	int i = 0;
	for (auto character : line) {
		if (isvalidvariablecharacter(character)) {
			return i;
		}
		i++;
	}
	return -1;
}
int startofqword(string line) {
	int i = 0;
	for (auto character : line) {
		if (isvalidvariablecharacter(character) || character == '"' || character == ' ') {
			return i;
		}
		i++;
	}
	return -1;
}
string gethash(string line) {
	bool hashing = false;
	string retvalue = "#";
	for (auto character : line) {
		if (character == '#') {
			hashing = true;
		} else
		if (hashing) {
			if (isnumber(character)) {
				retvalue += character;
			}
			else {
				return retvalue;
			}
		}
	}
	return retvalue;
}
int getvalueofhash(string hash) {
	if (hash.starts_with('#')) {
		return stoi(hash.substr(1)) - 3;
	}
	return -1;
}
bool isspecialchar(char character) {
	switch (character) {
	case '&':
		return true;
	case '|':
		return true;
	case ')':
		return true;
	case '(':
		return true;
	case '=':
		return true;
	}
	return false;
}
string getrightof(string line, string value) {
	int location = line.find(value) + value.length() - 1;
	int i = 0;
	string retvalue = "";
	for (auto character : line) {
		bool isspecial = isspecialchar(character);
		if (i > location) {
			if (!isspecial) {
				retvalue += character;
			}
			else if (isspecial || i == line.length()-1) {
				return retvalue;
			}
		}
		
		i++;
	}
	return retvalue;
}
string getvardataifany(string name, vector<rfppvar>& variablelis) {
	int index = getvar(name, variablelis);
	if (index != -1) {
		return variablelis[index].value;
	} 
	vector<string> split = seperateby(name, '[');
	int varnum = getvar(split[0], variablelis);
	
	if (varnum != -1) {
		int varvarnum = stoi(split[1].substr(0, split[1].length() - 1));
		string retvalue = getvaluefromlist(variablelis[varnum], varvarnum, variablelis);;
		int i = 0;
		for (auto each : split) {
			if (i > 1 ) {
				int varvarnum = stoi(each.substr(0, each.length() - 1));
				rfppvar list;
				list.value = retvalue;
				retvalue = getvaluefromlist(list, varvarnum, variablelis);
			}
			i++;
		}
		return retvalue;
	}
	split = seperateby(name, '(');
	varnum = getfunc(split[0]);
	if (varnum != -1) {
		return runfunc(varnum, '(' + split[1]);
	}
	if (name.starts_with('{') && name.ends_with('}')) {
		string values = getlistvalues(name, variablelis);
		return values;
	}
	return name;
}
string getleftof(string line, string value) {
	int location = line.find(value);
	int lastspecial = -1;
	int i = 0;
	for (auto character : line) {
		if (i == location) {
			i++;
			break;
		} else 
		if (isspecialchar(character)) {
			lastspecial = i;
		} 
		i++;
	}
	return line.substr(lastspecial + 1, location - 1 - lastspecial);
	
}
string getboolresult(string operation, vector<rfppvar>& variablelis) {
	/*if (operation == "true" || operation == "false") {
		return operation;
	}
	string left = before(operation, "==");
	string right = after(operation, "==");
	if (left != "" && right != "") {

	}*/
	vector<string> strings;
	operation = removespaces(operation, true);
	string::size_type startval;
	int endval;
	bool done = false;
	/*while (!done) {
		startval = operation.find("(");
		endval = getopposing('(', operation, startval);
		if (startval != string::npos) {
			string val = operation.substr(startval + 1, endval - startval - 1);
			auto tom = getoperationresult(val, variablelis);
			operation.replace(startval, endval - startval + 1, tom);
		}
		else {
			done = true;
		}
	}
	done = false;*/
	int i = 3;
	
	while (!done) {
		startval = operation.find("{");
		endval = getopposing('{', operation, startval);
		if (startval != string::npos) {
			string val = operation.substr(startval + 1, endval - startval - 1);
			replaced.push_back('{' + val+ '}');
			operation.replace(startval, endval - startval + 1, "#" + to_string(i));
			i++;
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = startofqword(operation);
		if (startval != -1) {
			string word = operation.substr(startval, endofqword(operation) + 1 - startval);
			if (word == "true") {
				operation.replace(startval, endofqword(operation) + 1 - startval, "1");
			}
			else if (word == "false") {
				operation.replace(startval, endofqword(operation) + 1 - startval, "0");
			}
			else {
				replaced.push_back(word);
				operation.replace(startval, endofqword(operation)+ 1 - startval, "#" + to_string(i));

				i++;
			}
			
			
			
		}
		else {
			done = true;
		}
	}
	while (!done) {
		startval = operation.find("true");
		if (startval != string::npos) {
			operation.replace(startval, 4, "1");
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("false");
		if (startval != string::npos) {
			operation.replace(startval, 4, "1");
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("(");
		endval = getopposing('(', operation, startval);
		if (startval != string::npos) {
			string val = operation.substr(startval + 1, endval - startval - 1);
			auto tom = getboolresult(val, variablelis);
			operation.replace(startval, endval - startval + 1, tom);
		}
		else {
			done = true;
		}
	}
	done = false;
	/*while (!done) {
		startval = operation.find("#");
		
		if (startval != string::npos) {
			string hash = gethash(operation);
			auto replacedtext = replaced[getvalueofhash(hash)];
			operation.replace(startval, hash.length(), replacedtext);
			cout << operation;
		}
		else {
			done = true;
		}
	}*/
	done = false;
	while (!done) {
		startval = operation.find("==");

		if (startval != string::npos) {
			string left = getleftof(operation, "==");
			string right = getrightof(operation, "==");
			int leftl = left.length();
			int rightl = right.length();
			string replacedtext;
			int hvall = getvalueofhash(left);
			if (hvall != -1) {
				left = getvardataifany(replaced[hvall], variablelis)  ;
			}
			int hvalr = getvalueofhash(right);
			if (hvalr != -1) {
				right = getvardataifany(replaced[hvalr], variablelis);
			}
			if (left == right) {
				replacedtext = "1";
			}
			else {
				replacedtext = "0";
			}


			operation.replace(startval - (leftl), 2 + (rightl + leftl), replacedtext);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("||");

		if (startval != string::npos) {
			string left = getleftof(operation, "||");
			string right = getrightof(operation, "||");
			int leftl = left.length();
			int rightl = right.length();
			string replacedtext;
			int hvall = getvalueofhash(left);
			if (hvall != -1) {
				left = getvardataifany(replaced[hvall], variablelis);
			}
			int hvalr = getvalueofhash(right);
			if (hvalr != -1) {
				right = getvardataifany(replaced[hvalr], variablelis);
			}
			if (left == "1" || right == "1") {
				replacedtext = "1";
			}
			else {
				replacedtext = "0";
			}


			operation.replace(startval - (leftl), 2 + (rightl + leftl), replacedtext);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("&&");

		if (startval != string::npos) {
			string left = getleftof(operation, "&&");
			string right = getrightof(operation, "&&");
			int leftl = left.length();
			int rightl = right.length();
			string replacedtext;
			int hvall = getvalueofhash(left);
			if (hvall != -1) {
				left = getvardataifany(replaced[hvall], variablelis);
			}
			int hvalr = getvalueofhash(right);
			if (hvalr != -1) {
				right = getvardataifany(replaced[hvalr], variablelis);
			}
			if (left == "1" &&  right == "1") {
				replacedtext = "1";
			}
			else {
				replacedtext = "0";
			}
				

			operation.replace(startval - (leftl), 2 + (rightl + leftl), replacedtext);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("!=");

		if (startval != string::npos) {
			string left = getleftof(operation, "!=");
			string right = getrightof(operation, "!=");
			int leftl = left.length();
			int rightl = right.length();
			string replacedtext;
			int hvall = getvalueofhash(left);
			if (hvall != -1) {
				left = getvardataifany(replaced[hvall], variablelis);
			}
			int hvalr = getvalueofhash(right);
			if (hvalr != -1) {
				right = getvardataifany(replaced[hvalr], variablelis);
			}
			if (left != right) {
				replacedtext = "1";
			}
			else {
				replacedtext = "0";
			}


			operation.replace(startval - (leftl), 2 + (rightl + leftl), replacedtext);
		}
		else {
			done = true;
		}
	}
	done = false;
	while (!done) {
		startval = operation.find("#");

		if (startval != string::npos) {
			int hvall = getvalueofhash(operation);
			if (hvall != -1) {
				operation = getvardataifany(replaced[hvall], variablelis);
			}
		}
		else {
			done = true;
		}
	}

	
	return operation;
	
}
string removenonstringspaces(string line) {
	bool isquotes = false;
	string retvalue = "";
	for (auto character : line) {
		if (character == '\"') {
			isquotes = !isquotes;
		}
		if (character != ' ' || isquotes) {
			retvalue += character;
		}
	}
	return retvalue;
}



string getlistvalues(string line, vector<rfppvar>& variablelis) {
	string sub = line.substr(1, line.length() - 2);
	string retvalue = "";
	for (auto value : seperateby(sub, ',', true)) {
		value = removewhitespace(value);
		int type = gettype(value, variablelis);
		switch (type) {
		case 1:
			retvalue += getoperationresult(value, variablelis) + ",";
			break;
		case 2:
			replaced.clear();
			retvalue += getboolresult(value, variablelis) + ",";
			break;
		case 3:
			retvalue += value + ",";
			break;
		case 4:
			retvalue += getlistvalues(value, variablelis) + ",";
			break;
		case 5:
			retvalue += getvardataifany(value, variablelis) + ",";
			break;
		case 6:
			retvalue += getvardataifany(value, variablelis) + ",";
			break;
		}
	}
	retvalue.pop_back();
	retvalue = "{" + retvalue + "}";
	return retvalue;
}

string getrfppclass(int type) {
	switch (type) {
	case 1:
			return "rfpp-number";
	case 2:
		return "rfpp-bool";

	case 3:
		return "rfpp-string";
	case 4:
		return "rfpp-list";
	}
}

bool setvariable(vector<rfppvar>& variablelis, string line="", string name = "", string description = "", string value = "", int type=0, string rfppclass="rfppbase", bool makevar = true) {
	//1 = int
	//2 = bool
	//3 = string
	//4 = list
	//5 = another variable
	if (line == "" && name =="") {
		reporterror(1);
		return false;
	}
	else if (line != "") {
		int endofname = line.find(" ");
		name = line.substr(0, endofname);
		int startofval = endofname + 3;
		value = line.substr(startofval, line.length());
		type = gettype(value, variablelis);
	}
	if (!type) {
		type = gettype(value, variablelis);
	}
	rfppvar variable;
	int existingnum = getvar(name, variablelis);
	if (existingnum != -1) {
		int num;
		switch (type) {
		case 0:
			reporterror(2);
			return false;
			break;
		case 1:
			variablelis[existingnum].value = getoperationresult(removespaces(value), variablelis);
			variablelis[existingnum].type = 1;
			break;
		case 2:
			replaced.clear();
			variablelis[existingnum].value = getboolresult(removespaces(value), variablelis);
			variablelis[existingnum].type = 2;
			break;
		case 3:
			variablelis[existingnum].value = value;
			variablelis[existingnum].type = 3;
			break;
		case 4:
			variablelis[existingnum].value = value;
			variablelis[existingnum].type = 4;
			break;
		case 5:
			num = getvar(value, variablelis);
			variablelis[existingnum] = variablelis[num];

			break;
		case 6:
			variablelis[existingnum].value = getvardataifany(value, variablelis);
			variablelis[existingnum].type = gettype(variablelis[existingnum].value, variablelis);
			variablelis[existingnum].rfppclass = getrfppclass(variablelis[existingnum].type);
			break;
		case 7:
			variablelis[existingnum].value = getvardataifany(value, variablelis);
			variablelis[existingnum].type = gettype(variablelis[existingnum].value, variablelis);
			variablelis[existingnum].rfppclass = getrfppclass(variablelis[existingnum].type);
			break;
		}
		makevar = false;
	}
	else {
		int num;
		switch (type) {
		case 0:
			reporterror(3);
			return false;
			break;
		case 1:
			variable.type = 1;
			variable.name = name;
			variable.description = "";
			variable.value = getoperationresult(removespaces(value), variablelis);

			variable.rfppclass = "rfpp-number";
			break;
		case 2:
			variable.type = 2;
			variable.name = name;
			variable.description = "";
			replaced.clear();
			variable.value = getboolresult(removespaces(value), variablelis);
			variable.rfppclass = "rfpp-bool";
			break;
		case 3:
			variable.type = 3;
			variable.name = name;
			variable.description = "";
			variable.value = value;
			variable.rfppclass = "rfpp-string";
			break;
		case 4:
			variable.type = 4;
			variable.name = name;
			variable.description = "";
			variable.value = getlistvalues(removenonstringspaces(value), variablelis);
			variable.rfppclass = "rfpp-list";
			break;
		case 5:
			num = getvar(value, variablelis);
			variable.name = name;
			variable.value = variablelis[num].value;
			variable.type = variablelis[num].type;
			variable.rfppclass = variablelis[num].rfppclass;
			break;
		case 6:
			variable.type = 6;
			variable.name = name;
			variable.description = "";
			variable.value = getvardataifany(value, variablelis);
			variable.rfppclass = getrfppclass(gettype(variable.value, variablelis));
			break;
		case 7:
			variable.type = 7;
			variable.name = name;
			variable.description = "";
			variable.value = getvardataifany(value, variablelis);
			variable.rfppclass = getrfppclass(gettype(variable.value, variablelis));
			break;
		}
		
	}
	if (makevar) {
		variablelis.push_back(variable);
	}
	return true;

}


vector<rfppvar> getparameters(string params) {
	vector<rfppvar> retvalue;
	for (auto param : seperateby(params, ',')) {
		rfppvar addvalue;
		addvalue.name = removespaces(param);
		retvalue.push_back(addvalue);
	}
	if (retvalue.empty()) {
		rfppvar addvalue;
		addvalue.name = removespaces(params);
		retvalue.push_back(addvalue);
	}
	return retvalue;
}
void makefunction(int i, string line) {
	string function = after(line, " ");
	string name = before(function, "(");
	string parameters = before(after(line, "("), ")");
	rfppfunction func;
	func.name = name;
	func.startline = i;
	func.parameters = getparameters(parameters);
	func.endline = getopposingend(i);
	functionlist.push_back(func);
}

int getfuncbyendlinenum(int endline) {
	int i = 0;
	for (auto func : functionlist) {
		if (func.endline == endline) {
			return i;
		}
	}
	return -1;
}
void applyend(int linenum) {
	if (endneeded.size() > 0 && getfuncbyendlinenum(linenum) != -1) {
		endneeded.pop_back();
		run = true;
	};
	
	
}



int runline(string line, vector<rfppvar>& variablelis, int i, string& returnvalue) {
	line = removewhitespace(line);
	mostrecentline = line;
	currentline = i;
	if (line.find(" = ") != string::npos) {
		if (run) {
			setvariable(variablelis, line);
		}


	}
	else if (line.starts_with("if ")) {
		if (run) {
			replaced.clear();
			int num = stoi(getboolresult(before(after(line, "("), ")"), variablelis));
			int elseif = getopposingelseif(i);
			int elsee = getopposingelse(i);
			if (num) {
				runcodetoend(i, variablelis);
				i = getopposingendf(i);
				return i;
			}
			else if (elseif != -1) {
				while (elseif != -1) {
					
					if (stoi(getboolresult(before(after(lines[elseif], "("), ")"), variablelis))) {
						runcodetoend(elseif, variablelis);
						i = getopposingendf(i);
						return i;
					}
					else {
						elseif = getopposingelseif(elseif);
					}
					
				}
			}
			if (elsee != -1) {
				runcodetoend(elsee, variablelis);
				i = getopposingendf(i);
				return i;
			}
			
			int op = getopposingend(i);
			return op;
		}


	}
	else if (line == "end") {

		applyend(i);
	}

	else if (line.starts_with("for every ")) {
		if (run) {
			replaced.clear();
			string indvar = after(before(line, " in"), "for every ");
			string list = after(line, "in ");
			string listdata = getvardataifany(list, variablelis);
			vector<string> listlist = unpacklist(listdata);
			int x = 0;
			for (auto data : listlist) {
				setvariable(variablelis, "", indvar, "", listlist[x]);
				runcodetoend(i, variablelis);
				x++;
			}
			return getopposingend(i);
			
		}

	}
	else if (line.starts_with("while ")) {
		if (run) {
			replaced.clear();
			string content = before(after(line, "("), ")");
			replaced.clear();
			if (stoi(getboolresult(content, variablelis))) {
				runcodetoend(i, variablelis);
				while (stoi(getboolresult(content, variablelis))) {
					replaced.clear();
					runcodetoend(i, variablelis);
				}
			}
			return getopposingend(i);
		}

	}
	else if (line.starts_with("define ")) {

		makefunction(i, line);
		endneeded.push_back(i);
		run = false;
	}
	else if (line.starts_with("print ")) {
		if (run) {
			cout << getvardataifany(after(line, " "), variablelis) << "\n";
		}

	} else if (line.starts_with("return ")) {
		if (run) {
			returnvalue = getvardataifany(line.substr(7), variablelis);
		}
	}
	
	else {
		if (run) {
			int func = getfunc(before(line, "("));
			if (func != -1) {
				runfunc(func, line);
			}
		}

	}
	return i;
}
string runfunc(int func, string ogline) {
	rfppfunction function = functionlist[func];
	string line;
	vector<rfppvar> funcvarlist = function.parameters;
	string returnvalue = "";
	int i = 0;
	for (auto param : seperateby(before(after(ogline, "("), ")"), ',')) {
		int varnum = getvar(removespaces(param), variablelist);
		if (varnum != -1) {
			funcvarlist[i].value = variablelist[varnum].value;
		}
		else {
			funcvarlist[i].value = getvardataifany(removespaces(param), variablelist);
			funcvarlist[i].type = gettype(removespaces(param), variablelist);
			funcvarlist[i].rfppclass = getrfppclass(funcvarlist[i].type);
		}

		i++;
	}
	bool norun = false;
	for (int i = function.startline + 1; i != function.endline; i++) {
		line = lines[i];
		line = removewhitespace(line);
		 if (line.starts_with("return ")) {
			if (run) {
				returnvalue = getvardataifany(line.substr(7), funcvarlist);
				norun = true;
			}
		 }
		 else if (!norun && returnvalue == "") {
			 i = runline(line, funcvarlist, i, returnvalue);
		 }
		 else if (norun || returnvalue != "") {
			 break;
		 }
		
	}
	return returnvalue;
}
int main()
{
	string filedir = "C:\\Users\\egg\\source\\repos\\CMakeProject1\\CMakeProject1\\HelloWorld.rfp";
	ifstream inputFile(filedir);
	if (!inputFile.is_open()) {
		cerr << "Shit went wrong, man.";
		return 1;
	}
	string linee;
	
	while (getline(inputFile, linee)) {
		lines.push_back(linee);
	}
	int i = 0;
	string line;
	string idk;
	for (i = 0; i < lines.size(); i++) {
		line = lines[i];
		//for every line, essentially
		line = removewhitespace(line);
		i = runline(line, variablelist, i, idk);
	}
	return 0;
}


/* define range(number) 
	i = 3
	x = 1
	c = 2
	v = 3
	b = number
	if (1)
		print "hi!"
	end
	return {i,x,c,v,b}



end




num = 3
num = num - 1
valtoprint = range(num)

for every i in valtoprint
	print i
end

valtoprint = range(3)

for every i in valtoprint
	print i
end
*/