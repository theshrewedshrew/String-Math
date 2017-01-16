#include<iostream>
#include<string>
#include <algorithm>
#include <vector>
using namespace std;
const string T = "2000000";
const int DecimalAccuracy = 2000000;
#pragma region PROTOTYPES
// COMPARE OPERATORS 
bool isLessThan(string, string);
bool isGreaterThan(string, string);
bool isEqualTo(string, string);


// MATH OPERATORS
string ADD(string, string);
string SUB(string, string);
string MULTI(string, string);
string DIVIDE(string, string);



// MECHANICS
void trim(string&);
void removeDecimal(string &);
void replaceDecimal(string &, int);
int modulo(int, int);
int Decimal(string);
int Shift(string&, string&);
string Reverse(string);
string ZeroSpawn(int);

#pragma endregion

void main(){
	cout << boolalpha;
	string str = "0100000000";
	trim(str);
	cout << DIVIDE("60", "3") << endl;
	cout << SUB("10000" , "1") << endl;
	cout << MULTI(".2", "42") << endl;
	system("pause");
}
#pragma region MECHANICS
// needed for negative modulus
int modulo(int a, int b) { 
	return a >= 0 ? a % b : (b - abs(a%b)) % b; 
} 
int Shift(string &x, string&y){
	int SHIFT;
	int SHIFTX = Decimal(x); // SET THE NUMBER OF DECIMAL PLACES NEEDED 
	int SHIFTY = Decimal(y); // SET THE NUMBER OF DECIMAL PLACES NEEDED

	if (abs(SHIFTX - SHIFTY) > 0){
		if (SHIFTX > SHIFTY){
			y += ZeroSpawn(abs(SHIFTX - SHIFTY));
			SHIFT = SHIFTX;
		}
		else
			x += ZeroSpawn(abs(SHIFTX - SHIFTY));
		SHIFT = SHIFTY;

	}
	else
		SHIFT = SHIFTX;
	return SHIFT;
}
int Decimal(string str){
	int npos = str.find('.');
	if (npos < 0) // IF no Decimal then npos will be less than zero
		return 0;
	return str.length() - npos - 1; // TAKES str.length() subtracts the location of the '.' and then subtracts 1 from that as well. 
	
}
void removeDecimal(string & s){
	s.erase(remove_if(s.begin(), s.end(), &ispunct), s.end());
}
void replaceDecimal(string & s, int SHIFT){
	if (SHIFT == 0)
		return;

	s = s.substr(0, s.length() - SHIFT) + "." + s.substr(s.length() - SHIFT);
}
void trim(string &str){
	bool neg = false;
	while (str[0] == '-'){
		str = str.substr(1);
		neg = !neg;
	}
	while (str[0] == '0'){
		if (str.length() == 1)
			break;
		str = str.substr(1);
	}
	if (Decimal(str) != 0)
		while (str[str.length() - 1] == '0' || str[str.length() - 1] == '.') {
		if (str.length() == 1)
			break;
		str = str.substr(0, str.length() - 1);
		}
	if (str == "." || str == "0"){
		str = "0";
		return;
	}
	if (str[0] == '.'){
		str = "0" + str;
	}
	if (neg){
		str = "-" + str;
	}
	if (str[str.length() - 1] == '.')
		str = str.substr(0, str.length() - 1);
	return;
}
string ZeroSpawn(int x){
	string str = "";
	for (int i = 0; i < x; i++)
		str += "0";
	return str;
}
string Reverse(string x){
	string str = "";
	while (!x.empty()){
		str += x.back();
		x.pop_back();
	}
	return str;
}


#pragma endregion

