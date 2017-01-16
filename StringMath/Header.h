#include<iomanip>
#include<Windows.h>
#include<vector>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <thread>

using namespace std;

const string T = "2000000";
const int DecimalAccuracy = 3000;

void PI(string approx, string overLimit, string threadCount, string &a);
string decimalAcc(string check, string value);
string BigNumDivision(string x, string y);
string CombiningFractions(string x, string y);
string AddTwoStrings(string a, string b);
string  StringMULT(string a, string b);
bool isLessthan(string x, string y);
bool isEqualTo(string x, string y);
bool charLess(char x, char y);
string Subtraction(string x, string y);
string LongDivision(string x, string y);
string IntDivision(string x, string y);
string ModString(string x, string y);
string ADD(string x, string y);
string MULTI(string x, string y);
string SUB(string x, string y);
string DIVIDE(string x, string y);
string isnegative(bool isNegative);
string placeDecimal(int Shift, int WholeNumSize, string x);
string LongDecimalDivision(string x, string y);
string convert(int x);
string DecimalDivision(string x, string y);
string gcd(string x, string y);
string FinalLongDivision(string x, string y, int Shift);
bool isDecimal(string x);
string DecimalAddition(string x, string y);
string DecimalSubtraction(string x, string y);
string AddingFractions(string x, string y);
string lcm(string x, string y);
string SQRootString(string x);
string PowRString(string x, string y);
string BiNomialCoefficient(string x, string y);
string Factorial(string value);
string FactorialLimit(string value, string limit);
bool isEven(char t);


bool isDecimal(string x){
	int Alen = x.length() - 1;
	int pos = x.find('.');
	if (pos < Alen && pos >= 0){
		return true;
	}
	return false;
}

string gcd(string x, string y){

	while (x[0] == '0'){
		if (x.length() == 1){
			break;
		}
		x = x.substr(1);
	}

	while (y[0] == '0'){
		if (y.length() == 1){
			break;
		}
		y = y.substr(1);
	}

	if (isEqualTo(y, "0")){
		return x;
	}
	else
		return gcd(y, ModString(x, y));

}

string placeDecimal(int Shift, int WholeNumSize, string x){
	int XLen = x.length();
	string tempX = "";
	Shift = WholeNumSize - Shift;

	if (Shift < 0){

		while (XLen < abs(Shift)){
			x = x + '0';
			XLen = x.length();
		}

		// now x is at least the number of shift positions long.
		if (XLen == Shift){
			return x + ".0";
		}

		int count = 0;
		if (Shift == 0){ tempX = '0'; }
		for (int i = 0; i < XLen; i++){
			if (count == Shift){
				tempX = tempX + ".";
			}
			tempX = tempX + x[i];
			count++;
		}
	}
	else{

		int count = 0;
		tempX = "";
		while (XLen < (Shift)){
			x = x + '0';
			XLen = x.length();
		}
		for (int i = 0; i <XLen; i++){
			if (count == Shift){
				tempX = tempX + '.';

			}
			tempX = tempX + x[i];
			count++;
		}

	}

	return tempX;
}

string isnegative(bool isNegative){
	if (isNegative){
		return "-";
	}
	return "";
}

