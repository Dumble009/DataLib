#include "DataLibErrorCode.h"

namespace data
{
    inline bool IsDataLibActionSucceeded(DataLibErrorCode code)
    {
        return code == DataLibErrorCode::DATA_LIB_SUCCESS;
    }
}