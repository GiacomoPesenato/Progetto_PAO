#ifndef JSON_FILE_H
#define JSON_FILE_H

#include <string>
#include <vector>

#include "../sensore.h"
#include "../Converter/json.h"

namespace DataMapper {

class JsonFile {
  private:
    std::string percorso;

  public:
    JsonFile(const std::string& percorso);
    static JsonFile dalPercorso(const std::string& percorso);
    const std::string& getPercorso() const;
    void setPercorso(const std::string& percorso);
    void scriviJson(const std::vector<Sensore*>& sensors);
    std::vector<Sensore*> caricaSensoriJson();
};

}
#endif
