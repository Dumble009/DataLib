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
            DataLibErrorCode Write();

        public:
            ChunkEncoder();

            template <class T>
            DataLibErrorCode Encode(
                const T *head,
                size_t size,
                const std::string &path,
                int structure)
            {
                return DataLibErrorCode::DATA_LIB_SUCCESS;
            }
        };
    }
}