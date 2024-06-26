#ifndef SENSORE_VISITOR_H
#define SENSORE_VISITOR_H

class SensoreAria;
class SensoreElettrodomestico;
class SensoreLampadina;
class SensorePannelli;
class SensoreTemperatura;
class SensoreUmidita;

class sensoreVisitor{
public:
    virtual void visita(const SensoreAria& aria) = 0;
    virtual void visita(const SensoreElettrodomestico& elettrodomestico) = 0;
    virtual void visita(const SensoreLampadina& lampadina) = 0;
    virtual void visita(const SensorePannelli& pannelli) = 0;
    virtual void visita(const SensoreTemperatura& temperatura) = 0;
    virtual void visita(const SensoreUmidita& umidita) = 0;

    virtual ~sensoreVisitor() = default;
};

#endif
