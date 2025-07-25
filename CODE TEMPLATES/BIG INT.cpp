/*
    string a, b; |a| <= 10 ^ 6
    a + b
    a - b
    a * b
    a / b
    a % b
*/

class BigInt {
private:
    // 每个元素存储一个数字位，0-9，低位在前
    vector<int> digits;
    bool negative;

    // 去除前导零
    void removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0)
            digits.pop_back();
        if (digits.size() == 1 && digits[0] == 0)
            negative = false; // 零为正数
    }

    // 比较两个绝对值，返回：
    // 1 如果 |*this| > |other|
    // -1 如果 |*this| < |other|
    // 0 如果 |*this| == |other|
    int compareAbs(const BigInt& other) const {
        if (digits.size() > other.digits.size()) return 1;
        if (digits.size() < other.digits.size()) return -1;
        for (int i = digits.size()-1; i >=0; --i) {
            if (digits[i] > other.digits[i]) return 1;
            if (digits[i] < other.digits[i]) return -1;
        }
        return 0;
    }

    // 加法，假设两个数都是正数
    BigInt addAbs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        int carry = 0;
        int n = max(digits.size(), other.digits.size());
        for(int i=0; i<n; ++i){
            int sum = carry;
            if(i < digits.size()) sum += digits[i];
            if(i < other.digits.size()) sum += other.digits[i];
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }
        if(carry) result.digits.push_back(carry);
        result.negative = false;
        return result;
    }

    // 减法，假设 |*this| >= |other|
    BigInt subtractAbs(const BigInt& other) const {
        BigInt result;
        result.digits.clear();
        int carry = 0;
        for(int i=0; i<digits.size(); ++i){
            int diff = digits[i] - carry;
            if(i < other.digits.size()) diff -= other.digits[i];
            if(diff < 0){
                diff += 10;
                carry = 1;
            }
            else{
                carry = 0;
            }
            result.digits.push_back(diff);
        }
        result.negative = false;
        result.removeLeadingZeros();
        return result;
    }

    // 乘以一个单一数字，假设 digit 是 0-9
    BigInt multiplyByDigit(int digit) const {
        BigInt result;
        result.digits.clear();
        if(digit == 0){
            result.digits.push_back(0);
            result.negative = false;
            return result;
        }
        int carry = 0;
        for(auto d : digits){
            long long temp = (long long)d * digit + carry;
            carry = temp / 10;
            result.digits.push_back(temp % 10);
        }
        if(carry) result.digits.push_back(carry);
        result.negative = false;
        return result;
    }

