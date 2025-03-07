#include "main.h" 

int main(int argc, char* argv[]) {
    //����У��
    if (argc != 4) {
        cerr << "�÷�: " << argv[0]
            << " ԭ���ļ� ��Ϯ�ļ� ����ļ�" << endl;
        return 1;
    }

    //���������в���
    string original = argv[1];
    string plagiarism = argv[2];
    string output = argv[3];

    //��ȡԭ������
    ifstream orig_file(original, ios::binary);
    if (!orig_file) {
        cerr << "�����޷���ԭ���ļ�!" << endl;
        return 1;
    }
    string orig_content((istreambuf_iterator<char>(orig_file)),
        istreambuf_iterator<char>());
    orig_file.close();

    //��ȡ��Ϯ������
    ifstream plag_file(plagiarism, ios::binary);
    if (!plag_file) {
        cerr << "�����޷��򿪳�Ϯ�ļ�!" << endl;
        return 1;
    }
    string plag_content((istreambuf_iterator<char>(plag_file)),
        istreambuf_iterator<char>());
    plag_file.close();

    //����n-gram��Ƶ
    auto orig_ngrams = get_ngrams(orig_content);
    auto plag_ngrams = get_ngrams(plag_content);

    //�������ƶ�
    double similarity = compute_cosine(orig_ngrams, plag_ngrams);

    //���������ļ�
    ofstream out_file(output);
    if (!out_file) {
        cerr << "�����޷���������ļ�!" << endl;
        return 1;
    }

    out_file.precision(2); 
    out_file << fixed << similarity * 100 << endl;
    out_file.close();

    return 0;
}