string FinalLongDivision(string x, string y, int Shift){
	// positive shift goes left
	// negaitve shift goes right
	string Solution = "";

	int T = DecimalAccuracy;

	if (Shift > T){
		T = Shift + (int)(Shift / 2);
	}
	else{
		T += abs(Shift);
	}
	int X = x.length();
	while (x[0] == '0'){
		if (x.length() == 1){
			return "0";
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			return "DNE : Cannot divide by zero";
		}
		y = y.substr(1);
	}
	if (Shift > 0){
		Shift *= -1;

		while (Shift < 0){
			x = '0' + x;
			Shift++;
		}
	}
	else{
		Shift = abs(Shift) + X;

	}

	//    ____._
	//  y|   x 0
	// The repetitive motion is appending a zero to the end of x after every subtractive of the multiplicitve of y Solution holds the indvidual number each time
	int count = 0;
	bool Pattern = false;
	string tempX = x;
	int TempXLength = tempX.length();
	x = "";
	string ToAdd = "0";
	vector<string> Product;
	while (isLessthan(ToAdd, "10")){
		Product.push_back(MULTI(ToAdd, y));
		ToAdd = ADD(ToAdd, "1");
	}// this gives us every value from 0 to 9 multiplied by y stored in a vector at placement index 0 thru 9 
	while (count < T){
		if (count < TempXLength)
			x = x + tempX[count];
		else
			x = x + '0';



		int i = 0;
		while (isLessthan(Product[i], x)){
			i++;
			if (i == 9){
				break;
			}
		}
		if (i == 0) {}
		else if (!isEqualTo(Product[i], x)){
			i--;
		}

		x = SUB(x, Product[i]);
		if (count == Shift){
			Solution = Solution + ".";
		}
		Solution = Solution + (char)(i + 48);

		if (count > TempXLength && count > Shift){
			int ZeroCheck = 0;
			while (x[0] == '0'){
				if (x.length() == 1){
					return Solution;
				}
				x = x.substr(1);

			}
		}

		//if (Pattern){ // Pattern need ideas ... 
		//	for (int i = 0; i < Solution.length(); i++){
		//		for (int j = i; j < Solution.length() - j; j++){

		//		}

		//	}
		//}
		count++;
	}



	return Solution;
}

string DIVIDE(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);
			return DIVIDE(x, y);
		}
		else{
			return '-' + DIVIDE(x, y);
		}
	}
	if (y[0] == '-'){
		y = y.substr(1);
		return '-' + DIVIDE(x, y);
	}
	bool isDecimal = false;
	int NumOfShifts = 0;
	if (x.find('.') < x.length()){
		string tempX = "";
		if (x.find('.') > 0)
			tempX = x.substr(0, x.find('.')) + x.substr(x.find('.') + 1);
		else
			tempX = x.substr(1);

		NumOfShifts += x.length() - 1 - x.find('.');
		x = tempX;
		isDecimal = true;
	}

	if (y.find('.') < y.length()){
		string tempY = "";
		if (y.find('.') > 0)
			tempY = y.substr(0, y.find('.')) + y.substr(y.find('.') + 1);
		else
			tempY = y.substr(1);

		NumOfShifts -= y.length() - 1 - y.find('.');
		y = tempY;
		isDecimal = true;
	}


	string result = LongDivision(x, y);
	bool negative = false;
	while (result[0] == '-'){
		if (negative){
			negative = false;
		}
		else{
			negative = true;
		}
		result = result.substr(1);
	}
	string tempHold = result;
	if (isDecimal)
	{
		string answer = FinalLongDivision(x, y, NumOfShifts);
		while (answer[0] == '0'){
			answer = answer.substr(1);
		}
		int Alen = answer.length() - 1;
		int pos = answer.find('.');
		if (pos < Alen && pos >= 0){
			while (answer[Alen] == '0'){

				answer = answer.substr(0, Alen - 1);
				Alen = answer.length() - 1;
			}
		}
		return answer;

	}

	return isnegative(negative) + tempHold;
}

string convert(int x){
	string Conversion = "";
	string sign = "";
	if (x < 0){
		sign = "-";
		x = abs(x);
	}
	while (x > 0){
		int value = x % 10;
		Conversion = (char)(value + 48) + Conversion;
		x /= 10;
		if (x == 0){
			break;
		}
	}

	return sign + Conversion;
}

string ADD(string x, string y){
	string result = AddTwoStrings(x, y);
	bool negative = false;
	while (result[0] == '-'){
		if (negative){
			negative = false;
		}
		else{
			negative = true;
		}
		result = result.substr(1);
	}
	return isnegative(negative) + result;
}

string SUB(string x, string y){
	string result = Subtraction(x, y);
	bool negative = false;
	while (result[0] == '-'){
		if (negative){
			negative = false;
		}
		else{
			negative = true;
		}
		result = result.substr(1);
	}
	return isnegative(negative) + result;
}

