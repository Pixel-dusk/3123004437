#include "function.h" 
#include <cmath>      

const int N = 2;

//UTF-8�ַ��ָ��
vector<string> split_utf8(const string& s) {
    vector<string> chars;
    for (size_t i = 0; i < s.length();) {
        unsigned char c = s[i];
        int len = 0;
        //����UTF-8�ж��ַ�����
        if (c <= 0x7F) {
            len = 1;
        }
        else if ((c & 0xE0) == 0xC0) {
            len = 2;
        }
        else if ((c & 0xF0) == 0xE0) {
            len = 3;
        }
        else if ((c & 0xF8) == 0xF0) {
            len = 4;
        }
        else {
            ++i;
            continue;
        }

        if (i + len > s.length()) break;
        //��ȡ�����ַ�
        chars.push_back(s.substr(i, len));
        i += len; //�ƶ�����һ���ַ�
    }
    return chars;
}

//����n-gram��Ƶ��
unordered_map<string, int> get_ngrams(const string& s) {
    unordered_map<string, int> res;
    vector<string> chars = split_utf8(s);

    //���ַ�������nʱ���ؿձ�
    if (chars.size() < N) return res;

    for (size_t i = 0; i <= chars.size() - N; ++i) {
        string gram;
        //�������N���ַ�
        for (int j = 0; j < N; ++j) {
            gram += chars[i + j]; //ƴ���ַ��γ�n-gram
        }
        res[gram]++; //ͳ��n-gram���ִ���
    }
    return res;
}

//�����������ƶ�
double compute_cosine(const unordered_map<string, int>& a,
    const unordered_map<string, int>& b) {
    double dot = 0.0; //���

    //������
    for (const auto& pair : a) {
        auto it = b.find(pair.first);
        if (it != b.end()) {
            dot += pair.second * it->second;
        }
    }

    //��������ģ��
    double norm_a = 0.0, norm_b = 0.0;
    for (const auto& pair : a) norm_a += pow(pair.second, 2);
    for (const auto& pair : b) norm_b += pow(pair.second, 2);
    norm_a = sqrt(norm_a);
    norm_b = sqrt(norm_b);

    //�������������
    if (norm_a == 0 || norm_b == 0)
        return 0.0;

    return dot / (norm_a * norm_b); //�������ƶȹ�ʽ
}