#pragma region MATH
string ADD(string x, string y){
	// Check x and y for positive and negative
	if (x[0] == '-' || y[0] == '-'){
		if (x[0] == '-' && y[0] == '-') // both neg then neg SUM
			return '-' + ADD(x.substr(1), y.substr(1));
		else if (x[0] == '-'){
			return SUB(y, x.substr(1)); // x neg then really y - x 
		}
		else
			return SUB(x, y.substr(1)); // y neg then really x - y
	}
	// Check x and y for decimals
	int SHIFT = Shift(x, y);
	removeDecimal(x);
	removeDecimal(y);
	int carry = 0;
	int endX = 0;
	int endY = 0;
	string result = "";
	while (carry != 0 || !x.empty() && !y.empty()){ // this will continually pop the end character off the give strings while it needs too. Once Carry = 0 and both are empty or one it will just add the remainder to the begining of the result string
		if (!x.empty()){
			endX = x.back() - 48;
			x.pop_back();
		}
		if (!y.empty()){
			endY = y.back() - 48;
			y.pop_back();
		}
		carry += endX + endY; // ADDITIVE of the Carry Values
		endX = endY = 0; // Set endX and endY back to zero so that in subsequent uses they retain integrity
		result = (char)((carry % 10) + 48) + result; // appends the new placement on to the string
		carry -= carry % 10;
		carry /= 10;
	}
	if (!x.empty()){
		result = x + result;
	}
	if (!y.empty()){
		result = y + result;
	}
	replaceDecimal(result, SHIFT);
	trim(result);
	return result;
}
string SUB(string x, string y){
	// Check x and y for positive and negative
	if (x[0] == '-' || y[0] == '-'){
		if (x[0] == '-' && y[0] == '-') // both neg then -x - (-y) => -x + y => y - x or sub(y,x)
			return SUB(y.substr(1), x.substr(1));
		else if (x[0] == '-'){
			return "-" + ADD(y, x.substr(1)); // x neg then really - x - y => - (x + y) 
		}
		else
			return ADD(x, y.substr(1)); // y neg then really x - (-y) => x + y
	}
	// Check x and y for decimals
	bool isNeg = false;
	if (isLessThan(x, y)){
		isNeg = true;
		swap(x, y);
	}
	int SHIFT = Shift(x, y);
	int carry = 0;
	int endX = 0;
	int endY = 0;
	string result = "";
	while (carry != 0 || !x.empty() && !y.empty()){ // this will continually pop the end character off the give strings while it needs too. Once Carry = 0 and both are empty or one it will just add the remainder to the begining of the result string
		if (!x.empty()){
			endX = x.back() - 48;
			x.pop_back();
		}
		if (!y.empty()){
			endY = y.back() - 48;
			y.pop_back();
		}
		carry = endX - (endY + carry); // ADDITIVE of the Carry Values
		endX = endY = 0; // Set endX and endY back to zero so that in subsequent uses they retain integrity
		result = (char)((modulo(carry, 10)) + 48) + result; // appends the new placement on to the string
		carry -= modulo(carry, 10);
		carry /= -10;
	}
	if (!x.empty()){
		result = x + result;
	}
	trim(result);
	if (isNeg){
		result = "-" + result;
	}
	return result;
}
string MULTI(string x, string y){
	// Check x and y for positive and negative
	if (x[0] == '-' || y[0] == '-'){
		if (x[0] == '-' && y[0] == '-') // both neg then neg SUM
			return MULTI(x.substr(1), y.substr(1));
		else if (x[0] == '-'){
			return '-' + MULTI(y, x.substr(1)); // x neg then really y - x 
		}
		else
			return '-' + MULTI(x, y.substr(1)); // y neg then really x - y
	}
	// Check x and y for decimals
	int SHIFTX = Decimal(x); // SET THE NUMBER OF DECIMAL PLACES NEEDED 
	int SHIFTY = Decimal(y); // SET THE NUMBER OF DECIMAL PLACES NEEDED
	int SHIFT = SHIFTX + SHIFTY;
	removeDecimal(x);
	removeDecimal(y);
	int carry = 0;
	int endX = 0;
	int endY = 0;
	string result = "";
	string hold = "0";
	string mult = x;
	int count = 0;
	while (!y.empty()){ // this will continually pop the end character off the give strings while it needs too. Once Carry = 0 and both are empty or one it will just add the remainder to the begining of the result string
		endY = y.back() - 48;
		y.pop_back();
		result = "";
		if (endY != 0)
			mult = x;
		while (!mult.empty()){
			endX = mult.back() - 48;
			mult.pop_back();
			carry += endX * endY; // ADDITIVE of the Carry Values
			endX = endY = 0; // Set endX and endY back to zero so that in subsequent uses they retain integrity
			result = (char)((carry % 10) + 48) + result; // appends the new placement on to the string
			carry -= carry % 10;
			carry /= 10;
		}
		result = result + ZeroSpawn(count++);
		hold = ADD(hold, result);
	}
	result = hold;
	replaceDecimal(result, SHIFT);
	trim(result);
	return result;
}
string DIVIDE(string x, string y){
	
	// Check x and y for positive and negative
	if (x[0] == '-' || y[0] == '-'){
		if (x[0] == '-' && y[0] == '-') // both neg then neg SUM
			return DIVIDE(x.substr(1), y.substr(1));
		else if (x[0] == '-'){
			return '-' + DIVIDE(x.substr(1), y); // x neg then really y - x 
		}
		else
			return '-' + DIVIDE(x, y.substr(1)); // y neg then really x - y
	}
	// 
/*
	return "";
	*/


	string hold = "";
	string Remainder = " R : ";
	// x divided by y

	trim(x);
	trim(y);
	if (isEqualTo(y, "0")){
		return "Cannot implicitly divide by zero.";
	}
	string R = "0";
	string Solution = "";
	int xLen = x.length();
	for (int i = 0; i < xLen; i++){
		R = R + x[i];
		int count = 0;
		while (isLessThan(y, R)){
			count++;
			//	cout << "R : " << R << " y : " << y << " = " ;
			R = SUB(R, y);
			//	cout << R << endl;
		}
		if (isEqualTo(y, R)){
			//	cout <<" EqualTo " << endl;
			R = "0";
			count++;
		}
		//	cout << Solution << endl;
		Solution = Solution + (char)(count + 48);
		//	cout << Solution << endl;
	}

	while (Solution[0] == '0'){
		if (Solution.length() == 1){
			break;
		}
		//	cout << Solution << " : " << Solution.substr(1) << endl;
		Solution = Solution.substr(1);
	}
	while (R[0] == '0'){
		if (R.length() == 0){
			break;
		}
		else if (R.length() == 1){
			break;
		}
		R = R.substr(1);
	}

	if (R == "0")
		return Solution;

	return Solution + Remainder + R + " / " + y;

}

