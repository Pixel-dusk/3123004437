#include "main.h" 

int main(int argc, char* argv[]) {
    //参数校验
    if (argc != 4) {
        cerr << "用法: " << argv[0]
            << " 原文文件 抄袭文件 输出文件" << endl;
        return 1;
    }

    //解析命令行参数
    string original = argv[1];
    string plagiarism = argv[2];
    string output = argv[3];

    //读取原文内容
    ifstream orig_file(original, ios::binary);
    if (!orig_file) {
        cerr << "错误：无法打开原文文件!" << endl;
        return 1;
    }
    string orig_content((istreambuf_iterator<char>(orig_file)),
        istreambuf_iterator<char>());
    orig_file.close();

    //读取抄袭版内容
    ifstream plag_file(plagiarism, ios::binary);
    if (!plag_file) {
        cerr << "错误：无法打开抄袭文件!" << endl;
        return 1;
    }
    string plag_content((istreambuf_iterator<char>(plag_file)),
        istreambuf_iterator<char>());
    plag_file.close();

    //计算n-gram词频
    auto orig_ngrams = get_ngrams(orig_content);
    auto plag_ngrams = get_ngrams(plag_content);

    //计算相似度
    double similarity = compute_cosine(orig_ngrams, plag_ngrams);

    //输出结果到文件
    ofstream out_file(output);
    if (!out_file) {
        cerr << "错误：无法创建输出文件!" << endl;
        return 1;
    }

    out_file.precision(2); 
    out_file << fixed << similarity * 100 << endl;
    out_file.close();

    return 0;
}