string MULTI(string x, string y){
	while (x[0] == '0'){
		if (x.length() == 1){
			return "0";
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			return "0";
		}
		y = y.substr(1);
	}
	bool isDecimal = false;
	int NumOfShifts = 0;
	if (x.find('.') < x.length()){
		string tempX = "";
		//cout << x << endl;
		if (x.find('.') > 0)
			tempX = x.substr(0, x.find('.')) + x.substr(x.find('.') + 1);
		else
			tempX = x.substr(1);

		NumOfShifts += x.length() - 1 - x.find('.');
		x = tempX;
		isDecimal = true;
	}

	if (y.find('.') < y.length()){
		string tempY = "";
		if (y.find('.') > 0)
			tempY = y.substr(0, y.find('.')) + y.substr(y.find('.') + 1);
		else
			tempY = y.substr(1);

		NumOfShifts += y.length() - 1 - y.find('.');
		y = tempY;
		isDecimal = true;
	}

	string result = StringMULT(x, y);
	bool negative = false;
	while (result[0] == '-'){
		if (negative){
			negative = false;
		}
		else{
			negative = true;
		}
		result = result.substr(1);
	}
	if (isDecimal)
		result = placeDecimal(NumOfShifts, result.length(), result);

	return isnegative(negative) + result;
}

string ModString(string x, string y){
	if (y[0] == '-'){
		y = y.substr(1);
		return '-' + ModString(x, y);
	}
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);

		}
		else {
			return '-' + LongDivision(x, y);
		}

	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return '-' + LongDivision(x, y);
	}
	string hold = "";
	string Remainder = " R : ";
	// x divided by y

	while (x[0] == '0'){
		if (x.length() == 1){
			break;
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			return "Cannot implicitly divide by zero.";
		}
		y = y.substr(1);
	}
	string R = "0";
	string Solution = "";
	int xLen = x.length();
	for (int i = 0; i < xLen; i++){
		R = R + x[i];
		int count = 0;
		while (isLessthan(y, R)){
			count++;
			//	cout << "R : " << R << " y : " << y << " = " ;
			R = Subtraction(R, y);
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

	return R;
}

string IntDivision(string x, string y){
	string a = LongDivision(x, y);
	int pos = a.find(' ');
	a = a.substr(0, pos);
	return a;
}

string AddTwoStrings(string a, string b){
	if (a[0] == '-'){
		a = a.substr(1);
		if (b[0] == '-'){
			b = b.substr(1);
			return '-' + AddTwoStrings(a, b);
		}
		else {
			return Subtraction(b, a);
		}

	}
	else if (b[0] == '-'){
		b = b.substr(1);
		return Subtraction(a, b);
	}

	if (isDecimal(a) || isDecimal(b)){
		return DecimalAddition(a, b);
	}
	int c = a.length();
	int d = b.length();
	string result = "";
	while (c < d){
		a = "0" + a;
		c = a.length();
	}
	while (d < c){
		b = "0" + b;
		d = b.length();
	}
	int count = 0;
	while (count < c){
		result += "0";
		count++;
	}
	for (int i = count - 1; i >= 0; i--){
		int value = (result[i] - 48) + (a[i] - 48) + (b[i] - 48);
		if (value > 9){
			result[i] = (char)((value % 10) + 48);
			if (i > 0){
				result[i - 1] = (char)((value / 10) + 48);
			}
			else{
				result = "1" + result;
			}

		}
		else{
			result[i] = (char)((value)+48);
		}

	}
	return result;
}

string StringMULT(string a, string b){
	if (a[0] == '-'){
		a = a.substr(1);
		if (b[0] == '-'){
			b = b.substr(1);

		}
		else {
			return '-' + StringMULT(a, b);
		}

	}
	else if (b[0] == '-'){
		b = b.substr(1);
		return '-' + StringMULT(a, b);
	}
	int c;
	int count = 0;
	int d;
	char e;
	string RESULT = "0";
	vector<string> line;
	c = a.length();
	d = b.length();
	while (c < d){
		a = "0" + a;
		c = a.length();
	}
	while (d < c){
		b = "0" + b;
		d = b.length();
	}

	for (int j = c - 1; j>-1; j--){
		int carry = 0;
		line.push_back("");
		int TrailingZeros = 0;
		while (TrailingZeros < count){
			line[count] += "0";
			TrailingZeros++;
		}
		for (int i = d - 1; i>-1; i--){

			int value = ((a[i] - 48)*(b[j] - 48)) + carry;
			if (value > 9){
				e = (char)(value % 10 + 48);
				carry = value / 10;
			}
			else{
				e = (char)(value + 48);
				carry = 0;
			}
			line[count] = e + line[count];

		}
		if (carry > 0){
			line[count] = (char)(carry + 48) + line[count];
		}
		count++;
	}

	for (int i = 0; i<count; i++){
		//cout<<line[i]<<endl;
	}
	// ADD LINES
	count = 0;
	int size = line.size();
	while (count < (size)){
		RESULT = AddTwoStrings(RESULT, line[count]);
		count++;
	}

	// 	cout << "ALL LEADING ZEROS : " << RESULT << endl;
	while (RESULT[0] == '0'){
		RESULT = RESULT.substr(1);
	}
	return RESULT;
}

bool isEqualTo(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);

		}
		else {
			return false;
		}

	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return false;
	}
	while (x[0] == '0'){
		if (x.length() == 1){
			break;
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			break;
		}
		y = y.substr(1);
	}

	if (x.length() != y.length())
	{
		return false;
	}
	else{
		int xLen = x.length();
		for (int i = 0; i < xLen; i++){
			if (x[i] != y[i]){ return false; }

		}
	}
	return true;
}

