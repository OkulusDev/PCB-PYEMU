#include <stdio.h>
#include <stdlib.h>

// Определение базового класса компонента
typedef struct {
    char name[20];
    float value;
} Component;

// Определение класса линейного компонента, наследующего от базового класса
typedef struct {
    Component base;
    float voltage;
} LinearComponent;

// Определение класса провода
typedef struct {
    char name[20];
    Component* startComponent;
    Component* endComponent;
} Wire;

// Определение класса платы
typedef struct {
    char name[20];
    LinearComponent** components;
    Wire** wires;
    int numComponents;
    int numWires;
    float powerConsumption;
} PCB;

// Функция для создания компонента
Component* createComponent(const char* name, float value) {
    Component* component = (Component*)malloc(sizeof(Component));
    sprintf(component->name, "%s", name);
    component->value = value;
    return component;
}

// Функция для создания линейного компонента
LinearComponent* createLinearComponent(const char* name, float value, float voltage) {
    LinearComponent* component = (LinearComponent*)malloc(sizeof(LinearComponent));
    sprintf(component->base.name, "%s", name);
    component->base.value = value;
    component->voltage = voltage;
    return component;
}

// Функция для создания провода
Wire* createWire(const char* name, Component* startComponent, Component* endComponent) {
    Wire* wire = (Wire*)malloc(sizeof(Wire));
    sprintf(wire->name, "%s", name);
    wire->startComponent = startComponent;
    wire->endComponent = endComponent;
    return wire;
}

// Функция для создания платы
PCB* createPCB(const char* name) {
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    sprintf(pcb->name, "%s", name);
    pcb->components = NULL;
    pcb->wires = NULL;
    pcb->numComponents = 0;
    pcb->numWires = 0;
    pcb->powerConsumption = 0.0;
    return pcb;
}

// Функция для добавления компонента на плату
void addComponent(PCB* pcb, LinearComponent* component) {
    pcb->numComponents++;
    pcb->components = (LinearComponent**)realloc(pcb->components, pcb->numComponents * sizeof(LinearComponent*));
    pcb->components[pcb->numComponents - 1] = component;
}

// Функция для добавления провода на плату
void addWire(PCB* pcb, Wire* wire) {
    pcb->numWires++;
    pcb->wires = (Wire**)realloc(pcb->wires, pcb->numWires * sizeof(Wire*));
    pcb->wires[pcb->numWires - 1] = wire;
}

// Функция для вычисления потребления энергии на плате
float calculatePowerConsumption(PCB* pcb) {
    float totalPower = 0.0;
    for (int i = 0; i < pcb->numComponents; i++) {
        totalPower += pcb->components[i]->voltage * pcb->components[i]->base.value;
    }
    pcb->powerConsumption = totalPower;
    return totalPower;
}

// Функция для вывода информации о плате
void printPCB(PCB* pcb) {
    printf("PCB Name: %s\n", pcb->name);
    printf("Components:\n");
    for (int i = 0; i < pcb->numComponents; i++) {
        printf("- Name: %s, Value: %.2f, Voltage: %.2f\n", pcb->components[i]->base.name, pcb->components[i]->base.value, pcb->components[i]->voltage);
    }
    printf("Wires:\n");
    for (int i = 0; i < pcb->numWires; i++) {
        printf("- Name: %s, Start Component: %s, End Component: %s\n", pcb->wires[i]->name, pcb->wires[i]->startComponent->name, pcb->wires[i]->endComponent->name);
    }
    printf("Power Consumption: %.2f\n", pcb->powerConsumption);
}

int main() {
    PCB* pcb = createPCB("MyPCB");

    // Пример создания компонентов
    LinearComponent* resistor = createLinearComponent("Resistor", 100.0, 5.0);
    LinearComponent* resistor2 = createLinearComponent("Resistor", 420.0, 3.9);
    LinearComponent* transistor = createLinearComponent("Transistor", 0.1, 3.3);
    LinearComponent* transistor2 = createLinearComponent("Transistor", 0.3, 2.1);
    // ... создание остальных компонентов

    // Пример добавления компонентов на плату
    addComponent(pcb, (LinearComponent*)resistor);
    addComponent(pcb, (LinearComponent*)transistor);
    addComponent(pcb, (LinearComponent*)resistor2);
    addComponent(pcb, (LinearComponent*)transistor2);
    // ... добавление остальных компонентов

    // Пример создания и добавления провода на плату
    Wire* wire = createWire("Wire1", (Component*)resistor, (Component*)transistor);
    Wire* wire2 = createWire("Wire1", (Component*)transistor, (Component*)resistor2);
    Wire* wire3 = createWire("Wire1", (Component*)resistor2, (Component*)transistor);
    addWire(pcb, wire);
    addWire(pcb, wire2);
    addWire(pcb, wire3);

    // Вычисление потребления энергии
    calculatePowerConsumption(pcb);

    // Вывод информации о плате
    printPCB(pcb);

    // Освобождение памяти
    // ... освобождение компонентов и проводов
    free(pcb->components);
    free(pcb->wires);
    free(pcb);
    
    return 0;
}
