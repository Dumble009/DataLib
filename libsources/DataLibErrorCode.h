namespace data
{
    enum class DataLibErrorCode
    {
        DATA_LIB_SUCCESS,
        DATA_LIB_FAILED_TO_ENCODE,
        DATA_LIB_FAILED_TO_DECODE,
        DATA_LIB_FAILED_TO_DECODE_VECTOR,
        DATA_LIB_FAILED_TO_OPEN_FILE,
        DATA_LIB_FAILED_TO_WRITE_DATA,
        DATA_LIB_FAILED_TO_READ_DATA,
    };

    // DataLibErrorCodeを返す関数の結果を受け取り、正常に終了したかどうか判定する
    inline bool IsDataLibActionSucceeded(DataLibErrorCode code)
    {
        // inline関数なのでヘッダに記述する必要がある
        return code == DataLibErrorCode::DATA_LIB_SUCCESS;
    }
}