bool charLess(char x, char y){
	int xVal = (int)x - 48;
	int yVal = (int)y - 48;
	if (xVal < yVal)
		return true;
	else
		return false;
}

bool isLessthan(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);
			return !(isLessthan(x, y));

		}
		else {
			return true;
		}

	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return false;
	}

	while (x[0] == '0'){
		if (x.length() == 1){
			break;
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			break;
		}
		y = y.substr(1);
	}
	if (isEqualTo(x, y)){
		return false;
	}
	if (x.length() < y.length()){
		return true;
	}
	else if (y.length() < x.length()){
		return false;
	}
	else{
		int xLen = x.length();
		for (int i = 0; i < xLen; i++){

			if (charLess(x[i], y[i])){
				return true;
			}
			else if (charLess(y[i], x[i])){
				return false;
			}

		}

		return false;
	}
}

string Subtraction(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);
			// - x - ( - y ) = - x + y = y - x
			return Subtraction(y, x);
		}
		else {
			// - x - y 

			return '-' + AddTwoStrings(x, y);
		}

	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return AddTwoStrings(x, y);
	}
	if (isDecimal(x) || isDecimal(y)){
		return DecimalSubtraction(x, y);
	}

	string result = "";
	if (isLessthan(x, y)){
		return '-' + Subtraction(y, x);
	}
	// x - y


	int c = x.length();
	int d = y.length();
	while (c < d){
		x = "0" + x;
		c = x.length();
	}
	while (d < c){
		y = "0" + y;
		d = y.length();
	}
	// remember its x - y
	for (int i = c - 1; i >= 0; i--){
		int value = (x[i] - 48) - (y[i] - 48);
		if (value < 0){
			// 1 - 9 = - 8 
			value = value + 10; // equals positive value!!!
			char temp = (char)(value + 48);
			result = temp + result;
			x[i - 1] = (char)(x[i - 1] - 48 - 1 + 48);
		}
		else {
			result = (char)(value + 48) + result;
		}
		//cout <<x[i] << " : " << y[i] << " = " << result << endl;
		value = 0;
	}



	return result;
}