#pragma endregion

#pragma region COMPARE
bool isEqualTo(string x, string y){
	trim(x);
	trim(y);
	return !isLessThan(x,y) && !isGreaterThan(x,y);
}
bool isGreaterThan(string x, string y){
	return isLessThan(y, x);
}
bool isLessThan(string x, string y){ // x < y true or false
	if (x == y){
		return false;
	}
	if (x[0] == '-' )
		if( y[0] != '-')
		return true;
		else
		{
			x = x.substr(1);
			y = y.substr(1);
		}
	if (y[0] == '-')
		return false;
	trim(x);
	trim(y);
	int SHIFT = Shift(x, y);
	removeDecimal(x);
	removeDecimal(y);
	if (x.length() < y.length())
		return true;
	else if (x.length() == y.length()){
		// THIS IS WHERE WE CHECK EVERY VALUE IF X IS LARGER WE RETURN FALSE ELSE RETURN TRUE IF Y IS LARGER AND CONTINUE CHECKING IF SAME
		x = Reverse(x);
		y = Reverse(y);
		while (!x.empty()){
			char X = x.back();
			x.pop_back();
			char Y = y.back();
			y.pop_back();
			if (X < Y)
				return true;
			if (Y < X)
				return false;
		}
	}
	return false;
}

#pragma endregion

