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
    virtual void visit(const SensoreAria& aria) = 0;
    virtual void visit(const SensoreElettrodomestico& elettrodomestico) = 0;
    virtual void visit(const SensoreLampadina& lampadina) = 0;
    virtual void visit(const SensorePannelli& pannelli) = 0;
    virtual void visit(const SensoreTemperatura& temperatura) = 0;
    virtual void visit(const SensoreUmidita& umidita) = 0;

    virtual ~sensoreVisitor() = default;
};

#endif