public:
    // 默认构造函数，表示0
    BigInt() : digits(1, 0), negative(false) {}

    // 从字符串构造，支持负数
    BigInt(string num) {
        if(num.empty()){
            digits.push_back(0);
            negative = false;
            return;
        }
        if(num[0] == '-'){
            negative = true;
            num = num.substr(1);
        }
        else{
            negative = false;
        }
        // 去除前导零
        int pos = 0;
        while(pos < num.size()-1 && num[pos] == '0') pos++;
        num = num.substr(pos);
        // 反向存储数字位
        digits.assign(num.rbegin(), num.rend());
        for(auto &c : digits) c -= '0';
        removeLeadingZeros();
    }

    // 从整数构造
    BigInt(long long num) {
        if(num < 0){
            negative = true;
            num = -num;
        }
        else{
            negative = false;
        }
        if(num == 0){
            digits.push_back(0);
        }
        while(num > 0){
            digits.push_back(num % 10);
            num /= 10;
        }
    }

    // 转换为字符串
    string toString() const {
        string s = "";
        for(auto it = digits.rbegin(); it != digits.rend(); ++it){
            s += to_string(*it);
        }
        if(negative && s != "0") s = "-" + s;
        return s;
    }

    // 比较操作
    bool operator<(const BigInt& other) const {
        if(negative != other.negative){
            return negative;
        }
        if(!negative){
            // 都为正
            int cmp = compareAbs(other);
            return cmp < 0;
        }
        else{
            // 都为负，取反
            int cmp = compareAbs(other);
            return cmp > 0;
        }
    }

    bool operator>(const BigInt& other) const { return other < *this; }
    bool operator<=(const BigInt& other) const { return !(other < *this); }
    bool operator>=(const BigInt& other) const { return !(*this < other); }
    bool operator==(const BigInt& other) const { return (digits == other.digits) && (negative == other.negative); }
    bool operator!=(const BigInt& other) const { return !(*this == other); }

    // 加法
    BigInt operator+(const BigInt& other) const {
        BigInt result;
        if(!negative && !other.negative){
            result = addAbs(other);
        }
        else if(negative && other.negative){
            result = addAbs(other);
            result.negative = true;
        }
        else{
            if(!negative && other.negative){
                BigInt o = other;
                o.negative = false;
                if(*this < o){
                    result = o.subtractAbs(*this);
                    result.negative = true; // 修正这里
                }
                else{
                    result = subtractAbs(o);
                    result.negative = false; // 修正这里
                }
            }
            else{ // negative + positive
                BigInt a = *this;
                a.negative = false;
                if(a < other){
                    result = other.subtractAbs(a);
                    result.negative = false;
                }
                else{
                    result = a.subtractAbs(other);
                    result.negative = true;
                }
            }
        }
        result.removeLeadingZeros();
        return result;
    }

    // 减法
    BigInt operator-(const BigInt& other) const {
        BigInt negOther = other;
        negOther.negative = !other.negative;
        return (*this + negOther);
    }

    // 乘法
    BigInt operator*(const BigInt& other) const {
        BigInt result;
        result.digits.assign(digits.size() + other.digits.size(), 0);
        for(int i=0; i < digits.size(); ++i){
            for(int j=0; j < other.digits.size(); ++j){
                result.digits[i+j] += digits[i] * other.digits[j];
            }
        }
        // 处理进位
        int carry = 0;
        for(int i=0; i < result.digits.size(); ++i){
            result.digits[i] += carry;
            carry = result.digits[i] / 10;
            result.digits[i] %= 10;
        }
        while(result.digits.size() >1 && result.digits.back() == 0)
            result.digits.pop_back();
        // 处理符号
        result.negative = negative != other.negative;
        if(result.digits.size() ==1 && result.digits[0] ==0)
            result.negative = false;
        return result;
    }

    // 除法和取模，返回商和余数
    pair<BigInt, BigInt> divide(const BigInt& other) const {
        if(other == BigInt("0")){
            throw invalid_argument("Division by zero");
        }

        BigInt dividend = *this;
        BigInt divisor = other;

        // 处理符号
        bool resultNegative = dividend.negative != divisor.negative;

        dividend.negative = false;
        divisor.negative = false;

        // 如果 dividend < divisor, 商 = 0, 余数 = dividend
        if(dividend.compareAbs(divisor) < 0){
            return {BigInt("0"), dividend};
        }

        // Initialize quotient and remainder
        BigInt quotient;
        quotient.digits.clear();
        quotient.negative = resultNegative;

        BigInt remainder;
        remainder.digits.clear();
        remainder.negative = false;

        // Process from the highest digit to the lowest
        for(int i = dividend.digits.size()-1; i >=0; --i){
            // Shift remainder left by 1 digit and add the current digit
            remainder.digits.insert(remainder.digits.begin(), dividend.digits[i]);
            remainder.removeLeadingZeros();

            // Find the maximum number q such that divisor * q <= remainder
            int q = 0;
            int left = 0, right = 9;
            while(left <= right){
                int mid = left + (right - left) / 2;
                BigInt temp = divisor.multiplyByDigit(mid);
                if(temp <= remainder){
                    q = mid;
                    left = mid +1;
                }
                else{
                    right = mid -1;
                }
            }

            // Append q to the quotient
            quotient.digits.push_back(q);

            // Subtract (divisor * q) from remainder
            BigInt subtractVal = divisor.multiplyByDigit(q);
            remainder = remainder - subtractVal;
        }

        // Reverse the quotient digits since we processed from high to low
        reverse(quotient.digits.begin(), quotient.digits.end());

        // Remove leading zeros
        quotient.removeLeadingZeros();
        remainder.removeLeadingZeros();

        // Handle sign for remainder
        remainder.negative = dividend.negative;

        return {quotient, remainder};
    }

    // 取模
    BigInt operator%(const BigInt& other) const {
        pair<BigInt, BigInt> divMod = this->divide(other);
        return divMod.second;
    }

    // 除法
    BigInt operator/(const BigInt& other) const {
        pair<BigInt, BigInt> divMod = this->divide(other);
        return divMod.first;
    }

    // 输出重载
    friend ostream& operator<<(ostream& os, const BigInt& num){
        os << num.toString();
        return os;
    }

    // 输入重载
    friend istream& operator>>(istream& is, BigInt& num){
        string s;
        is >> s;
        num = BigInt(s);
        return is;
    }
};

int main() {
    BigInt a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}