#pragma once
#include <vector>
#include <string>
#include "../DataLibErrorCode.h"

namespace data
{
    namespace encoder
    {
        // T型の値をheadからsize個、pathのファイルに書き込む
        class ChunkEncoder
        {
        private:
            std::vector<char> writeData;
            DataLibErrorCode Write(const std::string &path);

        public:
            ChunkEncoder();

            // 任意の型Tに対応できるようにヘッダで実装する必要がある
            // sizeはバイト数ではなく、要素数
            template <class T>
            DataLibErrorCode Encode(
                const T *head,
                size_t size,
                const std::string &path,
                int structure)
            {
                size_t byteCounts = sizeof(T) * size; // 扱うデータ全体のバイト数
                writeData.resize(byteCounts);

                void *ptr = (void *)head;
                char *bytes = (char *)ptr;

                for (size_t i = 0; i < byteCounts; i++)
                {
                    writeData[i] = bytes[i];
                }

                return Write(path);
            }
        };
    }
}