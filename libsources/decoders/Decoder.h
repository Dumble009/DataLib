#pragma once
#include <vector>
#include <string>

#include "../DataLibErrorCode.h"

namespace data
{
    namespace decoder
    {
        class Decoder
        {
        private:
            std::vector<char> readBytes; // ファイルから読み込んだバイト配列

            template <class T>
            DataLibErrorCode DecodeImp(T *data,
                                       const std::vector<char> &bytes,
                                       int *head,
                                       int option);

            template <class T>
            DataLibErrorCode DecodeImp(std::vector<T> *data,
                                       const std::vector<char> &bytes,
                                       int *head,
                                       int option);

        public:
            Decoder();

            DataLibErrorCode Read(const std::string &path);

            template <class T>
            DataLibErrorCode Decode(T *data,
                                    const std::string &path,
                                    int option);
        };
    }
}