#ifndef SENSOR_DATA_MAPPER_JSON_FILE_H
#define SENSOR_DATA_MAPPER_JSON_FILE_H

#include <string>
#include <vector>

#include "../sensore.h"
#include "../Converter/json.h"

namespace DataMapper {

class JsonFile {
  private:
    std::string path;

  public:
    JsonFile(const std::string& path);
    static JsonFile fromPath(const std::string& path);
    const std::string& getPath() const;
    void setPath(const std::string& path);
    void store(const std::vector<Sensore*>& sensors);
    std::vector<Sensore*> load();
};

}
#endif
