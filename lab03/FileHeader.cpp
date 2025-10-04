#include "FileHeader.h"
#include "formato.h"

using namespace std;

FileHeader::FileHeader()
    : registro_formato(FIXO), total_data_size(0), num_registros(0),
      last_modified(time(nullptr)) {}
FileHeader ::FileHeader(Formato registro_formato, long long total_data_size,
                        int num_registros, time_t last_modified)
    : registro_formato(registro_formato), total_data_size(total_data_size),
      num_registros(num_registros), last_modified(last_modified) {}