string LongDivision(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);

		}
		else {
			return '-' + LongDivision(x, y);
		}

	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return '-' + LongDivision(x, y);
	}
	string hold = "";
	string Remainder = " R : ";
	// x divided by y

	while (x[0] == '0'){
		if (x.length() == 1){
			break;
		}
		x = x.substr(1);
	}
	while (y[0] == '0'){
		if (y.length() == 1){
			return "Cannot implicitly divide by zero.";
		}
		y = y.substr(1);
	}
	string R = "0";
	string Solution = "";
	int xLen = x.length();
	for (int i = 0; i < xLen; i++){
		R = R + x[i];
		int count = 0;
		while (isLessthan(y, R)){
			count++;
			//	cout << "R : " << R << " y : " << y << " = " ;
			R = Subtraction(R, y);
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


	return Solution + Remainder + R + " / " + y;

}

string LongDecimalDivision(string x, string y){
	// This function works with the decimal division of the remainder to T number of places
	int T = DecimalAccuracy;
	int X = x.length();
	string Solution = "";
	if (x == "0") { return ""; }
	//    ____._
	//  y|   x 0
	// The repetitive motion is appending a zero to the end of x after every subtractive of the multiplicitve of y Solution holds the indvidual number each time
	int count = 0;
	bool Pattern = false;
	while (count < T){
		x = x + "0";
		string ToAdd = "0";
		string Product = MULTI(ToAdd, y);
		while (isLessthan(Product, x)){
			ToAdd = ADD(ToAdd, "1");
			Product = MULTI(ToAdd, y);
		}
		if (!isEqualTo(Product, x))
			ToAdd = SUB(ToAdd, "1");
		Product = MULTI(ToAdd, y);
		x = SUB(x, Product);
		Solution = Solution + ToAdd;
		while (x[0] == '0'){
			if (x.length() == 1){
				return Solution;
			}
			x = x.substr(1);
		}

		//if (Pattern){ // Pattern need ideas ... 
		//	for (int i = 0; i < Solution.length(); i++){
		//		for (int j = i; j < Solution.length() - j; j++){

		//		}

		//	}
		//}
		count++;
	}

	return Solution;
}

string DecimalDivision(string x, string y){
	if (x[0] == '-'){
		x = x.substr(1);
		if (y[0] == '-'){
			y = y.substr(1);
		}
		else{
			return '-' + DecimalDivision(x, y);
		}
	}
	else if (y[0] == '-'){
		y = y.substr(1);
		return '-' + DecimalDivision(x, y);
	}


	string temp = "";
	string answer = DIVIDE(x, y);



	string Remainder;


	int firstSpace = answer.find(' ');
	int RemainderPos = answer.find(':') + 2;
	int RemainderR = answer.find('R');

	if (RemainderR < 0){ return answer; }
	int RemainderLen = answer.find('/') - RemainderPos - 1;
	Remainder = answer.substr(RemainderPos, RemainderLen);

	int OpenPara = answer.find('(') + 1;
	int CloseParaLen = answer.find(')') - OpenPara;
	string shift = answer.substr(OpenPara, CloseParaLen);

	string WholeNum = answer.substr(0, firstSpace);
	if (Remainder == "0"){ return WholeNum; }

	// Remainder , WholeNum, shift, y = Number dividing by so Remainder / y
	string decimal = LongDecimalDivision(Remainder, y);

	return WholeNum + decimal;

}

string DecimalAddition(string x, string y){
	int posX = x.length();
	int posY = y.length();
	if (isDecimal(x)){
		posX = x.find('.');
	}
	else{
		x = x + ".0";
		posX = x.find('.');
	}
	if (isDecimal(y)){
		posY = y.find('.');
	}
	else{
		y = y + ".0";
		posY = y.find('.');
	}

	int XDigit = x.length() - posX;
	int YDigit = y.length() - posY;

	while (XDigit < YDigit){
		XDigit++;
		x = x + '0';
	}
	while (YDigit < XDigit){
		YDigit++;
		y = y + '0';
	}
	string XWhole, YWhole;
	if (0 != posX)
		XWhole = x.substr(0, posX);
	else
		XWhole = "0";
	if (0 != posY)
		YWhole = y.substr(0, posY);
	else
		YWhole = "0";
	string XDec, YDec;
	XDec = x.substr(posX + 1);
	YDec = y.substr(posY + 1);



	string Dec = AddTwoStrings(XDec, YDec);
	string Whole = AddTwoStrings(XWhole, YWhole);
	string carry = "";

	while (Dec.length() < YDec.length()){
		carry = carry + Dec[0];
		Dec = Dec.substr(1);
	}
	carry = "0" + carry;
	Whole = AddTwoStrings(Whole, carry);

	string result = Whole + "." + Dec;

	return result;
}

string DecimalSubtraction(string x, string y){
	int posX = x.length();
	int posY = y.length();
	if (isDecimal(x)){
		posX = x.find('.');
	}
	else{
		x = x + '.';
	}
	if (isDecimal(y)){
		posY = y.find('.');
	}
	else{
		y = y + '.';
	}

	int XDigit = x.length() - posX;
	int YDigit = y.length() - posY;


	string XWhole, YWhole;
	if (0 != posX)
		XWhole = x.substr(0, posX);
	else
		XWhole = "0";
	if (0 != posY)
		YWhole = x.substr(0, posY);
	else
		YWhole = "0";
	string XDec, YDec;
	XDec = x.substr(posX + 1);
	YDec = y.substr(posY + 1);

	while (XDec.length() < YDec.length()){
		XDec = XDec + "0";
	}
	while (YDec.length() < XDec.length()){
		YDec = YDec + "0";
	}

	string Dec = Subtraction(XDec, YDec);
	string Whole = Subtraction(XWhole, YWhole);
	string carry = "0";
	string ADDER = "1";
	while (XDec.length() > ADDER.length()){
		ADDER = ADDER + '0';
	}
	while (Dec[0] == '-'){
		carry = AddTwoStrings(carry, "1");
		Dec = AddTwoStrings(ADDER, Dec);
	}
	Whole = Subtraction(Whole, carry);

	return Whole + '.' + Dec;

}

bool isEven(char t){
	int x = (int)t - 48;
	if (x % 2 == 0){
		return true;
	}
	return false;
}

string FactorialLimit(string value, string limit){
	string fact = "1";
	while (!(isEqualTo(value, limit))){
		fact = MULTI(fact, value);
		value = SUB(value, "1");
	}
	return fact;
}

string Factorial(string value){
	string fact = "1";
	while (!(isEqualTo(value, "0"))){
		fact = MULTI(fact, value);
		value = SUB(value, "1");
	}
	return fact;
}

string BiNomialCoefficient(string x, string y){
	// { x  }         x!
	// { y  }  =  ---------
	//            (x-y)! y!

	string limit = SUB(x, y);
	if (isLessthan(limit, y)){
		string temp = y;
		y = limit;
		limit = temp;

	}
	string top = FactorialLimit(x, limit);
	string bottom = Factorial(y);
	bottom = bottom + '.';
	//cout << "top : " << top << endl << " ----------------" << endl << "bottom : " << bottom << endl;
	return top + '/' + bottom;
}

string PowRString(string x, string y){
	string result = "1";
	string limit = "0";
	while (!isEqualTo(y, limit)){
		result = MULTI(result, x);
		limit = AddTwoStrings(limit, "1");
	}


	return result;
}


string PrintTime(){

	time_t rawtime;
	time(&rawtime);
	string s = ctime(&rawtime);
	return "Current local time and date: " + s + "\n";

}

string TimeElapsed(time_t Start){
	string temp, input;
	temp = "";
	ifstream read;
	ofstream filet;
	filet.open("temp.txt");
	time_t current = clock();
	filet << "Time Elapsed : " << current - Start << " (ms). " << "\n";
	filet << setw(4) << setfill('0') << (((current - Start) / 1000) / 3600 * 24) << " days : " << setw(2) << setfill('0') << (((current - Start) / 1000) / 3600) % 24 << " hours : " << setw(2) << setfill('0') << (((current - Start) / 1000) / 60) % 60 << " mins : " << setw(2) << setfill('0') << (((current - Start) / 1000)) % 60 << " secs \n";
	filet.close();
	read.open("temp.txt");
	getline(read, input);
	temp = temp + input;
	getline(read, input);
	temp = temp + "\n" + input + "\n \n";
	return temp;
}

void PI(string approx, string overLimit, string threadCount, string &a){
	string hold = approx;
	string end1 = SUB(overLimit, "1");
	time_t Start = clock();
	string temp = PrintTime();
	ofstream file;
	string FileName = "Pi" + threadCount + ".txt";
	file.open(FileName.c_str(), ios::app);
	file << temp;
	string pi = "0/1";


	while (isLessthan(approx, overLimit)){
		string BiNomial = BiNomialCoefficient(MULTI(approx, "2"), approx);
		//cout << "BiNomial : " << BiNomial << endl;
		string BiTop, BiBottom;
		BiTop = BiNomial.substr(0, BiNomial.find('/'));
		BiBottom = BiNomial.substr(BiNomial.find('/') + 1);
		string CubeTop = PowRString(BiTop, "3");
		string CubeBottom = PowRString(BiBottom, "3");
		//cout << "Cube : " << CubeTop << " / " << CubeBottom << endl; 

		string top = AddTwoStrings(MULTI("42", approx), "5");
		//cout << "Top :" << top << endl;

		string bottom = PowRString("2", AddTwoStrings(MULTI("12", approx), "4"));
		//cout << "2 ^ (" << AddTwoStrings(MULTI("12", approx),"4") << ") " << endl;


		//cout << "Bottom : " << bottom << endl;

		string Part2 = top + '/' + bottom;
		//cout << "Part 2 : " << Part2 << endl;
		// Here on is where problems lay
		string Add = MULTI(CubeTop, top);
		string AddBottom = MULTI(CubeBottom, bottom);
		pi = AddingFractions(pi, Add + '/' + AddBottom);
		cout << "n : " << approx << "\n" << "evaluation of 1/pi: where pi : " << "\n" << pi << "\n";
		file << "n : " << approx << "\n" << "evaluation of 1/pi: where pi : " << "\n" << pi << "\n";
		file.close();
		temp = TimeElapsed(Start);
		file.open(FileName.c_str(), ios::app);
		file << temp << "\n";
		temp = PrintTime();

		file << temp << "\n";
		approx = AddTwoStrings(approx, "1");
	}
	string piT, piB;
	piT = pi.substr(0, pi.find('/'));
	piB = pi.substr(pi.find('/') + 1);
	//piT += ".";
	//piB  += ".";
	temp = TimeElapsed(Start);
	file << temp << endl;
	PrintTime();
	file << "From " << hold << " to " << end1 << " : \n " << piT + "/" + piB;
	file.close();
	a = piT + '/' + piB;
	return; // piT + "/" + piB;

}

string lcm(string x, string y){
	string top = MULTI(x, y);
	string GCD = gcd(x, y);
	return IntDivision(top, GCD);
}

string SQRootString(string x){
	string y = x;
	int yLen = x.length();
	string temp = "1";
	for (int i = 1; i < yLen; i++){
		temp = temp + '0';
	}
	y = SUB(y, temp);
	int posY = y.find('.');
	if (posY < 0 || posY >= yLen){
		y = y + ".0";
	}

	string topBound = x;
	string bottomBound = "0";
	while (!isEqualTo(MULTI(y, y), x)){
		if (isLessthan(MULTI(y, y), x)){
			topBound = y;
			y = SUB(y, DIVIDE(SUB(topBound, bottomBound), "2.0"));

			int yCheck = y.length();
			int yPost = y.find('.');

		}
		else {
			bottomBound = y;
			y = ADD(DIVIDE(SUB(topBound, bottomBound), "2.0"), y);

		}
		string temp = ADD(y, ".00001");
		if (!isLessthan(MULTI(temp, temp), x)){
			return y;
		}

	}
	return y;
}

string AddingFractions(string x, string y){

	string topX = x.substr(0, x.find('/'));
	string bottomX = x.substr(x.find('/') + 1);
	string XGCD = gcd(topX, bottomX);
	string topXSimplfy = IntDivision(topX, XGCD);
	string bottomXSimplfy = IntDivision(bottomX, XGCD);

	string topY = y.substr(0, y.find('/'));
	string bottomY = y.substr(y.find('/') + 1);
	string YGCD = gcd(topY, bottomY);
	string topYSimplfy = IntDivision(topY, YGCD);
	string bottomYSimplfy = IntDivision(bottomY, YGCD);

	string LCM = lcm(bottomXSimplfy, bottomYSimplfy);
	string Xmult = IntDivision(LCM, bottomXSimplfy);
	//cout << LCM << " : " << bottomYSimplfy << endl;
	string Ymult = IntDivision(LCM, bottomYSimplfy);

	string TOPX = MULTI(topXSimplfy, Xmult);
	bottomX = MULTI(bottomXSimplfy, Xmult);
	bottomY = MULTI(bottomYSimplfy, Ymult);
	//cout << "BottomY : " << bottomY << endl;
	//cout << bottomX << endl;
	//cout << topYSimplfy << " : " <<  Ymult <<  endl;
	string TOPY = MULTI(topYSimplfy, Ymult);

	//cout << TOPX  << " : " << TOPY << endl;
	topX = ADD(TOPX, TOPY);
	XGCD = gcd(topX, bottomX);
	topXSimplfy = IntDivision(topX, XGCD);
	bottomXSimplfy = IntDivision(bottomX, XGCD);



	string result = topXSimplfy + "/" + bottomXSimplfy;
	return result;



}

string BigNumDivision(string x, string y){
	string solution = "";
	// we are taking x divided by y
	// develop the multiples of y
	vector<string> MultY;
	int k = 0;
	for (string i = "0"; isLessthan(i, "11"); i = AddTwoStrings(i, "1"))
	{
		MultY.push_back(MULTI(i, y));
		cout << i << " : " << MultY[k] << endl;
		k += 1;
	}
	// we can develop a list of y multiples which we can check if y is lessthan or equal to x if so then subtract that number from the current x
	int Len = x.length();
	string NewX = "";
	k = 0;
	while (k < Len){
		NewX = NewX + x[k];
		k++;
		for (int j = 0; j < 11; j++)
			if (!isLessthan(MultY[j], NewX)){
				if (isEqualTo(MultY[j], NewX)){
					NewX = "0";
					solution = solution + (char)(j + 48);
				}
				else{
					NewX = SUB(NewX, MultY[j - 1]);
					solution = solution + (char)(j + 47);
					j += 11;
				}
			}

		while (NewX[0] == '0'){
			if (NewX.length() == 1){
				break;
			}
			else{
				NewX = NewX.substr(1);
			}

		}
		while (solution[0] == '0'){
			if (solution.length() == 1){
				break;
			}
			else{
				solution = solution.substr(1);
			}

		}
	}
	string dec = "0";
	solution = solution + ".";
	while (!isEqualTo(NewX, "0") && isLessthan(dec, T)){
		NewX = NewX + "0";
		for (int j = 0; j < 11; j++){
			if (!isLessthan(MultY[j], NewX)){
				if (isEqualTo(MultY[j], NewX)){
					NewX = "0";
					solution = solution + (char)(j + 48);
				}
				else{
					NewX = SUB(NewX, MultY[j - 1]);
					solution = solution + (char)(j + 47);
					j += 11;
				}
			}
		}
		dec = AddTwoStrings(dec, "1");

		while (NewX[0] == '0'){
			if (NewX.length() == 1){
				return solution;
			}
			else{
				NewX = NewX.substr(1);
			}

		}

	}

	return solution;
}


string decimalAcc(string check, string value){
	bool error = true;
	string start = "0";
	char C, V;
	bool end = false;
	while (check.length() != 0 && error){
		if (value.length() == 1 || check.length() == 1){
			V = value[0];
			C = check[0];
			end = true;
			if (C != V){
				error = false;
				return start;
			}
			else
			{
				start = AddTwoStrings(start, "1");
			}

		}
		else{
			C = check[0];
			V = value[0];
			check = check.substr(1);
			value = value.substr(1);
			if (C != V){
				error = false;
				return start;
			}
			else
			{
				start = AddTwoStrings(start, "1");
			}

		}



		if (end){
			return start;
		}
	}

	return start;

}